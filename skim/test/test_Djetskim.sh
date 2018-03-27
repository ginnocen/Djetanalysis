#!/bin/bash

INFILE="/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/MC/mixing/crab_HiForestAOD_DfinderMC_PbPb_20180326_Pthat80_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_25.root"
INFILEmixing="/afs/lns.mit.edu/user/ginnocen/Djetanalysis/CMSSW_9_0_0/src/Djetanalysis/skim/test/listmixing.list"
OUTFILE="test.root"
isPP=0
isMC=1
JETPTMIN=0
START=0
END=-1

cd ../
g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
./D_jet_skim.exe $INFILE $OUTFILE $isPP $isMC $JETPTMIN $START $END $INFILEmixing 
mv $OUTFILE test/
rm D_jet_skim.exe
cd test/
