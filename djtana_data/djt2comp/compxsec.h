#ifndef _COMPXSEC_H_
#define _COMPXSEC_H_

#include "prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TFile.h>

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};
const int nCorr = 2;
TString legCorr[nCorr-1] = {"sgen / gen jet"};
Color_t colCorr[nCorr-1] = {kRed-7};
TString tHist[nCorr] = {"hSignalRsubMe_pt", "hSignalRsubMe_pt"};
TString tRatio[nCorr] = {"hSignalRsubRatioMe_pt", "hSignalRsubRatioMe_pt"};

//
TH1F* ahSignalRnorm[nCorr][nPtBins];

//
TH1F* ahCorrFactor[nPtBins];

int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();

  if(opt=="usehist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahCorrFactor[i] = new TH1F(Form("hCorrFactor_%d",i), "", nDrBins, drBins);
        }
      return 0; 
    }
  std::cout<<"error: invalid option for createhists()"<<std::endl;
  return 1;
}

int gethists(std::vector<TFile*> inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();

  if(opt=="usehist")
    {
      for(int m=0;m<nCorr;m++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              ahSignalRnorm[m][i] = (TH1F*)inf[m]->Get(Form("%s_%d",tHist[m].Data(),i));
              ahSignalRnorm[m][i]->SetName(Form("hSignalRnorm_Case%d_pt_%d",m,i));
              // ahSignalRnorm[m][i]->Scale(1./ahSignalRnorm[m][i]->Integral("width"));
            }
        }
      return 0;
    }
  if(opt=="usehist_ratio")
    {
      for(int m=0;m<nCorr;m++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              ahSignalRnorm[m][i] = (TH1F*)inf[m]->Get(Form("%s_%d",tRatio[m].Data(),i));
              ahSignalRnorm[m][i]->SetName(Form("hSignalRnorm_Case%d_pt_%d",m,i));
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
