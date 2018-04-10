#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "prefilters.h"
#include "../includes/djet.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/dfitter.h"
#include "../includes/djtcorr.h"
#include "../includes/djthlt.h"
#include "../includes/djtweight.h"
#include "../includes/djtuti.h"
#include "../includes/systmetics.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TGraphErrors.h>

const Float_t DZERO_MASS = 1.8649;

//
const int nRefBins = 2;
// TString tRef[nRefBins] = {"eta", "etaref", "sigDueJ", "ueDsigJ", "ueDueJ"};
TString tRef[nRefBins] = {"eta", "etaref"};
const int nMeBins = 3;
TString tMe[nMeBins] = {"uej", "ued", "uejd"};
TString tlegMe[nMeBins] = {"MB jets", "MB D", "MB jets, MB D"};

Color_t amcolor[2] = {kBlack, kBlack};
Style_t amstyle[nRefBins] = {20, 24};
Style_t amstyleMe[nMeBins] = {24, 25, 28};

// Color_t fmcolor[3] = {kAzure-6, kRed+3};
Color_t fmcolor[3] = {kAzure+3, kRed+3, kGreen+3};
Style_t fmstyle[3] = {20, 21, 34};
// Color_t ffcolor[3] = {kAzure-4, kRed-9};
Color_t ffcolor[3] = {kAzure-8, kRed-9, kGreen-8};
TString fleg[3] = {"pp", "PbPb", "PYTHIA"};

TH1F* hNjets;

TH1F* ahHistoRMass[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSignal[nPtBins][nDrBins];
TH1F* ahHistoRMassSwapped[nPtBins][nDrBins];
// TH1F* ahHistoRMassSignal[nRefBins][nPtBins][nDrBins];
// TH1F* ahHistoRMassSwapped[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSignalRef[nPtBins];
TH1F* ahHistoRMassSwappedRef[nPtBins];
TH1F* ahHistoRMassSignalMe[nPtBins];
TH1F* ahHistoRMassSwappedMe[nPtBins];

TH1F* ahREfficiency[nRefBins][nPtBins];
TH1F* ahREff[nRefBins][nPtBins];
TH1F* ahRAcceptance[nRefBins][nPtBins];
TH1F* ahNumREfficiency[nRefBins][nPtBins];
TH1F* ahDenREfficiency[nRefBins][nPtBins];
TH1F* ahAccREfficiency[nRefBins][nPtBins];

TH1F* ahSignalRraw[nRefBins][nPtBins];
TH1F* ahSignalR[nRefBins][nPtBins];
TH1F* ahSignalRnorm[nRefBins][nPtBins];

TH1F* ahHistoRMassRef[nPtBins];
TH1F* ahREfficiencyRef[nPtBins];
TH1F* ahREffRef[nPtBins];
TH1F* ahRAcceptanceRef[nPtBins];
TH1F* ahNumREfficiencyRef[nPtBins];
TH1F* ahDenREfficiencyRef[nPtBins];
TH1F* ahAccREfficiencyRef[nPtBins];

TH1F* ahSignalRrawRef[nPtBins];
TH1F* ahSignalRRef[nPtBins];

TH1F* ahHistoRMassMe[nMeBins][nPtBins];

TH1F* ahSignalRrawMe[nMeBins][nPtBins];
TH1F* ahSignalRMe[nMeBins][nPtBins];
TH1F* ahSignalRnormMe[nMeBins][nPtBins];

TH1F* ahSignalRsub[nPtBins];
TH1F* ahSignalRsubUncorr[nPtBins];
TH1F* ahSignalRsubMe[nPtBins];
TH1F* ahSignalRsubUncorrMe[nPtBins];

//
TH1F* ahSignalRsubP[2][nPtBins];
TH1F* ahSignalRsubMeP[2][nPtBins];
TH1F* ahSignalRsubRatio[nPtBins];
TH1F* ahSignalRsubRatioMe[nPtBins];
TGraphErrors* agSignalRsubP[2][nPtBins];
TGraphErrors* agSignalRsubMeP[2][nPtBins];
TGraphErrors* agSignalRsubRatio[nPtBins];
TGraphErrors* agSignalRsubRatioMe[nPtBins];
TH1F* ahSignalRsubPYTHIA[nPtBins];
TH1F* ahSignalRsubRatioPYTHIA[nPtBins];
TH1F* ahSignalRsubRatioPYTHIAMe[nPtBins];
TGraphErrors* agSignalRsubPYTHIA[nPtBins];
TGraphErrors* agSignalRsubRatioPYTHIA[nPtBins];
TGraphErrors* agSignalRsubRatioPYTHIAMe[nPtBins];

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
          for(int j=0;j<nDrBins;j++) 
            {
              ahHistoRMassSignal[i][j] = new TH1F(Form("hHistoRMassSignal_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSignal[i][j]->Sumw2();
              ahHistoRMassSwapped[i][j] = new TH1F(Form("hHistoRMassSwapped_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwapped[i][j]->Sumw2();
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

          ahHistoRMassSignalRef[i] = new TH1F(Form("hHistoRMassSignalRef_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          ahHistoRMassSignalRef[i]->Sumw2();
          ahHistoRMassSwappedRef[i] = new TH1F(Form("hHistoRMassSwappedRef_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          ahHistoRMassSwappedRef[i]->Sumw2();
          ahHistoRMassSignalMe[i] = new TH1F(Form("hHistoRMassSignalMe_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          ahHistoRMassSignalMe[i]->Sumw2();
          ahHistoRMassSwappedMe[i] = new TH1F(Form("hHistoRMassSwappedMe_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          ahHistoRMassSwappedMe[i]->Sumw2();

        }
      return 0;
    }
  if(opt=="savehist")
    {
      hNjets = new TH1F("hNjets", "", 1, 0, 1);
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMass[l][i][j] = new TH1F(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  ahHistoRMass[l][i][j]->Sumw2();
                }
            }
          ahHistoRMassRef[i] = new TH1F(Form("hHistoRMassRef_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          ahHistoRMassRef[i]->Sumw2();
          for(int l=0;l<nMeBins;l++)
            {
              ahHistoRMassMe[l][i] = new TH1F(Form("hHistoRMassMe_%s_pt_%d",tMe[l].Data(),i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassMe[l][i]->Sumw2();
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRraw[l][i] = new TH1F(Form("hSignalRraw_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalRraw[l][i]->Sumw2();
              ahSignalR[l][i] = new TH1F(Form("hSignalR_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalR[l][i]->Sumw2();
              ahSignalRnorm[l][i] = new TH1F(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalRnorm[l][i]->Sumw2();
            }
          for(int l=0;l<nMeBins;l++)
            {
              ahSignalRrawMe[l][i] = new TH1F(Form("hSignalRrawMe_%s_pt_%d",tMe[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalRrawMe[l][i]->Sumw2();
              ahSignalRMe[l][i] = new TH1F(Form("hSignalRMe_%s_pt_%d",tMe[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalRMe[l][i]->Sumw2();
              ahSignalRnormMe[l][i] = new TH1F(Form("hSignalRnormMe_%s_pt_%d",tMe[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalRnormMe[l][i]->Sumw2();
            }
          ahSignalRRef[i] = new TH1F(Form("hSignalRRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahSignalRRef[i]->Sumw2();
          ahSignalRrawRef[i] = new TH1F(Form("hSignalRrawRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahSignalRrawRef[i]->Sumw2();

          ahSignalRsub[i] = new TH1F(Form("hSignalRsub_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsub[i]->Sumw2();
          ahSignalRsubUncorr[i] = new TH1F(Form("hSignalRsubUncorr_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsubUncorr[i]->Sumw2();
          ahSignalRsubMe[i] = new TH1F(Form("hSignalRsubMe_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsubMe[i]->Sumw2();
          ahSignalRsubUncorrMe[i] = new TH1F(Form("hSignalRsubUncorrMe_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsubUncorrMe[i]->Sumw2();
        }
      return 0;
    }
  if(opt=="saveratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRsubRatio[i] = new TH1F(Form("hSignalRsubRatio_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsubRatio[i]->Sumw2();
          ahSignalRsubRatioMe[i] = new TH1F(Form("hSignalRsubRatioMe_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsubRatioMe[i]->Sumw2();
        }
      return 0;
    }
  if(opt=="pythia")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRsubRatioPYTHIA[i] = new TH1F(Form("hSignalRsubRatioPYTHIA_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsubRatioPYTHIA[i]->Sumw2();
          ahSignalRsubRatioPYTHIAMe[i] = new TH1F(Form("hSignalRsubRatioPYTHIAMe_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRsubRatioPYTHIAMe[i]->Sumw2();
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
          for(int j=0;j<nDrBins;j++) 
            {
              ahHistoRMassSignal[i][j]->Write();
              ahHistoRMassSwapped[i][j]->Write();
            }
          ahREfficiencyRef[i]->Write();
          ahREffRef[i]->Write();
          ahRAcceptanceRef[i]->Write();
          ahNumREfficiencyRef[i]->Write();
          ahDenREfficiencyRef[i]->Write();
          ahAccREfficiencyRef[i]->Write();

          ahHistoRMassSignalRef[i]->Write();
          ahHistoRMassSwappedRef[i]->Write();
          ahHistoRMassSignalMe[i]->Write();
          ahHistoRMassSwappedMe[i]->Write();
        }
      return 0;
    }
  if(opt=="savehist")
    {
      hNjets->Write();
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j]->Write();
            }
          for(int l=0;l<nMeBins;l++)
            {
              ahHistoRMassMe[l][i]->Write();
            }
          ahHistoRMassRef[i]->Write();
        }
      return 0;
    }
  if(opt.Contains("usehist"))
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRraw[l][i]->Write();
              ahSignalR[l][i]->Write();
              ahSignalRnorm[l][i]->Write();
            }
          for(int l=0;l<nMeBins;l++)
            {
              ahSignalRrawMe[l][i]->Write();
              ahSignalRMe[l][i]->Write();
              ahSignalRnormMe[l][i]->Write();
            }
          ahSignalRsub[i]->Write();
          ahSignalRsubUncorr[i]->Write();
          ahSignalRsubMe[i]->Write();
          ahSignalRsubUncorrMe[i]->Write();
        }
      return 0;
    }
  if(opt=="saveratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRsubRatio[i]->Write();
          ahSignalRsubRatioMe[i]->Write();
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
  if(opt=="hist")
    {
      hNjets = (TH1F*)inf->Get("hNjets");
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) 
                { ahHistoRMass[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j)); }
            }
          for(int l=0;l<nMeBins;l++)
            { ahHistoRMassMe[l][i] = (TH1F*)inf->Get(Form("hHistoRMassMe_%s_pt_%d",tMe[l].Data(),i)); }
          ahHistoRMassRef[i] = (TH1F*)inf->Get(Form("hHistoRMassRef_pt_%d",i));
        }
      return 0;
    }
  if(opt=="tpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahREfficiency[l][i] = (TH1F*)inf->Get(Form("hREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahREff[l][i] = (TH1F*)inf->Get(Form("hREff_%s_pt_%d",tRef[l].Data(),i));
              ahRAcceptance[l][i] = (TH1F*)inf->Get(Form("hRAcceptance_%s_pt_%d",tRef[l].Data(),i));
              ahNumREfficiency[l][i] = (TH1F*)inf->Get(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahDenREfficiency[l][i] = (TH1F*)inf->Get(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahAccREfficiency[l][i] = (TH1F*)inf->Get(Form("hAccREfficiency_%s_pt_%d",tRef[l].Data(),i));
            } 
          for(int j=0;j<nDrBins;j++) 
            {
              ahHistoRMassSignal[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignal_pt_%d_dr_%d",i,j));
              ahHistoRMassSwapped[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwapped_pt_%d_dr_%d",i,j));
            }
          ahREfficiencyRef[i] = (TH1F*)inf->Get(Form("hREfficiencyRef_pt_%d",i));
          ahREffRef[i] = (TH1F*)inf->Get(Form("hREffRef_pt_%d",i));
          ahRAcceptanceRef[i] = (TH1F*)inf->Get(Form("hRAcceptanceRef_pt_%d",i));
          ahNumREfficiencyRef[i] = (TH1F*)inf->Get(Form("hNumREfficiencyRef_pt_%d",i));
          ahDenREfficiencyRef[i] = (TH1F*)inf->Get(Form("hDenREfficiencyRef_pt_%d",i));
          ahAccREfficiencyRef[i] = (TH1F*)inf->Get(Form("hAccREfficiencyRef_pt_%d",i));
          ahHistoRMassSignalRef[i] = (TH1F*)inf->Get(Form("hHistoRMassSignalRef_pt_%d",i));
          ahHistoRMassSwappedRef[i] = (TH1F*)inf->Get(Form("hHistoRMassSwappedRef_pt_%d",i));
          ahHistoRMassSignalMe[i] = (TH1F*)inf->Get(Form("hHistoRMassSignalMe_pt_%d",i));
          ahHistoRMassSwappedMe[i] = (TH1F*)inf->Get(Form("hHistoRMassSwappedMe_pt_%d",i));
        }
      return 0;
    }
  if(opt.Contains("plothist"))
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnorm[l][i] = (TH1F*)inf->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
            }
          for(int l=0;l<nMeBins;l++)
            {
              ahSignalRnormMe[l][i] = (TH1F*)inf->Get(Form("hSignalRnormMe_%s_pt_%d",tMe[l].Data(),i));
            }
          ahSignalRsub[i] = (TH1F*)inf->Get(Form("hSignalRsub_pt_%d",i));
          ahSignalRsubUncorr[i] = (TH1F*)inf->Get(Form("hSignalRsubUncorr_pt_%d",i));
          ahSignalRsubMe[i] = (TH1F*)inf->Get(Form("hSignalRsubMe_pt_%d",i));
          ahSignalRsubUncorrMe[i] = (TH1F*)inf->Get(Form("hSignalRsubUncorrMe_pt_%d",i));
        }
      return 0;
    }
  if(opt.Contains("saveratio") && (opt.Contains("pp")||opt.Contains("pbpb")))
    {
      Int_t isPbPb = opt.Contains("pp")?0:1;
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRsubP[isPbPb][i] = (TH1F*)inf->Get(Form("hSignalRsub_pt_%d",i));
          ahSignalRsubP[isPbPb][i]->SetName(Form("hSignalRsub_pt_%d_%s",i,tPbPb[isPbPb].Data()));
          ahSignalRsubMeP[isPbPb][i] = (TH1F*)inf->Get(Form("hSignalRsubMe_pt_%d",i));
          ahSignalRsubMeP[isPbPb][i]->SetName(Form("hSignalRsubMe_pt_%d_%s",i,tPbPb[isPbPb].Data()));
        }
      return 0;
    }
  if(opt=="plotratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRsubRatio[i] = (TH1F*)inf->Get(Form("hSignalRsubRatio_pt_%d",i));
          ahSignalRsubRatioMe[i] = (TH1F*)inf->Get(Form("hSignalRsubRatioMe_pt_%d",i));
        }
      return 0;
    }
  if(opt=="pythia")
    {
      for(int i=0;i<nPtBins;i++)
        { 
          ahSignalRsubPYTHIA[i] = (TH1F*)inf->Get(Form("hSignalRsub_pt_%d",i));
          ahSignalRsubPYTHIA[i]->SetName(Form("hSignalRsub_pt_%d_PYTHIA",i));
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

void verbose_stat(Float_t jetptmin, Float_t jetptmax)
{
  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]<999?Form("%s - %s",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()):Form(" > %s",xjjc::number_remove_zero(ptBins[i]).c_str());
      std::cout<<std::setiosflags(std::ios::left)<<"jetpt "<<std::setw(5)<<jetptmin<<" - "<<std::setw(5)<<jetptmax<<" Dpt "<<std::setw(10)<<texpt<<std::endl;
      std::cout<<"normal cone:"<<std::endl;
      int l=0;
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(13)<<"r";
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<"raw"<<std::setw(15)<<"raw stat";
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<"eff"<<std::setw(15)<<"eff stat";
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<"yield/dr"<<std::setw(15)<<"yield/dr stat";
      std::cout<<std::endl;
      for(int j=0;j<nDrBins;j++)
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(6)<<drBins[j]<<" - "<<std::setw(6)<<drBins[j+1];
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<(ahSignalRraw)[l][i]->GetBinContent(j+1)<<std::setw(15)<<(ahSignalRraw)[l][i]->GetBinError(j+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<(ahREfficiency)[l][i]->GetBinContent(j+1)<<std::setw(15)<<(ahREfficiency)[l][i]->GetBinError(j+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<(ahSignalRnorm)[l][i]->GetBinContent(j+1)<<std::setw(15)<<(ahSignalRnorm)[l][i]->GetBinError(j+1);
          std::cout<<std::endl;
        }
      std::cout<<"ref cone:"<<std::endl;
      l = 1;
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(13)<<"r";
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<"yield/dr"<<std::setw(15)<<"yield/dr stat";
      std::cout<<std::endl;
      for(int j=0;j<nDrBins;j++)
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(6)<<drBins[j]<<" - "<<std::setw(6)<<drBins[j+1];
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<(ahSignalRrawRef)[i]->GetBinContent(j+1)<<std::setw(15)<<(ahSignalRrawRef)[i]->GetBinError(j+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<(ahREfficiencyRef)[i]->GetBinContent(j+1)<<std::setw(15)<<(ahREfficiencyRef)[i]->GetBinError(j+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<(ahSignalRnorm)[l][i]->GetBinContent(j+1)<<std::setw(15)<<(ahSignalRnorm)[l][i]->GetBinError(j+1);
          std::cout<<std::endl;
        }
      std::cout<<"subtracted:"<<std::endl;
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(13)<<"r";
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<"(1/N)dN/dr"<<std::setw(15)<<"(1/N)dN/dr stat";
      std::cout<<std::endl;
      for(int j=0;j<nDrBins;j++)
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(6)<<drBins[j]<<" - "<<std::setw(6)<<drBins[j+1];
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<(ahSignalRsub)[i]->GetBinContent(j+1)<<std::setw(15)<<(ahSignalRsub)[i]->GetBinError(j+1);
          std::cout<<std::endl;
        }
    }
}


#endif


