#ifndef _DJTCLOSURE_H_
#define _DJTCLOSURE_H_

#include "../includes/prefilters.h"
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

const Float_t DZERO_MASS = 1.8649;

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};
const int nCases = 4;
TString tCases[nCases] = {"RecoD_RecoJet", "GenD_RecoJet", "RecoD_GenJet", "GenD_GenJet"};
TString legCases[nCases] = {"RecoD, RecoJet", "GenD, RecoJet", "RecoD, GenJet", "GenD, GenJet"};

//
Color_t amcolor[nCases] = {kBlack, kAzure-1, kGreen+3, kRed+1};
Style_t amstyle[nRefBins] = {20, 24};

// TH1F* hNjets;

TH1F* ahSignalRnorm[nCases][nRefBins][nPtBins];
TH1F* ahSignalZnorm[nCases][nRefBins][nPtBins];
TH1F* ahSignalRsub[nCases][nPtBins];
TH1F* ahSignalZsub[nCases][nPtBins];

TH1F* ahSignalRnormRatio[nCases][nRefBins][nPtBins];
TH1F* ahSignalZnormRatio[nCases][nRefBins][nPtBins];
TH1F* ahSignalRsubRatio[nCases][nPtBins];
TH1F* ahSignalZsubRatio[nCases][nPtBins];

//
int gethists(std::vector<TFile*> inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();

  if(opt=="plothist")
    {
      for(int m=0;m<nCases;m++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              for(int l=0;l<nRefBins;l++)
                {
                  ahSignalRnorm[m][l][i] = (TH1F*)inf[m]->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
                  ahSignalZnorm[m][l][i] = (TH1F*)inf[m]->Get(Form("hSignalZnorm_%s_pt_%d",tRef[l].Data(),i));
                }
              ahSignalRsub[m][i] = (TH1F*)inf[m]->Get(Form("hSignalRsub_pt_%d",i));
              ahSignalZsub[m][i] = (TH1F*)inf[m]->Get(Form("hSignalZsub_pt_%d",i));
            }
        }
      return 0;
    }
  if(opt=="plotratio")
    {
      for(int m=0;m<nCases;m++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              for(int l=0;l<nRefBins;l++)
                {
                  ahSignalRnormRatio[m][l][i] = (TH1F*)inf[m]->Get(Form("hSignalRnormRatio_%s_pt_%d",tRef[l].Data(),i));
                  ahSignalZnormRatio[m][l][i] = (TH1F*)inf[m]->Get(Form("hSignalZnormRatio_%s_pt_%d",tRef[l].Data(),i));
                }
              ahSignalRsubRatio[m][i] = (TH1F*)inf[m]->Get(Form("hSignalRsubRatio_pt_%d",i));
              ahSignalZsubRatio[m][i] = (TH1F*)inf[m]->Get(Form("hSignalZsubRatio_pt_%d",i));
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
