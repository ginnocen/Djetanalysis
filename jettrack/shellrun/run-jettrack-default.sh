#!/bin/bash

#if [[ $# -ne 9 ]]; then
#    echo "Usage: ./run-jettrack.sh [input] [output] [jetptmin] [trkptmin] [isMC] [isPP] [hibinmin] [hibinmax] [recolabel]"
#    exit 1
#fi

#
isMC=${5:-0}
isPP=${6:-1}
HIBINMIN=${7:-0}
HIBINMAX=${8:-200}
LABELRECO=${9:-"recoreco"}

#
DEFAULT_INPUT="/export/d00/scratch/biran/djet/jet-track-skim-pp.root"
DEFAULT_OUTPUT="test.root"
DEFAULT_JETPTMIN=80
DEFAULT_TRKPTMIN=2
#
INPUT=${1:-${DEFAULT_INPUT}}
OUTPUT=${2:-${DEFAULT_OUTPUT}}
JETPTMIN=${3:-${DEFAULT_JETPTMIN}}
TRKPTMIN=${4:-${DEFAULT_TRKPTMIN}}

#
TMC=("data" "mc")
TPP=("pbpb" "pp")
LABEL=${TPP[isPP]}${TMC[isMC]}

#
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape || exit 1
g++ draw_jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_jetshape || exit 1

set -x

./jetshape $INPUT $LABEL $HIBINMIN $HIBINMAX $JETPTMIN $LABELRECO $TRKPTMIN
./draw_jetshape $LABEL ${LABEL}_${LABELRECO}_${JETPTMIN}_${TRKPTMIN}.root $OUTPUT $LABELRECO

rm jetshape
rm draw_jetshape

set +x