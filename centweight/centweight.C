#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCut.h>
#include <TF1.h>

TString str_fcentweight = "TMath::Exp(1.73189e+00-1.95674e-02*x-3.23682e-04*x*x+3.25107e-06*x*x*x-1.21428e-08*x*x*x*x)";

void getcentweight()
{
  TF1* fcentweight = new TF1("fcentweight", str_fcentweight.Data(), 0, 200);
  TFile* infdata = new TFile("/export/d00/scratch/jwang/Djets/data/DjetFiles_20180411_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLT6080100_jetpt50_mix10_skimbranch.root", "");
  TTree* ntdata = (TTree*)infdata->Get("djt");
  TTree* nthltdata = (TTree*)infdata->Get("hlt");
  TFile* infmc = new TFile("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20180406_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20180326_pthatweight.root", "");
  TTree* ntmc = (TTree*)infmc->Get("djt");
  TTree* nthltmc = (TTree*)infmc->Get("hlt");

  TH1F* hdata = new TH1F("hdata", "", 200, 0, 200);
  hdata->Sumw2();
  TH1F* hdataHLT[3];
  for(int i=0;i<3;i++) { hdataHLT[i] = new TH1F(Form("hdataHLT_%d",i), "", 200, 0, 200); hdataHLT[i]->Sumw2(); }
  TH1F* hmc = new TH1F("hmc", "", 200, 0, 200);
  hmc->Sumw2();
  TH1F* hmcHLT[3];
  for(int i=0;i<3;i++) { hmcHLT[i] = new TH1F(Form("hmcHLT_%d",i), "", 200, 0, 200); hmcHLT[i]->Sumw2(); }
  TH1F* hmcweight = new TH1F("hmcweight", "", 200, 0, 200);

  ntmc->SetBranchStatus("*", 0);
  ntmc->SetBranchStatus("hiBin", 1);
  ntmc->SetBranchStatus("pthatweight", 1);
  nthltmc->SetBranchStatus("HLT_HIPuAK4CaloJet40_Eta5p1_v2", 1);
  nthltmc->SetBranchStatus("HLT_HIPuAK4CaloJet60_Eta5p1_v2", 1);
  nthltmc->SetBranchStatus("HLT_HIPuAK4CaloJet80_Eta5p1_v2", 1);
  nthltmc->SetBranchStatus("HLT_HIPuAK4CaloJet100_Eta5p1_v2", 1);
  Int_t mchiBin = 0; ntmc->SetBranchAddress("hiBin", &mchiBin);
  Float_t pthatweight = 0; ntmc->SetBranchAddress("pthatweight", &pthatweight);
  Int_t HLT_AK4Jet40_MC; nthltmc->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_v2", &HLT_AK4Jet40_MC);
  Int_t HLT_AK4Jet60_MC; nthltmc->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_v2", &HLT_AK4Jet60_MC);
  Int_t HLT_AK4Jet80_MC; nthltmc->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_v2", &HLT_AK4Jet80_MC);
  Int_t HLT_AK4Jet100_MC; nthltmc->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_v2", &HLT_AK4Jet100_MC);

  ntdata->SetBranchStatus("*", 0);
  ntdata->SetBranchStatus("hiBin", 1);
  nthltdata->SetBranchStatus("HLT_HIPuAK4CaloJet40_Eta5p1_v1", 1);
  nthltdata->SetBranchStatus("HLT_HIPuAK4CaloJet60_Eta5p1_v1", 1);
  nthltdata->SetBranchStatus("HLT_HIPuAK4CaloJet80_Eta5p1_v1", 1);
  nthltdata->SetBranchStatus("HLT_HIPuAK4CaloJet100_Eta5p1_v1", 1);
  Int_t datahiBin = 0; ntdata->SetBranchAddress("hiBin", &datahiBin);
  Int_t HLT_AK4Jet40_DATA; nthltdata->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_v1", &HLT_AK4Jet40_DATA);
  Int_t HLT_AK4Jet60_DATA; nthltdata->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_v1", &HLT_AK4Jet60_DATA);
  Int_t HLT_AK4Jet80_DATA; nthltdata->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_v1", &HLT_AK4Jet80_DATA);
  Int_t HLT_AK4Jet100_DATA; nthltdata->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_v1", &HLT_AK4Jet100_DATA);

  for(int i=0;i<ntmc->GetEntries();i++)
    {
      ntmc->GetEntry(i);
      nthltmc->GetEntry(i);
      if(HLT_AK4Jet60_MC) { hmcHLT[0]->Fill(mchiBin, pthatweight); }
      if(HLT_AK4Jet80_MC) { hmcHLT[1]->Fill(mchiBin, pthatweight); }
      if(HLT_AK4Jet100_MC) { hmcHLT[2]->Fill(mchiBin, pthatweight); }
      hmc->Fill(mchiBin, pthatweight);
      hmcweight->Fill(mchiBin, pthatweight * fcentweight->Eval(mchiBin));
    }
  for(int i=0;i<ntdata->GetEntries();i++)
    {
      ntdata->GetEntry(i);
      nthltdata->GetEntry(i);
      if(HLT_AK4Jet60_DATA) { hdataHLT[0]->Fill(datahiBin); }
      if(HLT_AK4Jet80_DATA) { hdataHLT[1]->Fill(datahiBin); }
      if(HLT_AK4Jet100_DATA) { hdataHLT[2]->Fill(datahiBin); }

      if(!HLT_AK4Jet60_DATA) continue;
      hdata->Fill(datahiBin);
    }

  hdata->Scale(1./hdata->Integral());
  for(int i=0;i<3;i++) { hdataHLT[i]->Scale(1./hdataHLT[i]->Integral()); }
  hmc->Scale(1./hmc->Integral());
  for(int i=0;i<3;i++) { hmcHLT[i]->Scale(1./hmcHLT[i]->Integral()); }
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
  for(int i=0;i<3;i++) { hdataHLT[i]->Write(); }
  hmc->Write();
  for(int i=0;i<3;i++) { hmcHLT[i]->Write(); }
  hmcweight->Write();
  hratio->Write();
  hratioweight->Write();
  outf->Close();
}

int main()
{
  getcentweight();
  return 0;
}
