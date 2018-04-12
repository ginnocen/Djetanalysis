#include <iostream>
#include <iomanip>
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/djet.h"
#include "../includes/djtweight.h"
#include <TGraphAsymmErrors.h> 
#include <TFile.h>
#include <TCanvas.h>
#include <TH2F.h>
#include <TF1.h>

int const nptBins=12;
Float_t ptBins[nptBins+1] = {4., 5., 6., 8., 10., 12.5, 15., 20., 25., 30., 40., 60., 100.};

int const nyBins=8;
Float_t yBins[nyBins+1] = {-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0};

TH1F* ahHistoMassPt[nptBins];
TH1F* ahHistoMassPtSignal[nptBins];
TH1F* ahHistoMassPtSwapped[nptBins];
TH1F* ahHistoMassY[nyBins];
TH1F* ahHistoMassYSignal[nyBins];
TH1F* ahHistoMassYSwapped[nyBins];

int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
    for(int j=0;j<nptBins;j++) {
      ahHistoMassPt[j] = new TH1F(Form("ahHistoMassPt_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassPt[j]->Sumw2();
      ahHistoMassPtSignal[j] = new TH1F(Form("ahHistoMassPtSignal_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassPtSignal[j]->Sumw2();
      ahHistoMassPtSwapped[j] = new TH1F(Form("ahHistoMassPtSwapped_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassPtSwapped[j]->Sumw2();

    }
    for(int j=0;j<nyBins;j++) {
      ahHistoMassY[j] = new TH1F(Form("ahHistoMassY_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassY[j]->Sumw2();
      ahHistoMassYSignal[j] = new TH1F(Form("ahHistoMassYSignal_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassYSignal[j]->Sumw2();
      ahHistoMassYSwapped[j] = new TH1F(Form("ahHistoMassYSwapped_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassYSwapped[j]->Sumw2();
    }
  }
  return 0;
}

int writehists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  std::cout<<"step1"<<std::endl;

  if(opt=="savehist")
    {
      for(int j=0;j<nptBins;j++) {
      ahHistoMassPt[j]->Write();
      ahHistoMassPtSignal[j]->Write();
      ahHistoMassPtSwapped[j]->Write();
      }
      for(int j=0;j<nyBins;j++) {
      ahHistoMassY[j]->Write();
      ahHistoMassYSignal[j]->Write();
      ahHistoMassYSwapped[j]->Write();
      }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

int gethists(TFile* inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="plothist")
    {
    /*
      hDpt_MC_fine = (TH1F*)inf->Get("hDpt_MC_fine");
      hDpt_MC_fine->Sumw2();
      hDpt_MC = (TH1F*)inf->Get("hDpt_MC");
      hDpt_MC->Sumw2();
      hDpt_MC_weight = (TH1F*)inf->Get("hDpt_MC_weight");
      hDpt_MC_weight->Sumw2();
      hDpt_data = (TH1F*)inf->Get("hDpt_data");
      hDpt_data->Sumw2();
      hDpt_Ratio = (TH1F*)inf->Get("hDpt_Ratio");
      hDpt_Ratio->Sumw2();
      hDpt_Ratio_weight = (TH1F*)inf->Get("hDpt_Ratio_weight");
      hDpt_Ratio_weight->Sumw2();
    */
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

