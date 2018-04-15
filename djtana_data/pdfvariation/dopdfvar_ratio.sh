#!/bin/bash
# dopdfvar_ratio.sh #

source ../includes/utility.shinc

ifScale=1
ifSmearPt=0
ifSmearPhi=0

# Select the systems the macros run on 
kRECOGEN=(0)

##
# scaleNsmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

# nCOL loop
COLSYST=('pp' 'PbPb')
ISMC=(0 0)
HLTOPT=("" "")

MAXEVT=-1

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# Do not touch the macros below if you don't know what they mean #

[[ $DO_PLOTRATIO -eq 0 ]] && echo "./dopdfvariation.sh [DO_PLOTRATIO]"

#
tMC=('data' 'MC')

#
function produce_postfix()
{
    if [[ $# -eq 3 ]]
    then
        echo ${COLSYST[$1]}_${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${HLTOPT[$1]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}
        return 0
    elif [[ $# -eq 4 ]]
    then
        echo ${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${HLTOPT[$1]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}
        return 0
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("rootfiles" "plotpdfvarfit" "plotpdfvar")
mk_dirs ${FOLDERS[@]}

##

# pdfvar_plotratio.C #
g++ pdfvar_plotratio.C $(root-config --cflags --libs) -g -o pdfvar_plotratio.exe || return 1;

if [[ $DO_PLOTRATIO -eq 1 ]]
then
    for j in ${jJET[@]}
    do
        for k in ${kRECOGEN[@]}
        do
            if [[ $k -eq 0 || ${ISMC[i]} -eq 1 ]] # only RecoD_RecoJet will run for data
            then
                tPOSTFIX_PP=Djet_$(produce_postfix 0 $j $k)
                tPOSTFIX_PbPb=Djet_$(produce_postfix 1 $j $k)
                echo -e "-- Processing ${FUNCOLOR}pdfvar_plotratio.C${NC} :: ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                [[ ! -f "rootfiles/pdfvar_${tPOSTFIX_PP}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/pdfvar_${tPOSTFIX_PP}.root doesn't exist. Process pdfvar_usehist.C first."; continue; }
                [[ ! -f "rootfiles/pdfvar_${tPOSTFIX_PbPb}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/pdfvar_${tPOSTFIX_PbPb}.root doesn't exist. Process pdfvar_usehist.C first."; continue; }
                tPOSTFIX=Djet_$(produce_postfix 0 $j $k "ratio")
                ./pdfvar_plotratio.exe "rootfiles/pdfvar_${tPOSTFIX_PP}" "rootfiles/pdfvar_${tPOSTFIX_PbPb}" "$tPOSTFIX" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                echo
            fi
        done
    done
fi

rm pdfvar_plotratio.exe

