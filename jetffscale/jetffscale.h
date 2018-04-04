#ifndef _JETFFSCALE_H_
#define _JETFFSCALE_H_

// #include "RtypesCore.h"
// Float_t jtptBins[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300};
// const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;
// #define _JTPTBINS

#include "../includes/djet.h"
#include "prefilters.h"
#include "../includes/djtcorr.h"
#include "../includes/djtweight.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TF1.h>

const int nJtnpfBins = 36;
Float_t minJtnpfBins = 0, maxJtnpfBins = (float)nJtnpfBins;
Float_t jtnpfBins[nJtnpfBins];

Float_t xrangeAng;
void setxrangeAng(Int_t ispp) { xrangeAng = ispp?0.05:0.08; }

void init(Int_t ispp) 
{
  setxrangeAng(ispp);
  for(int i=0;i<=nJtnpfBins;i++)
    {
      jtnpfBins[i] = minJtnpfBins + (maxJtnpfBins-minJtnpfBins)*i/nJtnpfBins;
    }
}

TH1F* ahHistoResoPt[NCentBins][nJtptBins];
TH1F* ahHistoResoNpfPt[NCentBins][nJtptBins][nJtnpfBins];
TH1F* ahHistoResoPtCorr[NCentBins][nJtptBins];
TH1F* ahHistoResoNpfPtCorr[NCentBins][nJtptBins][nJtnpfBins];

TH1F* hScalePt[NCentBins];
TH1F* hScalePtCorr[NCentBins];
TH1F* hScaleNpfPt[NCentBins][nJtptBins];
TH1F* hScaleNpfPtCorr[NCentBins][nJtptBins];

TH1F* hScaleP0NpfPt[NCentBins];
TH1F* hScaleP1NpfPt[NCentBins];
TH2F* hvScalePt[NCentBins][nJtptBins];

TH1F* hScaleNpfPtPP[NCentBins][nJtptBins];
TH1F* hScaleNpfPtCorrPP[NCentBins][nJtptBins];
TH1F* hScaleNpfPtPbPb[NCentBins][nJtptBins];
TH1F* hScaleNpfPtCorrPbPb[NCentBins][nJtptBins];
TH2F* hvScalePtPP[NCentBins][nJtptBins];
TH2F* hvScalePtPbPb[NCentBins][nJtptBins];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              for(int j=0;j<nJtnpfBins;j++)
                {
                  ahHistoResoNpfPt[k][i][j] = new TH1F(Form("hHistoResoNpfPt_%d_%d_%d",k,i,j), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
                  ahHistoResoNpfPt[k][i][j]->Sumw2();
                  ahHistoResoNpfPtCorr[k][i][j] = new TH1F(Form("hHistoResoNpfPtCorr_%d_%d_%d",k,i,j), ";p_{T}^{reco} / p_{T}^{gen}, Corr;", 50, 0, 2);
                  ahHistoResoNpfPtCorr[k][i][j]->Sumw2();
                }
              ahHistoResoPt[k][i] = new TH1F(Form("hHistoResoPt_%d_%d",k,i), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
              ahHistoResoPt[k][i]->Sumw2();
              ahHistoResoPtCorr[k][i] = new TH1F(Form("hHistoResoPtCorr_%d_%d",k,i), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
              ahHistoResoPtCorr[k][i]->Sumw2();
              hvScalePt[k][i] = new TH2F(Form("hvScalePt_%d_%d",k,i), ";nPF;Jet energy scale", nJtnpfBins, minJtnpfBins, maxJtnpfBins, 100, 0.8, 1.2);
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hScaleNpfPt[k][i] = new TH1F(Form("hScaleNpfPt_%d_%d",k,i), ";nPF;#mu(p_{T}^{reco} / p_{T}^{gen})", nJtnpfBins, jtnpfBins);
              hScaleNpfPtCorr[k][i] = new TH1F(Form("hScaleNpfPtCorr_%d_%d",k,i), ";nPF;#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", nJtnpfBins, jtnpfBins);
            }
          hScalePt[k] = new TH1F(Form("hScalePt_%d",k), ";p_{T}^{reco};#mu(p_{T}^{reco} / p_{T}^{gen})", nJtptBins, jtptBins);
          hScalePtCorr[k] = new TH1F(Form("hScalePtCorr_%d",k), ";p_{T}^{reco};#mu(p_{T}^{reco} / p_{T}^{gen})", nJtptBins, jtptBins);
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          hScaleP0NpfPt[k] = new TH1F(Form("hScaleP0NpfPt_%d",k), ";jet p_{T}^{reco} (GeV/c);a_{0}", nJtptBins, jtptBins);
          hScaleP1NpfPt[k] = new TH1F(Form("hScaleP1NpfPt_%d",k), ";jet p_{T}^{reco} (GeV/c);a_{1}", nJtptBins, jtptBins);
        }
      return 0;
    }
  std::cout<<"error: invalid option for createhists()"<<std::endl;
  return 1;
}

int gethists(TFile* inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="usehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              for(int j=0;j<nJtnpfBins;j++)
                {
                  ahHistoResoNpfPt[k][i][j] = (TH1F*)inf->Get(Form("hHistoResoNpfPt_%d_%d_%d",k,i,j));
                  ahHistoResoNpfPtCorr[k][i][j] = (TH1F*)inf->Get(Form("hHistoResoNpfPtCorr_%d_%d_%d",k,i,j));
                }
              ahHistoResoPt[k][i] = (TH1F*)inf->Get(Form("hHistoResoPt_%d_%d",k,i));
              ahHistoResoPtCorr[k][i] = (TH1F*)inf->Get(Form("hHistoResoPtCorr_%d_%d",k,i));
            }
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hScaleNpfPt[k][i] = (TH1F*)inf->Get(Form("hScaleNpfPt_%d_%d",k,i));
              hScaleNpfPtCorr[k][i] = (TH1F*)inf->Get(Form("hScaleNpfPtCorr_%d_%d",k,i));
            }
          hScalePt[k] = (TH1F*)inf->Get(Form("hScalePt_%d",k));
          hScalePtCorr[k] = (TH1F*)inf->Get(Form("hScalePtCorr_%d",k));
        }
      return 0;
    }
  if(opt=="plothistpp")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hScaleNpfPtPP[k][i] = (TH1F*)inf->Get(Form("hScaleNpfPt_%d_%d",k,i));
              hScaleNpfPtPP[k][i]->SetName(Form("hScaleNpfPt_%d_%d_pp",k,i));
              hScaleNpfPtCorrPP[k][i] = (TH1F*)inf->Get(Form("hScaleNpfPtCorr_%d_%d",k,i));
              hScaleNpfPtCorrPP[k][i]->SetName(Form("hScaleNpfPtCorr_%d_%d_pp",k,i));
            }
        }
      return 0;
    }
  if(opt=="plothistpbpb")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hScaleNpfPtPbPb[k][i] = (TH1F*)inf->Get(Form("hScaleNpfPt_%d_%d",k,i));
              hScaleNpfPtPbPb[k][i]->SetName(Form("hScaleNpfPt_%d_%d_pbpb",k,i));
              hScaleNpfPtCorrPbPb[k][i] = (TH1F*)inf->Get(Form("hScaleNpfPtCorr_%d_%d",k,i));
              hScaleNpfPtCorrPbPb[k][i]->SetName(Form("hScaleNpfPtCorr_%d_%d_pbpb",k,i));
            }
        }
      return 0;
    }
  if(opt=="plothistscale")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hvScalePt[k][i] = (TH2F*)inf->Get(Form("hvScalePt_%d_%d",k,i));
            }
        }
      return 0;
    }
  if(opt=="plothistscalepp")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hvScalePtPP[k][i] = (TH2F*)inf->Get(Form("hvScalePt_%d_%d",k,i));
              hvScalePtPP[k][i]->SetName(Form("hvScalePt_%d_%d_pp",k,i));
            }
        }
      return 0;
    }
  if(opt=="plothistscalepbpb")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hvScalePtPbPb[k][i] = (TH2F*)inf->Get(Form("hvScalePt_%d_%d",k,i));
              hvScalePtPbPb[k][i]->SetName(Form("hvScalePt_%d_%d_pbpb",k,i));
            }
        }
      return 0;
    }

  if(opt=="plotpar")
    {
      for(int k=0;k<nCentBins;k++)
        {
          hScaleP0NpfPt[k] = (TH1F*)inf->Get(Form("hScaleP0NpfPt_%d",k));
          hScaleP1NpfPt[k] = (TH1F*)inf->Get(Form("hScaleP1NpfPt_%d",k));
          hScalePt[k] = (TH1F*)inf->Get(Form("hScalePt_%d",k));
        }
      return 0;
    }
  if(opt=="plotparcomp")
    {
      for(int k=0;k<nCentBins;k++)
        {
          hScalePt[k] = (TH1F*)inf->Get(Form("hScalePt_%d",k));
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

int writehists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              for(int j=0;j<nJtnpfBins;j++)
                {
                  ahHistoResoNpfPt[k][i][j]->Write();
                  ahHistoResoNpfPtCorr[k][i][j]->Write();
                }
              ahHistoResoPt[k][i]->Write();
              ahHistoResoPtCorr[k][i]->Write();
              hvScalePt[k][i]->Write();
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              hScaleNpfPt[k][i]->Write();
              hScaleNpfPtCorr[k][i]->Write();
            }
          hScalePt[k]->Write();
          hScalePtCorr[k]->Write();
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          hScaleP0NpfPt[k]->Write();
          hScaleP1NpfPt[k]->Write();
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
