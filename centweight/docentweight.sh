#!/bin/bash

DO_CENTWEIGHT=${1:-0}

[[ ! -d outf ]] && { mkdir outf ; }

g++ centweight.C $(root-config --libs --cflags) -g -o centweight.exe
[[ $DO_CENTWEIGHT -eq 1 ]] && { ./centweight.exe ; }

rm centweight.exe