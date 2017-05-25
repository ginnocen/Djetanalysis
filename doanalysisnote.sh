#!/bin/bash
downloadfromscratch=0
uploadplots=0
commitplots=1


export trunk=analysisnote/notes/AN-17-097/trunk/
export home=/net/hisrv0001/home/ginnocen/Djet/CMSSW_7_5_8_patch3/src/Djetanalysis

if [ $downloadfromscratch -eq 1 ]
then

  svn co -N svn+ssh://svn.cern.ch/reps/tdr2 analysisnote
  cd analysisnote
  svn update utils
  svn update -N notes
  svn update notes/AN-17-097
fi

if [ $uploadplots -eq 1 ]
then
  cd $trunk
  cp -r $home/PlotsFits PlotsFits
  cp -r $home/PlotsResults PlotsResults
fi

if [ $commitplots -eq 1 ]
then
  cd $trunk
  svn add PlotsResults PlotsFits
  svn commit -m "update plots"
fi


cd $home


