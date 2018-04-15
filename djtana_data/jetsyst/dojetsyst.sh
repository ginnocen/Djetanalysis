#!/bin/bash
# dojetsyst.sh #

source ../includes/utility.shinc

# Select the systems the macros run on 
iCOL=(0 1)

##
# nCOL loop
COLSYST=('pp' 'PbPb')
tHLT=('' '')

# nScaleSmear
tScale=("woScale" "wScaleP" "wScaleM" "wScaleQ" "wScaleG")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng")


# Do not touch the macros below if you don't know what they mean #
#
lSmearPhi=0
lSmearPt=0

#
function produce_postfix()
{
    if [[ $# -eq 3 ]]
    then
        echo ${COLSYST[$1]}_data_RecoD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${tHLT[$1]}_${tScale[$3]}_${tSmearPt[$lSmearPt]}_${tSmearPhi[$lSmearPhi]}
    elif [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}_data_RecoD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${tHLT[$1]}
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("plotjetsyst")
mk_dirs ${FOLDERS[@]}

##
[[ $DO_PLOTHIST -eq 0 ]] && echo "./dodjetsyst.sh [DO_PLOTHIST]"

##

# jetsyst_plothist.C #
g++ jetsyst_plothist.C $(root-config --cflags --libs) -g -o jetsyst_plothist.exe || return 1;
if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            echo -e "-- Processing ${FUNCOLOR}jetsyst_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
            tPOSTFIX=Djet_$(produce_postfix $i $j)

            file[0]="../djtanajetsyst/rootfiles/xsec_Djet_$(produce_postfix $i $j 0)"
            file[1]="../djtanajetsyst/rootfiles/xsec_Djet_$(produce_postfix $i $j 1)"
            file[2]="../djtanajetsyst/rootfiles/xsec_Djet_$(produce_postfix $i $j 2)"
            file[3]="../djtanajetsyst/rootfiles/xsec_Djet_$(produce_postfix $i $j 3)"
            file[4]="../djtanajetsyst/rootfiles/xsec_Djet_$(produce_postfix $i $j 4)"
            # file[5]="../djtanajetsyst/rootfiles/xsec_Djet_$(produce_postfix $i $j 0 1)"

            for inf in ${file[@]}
            do
                [[ ! -f "${inf}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${inf}.root doesn't exist."; exit 1;}                
            done
            ./jetsyst_plothist.exe "${file[0]}" "${file[1]}" "${file[2]}" "${file[3]}" "${file[4]}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            echo
        done
    done
fi
rm jetsyst_plothist.exe


