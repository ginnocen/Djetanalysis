#!/bin/sh

iPTHAT=8

#
isMC=1
isPP=1
MAXFILENO=1000000000000000

#
PTHATS=(0 5 10 15 30 50 80 120 170)
DATES=(170504_195346 170405_183014 170405_174114 170405_173147 170504_195942 170405_172432 170405_172740 170405_174225 170504_195818)

runjobs=${1:-0}
merger=${2:-0}

INPUTDIR="/mnt/hadoop/cms/store/user/wangj/Pythia8_prompt_D0pt0p0_Pthat${PTHATS[iPTHAT]}_pp502_TuneCUETP8M1/crab_DfinderMC_pp_20170404_Pthat${PTHATS[iPTHAT]}_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar/${DATES[iPTHAT]}/0000/"
OUTPUTPRIDIR="/mnt/hadoop/cms/store/user/jwang/Djets/"
OUTPUTSUBDIR="DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_Pthat${PTHATS[iPTHAT]}_20170404"
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

