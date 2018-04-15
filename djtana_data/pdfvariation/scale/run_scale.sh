#!/bin/bash

mkdir -p plotscale

g++ scale.C $(root-config --libs --cflags) -g -o scale.exe
./scale.exe
rm scale.exe