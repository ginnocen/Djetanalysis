#!/bin/bash

if [[ $0 != *.sh ]]
then
    echo -e "\e[31;1merror:\e[0m use \e[32;1m./script.sh\e[0m instead of \e[32;1msource script.sh\e[0m"
    return 1
fi

#
iPTHAT=8
j=1
#
isMC=1
isPP=0
JETPTMIN=0
MAXFILENO=10000
ifCHECKEMPTY=0

#
PTHATS=(0 5 10 15 30 50 80 120 170)
DATES=(171214_180030 171214_190100 171214_190718 171214_191746 171214_191842 171214_192148 171214_195924 171214_200125 171214_200812)

movetosubmit=${1:-0}
runjobs=${2:-0}
merger=${3:-0}

#
INPUTDIR="/mnt/hadoop/cms/store/user/wangj/Pythia8_prompt_D0pt0p0_Pthat${PTHATS[iPTHAT]}_Hydjet_MB/crab_HiForestAOD_DfinderMC_PbPb_20171214_Pthat${PTHATS[iPTHAT]}_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/${DATES[iPTHAT]}/000${j}/"
OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djetsgfal/"
OUTPUTSUBDIR="DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat${PTHATS[iPTHAT]}_20171214"

MERGEOUTPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
WORKDIR="/work/$USER/Djet/"

OUTPUTDIR="${OUTPUTPRIDIR}/${OUTPUTSUBDIR}"
LOGDIR="logs/log_${OUTPUTSUBDIR}"

##

if [[ ! -d "$WORKDIR" ]]
then
    mkdir -p $WORKDIR
fi

if [ "$movetosubmit" -eq 1 ]
then
    if [[ $(hostname) == "submit-hi2.mit.edu" || $(hostname) == "submit.mit.edu" ]]
    then
        cd ../skim
        g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
        cd ../condor

        mv ../skim/D_jet_skim.exe $WORKDIR/
        cp residuals.tgz $WORKDIR/
        cp $0 $WORKDIR/
        cp skim_djet_checkfile.sh $WORKDIR/
        cp skim_condor_checkfile.sh $WORKDIR/
    else
        echo -e "\e[31;1merror:\e[0m compile macros on \e[32;1msubmit-hiX.mit.edu\e[0m or \e[32;1msubmit.mit.edu\e[0m."
    fi
fi

if [ "$runjobs" -eq 1 ]
then
    if [[ $(hostname) == "submit.mit.edu" ]]
    then
        ./skim_condor_checkfile.sh "$INPUTDIR" $OUTPUTDIR $MAXFILENO $LOGDIR residuals.tgz $isPP $isMC $JETPTMIN $ifCHECKEMPTY
    else
        echo -e "\e[31;1merror:\e[0m submit jobs on \e[32;1msubmit.mit.edu\e[0m."
    fi
fi

if [ "$merger" -eq 1 ]
then
   rm ${MERGEOUTPUTDIR}/${OUTPUTSUBDIR}.root
   hadd ${MERGEOUTPUTDIR}/${OUTPUTSUBDIR}.root ${OUTPUTPRIDIR}/${OUTPUTSUBDIR}/*.root
fi

