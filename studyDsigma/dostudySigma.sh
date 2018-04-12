#!/bin/bash
# dostudySigma.sh #

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
    echo ${COLSYST[i]}_${DataFlag[i]}_pthat${isPtHat}_ptcutforYstudy$(float_to_string ${ptcutforYstudy})_ycutforPtstudy$(float_to_string ${ycutforPtstudy})
}

function produce_postfixNosample()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[i]}_pthat${isPtHat}_ptcutforYstudy$(float_to_string ${ptcutforYstudy})_ycutforPtstudy$(float_to_string ${ycutforPtstudy})
}


function produce_postfixMC()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[i]}_MC_pthat${isPtHat}_ptcutforYstudy$(float_to_string ${ptcutforYstudy})_ycutforPtstudy$(float_to_string ${ycutforPtstudy})
}

function produce_postfixData()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[i]}_Data_pthat${isPtHat}_ptcutforYstudy$(float_to_string ${ptcutforYstudy})_ycutforPtstudy$(float_to_string ${ycutforPtstudy})
}





DO_SAVEHIST=${1:-0}
DO_PLOTHIST=${2:-0}
DO_COMPARE=${3:-0}
ptcutforYstudy=${4:-0}
ycutforPtstudy=${5:-0}
isPtHat=${6:-0}

# Select the systems the macros run on 
ISMC=(1 0)
iCOL=(0 1)

COLSYST=('pp' 'pp')
DataFlag=('MC' 'Data')

MAXEVT=-1

# dataset[nCOL]
INPUTNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20180214_pp_5TeV_HighPtLowerJetsHighPtJet80_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_HLT406080100.root"
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
        ./studySigma_savehist.exe "${INPUTNAME[i]}" "rootfiles/hist_$tPOSTFIX" "${COLSYST[i]}" $MAXEVT ${ISMC[i]} $isPtHat ${ptcutforYstudy} ${ycutforPtstudy} &
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
        tPOSTFIXMC=Djet_$(produce_postfixMC $i)
        echo -e "-- Processing ${FUNCOLOR}studySigma_usehist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        ./studySigma_usehist.exe "rootfiles/hist_$tPOSTFIX" "rootfiles/hist_$tPOSTFIXMC" "$tPOSTFIX" "${COLSYST[i]}"
        echo
    done

fi

rm studySigma_usehist.exe
g++ studySigma_plothist.C $(root-config --cflags --libs) -g -o studySigma_plothist.exe || return 1;

if [[ $DO_COMPARE -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
         tPOSTFIX=Djet_$(produce_postfixNosample $i)
         tPOSTFIXData=Djet_$(produce_postfixData $i)
         tPOSTFIXMC=Djet_$(produce_postfixMC $i)
        echo -e "-- Processing ${FUNCOLOR}studySigma_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC}"
        ./studySigma_plothist.exe "rootfiles/xsec_$tPOSTFIXData" "rootfiles/xsec_$tPOSTFIXMC" "${COLSYST[i]}" "$tPOSTFIX" 
        echo
    done
fi


rm studySigma_plothist.C.exe
