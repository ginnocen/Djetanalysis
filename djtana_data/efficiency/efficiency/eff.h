#ifndef _EFF_H_
#define _EFF_H_

#include "../includes/djet.h"
#include "prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/djtcorr.h"
#include "../includes/djtweight.h"
#include "../includes/djtuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TF1.h>

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

Color_t amcolor[2] = {kBlack, kRed};
Style_t amstyle[nRefBins][2] = {{20, 21},   {24, 25}};

TH1F* ahREfficiency[nRefBins][nPtBins];
TH1F* ahREff[nRefBins][nPtBins];
TH1F* ahRAcceptance[nRefBins][nPtBins];
TH1F* ahNumREfficiency[nRefBins][nPtBins];
TH1F* ahDenREfficiency[nRefBins][nPtBins];
TH1F* ahAccREfficiency[nRefBins][nPtBins];

TH1F* ahREfficiencyRef[nPtBins];
TH1F* ahREffRef[nPtBins];
TH1F* ahRAcceptanceRef[nPtBins];
TH1F* ahNumREfficiencyRef[nPtBins];
TH1F* ahDenREfficiencyRef[nPtBins];
TH1F* ahAccREfficiencyRef[nPtBins];

const int NHIST = 10;
Color_t colorlist[] = {kGreen-5, kRed-7, kAzure-4, kOrange-4, kBlue-6, kGray+2, kMagenta-8, kCyan+2, kYellow-2, };

TH1F* vhREfficiency[nPtBins][NHIST];
TH1F* vhREff[nPtBins][NHIST];
TH1F* vhRAcceptance[nPtBins][NHIST];
TH1F* vhREfficiencyRef[nPtBins][NHIST];
TH1F* vhREffRef[nPtBins][NHIST];
TH1F* vhRAcceptanceRef[nPtBins][NHIST];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savetpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahREfficiency[l][i] = new TH1F(Form("hREfficiency_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahREfficiency[l][i]->Sumw2();
              ahREff[l][i] = new TH1F(Form("hREff_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahREff[l][i]->Sumw2();
              ahRAcceptance[l][i] = new TH1F(Form("hRAcceptance_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahRAcceptance[l][i]->Sumw2();
              ahNumREfficiency[l][i] = new TH1F(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahNumREfficiency[l][i]->Sumw2();
              ahDenREfficiency[l][i] = new TH1F(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahDenREfficiency[l][i]->Sumw2();
              ahAccREfficiency[l][i] = new TH1F(Form("hAccREfficiency_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahAccREfficiency[l][i]->Sumw2();
            }
          ahREfficiencyRef[i] = new TH1F(Form("hREfficiencyRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahREfficiencyRef[i]->Sumw2();
          ahREffRef[i] = new TH1F(Form("hREffRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahREffRef[i]->Sumw2();
          ahRAcceptanceRef[i] = new TH1F(Form("hRAcceptanceRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahRAcceptanceRef[i]->Sumw2();
          ahNumREfficiencyRef[i] = new TH1F(Form("hNumREfficiencyRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahNumREfficiencyRef[i]->Sumw2();
          ahDenREfficiencyRef[i] = new TH1F(Form("hDenREfficiencyRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahDenREfficiencyRef[i]->Sumw2();
          ahAccREfficiencyRef[i] = new TH1F(Form("hAccREfficiencyRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahAccREfficiencyRef[i]->Sumw2();
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

  if(opt=="savetpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahREfficiency[l][i]->Write();
              ahREff[l][i]->Write();
              ahRAcceptance[l][i]->Write();
              ahNumREfficiency[l][i]->Write();
              ahDenREfficiency[l][i]->Write();
              ahAccREfficiency[l][i]->Write();
            }
          ahREfficiencyRef[i]->Write();
          ahREffRef[i]->Write();
          ahRAcceptanceRef[i]->Write();
          ahNumREfficiencyRef[i]->Write();
          ahDenREfficiencyRef[i]->Write();
          ahAccREfficiencyRef[i]->Write();
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

int gethists(std::vector<TFile*> inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="tpl")
    {
      if(inf.size()!=1) { std::cout<<"error: wrong inputfile number gethists()"<<std::endl; return 2; }
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahREfficiency[l][i] = (TH1F*)inf[0]->Get(Form("hREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahREff[l][i] = (TH1F*)inf[0]->Get(Form("hREff_%s_pt_%d",tRef[l].Data(),i));
              ahRAcceptance[l][i] = (TH1F*)inf[0]->Get(Form("hRAcceptance_%s_pt_%d",tRef[l].Data(),i));
              ahNumREfficiency[l][i] = (TH1F*)inf[0]->Get(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahDenREfficiency[l][i] = (TH1F*)inf[0]->Get(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahAccREfficiency[l][i] = (TH1F*)inf[0]->Get(Form("hAccREfficiency_%s_pt_%d",tRef[l].Data(),i));
            }
          ahREfficiencyRef[i] = (TH1F*)inf[0]->Get(Form("hREfficiencyRef_pt_%d",i));
          ahREffRef[i] = (TH1F*)inf[0]->Get(Form("hREffRef_pt_%d",i));
          ahRAcceptanceRef[i] = (TH1F*)inf[0]->Get(Form("hRAcceptanceRef_pt_%d",i));
          ahNumREfficiencyRef[i] = (TH1F*)inf[0]->Get(Form("hNumREfficiencyRef_pt_%d",i));
          ahDenREfficiencyRef[i] = (TH1F*)inf[0]->Get(Form("hDenREfficiencyRef_pt_%d",i));
          ahAccREfficiencyRef[i] = (TH1F*)inf[0]->Get(Form("hAccREfficiencyRef_pt_%d",i));
        }
      return 0;
    }
  if(opt=="plothist")
    {
      int nhist = inf.size();
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nhist;j++)
            {
              vhREfficiency[i][j] = (TH1F*)inf[j]->Get(Form("hREfficiency_%s_pt_%d",tRef[0].Data(),i));
              vhREfficiency[i][j]->SetName(Form("%s_%d",vhREfficiency[i][j]->GetName(),j));
              vhREff[i][j] = (TH1F*)inf[j]->Get(Form("hREff_%s_pt_%d",tRef[0].Data(),i));
              vhREff[i][j]->SetName(Form("%s_%d",vhREff[i][j]->GetName(),j));
              vhRAcceptance[i][j] = (TH1F*)inf[j]->Get(Form("hRAcceptance_%s_pt_%d",tRef[0].Data(),i));
              vhRAcceptance[i][j]->SetName(Form("%s_%d",vhRAcceptance[i][j]->GetName(),j));

              vhREfficiencyRef[i][j] = (TH1F*)inf[j]->Get(Form("hREfficiencyRef_pt_%d",i));
              vhREfficiencyRef[i][j]->SetName(Form("%s_%d",vhREfficiencyRef[i][j]->GetName(),j));
              vhREffRef[i][j] = (TH1F*)inf[j]->Get(Form("hREffRef_pt_%d",i));
              vhREffRef[i][j]->SetName(Form("%s_%d",vhREffRef[i][j]->GetName(),j));
              vhRAcceptanceRef[i][j] = (TH1F*)inf[j]->Get(Form("hRAcceptanceRef_pt_%d",i));
              vhRAcceptanceRef[i][j]->SetName(Form("%s_%d",vhRAcceptanceRef[i][j]->GetName(),j));
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
