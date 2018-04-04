#!/bin/bash
# dojetresolution.sh #

DO_SAVEHIST=${1:-0}
DO_USEHIST=${2:-0}
DO_PLOTHIST=${3:-0}
DO_PLOTHISTQG=${4:-0}

source ../includes/utility.shinc
cp ../includes/prefilters_data.h prefilters.h

# Select the systems the macros run on 
iCOL=(0 1)
iFLAVOR=(0 1 2)
##

# nFLAVOR
FLAVOR=('incl' 'quark' 'gluon')

# nCOL loop
COLSYST=('pp' 'PbPb')

# dataset[nCOL]
INPUTDANAME=(
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root'
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20180328_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root'
)

MAXEVT=-1

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_USEHIST -eq 0 && $DO_PLOTHIST -eq 0 && $DO_PLOTHISTQG -eq 0 ]] && echo "./dojetresolution.sh [DO_SAVEHIST] [DO_USEHIST] [DO_PLOTHIST] [DO_PLOTHISTQG]"

function produce_postfix()
{
    if [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}_${FLAVOR[$2]}
    elif [[ $# -eq 1 ]]
    then
        echo ${COLSYST[$1]}
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("rootfiles" "plotresos" "plotfits" "plotfitsall" "plotqg" "plotfitspull" "plotmatrix" "plotpar")
mk_dirs ${FOLDERS[@]}

##

# jetreso_savehist.C #

g++ jetreso_savehist.C $(root-config --cflags --libs) -g -o jetreso_savehist.exe || return 1;
for i in ${iCOL[@]}
do
    for j in ${iFLAVOR[@]}
    do
        tPOSTFIX=Djet_reso_$(produce_postfix $i $j)
        if [[ $DO_SAVEHIST -eq 1 ]]
        then
            echo -e "-- Processing ${FUNCOLOR}jetreso_savehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
            ./jetreso_savehist.exe "${INPUTDANAME[i]}" "rootfiles/hist_${tPOSTFIX}" "${COLSYST[i]}" $j $MAXEVT &
            echo
        fi
    done
done
wait
rm jetreso_savehist.exe


# jetreso_usehist.C #

g++ jetreso_usehist.C $(root-config --cflags --libs) -g -o jetreso_usehist.exe || return 1;
if [[ $DO_USEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${iFLAVOR[@]}
        do
            tPOSTFIX=Djet_reso_$(produce_postfix $i $j)
            echo -e "-- Processing ${FUNCOLOR}jetreso_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
            [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process jetreso_savehist.C first."; continue; }
            ./jetreso_usehist.exe "rootfiles/hist_${tPOSTFIX}" "${tPOSTFIX}" "${COLSYST[i]}"
            echo
        done
    done
fi
rm jetreso_usehist.exe

# jetreso_plothist.C #

g++ jetreso_plothist.C $(root-config --cflags --libs) -g -o jetreso_plothist.exe || return 1;
g++ jetreso_plotpar.C $(root-config --cflags --libs) -g -o jetreso_plotpar.exe || return 1;
if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${iFLAVOR[@]}
        do

            tPOSTFIX=Djet_reso_$(produce_postfix $i $j)
            echo -e "-- Processing ${FUNCOLOR}jetreso_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
            [[ ! -f "rootfiles/reso_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/reso_${tPOSTFIX}.root doesn't exist. Process jetreso_usehist.C first."; continue; }
            ./jetreso_plothist.exe "rootfiles/reso_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}"
            echo
        done
    done
    ./jetreso_plotpar.exe
fi
rm jetreso_plotpar.exe
rm jetreso_plothist.exe

# jetreso_plothistqg.C #

g++ jetreso_plothistqg.C $(root-config --cflags --libs) -g -o jetreso_plothistqg.exe || return 1;
if [[ $DO_PLOTHISTQG -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        outPOSTFIX=Djet_reso_$(produce_postfix $i)
        tPOSTFIX[0]=Djet_reso_$(produce_postfix $i 0)
        tPOSTFIX[1]=Djet_reso_$(produce_postfix $i 1)
        tPOSTFIX[2]=Djet_reso_$(produce_postfix $i 2)
        echo -e "-- Processing ${FUNCOLOR}jetreso_plothistqg.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        for postfix in ${tPOSTFIX[@]}
        do
            [[ ! -f "rootfiles/reso_${postfix}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/reso_${postfix}.root doesn't exist. Process jetreso_usehist.C first."; exit 1; }
        done
        ./jetreso_plothistqg.exe "rootfiles/reso_${tPOSTFIX[0]}" "rootfiles/reso_${tPOSTFIX[1]}" "rootfiles/reso_${tPOSTFIX[2]}" "$outPOSTFIX" "${COLSYST[i]}"
        echo
    done
fi
rm jetreso_plothistqg.exe

rm prefilters.h