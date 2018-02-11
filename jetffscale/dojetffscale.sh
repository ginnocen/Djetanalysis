#!/bin/bash
# dojetffscale.sh #

DO_SAVEHIST=${1:-0}
DO_USEHIST=${2:-0}
DO_PLOTHIST=${3:-0}
DO_PLOTPAR=${4:-0}
DO_PLOTHIST_COMB=${5:-0}

ifCorr=1
# Select the systems the macros run on 
iCOL=(0 1)

##

# nCOL loop
COLSYST=('pp' 'PbPb')

# dataset[nCOL]
INPUTDANAME=(
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root'
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root'
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_USEHIST -eq 0 && $DO_PLOTHIST -eq 0 && $DO_PLOTPAR -eq 0 && $DO_PLOTHIST_COMB -eq 0 ]] && echo "./dojetresolution.sh [DO_SAVEHIST] [DO_USEHIST] [DO_PLOTHIST] [DO_PLOTPAR] [DO_PLOTHIST_COMB]"

#
nCOL=${#COLSYST[@]}

#
NC='\033[0m'
FUNCOLOR='\033[1;33m'
ARGCOLOR='\033[1;32m'
ERRCOLOR='\033[1;31m'

#
function float_to_string()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "${ERRCOLOR}error:${NC} invalid argument number - float_to_string()"
        return 1
    fi
    part1=`echo $1 | awk -F "." '{print $1}'`
    part2=`echo $1 | awk -F "." '{print $2}'`
    rt_float_to_string=${part1:-0}p${part2:-0}
    echo $rt_float_to_string
}

function produce_postfix()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[$1]}
}

#
FOLDERS=("rootfiles" "plotresos" "plotfits" "plotresopts")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

##

# jetffscale_savehist.C #

g++ jetffscale_savehist.C $(root-config --cflags --libs) -Werror -Wall -o jetffscale_savehist.exe || return 1;
for i in ${iCOL[@]}
do
    tPOSTFIX=Djet_reso_$(produce_postfix $i)
    if [[ $DO_SAVEHIST -eq 1 ]]
    then
        echo -e "-- Processing ${FUNCOLOR}jetffscale_savehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        ./jetffscale_savehist.exe "${INPUTDANAME[i]}" "rootfiles/hist_${tPOSTFIX}" "${COLSYST[i]}" "$ifCorr" &
        echo
    fi
done
wait
rm jetffscale_savehist.exe


# jetffscale_usehist.C #

g++ jetffscale_usehist.C $(root-config --cflags --libs) -Werror -Wall -o jetffscale_usehist.exe || return 1;
if [[ $DO_USEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        tPOSTFIX=Djet_reso_$(produce_postfix $i)
        echo -e "-- Processing ${FUNCOLOR}jetffscale_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process jetffscale_savehist.C first."; continue; }
        ./jetffscale_usehist.exe "rootfiles/hist_${tPOSTFIX}" "${tPOSTFIX}" "${COLSYST[i]}"
        echo
    done
fi
rm jetffscale_usehist.exe

# jetffscale_plothist.C #

g++ jetffscale_plothist.C $(root-config --cflags --libs) -Werror -Wall -o jetffscale_plothist.exe || return 1;
if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        tPOSTFIX=Djet_reso_$(produce_postfix $i)
        echo -e "-- Processing ${FUNCOLOR}jetffscale_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        [[ ! -f "rootfiles/reso_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/reso_${tPOSTFIX}.root doesn't exist. Process jetffscale_usehist.C first."; continue; }
        [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process jetffscale_savehist.C first."; continue; }
        ./jetffscale_plothist.exe "rootfiles/reso_${tPOSTFIX}" "rootfiles/hist_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" $ifCorr
        [[ $ifCorr -eq 1 ]] && { ./jetffscale_plothist.exe "rootfiles/reso_${tPOSTFIX}" "rootfiles/hist_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" 0; }
        echo
    done
fi
rm jetffscale_plothist.exe

# jetffscale_plothist_comb.C #

g++ jetffscale_plothist_comb.C $(root-config --cflags --libs) -Werror -Wall -o jetffscale_plothist_comb.exe || return 1;
if [[ $DO_PLOTHIST_COMB -eq 1 ]]
then
    tPOSTFIX=Djet_reso
    files[0]="rootfiles/reso_Djet_reso_$(produce_postfix 0)"
    files[1]="rootfiles/reso_Djet_reso_$(produce_postfix 1)"
    files[2]="rootfiles/hist_Djet_reso_$(produce_postfix 0)"
    files[3]="rootfiles/hist_Djet_reso_$(produce_postfix 1)"
    echo -e "-- Processing ${FUNCOLOR}jetffscale_plothist_comb.C${NC}"
    for inf in ${files[@]}
    do
        [[ ! -f "${inf}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${inf}.root doesn't exist."; exit 1; }
    done
    ./jetffscale_plothist_comb.exe "${files[0]}" "${files[1]}" "${files[2]}" "${files[3]}" "$tPOSTFIX" $ifCorr
    echo
fi
rm jetffscale_plothist_comb.exe

# jetffscale_plotpar.C #

g++ jetffscale_plotpar.C $(root-config --cflags --libs) -Werror -Wall -o jetffscale_plotpar.exe || return 1;
if [[ $DO_PLOTPAR -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        tPOSTFIX=Djet_reso_$(produce_postfix $i)
        echo -e "-- Processing ${FUNCOLOR}jetffscale_plotpar.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        [[ ! -f "rootfiles/scalepar_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/scalepar_${tPOSTFIX}.root doesn't exist. Process jetffscale_usehist.C first."; continue; }
        [[ ! -f "rootfiles/reso_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/reso_${tPOSTFIX}.root doesn't exist. Process jetffscale_usehist.C first."; continue; }
        ./jetffscale_plotpar.exe "rootfiles/scalepar_${tPOSTFIX}" "rootfiles/reso_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}"
        echo
    done
fi
rm jetffscale_plotpar.exe
