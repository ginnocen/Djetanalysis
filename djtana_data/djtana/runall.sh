#!/bin/bash

DO_2DBINS=1
DO_1DBINS=0

SAVETPL=0
SAVEHIST=0
USEHIST=0
PLOTHIST=0

[[ $DO_2DBINS -eq 1 ]] && ./dodjtana_2Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST
[[ $DO_1DBINS -eq 1 ]] && ./dodjtana_1Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST

SAVERATIO=1
PLOTRATIO=1
FINALPLOT=1

[[ $DO_2DBINS -eq 1 ]] && ./dodjtana_ratio_2Dbins.sh $SAVERATIO $PLOTRATIO $FINALPLOT
[[ $DO_1DBINS -eq 1 ]] && ./dodjtana_ratio_1Dbins.sh $SAVERATIO $PLOTRATIO $FINALPLOT



