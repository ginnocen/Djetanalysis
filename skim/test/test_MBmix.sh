#!/bin/bash

DJETFILE="test/test.root"
MBFILE="test/test_MB.root"
OUTFILE="test_mix.root"

cd ../
g++ MB_D_jet_mix.C $(root-config --cflags --libs) -Wall -O2 -o MB_D_jet_mix.exe
./MB_D_jet_mix.exe $DJETFILE $MBFILE $OUTFILE
mv $OUTFILE test/
rm MB_D_jet_mix.exe
cd test/
