#!/bin/bash

DO_SKIM=${1:-0}

[[ -f ../D_jet_skim.exe ]] && { rm ../D_jet_skim.exe ; }

INFILE=/mnt/hadoop/cms/store/user/ginnocen/HIHardProbes/crab_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_26March/170327_025517/0000/HiForestAOD_524.root
MIXFILE="/mnt/hadoop/cms/store/user/jwang/Djets/HiForestAOD_DfinderData_PbPb_20180329_HIMinimumBias2/crab_HiForestAOD_DfinderData_PbPb_20180329_HIMinimumBias2_part2_1_0000_1.root"
OUTFILE="test.root"
isPP=0
isMC=0
JETPTMIN=0

cd ../
g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
if [[ $DO_SKIM -eq 1 ]]; then
    echo $MIXFILE > listmixing.list
    ./D_jet_skim.exe $INFILE $OUTFILE $isPP $isMC $JETPTMIN
    mv $OUTFILE test/
    # rm listmixing.list
fi
rm D_jet_skim.exe
cd test/