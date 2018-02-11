#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>

Float_t uncert_scale = 0.02;
Float_t uncert_reso = 0.15;

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

const int nScale = 2;
TString nameScale[nScale] = {"ScaleP", "ScaleM"};
TString legScale[nScale] = {"increase scale", "decrease scale"};
const int nReso = 1;
TString nameReso[nReso] = {"15per"};
TString legReso[nReso] = {"data-MC diff"};

Color_t colorlist[] = {kGreen-5, kRed-9, kAzure-4, kViolet-9, kOrange-9};

TH1F* hNjets;

// TH1F* ahSignalRraw[nRefBins][nPtBins];
// TH1F* ahSignalR[nRefBins][nPtBins];
TH1F* ahSignalRnorm[nRefBins][nPtBins];
TH1F* ahSignalRnormScale[nRefBins][nPtBins][nScale];
TH1F* ahSignalRnormReso[nRefBins][nPtBins][nReso];
TH1F* ahSignalRsub[nPtBins];
TH1F* ahSignalRsubScale[nPtBins][nScale];
TH1F* ahSignalRsubReso[nPtBins][nReso];

TH1F* ahDevRnormScale[nRefBins][nPtBins][nScale];
TH1F* ahDevRsubScale[nPtBins][nScale];
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
              for(int v=0;v<nScale;v++)
                ahDevRnormScale[l][i][v] = new TH1F(Form("hDevRnormScale_%s_%s_pt_%d",nameScale[v].Data(),tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              for(int v=0;v<nReso;v++)
                ahDevRnormReso[l][i][v] = new TH1F(Form("hDevRnormReso_%s_%s_pt_%d",nameReso[v].Data(),tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
            }
          for(int v=0;v<nScale;v++)
            ahDevRsubScale[i][v] = new TH1F(Form("hDevRsubScale_%s_pt_%d",nameScale[v].Data(),i), ";#DeltaR;", nDrBins, drBins);
          for(int v=0;v<nReso;v++)
            ahDevRsubReso[i][v] = new TH1F(Form("hDevRsubReso_%s_pt_%d",nameReso[v].Data(),i), ";#DeltaR;", nDrBins, drBins);
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

  // if(opt.Contains("usehist"))
  //   {
  //     for(int i=0;i<nPtBins;i++)
  //       {
  //         for(int l=0;l<nRefBins;l++)
  //           {
  //             ahSignalRraw[l][i]->Write();
  //             ahSignalZraw[l][i]->Write();
  //             ahSignalR[l][i]->Write();
  //             ahSignalZ[l][i]->Write();
  //             ahSignalRnorm[l][i]->Write();
  //             ahSignalZnorm[l][i]->Write();
  //           }
  //         ahSignalRsub[i]->Write();
  //         ahSignalZsub[i]->Write();
  //       }
  //     return 0;
  //   }
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
          ahSignalRsub[i] = (TH1F*)inf[0]->Get(Form("hSignalRsub_pt_%d",i));
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
                }
              ahSignalRsubScale[i][v] = (TH1F*)inf[v]->Get(Form("hSignalRsub_pt_%d",i));
              ahSignalRsubScale[i][v]->SetName(Form("hSignalRsub_%s_pt_%d",nameScale[v].Data(),i));              
            }
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
                }
              ahSignalRsubReso[i][v] = (TH1F*)inf[v]->Get(Form("hSignalRsub_pt_%d",i));
              ahSignalRsubReso[i][v]->SetName(Form("hSignalRsub_%s_pt_%d",nameReso[v].Data(),i));              
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}



#endif
