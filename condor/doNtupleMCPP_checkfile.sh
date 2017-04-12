#!/bin/sh
isMC=1
isPP=1
MAXFILENO=10

runjobs=${1:-0}
merger=${2:-0}

INPUTDIR="/mnt/hadoop/cms/store/user/wangj/Pythia8_prompt_D0pt0p0_Pthat30_pp502_TuneCUETP8M1/crab_DfinderMC_pp_20170404_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/170404_181158/"
OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djets/"
OUTPUTSUBDIR="DjetFiles_20170412_pp_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat30_20170404"
OUTPUTDIR="${OUTPUTPRIDIR}/${OUTPUTSUBDIR}"
LOGDIR="/export/d00/scratch/jwang/hadooplogs/log_${OUTPUTSUBDIR}"

MERGEOUTPUTDIR="/export/d00/scratch/jwang/"

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

