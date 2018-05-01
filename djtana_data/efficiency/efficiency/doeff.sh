#!/bin/bash
# doeff.sh #

source ../includes/utility.shinc

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

ifScale=1
ifSmearPt=1
ifSmearPhi=1

# Select the systems the macros run on 
iCOL=(0 1 2 7 8 9)
kRECOGEN=(0)
iCOLY=(0 1)
lTYPE=(0 1 2)

##
# scaleNsmear
tScale=("woScale" "wScaleRMG" "wScaleFF")
tSmearPt=("woSmearPt" "wSmearPt")
tSmearPhi=("woSmearAng" "wSmearAngJet" "wSmearAngJetD")

MAXEVT=-1

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# dataset[nCOL]
INPUTMCNAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root pp pthatweight"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root pp noweight"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root pp pthatweightDpt"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat30_20171214.root pp pthat30"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat50_20171214.root pp pthat50"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat80_20171214.root pp pthat80"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171215_pp_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat15_20171214.root pp pthat15"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root PbPb pthatweight"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root PbPb noweight"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root PbPb pthatweightDpt"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat30_20180326.root PbPb pthat30"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat50_20180326.root PbPb pthat50"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat80_20180326.root PbPb pthat80" 
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat15_20180326.root PbPb pthat15"
)
COLY=("pp" "PbPb")
TYPE=(pthatweight noweight pthatweightDpt pthat30 pthat50 pthat80 pthat15)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVETPL -eq 0 && $DO_USEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./doeff.sh [DO_SAVETPL] [DO_USEHIST] [DO_PLOTHIST]"

#
function produce_postfix()
{
    if [[ $# -ne 2 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo MC_${RECOGEN[$2]}_jetpt_$(float_to_string ${JETPTMIN[$1]})_$(float_to_string ${JETPTMAX[$1]})_jeteta_$(float_to_string ${JETETAMIN[$1]})_$(float_to_string ${JETETAMAX[$1]})_${tScale[$ifScale]}_${tSmearPt[$ifSmearPt]}_${tSmearPhi[$ifSmearPhi]}
}

#
FOLDERS=("ploteff" "ploteffall" "rootfiles")
mk_dirs ${FOLDERS[@]}

##

# eff_savetpl.C #
g++ eff_savetpl.C $(root-config --cflags --libs) -g -o eff_savetpl.exe || return 1;

for i in ${iCOL[@]}
do
    arrayINPUT=(${INPUTMCNAME[i]})
    COLSYST=${arrayINPUT[1]}
    NAME=${arrayINPUT[2]}
    for j in ${jJET[@]}
    do
        for k in ${kRECOGEN[@]}
        do
            tPOSTFIX=Djet_${COLSYST}_$(produce_postfix $j $k)_${NAME}
            if [[ $DO_SAVETPL -eq 1 ]]
            then
                echo -e "-- Processing ${FUNCOLOR}eff_savetpl.C${NC} :: ${ARGCOLOR}${COLSYST}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                ./eff_savetpl.exe ${INPUTMCNAME[i]} "rootfiles/masstpl_${tPOSTFIX}" $k ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} $ifScale $ifSmearPt $ifSmearPhi $MAXEVT &
                echo
            fi
        done
    done
done

wait
rm eff_savetpl.exe


# eff_usehist.C #
g++ eff_usehist.C $(root-config --cflags --libs) -g -o eff_usehist.exe || return 1;

if [[ $DO_USEHIST -eq 1 ]]
then
    for i in ${iCOL[@]}
    do
        arrayINPUT=(${INPUTMCNAME[i]})
        COLSYST=${arrayINPUT[1]}
        NAME=${arrayINPUT[2]}
        for j in ${jJET[@]}
        do
            for k in ${kRECOGEN[@]}
            do
                tPOSTFIX=Djet_${COLSYST}_$(produce_postfix $j $k)_${NAME}
                echo -e "-- Processing ${FUNCOLOR}eff_usehist.C${NC} :: ${ARGCOLOR}${COLSYST}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                [[ ! -f "rootfiles/masstpl_${tPOSTFIX}.root"  && ( $k -eq 0  ||  $k -eq 2 ) ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/masstpl_${tPOSTFIX}.root doesn't exist. Process eff_savetpl.C first."; continue; }
                set -x
                ./eff_usehist.exe "rootfiles/masstpl_${tPOSTFIX}" "$tPOSTFIX" "${COLSYST}" $k ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                set +x 
                echo
            done
        done
    done
fi

rm eff_usehist.exe

# eff_plothist.C #
g++ eff_plothist.C $(root-config --cflags --libs) -g -o eff_plothist.exe || return 1;

if [[ $DO_PLOTHIST -eq 1 ]]
then
    for j in ${jJET[@]}
    do
        for k in ${kRECOGEN[@]}
        do
            for i in ${iCOLY[@]}
            do
                INPUT=""
                for l in ${lTYPE[@]}
                do
                    tPOSTFIX=Djet_${COLY[i]}_$(produce_postfix $j $k)_${TYPE[l]}
                    [[ ! -f "rootfiles/masstpl_${tPOSTFIX}.root" ]] && { echo -e "${ERRCOLOR}error:${NC} rootfiles/masstpl_${tPOSTFIX}.root doesn't exist. Process eff_usehist.C first."; exit; }
                    INPUT=${INPUT}rootfiles/masstpl_${tPOSTFIX}" "${TYPE[l]}" "
                done
                echo -e "-- Processing ${FUNCOLOR}eff_plothist.C${NC} :: ${ARGCOLOR}${COLY[i]}${NC}"
                tPOSTFIX=Djet_${COLY[i]}_$(produce_postfix $j $k)
                set -x
                ./eff_plothist.exe $INPUT "$tPOSTFIX" "${COLY[i]}" ${JETPTMIN[j]} ${JETPTMAX[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
                set +x
            done
        done
    done
fi

rm eff_plothist.exe