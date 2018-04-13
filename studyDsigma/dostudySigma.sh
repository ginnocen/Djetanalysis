#!/bin/bash
# dostudySigma.sh #

#source dostudySigma.sh 1 1 1 4.0 2.0 0 0.15 4.5 0.12
#DO_SAVEHIST DO_PLOTHIST DO_COMPARE ptcutforYstudy ycutforPtstudy isPtHat cutval_Dchi2cl cutval_Dsvpv cutval_Dalpha


source ../includes/utility.shinc

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi


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
    if [[ $# -ne 1 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[i]}_pthat${isPtHat}_ptcutforYstudy$(float_to_string ${ptcutforYstudy})_ycutforPtstudy$(float_to_string ${ycutforPtstudy})_cutval_Dchi2cl$(float_to_string ${cutval_Dchi2cl})_cutval_Dsvpv$(float_to_string ${cutval_Dsvpv})_cutval_Dalpha$(float_to_string ${cutval_Dalpha})
}


DO_SAVEHIST=${1:-0}
DO_PLOTHIST=${2:-0}
DO_COMPARE=${3:-0}
ptcutforYstudy=${4:-0}
ycutforPtstudy=${5:-0}
isPtHat=${6:-0}
cutval_Dchi2cl=${7:-0}
cutval_Dsvpv=${8:-0}
cutval_Dalpha=${9:-0}

iCOL=(2 3)

# Select the systems the macros run on 
ISMC=(1 0 1 0)
COLSYST=('pp' 'pp' 'PbPb' 'PbPb')
DataFlag=('MC' 'Data' 'MC' 'Data')

MAXEVT=10000

# dataset[nCOL]
INPUTNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180214_pp_5TeV_HighPtLowerJetsHighPtJet80_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_HLT406080100.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180406_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLT6080100.root"
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dostudySigma.sh [DO_SAVEHIST] [DO_PLOTHIST]"

#
FOLDERS=("plotDpt" "rootfiles")
mk_dirs ${FOLDERS[@]}

##

# studySigma_savehist.C #
g++ studySigma_savehist.C $(root-config --cflags --libs) -g -o studySigma_savehist.exe || return 1;

if [[ $DO_SAVEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}     
    do
        tPOSTFIX=Djet_$(produce_postfix $i)
        echo -e "-- Processing ${FUNCOLOR}studySigma_savehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        set -x
        ./studySigma_savehist.exe "${INPUTNAME[i]}" "rootfiles/hist_${DataFlag[i]}_$tPOSTFIX" "${COLSYST[i]}" $MAXEVT ${ISMC[i]} $isPtHat ${ptcutforYstudy} ${ycutforPtstudy}  ${cutval_Dchi2cl} ${cutval_Dsvpv} ${cutval_Dalpha}&
        set +x
        echo
    done
fi
wait
rm studySigma_savehist.exe


g++ studySigma_usehist.C $(root-config --cflags --libs) -g -o studySigma_usehist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        tPOSTFIX=Djet_$(produce_postfix $i)
        echo -e "-- Processing ${FUNCOLOR}studySigma_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        ./studySigma_usehist.exe "rootfiles/hist_${DataFlag[i]}_$tPOSTFIX" "rootfiles/hist_MC_$tPOSTFIX" "${DataFlag[i]}_${tPOSTFIX}_gaussianindex2" "${COLSYST[i]}" 2
        ./studySigma_usehist.exe "rootfiles/hist_${DataFlag[i]}_$tPOSTFIX" "rootfiles/hist_MC_$tPOSTFIX" "${DataFlag[i]}_${tPOSTFIX}_gaussianindex5" "${COLSYST[i]}" 5
        echo
    done

fi

rm studySigma_usehist.exe
g++ studySigma_plothist.C $(root-config --cflags --libs) -g -o studySigma_plothist.exe || return 1;

if [[ $DO_COMPARE -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
         tPOSTFIX=Djet_$(produce_postfix $i)
        echo -e "-- Processing ${FUNCOLOR}studySigma_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        ./studySigma_plothist.exe "rootfiles/xsec_Data_${tPOSTFIX}_gaussianindex2" "rootfiles/xsec_MC_${tPOSTFIX}_gaussianindex2" "${COLSYST[i]}" "${tPOSTFIX}_gaussianindex2" 
        ./studySigma_plothist.exe "rootfiles/xsec_Data_${tPOSTFIX}_gaussianindex5" "rootfiles/xsec_MC_${tPOSTFIX}_gaussianindex5" "${COLSYST[i]}" "${tPOSTFIX}_gaussianindex5" 
        echo
    done
fi


rm studySigma_plothist.exe
