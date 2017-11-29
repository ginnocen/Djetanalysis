#ifndef _JETRESOLUTION_H_
#define _JETRESOLUTION_H_

#include "../includes/djet.h"
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
#include <TF1.h>

Float_t jtptBins[] = {30, 40, 50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 250, 300};
const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;
Float_t jtetaBins[] = {0, 1.0, 1.6};
const int nJtetaBins = sizeof(jtetaBins)/sizeof(jtetaBins[0])-1;
Color_t jtetaColor[] = {kBlack, kBlue, kRed+2};

TH1F* ahHistoResoPt[nJtetaBins+1][nJtptBins];
TH1F* ahHistoResoPtCorr[nJtetaBins+1][nJtptBins];
TH1F* ahHistoResoPhi[nJtetaBins+1][nJtptBins];
TH1F* ahHistoResoEta[nJtetaBins+1][nJtptBins];

TH1F* hScalePt[nJtetaBins+1];
TH1F* hScalePtCorr[nJtetaBins+1];
TH1F* hResoPt[nJtetaBins+1];
TH1F* hResoPhi[nJtetaBins+1];
TH1F* hResoEta[nJtetaBins+1];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int j=0;j<nJtetaBins+1;j++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              ahHistoResoPt[j][i] = new TH1F(Form("hHistoResoPt_%d_%d",j,i), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
              ahHistoResoPt[j][i]->Sumw2();
              ahHistoResoPtCorr[j][i] = new TH1F(Form("hHistoResoPtCorr_%d_%d",j,i), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
              ahHistoResoPtCorr[j][i]->Sumw2();
              ahHistoResoPhi[j][i] = new TH1F(Form("hHistoResoPhi_%d_%d",j,i), ";#phi^{reco} - #phi^{gen};", 50, -0.08, 0.08);
              ahHistoResoPhi[j][i]->Sumw2();
              ahHistoResoEta[j][i] = new TH1F(Form("hHistoResoEta_%d_%d",j,i), ";#eta^{reco} - #eta^{gen};", 50, -0.08, 0.08);
              ahHistoResoEta[j][i]->Sumw2();
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int j=0;j<nJtetaBins+1;j++)
        {
          hResoPt[j] = new TH1F(Form("hResoPt_%d",j), ";Gen Jet p_{T} (GeV/c);p_{T}^{reco} / p_{T}^{gen}", nJtptBins, jtptBins);
          hResoPhi[j] = new TH1F(Form("hResoPhi_%d",j), ";Gen Jet p_{T} (GeV/c);#phi^{reco} - #phi^{gen}", nJtptBins, jtptBins);
          hResoEta[j] = new TH1F(Form("hResoEta_%d",j), ";Gen Jet p_{T} (GeV/c);#eta^{reco} - #eta^{gen}", nJtptBins, jtptBins);
          hScalePt[j] = new TH1F(Form("hScalePt_%d",j), ";Gen Jet p_{T} (GeV/c);p_{T}^{reco} / p_{T}^{gen}", nJtptBins, jtptBins);
          hScalePtCorr[j] = new TH1F(Form("hScalePtCorr_%d",j), ";Gen Jet p_{T} (GeV/c);p_{T}^{reco} / p_{T}^{gen}", nJtptBins, jtptBins);
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
      for(int j=0;j<nJtetaBins+1;j++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              ahHistoResoPt[j][i] = (TH1F*)inf->Get(Form("hHistoResoPt_%d_%d",j,i));
              ahHistoResoPtCorr[j][i] = (TH1F*)inf->Get(Form("hHistoResoPtCorr_%d_%d",j,i));
              ahHistoResoPhi[j][i] = (TH1F*)inf->Get(Form("hHistoResoPhi_%d_%d",j,i));
              ahHistoResoEta[j][i] = (TH1F*)inf->Get(Form("hHistoResoEta_%d_%d",j,i));
            }
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int j=0;j<nJtetaBins+1;j++)
        {
          hResoPt[j] = (TH1F*)inf->Get(Form("hResoPt_%d",j));
          hResoPhi[j] = (TH1F*)inf->Get(Form("hResoPhi_%d",j));
          hResoEta[j] = (TH1F*)inf->Get(Form("hResoEta_%d",j));
          hScalePt[j] = (TH1F*)inf->Get(Form("hScalePt_%d",j));
          hScalePtCorr[j] = (TH1F*)inf->Get(Form("hScalePtCorr_%d",j));
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
      for(int j=0;j<nJtetaBins+1;j++)
        {
          for(int i=0;i<nJtptBins;i++)
            {
              ahHistoResoPt[j][i]->Write();
              ahHistoResoPtCorr[j][i]->Write();
              ahHistoResoPhi[j][i]->Write();
              ahHistoResoEta[j][i]->Write();
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int j=0;j<nJtetaBins+1;j++)
        {
          hResoPt[j]->Write();
          hResoPhi[j]->Write();
          hResoEta[j]->Write();
          hScalePt[j]->Write();
          hScalePtCorr[j]->Write();
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
