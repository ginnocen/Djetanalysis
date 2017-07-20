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


void JetShape(int jetptmin=80){

  void runJetShape(int,int,int,int,int);
  void JetShapeComparison(int,int,int);
  runJetShape(4,20,jetptmin,0,20);
  runJetShape(20,999,jetptmin,0,20);
  JetShapeComparison(jetptmin,0,20);
}

void runJetShape(int intDptlow_cut=6, int intDpthigh_cut=999, int intjetpt_cut=80, int intjetetamin_cut=0, int intjetetamax_cut=20){
 
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
   hSignalDataPP->SetName("hSignalDataPP");
   hSignalDataPbPb->SetName("hSignalDataPbPb");
   
   TH1F*hEfficiencyPP=(TH1F*)filePP->Get("fhEfficiency_0_indexBkg0");
   TH1F*hEfficiencyPbPb=(TH1F*)filePbPb->Get("fhEfficiency_0_indexBkg0");
   hEfficiencyPP->SetName("hEfficiencyPP");
   hEfficiencyPbPb->SetName("hEfficiencyPbPb");
   
   TH1F*hJetShapePP=(TH1F*)filePP->Get("hSignalData_indexBkg0");
   TH1F*hJetShapePbPb=(TH1F*)filePbPb->Get("hSignalData_indexBkg0");          
   hJetShapePP->SetName("hJetShapePP");
   hJetShapePbPb->SetName("hJetShapePbPb");

   hJetShapePP->Divide(hEfficiencyPP);
   hJetShapePbPb->Divide(hEfficiencyPbPb);
   
   TH1F*hJetShapePbPbOverPP=(TH1F*)hJetShapePbPb->Clone("hJetShapePbPbOverPP");
   hJetShapePbPbOverPP->Divide(hJetShapePP);

   TFile *foutput=new TFile(output.Data(),"recreate");
   hSignalDataPP->Write();
   hSignalDataPbPb->Write();
   hEfficiencyPP->Write();
   hEfficiencyPbPb->Write();
   hJetShapePP->Write();
   hJetShapePbPb->Write();
   hJetShapePbPbOverPP->Write();
   foutput->Close(); 
}


void JetShapeComparison(int intjetpt_cut=80,int intjetetamin_cut=0,int intjetetamax_cut=20){
 
   TString input1;
   TString input2;

   input1=Form("Files/results_jet%d_Dlow4_Dhigh20_jetetamin%d_jetetamax%d.root",intjetpt_cut,intjetetamin_cut,intjetetamax_cut);
   input2=Form("Files/results_jet%d_Dlow20_Dhigh999_jetetamin%d_jetetamax%d.root",intjetpt_cut,intjetetamin_cut,intjetetamax_cut);

   TFile*file1=new TFile(input1.Data());
   TFile*file2=new TFile(input2.Data());

   TH1F*hJetShapePbPbOverPP1=(TH1F*)file1->Get("hJetShapePbPbOverPP");
   TH1F*hSignalDataPP1=(TH1F*)file1->Get("hSignalDataPP");
   TH1F*hSignalDataPbPb1=(TH1F*)file1->Get("hSignalDataPbPb");
   TH1F*hJetShapePP1=(TH1F*)file1->Get("hJetShapePP");
   TH1F*hJetShapePbPb1=(TH1F*)file1->Get("hJetShapePbPb");
   TH1F*hEfficiencyPP1=(TH1F*)file1->Get("hEfficiencyPP");
   TH1F*hEfficiencyPbPb1=(TH1F*)file1->Get("hEfficiencyPbPb");

   TH1F*hJetShapePbPbOverPP2=(TH1F*)file2->Get("hJetShapePbPbOverPP");
   TH1F*hSignalDataPP2=(TH1F*)file2->Get("hSignalDataPP");
   TH1F*hSignalDataPbPb2=(TH1F*)file2->Get("hSignalDataPbPb");
   TH1F*hJetShapePP2=(TH1F*)file2->Get("hJetShapePP");
   TH1F*hJetShapePbPb2=(TH1F*)file2->Get("hJetShapePbPb");
   TH1F*hEfficiencyPP2=(TH1F*)file2->Get("hEfficiencyPP");
   TH1F*hEfficiencyPbPb2=(TH1F*)file2->Get("hEfficiencyPbPb");

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
 
   TCanvas*canvasPbPbOverPP=new TCanvas("canvasPbPbOverPP","canvasPbPbOverPP",500,500);
   canvasPbPbOverPP->SetLogy();
   TH2F* hemptyPbPbOverPP=new TH2F("hemptyPbPbOverPP","",50,0,.5,10,0.1,20.0);
   hemptyPbPbOverPP->GetXaxis()->CenterTitle();
   hemptyPbPbOverPP->GetYaxis()->CenterTitle();
   hemptyPbPbOverPP->GetXaxis()->SetTitle("#Delta R");
   hemptyPbPbOverPP->GetYaxis()->SetTitle("D^{0} meson yield PbPb/pp");
   hemptyPbPbOverPP->GetXaxis()->SetTitleOffset(0.9);
   hemptyPbPbOverPP->GetYaxis()->SetTitleOffset(1.1);
   hemptyPbPbOverPP->GetXaxis()->SetTitleSize(0.05);
   hemptyPbPbOverPP->GetYaxis()->SetTitleSize(0.05);
   hemptyPbPbOverPP->GetXaxis()->SetTitleFont(42);
   hemptyPbPbOverPP->GetYaxis()->SetTitleFont(42);
   hemptyPbPbOverPP->GetXaxis()->SetLabelFont(42);
   hemptyPbPbOverPP->GetYaxis()->SetLabelFont(42);
   hemptyPbPbOverPP->GetXaxis()->SetLabelSize(0.035);
   hemptyPbPbOverPP->GetYaxis()->SetLabelSize(0.035);
  
   TLegend *legendJetShapePbPbOverPP=new TLegend(0.2729839,0.7415254,0.616129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
   legendJetShapePbPbOverPP->SetBorderSize(0);
   legendJetShapePbPbOverPP->SetLineColor(0);
   legendJetShapePbPbOverPP->SetFillColor(0);
   legendJetShapePbPbOverPP->SetFillStyle(1001);
   legendJetShapePbPbOverPP->SetTextFont(42);
   legendJetShapePbPbOverPP->SetTextSize(0.04);
 
   TLegendEntry *ent_hJetShapePbPbOverPP1=legendJetShapePbPbOverPP->AddEntry(hJetShapePbPbOverPP1,"D^{0} p_{\rm T} > 6 GeV/c","pf");
   ent_hJetShapePbPbOverPP1->SetTextFont(42);
   ent_hJetShapePbPbOverPP1->SetLineColor(1);
   ent_hJetShapePbPbOverPP1->SetFillColor(0);
   ent_hJetShapePbPbOverPP1->SetMarkerColor(1);
 
   TLegendEntry *ent_hJetShapePbPbOverPP2=legendJetShapePbPbOverPP->AddEntry(hJetShapePbPbOverPP2,"D^{0} p_{\rm T} > 20 GeV/c","pf");
   ent_hJetShapePbPbOverPP2->SetTextFont(42);
   ent_hJetShapePbPbOverPP2->SetLineColor(1);
   ent_hJetShapePbPbOverPP2->SetFillColor(0);
   ent_hJetShapePbPbOverPP2->SetMarkerColor(2);

   canvasPbPbOverPP->cd(); 
   hemptyPbPbOverPP->Draw();
   hJetShapePbPbOverPP1->SetLineColor(1);
   hJetShapePbPbOverPP1->SetMarkerColor(1);
   hJetShapePbPbOverPP1->SetLineWidth(2);
   hJetShapePbPbOverPP1->SetMarkerStyle(23);
   hJetShapePbPbOverPP2->SetLineColor(2);
   hJetShapePbPbOverPP2->SetMarkerColor(2);
   hJetShapePbPbOverPP2->SetLineWidth(2);
   hJetShapePbPbOverPP2->SetMarkerStyle(21);
   hJetShapePbPbOverPP1->Draw("psame");
   hJetShapePbPbOverPP2->Draw("psame");
   legendJetShapePbPbOverPP->Draw();
   canvasPbPbOverPP->SaveAs(Form("PlotsResults/canvasPbPbOverPPPbPbOverPPJetShape_Jet%d_Dmin%d_Dmax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));


   TCanvas*canvasYields=new TCanvas("canvasYields","canvasYields",1000,500);
   canvasYields->Divide(2,1);
   canvasYields->cd(1);
   gPad->SetLogy();
   
   TH2F* hemptyYieldsPP=new TH2F("hemptyYieldsPP","",50,0,.5,10,0.000001,100);
   hemptyYieldsPP->GetXaxis()->CenterTitle();
   hemptyYieldsPP->GetYaxis()->CenterTitle();
   hemptyYieldsPP->GetXaxis()->SetTitle("#Delta R");
   hemptyYieldsPP->GetYaxis()->SetTitle("D^{0} meson yield pp");
   hemptyYieldsPP->GetXaxis()->SetTitleOffset(0.9);
   hemptyYieldsPP->GetYaxis()->SetTitleOffset(1.2);
   hemptyYieldsPP->GetXaxis()->SetTitleSize(0.05);
   hemptyYieldsPP->GetYaxis()->SetTitleSize(0.05);
   hemptyYieldsPP->GetXaxis()->SetTitleFont(42);
   hemptyYieldsPP->GetYaxis()->SetTitleFont(42);
   hemptyYieldsPP->GetXaxis()->SetLabelFont(42);
   hemptyYieldsPP->GetYaxis()->SetLabelFont(42);
   hemptyYieldsPP->GetXaxis()->SetLabelSize(0.035);
   hemptyYieldsPP->GetYaxis()->SetLabelSize(0.035);

   TLegend *legendJetShapeYields=new TLegend(0.2729839,0.7415254,0.616129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
   legendJetShapeYields->SetBorderSize(0);
   legendJetShapeYields->SetLineColor(0);
   legendJetShapeYields->SetFillColor(0);
   legendJetShapeYields->SetFillStyle(1001);
   legendJetShapeYields->SetTextFont(42);
   legendJetShapeYields->SetTextSize(0.04);
 
   TLegendEntry *ent_hJetShapeYields1=legendJetShapeYields->AddEntry(hSignalDataPP1,"D^{0} p_{\rm T} > 6 GeV/c","pf");
   ent_hJetShapeYields1->SetTextFont(42);
   ent_hJetShapeYields1->SetLineColor(1);
   ent_hJetShapeYields1->SetFillColor(0);
   ent_hJetShapeYields1->SetMarkerColor(1);
 
   TLegendEntry *ent_hJetShapeYields2=legendJetShapeYields->AddEntry(hSignalDataPP2,"D^{0} p_{\rm T} > 20 GeV/c","pf");
   ent_hJetShapeYields2->SetTextFont(42);
   ent_hJetShapeYields2->SetLineColor(1);
   ent_hJetShapeYields2->SetFillColor(0);
   ent_hJetShapeYields2->SetMarkerColor(2);
   
   hemptyYieldsPP->Draw();
   hSignalDataPP1->SetLineColor(1);
   hSignalDataPP1->SetMarkerColor(1);
   hSignalDataPP1->SetLineWidth(2);
   hSignalDataPP1->SetMarkerStyle(23);
   hSignalDataPP2->SetLineColor(2);
   hSignalDataPP2->SetMarkerColor(2);
   hSignalDataPP2->SetLineWidth(2);
   hSignalDataPP2->SetMarkerStyle(21);
   hSignalDataPP1->Draw("psame");
   hSignalDataPP2->Draw("psame");
   legendJetShapeYields->Draw();

   canvasYields->cd(2);
   gPad->SetLogy(); 

   TH2F* hemptyYieldsPbPb=new TH2F("hemptyYieldsPbPb","",50,0,.5,10,0.000001,100);
   hemptyYieldsPbPb->GetXaxis()->CenterTitle();
   hemptyYieldsPbPb->GetYaxis()->CenterTitle();
   hemptyYieldsPbPb->GetXaxis()->SetTitle("#Delta R");
   hemptyYieldsPbPb->GetYaxis()->SetTitle("D^{0} meson yield PbPb");
   hemptyYieldsPbPb->GetXaxis()->SetTitleOffset(0.9);
   hemptyYieldsPbPb->GetYaxis()->SetTitleOffset(1.2);
   hemptyYieldsPbPb->GetXaxis()->SetTitleSize(0.05);
   hemptyYieldsPbPb->GetYaxis()->SetTitleSize(0.05);
   hemptyYieldsPbPb->GetXaxis()->SetTitleFont(42);
   hemptyYieldsPbPb->GetYaxis()->SetTitleFont(42);
   hemptyYieldsPbPb->GetXaxis()->SetLabelFont(42);
   hemptyYieldsPbPb->GetYaxis()->SetLabelFont(42);
   hemptyYieldsPbPb->GetXaxis()->SetLabelSize(0.035);
   hemptyYieldsPbPb->GetYaxis()->SetLabelSize(0.035);

   hemptyYieldsPbPb->Draw();
   hSignalDataPbPb1->SetLineColor(1);
   hSignalDataPbPb1->SetMarkerColor(1);
   hSignalDataPbPb1->SetLineWidth(2);
   hSignalDataPbPb1->SetMarkerStyle(23);
   hSignalDataPbPb2->SetLineColor(2);
   hSignalDataPbPb2->SetMarkerColor(2);
   hSignalDataPbPb2->SetLineWidth(2);
   hSignalDataPbPb2->SetMarkerStyle(21);
   hSignalDataPbPb1->Draw("psame");
   hSignalDataPbPb2->Draw("psame");
   legendJetShapeYields->Draw();


   canvasYields->SaveAs(Form("PlotsResults/canvasYieldsJetShape_Jet%d_Dmin%d_Dmax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));



   TCanvas*canvasEfficiencies=new TCanvas("canvasEfficiencies","canvasEfficiencies",1000,500);
   canvasEfficiencies->Divide(2,1);
   canvasEfficiencies->cd(1);
   
   TH2F* hemptyEfficienciesPP=new TH2F("hemptyEfficienciesPP","",50,0,.5,10,0.,1.0);
   hemptyEfficienciesPP->GetXaxis()->CenterTitle();
   hemptyEfficienciesPP->GetYaxis()->CenterTitle();
   hemptyEfficienciesPP->GetXaxis()->SetTitle("#Delta R");
   hemptyEfficienciesPP->GetYaxis()->SetTitle("Efficiency D^{0} meson pp");
   hemptyEfficienciesPP->GetXaxis()->SetTitleOffset(0.9);
   hemptyEfficienciesPP->GetYaxis()->SetTitleOffset(1.2);
   hemptyEfficienciesPP->GetXaxis()->SetTitleSize(0.05);
   hemptyEfficienciesPP->GetYaxis()->SetTitleSize(0.05);
   hemptyEfficienciesPP->GetXaxis()->SetTitleFont(42);
   hemptyEfficienciesPP->GetYaxis()->SetTitleFont(42);
   hemptyEfficienciesPP->GetXaxis()->SetLabelFont(42);
   hemptyEfficienciesPP->GetYaxis()->SetLabelFont(42);
   hemptyEfficienciesPP->GetXaxis()->SetLabelSize(0.035);
   hemptyEfficienciesPP->GetYaxis()->SetLabelSize(0.035);

   TLegend *legendJetShapeEfficiencies=new TLegend(0.2729839,0.7415254,0.616129,0.8622881,"");//0.5100806,0.5868644,0.8084677,0.7605932
   legendJetShapeEfficiencies->SetBorderSize(0);
   legendJetShapeEfficiencies->SetLineColor(0);
   legendJetShapeEfficiencies->SetFillColor(0);
   legendJetShapeEfficiencies->SetFillStyle(1001);
   legendJetShapeEfficiencies->SetTextFont(42);
   legendJetShapeEfficiencies->SetTextSize(0.04);
 
   TLegendEntry *ent_hJetShapeEfficiencies1=legendJetShapeEfficiencies->AddEntry(hEfficiencyPP1,"D^{0} p_{\rm T} > 6 GeV/c","pf");
   ent_hJetShapeEfficiencies1->SetTextFont(42);
   ent_hJetShapeEfficiencies1->SetLineColor(1);
   ent_hJetShapeEfficiencies1->SetFillColor(0);
   ent_hJetShapeEfficiencies1->SetMarkerColor(1);
 
   TLegendEntry *ent_hJetShapeEfficiencies2=legendJetShapeEfficiencies->AddEntry(hEfficiencyPP2,"D^{0} p_{\rm T} > 20 GeV/c","pf");
   ent_hJetShapeEfficiencies2->SetTextFont(42);
   ent_hJetShapeEfficiencies2->SetLineColor(1);
   ent_hJetShapeEfficiencies2->SetFillColor(0);
   ent_hJetShapeEfficiencies2->SetMarkerColor(2);
   
   hemptyEfficienciesPP->Draw();
   hEfficiencyPP1->SetLineColor(1);
   hEfficiencyPP1->SetMarkerColor(1);
   hEfficiencyPP1->SetLineWidth(2);
   hEfficiencyPP1->SetMarkerStyle(23);
   hEfficiencyPP2->SetLineColor(2);
   hEfficiencyPP2->SetMarkerColor(2);
   hEfficiencyPP2->SetLineWidth(2);
   hEfficiencyPP2->SetMarkerStyle(21);
   hEfficiencyPP1->Draw("psame");
   hEfficiencyPP2->Draw("psame");
   legendJetShapeEfficiencies->Draw();

   canvasEfficiencies->cd(2);

   TH2F* hemptyEfficienciesPbPb=new TH2F("hemptyEfficienciesPbPb","",50,0,.5,10,0.,1.0);
   hemptyEfficienciesPbPb->GetXaxis()->CenterTitle();
   hemptyEfficienciesPbPb->GetYaxis()->CenterTitle();
   hemptyEfficienciesPbPb->GetXaxis()->SetTitle("#Delta R");
   hemptyEfficienciesPbPb->GetYaxis()->SetTitle("Efficiency D^{0} meson PbPb");
   hemptyEfficienciesPbPb->GetXaxis()->SetTitleOffset(0.9);
   hemptyEfficienciesPbPb->GetYaxis()->SetTitleOffset(1.2);
   hemptyEfficienciesPbPb->GetXaxis()->SetTitleSize(0.05);
   hemptyEfficienciesPbPb->GetYaxis()->SetTitleSize(0.05);
   hemptyEfficienciesPbPb->GetXaxis()->SetTitleFont(42);
   hemptyEfficienciesPbPb->GetYaxis()->SetTitleFont(42);
   hemptyEfficienciesPbPb->GetXaxis()->SetLabelFont(42);
   hemptyEfficienciesPbPb->GetYaxis()->SetLabelFont(42);
   hemptyEfficienciesPbPb->GetXaxis()->SetLabelSize(0.035);
   hemptyEfficienciesPbPb->GetYaxis()->SetLabelSize(0.035);

   hemptyEfficienciesPbPb->Draw();
   hEfficiencyPbPb1->SetLineColor(1);
   hEfficiencyPbPb1->SetMarkerColor(1);
   hEfficiencyPbPb1->SetLineWidth(2);
   hEfficiencyPbPb1->SetMarkerStyle(23);
   hEfficiencyPbPb2->SetLineColor(2);
   hEfficiencyPbPb2->SetMarkerColor(2);
   hEfficiencyPbPb2->SetLineWidth(2);
   hEfficiencyPbPb2->SetMarkerStyle(21);
   hEfficiencyPbPb1->Draw("psame");
   hEfficiencyPbPb2->Draw("psame");
   legendJetShapeEfficiencies->Draw();


   canvasEfficiencies->SaveAs(Form("PlotsResults/canvasEfficienciesJetShape_Jet%d_Dmin%d_Dmax%d.pdf",intjetpt_cut,intjetetamin_cut,intjetetamax_cut));


}



