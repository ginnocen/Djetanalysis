#!/bin/bash

runjobs=0
merger=1


variablehadoop="/mnt/hadoop/cms/store/user/ginnocen/Pythia8_prompt_D0pt0p0_Pthat30_Hydjet_MB/crab_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split/170331_141358"
output="/mnt/hadoop/cms/store/user/ginnocen/DjetFiles_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split"
filelist="MCHydjetDmesonPthat30.list"
mergeroutput="/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split"

if [ "$runjobs" -eq 1 ]
then 
  rm $output/*.root
  ls $variablehadoop/*/*.root >> $filelist
  cmsenv
  cd ../skim
  g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
  cd ../condor
  cp ../skim/D_jet_skim.exe .
  ./skim-condor.sh $filelist $output residuals.tgz
fi

if [ "$merger" -eq 1 ]
then
  rm $mergeroutput/merged.root

  hadd $mergeroutput/merged.root $output/*.root
fi

