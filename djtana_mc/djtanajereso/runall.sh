#!/bin/bash

SAVETPL=1
SAVEHIST=1
USEHIST=1
PLOTHIST=1

sed -i 's/kRECOGEN=(.*/kRECOGEN=(3)/g' dodjtana.sh
# ./dodjtana_2Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST 0 0 1 0 1 1
# ./dodjtana_1Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST 0 0 1 0 1 1
./dodjtana_2Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST 0 0 1 0 2 1
./dodjtana_1Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST 0 0 1 0 2 1
sed -i 's/kRECOGEN=(.*/kRECOGEN=(0 1 2 3)/g' dodjtana.sh