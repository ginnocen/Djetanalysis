#!/bin/bash
# dodjtana.sh #

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

cp ../includes/prefilters_data_2Dbins.h ../includes/prefilters.h
# cp ../includes/prefilters_finecorr.h ../includes/prefilters.h

if [ ! -f ../includes/prefilters.h ]
then
    exit 1
fi

DO_SAVETPL=${1:-0}
DO_SAVEHIST=${2:-0}
DO_USEHIST=${3:-0}
DO_PLOTHIST=${4:-0}

ifScale=0
ifSmearPt=0
ifSmearPhi=0

CORRSMEAR=0
CORRFACTOR=0
SIGNALMC=1

# Select the systems the macros run on 
iCOL=(0 2)
jJET=(0)
kRECOGEN=(3)

##
# corrSmear
tCORRSMEAR=("Raw" "" "Smear")
# corrFactor
tCORRFACTOR=("_woCorr" "")
# signalMC
tSIGNALMC=("" "Signal_")
# scaleNsmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

# nCOL loop
COLSYST=('pp' 'pp' 'PbPb' 'PbPb')
ISMC=(1 0 1 0)
HLTOPT=("HLT60test" "" "HLT60test" "")

# nJET loop
JETPTMIN=(60)
JETPTMAX=(999)
JETETAMIN=(0.3)
JETETAMAX=(1.6)

MAXEVT=-1

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# dataset[nCOL]
INPUTDANAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    # "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"
    # "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20171120_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180214_pp_5TeV_HighPtLowerJetsHighPtJet80_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    # "$PREFIX/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1/merged_total.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080.root"
)
INPUTMCNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVETPL -eq 0 && $DO_SAVEHIST -eq 0 && $DO_USEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dodjtana.sh [DO_SAVETPL] [DO_SAVEHIST] [DO_USEHIST] [DO_PLOTHIST]"

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
    echo ${COLSYST[$1]}${tCORRSMEAR[$CORRSMEAR]}${tCORRFACTOR[$CORRFACTOR]}_${tSIGNALMC[$SIGNALMC]}${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_$(float_to_string ${JETPTMAX[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${HLTOPT[$1]}_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}
}

#
FOLDERS=("plotfits" "plotxsecs" "ploteff" "rootfiles")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

##

# djtana_savetpl.C + djtana_savehist.C #
g++ djtana_savetpl.C $(root-config --cflags --libs) -g -o djtana_savetpl.exe || return 1;
g++ djtana_savehist.C $(root-config --cflags --libs) -g -o djtana_savehist.exe || return 1;

for i in ${iCOL[@]}
do
    [[ ${ISMC[i]} -eq 0 && $SIGNALMC -eq 1 ]] && { echo "error: Set SIGNALMC=0 for data"; continue; }
    [[ ${COLSYST[i]} != "pp" && $CORRSMEAR -eq 2 ]] && { echo "ignore PbPb for smearPP"; continue; }
    for j in ${jJET[@]}
    do
        for k in ${kRECOGEN[@]}
        do
            [[ $k -ne 0 && ${ISMC[i]} -eq 0 ]] && continue # only RecoD_RecoJet will run for data
            tPOSTFIX=Djet_$(produce_postfix $i $j $k)
            if [[ $DO_SAVETPL -eq 1 ]]
            then
                echo -e "-- Processing ${FUNCOLOR}djtana_savetpl.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                ./djtana_savetpl.exe "${INPUTMCNAME[i]}" "rootfiles/masstpl_${tPOSTFIX}" "${COLSYST[i]}" ${ISMC[i]} $k ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $ifScale $ifSmearPt $ifSmearPhi $CORRSMEAR $MAXEVT &
                echo
            fi
            if [[ $DO_SAVEHIST -eq 1 ]]
            then
                echo -e "-- Processing ${FUNCOLOR}djtana_savehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                ./djtana_savehist.exe "${INPUTDANAME[i]}" "rootfiles/hist_${tPOSTFIX}" "${COLSYST[i]}" ${ISMC[i]} $k ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $ifScale $ifSmearPt $ifSmearPhi $SIGNALMC $CORRSMEAR $CORRFACTOR $MAXEVT &
                echo
            fi
        done
    done
done

wait
rm djtana_savehist.exe
rm djtana_savetpl.exe


# djtana_usehist.C #
g++ djtana_usehist.C $(root-config --cflags --libs) -g -o djtana_usehist.exe || return 1;

if [[ $DO_USEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        [[ ${ISMC[i]} -eq 0 && $SIGNALMC -eq 1 ]] && { echo "error: Set SIGNALMC=0 for data"; continue; }
        [[ ${COLSYST[i]} != "pp" && $CORRSMEAR -eq 2 ]] && { echo "ignore PbPb for smearPP"; continue; }
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                [[ $k -ne 0 && ${ISMC[i]} -eq 0 ]] && continue # only RecoD_RecoJet will run for data
                tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                echo -e "-- Processing ${FUNCOLOR}djtana_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                [[ ! -f "rootfiles/hist_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/hist_${tPOSTFIX}.root doesn't exist. Process djtana_savehist.C first."; continue; }
                [[ ! -f "rootfiles/masstpl_${tPOSTFIX}.root"  && ( $k -eq 0  ||  $k -eq 2 ) ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/masstpl_${tPOSTFIX}.root doesn't exist. Process djtana_savetpl.C first."; continue; }
                ./djtana_usehist.exe "rootfiles/hist_${tPOSTFIX}" "rootfiles/masstpl_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" $k ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $SIGNALMC
                echo
            done
        done
    done
fi

rm djtana_usehist.exe

# djtana_plothist.C #
g++ djtana_plothist.C $(root-config --cflags --libs) -g -o djtana_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        [[ ${ISMC[i]} -eq 0 && $SIGNALMC -eq 1 ]] && { echo "error: Set SIGNALMC=0 for data"; continue; }
        [[ ${COLSYST[i]} != "pp" && $CORRSMEAR -eq 2 ]] && { echo "ignore PbPb for smearPP"; continue; }
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                [[ $k -ne 0 && ${ISMC[i]} -eq 0 ]] && continue # only RecoD_RecoJet will run for data
                tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                echo -e "-- Processing ${FUNCOLOR}djtana_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                [[ ! -f "rootfiles/xsec_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/xsec_${tPOSTFIX}.root doesn't exist. Process djtana_usehist.C first."; continue; }
                ./djtana_plothist.exe "rootfiles/xsec_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST[i]}" ${ISMC[i]} ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $SIGNALMC
                echo
            done
        done
    done
fi

rm djtana_plothist.exe

rm ../includes/prefilters.h
