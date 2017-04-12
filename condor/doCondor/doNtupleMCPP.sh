#!/bin/bash

runjobs=1
merger=1


variablehadoop="/mnt/hadoop/cms/store/user/wangj/Pythia8_prompt_D0pt0p0_Pthat30_pp502_TuneCUETP8M1/crab_DfinderMC_pp_20170404_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/170404_181158/"
output="/mnt/hadoop/cms/store/user/jwang/DjetFiles_pp_5TeV_TuneCUETP8M1_Dfinder_MC_pthat30_20170404/"
filelist="MCTuneCUETP8M1DmesonPthat30_finalmerge_20170404.list"
mergeroutputdir="/export/d00/scratch/jwang/"
mergeroutput="DjetFiles_pp_5TeV_TuneCUETP8M1_Dfinder_MC_pthat30_20170404"

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
  ./skim-condor.sh $filelist $output residuals.tgz 1 1 
fi

if [ "$merger" -eq 1 ]
then
   rm -rf ${mergeroutputdir}/${mergeroutput}
   #mkdir ${mergeroutputdir}/${mergeroutput}
   cp -r $output ${mergeroutputdir}/${mergeroutput}
   hadd ${mergeroutputdir}/${mergeroutput}.root ${mergeroutputdir}/${mergeroutput}/*.root
fi

