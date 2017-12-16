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

Float_t jtptBins[] = {30, 40, 50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 250, 300};
const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;
// Float_t jtetaBins[] = {0, 1.0, 1.6};
// const int nJtetaBins = sizeof(jtetaBins)/sizeof(jtetaBins[0])-1;
const int nJtnpfBins = 40;
Float_t minJtnpfBins = 0, maxJtnpfBins = (float)nJtnpfBins;
Float_t jtnpfBins[nJtnpfBins];
// Color_t jtetaColor[] = {kBlack, kBlue, kRed+2};

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
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
