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

TH1F* hDpt_MC_fine;
TH1F* hDpt_MC;
TH1F* hDpt_MC_weight;
TH1F* hDpt_data;
TH1F* hDpt_Ratio;
TH1F* hDpt_Ratio_weight;

Float_t ptBins[] = {2., 3., 4., 5., 6., 8., 10., 12.5, 15., 20., 25., 30., 40., 60., 100.};
const int nPtBins = sizeof(ptBins)/sizeof(ptBins[0])-1;
int NPTBINS = 200;
Float_t PT_MIN = 0, PT_MAX = 100;

int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      hDpt_MC_fine = new TH1F("hDpt_MC_fine", "", NPTBINS, PT_MIN, PT_MAX);
      hDpt_MC_fine->Sumw2();
      hDpt_MC = new TH1F("hDpt_MC", "", nPtBins, ptBins);
      hDpt_MC->Sumw2();
      hDpt_MC_weight = new TH1F("hDpt_MC_weight", "", nPtBins, ptBins);
      hDpt_MC_weight->Sumw2();
      hDpt_data = new TH1F("hDpt_data", "", nPtBins, ptBins);
      hDpt_data->Sumw2();
      hDpt_Ratio = new TH1F("hDpt_Ratio", "", nPtBins, ptBins);
      hDpt_Ratio->Sumw2();
      hDpt_Ratio_weight = new TH1F("hDpt_Ratio_weight", "", nPtBins, ptBins);
      hDpt_Ratio_weight->Sumw2();
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
      hDpt_MC_fine->Write();
      hDpt_MC->Write();
      hDpt_MC_weight->Write();
      hDpt_data->Write();
      hDpt_Ratio->Write();
      hDpt_Ratio_weight->Write();
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
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

