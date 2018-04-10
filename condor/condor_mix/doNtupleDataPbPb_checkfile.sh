#!/bin/bash

if [[ $0 != *.sh ]]
then
    echo -e "\e[31;1merror:\e[0m use \e[32;1m./script.sh\e[0m instead of \e[32;1msource script.sh\e[0m"
    return 1
fi

#
isMC=0
isPP=0
MAXFILENO=100000
ifCHECKEMPTY=0
MIX_FILELIST="list_data_MB.txt"
JETPTMIN=0

#
movetosubmit=${1:-0}
runjobs=${2:-0}

# INPUTDIR="/mnt/hadoop/cms/store/user/ginnocen/HIHardProbes/crab_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_26March/170327_025517/0004/" # 0004
# INPUTDIR="/mnt/hadoop/cms/store/user/ginnocen/HIHardProbes/crab_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part2_26March/170327_025543/0009/" # 0009
# INPUTDIR="/mnt/hadoop/cms/store/user/ginnocen/HIHardProbes/crab_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part3_26March/170327_025650/0005/" # 0005
INPUTDIR="/mnt/hadoop/cms/store/user/ginnocen/HIHardProbes/crab_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part4_26March/170327_025720/0002/" # 0002
OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djetsgfal/"
OUTPUTSUBDIR="DjetFiles_20180406_PbPb_5TeV_HIHardProbes_skimmed_1unit_part4_26March_20170326_HLT6080100" ###########!!!!!

# MERGEOUTPUTDIR="/export/d00/scratch/jwang/Djets/data/"
WORKDIR="/work/$USER/DjetMix/"

#
OUTPUTDIR="${OUTPUTPRIDIR}/${OUTPUTSUBDIR}"
LOGDIR="logs/log_${OUTPUTSUBDIR}"

##

if [[ ! -d "$WORKDIR" ]]
then
    mkdir -p $WORKDIR
fi

if [ "$movetosubmit" -eq 1 ]
then
    if [[ $(hostname) == "submit-hi2.mit.edu" || $(hostname) == "submit.mit.edu" ]]
    then
        cd ../skim
        g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
        cd ../condor

        mv ../skim/D_jet_skim.exe $WORKDIR/
        # cp residuals.tgz $WORKDIR/
        cp $0 $WORKDIR/
        cp skim_djet_checkfile.sh $WORKDIR/
        cp skim_condor_checkfile.sh $WORKDIR/
        cp $MIX_FILELIST $WORKDIR/
    else
        echo -e "\e[31;1merror:\e[0m compile macros on \e[32;1msubmit-hiX.mit.edu\e[0m or \e[32;1msubmit.mit.edu\e[0m."
    fi
fi

if [ "$runjobs" -eq 1 ]
then 
    if [[ $(hostname) == "submit.mit.edu" ]]
    then
        ./skim_condor_checkfile.sh $INPUTDIR $OUTPUTDIR $MAXFILENO $LOGDIR $MIX_FILELIST $isPP $isMC $JETPTMIN $ifCHECKEMPTY
    else
        echo -e "\e[31;1merror:\e[0m submit jobs on \e[32;1msubmit.mit.edu\e[0m."
    fi
fi

# INPUTDIR="/mnt/hadoop/cms/store/user/wangj/HighPtLowerJets/crab_HiForestAOD_DfinderData_pp_20170614_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/170615_172204/0000/"
# OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djets/"
# OUTPUTSUBDIR="DjetFiles_20170616_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614"

# INPUTDIR="/mnt/hadoop/cms/store/user/ginnocen/HighPtJet80/crab_pp_5TeV_HighPtJet80_Dfinder_2april/170402_230535/0000/"
# OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djets/"
# OUTPUTSUBDIR="DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1"

# MERGEOUTPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
