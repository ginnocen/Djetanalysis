#!/bin/bash
# dodjtana_ratio.sh #

# Select the systems the macros run on 
iCOL=(0 1)
jJET=(1)
kRECOGEN=(0 1 2 3)

##

# nCOL loop
ISMC=(0 1)

# nJET loop
JETPTMIN=(40 40)
JETETAMIN=(0 0.3)
JETETAMAX=(2.0 1.6)

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

#
DO_SAVERATIO=${1:-0}
DO_PLOTRATIO=${2:-0}

# Do not touch the macros below if you don't know what they mean #
#
nCOL=${#COLSYST[@]}
nRECOGEN=${#RECOGEN[@]}
nJET=${#JETPTMIN[@]}

#
NC='\033[0m'
FUNCOLOR='\033[1;33m'
ARGCOLOR='\033[1;32m'
ERRCOLOR='\033[1;31m'
tMC=('data' 'MC')

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
    if [[ $# -ne 3 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})
}

#
FOLDERS=("plotratios" "rootfiles")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
	mkdir -p $i
    fi
done

##

# djtana_saveratio.C #
g++ djtana_saveratio.C $(root-config --cflags --libs) -g -o djtana_saveratio.exe || return 1;

if [ $DO_SAVERATIO -eq 1 ]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                if [ $k -eq 0 ] || [ ${ISMC[i]} -eq 1 ] # only RecoD_RecoJet will run for data
                then
                    tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                    tPOSTFIXPP=Djet_pp_$(produce_postfix $i $j $k)
                    tPOSTFIXPbPb=Djet_PbPb_$(produce_postfix $i $j $k)
                    echo -e "-- Processing ${FUNCOLOR}djtana_saveratio.C${NC} :: ${ARGCOLOR}PbPb/pp${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                    ./djtana_saveratio.exe "rootfiles/xsec_${tPOSTFIXPP}" "rootfiles/xsec_${tPOSTFIXPbPb}" "rootfiles/ratio_$tPOSTFIX" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                    echo
                fi
            done
        done
    done
fi

rm djtana_saveratio.exe

# djtana_plotratio.C #
g++ djtana_plotratio.C $(root-config --cflags --libs) -g -o djtana_plotratio.exe || return 1;

if [ $DO_PLOTRATIO -eq 1 ]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                if [ $k -eq 0 ] || [ ${ISMC[i]} -eq 1 ] # only RecoD_RecoJet will run for data
                then
                    tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                    echo -e "-- Processing ${FUNCOLOR}djtana_plotratio.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                    # set -x
                    ./djtana_plotratio.exe "rootfiles/ratio_${tPOSTFIX}" "$tPOSTFIX" ${ISMC[i]} ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                    # set +x
                    echo
                fi
            done
        done
    done
fi

rm djtana_plotratio.exe


