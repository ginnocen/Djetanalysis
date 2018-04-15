#!/bin/bash
# dodjtana.sh #

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

source ../includes/utility.shinc

# Select the systems the macros run on 
iCOL=(0 1)
##

# nCOL loop
COLSYST=('pp' 'PbPb')
ISMC=(1 1)
HLTOPT=("noHLT" "noHLT")

# dataset[nCOL]
INPUTNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root"
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dodjtana.sh [DO_SAVEHIST] [DO_PLOTHIST]"

function produce_postfix()
{
    if [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}_MC_GenD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("rootfiles" "plotbkgsub")
mk_dirs ${FOLDERS[@]}

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
            ./djtana_savehist.exe "${INPUTNAME[i]}" "rootfiles/hist_${tPOSTFIX}" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} -1 &
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
            ./djtana_plothist.exe "rootfiles/hist_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            echo
        done
    done
fi

rm djtana_plothist.exe
