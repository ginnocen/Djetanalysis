#!/bin/bash

DO_SKIM=${1:-0}

[[ -f ../D_jet_skim.exe ]] && { rm ../D_jet_skim.exe ; }

INFILE=/mnt/hadoop/cms/store/user/wangj/Hydjet_Quenched_MinBias_5020GeV_750/crab_HiForestAOD_DfinderMC_PbPb_20180326_Hydjet_Quenched_MinBias_dPt4tkPt1p5Alpha0p2Decay2/180327_222731/0000/HiForestAOD_100.root
# MIXFILE="/mnt/hadoop/cms/store/user/jwang/Djets/HiForestAOD_DfinderData_PbPb_20180329_HIMinimumBias2/crab_HiForestAOD_DfinderData_PbPb_20180329_HIMinimumBias2_part2_1_0000_5.root"
MIXFILE="/mnt/hadoop/cms/store/user/jwang/Djets/HiForestAOD_DfinderMC_PbPb_20180326_Hydjet_Quenched_MinBias_dPt4tkPt1p5Alpha0p2Decay2.root"
OUTFILE="test.root"
isPP=0
isMC=1
JETPTMIN=0
iSTART=0
iEND=10

cd ../
g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
if [[ $DO_SKIM -eq 1 ]]; then
    echo $MIXFILE > listmixing.list
    ./D_jet_skim.exe $INFILE $OUTFILE $isPP $isMC $JETPTMIN $iSTART $iEND
    mv $OUTFILE test/
    rm listmixing.list
fi
rm D_jet_skim.exe
cd test/