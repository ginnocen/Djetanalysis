#!/bin/bash
# dostudySigma.sh #

source ../includes/utility.shinc

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

DO_SAVEHIST=${1:-0}
DO_PLOTHIST=${2:-0}

# Select the systems the macros run on 
COLSYST=('pp' 'pp')
DataFlag=('MC' 'Data')
ISMC=(1 0)
iCOL=(0 1)


MAXEVT=-1

# dataset[nCOL]
INPUTNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180214_pp_5TeV_HighPtLowerJetsHighPtJet80_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_HLT406080100.root"
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dostudySigma.sh [DO_SAVEHIST] [DO_PLOTHIST]"

#
FOLDERS=("plotDpt" "rootfiles")
mk_dirs ${FOLDERS[@]}

##

# studySigma_savehist.C #
g++ studySigma_savehist.C $(root-config --cflags --libs) -g -o studySigma_savehist.exe || return 1;

if [[ $DO_SAVEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        echo -e "-- Processing ${FUNCOLOR}studySigma_savehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        set -x
        ./studySigma_savehist.exe "${INPUTNAME[i]}" "rootfiles/hist_${COLSYST[i]}_${DataFlag[i]}" "${COLSYST[i]}" $MAXEVT ${ISMC[i]} &
        set +x
        echo
    done
fi
wait
rm studySigma_savehist.exe


# studySigma_plothist.C #
#g++ studySigma_plothist.C $(root-config --cflags --libs) -g -o studySigma_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        echo -e "-- Processing ${FUNCOLOR}studySigma_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        [[ ! -f "rootfiles/hist_${COLSYST[i]}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${COLSYST[i]}.root doesn't exist. Process studySigma_savehist.C first."; continue; }
        #./studySigma_plothist.exe "rootfiles/hist_${COLSYST[i]}" "${COLSYST[i]}"
        echo
    done
fi

rm studySigma_plothist.exe
