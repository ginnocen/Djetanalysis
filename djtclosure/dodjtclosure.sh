#!/bin/bash
# dodjtclosure.sh #

DIRPREFIX="../djtana/"

# Select the systems the macros run on 
iCOL=(0 1)
jJET=(1)

##

# nCOL loop
COLSYST=('pp' 'PbPb')

# nJET loop
JETPTMIN=(40 40)
JETETAMIN=(0 0.3)
JETETAMAX=(2.0 1.6)

# Do not touch the macros below if you don't know what they mean #
#
nCOL=${#COLSYST[@]}
nJET=${#JETPTMIN[@]}

RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

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
        echo ${COLSYST[$1]}_MC_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})
    elif [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("plotxsecs")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
	mkdir -p $i
    fi
done

##

# djtclosure_plothist.C #
g++ djtclosure_plothist.C $(root-config --cflags --libs) -g -o djtclosure_plothist.exe || return 1;

for i in ${iCOL[@]}
do
    for j in ${jJET[@]}
    do
        tPOSTFIX=Djet_$(produce_postfix $i $j)
        tPOSTFIX_rDrJ=Djet_$(produce_postfix $i $j 0)
        tPOSTFIX_gDrJ=Djet_$(produce_postfix $i $j 1)
        tPOSTFIX_rDgJ=Djet_$(produce_postfix $i $j 2)
        tPOSTFIX_gDgJ=Djet_$(produce_postfix $i $j 3)
        echo -e "-- Processing ${FUNCOLOR}djtclosure_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        ./djtclosure_plothist.exe "${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_rDrJ}" "${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_gDrJ}" "${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_rDgJ}" "${DIRPREFIX}/rootfiles/xsec_${tPOSTFIX_gDgJ}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
        echo
    done
done

rm djtclosure_plothist.exe

