#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TFile.h>

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

const int nReso = 1;
TString nameReso[nReso] = {"15per"};
TString legReso[nReso] = {"data-MC diff"};

Color_t colorlist[] = {kGreen-5, kRed-9, kAzure-4, kViolet-9, kOrange-9};

TH1F* hNjets;

// TH1F* ahSignalRraw[nRefBins][nPtBins];
// TH1F* ahSignalR[nRefBins][nPtBins];
TH1F* ahSignalRnorm[nRefBins][nPtBins];
TH1F* ahSignalRnormReso[nRefBins][nPtBins][nReso];
TH1F* ahSignalRsub[nPtBins];
TH1F* ahSignalRsubReso[nPtBins][nReso];

TH1F* ahDevRnormReso[nRefBins][nPtBins][nReso];
TH1F* ahDevRsubReso[nPtBins][nReso];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="plothist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int v=0;v<nReso;v++)
                ahDevRnormReso[l][i][v] = new TH1F(Form("hDevRnormReso_%s_%s_pt_%d",nameReso[v].Data(),tRef[l].Data(),i), ";r;", nDrBins, drBins);
            }
          for(int v=0;v<nReso;v++)
            ahDevRsubReso[i][v] = new TH1F(Form("hDevRsubReso_%s_pt_%d",nameReso[v].Data(),i), ";r;", nDrBins, drBins);
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

  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

int gethists(std::vector<TFile*> inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt.Contains("plothist_default"))
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnorm[l][i] = (TH1F*)inf[0]->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
            }
          ahSignalRsub[i] = (TH1F*)inf[0]->Get(Form("hSignalRsubMe_pt_%d",i));
        }
      return 0;
    }
  if(opt.Contains("plothist_reso"))
    {
      for(int v=0;v<nReso;v++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              for(int l=0;l<nRefBins;l++)
                {
                  ahSignalRnormReso[l][i][v] = (TH1F*)inf[v]->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
                  ahSignalRnormReso[l][i][v]->SetName(Form("hSignalRnorm_%s_%s_pt_%d",nameReso[v].Data(),tRef[l].Data(),i));
                  ahSignalRnormReso[l][i][v]->Scale(1./ahSignalRnormReso[l][i][v]->Integral("width"));
                }
              ahSignalRsubReso[i][v] = (TH1F*)inf[v]->Get(Form("hSignalRsubMe_pt_%d",i));
              ahSignalRsubReso[i][v]->SetName(Form("hSignalRsubMe_%s_pt_%d",nameReso[v].Data(),i));              
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
