#!/bin/bash

if [[ $# -ne 3 ]]
then
    echo "Usage: ./dodjtana_MBsub.sh [domix] [makehists] [doMBsubtract]"
fi

DOMIX=${1:-0}
MAKEHISTS=${2:-0}
DOMBSUB=${3:-0}

WORKPATH="/mnt/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC"
#WORKPATH="~/scratchmc"
MBPATH="/mnt/hadoop/cms/store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2"
DJETFILE="HiForest_pt_25_pthat_120"
MBJETFILE="0"
MBMIXFILE="fastmix_HiForest_pt_25_pthat_120"
OUTFILE="subtracted_pt_25_pthat_120"
ISPP=0
ISMC=1

if [[ $DOMIX -eq 1 ]]
then
    cd ../skim
    g++ MB_D_jet_mix_fast.C $(root-config --cflags --libs) -Wall -O2 -o MB_D_jet_mix_fast.exe
    ./MB_D_jet_mix_fast.exe "${WORKPATH}/${DJETFILE}.root" "${MBPATH}/${MBJETFILE}.root" "${WORKPATH}/${MBMIXFILE}.root" $ISMC $ISPP
    rm MB_D_jet_mix_fast.exe
    cd ../djtcorrelation
fi

if [[ $MAKEHISTS -eq 1 ]]
then
    FILES=($DJETFILE $MBMIXFILE "gen_${DJETFILE}")
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
    ./djtana_savetpl_corr.exe "${WORKPATH}/${DJETFILE}.root" "rootfiles/${DJETFILE}_hists" $COLL $ISMC 1 25 0.0 2.0 
    ./djtana_savetpl_corr.exe "${WORKPATH}/${DJETFILE}.root" "rootfiles/gen_${DJETFILE}_hists" $COLL $ISMC 3 25 0.0 2.0 
    ./djtana_savetpl_corr.exe "${WORKPATH}/${MBMIXFILE}.root" "rootfiles/${MBMIXFILE}_hists" $COLL $ISMC 1 25 0.0 2.0
    wait
    ./djtana_plothist.exe "rootfiles/${DJETFILE}_hists" $DJETFILE $COLL $ISMC 25 0.0 2.0 &
    ./djtana_plothist.exe "rootfiles/gen_${DJETFILE}_hists" "gen_${DJETFILE}" $COLL $ISMC 25 0.0 2.0 &
    ./djtana_plothist.exe "rootfiles/${MBMIXFILE}_hists" $MBMIXFILE $COLL $ISMC 25 0.0 2.0
    rm djtana_savetpl_corr.exe
    rm djtana_plothist.exe
fi

if [[ $DOMBSUB -eq 1 ]]
then
    g++ MBsubtract_closure.C $(root-config --cflags --libs) -Werror -Wall -O2 -o MBsubtract_closure.exe
    ./MBsubtract_closure.exe "rootfiles/${DJETFILE}_hists.root" "rootfiles/${MBMIXFILE}_hists.root" "rootfiles/gen_${DJETFILE}_hists.root" "rootfiles/${OUTFILE}.root"
    rm MBsubtract_closure.exe
fi
    
