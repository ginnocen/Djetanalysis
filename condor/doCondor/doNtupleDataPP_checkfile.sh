#!/bin/sh

#
isMC=0
isPP=1
MAXFILENO=1000000
ifCHECKEMPTY=1

#
runjobs=${1:-0}
merger=${2:-0}

INPUTDIR="/mnt/hadoop/cms/store/user/wangj/HighPtLowerJets/crab_HiForestAOD_DfinderData_pp_20170614_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/170615_172204/0000/"
OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djets/"
OUTPUTSUBDIR="DjetFiles_20170616_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614"
OUTPUTDIR="${OUTPUTPRIDIR}/${OUTPUTSUBDIR}"
LOGDIR="/export/d00/scratch/jwang/hadooplogs/log_${OUTPUTSUBDIR}"

MERGEOUTPUTDIR="/export/d00/scratch/jwang/Djets/MC/"

if [ "$runjobs" -eq 1 ]
then 
  cmsenv
  cd ../skim
  g++ D_jet_skim.C $(root-config --cflags --libs) -Werror -Wall -O2 -o D_jet_skim.exe
  cd ../condor
  cp ../skim/D_jet_skim.exe .
  ./skim_condor_checkfile.sh $INPUTDIR $OUTPUTDIR $MAXFILENO $LOGDIR residuals.tgz $isPP $isMC $ifCHECKEMPTY
fi

if [ "$merger" -eq 1 ]
then
   rm ${MERGEOUTPUTDIR}/${OUTPUTSUBDIR}.root
   hadd ${MERGEOUTPUTDIR}/${OUTPUTSUBDIR}.root ${OUTPUTPRIDIR}/${OUTPUTSUBDIR}/*.root
fi

