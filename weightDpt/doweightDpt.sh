#!/bin/bash
# doweightDpt.sh #

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
iCOL=(0 1)

##
# nCOL loop
COLSYST=('pp' 'PbPb')

MAXEVT=-1

# dataset[nCOL]
INPUTMCNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180328_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root"
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./doweightDpt.sh [DO_SAVEHIST] [DO_PLOTHIST]"

#
FOLDERS=("plotDpt" "rootfiles")
mk_dirs ${FOLDERS[@]}

##

# weightDpt_savehist.C #
g++ weightDpt_savehist.C $(root-config --cflags --libs) -g -o weightDpt_savehist.exe || return 1;

if [[ $DO_SAVEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        echo -e "-- Processing ${FUNCOLOR}weightDpt_savehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        set -x
        ./weightDpt_savehist.exe "${INPUTMCNAME[i]}" "rootfiles/hist_${COLSYST[i]}" "${COLSYST[i]}" $MAXEVT &
        set +x
        echo
    done
fi
wait
rm weightDpt_savehist.exe


# weightDpt_plothist.C #
g++ weightDpt_plothist.C $(root-config --cflags --libs) -g -o weightDpt_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        echo -e "-- Processing ${FUNCOLOR}weightDpt_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        [[ ! -f "rootfiles/hist_${COLSYST[i]}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${COLSYST[i]}.root doesn't exist. Process weightDpt_savehist.C first."; continue; }
        ./weightDpt_plothist.exe "rootfiles/hist_${COLSYST[i]}" "${COLSYST[i]}"
        echo
    done
fi

rm weightDpt_plothist.exe
