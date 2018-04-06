#!/bin/bash
# docompxsec.sh #

DO_USEHIST=${1:-0}

source ../includes/utility.shinc
cp ../includes/prefilters_data.h prefilters.h

# Select the systems the macros run on 
iCOL=(0 1)
jJET=(0 1 2)
kPAR=(0 2)

##
# nCOL loop
COLSYST=('pp' 'PbPb')

# nJET loop
JETPTMIN=(60 80 100)
JETPTMAX=(80 100 999)
JETETAMIN=(0.3 0.3 0.3)
JETETAMAX=(1.6 1.6 1.6)

# Do not touch the macros below if you don't know what they mean #
#
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

#
function produce_postfix()
{
    if [[ $# -eq 3 ]]
    then
        echo MC_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_noHLT
    elif [[ $# -eq 2 ]]
    then
        echo MC_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_noHLT
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
            file_0[0]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            file_1[0]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 3)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            leg_0[0]="Reco Jet, Gen D"
            leg_1[0]="sGen Jet, Gen D"
            texname[0]="corrFactor"

            tPOSTFIX[1]=corrNonclosureCorr_Djet_${COLSYST[i]}_$(produce_postfix $i $j)
            file_0[1]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_Signal_$(produce_postfix $i $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            file_1[1]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_Signal_$(produce_postfix $i $j 3)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            leg_0[1]="corr Reco Jet, Gen D"
            leg_1[1]="sGen Jet, Gen D"
            texname[1]=""

            tPOSTFIX[2]=corrReso_Djet_${COLSYST[i]}_$(produce_postfix $i $j)
            file_0[2]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 3)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            file_1[2]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 3)_${tScale[0]}_${tSmearPt[0]}_${tSmearPhi[0]}"
            leg_0[2]="sGen Jet, Gen D"
            leg_1[2]="Gen Jet, Gen D"
            texname[2]="corrFactorSg"

            tPOSTFIX[3]=xScale_Djet_${COLSYST[i]}_$(produce_postfix $i $j)
            file_0[3]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 1)_${tScale[2]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            file_1[3]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            leg_0[3]="Frag-dep JES"
            leg_1[3]="Frag-indep JES"
            texname[3]=""

            tPOSTFIX[4]=corrFinal_Djet_${COLSYST[i]}_$(produce_postfix $i $j)
            file_0[4]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            file_1[4]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 3)_${tScale[0]}_${tSmearPt[0]}_${tSmearPhi[0]}"
            leg_0[4]="corr Reco Jet, Reco D"
            leg_1[4]="Gen Jet, Gen D"
            texname[4]=""

            tPOSTFIX[5]=corrFinalCorr_Djet_${COLSYST[i]}_$(produce_postfix $i $j)
            file_0[5]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}_Signal_$(produce_postfix $i $j 0)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
            file_1[5]="../djtana/rootfiles/xsec_Djet_${COLSYST[i]}Raw_woCorr_Signal_$(produce_postfix $i $j 3)_${tScale[0]}_${tSmearPt[0]}_${tSmearPhi[0]}"
            leg_0[5]="corr Reco Jet, Reco D"
            leg_1[5]="Gen Jet, Gen D"
            texname[5]=""

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

rm prefilters.h