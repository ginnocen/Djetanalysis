#!/bin/bash

if [[ $# -ne 7 ]]; then
    echo "usage: ./skim-djet.sh [input file] [output dir] [output filename] [residuals] [isPP] [isMC] [proxy]"
    exit 1
fi

INFILE=$1
DESTINATION=$2
OUTFILE=$3
RESIDUALS=$4
isPP=$5
isMC=$6
export X509_USER_PROXY=${PWD}/$7

SRM_PREFIX="/mnt/hadoop/"
SRM_PATH=${DESTINATION#${SRM_PREFIX}}

tar -xzvf $RESIDUALS

#FILE=$(head -n$(($1+1)) $2 | tail -n1)

echo ./D_jet_skim.exe $INFILE $OUTFILE $isPP $isMC
./D_jet_skim.exe $INFILE $OUTFILE $isPP $isMC

if [[ $? -eq 0 ]]; then
    # gfal-copy file://${PWD}/${OUTFILE}  srm://se01.cmsaf.mit.edu:8443/srm/v2/server?SFN=${DESTINATION}/${OUTFILE}
    gfal-copy file://$PWD/${OUTFILE} gsiftp://se01.cmsaf.mit.edu:2811/${SRM_PATH}/${OUTFILE}
    # mv $OUTFILE $DESTINATION/
fi

rm $OUTFILE