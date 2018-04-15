#!/bin/bash
# docompxsec.sh #

DO_USEHIST=${1:-0}

cp ../includes/prefilters_data_2Dbins.h prefilters.h

# Select the systems the macros run on 
jJET=(0)

# nJET loop
JETPTMIN=(60 60)
JETPTMAX=(999 999)
JETETAMIN=(0. 0.3)
JETETAMAX=(1.6 1.6)

source docompxsec_ratio.sh

rm prefilters.h