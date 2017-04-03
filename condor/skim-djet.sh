#!/bin/bash

if [[ $# -ne 6 ]]; then
    echo "usage: ./skim-djet.sh [n] [input list] [output dir] [residuals] [isPP] [isMC]"
    exit 1
fi

tar -xzvf $4

FILE=$(head -n$(($1+1)) $2 | tail -n1)

echo ./D_jet_skim.exe $FILE ${1}.root $5 $6
./D_jet_skim.exe $FILE ${1}.root $5 $6

if [[ $? -eq 0 ]]; then
    mv ${1}.root ${3}
fi
