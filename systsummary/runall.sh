#!/bin/bash

DO_2DBINS=1
DO_1DBINS=0

[[ $DO_2DBINS -eq 1 ]] && ./dosystsummary_2Dbins.sh 1
[[ $DO_1DBINS -eq 1 ]] && ./dosystsummary_1Dbins.sh 1
