#!/bin/bash
# doeff.sh #

cp ../includes/prefilters_data_2Dbins.h prefilters.h

DO_SAVETPL=${1:-0}
DO_USEHIST=${2:-0}
DO_PLOTHIST=${3:-0}

# Select the systems the macros run on 
jJET=(0)
# nJET loop
JETPTMIN=(60)
JETPTMAX=(999)
JETETAMIN=(0.)
JETETAMAX=(1.6)

source doeff.sh

rm prefilters.h
