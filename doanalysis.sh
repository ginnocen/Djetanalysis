source /net/hisrv0001/home/ginnocen/env.sh
cmsenv
g++ d_jet.C $(root-config --cflags --libs) -Werror -Wall -O2 -o d_jet.exe
./d_jet.exe /export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_merged/total.root output_test.root
