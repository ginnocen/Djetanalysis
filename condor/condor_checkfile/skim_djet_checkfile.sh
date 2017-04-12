#!/bin/bash

if [[ $# -ne 6 ]]; then
    echo "usage: ./skim-djet.sh [input file] [output dir] [output filename] [residuals] [isPP] [isMC]"
    exit 1
fi

INFILE=$1
DESTINATION=$2
OUTFILE=$3
RESIDUALS=$4
isPP=$5
isMC=$6

tar -xzvf $RESIDUALS

#FILE=$(head -n$(($1+1)) $2 | tail -n1)

echo ./D_jet_skim.exe $INFILE $OUTFILE $isPP $isMC
./D_jet_skim.exe $INFILE $OUTFILE $isPP $isMC

if [[ $? -eq 0 ]]; then
    mv $OUTFILE $DESTINATION/
fi
