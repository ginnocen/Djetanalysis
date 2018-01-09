#ifndef _JETFFSCALE_H_
#define _JETFFSCALE_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/paramCorr.h"
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

Float_t jtptBins[] = {30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300};
// Float_t jtptBins[] = {30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400};
const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;
const int nJtnpfBins = 40;
Float_t minJtnpfBins = 0, maxJtnpfBins = (float)nJtnpfBins;
Float_t jtnpfBins[nJtnpfBins];

Float_t xrangeAng;
void setxrangeAng(Int_t ispp) {xrangeAng = ispp?0.05:0.08;}

void init(Int_t ispp) 
{
  setnCentBins(ispp); setxrangeAng(ispp);
  for(int i=0;i<=nJtnpfBins;i++)
    {
      jtnpfBins[i] = minJtnpfBins + (maxJtnpfBins-minJtnpfBins)*i/nJtnpfBins;
    }
}

TH1F* ahHistoResoNpfPt[NCentBins][nJtptBins][nJtnpfBins];
TH1F* ahHistoResoNpfPtCorr[NCentBins][nJtptBins][nJtnpfBins];

TH1F* hScaleNpfPt[NCentBins][nJtptBins];
TH1F* hScaleNpfPtCorr[NCentBins][nJtptBins];

TH1F* hScaleP0NpfPt[NCentBins];
TH1F* hScaleP1NpfPt[NCentBins];
TH2F* hvScalePt[NCentBins][nJtptBins];

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
  if(opt=="plotpar")
    {
      for(int k=0;k<nCentBins;k++)
        {
          hScaleP0NpfPt[k] = (TH1F*)inf->Get(Form("hScaleP0NpfPt_%d",k));
          hScaleP1NpfPt[k] = (TH1F*)inf->Get(Form("hScaleP1NpfPt_%d",k));
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
