#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include "TH1F.h"
#include "d_jet.C"
#include "fitter.cc"
#include "TCanvas.h"
using namespace std;

void analysis(){
  
  djet* t = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_merged/total.root");
  t->loop(1);
 
  djet* tMC = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split/merged.root");
  tMC->loop(0);

  TFile*foutput=new TFile("output.root","recreate");
  foutput->cd();

  TH1F*hAllOutConeMC=(TH1F*)tMC->GetHisto(1,0);
  TH1F*hAllOutConeMatchMC=(TH1F*)tMC->GetHisto(1,1);
  TH1F*hAllOutConeSwappedMC=(TH1F*)tMC->GetHisto(1,2);
  TH1F*hAllInConeMC=(TH1F*)tMC->GetHisto(0,0);
  TH1F*hAllInConeMatchMC=(TH1F*)tMC->GetHisto(0,1);
  TH1F*hAllInConeSwappedMC=(TH1F*)tMC->GetHisto(0,2);
  TH1F*hAllInConeData=(TH1F*)t->GetHisto(0,0);
  TH1F*hAllOutConeData=(TH1F*)t->GetHisto(1,0);
  
  hAllOutConeMC->SetName("hAllOutConeMC");
  hAllOutConeMatchMC->SetName("hAllOutConeMatchMC");
  hAllOutConeSwappedMC->SetName("hAllOutConeSwappedMC");
  hAllInConeMC->SetName("hAllInConeMC");
  hAllInConeMatchMC->SetName("hAllInConeMatchMC");
  hAllInConeSwappedMC->SetName("hAllInConeSwappedMC");
  hAllInConeData->SetName("hAllInConeData");
  hAllOutConeData->SetName("hAllOutConeData");
   
}
void doFit(){


  TFile*foutput=new TFile("output.root","read");
  foutput->cd();

  TH1F*hAllOutConeMC=(TH1F*)foutput->Get("hAllOutConeMC");
  TH1F*hAllOutConeMatchMC=(TH1F*)foutput->Get("hAllOutConeMatchMC");
  TH1F*hAllOutConeSwappedMC=(TH1F*)foutput->Get("hAllOutConeSwappedMC");
  TH1F*hAllInConeMC=(TH1F*)foutput->Get("hAllInConeMC");
  TH1F*hAllInConeMatchMC=(TH1F*)foutput->Get("hAllInConeMatchMC");
  TH1F*hAllInConeSwappedMC=(TH1F*)foutput->Get("hAllInConeSwappedMC");
  TH1F*hAllInConeData=(TH1F*)foutput->Get("hAllInConeData");
  TH1F*hAllOutConeData=(TH1F*)foutput->Get("hAllOutConeData");

  Dfitter*dfitInCone=new Dfitter(hAllInConeData,hAllInConeMatchMC,hAllInConeSwappedMC);
  Dfitter*dfitOutCone=new Dfitter(hAllOutConeData,hAllOutConeMatchMC,hAllOutConeSwappedMC);
  dfitInCone->fit();
  //dfitOutCone->fit();
}
