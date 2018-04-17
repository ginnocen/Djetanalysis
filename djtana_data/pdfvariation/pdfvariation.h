#ifndef _PDFVARIATION_H_
#define _PDFVARIATION_H_

#include "prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/djet.h"
#include "../includes/djtweight.h"
#include "../includes/djtcorr.h"
#include "../includes/djtuti.h"
#include "dfitter_variation.h"

#include <TH2F.h>
#include <TH1F.h>
#include <TFile.h>
#include <TColor.h>

const Float_t DZERO_MASS = 1.8649;

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

const int nVariation = 9;
TString fitopt[nVariation] = {"", "3", "2PO", "", "", "", "", "", ""};
TString fitname[nVariation] = {"Default", "3", "2PO", "narrow", "wide", "widpol3", "widpol4", "widpol5", "widpol6"};
TString fitleg[nVariation] = {"Default","3 Gaus", "2nd ord pol", "width -", "width +", "width pol3", "width pol4", "width pol5", "width pol6"};
int vsignal[] = {1, 3, 4, 5, 6, 7, 8};

const int nvsignal = sizeof(vsignal) / sizeof(vsignal[0]);
int vbackground[] = {2};
const int nvbackground = sizeof(vbackground) / sizeof(vbackground[0]);
// TString fitopt[nVariation] = {"", "3", "WP", "WM", "2PO"};
// TString fitname[nVariation] = {"Default", "3", "WP", "WM", "2PO"};
// TString fitleg[nVariation] = {"Default","3 Gaus", "Increase wid", "Decrease wid", "2nd ord pol"};
Color_t fitcolor[] = {kGray+3, kOrange-9, kGreen-5, kRed-9, kAzure-4, kViolet-9, kCyan-3, kMagenta-8, kYellow-8};

TH1F* ahHistoRMass[nPtBins][nDrBins];
TH1F* ahHistoRMassSignal[nPtBins][nDrBins];
TH1F* ahHistoRMassSwapped[nPtBins][nDrBins];

TH1F* ahHistoRMassSignallow[nPtBins][nDrBins];
TH1F* ahHistoRMassSwappedlow[nPtBins][nDrBins];
TH1F* ahHistoRMassSignalhigh[nPtBins][nDrBins];
TH1F* ahHistoRMassSwappedhigh[nPtBins][nDrBins];
TH1F* ahHistoRMassSignalpol3[nPtBins][nDrBins];
TH1F* ahHistoRMassSwappedpol3[nPtBins][nDrBins];
TH1F* ahHistoRMassSignalpol4[nPtBins][nDrBins];
TH1F* ahHistoRMassSwappedpol4[nPtBins][nDrBins];
TH1F* ahHistoRMassSignalpol5[nPtBins][nDrBins];
TH1F* ahHistoRMassSwappedpol5[nPtBins][nDrBins];
TH1F* ahHistoRMassSignalpol6[nPtBins][nDrBins];
TH1F* ahHistoRMassSwappedpol6[nPtBins][nDrBins];

TH1F* ahSignalRraw[nPtBins][nVariation];
TH1F* ahSignalRdev[nPtBins][nVariation];
TH1F* ahSignalRdevtotal[nPtBins];

TH1F* ahSignalRrawPP[nPtBins][nVariation];
TH1F* ahSignalRrawPbPb[nPtBins][nVariation];
TH1F* ahSignalRrawRatio[nPtBins][nVariation];
TH1F* ahSignalRdevRatio[nPtBins][nVariation];
TH1F* ahSignalRdevtotalRatio[nPtBins];

int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savetpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              ahHistoRMassSignallow[i][j] = new TH1F(Form("hHistoRMassSignallow_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSignallow[i][j]->Sumw2();
              ahHistoRMassSwappedlow[i][j] = new TH1F(Form("hHistoRMassSwappedlow_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwappedlow[i][j]->Sumw2();
              ahHistoRMassSignalhigh[i][j] = new TH1F(Form("hHistoRMassSignalhigh_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSignalhigh[i][j]->Sumw2();
              ahHistoRMassSwappedhigh[i][j] = new TH1F(Form("hHistoRMassSwappedhigh_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwappedhigh[i][j]->Sumw2();
              ahHistoRMassSignalpol3[i][j] = new TH1F(Form("hHistoRMassSignalpol3_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSignalpol3[i][j]->Sumw2();
              ahHistoRMassSwappedpol3[i][j] = new TH1F(Form("hHistoRMassSwappedpol3_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwappedpol3[i][j]->Sumw2();
              ahHistoRMassSignalpol4[i][j] = new TH1F(Form("hHistoRMassSignalpol4_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSignalpol4[i][j]->Sumw2();
              ahHistoRMassSwappedpol4[i][j] = new TH1F(Form("hHistoRMassSwappedpol4_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwappedpol4[i][j]->Sumw2();
              ahHistoRMassSignalpol5[i][j] = new TH1F(Form("hHistoRMassSignalpol5_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSignalpol5[i][j]->Sumw2();
              ahHistoRMassSwappedpol5[i][j] = new TH1F(Form("hHistoRMassSwappedpol5_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwappedpol5[i][j]->Sumw2();
              ahHistoRMassSignalpol6[i][j] = new TH1F(Form("hHistoRMassSignalpol6_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSignalpol6[i][j]->Sumw2();
              ahHistoRMassSwappedpol6[i][j] = new TH1F(Form("hHistoRMassSwappedpol6_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwappedpol6[i][j]->Sumw2();
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int v=0;v<nVariation;v++)
            {
              ahSignalRraw[i][v] = new TH1F(Form("hSignalRraw_%s_pt_%d_%s","eta",i,fitname[v].Data()), ";r;", nDrBins, drBins);
              ahSignalRdev[i][v] = new TH1F(Form("hSignalRdev_%s_pt_%d_%s","eta",i,fitname[v].Data()), ";r;", nDrBins, drBins);
            }
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRdevtotal[i] = new TH1F(Form("hSignalRdevtotal_%s_pt_%d","eta",i), ";r;", nDrBins, drBins);
        }
      return 0;
    }
  if(opt=="plotratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int v=0;v<nVariation;v++)
            {
              ahSignalRrawRatio[i][v] = new TH1F(Form("hSignalRrawRatio_%s_pt_%d_%s","eta",i,fitname[v].Data()), ";r;", nDrBins, drBins);
              ahSignalRdevRatio[i][v] = new TH1F(Form("hSignalRdevRatio_%s_pt_%d_%s","eta",i,fitname[v].Data()), ";r;", nDrBins, drBins);
            }
          ahSignalRdevtotalRatio[i] = new TH1F(Form("hSignalRdevtotalRatio_%s_pt_%d","eta",i), ";r;", nDrBins, drBins);
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
  if(opt=="hist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++) ahHistoRMass[i][j] = (TH1F*)inf->Get(Form("hHistoRMass_%s_pt_%d_dr_%d","eta",i,j));
        }
      return 0;
    }
  if(opt=="tpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              ahHistoRMassSignal[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignal_pt_%d_dr_%d",i,j));
              ahHistoRMassSwapped[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwapped_pt_%d_dr_%d",i,j));
            }
        }
      return 0;
    }
  if(opt=="tplscale")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              ahHistoRMassSignallow[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignallow_pt_%d_dr_%d",i,j));
              ahHistoRMassSwappedlow[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwappedlow_pt_%d_dr_%d",i,j));
              ahHistoRMassSignalhigh[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignalhigh_pt_%d_dr_%d",i,j));
              ahHistoRMassSwappedhigh[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwappedhigh_pt_%d_dr_%d",i,j));
              ahHistoRMassSignalpol3[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignalpol3_pt_%d_dr_%d",i,j));
              ahHistoRMassSwappedpol3[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwappedpol3_pt_%d_dr_%d",i,j));
              ahHistoRMassSignalpol4[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignalpol4_pt_%d_dr_%d",i,j));
              ahHistoRMassSwappedpol4[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwappedpol4_pt_%d_dr_%d",i,j));
              ahHistoRMassSignalpol5[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignalpol5_pt_%d_dr_%d",i,j));
              ahHistoRMassSwappedpol5[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwappedpol5_pt_%d_dr_%d",i,j));
              ahHistoRMassSignalpol6[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignalpol6_pt_%d_dr_%d",i,j));
              ahHistoRMassSwappedpol6[i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwappedpol6_pt_%d_dr_%d",i,j));
            }
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int v=0;v<nVariation;v++)
            {
              ahSignalRdev[i][v] = (TH1F*)inf->Get(Form("hSignalRdev_%s_pt_%d_%s","eta",i,fitname[v].Data()));
            }
        }
      return 0;
    }
  if(opt=="plotratiopp")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int v=0;v<nVariation;v++)
            {
              ahSignalRrawPP[i][v] = (TH1F*)inf->Get(Form("hSignalRraw_%s_pt_%d_%s","eta",i,fitname[v].Data()));
              ahSignalRrawPP[i][v]->SetName(Form("hSignalRrawPP_%s_pt_%d_%s","eta",i,fitname[v].Data()));                  
            }
        }
      return 0;
    }
  if(opt=="plotratiopbpb")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int v=0;v<nVariation;v++)
            {
              ahSignalRrawPbPb[i][v] = (TH1F*)inf->Get(Form("hSignalRraw_%s_pt_%d_%s","eta",i,fitname[v].Data()));
              ahSignalRrawPbPb[i][v]->SetName(Form("hSignalRrawPbPb_%s_pt_%d_%s","eta",i,fitname[v].Data()));                  
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
  if(opt=="savetpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              ahHistoRMassSignallow[i][j]->Write();
              ahHistoRMassSwappedlow[i][j]->Write();
              ahHistoRMassSignalhigh[i][j]->Write();
              ahHistoRMassSwappedhigh[i][j]->Write();
              ahHistoRMassSignalpol3[i][j]->Write();
              ahHistoRMassSwappedpol3[i][j]->Write();
              ahHistoRMassSignalpol4[i][j]->Write();
              ahHistoRMassSwappedpol4[i][j]->Write();
              ahHistoRMassSignalpol5[i][j]->Write();
              ahHistoRMassSwappedpol5[i][j]->Write();
              ahHistoRMassSignalpol6[i][j]->Write();
              ahHistoRMassSwappedpol6[i][j]->Write();
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int v=0;v<nVariation;v++)
            {
              ahSignalRraw[i][v]->Write();
              ahSignalRdev[i][v]->Write();
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
