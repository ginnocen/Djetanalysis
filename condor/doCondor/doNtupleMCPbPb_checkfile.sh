#!/bin/sh

iPTHAT=0
j=0

#
isMC=1
isPP=0
MAXFILENO=10000000000

#
PTHATS=(0 5 10 15 30 50 80 120 170)
DATES=(170509_012008 170509_012353 170509_013004 170509_013211 170509_013343 170509_011006 170509_013743 170509_014258 170509_014353)

runjobs=${1:-0}
merger=${2:-0}

INPUTDIR="/mnt/hadoop/cms/store/user/wangj/Pythia8_prompt_D0pt0p0_Pthat${PTHATS[iPTHAT]}_Hydjet_MB/crab_HiForestAOD_DfinderMC_PbPb_20170508_Pthat${PTHATS[iPTHAT]}_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/${DATES[iPTHAT]}/000${j}/"
OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djets/"
OUTPUTSUBDIR="DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat${PTHATS[iPTHAT]}_20170508"
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
  ./skim_condor_checkfile.sh $INPUTDIR $OUTPUTDIR $MAXFILENO $LOGDIR residuals.tgz $isPP $isMC 
fi

if [ "$merger" -eq 1 ]
then
   rm ${MERGEOUTPUTDIR}/${OUTPUTSUBDIR}.root
   hadd ${MERGEOUTPUTDIR}/${OUTPUTSUBDIR}.root ${OUTPUTPRIDIR}/${OUTPUTSUBDIR}/*.root
fi

