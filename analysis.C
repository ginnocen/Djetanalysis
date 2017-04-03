#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include "d_jet.C"
#include "TH1F.h"
#include "TH2F.h"
#include "fitter.cc"
#include "TCanvas.h"
#include "TLegend.h"
using namespace std;

void analysis(){
  
//  djet* tData = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_merged/total.root");
//  tData->loop(1);
//  tData->d_jet("myDatatest.root");
 
//  djet* tMC = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split/merged.root");
//  tMC->loop(0,60,999.,10,10000,10000,4.06,1000,0,1000,1000,0.);
//  tMC->d_jet("myMCtest.root");


  djet* tpp = new djet("/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/merged.root");
  tpp->loop(0,60,999.,10,10000,10000,4.06,1000,0,1000,1000,0.);
  tpp->d_jet("myDataPPtest.root");

}

void runFit(TString file="myDataPPtest.root", TString fileMC="myMCtest.root", TString output="resultsPP.root"){
  
   double Redges[6]={0.,0.05,0.1,0.2,0.3,0.5};
 
   TH1F *hHistoMassMC[5];
   TH1F *hHistoMassData[5];
   TH1F* hHistoGenSignal[5];
   TH1F* hHistoGenSwapped[5];
   TH1F*hSignalData=new TH1F("hSignalData","hSignalData",5,Redges);
   TH1F*hSignalMC=new TH1F("hSignalMC","hSignalMC",5,Redges);

   TFile* finput = new TFile(file.Data());
   TFile* finputMC = new TFile(fileMC.Data());
   Dfitter *fitData[5];   
   Dfitter *fitMC[5];   


    for (int i=0;i<5;i++){
      
      hHistoMassData[i]=(TH1F*)finput->Get(Form("fhHistoMass_R%d",i));
      hHistoMassMC[i]=(TH1F*)finputMC->Get(Form("fhHistoMass_R%d",i));
      hHistoGenSignal[i]=(TH1F*)finputMC->Get(Form("fhHistoGenSignal_R%d",i));
      hHistoGenSwapped[i]=(TH1F*)finputMC->Get(Form("fhHistoGenSwapped_R%d",i));
      fitData[i]=new Dfitter(hHistoMassData[i],hHistoGenSignal[i],hHistoGenSwapped[i]);
      fitMC[i]=new Dfitter(hHistoMassMC[i],hHistoGenSignal[i],hHistoGenSwapped[i]);

    }
    for (int i=0;i<5;i++){


       hSignalData->SetBinContent(i+1,fitData[i]->GetSignal());
       hSignalData->SetBinError(i+1,fitData[i]->GetSignalError());
   
       hSignalMC->SetBinContent(i+1,fitMC[i]->GetSignal());
       hSignalMC->SetBinError(i+1,fitMC[i]->GetSignalError());
    
      cout<<"data R bin="<<fitData[i]->GetSignal()<<endl;
      cout<<"data R bin="<<fitData[i]->GetSignalError()<<endl;
      cout<<"MC R bin="<<fitMC[i]->GetSignal()<<endl;
      cout<<"MC R bin="<<fitMC[i]->GetSignalError()<<endl;

}


  hSignalData->Scale(1./hSignalData->GetBinContent(1));
  hSignalMC->Scale(1./hSignalMC->GetBinContent(1));
 
  TCanvas*canvas=new TCanvas("canvas","canvas",600,500);
  canvas->cd();
  
  TH2F* hemptyFractions=new TH2F("hemptyFractions","",50,0,0.5,10,0,1.5);  
  hemptyFractions->GetXaxis()->CenterTitle();
  hemptyFractions->GetYaxis()->CenterTitle();
  hemptyFractions->GetXaxis()->SetTitle("#Delta R");
  hemptyFractions->GetYaxis()->SetTitle("D meson yield");
  hemptyFractions->GetXaxis()->SetTitleOffset(0.9);
  hemptyFractions->GetYaxis()->SetTitleOffset(1.0);
  hemptyFractions->GetXaxis()->SetTitleSize(0.05);
  hemptyFractions->GetYaxis()->SetTitleSize(0.05);
  hemptyFractions->GetXaxis()->SetTitleFont(42);
  hemptyFractions->GetYaxis()->SetTitleFont(42);
  hemptyFractions->GetXaxis()->SetLabelFont(42);
  hemptyFractions->GetYaxis()->SetLabelFont(42);
  hemptyFractions->GetXaxis()->SetLabelSize(0.035);
  hemptyFractions->GetYaxis()->SetLabelSize(0.035);  
  hemptyFractions->Draw();

  hSignalData->SetLineColor(2);
  hSignalData->Draw("psame");
  hSignalMC->SetLineColor(1);
  hSignalMC->Draw("psame");

  TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
  legend->SetTextSize(0.04);
  legend->AddEntry(hSignalData,"Data","l");
  legend->AddEntry(hSignalMC,"Background fit","l");
  legend->Draw();


  TFile* foutput = new TFile(output.Data(),"recreate");
  hSignalData->Write();
  hSignalMC->Write();
  foutput->Close();
}
