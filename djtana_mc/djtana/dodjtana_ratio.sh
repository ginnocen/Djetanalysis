#!/bin/bash
# dodjtana_ratio.sh #

source ../includes/utility.shinc

# Select the systems the macros run on 
iCOL=(1)
kRECOGEN=(0 1 2 3)

##
# corrFactor
tCORRFACTOR=("_woCorr" "")
# corrReso
tCORRRESO=("Raw" "")
# signalMC
tSIGNALMC=("" "Signal_")

# scaleNsmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt" "wSmearPtSyst")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

# Dgenweight
tDgenweight=("_noDweight" "")

# nCOL loop
ISMC=(0 1)
HLTOPTPP=("" "noHLT")
HLTOPTPbPb=("" "noHLT")

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVERATIO -eq 0 && $DO_PLOTRATIO -eq 0 ]] && echo "./dodjtana_ratio.sh [DO_SAVERATIO] [DO_PLOTRATIO]"

#
tMC=('data' 'MC')

#
function produce_postfix()
{
    if [[ $# -ne 3 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})
}

#
FOLDERS=("plotratios" "rootfiles")
mk_dirs ${FOLDERS[@]}
##

# djtana_saveratio.C #
g++ djtana_saveratio.C $(root-config --cflags --libs) -g -o djtana_saveratio.exe || return 1;

if [[ $DO_SAVERATIO -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                [[ $k -ne 0 && ${ISMC[i]} -eq 0 ]] && continue # only RecoD_RecoJet will run for data
                tPOSTFIXPP=Djet_pp${tCORRRESO[$CORRRESO]}${tCORRFACTOR[$CORRFACTOR]}_${tSIGNALMC[$SIGNALMC]}$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}${tDgenweight[$doDgenweight]}
                tPOSTFIXPbPb=Djet_PbPb${tCORRRESO[$CORRRESO]}${tCORRFACTOR[$CORRFACTOR]}_${tSIGNALMC[$SIGNALMC]}$(produce_postfix $i $j $k)_${HLTOPTPbPb[i]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}${tDgenweight[$doDgenweight]}
                tPOSTFIX=Djet_${tCORRRESO[$CORRRESO]}${tCORRFACTOR[$CORRFACTOR]}_${tSIGNALMC[$SIGNALMC]}$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_${HLTOPTPbPb[i]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}${tDgenweight[$doDgenweight]}
                echo -e "-- Processing ${FUNCOLOR}djtana_saveratio.C${NC} :: ${ARGCOLOR}PbPb/pp${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                [[ ! -f "rootfiles/xsec_${tPOSTFIXPP}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/xsec_${tPOSTFIXPP}.root doesn't exist. Process djtana_usehist.C first."; continue; }
                [[ ! -f "rootfiles/xsec_${tPOSTFIXPbPb}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/xsec_${tPOSTFIXPbPb}.root doesn't exist. Process djtana_usehist.C first."; continue; }
                ./djtana_saveratio.exe "rootfiles/xsec_${tPOSTFIXPP}" "rootfiles/xsec_${tPOSTFIXPbPb}" "rootfiles/ratio_$tPOSTFIX"
                echo
            done
        done
    done
fi

rm djtana_saveratio.exe

# djtana_plotratio.C #
g++ djtana_plotratio.C $(root-config --cflags --libs) -g -o djtana_plotratio.exe || return 1;

if [[ $DO_PLOTRATIO -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                if [[ $k -eq 0 || ${ISMC[i]} -eq 1 ]] # only RecoD_RecoJet will run for data
                then
                    tPOSTFIX=Djet_${tCORRRESO[$CORRRESO]}${tCORRFACTOR[$CORRFACTOR]}_${tSIGNALMC[$SIGNALMC]}$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_${HLTOPTPbPb[i]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}${tDgenweight[$doDgenweight]}
                    echo -e "-- Processing ${FUNCOLOR}djtana_plotratio.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                    [[ ! -f "rootfiles/ratio_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/ratio_${tPOSTFIX}.root doesn't exist. Process djtana_saveratio.C first."; continue; }
                    ./djtana_plotratio.exe "rootfiles/ratio_${tPOSTFIX}" "$tPOSTFIX" ${ISMC[i]} ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                    echo
                fi
            done
        done
    done
fi

rm djtana_plotratio.exe
