#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/xjjcuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>

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
TH1F* ahNumREfficiency[nRefBins][nPtBins];
TH1F* ahDenREfficiency[nRefBins][nPtBins];
TH1F* ahNumZEfficiency[nRefBins][nPtBins];
TH1F* ahDenZEfficiency[nRefBins][nPtBins];

void createhists_savetpl()
{
  hNjets = new TH1F("hNjets", "", 1, 0, 1);
  for(int l=0;l<nRefBins;l++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahNumREfficiency[l][i] = new TH1F(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
          ahDenREfficiency[l][i] = new TH1F(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
          ahNumZEfficiency[l][i] = new TH1F(Form("hNumZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
          ahDenZEfficiency[l][i] = new TH1F(Form("hDenZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
          for(int j=0;j<nDrBins;j++) 
            {
              ahHistoRMassSignal[l][i][j] = new TH1F(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoRMassSwapped[l][i][j] = new TH1F(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
            }
          for(int j=0;j<nZBins;j++) 
            {
              ahHistoZMassSignal[l][i][j] = new TH1F(Form("hHistoZMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              ahHistoZMassSwapped[l][i][j] = new TH1F(Form("hHistoZMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
            }
        }
    }
}
void writehists_savetpl()
{
  hNjets->Write();
  for(int l=0;l<nRefBins;l++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahNumREfficiency[l][i]->Write();
          ahDenREfficiency[l][i]->Write();
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
}

void createhists_savehist()
{
  hNjets = new TH1F("hNjets", "", 1, 0, 1);
  for(int l=0;l<nRefBins;l++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = new TH1F(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
          for(int j=0;j<nZBins;j++) ahHistoZMass[l][i][j] = new TH1F(Form("hHistoZMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
        }
    }
}
void writehists_savehist()
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
}
#endif
