#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/dfitter.h"
#include "../includes/djtcorr.h"
#include "../includes/djthlt.h"
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
TString tRef[nRefBins] = {"eta", "etaref"};

Color_t amcolor[2] = {kBlack, kRed};
Style_t amstyle[nRefBins][2] = {{20,     21},   {24,     25}};

Color_t fmcolor[2] = {kAzure-6, kRed+3};
Style_t fmstyle[2] = {20, 21};
Color_t ffcolor[2] = {kAzure-4, kRed-9};
TString fleg[2] = {"pp", "PbPb"};

TH1F* ahHistoRMass[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSignal[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSwapped[nRefBins][nPtBins][nDrBins];

TH1F* hNjets;

TH1F* ahREfficiency[nRefBins][nPtBins];
TH1F* ahNumREfficiency[nRefBins][nPtBins];
TH1F* ahDenREfficiency[nRefBins][nPtBins];

TH1F* ahSignalRraw[nRefBins][nPtBins];
TH1F* ahSignalR[nRefBins][nPtBins];
TH1F* ahSignalRnorm[nRefBins][nPtBins];
TH1F* ahSignalRsub[nPtBins];

TH1F* ahSignalRnormP[2][nRefBins][nPtBins];
TH1F* ahSignalRnormRatio[nRefBins][nPtBins];
TH1F* ahSignalRsubP[2][nPtBins];
TH1F* ahSignalRsubRatio[nPtBins];

TGraphErrors* agSignalRsubP[2][nPtBins];
TGraphErrors* agSignalRsubRatio[nPtBins];

TH1F* ahHistoRMassRef[nPtBins];
TH1F* ahHistoRMassSignalRef[nPtBins];
TH1F* ahHistoRMassSwappedRef[nPtBins];
TH1F* ahREfficiencyRef[nPtBins];
TH1F* ahNumREfficiencyRef[nPtBins];
TH1F* ahDenREfficiencyRef[nPtBins];
TH1F* ahSignalRRef[nPtBins];

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
              ahNumREfficiency[l][i] = new TH1F(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahNumREfficiency[l][i]->Sumw2();
              ahDenREfficiency[l][i] = new TH1F(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahDenREfficiency[l][i]->Sumw2();
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j] = new TH1F(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  ahHistoRMassSignal[l][i][j]->Sumw2();
                  ahHistoRMassSwapped[l][i][j] = new TH1F(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  ahHistoRMassSwapped[l][i][j]->Sumw2();
                }
            }
          ahREfficiencyRef[i] = new TH1F(Form("hREfficiencyRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahREfficiencyRef[i]->Sumw2();
          ahNumREfficiencyRef[i] = new TH1F(Form("hNumREfficiencyRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahNumREfficiencyRef[i]->Sumw2();
          ahDenREfficiencyRef[i] = new TH1F(Form("hDenREfficiencyRef_pt_%d",i), ";r;", 1, 0, 0.3);
          ahDenREfficiencyRef[i]->Sumw2();

          ahHistoRMassSignalRef[i] = new TH1F(Form("hHistoRMassSignalRef_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          ahHistoRMassSignalRef[i]->Sumw2();
          ahHistoRMassSwappedRef[i] = new TH1F(Form("hHistoRMassSwappedRef_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          ahHistoRMassSwappedRef[i]->Sumw2();
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
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = new TH1F(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
            }
          ahHistoRMassRef[i] = new TH1F(Form("hHistoRMassRef_pt_%d",i), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
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
              ahSignalR[l][i] = new TH1F(Form("hSignalR_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalRnorm[l][i] = new TH1F(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
            }
          ahSignalRsub[i] = new TH1F(Form("hSignalRsub_pt_%d",i), ";r;", nDrBins, drBins);
          ahSignalRRef[i] = new TH1F(Form("hSignalRRef_pt_%d",i), ";r;", 1, 0, 0.3);
        }
      return 0;
    }
  if(opt=="saveratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormRatio[l][i] = new TH1F(Form("hSignalRnormRatio_%s_pt_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
            }
          ahSignalRsubRatio[i] = new TH1F(Form("hSignalRsubRatio_pt_%d",i), ";r;", nDrBins, drBins);
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
              ahNumREfficiency[l][i]->Write();
              ahDenREfficiency[l][i]->Write();
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j]->Write();
                  ahHistoRMassSwapped[l][i][j]->Write();
                }
            }
          ahREfficiencyRef[i]->Write();
          ahNumREfficiencyRef[i]->Write();
          ahDenREfficiencyRef[i]->Write();

          ahHistoRMassSignalRef[i]->Write();
          ahHistoRMassSwappedRef[i]->Write();
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
          ahSignalRsub[i]->Write();
        }
      return 0;
    }
  if(opt=="saveratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormRatio[l][i]->Write();
            }
          ahSignalRsubRatio[i]->Write();
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
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
            }
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
              ahDenREfficiency[l][i] = (TH1F*)inf->Get(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahNumREfficiency[l][i] = (TH1F*)inf->Get(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i));
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                  ahHistoRMassSwapped[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                }
            }
          ahREfficiencyRef[i] = (TH1F*)inf->Get(Form("hREfficiencyRef_pt_%d",i));
          ahNumREfficiencyRef[i] = (TH1F*)inf->Get(Form("hNumREfficiencyRef_pt_%d",i));
          ahDenREfficiencyRef[i] = (TH1F*)inf->Get(Form("hDenREfficiencyRef_pt_%d",i));
          ahHistoRMassSignalRef[i] = (TH1F*)inf->Get(Form("hHistoRMassSignalRef_pt_%d",i));
          ahHistoRMassSwappedRef[i] = (TH1F*)inf->Get(Form("hHistoRMassSwappedRef_pt_%d",i));
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
          ahSignalRsub[i] = (TH1F*)inf->Get(Form("hSignalRsub_pt_%d",i));
        }
      return 0;
    }
  if(opt.Contains("saveratio") && (opt.Contains("pp")||opt.Contains("pbpb")))
    {
      Int_t isPbPb = opt.Contains("pp")?0:1;
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormP[isPbPb][l][i] = (TH1F*)inf->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
              ahSignalRnormP[isPbPb][l][i]->SetName(Form("hSignalRnorm_%s_pt_%d_%s",tRef[l].Data(),i,tPbPb[isPbPb].Data()));
            }
          ahSignalRsubP[isPbPb][i] = (TH1F*)inf->Get(Form("hSignalRsub_pt_%d",i));
          ahSignalRsubP[isPbPb][i]->SetName(Form("hSignalRsub_pt_%d_%s",i,tPbPb[isPbPb].Data()));
        }
      return 0;
    }
  if(opt=="plotratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormRatio[l][i] = (TH1F*)inf->Get(Form("hSignalRnormRatio_%s_pt_%d",tRef[l].Data(),i));
            }
          ahSignalRsubRatio[i] = (TH1F*)inf->Get(Form("hSignalRsubRatio_pt_%d",i));
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
