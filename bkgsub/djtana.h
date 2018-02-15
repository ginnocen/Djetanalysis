#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/paramCorr.h"
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

Color_t amcolor[nPtBins] = {kBlack, kRed};
Style_t amstyle[nRefBins][nPtBins] = {{20,     21},   {24,     25}};

TH1F* ahSignalRPH[nRefBins][nPtBins];
TH1F* ahSignalRPHsub[nPtBins];
TH1F* ahSignalRP[nPtBins];
TH1F* ahSignalRatio[nPtBins];

TH1F* hnjet;

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();

  if(opt=="savehist")
    {
      hnjet = new TH1F("hnjet", "", 1, 0, 1);
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRP[i] = new TH1F(Form("hSignalRP_%d",i), ";#Delta R;", nDrBins, drBins);
          ahSignalRPHsub[i] = new TH1F(Form("hSignalRPHsub_%d",i), ";#Delta R;", nDrBins, drBins);
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRPH[l][i] = new TH1F(Form("hSignalRPH_%s_%d",tRef[l].Data(),i), ";#Delta R;", nDrBins, drBins);
            }
        }
      return 0;
    }

  if(opt=="plothist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRatio[i] = new TH1F(Form("hSignalRatio_%d",i), ";#Delta R;", nDrBins, drBins);
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
      for(int i=0;i<nPtBins;i++)
        {
          ahSignalRP[i]->Write();
          ahSignalRPHsub[i]->Write();
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRPH[l][i]->Write();
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
          ahSignalRP[i] = (TH1F*)inf->Get(Form("hSignalRP_%d",i));
          ahSignalRPHsub[i] = (TH1F*)inf->Get(Form("hSignalRPHsub_%d",i));
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRPH[l][i] = (TH1F*)inf->Get(Form("hSignalRPH_%s_%d",tRef[l].Data(),i));
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

#endif
