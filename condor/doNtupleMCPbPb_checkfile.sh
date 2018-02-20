#!/bin/bash

if [[ $0 != *.sh ]]
then
    echo -e "\e[31;1merror:\e[0m use \e[32;1m./script.sh\e[0m instead of \e[32;1msource script.sh\e[0m"
    return 1
fi

#
iPTHAT=7
j=0
#
isMC=1
isPP=0
JETPTMIN=25
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
OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/mjpeters/Djetsgfal"
#OUTPUTPRIDIR="/home/mjpeters/scratchmc"
OUTPUTSUBDIR="HiForest_pt_${JETPTMIN}_pthat_${PTHATS[iPTHAT]}"

MERGEOUTPUTDIR="/mnt/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC"
#MERGEOUTPUTDIR="/home/mjpeters/scratchmc"
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
        g++ MB_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o MB_jet_skim.exe

        mv ../skim/D_jet_skim.exe $WORKDIR/
        mv ../skim/MB_jet_skim.exe $WORKDIR/

        cd ../condor
        
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
   rm ${MERGEOUTPUTDIR}/MB_${OUTPUTSUBDIR}.root
   hadd -f ${MERGEOUTPUTDIR}/${OUTPUTSUBDIR}.root ${OUTPUTPRIDIR}/${OUTPUTSUBDIR}/*.root
   #hadd -j ${MERGEOUTPUTDIR}/MB_${OUTPUTSUBDIR}.root ${OUTPUTPRIDIR}/${OUTPUTSUBDIR}/[M]*[_][2][0-4][0-9].root
   wait
fi

