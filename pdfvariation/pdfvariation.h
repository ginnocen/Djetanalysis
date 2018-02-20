#ifndef _PDFVARIATION_H_
#define _PDFVARIATION_H_


#include "../includes/prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "dfitter_variation.h"

#include <TH2F.h>
#include <TH1F.h>
#include <TFile.h>
#include <TColor.h>

const Float_t DZERO_MASS = 1.8649;

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

const int nVariation = 6;
TString fitopt[nVariation] = {"", "3", "WP", "WM", "EPO", "2PO"};
TString fitname[nVariation] = {"Default", "3", "WP", "WM", "EXP", "2PO"};
TString fitleg[nVariation] = {"Default","3 Gaus", "Increase wid", "Decrease wid", "Exponential", "2nd ord pol"};
Color_t fitcolor[nVariation] = {kGray+3, kOrange-9, kGreen-5, kRed-9, kAzure-4, kViolet-9};

TH1F* ahHistoRMass[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSignal[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSwapped[nRefBins][nPtBins][nDrBins];

TH1F* ahSignalRraw[nRefBins][nPtBins][nVariation];
TH1F* ahSignalRdev[nRefBins][nPtBins][nVariation];

int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="usehist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int v=0;v<nVariation;v++)
                {
                  ahSignalRraw[l][i][v] = new TH1F(Form("hSignalRraw_%s_pt_%d_%s",tRef[l].Data(),i,fitname[v].Data()), ";#DeltaR;", nDrBins, drBins);
                  ahSignalRdev[l][i][v] = new TH1F(Form("hSignalRdev_%s_pt_%d_%s",tRef[l].Data(),i,fitname[v].Data()), ";#DeltaR;", nDrBins, drBins);
                }
            }
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
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
            }
        }
      return 0;
    }
  if(opt=="tpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++)
                {
                  ahHistoRMassSignal[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                  ahHistoRMassSwapped[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                }
            }
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int v=0;v<nVariation;v++)
                {
                  ahSignalRdev[l][i][v] = (TH1F*)inf->Get(Form("hSignalRdev_%s_pt_%d_%s",tRef[l].Data(),i,fitname[v].Data()));
                }
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
  if(opt=="usehist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int v=0;v<nVariation;v++)
                {
                  ahSignalRraw[l][i][v]->Write();
                  ahSignalRdev[l][i][v]->Write();
                }
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
