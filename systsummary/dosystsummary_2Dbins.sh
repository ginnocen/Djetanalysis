#!/bin/bash
# dosystsummary.sh #

cp ../includes/prefilters_data_2Dbins.h prefilters.h

DO_PLOTHIST=${1:-0}

# Select the systems the macros run on
jJET=(0)

# nJET loop
JETPTMIN=(60)
JETPTMAX=(999)
JETETAMIN=(0.)
JETETAMAX=(1.6)

source dosystsummary.sh

rm prefilters.h