#!/bin/bash

INFILE="/export/d00/scratch/jwang/Djets/HiForestAOD_DfinderMC_PbPb_20180326_Pythia8_prompt_D0pt0p0_Pthat30_Hydjet_MB_20files.root"
INFILEmixing="/afs/lns.mit.edu/user/ginnocen/Djetanalysis/CMSSW_9_0_0/src/Djetanalysis/skim/test/listmixing.list"
OUTFILE="/export/d00/scratch/ginnocen/test_fullstatistics20files.root"
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

# entire MC production
#/mnt/T2_US_MIT/hadoop/cms/store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root

#/export/d00/scratch/jwang/Djets/MC/mixing/HiForestAOD_Hydjet_Quenched_MinBias_5020GeV_750_NoPU_500evts.root
