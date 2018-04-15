#!/bin/bash
# dopdfvar_ratio.sh #

cp ../includes/prefilters_data_2Dbins.h prefilters.h

DO_PLOTRATIO=${1:-0}

# Select the systems the macros run on 
jJET=(0)

# nJET loop
JETPTMIN=(60 60)
JETPTMAX=(999 999)
JETETAMIN=(0 0.3)
JETETAMAX=(1.6 1.6)

source dopdfvar_ratio.sh

rm prefilters.h
