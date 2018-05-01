#!/bin/bash

DO_2DBINS=1
DO_1DBINS=0

[[ $DO_2DBINS -eq 1 ]] && ./docompxsec_ratio_2Dbins.sh 1
[[ $DO_1DBINS -eq 0 ]] && ./docompxsec_ratio_1Dbins.sh 1
