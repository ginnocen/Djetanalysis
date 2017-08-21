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
TH1F* ahHistoRMass[nPtBins][nDrBins];
TH1F* ahHistoRMassSignal[nPtBins][nDrBins];
TH1F* ahHistoRMassSwapped[nPtBins][nDrBins];
TH1F* ahHistoZMass[nPtBins][nZBins];
TH1F* ahHistoZMassSignal[nPtBins][nZBins];
TH1F* ahHistoZMassSwapped[nPtBins][nZBins];
    
// TH1F* hNjets;
// TH1F* ahDenEfficiency[indexGenRecoEff][indexBkgReflection];
// TH1F* ahNumEfficiency[indexGenRecoEff][indexBkgReflection];
// TH1F* ahEfficiency[indexGenRecoEff][indexBkgReflection];
// TH1F* ahZDenEfficiency[indexGenRecoEff][indexBkgReflection];
// TH1F* ahZNumEfficiency[indexGenRecoEff][indexBkgReflection];
// TH1F* ahZEfficiency[indexGenRecoEff][indexBkgReflection];

void createhists()
{
  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++) ahHistoRMass[i][j] = new TH1F(Form("hHistoRMass_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      for(int j=0;j<nZBins;j++) ahHistoZMass[i][j] = new TH1F(Form("hHistoZMass_pt_%d_dr_%d",i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
    }
}
void writehists()
{
  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++) ahHistoRMass[i][j]->Write();
      for(int j=0;j<nZBins;j++) ahHistoZMass[i][j]->Write();
    }
}

#endif
