#!/bin/bash
# dodjtana.sh #

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

mv ../includes/prefilters.h ../includes/prefilters_temp.h
cp ../includes/prefilters_finefinebin.h ../includes/prefilters.h

DO_SAVEHIST=${1:-0}
DO_PLOTHIST=${2:-0}
DO_CORRHIST=${3:-0}

USESIGNALMC=${4:-0}

# Select the systems the macros run on 
iCOL=(0 1)
jJET=(0 1)
##

# nCOL loop
COLSYST=('pp' 'PbPb')
ISMC=(1 1)
HLTOPT=("noHLT" "noHLT")

# nJET loop
JETPTMIN=(40 40)
JETETAMIN=(0.3 0.5)
JETETAMAX=(1.6 1.6)

# USESIGNALMC
tSIGNALMC=("" "_Signal")

# dataset[nCOL]
INPUTNAME=("$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root")
# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_PLOTHIST -eq 0 && $DO_CORRHIST -eq 0 ]] && echo "./dodjtana.sh [DO_SAVEHIST] [DO_PLOTHIST] [DO_CORRHIST]"

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
    if [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}_MC_GenD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})${tSIGNALMC[$USESIGNALMC]}
    elif [[ $# -eq 3 ]]
    then
        echo ${COLSYST[$1]}_MC_GenD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})${tSIGNALMC[$3]}
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("rootfiles" "plotbkgsub")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

##

# djtana_savehist.C #
g++ djtana_savehist.C $(root-config --cflags --libs) -g -o djtana_savehist.exe || return 1;

for i in ${iCOL[@]}
do
    for j in ${jJET[@]}
    do
        tPOSTFIX=Djet_$(produce_postfix $i $j)
        if [[ $DO_SAVEHIST -eq 1 ]]
        then
            echo -e "-- Processing ${FUNCOLOR}djtana_savehist.C${NC}"
            set -x
            ./djtana_savehist.exe "${INPUTNAME[i]}" "rootfiles/hist_${tPOSTFIX}" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $USESIGNALMC &
            set +x
            echo
        fi
    done
done
wait
rm djtana_savehist.exe


# djtana_plothist.C #
g++ djtana_plothist.C $(root-config --cflags --libs) -g -o djtana_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            tPOSTFIX=Djet_$(produce_postfix $i $j)
            echo -e "-- Processing ${FUNCOLOR}djtana_plothist.C${NC}"
            [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process djtana_savehist.C first."; continue; }
            ./djtana_plothist.exe "rootfiles/hist_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            echo
        done
    done
fi

rm djtana_plothist.exe

# djtana_corrhist.C #
g++ djtana_corrhist.C $(root-config --cflags --libs) -g -o djtana_corrhist.exe || return 1;

if [[ $DO_CORRHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            tPOSTFIX=Djet_$(produce_postfix $i $j 0)
            tPOSTFIX_SIGNAL=Djet_$(produce_postfix $i $j 1)
            echo -e "-- Processing ${FUNCOLOR}djtana_corrhist.C${NC}"
            [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process djtana_savehist.C first."; continue; }
            [[ ! -f "rootfiles/hist_${tPOSTFIX_SIGNAL}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX_SIGNAL}.root doesn't exist. Process djtana_savehist.C first."; continue; }
            ./djtana_corrhist.exe "rootfiles/hist_${tPOSTFIX}" "rootfiles/hist_${tPOSTFIX_SIGNAL}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            echo
        done
    done
fi

rm djtana_corrhist.exe

mv ../includes/prefilters_temp.h ../includes/prefilters.h