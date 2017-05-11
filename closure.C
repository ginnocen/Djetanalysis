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
#include "TStyle.h"
#include "TLegendEntry.h"

using namespace std;

void closure(int isPP=1){
 
   int intjetpt_cut=80;
   int intDptlow_cut=4;
   int intDpthigh_cut=999;

   TString input;

   if (isPP) input=Form("resultsPP_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
   else input=Form("resultsPbPb_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
   TFile*file=new TFile(input.Data());

   TH1F*hSignalMC[2];            
   TH1F*fhEfficiency[2];
   TH1F*fhNumEfficiency[2];
   TH1F*fhDenEfficiency[2]; 

   hSignalMC[0]=(TH1F*)file->Get("hSignalMC_indexBkg0");  



   for (int i=0;i<2;i++){
     fhNumEfficiency[i]=(TH1F*)file->Get(Form("fhNumEfficiency_%d_indexBkg0",i));
     fhDenEfficiency[i]=(TH1F*)file->Get(Form("fhDenEfficiency_%d_indexBkg0",i));
     fhEfficiency[i]=(TH1F*)file->Get(Form("fhEfficiency_%d_indexBkg0",i));
  }   


  TH1F*hGenD_RecoOverGenJets=(TH1F*)fhDenEfficiency[0]->Clone("hGenD_RecoOverGenJets");
  hGenD_RecoOverGenJets->SetName("hGenD_RecoOverGenJets");
  hGenD_RecoOverGenJets->Divide(fhDenEfficiency[1]);
  cout<<"step 3"<<endl;
  TH1F*hFitClosure=(TH1F*)hSignalMC[0]->Clone("hFitClosure");
  hFitClosure->SetName("hFitClosure");
  hFitClosure->Divide(fhNumEfficiency[0]);
  cout<<"step 4"<<endl;
  TH1F*hRecoJetDrecoOverGenJetGenD=(TH1F*)hSignalMC[0]->Clone("hRecoJetDrecoOverGenJetGenD");
  hRecoJetDrecoOverGenJetGenD->SetName("hRecoJetDrecoOverGenJetGenD");
  hRecoJetDrecoOverGenJetGenD->Divide(fhEfficiency[0]);
  hRecoJetDrecoOverGenJetGenD->Divide(fhDenEfficiency[1]);


  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
 
  gStyle->SetTitleX(.0f);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TCanvas*canvas=new TCanvas("canvas","canvas",1200,500);
  canvas->Divide(3,1);
  

  TH2F* hempty=new TH2F("hempty","",50,0,0.5,10,0.5,1.5);
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitle("#Delta R");
  hempty->GetXaxis()->SetTitleOffset(0.9);
  hempty->GetYaxis()->SetTitleOffset(1.0);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);
 
 
  TLegend *legend=new TLegend(0.2729839,0.7415254,0.616129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.04);

  TLegendEntry*entry;
  entry=legend->AddEntry(hRecoJetDrecoOverGenJetGenD,Form("pp, Jet 80 D p_{T}>%d, p_{T}<%d GeV",intDptlow_cut,intDpthigh_cut),"o");
  entry->SetTextFont(42);
  entry->SetLineColor(1);
  entry->SetMarkerColor(1);
 
  TH2F*hemp[6];
  for (int i=0;i<6;i++){
    hemp[i]=(TH2F*)hempty->Clone(Form("hemp_%d",i));
  }
 
  canvas->cd(1); 
  hemp[1]->GetYaxis()->SetTitle("Gen D, RecoJet/GenJet");
  hemp[1]->Draw();
  hGenD_RecoOverGenJets->Draw("psame");
  canvas->cd(2);
  hemp[2]->GetYaxis()->SetTitle("Fit Closure");
  hemp[2]->Draw();
  hFitClosure->Draw("psame");
  canvas->SaveAs("canvasClosurePP.pdf");
  canvas->cd(3);
  hemp[3]->GetYaxis()->SetTitle("");
  hemp[3]->Draw();
  hRecoJetDrecoOverGenJetGenD->Draw("psame");
  
 
}
