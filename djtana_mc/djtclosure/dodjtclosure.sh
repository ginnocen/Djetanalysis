#!/bin/bash
# dodjtclosure.sh #

DIRPREFIX="../djtana/"

source ../includes/utility.shinc

# Select the systems the macros run on 
iCOL=(0 1)

#
CORRFACTOR=0
CORRRESO=0
SIGNALMC=1
lScale=1
lSmearPt=1
lSmearPhi=1

##
# corrFactor
tCORRFACTOR=("_woCorr" "")
# corrReso
tCORRRESO=("Raw" "")
# signalMC
tSIGNALMC=("" "Signal_")
# nScaleSmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

##
# nCOL loop
COLSYST=('pp' 'PbPb')

# Do not touch the macros below if you don't know what they mean #
#
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

#
function produce_postfix()
{
    if [[ $# -eq 3 ]]
    then
        echo ${COLSYST[$1]}${tCORRRESO[$CORRRESO]}${tCORRFACTOR[$CORRFACTOR]}_${tSIGNALMC[$SIGNALMC]}MC_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_noHLT_${tScale[$lScale]}_${tSmearPt[$lSmearPt]}_${tSmearPhi[$lSmearPhi]}
    elif [[ $# -eq 2 ]]
    then
        echo ${COLSYST[$1]}${tCORRRESO[$CORRRESO]}${tCORRFACTOR[$CORRFACTOR]}_${tSIGNALMC[$SIGNALMC]}MC_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_noHLT_${tScale[$lScale]}_${tSmearPt[$lSmearPt]}_${tSmearPhi[$lSmearPhi]}
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}


FOLDERS=("plotclosure" "plotclosureAN")
mk_dirs ${FOLDERS[@]}

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
            echo -e "-- Processing ${FUNCOLOR}djtclosure_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tScale[lScale]}${NC}, ${ARGCOLOR}${tSmearPt[lSmearPt]}${NC}, ${ARGCOLOR}${tSmearPhi[lSmearPhi]}${NC}"
            tPOSTFIX=Djet_$(produce_postfix $i $j)
            file[0]="../djtana/rootfiles/xsec_Djet_$(produce_postfix $i $j 0)"
            file[1]="../djtana/rootfiles/xsec_Djet_$(produce_postfix $i $j 1)"
            file[2]="../djtana/rootfiles/xsec_Djet_$(produce_postfix $i $j 2)"
            file[3]="../djtana/rootfiles/xsec_Djet_$(produce_postfix $i $j 3)"
            for inf in ${file[@]}
            do
                [[ ! -f "${inf}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${inf}.root doesn't exist."; exit 1;}
            done
            set -x
            ./djtclosure_plothist.exe "${file[0]}" "${file[1]}" "${file[2]}" "${file[3]}" "$tPOSTFIX" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
            set +x
        done
    done
fi
rm djtclosure_plothist.exe

