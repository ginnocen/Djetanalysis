#!/bin/bash
# docompxsec.sh #

source ../includes/utility.shinc

# Select the systems the macros run on 
iCOL=(0 1)
kPAR=(0)

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
        echo data_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_
    elif [[ $# -eq 2 ]]
    then
        echo data_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_
    else
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
}

#
FOLDERS=("plotcomp")
mk_dirs ${FOLDERS[@]}

##
[[ $DO_USEHIST -eq 0 ]] && echo "./dodjtana.sh [DO_USEHIST]"

##

# nScaleSmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

# compxsec_usehist.C #
g++ compxsec_usehist.C $(root-config --cflags --libs) -g -o compxsec_usehist.exe || return 1;
if [[ $DO_USEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            tPOSTFIX[0]=corrNonclosure_Djet_${COLSYST[i]}_woCorr_$(produce_postfix $i $j)
            file_0[0]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}_$(produce_postfix $i $j 0)_${tScale[1]}_${tSmearPt[0]}_${tSmearPhi[0]}"
            file_1[0]="../djtana_trigeff/rootfiles/xsec_Djet_${COLSYST[i]}_$(produce_postfix $i $j 0)_${tScale[1]}_${tSmearPt[0]}_${tSmearPhi[0]}"
            leg_0[0]="w/o trig eff corr"
            leg_1[0]="w/ trig eff corr"
            texname[0]="trigeff"

            nPAR=${#tPOSTFIX[@]}
            echo $nPAR
            #
            for k in ${kPAR[@]}
            do
                echo -e "-- Processing ${FUNCOLOR}compxsec_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tPOSTFIX[k]}${NC}"
                echo "${file_0[k]}.root"
                echo "${file_1[k]}.root"
                [[ ! -f "${file_0[k]}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${file_0[k]}.root doesn't exist."; continue;}                
                [[ ! -f "${file_1[k]}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${file_1[k]}.root doesn't exist."; continue;}                
                ./compxsec_usehist.exe "${file_0[k]}" "${file_1[k]}" "${leg_0[k]}" "${leg_1[k]}" "${tPOSTFIX[k]}" "${COLSYST[i]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} "${texname[k]}"
                echo
            done
        done
    done
fi
rm compxsec_usehist.exe
