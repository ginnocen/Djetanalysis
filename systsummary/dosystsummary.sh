#!/bin/bash
# dosystsummary.sh #

source ../includes/utility.shinc

# Select the systems the macros run on
iCOL=(0 1)

# nCOL loop
COLSYST=('pp' 'PbPb')

# Do not touch the macros below if you don't know what they mean #

[[ $DO_PLOTHIST -eq 0 ]] && echo "./dosystsummary.sh [DO_PLOTHIST]"

#
function produce_postfix()
{
    if [[ $# -ne 2 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[$1]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})
}

#
FOLDERS=("plotsyst");
mk_dirs ${FOLDERS[@]}

g++ syst_plothist.C $(root-config --cflags --libs) -g -o syst_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            tPOSTFIX=Djet_$(produce_postfix $i $j)
            echo -e "-- Processing ${FUNCOLOR}syst_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
            ./syst_plothist.exe "${tPOSTFIX}" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            echo
        done
    done
fi

rm syst_plothist.exe