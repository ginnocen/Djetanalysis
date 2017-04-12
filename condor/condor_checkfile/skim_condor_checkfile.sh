#!/bin/bash

if [[ $# -ne 7 ]]; then
    echo "usage: ./skim-condor.sh [input dir] [output dir] [max jobs] [log dir] [residuals] [isPP] [isMC]"
    exit 1
fi

DATASET=$1
DESTINATION=$2
MAXFILES=$3
LOGDIR=$4
RESIDUALS=$5
isPP=$6
isMC=$7

rm filelist.txt
ls $DATASET  | awk '{print "" $0}' >> filelist.txt

if [ ! -d $DESTINATION ]
then
    mkdir -p $DESTINATION
fi
if [ ! -d $LOGDIR ]
then
    mkdir -p $LOGDIR
fi

counter=0
for i in `cat filelist.txt`
do
    if [ $counter -ge $MAXFILES ]
    then
        break
    fi
    ifexist=`ls ${DESTINATION}/skim_djet_$i`
    if [ -z $ifexist ]
    then
        infn=`echo $i | awk -F "." '{print $1}'`
        INFILE="${DATASET}/$i"
	
	cat > skim-djet.condor <<EOF

Universe     = vanilla
Initialdir   = $PWD/
Notification = Error
Executable   = $PWD/skim_djet_checkfile.sh
Arguments    = $INFILE $DESTINATION skim_djet_${infn}.root $RESIDUALS $isPP $isMC
GetEnv       = True
Output       = $LOGDIR/log-${infn}.out
Error        = $LOGDIR/log-${infn}.err
Log          = $LOGDIR/log-${infn}.log
Rank         = Mips
+AccountingGroup = "group_cmshi.$(whoami)"
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = D_jet_skim.exe,residuals.tgz

Queue 
EOF
	condor_submit skim-djet.condor
	mv skim-djet.condor $LOGDIR/log-${infn}.condor
	counter=$(($counter+1))	
    fi
done

echo "Submitted $counter jobs to Condor."