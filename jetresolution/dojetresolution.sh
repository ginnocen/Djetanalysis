#!/bin/bash
# dojetresolution.sh #

DO_SAVEHIST=${1:-0}
DO_USEHIST=${2:-0}
DO_PLOTHIST=${3:-0}

# Select the systems the macros run on 
iCOL=(0)

##

# nCOL loop
COLSYST=('pp' 'PbPb')
# ISMC=(1 0 1 0)

# dataset[nCOL]
INPUTDANAME=(
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20171127_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root'
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root'
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_USEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dojetresolution.sh [DO_SAVEHIST] [DO_USEHIST] [DO_PLOTHIST]"

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
FOLDERS=("rootfiles" "plotpulls")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

##

# jetreso_savehist.C #

g++ jetreso_savehist.C $(root-config --cflags --libs) -g -o jetreso_savehist.exe || return 1;
for i in ${iCOL[@]}
do
    tPOSTFIX=Djet_reso_$(produce_postfix $i)
    if [[ $DO_SAVEHIST -eq 1 ]]
    then
        echo -e "-- Processing ${FUNCOLOR}jetreso_savehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        ./jetreso_savehist.exe "${INPUTDANAME[i]}" "rootfiles/hist_${tPOSTFIX}" "${COLSYST[i]}" 
        echo
    fi
done
rm jetreso_savehist.exe


# jetreso_usehist.C #

g++ jetreso_usehist.C $(root-config --cflags --libs) -g -o jetreso_usehist.exe || return 1;
if [[ $DO_USEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        tPOSTFIX=Djet_reso_$(produce_postfix $i)
        echo -e "-- Processing ${FUNCOLOR}jetreso_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process jetreso_savehist.C first."; continue; }
        ./jetreso_usehist.exe "rootfiles/hist_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}"
        echo
    done
fi
rm jetreso_usehist.exe

# jetreso_plothist.C #
# g++ jetreso_plothist.C $(root-config --cflags --libs) -g -o jetreso_plothist.exe || return 1;

# if [[ $DO_PLOTHIST -eq 1 ]]
# then
#     for i in ${iCOL[@]}
#     do
#         tPOSTFIX=Djet_reso_$(produce_postfix $i)
#         echo -e "-- Processing ${FUNCOLOR}jetreso_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
#         [[ ! -f "rootfiles/xsec_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/xsec_${tPOSTFIX}.root doesn't exist. Process jetreso_usehist.C first."; continue; }
#         ./jetreso_plothist.exe "rootfiles/xsec_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" ${ISMC[i]} ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
#         echo
#     done
# fi

# rm jetreso_plothist.exe
