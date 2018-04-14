#!/bin/bash
# docompxsec.sh #

source ../includes/utility.shinc

# Select the systems the macros run on 
kPAR=(0)

##
# Do not touch the macros below if you don't know what they mean #
#
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

#
function produce_postfix()
{
    if [[ $# -eq 2 ]]
    then
        echo MC_${RECOGEN[$2]}_jetpt_$(float_to_string ${JETPTMIN[$1]})_$(float_to_string ${JETPTMAX[$1]})_jeteta_$(float_to_string ${JETETAMIN[$1]})_$(float_to_string ${JETETAMAX[$1]})_noHLT_noHLT
    elif [[ $# -eq 1 ]]
    then
        echo MC_jetpt_$(float_to_string ${JETPTMIN[$1]})_$(float_to_string ${JETPTMAX[$1]})_jeteta_$(float_to_string ${JETETAMIN[$1]})_$(float_to_string ${JETETAMAX[$1]})_noHLT_noHLT
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

# compxsec_usehist_ratio.C #
g++ compxsec_usehist_ratio.C $(root-config --cflags --libs) -g -o compxsec_usehist_ratio.exe || return 1;
if [[ $DO_USEHIST -eq 1 ]]
then
    for j in ${jJET[@]}
    do
        tPOSTFIX[0]=corrNonclosure_Djet_woCorr_$(produce_postfix $j)
        file_0[0]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        file_1[0]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 3)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        leg_0[0]="Reco Jet, Gen D"
        leg_1[0]="sGen Jet, Gen D"
        texname[0]="corrFactor"

        tPOSTFIX[1]=corrNonclosureCorr_Djet_$(produce_postfix $j)
        file_0[1]="../djtana/rootfiles/ratio_Djet_Raw_Signal_$(produce_postfix $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        file_1[1]="../djtana/rootfiles/ratio_Djet_Raw_Signal_$(produce_postfix $j 3)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        leg_0[1]="corr Reco Jet, Gen D"
        leg_1[1]="sGen Jet, Gen D"
        texname[1]=""

        tPOSTFIX[2]=corrReso_Djet_$(produce_postfix $j)
        file_0[2]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 3)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        file_1[2]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 3)_${tScale[0]}_${tSmearPt[0]}_${tSmearPhi[0]}"
        leg_0[2]="sGen Jet, Gen D"
        leg_1[2]="Gen Jet, Gen D"
        texname[2]="corrFactorSg"

        tPOSTFIX[3]=xScale_Djet_$(produce_postfix $j)
        file_0[3]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 1)_${tScale[2]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        file_1[3]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        leg_0[3]="Frag-dep JES"
        leg_1[3]="Frag-indep JES"
        texname[3]=""

        tPOSTFIX[4]=corrFinal_Djet_$(produce_postfix $j)
        file_0[4]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 1)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        file_1[4]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 3)_${tScale[0]}_${tSmearPt[0]}_${tSmearPhi[0]}"
        leg_0[4]="corr Reco Jet, Reco D"
        leg_1[4]="Gen Jet, Gen D"
        texname[4]=""

        tPOSTFIX[5]=corrFinalCorr_Djet_$(produce_postfix $j)
        file_0[5]="../djtana/rootfiles/ratio_Djet_Signal_$(produce_postfix $j 0)_${tScale[1]}_${tSmearPt[1]}_${tSmearPhi[1]}"
        file_1[5]="../djtana/rootfiles/ratio_Djet_Raw_woCorr_Signal_$(produce_postfix $j 3)_${tScale[0]}_${tSmearPt[0]}_${tSmearPhi[0]}"
        leg_0[5]="corr Reco Jet, Reco D"
        leg_1[5]="Gen Jet, Gen D"
        texname[5]=""

        nPAR=${#tPOSTFIX[@]}
        echo $nPAR
            #
        for k in ${kPAR[@]}
        do
            echo -e "-- Processing ${FUNCOLOR}compratio_usehist.C${NC} :: ${ARGCOLOR}${NC} - ${ARGCOLOR}${tPOSTFIX[k]}${NC}"
            echo "${file_0[k]}.root"
            echo "${file_1[k]}.root"
            [[ ! -f "${file_0[k]}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${file_0[k]}.root doesn't exist."; continue;}                
            [[ ! -f "${file_1[k]}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} ${file_1[k]}.root doesn't exist."; continue;}                
            ./compxsec_usehist_ratio.exe "${file_0[k]}" "${file_1[k]}" "${leg_0[k]}" "${leg_1[k]}" "${tPOSTFIX[k]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} "${texname[k]}"
            echo
        done
    done
fi
rm compxsec_usehist_ratio.exe
