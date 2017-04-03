#!/bin/bash

runjobs=0
merger=1

variablehadoop="/mnt/hadoop/cms/store/user/ginnocen/HighPtJet80/crab_pp_5TeV_HighPtJet80_Dfinder_2april/170402_230535"
output="/mnt/hadoop/cms/store/user/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_unmerged_v1"
filelist="HighPtJet80_pp_5TeV_Dfinder_2april_v1.list"
mergeroutput="/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1"

if [ "$runjobs" -eq 1 ]
then 
  
  rm -rf $output
  mkdir $output
  rm $filelist
  ls $variablehadoop/*/*.root >> $filelist
  cmsenv
  cd ../skim
  g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
  cd ../condor
  cp ../skim/D_jet_skim.exe .
  ./skim-condor.sh $filelist $output residuals.tgz 1 0
fi

if [ "$merger" -eq 1 ]
then
  rm -rf $mergeroutput
  mkdir $mergeroutput

  hadd $mergeroutput/merged.root $output/*.root
fi

