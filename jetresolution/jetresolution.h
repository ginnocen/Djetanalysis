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

Float_t jtptBins[] = {30, 40, 50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 250, 300};
const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;


TH1F* ahHistoResoPt[nJtptBins];
TH1F* ahHistoResoPhi[nJtptBins];
TH1F* ahHistoResoEta[nJtptBins];


//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int i=0;i<nJtptBins;i++)
        {
          ahHistoResoPt[i] = new TH1F(Form("hHistoResoPt_%d",i), ";Gen Jet p_{T} (GeV/c);", 50, 0, 2);
          ahHistoResoPt[i]->Sumw2();
          ahHistoResoPhi[i] = new TH1F(Form("hHistoResoPhi_%d",i), ";Gen Jet p_{T} (GeV/c);", 50, -0.08, 0.08);
          ahHistoResoPhi[i]->Sumw2();
          ahHistoResoEta[i] = new TH1F(Form("hHistoResoEta_%d",i), ";Gen Jet p_{T} (GeV/c);", 50, -0.08, 0.08);
          ahHistoResoEta[i]->Sumw2();
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
