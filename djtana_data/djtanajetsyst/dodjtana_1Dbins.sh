#!/bin/bash
# dodjtana.sh #

cp ../includes/prefilters_data_1Dbins.h prefilters.h

DO_SAVETPL=${1:-0}
DO_SAVEHIST=${2:-0}
DO_USEHIST=${3:-0}
DO_PLOTHIST=${4:-0}

# Select the systems the macros run on 
jJET=(0 1 2)

# nJET loop
JETPTMIN=(60 80 100 60 80 100)
JETPTMAX=(80 100 999 80 100 999)
JETETAMIN=(0. 0. 0. 0.3 0.3 0.3)
JETETAMAX=(1.6 1.6 1.6 1.6 1.6 1.6)

source dodjtana.sh

rm prefilters.h
