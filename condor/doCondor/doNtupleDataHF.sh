#!/bin/bash

runjobs=0
merger=1

variablehadoop="/mnt/hadoop/cms/store/user/wangj/HeavyFlavor/crab_DfinderData_pp_20170405_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/170405_215700/"
output="/mnt/hadoop/cms/store/user/jwang/DjetFiles_pp_5TeV_HeavyFlavor_Dfinder_Data_20170405/"
filelist="Data_finalmerge_20170405.list"
mergeroutputdir="/export/d00/scratch/jwang/"
mergeroutput="DjetFiles_pp_5TeV_HeavyFlavor_Dfinder_Data_20170405_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar"

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
   rm -rf ${mergeroutputdir}/${mergeroutput}
   #mkdir ${mergeroutputdir}/${mergeroutput}
   cp -r $output ${mergeroutputdir}/${mergeroutput}
   hadd ${mergeroutputdir}/${mergeroutput}.root ${mergeroutputdir}/${mergeroutput}/*.root
fi

