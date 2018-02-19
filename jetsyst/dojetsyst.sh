#!/bin/bash
# dojetsyst.sh #

DO_PLOTHIST=${1:-0}

# Select the systems the macros run on 
iCOL=(0 1)
jJET=(0)

##
# nCOL loop
COLSYST=('pp' 'PbPb')
tHLT=('HLTJet40Jet60' 'HLTJet40Jet60Jet80')

# nJET loop
JETPTMIN=(40)
JETETAMIN=(0.3)
JETETAMAX=(1.6)

# nScaleSmear
tScale=("woScale" "wScaleP" "wScaleM")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng")


# Do not touch the macros below if you don't know what they mean #
#
lSmearPhi=0

nCOL=${#COLSYST[@]}
nJET=${#JETPTMIN[@]}

RECOGEN=('RecoD_RecoJet')

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
    if [[ $# -eq 4 ]]
    then
        echo ${COLSYST[$1]}_data_RecoD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${tHLT[$1]}_${tScale[$3]}_${tSmearPt[$4]}_${tSmearPhi[$lSmearPhi]}
    elif [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}_data_RecoD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${tHLT[$1]}
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("plotjetsyst")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

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

            file[0]="rootfiles/xsec_Djet_$(produce_postfix $i $j 0 0)"
            file[1]="rootfiles/xsec_Djet_$(produce_postfix $i $j 1 0)"
            file[2]="rootfiles/xsec_Djet_$(produce_postfix $i $j 2 0)"
            file[3]="rootfiles/xsec_Djet_$(produce_postfix $i $j 0 1)"

            for inf in ${file[@]}
            do
                [[ ! -f "${inf}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${inf}.root doesn't exist."; exit 1;}                
            done
            ./jetsyst_plothist.exe "${file[0]}" "${file[1]}" "${file[2]}" "${file[3]}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            echo
        done
    done
fi
rm jetsyst_plothist.exe