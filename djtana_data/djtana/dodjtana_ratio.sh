#!/bin/bash
# dodjtana_ratio.sh #

PLOTPYTHIA=1

source ../includes/utility.shinc

# Select the systems the macros run on 
iCOL=(0)
kRECOGEN=(0)

##

# nCOL loop
ISMC=(0 1)
HLTOPTPP=("" "noHLT")
HLTOPTPbPb=("" "noHLT")

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVERATIO -eq 0 && $DO_PLOTRATIO -eq 0 && $DO_FINALPLOT -eq 0 ]] && echo "./dodjtana_ratio.sh [DO_SAVERATIO] [DO_PLOTRATIO] [DO_FINALPLOT]"

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
FOLDERS=("plotratios" "plotfinal" "rootfiles")
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
                tPOSTFIXPP=Djet_pp_$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_wScaleRMG_woSmearPt_woSmearAng
                tPOSTFIXPbPb=Djet_PbPb_$(produce_postfix $i $j $k)_${HLTOPTPbPb[i]}_wScaleRMG_woSmearPt_woSmearAng
                tPOSTFIX=Djet_$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_${HLTOPTPbPb[i]}_wScaleRMG_woSmearPt_woSmearAng
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
                    tPOSTFIX=Djet_$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_${HLTOPTPbPb[i]}_wScaleRMG_woSmearPt_woSmearAng
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

# djtana_finalplot.C #
g++ djtana_finalplot.C $(root-config --cflags --libs) -g -o djtana_finalplot.exe || return 1;

if [[ $DO_FINALPLOT -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                if [[ $k -eq 0 || ${ISMC[i]} -eq 1 ]] # only RecoD_RecoJet will run for data
                then
                    tPOSTFIXPP=Djet_pp_$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_wScaleRMG_woSmearPt_woSmearAng
                    tPOSTFIXPbPb=Djet_PbPb_$(produce_postfix $i $j $k)_${HLTOPTPbPb[i]}_wScaleRMG_woSmearPt_woSmearAng
                    tPOSTFIXPYTHIA=Djet_ppRaw_woCorr_Signal_$(produce_postfix 1 $j 3)_noHLT_woScale_woSmearPt_woSmearAng_noDweight
                    tPOSTFIX=Djet_$(produce_postfix $i $j $k)_${HLTOPTPP[i]}_${HLTOPTPbPb[i]}_wScaleRMG_woSmearPt_woSmearAng
                    echo -e "-- Processing ${FUNCOLOR}djtana_finalplot.C${NC} :: ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                    [[ ! -f "rootfiles/xsec_${tPOSTFIXPP}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/xsec_${tPOSTFIXPP}.root doesn't exist. Process djtana_usehist.C first."; continue; }
                    [[ ! -f "rootfiles/xsec_${tPOSTFIXPbPb}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/xsec_${tPOSTFIXPbPb}.root doesn't exist. Process djtana_usehist.C first."; continue; }
                    [[ ! -f "rootfiles/ratio_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/ratio_${tPOSTFIX}.root doesn't exist. Process djtana_saveratio.C first."; continue; }
                    [[ ! -f "../../djtana_mc/djtana/rootfiles/xsec_${tPOSTFIXPYTHIA}.root" && $PLOTPYTHIA -eq 1 ]] && { echo -e "${ERRCOLOR}error:${NC} ../../djtana_mc/djtana/rootfiles/xsec_${tPOSTFIXPYTHIA}.root  doesn't exist. Process Monte-Carlo first."; continue; }
                    ./djtana_finalplot.exe "rootfiles/xsec_${tPOSTFIXPP}" "rootfiles/xsec_${tPOSTFIXPbPb}" "rootfiles/ratio_${tPOSTFIX}" "$tPOSTFIX" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $PLOTPYTHIA "../../djtana_mc/djtana/rootfiles/xsec_${tPOSTFIXPYTHIA}"
                    echo
                fi
            done
        done
    done
fi

rm djtana_finalplot.exe