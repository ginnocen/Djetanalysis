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

const int nScale = 4;
TString nameScale[nScale] = {"ScaleP", "ScaleM", "ScaleQ", "ScaleG"};
TString legScale[nScale] = {"data-MC diff+", "data-MC diff-", "Quark jes", "Gluon jes"};

Color_t colorlist[] = {kGreen-5, kRed-9, kAzure-4, kViolet-9, kOrange-9};

TH1F* ahSignalRnorm[nRefBins][nPtBins];
TH1F* ahSignalRnormScale[nRefBins][nPtBins][nScale];
TH1F* ahSignalRsub[nPtBins];
TH1F* ahSignalRsubScale[nPtBins][nScale];

TH1F* ahDevRnormScale[nRefBins][nPtBins][nScale];
TH1F* ahDevRsubScale[nPtBins][nScale];
TH1F* ahDevRsubtotal[nPtBins];

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
              for(int v=0;v<nScale;v++)
                { ahDevRnormScale[l][i][v] = new TH1F(Form("hDevRnormScale_%s_%s_pt_%d",nameScale[v].Data(),tRef[l].Data(),i), ";r;", nDrBins, drBins); }
            }
          for(int v=0;v<nScale;v++)
            { ahDevRsubScale[i][v] = new TH1F(Form("hDevRsubScale_%s_pt_%d",nameScale[v].Data(),i), ";r;", nDrBins, drBins); }
          ahDevRsubtotal[i] = new TH1F(Form("hDevRsubtotal_pt_%d",i), ";r;", nDrBins, drBins);
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
              ahSignalRnorm[l][i]->Scale(1./ahSignalRnorm[l][i]->Integral("width"));
            }
          ahSignalRsub[i] = (TH1F*)inf[0]->Get(Form("hSignalRsubMe_pt_%d",i));
        }
      return 0;
    }
  if(opt.Contains("plothist_scale"))
    {
      for(int v=0;v<nScale;v++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              for(int l=0;l<nRefBins;l++)
                {
                  ahSignalRnormScale[l][i][v] = (TH1F*)inf[v]->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
                  ahSignalRnormScale[l][i][v]->SetName(Form("hSignalRnorm_%s_%s_pt_%d",nameScale[v].Data(),tRef[l].Data(),i));
                  ahSignalRnormScale[l][i][v]->Scale(1./ahSignalRnormScale[l][i][v]->Integral("width"));
                }
              ahSignalRsubScale[i][v] = (TH1F*)inf[v]->Get(Form("hSignalRsubMe_pt_%d",i));
              ahSignalRsubScale[i][v]->SetName(Form("hSignalRsubMe_%s_pt_%d",nameScale[v].Data(),i));              
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}



#endif
