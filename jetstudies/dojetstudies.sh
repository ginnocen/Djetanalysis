#!/bin/bash
# dodjtclosure.sh #

DIRPREFIX="../djtana/"

# Select the systems the macros run on 
iCOL=(0)
jJET=(0)
kRECOGEN=(0 1 2 3)
HLTOPT="noHLT"
##

# nCOL loop
COLSYST=('pp' 'pp' 'PbPb' 'PbPb')
ISMC=(1 0 1 0)
tMC=('data' 'MC')

# nJET loop
JETPTMIN=(4)
JETETAMIN=(0)
JETETAMAX=(2.0)

# Do not touch the macros below if you don't know what they mean #
#
nCOL=${#COLSYST[@]}
nJET=${#JETPTMIN[@]}

RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# dataset[nCOL]
INPUTDANAME=(
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root'
    '/export/d00/scratch/jwang/Djets/data/DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root'
    '/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root'
    '/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1/merged_total.root'
)

# Do not touch the macros below if you don't know what they mean #

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
    if [[ $# -ne 3 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[$1]}_${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})
}

#
FOLDERS=("jetstudies_results")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

##
# jetstudies_plothist.C #
g++ jetstudies_savehisto.C $(root-config --cflags --libs) -g -o jetstudies_savehisto.exe || return 1;

for i in ${iCOL[@]}
do
    for j in ${jJET[@]}
    do
        for k in ${kRECOGEN[@]}
        do
            if [[ $k -eq 0 || ${ISMC[i]} -eq 1 ]] # only RecoD_RecoJet will run for data
            then
                tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                echo -e "-- Processing ${FUNCOLOR}jetstudies_savehisto.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                echo -e "-- Jet Parameters ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}"
                ./jetstudies_savehisto.exe "${INPUTDANAME[i]}" "jetstudies_results/hist_${tPOSTFIX}" "${COLSYST[i]}" ${ISMC[i]} $k ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} "${HLTOPT}" &
                echo
            fi
        done
    done
done

wait

#rm jetstudies_plothist.exe
