#!/bin/bash
# dodjtana.sh #

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
jJET=(0)

##

# nJET loop
JETPTMIN=(40)
JETETAMIN=(0.3)
JETETAMAX=(1.6)

# dataset[nCOL]
INPUTNAME="$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dodjtana.sh [DO_SAVEHIST] [DO_PLOTHIST]"

#
nJET=${#JETPTMIN[@]}

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
    echo jetpt_$(float_to_string ${JETPTMIN[$1]})_jeteta_$(float_to_string ${JETETAMIN[$1]})_$(float_to_string ${JETETAMAX[$1]})
}

#
FOLDERS=("rootfiles" "plotclosure")
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

for j in ${jJET[@]}
do
    tPOSTFIX=Djet_$(produce_postfix $j)
    if [[ $DO_SAVEHIST -eq 1 ]]
    then
        echo -e "-- Processing ${FUNCOLOR}djtana_savehist.C${NC}"
        set -x
        ./djtana_savehist.exe "${INPUTNAME}" "rootfiles/hist_${tPOSTFIX}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} 
        set +x
        echo
    fi
done

rm djtana_savehist.exe


# djtana_plothist.C #
g++ djtana_plothist.C $(root-config --cflags --libs) -g -o djtana_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for j in ${jJET[@]}
    do
        tPOSTFIX=Djet_$(produce_postfix $j)
        echo -e "-- Processing ${FUNCOLOR}djtana_plothist.C${NC}"
        [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process djtana_savehist.C first."; continue; }
        ./djtana_plothist.exe "rootfiles/hist_${tPOSTFIX}" "$tPOSTFIX" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
        echo
    done
fi

rm djtana_plothist.exe
