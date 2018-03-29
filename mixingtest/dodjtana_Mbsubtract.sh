#!/bin/bash

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
   PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
   PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
   echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

if [[ $# -ne 3 ]]
then
    echo "Usage: ./dodjtana_MBsub.sh [domix] [makehists] [doMBsubtract]"
fi

DOMIX=${1:-0}

#DJETPATH="~/mbfile/T2_US_MIT/submit-hi2/scratch/jwang/Djets/MC"
#WORKPATH="~/mbfile/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC"
DJETPATH="${PREFIX}/scratch/ginnocen"
WORKPATH="${PREFIX}/scratch/ginnocen"
MBPATH="/mnt/T2_US_MIT/hadoop/cms/store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2"
DJETFILE="ginnocen"
MBJETFILE="0"
MBMIXFILE="test_fullstatistics20files"
ISPP=0
ISMC=1
JETPTMIN=40
JETETAMIN=0.0
JETETAMAX=1.6
OUTFILE="MBsubtract_out"

if [[ $DOMIX -eq 1 ]]
then
    g++ MB_D_jet_mix_fast.C $(root-config --cflags --libs) -Wall -O2 -o MB_D_jet_mix_fast.exe
    ./MB_D_jet_mix_fast.exe "${DJETPATH}/${DJETFILE}.root" "${MBPATH}/${MBJETFILE}.root" "${WORKPATH}/${MBMIXFILE}.root" $ISMC $ISPP
    rm MB_D_jet_mix_fast.exe
fi
