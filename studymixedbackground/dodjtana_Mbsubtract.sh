#!/bin/bash

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
   PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
   PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
   echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

if [[ $# -ne 3 ]]
then
    echo "Usage: ./dodjtana_MBsub.sh [domix] [makehists] [doMBsubtract]"
fi

DOMIX=${1:-0}
MAKEHISTS=${2:-0}
DOMBSUB=${3:-0}

#DJETPATH="~/mbfile/T2_US_MIT/submit-hi2/scratch/jwang/Djets/MC"
#WORKPATH="~/mbfile/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC"
DJETPATH="${PREFIX}/scratch/ginnocen"
WORKPATH="${PREFIX}/scratch/ginnocen"
MBPATH="/mnt/T2_US_MIT/hadoop/cms/store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2"
DJETFILE="ginnocen"
MBJETFILE="0"
MBMIXFILE="test_fullstatistics20files"
ISPP=0
ISMC=1
JETPTMIN=40
JETETAMIN=0.0
JETETAMAX=1.6
OUTFILE="MBsubtract_out"

if [[ $DOMIX -eq 1 ]]
then
    g++ MB_D_jet_mix_fast.C $(root-config --cflags --libs) -Wall -O2 -o MB_D_jet_mix_fast.exe
    ./MB_D_jet_mix_fast.exe "${DJETPATH}/${DJETFILE}.root" "${MBPATH}/${MBJETFILE}.root" "${WORKPATH}/${MBMIXFILE}.root" $ISMC $ISPP
    rm MB_D_jet_mix_fast.exe
fi

if [[ $MAKEHISTS -eq 1 ]]
then
    FILES=("${MBMIXFILE}signal" "gen_${MBMIXFILE}" "mixD_${MBMIXFILE}" "mixjet_${MBMIXFILE}" "mixboth_${MBMIXFILE}")
    cd plots
    for i in ${FILES[@]}
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
    ./djtana_savetpl_corr.exe "${WORKPATH}/${MBMIXFILE}.root" "rootfiles/${MBMIXFILE}signal_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 0 
    ./djtana_savetpl_corr.exe "${WORKPATH}/${MBMIXFILE}.root" "rootfiles/gen_${MBMIXFILE}_hists" $COLL $ISMC 3 $JETPTMIN $JETETAMIN $JETETAMAX 0 
    ./djtana_savetpl_corr.exe "${WORKPATH}/${MBMIXFILE}.root" "rootfiles/mixD_${MBMIXFILE}_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 1
    ./djtana_savetpl_corr.exe "${WORKPATH}/${MBMIXFILE}.root" "rootfiles/mixjet_${MBMIXFILE}_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 2
    ./djtana_savetpl_corr.exe "${WORKPATH}/${MBMIXFILE}.root" "rootfiles/mixboth_${MBMIXFILE}_hists" $COLL $ISMC 1 $JETPTMIN $JETETAMIN $JETETAMAX 3
    wait
    ./djtana_plothist.exe "rootfiles/${MBMIXFILE}signal_hists" "${MBMIXFILE}signal" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX &
    ./djtana_plothist.exe "rootfiles/gen_${MBMIXFILE}_hists" "gen_${DJETFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX &
    ./djtana_plothist.exe "rootfiles/mixD_${MBMIXFILE}_hists" "mixD_${MBMIXFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX &
    ./djtana_plothist.exe "rootfiles/mixjet_${MBMIXFILE}_hists" "mixjet_${MBMIXFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX &
    ./djtana_plothist.exe "rootfiles/mixboth_${MBMIXFILE}_hists" "mixboth_${MBMIXFILE}" $COLL $ISMC $JETPTMIN $JETETAMIN $JETETAMAX
    rm djtana_savetpl_corr.exe
    rm djtana_plothist.exe
fi

if [[ $DOMBSUB -eq 1 ]]
then
    g++ MBsubtract_closure.C $(root-config --cflags --libs) -Werror -Wall -O2 -o MBsubtract_closure.exe
    ./MBsubtract_closure.exe "rootfiles/${MBMIXFILE}signal_hists.root" "rootfiles/mixjet_${MBMIXFILE}_hists.root" "rootfiles/gen_${MBMIXFILE}_hists.root" "rootfiles/${OUTFILE}.root"
    rm MBsubtract_closure.exe
fi