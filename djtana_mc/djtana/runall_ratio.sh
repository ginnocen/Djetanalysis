#!/bin/bash

DO_2DBINS=1
DO_1DBINS=0

#
DO__CLOSURE=1
DO__RESO=0
DO__CLOSURE_CORR=0
DO__ALL_CORR=0

#
DO_SAVERATIO=1
DO_PLOTRATIO=0

# closure (0 1 2 3)
if [[ $DO__CLOSURE -eq 1 ]]; then
    # sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana_ratio.sh
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(1 3)/g' dodjtana_ratio.sh
    ./dodjtana_ratio_2Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 0 0 1 1 1 1 1
    ./dodjtana_ratio_1Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 0 0 1 1 1 1 1
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana_ratio.sh
fi

# resolution (3)
if [[ $DO__RESO -eq 1 ]]; then
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(3)/g' dodjtana_ratio.sh
    ./dodjtana_ratio_2Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 0 0 1 0 0 0 1
    ./dodjtana_ratio_1Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 0 0 1 0 0 0 1
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana_ratio.sh
fi

# closure corr (1)
if [[ $DO__CLOSURE_CORR -eq 1 ]]; then
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(1)/g' dodjtana_ratio.sh
    ./dodjtana_ratio_2Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 1 0 1 1 1 1 1
    ./dodjtana_ratio_1Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 1 0 1 1 1 1 1
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana_ratio.sh
fi

# all corr (0)
if [[ $DO__ALL_CORR -eq 1 ]]; then
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0)/g' dodjtana_ratio.sh
    ./dodjtana_ratio_2Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 1 1 1 1 1 1 1
    ./dodjtana_ratio_1Dbins.sh $DO_SAVERATIO $DO_PLOTRATIO 1 1 1 1 1 1 1
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana_ratio.sh
fi