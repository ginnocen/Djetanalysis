#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/dfitter.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>

const Float_t DZERO_MASS = 1.8649;

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

TH1F* ahHistoRMass[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSignal[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSwapped[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoZMass[nRefBins][nPtBins][nZBins];
TH1F* ahHistoZMassSignal[nRefBins][nPtBins][nZBins];
TH1F* ahHistoZMassSwapped[nRefBins][nPtBins][nZBins];
    
TH1F* hNjets;
TH1F* ahREfficiency[nRefBins][nPtBins];
TH1F* ahNumREfficiency[nRefBins][nPtBins];
TH1F* ahDenREfficiency[nRefBins][nPtBins];
TH1F* ahZEfficiency[nRefBins][nPtBins];
TH1F* ahNumZEfficiency[nRefBins][nPtBins];
TH1F* ahDenZEfficiency[nRefBins][nPtBins];

TH1F* ahSignalR[nRefBins][nPtBins];
TH1F* ahSignalZ[nRefBins][nPtBins];
TH1F* ahSignalRraw[nRefBins][nPtBins];
TH1F* ahSignalZraw[nRefBins][nPtBins];
TH1F* ahSignalRnorm[nRefBins][nPtBins];
TH1F* ahSignalZnorm[nRefBins][nPtBins];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savetpl")
    {
      hNjets = new TH1F("hNjets", "", 1, 0, 1); // ... is it necessary
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              ahREfficiency[l][i] = new TH1F(Form("hREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahNumREfficiency[l][i] = new TH1F(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahDenREfficiency[l][i] = new TH1F(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahZEfficiency[l][i] = new TH1F(Form("hZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahNumZEfficiency[l][i] = new TH1F(Form("hNumZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahDenZEfficiency[l][i] = new TH1F(Form("hDenZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j] = new TH1F(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  ahHistoRMassSwapped[l][i][j] = new TH1F(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                }
              for(int j=0;j<nZBins;j++) 
                {
                  ahHistoZMassSignal[l][i][j] = new TH1F(Form("hHistoZMassSignal_%s_pt_%d_z_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  ahHistoZMassSwapped[l][i][j] = new TH1F(Form("hHistoZMassSwapped_%s_pt_%d_z_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                }
            }
        }
      return 0;
    }
  if(opt=="savehist")
    {
      hNjets = new TH1F("hNjets", "", 1, 0, 1);
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = new TH1F(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              for(int j=0;j<nZBins;j++) ahHistoZMass[l][i][j] = new TH1F(Form("hHistoZMass_%s_pt_%d_z_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              ahSignalR[l][i] = new TH1F(Form("hSignalR_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahSignalZ[l][i] = new TH1F(Form("hSignalZ_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahSignalRraw[l][i] = new TH1F(Form("hSignalRraw_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahSignalZraw[l][i] = new TH1F(Form("hSignalZraw_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahSignalRnorm[l][i] = new TH1F(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahSignalZnorm[l][i] = new TH1F(Form("hSignalZnorm_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
            }
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
      hNjets->Write(); // ... is it necessary
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              ahREfficiency[l][i]->Write();
              ahNumREfficiency[l][i]->Write();
              ahDenREfficiency[l][i]->Write();
              ahZEfficiency[l][i]->Write();
              ahNumZEfficiency[l][i]->Write();
              ahDenZEfficiency[l][i]->Write();
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j]->Write();
                  ahHistoRMassSwapped[l][i][j]->Write();
                }
              for(int j=0;j<nZBins;j++) 
                {
                  ahHistoZMassSignal[l][i][j]->Write();
                  ahHistoZMassSwapped[l][i][j]->Write();
                }
            }
        }
      return 0;
    }
  if(opt=="savehist")
    {
      hNjets->Write();
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j]->Write();
              for(int j=0;j<nZBins;j++) ahHistoZMass[l][i][j]->Write();
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              ahSignalR[l][i]->Write();
              ahSignalZ[l][i]->Write();
              ahSignalRraw[l][i]->Write();
              ahSignalZraw[l][i]->Write();
              ahSignalRnorm[l][i]->Write();
              ahSignalZnorm[l][i]->Write();
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
  if(opt=="hist")
    {
      hNjets = (TH1F*)inf->Get("hNjets");
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
              for(int j=0;j<nZBins;j++) ahHistoZMass[l][i][j] = (TH1F*)inf->Get(Form("hHistoZMass_%s_pt_%d_z_%d",tRef[l].Data(),i,j));
            }
        }
      return 0;
    }
  if(opt=="tpl")
    {
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              ahREfficiency[l][i] = (TH1F*)inf->Get(Form("hREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahDenREfficiency[l][i] = (TH1F*)inf->Get(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahNumREfficiency[l][i] = (TH1F*)inf->Get(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahDenREfficiency[l][i] = (TH1F*)inf->Get(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahZEfficiency[l][i] = (TH1F*)inf->Get(Form("hZEfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahNumZEfficiency[l][i] = (TH1F*)inf->Get(Form("hNumZEfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahDenZEfficiency[l][i] = (TH1F*)inf->Get(Form("hDenZEfficiency_%s_pt_%d",tRef[l].Data(),i));
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                  ahHistoRMassSwapped[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                }
              for(int j=0;j<nZBins;j++) 
                {
                  ahHistoZMassSignal[l][i][j] = (TH1F*)inf->Get(Form("hHistoZMassSignal_%s_pt_%d_z_%d",tRef[l].Data(),i,j));
                  ahHistoZMassSwapped[l][i][j] = (TH1F*)inf->Get(Form("hHistoZMassSwapped_%s_pt_%d_z_%d",tRef[l].Data(),i,j));
                }
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}



#endif
