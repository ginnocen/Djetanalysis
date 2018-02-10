#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCut.h>
#include "centweight_h.h"

void getcentweight()
{
  TFile* infdata = new TFile("/export/d00/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080.root", "");
  TTree* ntdata = (TTree*)infdata->Get("djt");
  TFile* infmc = new TFile("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20171215_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20171214_pthatweight.root", "");
  TTree* ntmc = (TTree*)infmc->Get("djt");

  TH1F* hdata = new TH1F("hdata", "", 200, 0, 200);
  TH1F* hmc = new TH1F("hmc", "", 200, 0, 200);
  TH1F* hmcweight = new TH1F("hmcweight", "", 200, 0, 200);

  ntmc->SetBranchStatus("*", 0);
  ntmc->SetBranchStatus("hiBin", 1);
  ntmc->SetBranchStatus("pthatweight", 1);
  Int_t mchiBin = 0;
  ntmc->SetBranchAddress("hiBin", &mchiBin);
  Float_t pthatweight = 0;
  ntmc->SetBranchAddress("pthatweight", &pthatweight);
  ntdata->SetBranchStatus("*", 0);
  ntdata->SetBranchStatus("hiBin", 1);
  Int_t datahiBin = 0;
  ntdata->SetBranchAddress("hiBin", &datahiBin);

  for(int i=0;i<ntmc->GetEntries();i++)
    {
      ntmc->GetEntry(i);
      if(mchiBin==195) continue;
      hmc->Fill(mchiBin, pthatweight);
      hmcweight->Fill(mchiBin, pthatweight * centweight[mchiBin]);
    }
  for(int i=0;i<ntdata->GetEntries();i++)
    {
      ntdata->GetEntry(i);
      hdata->Fill(datahiBin);
    }
  hdata->Sumw2();

  hdata->Scale(1./hdata->Integral());
  hmc->Scale(1./hmc->Integral());
  hmcweight->Scale(1./hmcweight->Integral());

  TH1F* hratio = (TH1F*)hdata->Clone("hratio");
  hratio->Divide(hmc);
  TH1F* hratioweight = (TH1F*)hdata->Clone("hratioweight");
  hratioweight->Divide(hmcweight);
  
  std::ofstream fweight("centweight.h");
  fweight<<"Float_t centweight[200] = {";
  for(int i=0;i<200;i++)
    fweight<<hratio->GetBinContent(i+1)<<(i!=199?", ":"};");
  fweight<<std::endl;

  TFile* outf = new TFile("outf/weight.root", "recreate");
  outf->cd();
  hdata->Write();
  hmc->Write();
  hmcweight->Write();
  hratio->Write();
  hratioweight->Write();
  outf->Close();


  // fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet40_Eta5p1_v2":"HLT_HIPuAK4CaloJet40_Eta5p1_v1", 1);
  // fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet60_Eta5p1_v2":"HLT_HIPuAK4CaloJet60_Eta5p1_v1", 1);
  // fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet80_Eta5p1_v2":"HLT_HIPuAK4CaloJet80_Eta5p1_v1", 1);
  // fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet40_Eta5p1_v2":"HLT_HIPuAK4CaloJet40_Eta5p1_v1", &HLT_AK4Jet40);
  // fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet60_Eta5p1_v2":"HLT_HIPuAK4CaloJet60_Eta5p1_v1", &HLT_AK4Jet60);
  // fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet80_Eta5p1_v2":"HLT_HIPuAK4CaloJet80_Eta5p1_v1", &HLT_AK4Jet80);
}

int main()
{
  getcentweight();
  return 0;
}
