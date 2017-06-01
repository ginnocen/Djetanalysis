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


void ReflectionStudies(int isPP=1,int intjetpt_cut=80,int intjetetamin_cut=3,int intjetetamax_cut=16){
 
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
   
   TH1F*hSignalData_indexBkg1_file1_NormArea=(TH1F*)file1->Get("hSignalData_indexBkg1");
   TH1F*hSignalData_indexBkg1_file2_NormArea=(TH1F*)file2->Get("hSignalData_indexBkg1");
   
   hSignalData_indexBkg1_file1_NormArea->SetName("hSignalData_indexBkg1_file1_NormArea");
   hSignalData_indexBkg1_file2_NormArea->SetName("hSignalData_indexBkg1_file2_NormArea");
   

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
 
   TCanvas*canvas=new TCanvas("canvas","canvas",500,500);

   static const int nRedges=4;
   double Redges[nRedges+1]={0.,0.05,0.1,0.2,0.5};     //different R ranges
   double Area[nRedges+1];
   double Length[nRedges+1];
   for (int i=0;i<nRedges;i++){
     Area[i]=((Redges[i+1])*(Redges[i+1])-(Redges[i])*(Redges[i]))*3.14;
     Length[i]=(Redges[i+1]-Redges[i]);
   }

  for (int i=0;i<nRedges;i++){

    hSignalData_indexBkg1_file1_NormArea->SetBinContent(i+1,hSignalData_indexBkg1_file1_NormArea->GetBinContent(i+1)/Area[i]*Length[i]);
    hSignalData_indexBkg1_file1_NormArea->SetBinError(i+1,hSignalData_indexBkg1_file1_NormArea->GetBinError(i+1)/Area[i]*Length[i]);
    hSignalData_indexBkg1_file2_NormArea->SetBinContent(i+1,hSignalData_indexBkg1_file2_NormArea->GetBinContent(i+1)/Area[i]*Length[i]);
    hSignalData_indexBkg1_file2_NormArea->SetBinError(i+1,hSignalData_indexBkg1_file2_NormArea->GetBinError(i+1)/Area[i]*Length[i]);
  }

   gPad->SetLogy();
   TH2F* hemptyBkgNorm=new TH2F("hemptyBkgNorm","",50,0,.5,10,0.0000000001,1000);
   hemptyBkgNorm->GetXaxis()->CenterTitle();
   hemptyBkgNorm->GetYaxis()->CenterTitle();
   hemptyBkgNorm->GetXaxis()->SetTitle("#Delta R");
   hemptyBkgNorm->GetYaxis()->SetTitle("D^{0} meson yield / Area");
   hemptyBkgNorm->GetXaxis()->SetTitleOffset(0.9);
   hemptyBkgNorm->GetYaxis()->SetTitleOffset(1.1);
   hemptyBkgNorm->GetXaxis()->SetTitleSize(0.05);
   hemptyBkgNorm->GetYaxis()->SetTitleSize(0.05);
   hemptyBkgNorm->GetXaxis()->SetTitleFont(42);
   hemptyBkgNorm->GetYaxis()->SetTitleFont(42);
   hemptyBkgNorm->GetXaxis()->SetLabelFont(42);
   hemptyBkgNorm->GetYaxis()->SetLabelFont(42);
   hemptyBkgNorm->GetXaxis()->SetLabelSize(0.035);
   hemptyBkgNorm->GetYaxis()->SetLabelSize(0.035);
   hemptyBkgNorm->Draw();
   hSignalData_indexBkg1_file1_NormArea->SetLineColor(1);
   hSignalData_indexBkg1_file1_NormArea->SetMarkerColor(1);
   hSignalData_indexBkg1_file1_NormArea->SetLineWidth(2);
   hSignalData_indexBkg1_file1_NormArea->SetMarkerStyle(23);
   hSignalData_indexBkg1_file2_NormArea->SetLineColor(2);
   hSignalData_indexBkg1_file2_NormArea->SetMarkerColor(2);
   hSignalData_indexBkg1_file2_NormArea->SetLineWidth(2);
   hSignalData_indexBkg1_file2_NormArea->SetMarkerStyle(21);
   hSignalData_indexBkg1_file1_NormArea->Draw("same");

   if(isPP==1)canvas->SaveAs(Form("PlotsResults/canvasppBkg1Norm_Jet%d_jetetamin%d_jetetamax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));
   if(isPP==0)canvas->SaveAs(Form("PlotsResults/canvasPbPbBkg1Norm_Jet%d_jetetamin%d_jetetamax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));

}



void Check(int isPP=1,int intjetpt_cut=80,int intjetetamin_cut=3,int intjetetamax_cut=16){
 
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
   
   TH1F*hSignalData_indexBkg1OverBkg0_file1=(TH1F*)file1->Get("hSignalData_indexBkg1");
   TH1F*hSignalData_indexBkg0_file1=(TH1F*)file1->Get("hSignalData_indexBkg0");
   TH1F*hSignalData_indexBkg1_file2=(TH1F*)file2->Get("hSignalData_indexBkg1");
   TH1F*hSignalData_indexBkg0_file2=(TH1F*)file2->Get("hSignalData_indexBkg0");
   
  hSignalData_indexBkg1OverBkg0_file1->Divide(hSignalData_indexBkg0_file1);
  hSignalData_indexBkg1OverBkg0_file1->Draw();
  
   gPad->SetLogy();
   
   TCanvas*canvas=new TCanvas("canvas","canvas",500,500);
   canvas->SetLogy();

   TH2F* hemptyBkg1OverBkg0=new TH2F("hemptyBkg1OverBkg0","",50,0,.5,10,0.000001,100000);
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

   hemptyBkg1OverBkg0->Draw();
   hSignalData_indexBkg1OverBkg0_file1->SetLineColor(1);
   hSignalData_indexBkg1OverBkg0_file1->SetMarkerColor(1);
   hSignalData_indexBkg1OverBkg0_file1->SetLineWidth(2);
   hSignalData_indexBkg1OverBkg0_file1->SetMarkerStyle(23);
   hSignalData_indexBkg1OverBkg0_file1->Draw("psame");

   if(isPP==1)canvas->SaveAs(Form("PlotsResults/canvasppBkg1OverBkg0DYield_Jet%d_jetetamin%d_jetetamax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));
   if(isPP==0)canvas->SaveAs(Form("PlotsResults/canvasPbPbBkg1OverBkg0DYield_Jet%d_jetetamin%d_jetetamax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));

}

