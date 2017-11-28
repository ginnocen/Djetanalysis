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


TH1F* ahHistoResoPt[nJtptBins];
TH1F* ahHistoResoPhi[nJtptBins];
TH1F* ahHistoResoEta[nJtptBins];

TH1F* hResoPt;
TH1F* hResoPhi;
TH1F* hResoEta;

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int i=0;i<nJtptBins;i++)
        {
          ahHistoResoPt[i] = new TH1F(Form("hHistoResoPt_%d",i), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
          ahHistoResoPt[i]->Sumw2();
          ahHistoResoPhi[i] = new TH1F(Form("hHistoResoPhi_%d",i), ";#phi^{reco} - #phi^{gen};", 50, -0.08, 0.08);
          ahHistoResoPhi[i]->Sumw2();
          ahHistoResoEta[i] = new TH1F(Form("hHistoResoEta_%d",i), ";#eta^{reco} - #eta^{gen};", 50, -0.08, 0.08);
          ahHistoResoEta[i]->Sumw2();
        }
      return 0;
    }
  if(opt=="usehist")
    {
      hResoPt = new TH1F("hResoPt", ";Gen Jet p_{T} (GeV/c);p_{T}^{reco} / p_{T}^{gen}", nJtptBins, jtptBins);
      hResoPhi = new TH1F("hResoPhi", ";Gen Jet p_{T} (GeV/c);#phi^{reco} - #phi^{gen}", nJtptBins, jtptBins);
      hResoEta = new TH1F("hResoEta", ";Gen Jet p_{T} (GeV/c);#eta^{reco} - #eta^{gen}", nJtptBins, jtptBins);
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
      for(int i=0;i<nJtptBins;i++)
        {
          ahHistoResoPt[i] = (TH1F*)inf->Get(Form("hHistoResoPt_%d",i));
          ahHistoResoPhi[i] = (TH1F*)inf->Get(Form("hHistoResoPhi_%d",i));
          ahHistoResoEta[i] = (TH1F*)inf->Get(Form("hHistoResoEta_%d",i));
        }
      return 0;
    }
  std::cout<<"error: invalid option for createhists()"<<std::endl;
  return 1;
}

int writehists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int i=0;i<nJtptBins;i++)
        {
          ahHistoResoPt[i]->Write();
          ahHistoResoPhi[i]->Write();
          ahHistoResoEta[i]->Write();
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
