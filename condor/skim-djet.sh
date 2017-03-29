#!/bin/bash

if [[ $# -lt 4 ]]; then
    echo "usage: ./skim-djet.sh [n] [input list] [output dir] [residuals]"
    exit 1
fi

tar -xzvf $4

FILE=$(head -n$(($1+1)) $2 | tail -n1)

echo ./D_jet_skim.exe $FILE ${1}.root akPu3PFJetAnalyzer 0 0
./D_jet_skim.exe $FILE ${1}.root akPu3PFJetAnalyzer 0 0

if [[ $? -eq 0 ]]; then
    mv ${1}.root ${3}
fi
