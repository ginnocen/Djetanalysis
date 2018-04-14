#!/bin/bash
# dodjtana_ratio.sh #

DO_SAVERATIO=${1:-0}
DO_PLOTRATIO=${2:-0}
DO_FINALPLOT=${3:-0}

cp ../includes/prefilters_data_2Dbins.h prefilters.h

# Select the systems the macros run on 
jJET=(0 1)

# nJET loop
JETPTMIN=(60 60)
JETPTMAX=(999 999)
JETETAMIN=(0.0 0.3)
JETETAMAX=(1.6 1.6)

source dodjtana_ratio.sh

rm prefilters.h