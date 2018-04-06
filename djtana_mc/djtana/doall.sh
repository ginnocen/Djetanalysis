#!/bin/bash

#
DO__CLOSURE=1
DO__RESO=0
DO__CLOSURE_CORR=0
DO__ALL_CORR=0

#
DO_SAVETPL=1
DO_SAVEHIST=1
DO_USEHIST=1
DO_PLOTHIST=1

# closure (0 1 2 3)
if [[ $DO__CLOSURE -eq 1 ]]; then
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST
    ./dodjtana.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST
fi

# resolution (3)
if [[ $DO__RESO -eq 1 ]]; then
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 0 0 1 0 0 0
    ./dodjtana.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 0 0 1 0 0 0
fi

# closure corr (1)
if [[ $DO__CLOSURE_CORR -eq 1 ]]; then
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 0 1 1 1 1
    ./dodjtana.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 0 1 1 1 1
fi

# all corr (0)
if [[ $DO__ALL_CORR -eq 1 ]]; then
    ./dodjtana_2Dbins.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 1 1 1 1 1
    ./dodjtana.sh $DO_SAVETPL $DO_SAVEHIST $DO_USEHIST $DO_PLOTHIST 1 1 1 1 1 1
fi