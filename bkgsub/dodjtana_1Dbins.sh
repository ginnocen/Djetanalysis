#!/bin/bash
# dodjtana.sh #

cp ../includes/prefilters_data_1Dbins.h prefilters.h

DO_SAVEHIST=${1:-0}
DO_PLOTHIST=${2:-0}

# Select the systems the macros run on 
jJET=(0 1 2)

# nJET loop
JETPTMIN=(60 80 100)
JETPTMAX=(80 100 999)
JETETAMIN=(0. 0. 0.)
JETETAMAX=(1.6 1.6 1.6)

source dodjtana.sh

rm prefilters.h