#!/bin/bash
# dodjtclosure.sh #

DIRPREFIX="../djtana/"

DO_PLOTHIST=${1:-0}

# Select the systems the macros run on 
iCOL=(0 1)
jJET=(0)

##
# nCOL loop
COLSYST=('pp' 'PbPb')

# nJET loop
JETPTMIN=(40)
JETETAMIN=(0.3)
JETETAMAX=(1.6)

# nScaleSmear
tScale=("wScaleFF" "wScaleRMG")

# Do not touch the macros below if you don't know what they mean #
#

lSmearPt=1
lSmearPhi=1
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

nCOL=${#COLSYST[@]}
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
    if [[ $# -eq 3 ]]
    then
        echo ${COLSYST[$1]}_MC_GenD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_noHLT_${tScale[$3]}_${tSmearPt[$lSmearPt]}_${tSmearPhi[$lSmearPhi]}
    elif [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}_GenD_RecoJet_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_noHLT
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("plotclosure")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

##
[[ $DO_PLOTHIST -eq 0 ]] && echo "./dodjtana.sh [DO_PLOTHIST]"

##

# djtclosure_plothist.C #
g++ djtclosure_plothist.C $(root-config --cflags --libs) -g -o djtclosure_plothist.exe || return 1;
if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            echo -e "-- Processing ${FUNCOLOR}djtclosure_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
            tPOSTFIX=Djet_$(produce_postfix $i $j)
            k=0
            filenexist=0
            for rg in ${tScale[@]}
            do
                tPOSTFIX_RG[k]=Djet_$(produce_postfix $i $j $k)
                [[ ! -f "${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_RG[k]}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_RG[k]}.root doesn't exist. Process ../djtana/djtana_usehist.C first."; filenexist=$(($filenexist+1)); }
                k=$(($k+1))
            done
            [[ $filenexist -ne 0 ]] && continue
            ./djtclosure_plothist.exe "${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_RG[0]}" "${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_RG[1]}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            echo
        done
    done
fi
rm djtclosure_plothist.exe