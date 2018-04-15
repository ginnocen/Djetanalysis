#!/bin/bash
# dodjtana.sh #

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

source ../includes/utility.shinc

# Select the systems the macros run on 
iCOL=(1 3)
kRECOGEN=(0)

#
CORRFACTOR=1
SIGNALMC=0
ifScale=1
ifSmearPt=0
ifSmearPhi=0

##
# corrFactor
tCORRFACTOR=("_woCorr" "")

# scaleNsmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

# nCOL loop
COLSYST=('pp' 'pp' 'PbPb' 'PbPb')
ISMC=(1 0 1 0)
HLTOPT=("noHLT" "" "noHLT" "")

MAXEVT=-1

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# dataset[nCOL]
INPUTDANAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180214_pp_5TeV_HighPtLowerJetsHighPtJet80_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_HLT406080100.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180411_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLT6080100_jetpt50_mix10_skimbranch.root"
    # "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180411_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLT6080100_jetpt40.root"
    # "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180406_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLT6080100.root"
    # "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080100.root"
)
INPUTMCNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root"
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVETPL -eq 0 ]] && echo "./dodjtana.sh [DO_SAVETPL]"

#
tMC=('data' 'MC')

function produce_postfix()
{
    if [[ $# -ne 3 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[$1]}${tCORRFACTOR[$CORRFACTOR]}_${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${HLTOPT[$1]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}
}

#
FOLDERS=("rootfiles")
mk_dirs ${FOLDERS[@]}

##

# djtana_savetpl.C #
g++ djtana_savetpl.C $(root-config --cflags --libs) -g -o djtana_savetpl.exe || return 1;

if [[ $DO_SAVETPL -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        [[ ${ISMC[i]} -eq 0 && $SIGNALMC -eq 1 ]] && { echo "error: Set SIGNALMC=0 for data"; continue; }
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                [[ $k -ne 0 && ${ISMC[i]} -eq 0 ]] && continue # only RecoD_RecoJet will run for data
                tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                echo -e "-- Processing ${FUNCOLOR}djtana_savetpl.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                ./djtana_savetpl.exe "${INPUTMCNAME[i]}" "rootfiles/masstpl_${tPOSTFIX}" "${COLSYST[i]}" ${ISMC[i]} $k ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $ifScale $ifSmearPt $ifSmearPhi $MAXEVT &
                echo
            done
        done
    done
fi

wait
rm djtana_savetpl.exe
