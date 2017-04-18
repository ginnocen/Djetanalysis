#!/bin/bash

if [[ $# -ne 4 ]]; then
    echo "Usage: ./run-jettrack.sh [input] [output] [jetptmin] [trkptmin]"
    exit 1
fi

g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape || exit 1
g++ draw_jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_jetshape || exit 1

set -x

./jetshape $1 pbpbmc 0 200 $3 recoreco $4
./draw_jetshape pbpbmc pbpbmc_recoreco_${3}_${4}.root $2 recoreco