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

void analysis(double jetpt_cut=80.,double Dptlow_cut=10.){
  

  double jeteta_cut=1.6;
  double Dpthigh_cut=1000.;
  double Dy_cut=2.0;
  double decaylength_cut=4.06;
  double Dalpha_cut=0.12;
  double trkptmin_cut=2.0;
  double trketa_cut=2.0;
  double trkpterr_cut=0.3;
  double chi2cl_cut=0.1;
  
  int intjetpt_cut=(int)(jetpt_cut);
  int intDptlow_cut=(int)(Dptlow_cut);
/*
  djet* tData = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1/merged_total.root");
  tData->loop(1,jetpt_cut,jeteta_cut,Dptlow_cut,Dpthigh_cut,Dy_cut,decaylength_cut,Dalpha_cut,trkptmin_cut,trketa_cut,trkpterr_cut,chi2cl_cut);
  tData->d_jet(Form("myDataPbPbtest_jet%d_D%d",intjetpt_cut,intDptlow_cut));
 
  djet* tMC = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split_finalmerge_2April_v1/merged.root");
  tMC->loop(0,jetpt_cut,jeteta_cut,Dptlow_cut,Dpthigh_cut,Dy_cut,decaylength_cut,Dalpha_cut,trkptmin_cut,trketa_cut,trkpterr_cut,chi2cl_cut);
  tMC->d_jet(Form("myMCPbPbtest_jet%d_D%d",intjetpt_cut,intDptlow_cut));

  djet* tpp = new djet("/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/merged.root");
  tpp->loop(1,jetpt_cut,jeteta_cut,Dptlow_cut,Dpthigh_cut,Dy_cut,decaylength_cut,Dalpha_cut,trkptmin_cut,trketa_cut,trkpterr_cut,chi2cl_cut);
  tpp->d_jet(Form("myDataPPtest_jet%d_D%d",intjetpt_cut,intDptlow_cut));
*/
  void runFit(int,int,int);
  void comparePP_PbPb(int,int);
  runFit(1,intjetpt_cut,intDptlow_cut);
  runFit(0,intjetpt_cut,intDptlow_cut);
  comparePP_PbPb(intjetpt_cut,intDptlow_cut);

}

void runFit(int isPP=1,int intjetpt_cut=80, int intDptlow_cut=10){
 
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

 
   TString file,fileMC,output;

   if(isPP){
     file=Form("myDataPPtest_jet%d_D%d.root",intjetpt_cut,intDptlow_cut);
     fileMC=Form("myMCPbPbtest_jet%d_D%d.root",intjetpt_cut,intDptlow_cut);
     output=Form("resultsPP_jet%d_D%d.root",intjetpt_cut,intDptlow_cut);
   }
   
   if(!isPP){
     file=Form("myDataPbPbtest_jet%d_D%d.root",intjetpt_cut,intDptlow_cut);
     fileMC=Form("myMCPbPbtest_jet%d_D%d.root",intjetpt_cut,intDptlow_cut);
     output=Form("resultsPbPb_jet%d_D%d.root",intjetpt_cut,intDptlow_cut);
   }

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
 

  TCanvas*canvas=new TCanvas("canvas","canvas",500,500);
  canvas->cd();
  canvas->SetLogy();

  TH2F* hemptyFractions=new TH2F("hemptyFractions","",50,0,0.5,10,0.0001,50);  
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
  hSignalData->SetMarkerColor(2);
  hSignalData->Draw("psame");
  hSignalMC->SetLineColor(1);
  hSignalMC->SetMarkerColor(1);
  hSignalMC->Draw("psame");


  TLegend *legend=new TLegend(0.3729839,0.7415254,0.7016129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.04);

  TLegendEntry*entry;
  if(isPP){
  entry=legend->AddEntry(hSignalMC,"MC Hydjet+Pythia 5 TeV","f");
  entry->SetTextFont(42);
  entry->SetLineColor(1);
  entry->SetMarkerColor(1);
  entry=legend->AddEntry(hSignalData,"pp data 5 TeV","f");
  entry->SetTextFont(42);
  entry->SetLineColor(2);
  entry->SetMarkerColor(2);  
  legend->Draw();
  }
  else{
  entry=legend->AddEntry(hSignalMC,"MC Hydjet+Pythia 5 TeV","f");
  entry->SetTextFont(42);
  entry->SetLineColor(1);
  entry->SetMarkerColor(1);
  entry=legend->AddEntry(hSignalData,"PbPb data 5 TeV","f");
  entry->SetTextFont(42);
  entry->SetLineColor(2);
  entry->SetMarkerColor(2);
  legend->Draw();
  }
  if(isPP) canvas->SaveAs("canvasPP_dataMC.pdf");
  else canvas->SaveAs("canvasPbPb_dataMC.pdf");

  TFile* foutput = new TFile(output.Data(),"recreate");
  hSignalData->Write();
  hSignalMC->Write();
  foutput->Close();
}



void comparePP_PbPb(int intjetpt_cut=80, int intDptlow_cut=10){


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

   TFile* finputPP = new TFile(Form("resultsPP_jet%d_D%d.root",intjetpt_cut,intDptlow_cut));
   TFile* finputPbPb = new TFile(Form("resultsPbPb_jet%d_D%d.root",intjetpt_cut,intDptlow_cut));
   
   TH1F*hSignalDataPbPb=(TH1F*)finputPbPb->Get("hSignalData");
   TH1F*hSignalDataPP=(TH1F*)finputPP->Get("hSignalData");


   TCanvas*canvas=new TCanvas("canvas","canvas",500,500);
   canvas->cd();
   canvas->SetLogy();

   TH2F* hemptyFractions=new TH2F("hemptyFractions","",50,0,0.5,10,0.0001,50);
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

   hSignalDataPbPb->SetLineColor(2);
   hSignalDataPbPb->SetMarkerColor(2);
   hSignalDataPbPb->Draw("psame");
   hSignalDataPP->SetLineColor(1);
   hSignalDataPP->SetMarkerColor(1);
   hSignalDataPP->Draw("psame");

   TLegend *legend=new TLegend(0.3729839,0.7415254,0.7016129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
   legend->SetBorderSize(0);
   legend->SetLineColor(0);
   legend->SetFillColor(0);
   legend->SetFillStyle(1001);
   legend->SetTextFont(42);
   legend->SetTextSize(0.04);

   TLegendEntry*entry;
   entry=legend->AddEntry(hSignalDataPbPb,"PbPb data 5 TeV","f");
   entry->SetTextFont(42);
   entry->SetLineColor(2);
   entry->SetMarkerColor(2);
   entry=legend->AddEntry(hSignalDataPP,"pp data 5 TeV","f");
   entry->SetTextFont(42);
   entry->SetLineColor(1);
   entry->SetMarkerColor(1);
   legend->Draw();

   canvas->SaveAs("canvasPP_PbPb.pdf");

}
