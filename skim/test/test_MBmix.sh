#!/bin/bash

DJETFILE="/mnt/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC/ten_HiForest.root"
MBFILE="/mnt/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC/ten_MB_HiForest.root"
OUTFILE="/mnt/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC/mix_ten_HiForest.root"

cd ../
rm $OUTFILE
g++ MB_D_jet_mix.C $(root-config --cflags --libs) -Wall -O2 -o MB_D_jet_mix.exe
./MB_D_jet_mix.exe $DJETFILE $MBFILE $OUTFILE
rm MB_D_jet_mix.exe
cd test/
