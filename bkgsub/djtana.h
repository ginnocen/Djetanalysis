#ifndef _DJTANA_H_
#define _DJTANA_H_

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
#include <TRandom2.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TPad.h>

const Float_t DZERO_MASS = 1.8649;

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};
const int nMeBins = 3;
TString tMe[nMeBins] = {"uej", "ued", "uejd"};
TString tlegMe[nMeBins] = {"MB jets", "MB D", "MB jets, MB D"};

Color_t amcolor[2] = {kBlack, kRed};
Style_t amstyle[nRefBins][2] = {{20,     21},   {24,     25}};

TH1F* ahSignalRPH[nRefBins][nPtBins];
TH1F* ahSignalRPHsub[nPtBins];
TH1F* ahSignalRPHbkg[nPtBins];

TH1F* ahSignalRP[nRefBins][nPtBins];
TH1F* ahSignalRPsub[nPtBins];
TH1F* ahSignalRPbkg[nPtBins];

TH1F* ahSignalRMe[nMeBins][nPtBins];
TH1F* ahSignalRMesub[nPtBins];

TH1F* ahSignalRatio[nPtBins];
TH1F* ahSignalRatioMe[nPtBins];
TH1F* hDensity;
TH1F* hnjet;

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();

  if(opt=="savehist")
    {
      hnjet = new TH1F("hnjet", "", 1, 0, 1);
      hDensity = new TH1F("hDensity", "", nPtBins, 0, nPtBins);
      hDensity->Sumw2();
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRPsub[i] = new TH1F(Form("hSignalRPsub_%d",i), ";r;", nDrBins, drBins);
          ahSignalRPbkg[i] = new TH1F(Form("hSignalRPbkg_%d",i), ";r;", nDrBins, drBins);
          ahSignalRPHsub[i] = new TH1F(Form("hSignalRPHsub_%d",i), ";r;", nDrBins, drBins);
          ahSignalRPHbkg[i] = new TH1F(Form("hSignalRPHbkg_%d",i), ";r;", nDrBins, drBins);
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRP[l][i] = new TH1F(Form("hSignalRP_%s_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
              ahSignalRPH[l][i] = new TH1F(Form("hSignalRPH_%s_%d",tRef[l].Data(),i), ";r;", nDrBins, drBins);
            }
          for(int l=0;l<nMeBins;l++)
            {
              ahSignalRMe[l][i] = new TH1F(Form("hSignalRMe_%s_%d",tMe[l].Data(),i), ";r;", nDrBins, drBins);
            }
          ahSignalRMesub[i] = new TH1F(Form("hSignalRMesub_%d",i), ";r;", nDrBins, drBins);
        }
      return 0;
    }

  if(opt=="plothist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRatio[i] = new TH1F(Form("hSignalRatio_%d",i), ";r;", nDrBins, drBins);
          ahSignalRatioMe[i] = new TH1F(Form("hSignalRatioMe_%d",i), ";r;", nDrBins, drBins);
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
      hnjet->Write();
      hDensity->Write();
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRPsub[i]->Write();
          ahSignalRPbkg[i]->Write();
          ahSignalRPHsub[i]->Write();
          ahSignalRMesub[i]->Write();
          ahSignalRPHbkg[i]->Write();
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRP[l][i]->Write();
              ahSignalRPH[l][i]->Write();
            }
          for(int l=0;l<nMeBins;l++)
            {
              ahSignalRMe[l][i]->Write();
            }
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
      hnjet = (TH1F*)inf->Get("hnjet");
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRPsub[i] = (TH1F*)inf->Get(Form("hSignalRPsub_%d",i));
          ahSignalRPbkg[i] = (TH1F*)inf->Get(Form("hSignalRPbkg_%d",i));
          ahSignalRPHsub[i] = (TH1F*)inf->Get(Form("hSignalRPHsub_%d",i));
          ahSignalRPHbkg[i] = (TH1F*)inf->Get(Form("hSignalRPHbkg_%d",i));
          ahSignalRMesub[i] = (TH1F*)inf->Get(Form("hSignalRMesub_%d",i));
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRP[l][i] = (TH1F*)inf->Get(Form("hSignalRP_%s_%d",tRef[l].Data(),i));
              ahSignalRPH[l][i] = (TH1F*)inf->Get(Form("hSignalRPH_%s_%d",tRef[l].Data(),i));
            }
          for(int l=0;l<nMeBins;l++)
            {
              ahSignalRMe[l][i] = (TH1F*)inf->Get(Form("hSignalRMe_%s_%d",tMe[l].Data(),i));
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
