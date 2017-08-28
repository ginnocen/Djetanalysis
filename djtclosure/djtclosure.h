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
TH1F* ahSignalRnormPull[nCases][nRefBins][nPtBins];
TH1F* ahSignalZnormPull[nCases][nRefBins][nPtBins];
TH1F* ahSignalRsub[nCases][nPtBins];
TH1F* ahSignalZsub[nCases][nPtBins];
TH1F* ahSignalRsubPull[nCases][nPtBins];
TH1F* ahSignalZsubPull[nCases][nPtBins];

TH1F* ahSignalRsubRatio[nCases][nPtBins];
TH1F* ahSignalZsubRatio[nCases][nPtBins];
TH1F* ahSignalRsubRatioPull[nCases][nPtBins];
TH1F* ahSignalZsubRatioPull[nCases][nPtBins];

//
int createhists(Option_t* option)
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
                  ahSignalRnormPull[m][l][i] = new TH1F(Form("hSignalRnormPull_%s_pt_%d_%s",tRef[l].Data(),i,tCases[m].Data()), ";;", nDrBins, drBins);
                  ahSignalZnormPull[m][l][i] = new TH1F(Form("hSignalZnormPull_%s_pt_%d_%s",tRef[l].Data(),i,tCases[m].Data()), ";;", nZBins, zBins);
                }
              ahSignalRsubPull[m][i] = new TH1F(Form("hSignalRsubPull_pt_%d_%s",i,tCases[m].Data()), ";;", nDrBins, drBins);
              ahSignalZsubPull[m][i] = new TH1F(Form("hSignalZsubPull_pt_%d_%s",i,tCases[m].Data()), ";;", nZBins, zBins);
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
              ahSignalRsubRatioPull[m][i] = new TH1F(Form("hSignalRsubRatioPull_pt_%d_%s",i,tCases[m].Data()), ";;", nDrBins, drBins);
              ahSignalZsubRatioPull[m][i] = new TH1F(Form("hSignalZsubRatioPull_pt_%d_%s",i,tCases[m].Data()), ";;", nZBins, zBins);
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

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
                  ahSignalRnorm[m][l][i]->SetName(Form("hSignalRnorm_%s_pt_%d_%s",tRef[l].Data(),i,tCases[m].Data()));
                  ahSignalZnorm[m][l][i] = (TH1F*)inf[m]->Get(Form("hSignalZnorm_%s_pt_%d",tRef[l].Data(),i));
                  ahSignalZnorm[m][l][i]->SetName(Form("hSignalZnorm_%s_pt_%d_%s",tRef[l].Data(),i,tCases[m].Data()));
                }
              ahSignalRsub[m][i] = (TH1F*)inf[m]->Get(Form("hSignalRsub_pt_%d",i));
              ahSignalRsub[m][i]->SetName(Form("hSignalRsub_pt_%d_%s",i,tCases[m].Data()));
              ahSignalZsub[m][i] = (TH1F*)inf[m]->Get(Form("hSignalZsub_pt_%d",i));
              ahSignalZsub[m][i]->SetName(Form("hSignalZsub_pt_%d_%s",i,tCases[m].Data()));
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
              // for(int l=0;l<nRefBins;l++)
              //   {
              //     ahSignalRnormRatio[m][l][i] = (TH1F*)inf[m]->Get(Form("hSignalRnormRatio_%s_pt_%d",tRef[l].Data(),i));
              //     ahSignalRnormRatio[m][l][i]->SetName(Form("hSignalRnormRatio_%s_pt_%d_%s",tRef[l].Data(),i,tCases[m].Data()));
              //     ahSignalZnormRatio[m][l][i] = (TH1F*)inf[m]->Get(Form("hSignalZnormRatio_%s_pt_%d",tRef[l].Data(),i));
              //     ahSignalZnormRatio[m][l][i]->SetName(Form("hSignalZnormRatio_%s_pt_%d_%s",tRef[l].Data(),i,tCases[m].Data()));
              //   }
              ahSignalRsubRatio[m][i] = (TH1F*)inf[m]->Get(Form("hSignalRsubRatio_pt_%d",i));
              ahSignalRsubRatio[m][i]->SetName(Form("hSignalRsubRatio_pt_%d_%s",i,tCases[m].Data()));
              ahSignalZsubRatio[m][i] = (TH1F*)inf[m]->Get(Form("hSignalZsubRatio_pt_%d",i));
              ahSignalZsubRatio[m][i]->SetName(Form("hSignalZsubRatio_pt_%d_%s",i,tCases[m].Data()));
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
