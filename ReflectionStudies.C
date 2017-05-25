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


void ReflectionStudies(int isPP=1,int intjetpt_cut=80,int intjetetamin_cut=0,int intjetetamax_cut=20){
 
   TString input1;
   TString input2;
 
   if(isPP==1){
     input1=Form("Files/resultsPP_jet%d_Dlow6_Dhigh999_jetetamin%d_jetetamax%d.root",intjetpt_cut,intjetetamin_cut,intjetetamax_cut);
     input2=Form("Files/resultsPP_jet%d_Dlow20_Dhigh999_jetetamin%d_jetetamax%d.root",intjetpt_cut,intjetetamin_cut,intjetetamax_cut);
   }
   if(isPP==0){
     input1=Form("Files/resultsPbPb_jet%d_Dlow6_Dhigh999_jetetamin%d_jetetamax%d.root",intjetpt_cut,intjetetamin_cut,intjetetamax_cut);
     input2=Form("Files/resultsPbPb_jet%d_Dlow20_Dhigh999_jetetamin%d_jetetamax%d.root",intjetpt_cut,intjetetamin_cut,intjetetamax_cut);
   }
   
   TFile*file1=new TFile(input1.Data());
   TFile*file2=new TFile(input2.Data());

   TH1F*hSignalData_indexBkg0_file1=(TH1F*)file1->Get("hSignalData_indexBkg0");
   TH1F*hSignalData_indexBkg1_file1=(TH1F*)file1->Get("hSignalData_indexBkg1");
   TH1F*hSignalData_indexBkg0_file2=(TH1F*)file2->Get("hSignalData_indexBkg0");
   TH1F*hSignalData_indexBkg1_file2=(TH1F*)file2->Get("hSignalData_indexBkg1");
   
   hSignalData_indexBkg1_file1->Divide(hSignalData_indexBkg0_file1);
   hSignalData_indexBkg1_file2->Divide(hSignalData_indexBkg0_file2);
   
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
 
   TCanvas*canvasBkg1OverBkg0=new TCanvas("canvasBkg1OverBkg0","canvasBkg1OverBkg0",500,500);
   canvasBkg1OverBkg0->SetLogy();
   TH2F* hemptyBkg1OverBkg0=new TH2F("hemptyBkg1OverBkg0","",50,0,.5,10,0.001,1000.0);
   hemptyBkg1OverBkg0->GetXaxis()->CenterTitle();
   hemptyBkg1OverBkg0->GetYaxis()->CenterTitle();
   hemptyBkg1OverBkg0->GetXaxis()->SetTitle("#Delta R");
   hemptyBkg1OverBkg0->GetYaxis()->SetTitle("D^{0} meson yield Reflected/Standard");
   hemptyBkg1OverBkg0->GetXaxis()->SetTitleOffset(0.9);
   hemptyBkg1OverBkg0->GetYaxis()->SetTitleOffset(1.1);
   hemptyBkg1OverBkg0->GetXaxis()->SetTitleSize(0.05);
   hemptyBkg1OverBkg0->GetYaxis()->SetTitleSize(0.05);
   hemptyBkg1OverBkg0->GetXaxis()->SetTitleFont(42);
   hemptyBkg1OverBkg0->GetYaxis()->SetTitleFont(42);
   hemptyBkg1OverBkg0->GetXaxis()->SetLabelFont(42);
   hemptyBkg1OverBkg0->GetYaxis()->SetLabelFont(42);
   hemptyBkg1OverBkg0->GetXaxis()->SetLabelSize(0.035);
   hemptyBkg1OverBkg0->GetYaxis()->SetLabelSize(0.035);
  
   TLegend *legendDYieldBkg1OverBkg0=new TLegend(0.2729839,0.7415254,0.616129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
   legendDYieldBkg1OverBkg0->SetBorderSize(0);
   legendDYieldBkg1OverBkg0->SetLineColor(0);
   legendDYieldBkg1OverBkg0->SetFillColor(0);
   legendDYieldBkg1OverBkg0->SetFillStyle(1001);
   legendDYieldBkg1OverBkg0->SetTextFont(42);
   legendDYieldBkg1OverBkg0->SetTextSize(0.04);
 
   TLegendEntry *ent_hDYieldBkg1OverBkg01=legendDYieldBkg1OverBkg0->AddEntry(hSignalData_indexBkg1_file1,"D^{0} p_{\rm T} > 6 GeV/c","pf");
   ent_hDYieldBkg1OverBkg01->SetTextFont(42);
   ent_hDYieldBkg1OverBkg01->SetLineColor(1);
   ent_hDYieldBkg1OverBkg01->SetFillColor(0);
   ent_hDYieldBkg1OverBkg01->SetMarkerColor(1);
 
   TLegendEntry *ent_hDYieldBkg1OverBkg02=legendDYieldBkg1OverBkg0->AddEntry(hSignalData_indexBkg1_file2,"D^{0} p_{\rm T} > 20 GeV/c","pf");
   ent_hDYieldBkg1OverBkg02->SetTextFont(42);
   ent_hDYieldBkg1OverBkg02->SetLineColor(1);
   ent_hDYieldBkg1OverBkg02->SetFillColor(0);
   ent_hDYieldBkg1OverBkg02->SetMarkerColor(2);

   hemptyBkg1OverBkg0->Draw();
   hSignalData_indexBkg1_file1->SetLineColor(1);
   hSignalData_indexBkg1_file1->SetMarkerColor(1);
   hSignalData_indexBkg1_file1->SetLineWidth(2);
   hSignalData_indexBkg1_file1->SetMarkerStyle(23);
   hSignalData_indexBkg1_file2->SetLineColor(2);
   hSignalData_indexBkg1_file2->SetMarkerColor(2);
   hSignalData_indexBkg1_file2->SetLineWidth(2);
   hSignalData_indexBkg1_file2->SetMarkerStyle(21);
   hSignalData_indexBkg1_file1->Draw("psame");
   hSignalData_indexBkg1_file2->Draw("psame");
   legendDYieldBkg1OverBkg0->Draw();
   if(isPP==1)canvasBkg1OverBkg0->SaveAs(Form("PlotsResults/canvasppBkg1OverBkg0DYield_Jet%d_Dmin%d_Dmax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));
   if(isPP==0)canvasBkg1OverBkg0->SaveAs(Form("PlotsResults/canvasPbPbBkg1OverBkg0DYield_Jet%d_Dmin%d_Dmax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));


}



