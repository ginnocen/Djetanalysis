source /net/hisrv0001/home/ginnocen/env.sh
cmsenv
sampleData="/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_merged/total.root"
sampleMC="/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split/merged.root"

outputData="myoutputdata.root"
outputMC="myoutputMC.root"

g++ d_jet.C $(root-config --cflags --libs) -Werror -Wall -O2 -o d_jet.exe
./d_jet.exe $sampleMC $outputMC
