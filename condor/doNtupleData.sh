#!/bin/bash

runjobs=0
merger=1


#variablehadioop="/mnt/hadoop/cms/store/user/ginnocen/HIHardProbes/crab_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_26March/170327_025517"
output="/mnt/hadoop/cms/store/user/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part4_26March_finalMerge2April"
filelist="PbPb_Data_HiForest_finalMerge2April_part4.list"
mergeroutput="/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April"

if [ "$runjobs" -eq 1 ]
then 

  cd ../skim
  g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
  cd ../condor
  cp ../skim/D_jet_skim.exe .
  ./skim-condor.sh $filelist $output residuals.tgz
fi

if [ "$merger" -eq 1 ]
then
   rm -rf $mergeroutput
   mkdir $mergeroutput

   hadd $mergeroutput/merged_1.root /mnt/hadoop/cms/store/user/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_26March_finalMerge2April/*.root
   hadd $mergeroutput/merged_2.root /mnt/hadoop/cms/store/user/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part2_26March_finalMerge2April/*.root
   hadd $mergeroutput/merged_3.root /mnt/hadoop/cms/store/user/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part3_26March_finalMerge2April/*.root
   hadd $mergeroutput/merged_4.root /mnt/hadoop/cms/store/user/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part4_26March_finalMerge2April/*.root
   hadd $mergeroutput/merged_total.root hadd $mergeroutput/merged_1.root hadd $mergeroutput/merged_2.root hadd $mergeroutput/merged_3.root hadd $mergeroutput/merged_4.root

fi

