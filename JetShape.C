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

void JetShape(int intDptlow_cut=6, int intDpthigh_cut=999){
 
   int intjetpt_cut=80;
   int intjetetamin_cut=0;
   int intjetetamax_cut=20;

   TString inputPP;
   TString inputPbPb;
   TString output;

   inputPP=Form("Files/resultsPP_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
   inputPbPb=Form("Files/resultsPbPb_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
   output=Form("Files/results_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
   TFile*filePP=new TFile(inputPP.Data());
   TFile*filePbPb=new TFile(inputPbPb.Data());

   TH1F*hSignalDataPP=(TH1F*)filePP->Get("hSignalData_indexBkg0");
   TH1F*hSignalDataPbPb=(TH1F*)filePbPb->Get("hSignalData_indexBkg0");          
   TH1F*fhEfficiencyPP=(TH1F*)filePP->Get("fhEfficiency_0_indexBkg0");
   TH1F*fhEfficiencyPbPb=(TH1F*)filePbPb->Get("fhEfficiency_0_indexBkg0");
   

   hSignalDataPbPb->Divide(fhEfficiencyPbPb);
   hSignalDataPP->Divide(fhEfficiencyPP);
   hSignalDataPbPb->Divide(hSignalDataPP);


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

  TCanvas*canvas=new TCanvas("canvas","canvas",600,500);
  canvas->SetLogy();
  TH2F* hempty=new TH2F("hempty","",50,0,1.,10,0.1,20.0);
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
  entry=legend->AddEntry(hSignalDataPbPb,Form("pp, Jet 80 D p_{T}>%d, p_{T}<%d GeV",intDptlow_cut,intDpthigh_cut),"o");
  entry->SetTextFont(42);
  entry->SetLineColor(1);
  entry->SetMarkerColor(1);
 
 
  canvas->cd(); 
  hempty->GetYaxis()->SetTitle("PbPb/pp");
  hempty->Draw();
  hSignalDataPbPb->Draw("psame");
  TFile *foutput=new TFile(output.Data(),"recreate");
  hSignalDataPbPb->SetName("hJetShape");
  hSignalDataPbPb->Write();
  foutput->Close(); 
}




void FF(){
 
   int intjetpt_cut=80;
   int intDptlow_cut=6;
   int intDpthigh_cut=999;
   int intjetetamin_cut=0;
   int intjetetamax_cut=20;

   TString inputPP;
   TString inputPbPb;


   inputPP=Form("Files/resultsPP_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
   inputPbPb=Form("Files/resultsPbPb_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
   TFile*filePP=new TFile(inputPP.Data());
   TFile*filePbPb=new TFile(inputPbPb.Data());

   TH1F*hSignalDataPP=(TH1F*)filePP->Get("hSignalZData_indexBkg0");
   TH1F*hSignalDataPbPb=(TH1F*)filePbPb->Get("hSignalZData_indexBkg0");          
   TH1F*fhEfficiencyPP=(TH1F*)filePP->Get("fhZEfficiency_0_indexBkg0");
   TH1F*fhEfficiencyPbPb=(TH1F*)filePbPb->Get("fhZEfficiency_0_indexBkg0");
   

   hSignalDataPbPb->Divide(fhEfficiencyPbPb);
   hSignalDataPP->Divide(fhEfficiencyPP);
   hSignalDataPbPb->Divide(hSignalDataPP);


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

  TCanvas*canvas=new TCanvas("canvas","canvas",600,500);
  canvas->SetLogy();
  TH2F* hempty=new TH2F("hempty","",50,0,1.,10,0.1,20.0);
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
  entry=legend->AddEntry(hSignalDataPbPb,Form("pp, Jet 80 D p_{T}>%d, p_{T}<%d GeV",intDptlow_cut,intDpthigh_cut),"o");
  entry->SetTextFont(42);
  entry->SetLineColor(1);
  entry->SetMarkerColor(1);
 
 
  canvas->cd(); 
  hempty->GetYaxis()->SetTitle("PbPb/pp");
  hempty->Draw();
  hSignalDataPbPb->Draw("psame"); 
}
