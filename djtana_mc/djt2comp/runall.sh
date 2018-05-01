#!/bin/bash

DO_2DBINS=1
DO_1DBINS=0

[[ $DO_2DBINS -eq 1 ]] && ./docompxsec_2Dbins.sh 1
[[ $DO_1DBINS -eq 1 ]] && ./docompxsec_1Dbins.sh 1
