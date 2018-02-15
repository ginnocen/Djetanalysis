#!/bin/bash
# dopdfvariation.sh #

mv ../includes/prefilters.h ../includes/prefilters_temp.h
cp ../includes/prefilters_data.h ../includes/prefilters.h

if [ ! -f ../includes/prefilters.h ]
then
    exit 1
fi

DO_USEHIST=${1:-0}
DO_PLOTHIST=${2:-0}

ifScale=1
ifSmearPt=0
ifSmearPhi=0

# Select the systems the macros run on 
iCOL=(1 3)
jJET=(0 1)
kRECOGEN=(0)

##
# scaleNsmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

# nCOL loop
COLSYST=('pp' 'pp' 'PbPb' 'PbPb')
ISMC=(1 0 1 0)

# nJET loop
JETPTMIN=(40 40)
JETETAMIN=(0.3 0.3)
JETETAMAX=(1.6 1.6)
HLTOPT=("HLTJet40Jet60" "HLTJet40Jet60Jet80")

MAXEVT=-1

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# Do not touch the macros below if you don't know what they mean #

[[ $DO_USEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dopdfvariation.sh [DO_USEHIST] [DO_PLOTHIST]"

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
    echo ${COLSYST[$1]}_${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${HLTOPT[$2]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}
}

#
FOLDERS=("rootfiles" "plotpdfvarfit" "plotpdfvar")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

##

# pdfvar_usehist.C #
g++ pdfvar_usehist.C $(root-config --cflags --libs) -g -o pdfvar_usehist.exe || return 1;

if [[ $DO_USEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                if [[ $k -eq 0 || ${ISMC[i]} -eq 1 ]] # only RecoD_RecoJet will run for data
                then
                    tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                    echo -e "-- Processing ${FUNCOLOR}pdfvar_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                    [[ ! -f "../djtana/rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ../djtana/rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process djtana_savehist.C first."; continue; }
                    [[ ! -f "../djtana/rootfiles/masstpl_${tPOSTFIX}.root"  && ( $k -eq 0  ||  $k -eq 2 ) ]] && { echo -e "${ERRCOLOR}error:${NC} ../djtana/rootfiles/masstpl_${tPOSTFIX}.root doesn't exist. Process djtana_savetpl.C first."; continue; }
                    ./pdfvar_usehist.exe "../djtana/rootfiles/hist_${tPOSTFIX}" "../djtana/rootfiles/masstpl_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                    echo
                fi
            done
        done
    done
fi

rm pdfvar_usehist.exe

# pdfvar_plothist.C #
g++ pdfvar_plothist.C $(root-config --cflags --libs) -g -o pdfvar_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                if [[ $k -eq 0 || ${ISMC[i]} -eq 1 ]] # only RecoD_RecoJet will run for data
                then
                    tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                    echo -e "-- Processing ${FUNCOLOR}pdfvar_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                    [[ ! -f "rootfiles/pdfvar_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/pdfvar_${tPOSTFIX}.root doesn't exist. Process pdfvar_usehist.C first."; continue; }
                    ./pdfvar_plothist.exe "rootfiles/pdfvar_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                    echo
                fi
            done
        done
    done
fi

rm pdfvar_plothist.exe

mv ../includes/prefilters_temp.h ../includes/prefilters.h
