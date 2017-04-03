#!/bin/bash

runjobs=1
merger=0

variablehadoop="/mnt/hadoop/cms/store/user/ginnocen/HighPtJet80/crab_pp_5TeV_HighPtJet80_Dfinder_2april/170402_230535"
output="/mnt/hadoop/cms/store/user/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_unmerged"
filelist="HighPtJet80_pp_5TeV_Dfinder_2april.list"
mergeroutput="/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april"

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

