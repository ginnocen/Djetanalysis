#!/bin/bash

if [[ $# -ne 3 ]]
then
    echo "Usage: ./dodjtana_MBsub.sh [domix] [makehists] [doMBsubtract]"
fi

DOMIX=${1:-0}
MAKEHISTS=${2:-0}
DOMBSUB=${3:-0}

WORKPATH="/mnt/T2_US_MIT/submit-hi2/scratch/${USER}/Djet/MC"
DJETFILE="hundred_HiForest"
MBJETFILE="MB_hundred_HiForest"
MBMIXFILE="mix_hundred_HiForest"
OUTFILE="subtracted"
ISPP=0
ISMC=1

if [[ $DOMIX -eq 1 ]]
then
    cd ../skim
    g++ MB_D_jet_mix.C $(root-config --cflags --libs) -Werror -Wall -O2 -o MB_D_jet_mix.exe
    ./MB_D_jet_mix.exe "${WORKPATH}/${DJETFILE}.root" "${WORKPATH}/${MBJETFILE}.root" "${WORKPATH}/${MBMIXFILE}.root"
    rm MB_D_jet_mix.exe
    cd ../djtcorrelation
fi

if [[ $MAKEHISTS -eq 1 ]]
then
    if [[ $ISPP -eq 0 ]]
    then
        COLL="PbPb"
    else
        COLL="pp"
    fi
    g++ djtana_savetpl_corr.C $(root-config --cflags --libs) -Wall -O2 -o djtana_savetpl_corr.exe
    g++ djtana_plothist.C $(root-config --cflags --libs) -Wall -O2 -o djtana_plothist.exe
    ./djtana_savetpl_corr.exe "${WORKPATH}/${DJETFILE}.root" "rootfiles/${DJETFILE}_hists" $COLL $ISMC 0 40 0.0 2.0 &
    ./djtana_savetpl_corr.exe "${WORKPATH}/${MBMIXFILE}.root" "rootfiles/${MBMIXFILE}_hists" $COLL $ISMC 0 40 0.0 2.0
    wait
    ./djtana_plothist.exe "rootfiles/${DJETFILE}_hists.root" $DJETFILES $COLL $ISMC 40 0.0 2.0 &
    ./djtana_plothist.exe "rootfiles/${MBMIXFILE}_hists.root" $MBMIXFILE $COLL $ISMC 40 0.0 2.0
    rm djtana_savetpl_corr.exe
    rm djtana_plothist.exe
fi

if [[ $DOMBSUB -eq 1 ]]
then
    g++ MBsubtract.C $(root-config --cflags --libs) -Werror -Wall -O2 -o MBsubtract.exe
    ./MBsubtract.exe "rootfiles/${DJETFILE}_hists.root" "rootfiles/${MBMIXFILE}_hists.root" "rootfiles/${OUTFILE}.root"
    rm MBsubtract.exe
fi
    
