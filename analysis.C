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

void analysis(double jetpt_cut=80.,double Dptlow_cut=4.,double Dpthigh_cut=10.){

  double jeteta_cut=1.6;
  double Dy_cut=2.0;
  double decaylength_cut=4.06;
  double Dalpha_cut=0.12;
  double trkptmin_cut=2.0;
  double trketa_cut=2.0;
  double trkpterr_cut=0.3;
  double chi2cl_cut=0.1;
  
  int intjetpt_cut=(int)(jetpt_cut);
  int intDptlow_cut=(int)(Dptlow_cut);
  int intDpthigh_cut=(int)(Dpthigh_cut);  
/*
  djet* tData = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1/merged_total.root");
  tData->SetJetPtCutEta(jetpt_cut,jeteta_cut);
  tData->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
  tData->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut);
  tData->loop(1);
  tData->d_jet(Form("myDataPbPbtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
  
  djet* tMC = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split_finalmerge_2April_v1/merged.root");
  tMC->SetJetPtCutEta(jetpt_cut,jeteta_cut);
  tMC->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
  tMC->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut);
  tMC->loop(0);
  tMC->d_jet(Form("myMCPbPbtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
*/  
  djet* tpp = new djet("/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/merged.root");
  tpp->SetJetPtCutEta(jetpt_cut,jeteta_cut);
  tpp->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
  tpp->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut);
  tpp->loop(1);
  tpp->d_jet(Form("myDataPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));

  djet* tMCpp = new djet("/export/d00/scratch/jwang/Djets/DjetFiles_pp_5TeV_TuneCUETP8M1_Dfinder_MC_pthat30_20170404.root");
  tMCpp->SetJetPtCutEta(jetpt_cut,jeteta_cut);
  tMCpp->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
  tMCpp->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut); 
  tMCpp->loop(0);
  tMCpp->d_jet(Form("myMCPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
 
  void runFit(int,int,int,int);
  void comparePP_PbPb(int,int,int);
  runFit(1,intjetpt_cut,intDptlow_cut,intDpthigh_cut);
  //runFit(0,intjetpt_cut,intDptlow_cut,intDpthigh_cut);
  //comparePP_PbPb(intjetpt_cut,intDptlow_cut,intDpthigh_cut);
}

void runFit(int isPP=1,int intjetpt_cut=80, int intDptlow_cut=-9999,int intDpthigh_cut=-9999){

   djet* tempty = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1/merged_total.root");
   const int nedgesR=tempty->GetnRedges();
   double Redges[nedgesR+1];
   for (int m=0;m<nedgesR+1;m++) Redges[m]=tempty->GetRedgesEdges(m);

   const int nedgesZ=tempty->GetnZedges();
   double Zedges[nedgesZ+1];
   for (int m=0;m<nedgesZ+1;m++) Zedges[m]=tempty->GetZedgesEdges(m);

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
     file=Form("myDataPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     fileMC=Form("myMCPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     output=Form("resultsPP_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
   }
   
   if(!isPP){
     file=Form("myDataPbPbtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     fileMC=Form("myMCPbPbtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     output=Form("resultsPbPb_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
   }
 
   TH1F *hHistoMassMC[nedgesR];
   TH1F *hHistoMassData[nedgesR];
   TH1F* hHistoGenSignal[nedgesR];
   TH1F* hHistoGenSwapped[nedgesR];

   TH1F *hHistoZMassMC[nedgesZ];
   TH1F *hHistoZMassData[nedgesZ];
   TH1F* hHistoZGenSignal[nedgesZ];
   TH1F* hHistoZGenSwapped[nedgesZ];


   TH1F*hSignalData=new TH1F("hSignalData","hSignalData",nedgesR,Redges);
   TH1F*hSignalMC=new TH1F("hSignalMC","hSignalMC",nedgesR,Redges);
   TH1F*hZSignalData=new TH1F("hZSignalData","hZSignalData",nedgesZ,Zedges);
   TH1F*hZSignalMC=new TH1F("hZSignalMC","hZSignalMC",nedgesZ,Zedges);

   TFile* finput = new TFile(file.Data());
   TFile* finputMC = new TFile(fileMC.Data());
   Dfitter *fitData[nedgesR];   
   Dfitter *fitMC[nedgesR];   
   Dfitter *fitZData[nedgesZ];
   Dfitter *fitZMC[nedgesZ];

 
  //int isPP=1,int intjetpt_cut=80, int intDptlow_cut=10  
   TString canvasData;
   TString canvasMC;

    for (int i=0;i<nedgesR;i++){
      //jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
      canvasData=Form("ResultsDataJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Rindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);
      canvasMC=Form("ResultsMCJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Rindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);

      hHistoMassData[i]=(TH1F*)finput->Get(Form("fhHistoMass_R%d",i));
      hHistoMassMC[i]=(TH1F*)finputMC->Get(Form("fhHistoMass_R%d",i));
      hHistoGenSignal[i]=(TH1F*)finputMC->Get(Form("fhHistoGenSignal_R%d",i));
      hHistoGenSwapped[i]=(TH1F*)finputMC->Get(Form("fhHistoGenSwapped_R%d",i));
      fitData[i]=new Dfitter(hHistoMassData[i],hHistoGenSignal[i],hHistoGenSwapped[i],canvasData);
      fitMC[i]=new Dfitter(hHistoMassMC[i],hHistoGenSignal[i],hHistoGenSwapped[i],canvasMC);

    }
    for (int i=0;i<nedgesR;i++){

       hSignalData->SetBinContent(i+1,fitData[i]->GetSignal());
       hSignalData->SetBinError(i+1,fitData[i]->GetSignalError());
       hSignalMC->SetBinContent(i+1,fitMC[i]->GetSignal());
       hSignalMC->SetBinError(i+1,fitMC[i]->GetSignalError());
}

   TString canvasZData;
   TString canvasZMC;

    for (int i=0;i<nedgesZ;i++){

      canvasZData=Form("ResultsZDataJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Zindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);
      canvasZMC=Form("ResultsZMCJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Zindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);

      hHistoZMassData[i]=(TH1F*)finput->Get(Form("fhHistoZMass_Z%d",i));
      hHistoZMassMC[i]=(TH1F*)finputMC->Get(Form("fhHistoZMass_Z%d",i));
      hHistoZGenSignal[i]=(TH1F*)finputMC->Get(Form("fhHistoZGenSignal_Z%d",i));
      hHistoZGenSwapped[i]=(TH1F*)finputMC->Get(Form("fhHistoZGenSwapped_Z%d",i));
      fitZData[i]=new Dfitter(hHistoZMassData[i],hHistoZGenSignal[i],hHistoZGenSwapped[i],canvasZData);
      fitZMC[i]=new Dfitter(hHistoZMassMC[i],hHistoZGenSignal[i],hHistoZGenSwapped[i],canvasZMC);

    }
    for (int i=0;i<nedgesZ;i++){

       hZSignalData->SetBinContent(i+1,fitZData[i]->GetSignal());
       hZSignalData->SetBinError(i+1,fitZData[i]->GetSignalError());
       hZSignalMC->SetBinContent(i+1,fitZMC[i]->GetSignal());
       hZSignalMC->SetBinError(i+1,fitZMC[i]->GetSignalError());
}

  hSignalData->Scale(1./hSignalData->GetBinContent(1));
  hSignalMC->Scale(1./hSignalMC->GetBinContent(1));
 
  cout<<"number of entries Data"<<hZSignalData->GetEntries()<<endl;
  cout<<"number of entries MC"<<hZSignalMC->GetEntries()<<endl;
  int countMCZ=0;
  int countDataZ=0;

  for (int i=0;i<nedgesZ;i++){
    countMCZ=countMCZ+hZSignalMC->GetBinContent(i);
    countDataZ=countDataZ+hZSignalData->GetBinContent(i);
  }
 
  hZSignalData->Scale(1./(double)countDataZ);
  hZSignalMC->Scale(1./(double)countMCZ);
 

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


  TCanvas*canvasZ=new TCanvas("canvasZ","canvasZ",500,500);
  canvasZ->cd();
  canvasZ->SetLogy();

  TH2F* hemptyFractionsZ=new TH2F("hemptyFractionsZ","",50,0,1.0,10,0.0001,50);  
  hemptyFractionsZ->GetXaxis()->CenterTitle();
  hemptyFractionsZ->GetYaxis()->CenterTitle();
  hemptyFractionsZ->GetXaxis()->SetTitle("z=p_{T}(D)/p_{T}(Jet)");
  hemptyFractionsZ->GetYaxis()->SetTitle("D meson yield");
  hemptyFractionsZ->GetXaxis()->SetTitleOffset(0.9);
  hemptyFractionsZ->GetYaxis()->SetTitleOffset(1.0);
  hemptyFractionsZ->GetXaxis()->SetTitleSize(0.05);
  hemptyFractionsZ->GetYaxis()->SetTitleSize(0.05);
  hemptyFractionsZ->GetXaxis()->SetTitleFont(42);
  hemptyFractionsZ->GetYaxis()->SetTitleFont(42);
  hemptyFractionsZ->GetXaxis()->SetLabelFont(42);
  hemptyFractionsZ->GetYaxis()->SetLabelFont(42);
  hemptyFractionsZ->GetXaxis()->SetLabelSize(0.035);
  hemptyFractionsZ->GetYaxis()->SetLabelSize(0.035);  
  hemptyFractionsZ->Draw();

  hZSignalData->SetLineColor(2);
  hZSignalData->SetMarkerColor(2);
  hZSignalData->Draw("psame");
  hZSignalMC->SetLineColor(1);
  hZSignalMC->SetMarkerColor(1);
  hZSignalMC->Draw("psame");


  TLegend *legendZ=new TLegend(0.3729839,0.7415254,0.7016129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendZ->SetBorderSize(0);
  legendZ->SetLineColor(0);
  legendZ->SetFillColor(0);
  legendZ->SetFillStyle(1001);
  legendZ->SetTextFont(42);
  legendZ->SetTextSize(0.04);

  TLegendEntry*entryZ;
  if(isPP){
  entryZ=legendZ->AddEntry(hZSignalMC,"MC Hydjet+Pythia 5 TeV","f");
  entryZ->SetTextFont(42);
  entryZ->SetLineColor(1);
  entryZ->SetMarkerColor(1);
  entryZ=legendZ->AddEntry(hZSignalData,"pp data 5 TeV","f");
  entryZ->SetTextFont(42);
  entryZ->SetLineColor(2);
  entryZ->SetMarkerColor(2);  
  legendZ->Draw();
  }
  else{
  entryZ=legendZ->AddEntry(hZSignalMC,"MC Hydjet+Pythia 5 TeV","f");
  entryZ->SetTextFont(42);
  entryZ->SetLineColor(1);
  entryZ->SetMarkerColor(1);
  entryZ=legendZ->AddEntry(hZSignalData,"PbPb data 5 TeV","f");
  entryZ->SetTextFont(42);
  entryZ->SetLineColor(2);
  entryZ->SetMarkerColor(2);
  legendZ->Draw();
  }
  if(isPP) canvas->SaveAs("canvasZPP_dataMC.pdf");
  else canvas->SaveAs("canvasZPbPb_dataMC.pdf");


  TFile* foutput = new TFile(output.Data(),"recreate");
  hSignalData->Write();
  hSignalMC->Write();
  hZSignalData->Write();
  hZSignalMC->Write();
  foutput->Close();
}



void comparePP_PbPb(int intjetpt_cut=80, int intDptlow_cut=10,int intDpthigh_cut=9999){
 
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

   TFile* finputPP = new TFile(Form("resultsPP_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
   TFile* finputPbPb = new TFile(Form("resultsPbPb_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
   
   TH1F*hSignalDataPbPb=(TH1F*)finputPbPb->Get("hSignalData");
   TH1F*hSignalDataPP=(TH1F*)finputPP->Get("hSignalData");
   TH1F*hSignalMCPbPb=(TH1F*)finputPbPb->Get("hSignalMC");
   TH1F*hSignalMCPP=(TH1F*)finputPP->Get("hSignalMC");


   TH1F*ratioPbPbpp=(TH1F*)hSignalDataPbPb->Clone("ratioPbPbpp");
   TH1F*hden=(TH1F*)hSignalDataPP->Clone("hden");
   ratioPbPbpp->SetName("ratioPbPbpp");
   ratioPbPbpp->Divide(hden);   

   TH1F*ratioPbPbppMC=(TH1F*)hSignalMCPbPb->Clone("ratioPbPbpp");
   TH1F*hdenMC=(TH1F*)hSignalMCPP->Clone("hden");
   ratioPbPbppMC->SetName("ratioPbPbppMC");
   ratioPbPbppMC->Divide(hdenMC);


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

   canvas->SaveAs(Form("canvasDataMC_jet%d_Dlow%d_Dhigh%d.pdf",intjetpt_cut,intDptlow_cut,intDpthigh_cut));

   TCanvas*canvasRatio=new TCanvas("canvasRatio","canvasRatio",500,500);
   canvasRatio->cd();
   canvasRatio->SetLogy();

   TH2F* hemptyratio=new TH2F("hemptyratio","",50,0,0.5,10,0.1,30.0);
   hemptyratio->GetXaxis()->CenterTitle();
   hemptyratio->GetYaxis()->CenterTitle();
   hemptyratio->GetXaxis()->SetTitle("#Delta R");
   hemptyratio->GetYaxis()->SetTitle("PbPb/pp");
   hemptyratio->GetXaxis()->SetTitleOffset(0.9);
   hemptyratio->GetYaxis()->SetTitleOffset(1.0);
   hemptyratio->GetXaxis()->SetTitleSize(0.05);
   hemptyratio->GetYaxis()->SetTitleSize(0.05);
   hemptyratio->GetXaxis()->SetTitleFont(42);
   hemptyratio->GetYaxis()->SetTitleFont(42);
   hemptyratio->GetXaxis()->SetLabelFont(42);
   hemptyratio->GetYaxis()->SetLabelFont(42);
   hemptyratio->GetXaxis()->SetLabelSize(0.035);
   hemptyratio->GetYaxis()->SetLabelSize(0.035);
   hemptyratio->Draw();
   ratioPbPbpp->Draw("psame");
   canvasRatio->SaveAs(Form("canvasPbPbppjetData%d_Dlow%d_Dhigh%d.pdf",intjetpt_cut,intDptlow_cut,intDpthigh_cut));



   TCanvas*canvasRatioMC=new TCanvas("canvasRatioMC","canvasRatioMC",500,500);
   canvasRatioMC->cd();
   canvasRatioMC->SetLogy();

   TH2F* hemptyratioMC=new TH2F("hemptyratioMC","",50,0,0.5,10,0.1,30.0);
   hemptyratioMC->GetXaxis()->CenterTitle();
   hemptyratioMC->GetYaxis()->CenterTitle();
   hemptyratioMC->GetXaxis()->SetTitle("#Delta R");
   hemptyratioMC->GetYaxis()->SetTitle("PbPb/pp MC");
   hemptyratioMC->GetXaxis()->SetTitleOffset(0.9);
   hemptyratioMC->GetYaxis()->SetTitleOffset(1.0);
   hemptyratioMC->GetXaxis()->SetTitleSize(0.05);
   hemptyratioMC->GetYaxis()->SetTitleSize(0.05);
   hemptyratioMC->GetXaxis()->SetTitleFont(42);
   hemptyratioMC->GetYaxis()->SetTitleFont(42);
   hemptyratioMC->GetXaxis()->SetLabelFont(42);
   hemptyratioMC->GetYaxis()->SetLabelFont(42);
   hemptyratioMC->GetXaxis()->SetLabelSize(0.035);
   hemptyratioMC->GetYaxis()->SetLabelSize(0.035);
   hemptyratioMC->Draw();
   ratioPbPbppMC->Draw("psame");
   canvasRatioMC->SaveAs(Form("canvasPbPbppjetMC%d_Dlow%d_Dhigh%d.pdf",intjetpt_cut,intDptlow_cut,intDpthigh_cut));

   TFile*fouput=new TFile(Form("RatioPbPbppjet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut),"recreate");
   ratioPbPbpp->Write();
   fouput->Close();
}


void compareRatios(){
   
   void analysis(double,double,double);
   analysis(80.,4.,8.);                                  
   analysis(80.,8.,20.);   
   analysis(80.,20.,80.);   
                                  
/*
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

   TFile* finputJet1 = new TFile("RatioPbPbppjet80_Dlow4_Dhigh8.root");
   TFile* finputJet2 = new TFile("RatioPbPbppjet80_Dlow10_Dhigh999.root");

   TH1F*ratioPbPbppJet1=(TH1F*)finputJet1->Get("ratioPbPbpp");
   TH1F*ratioPbPbppJet2=(TH1F*)finputJet2->Get("ratioPbPbpp");

   TCanvas*canvas=new TCanvas("canvas","canvas",500,500);
   canvas->cd();
   canvas->SetLogy();

   TH2F* hemptyratio=new TH2F("hemptyratio","",50,0,0.5,10,0.1,30.0);
   hemptyratio->GetXaxis()->CenterTitle();
   hemptyratio->GetYaxis()->CenterTitle();
   hemptyratio->GetXaxis()->SetTitle("#Delta R");
   hemptyratio->GetYaxis()->SetTitle("PbPb/pp");
   hemptyratio->GetXaxis()->SetTitleOffset(0.9);
   hemptyratio->GetYaxis()->SetTitleOffset(1.0);
   hemptyratio->GetXaxis()->SetTitleSize(0.05);
   hemptyratio->GetYaxis()->SetTitleSize(0.05);
   hemptyratio->GetXaxis()->SetTitleFont(42);
   hemptyratio->GetYaxis()->SetTitleFont(42);
   hemptyratio->GetXaxis()->SetLabelFont(42);
   hemptyratio->GetYaxis()->SetLabelFont(42);
   hemptyratio->GetXaxis()->SetLabelSize(0.035);
   hemptyratio->GetYaxis()->SetLabelSize(0.035);
   hemptyratio->Draw();


   ratioPbPbppJet1->SetLineColor(1);
   ratioPbPbppJet1->SetMarkerColor(1);
   ratioPbPbppJet1->Draw("psame");
 
   ratioPbPbppJet2->SetLineColor(2);
   ratioPbPbppJet2->SetMarkerColor(2);
   ratioPbPbppJet2->Draw("psame");
   
   TLegend *legend=new TLegend(0.3729839,0.7415254,0.7016129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
   legend->SetBorderSize(0);
   legend->SetLineColor(0);
   legend->SetFillColor(0);
   legend->SetFillStyle(1001);
   legend->SetTextFont(42);
   legend->SetTextSize(0.04);

   TLegendEntry*entry;
   entry=legend->AddEntry(ratioPbPbppJet1,"Jet 80 D p_{T}>4, p_{T}<8 GeV","f");
   entry->SetTextFont(42);
   entry->SetLineColor(1);
   entry->SetMarkerColor(1);
   entry=legend->AddEntry(ratioPbPbppJet2,"Jet 80 D p_{T}>10 GeV","f");
   entry->SetTextFont(42);
   entry->SetLineColor(2);
   entry->SetMarkerColor(2);
   legend->Draw();
*/
}
