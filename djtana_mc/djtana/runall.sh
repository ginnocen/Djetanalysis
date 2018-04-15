#!/bin/bash

#
DO__CLOSURE=1
DO__RESO=1
DO__CLOSURE_CORR=0
DO__ALL_CORR=0

#
DO_SAVETPL=1
DO_SAVEHIST=1
DO_USEHIST=1
DO_PLOTHIST=1

# closure (0 1 2 3)
if [[ $DO__CLOSURE -eq 1 ]]; then
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana.sh
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 0 0 1 1 1 1
    ./dodjtana_1Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 0 0 1 1 1 1
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana.sh
fi

# resolution (3)
if [[ $DO__RESO -eq 1 ]]; then
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(3)/g' dodjtana.sh
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 0 0 1 0 0 0
    ./dodjtana_1Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 0 0 1 0 0 0
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana.sh
fi

# closure corr (1)
if [[ $DO__CLOSURE_CORR -eq 1 ]]; then
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(1)/g' dodjtana.sh
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 0 1 1 1 1
    ./dodjtana_1Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 0 1 1 1 1
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana.sh
fi

# all corr (0)
if [[ $DO__ALL_CORR -eq 1 ]]; then
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0)/g' dodjtana.sh
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 1 1 1 1 1
    ./dodjtana_1Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 1 1 1 1 1
    sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana.sh
fi