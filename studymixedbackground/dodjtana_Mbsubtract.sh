#!/bin/bash

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
   PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
   PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
   echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

if [[ $# -ne 2 ]]
then
    echo "Usage: ./dodjtana_MBsub.sh [makehists] [doMBsubtract]"
fi

MAKEHISTS=${1:-0}
DOMBSUB=${2:-0}

INPUTPATH="~/mbfile/T2_US_MIT/submit-hi2/scratch/ginnocen"
INPUTFILE="test_fullstatistics20files"
ISPP=0
ISMC=1
JETPTMIN=40
JETETAMIN=0.0
JETETAMAX=1.6
OUTFILE="MBsubtract_out"

if [[ $MAKEHISTS -eq 1 ]]
then
    if [[ ! -d plots ]]
    then
        mkdir -p plots
    fi
    FOLDERS=("${INPUTFILE}signal" "gen_${INPUTFILE}" "mixD_${INPUTFILE}" "mixjet_${INPUTFILE}" "mixboth_${INPUTFILE}")
    cd plots
    for i in ${FOLDERS[@]}
    do
        if [[ ! -d $i ]]
        then
            mkdir -p $i
        fi
    done
    cd ..
    if [[ $ISPP -eq 0 ]]
    then
        COLL="PbPb"
    else
        COLL="pp"
    fi
    g++ djtana_savetpl_corr.C $(root-config --cflags --libs) -Wall -O2 -o djtana_savetpl_corr.exe
    g++ djtana_plothist.C $(root-config --cflags --libs) -Wall -O2 -o djtana_plothist.exe
    ./djtana_savetpl_corr.exe "${INPUTPATH}/${INPUTFILE}.root" "rootfiles/${INPUTFILE}signal_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 0 
    ./djtana_savetpl_corr.exe "${INPUTPATH}/${INPUTFILE}.root" "rootfiles/gen_${INPUTFILE}_hists" $COLL $ISMC 3 $JETPTMIN $JETETAMIN $JETETAMAX 0 
    ./djtana_savetpl_corr.exe "${INPUTPATH}/${INPUTFILE}.root" "rootfiles/mixD_${INPUTFILE}_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 1 
    ./djtana_savetpl_corr.exe "${INPUTPATH}/${INPUTFILE}.root" "rootfiles/mixjet_${INPUTFILE}_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 2 
    ./djtana_savetpl_corr.exe "${INPUTPATH}/${INPUTFILE}.root" "rootfiles/mixboth_${INPUTFILE}_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 3
    wait
    ./djtana_plothist.exe "rootfiles/${INPUTFILE}signal_hists" "${INPUTFILE}signal" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX 
    ./djtana_plothist.exe "rootfiles/gen_${INPUTFILE}_hists" "gen_${INPUTFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX 
    ./djtana_plothist.exe "rootfiles/mixD_${INPUTFILE}_hists" "mixD_${INPUTFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX 
    ./djtana_plothist.exe "rootfiles/mixjet_${INPUTFILE}_hists" "mixjet_${INPUTFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX 
    ./djtana_plothist.exe "rootfiles/mixboth_${INPUTFILE}_hists" "mixboth_${INPUTFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX
    rm djtana_savetpl_corr.exe
    rm djtana_plothist.exe
fi

if [[ $DOMBSUB -eq 1 ]]
then
    g++ MBsubtract_closure.C $(root-config --cflags --libs) -Werror -Wall -O2 -o MBsubtract_closure.exe
    ./MBsubtract_closure.exe "rootfiles/${INPUTFILE}signal_hists.root" "rootfiles/mixjet_${INPUTFILE}_hists.root" "rootfiles/gen_${INPUTFILE}_hists.root" "rootfiles/${OUTFILE}.root"
    rm MBsubtract_closure.exe
fi