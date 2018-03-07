#!/bin/bash

if [[ $# -ne 3 ]]
then
    echo "Usage: ./dodjtana_MBsub.sh [domix] [makehists] [doMBsubtract]"
fi

DOMIX=${1:-0}
MAKEHISTS=${2:-0}
DOMBSUB=${3:-0}

DJETPATH="/mnt/hadoop/cms/store/user/jwang/Djetsgfal/DjetFiles_20180131_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat15_20171214"
WORKPATH="/afs/lns.mit.edu/user/ginnocen/Djetanalysis/CMSSW_9_0_0/src/Djetanalysis/djtcorrelation"
#WORKPATH="~/scratchmc"
MBPATH="/mnt/hadoop/cms/store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2"
DJETFILE="skim_djet_HiForestAOD_232"
MBJETFILE="0"
MBMIXFILE="fastmix_HiForest_pt_25_pthat_30"
ISPP=0
ISMC=1

if [[ $DOMIX -eq 1 ]]
then
    g++ MB_D_jet_mix_fast.C $(root-config --cflags --libs) -Wall -O2 -o MB_D_jet_mix_fast.exe
    ./MB_D_jet_mix_fast.exe "${DJETPATH}/${DJETFILE}.root" "${MBPATH}/${MBJETFILE}.root" "${WORKPATH}/${MBMIXFILE}.root" $ISMC $ISPP
    rm MB_D_jet_mix_fast.exe
fi
