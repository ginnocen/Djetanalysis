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


void divideBinWidth(TH1* h)
{
  h->Sumw2();
  for(int i=1;i<=h->GetNbinsX();i++)
    {
      Float_t val = h->GetBinContent(i);
      Float_t valErr = h->GetBinError(i);
      val/=h->GetBinWidth(i);
      valErr/=h->GetBinWidth(i);
      h->SetBinContent(i,val);
      h->SetBinError(i,valErr);
    }
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
}


void loop(double jetpt_cut=80.,double Dptlow_cut=4.,double Dpthigh_cut=999.){

  double jeteta_cut=1.6;
  double Dy_cut=2.0;
  double decaylength_cut=3;//4.06
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

  djet* tpp = new djet("/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/merged.root");
  tpp->SetJetPtCutEta(jetpt_cut,jeteta_cut);
  tpp->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
  tpp->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut);
  tpp->loop(1);
  tpp->d_jet(Form("myDataPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
*/
  djet* tMCpp = new djet("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root");
  tMCpp->SetJetPtCutEta(jetpt_cut,jeteta_cut);
  tMCpp->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
  tMCpp->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut); 
  tMCpp->loop(0);
  tMCpp->d_jet(Form("myMCPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
/* 
  void runFit(int,int,int,int,int);
  void comparePP_PbPb(int,int,int);
  runFit(1,intjetpt_cut,intDptlow_cut,intDpthigh_cut);
  runFit(0,intjetpt_cut,intDptlow_cut,intDpthigh_cut);
  comparePP_PbPb(intjetpt_cut,intDptlow_cut,intDpthigh_cut);
*/
}

void runFit(int isPP=1,int genIndex=0,int intjetpt_cut=80, int intDptlow_cut=4,int intDpthigh_cut=999){
 
   djet* tempty = new djet("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root");
   const int nedgesR=tempty->GetnRedges();
   double Redges[nedgesR+1];
   for (int m=0;m<nedgesR+1;m++) Redges[m]=tempty->GetRedgesEdges(m);

   const int nedgesZ=tempty->GetnZedges();
   double Zedges[nedgesZ+1];
   for (int m=0;m<nedgesZ+1;m++) Zedges[m]=tempty->GetZedgesEdges(m);

   TString file,fileMC,output;

   if(isPP){
     //file=Form("myDataPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     file=Form("myMCPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     fileMC=Form("myMCPPtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     output=Form("resultsPP_jet%d_Dlow%d_Dhigh%d_genIndex%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,genIndex);
   }
   
   if(!isPP){
     file=Form("myDataPbPbtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     fileMC=Form("myMCPbPbtest_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut);
     output=Form("resultsPbPb_jet%d_Dlow%d_Dhigh%d_genIndex%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,genIndex);
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

   TString canvasData;
   TString canvasMC;

   TH1F*hNjetsData=(TH1F*)finput->Get("hNjets");
   TH1F*hNjetsMC=(TH1F*)finputMC->Get("hNjets");
   hNjetsData->SetName("hNjetsData");
   hNjetsMC->SetName("hNjetsMC");
 
   TH1F*fhEfficiency=(TH1F*)finputMC->Get(Form("fhEfficiency_%d",genIndex));
   TH1F*fhZEfficiency=(TH1F*)finputMC->Get(Form("fhZEfficiency_%d",genIndex));
   TH1F*fhDenEfficiency=(TH1F*)finputMC->Get(Form("fhDenEfficiency_%d",genIndex));
   TH1F*fhNumEfficiency=(TH1F*)finputMC->Get(Form("fhNumEfficiency_%d",genIndex));
   TH1F*fhZDenEfficiency=(TH1F*)finputMC->Get(Form("fhZDenEfficiency_%d",genIndex));
   TH1F*fhZNumEfficiency=(TH1F*)finputMC->Get(Form("fhZNumEfficiency_%d",genIndex));
   /*
   fhEfficiency->SetName(Form("fhEfficiency_%d",genIndex));
   fhZEfficiency->SetName(Form("fhZEfficiency_%d",genIndex));
   fhNumEfficiency->SetName(Form("fhNumEfficiency_%d",genIndex));
   fhDenEfficiency->SetName(Form("fhDenEfficiency_%d",genIndex));
   fhZNumEfficiency->SetName(Form("fhZNumEfficiency_%d",genIndex));
   fhZDenEfficiency->SetName(Form("fhZDenEfficiency_%d",genIndex));
   */
    for (int i=0;i<nedgesR;i++){
      canvasData=Form("PlotsFits/ResultsDataJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Rindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);
      canvasMC=Form("PlotsFits/ResultsMCJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Rindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);

      hHistoMassData[i]=(TH1F*)finput->Get(Form("fhHistoMass_indexGen%d_R%d",genIndex,i));
      hHistoMassMC[i]=(TH1F*)finputMC->Get(Form("fhHistoMass_indexGen%d_R%d",genIndex,i));
      hHistoGenSignal[i]=(TH1F*)finputMC->Get(Form("fhHistoGenSignal_indexGen%d_R%d",genIndex,i));
      hHistoGenSwapped[i]=(TH1F*)finputMC->Get(Form("fhHistoGenSwapped_indexGen%d_R%d",genIndex,i));
      fitData[i]=new Dfitter(hHistoMassData[i],hHistoGenSignal[i],hHistoGenSwapped[i],canvasData);
      fitMC[i]=new Dfitter(hHistoMassMC[i],hHistoGenSignal[i],hHistoGenSwapped[i],canvasMC);

    }
    for (int i=0;i<nedgesR;i++){
       hSignalData->SetBinContent(i+1,fitData[i]->GetSignal());
       hSignalData->SetBinError(i+1,fitData[i]->GetSignalError());
       hSignalMC->SetBinContent(i+1,fitMC[i]->GetSignal());
       hSignalMC->SetBinError(i+1,fitMC[i]->GetSignalError());
       cout<<"GUARDA QUI pt bin="<<i<<", value"<<fitData[i]->GetSignal()<<endl;
    }

   TString canvasZData;
   TString canvasZMC;

    for (int i=0;i<nedgesZ;i++){

      canvasZData=Form("PlotsFits/ResultsZDataJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Zindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);
      canvasZMC=Form("PlotsFits/ResultsZMCJetPt%d_Dptmin%d_Dptmax%d_isPP%d_Zindex%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,isPP,i);

      hHistoZMassData[i]=(TH1F*)finput->Get(Form("fhHistoZMass_indexGen%d_R%d",genIndex,i));
      hHistoZMassMC[i]=(TH1F*)finputMC->Get(Form("fhHistoZMass_indexGen%d_R%d",genIndex,i));
      hHistoZGenSignal[i]=(TH1F*)finputMC->Get(Form("fhHistoZGenSignal_indexGen%d_R%d",genIndex,i));
      hHistoZGenSwapped[i]=(TH1F*)finputMC->Get(Form("fhHistoZGenSwapped_indexGen%d_R%d",genIndex,i));
      fitZData[i]=new Dfitter(hHistoZMassData[i],hHistoZGenSignal[i],hHistoZGenSwapped[i],canvasZData);
      fitZMC[i]=new Dfitter(hHistoZMassMC[i],hHistoZGenSignal[i],hHistoZGenSwapped[i],canvasZMC);

    }
    for (int i=0;i<nedgesZ;i++){
       hZSignalData->SetBinContent(i+1,fitZData[i]->GetSignal());
       hZSignalData->SetBinError(i+1,fitZData[i]->GetSignalError());
       hZSignalMC->SetBinContent(i+1,fitZMC[i]->GetSignal());
       hZSignalMC->SetBinError(i+1,fitZMC[i]->GetSignalError());
}
  double normJetsData=hNjetsData->GetBinContent(genIndex+1); 
  double normJetsMC=hNjetsMC->GetBinContent(genIndex+1);
 
 
  divideBinWidth(hSignalData);
  divideBinWidth(hSignalMC);
  divideBinWidth(hZSignalData);
  divideBinWidth(hZSignalMC);


  hSignalData->Scale(1./normJetsData);
  hZSignalData->Scale(1./normJetsData);
  hSignalMC->Scale(1./normJetsMC);
  hZSignalMC->Scale(1./normJetsMC);
  fhNumEfficiency->Scale(1./normJetsMC);
  fhDenEfficiency->Scale(1./normJetsMC);
  fhZDenEfficiency->Scale(1./normJetsMC);
  fhZNumEfficiency->Scale(1./normJetsMC);

  TH1F*hJetShape=(TH1F*)hSignalData->Clone("hJetShape");
  hJetShape->Sumw2();
  hJetShape->Divide(fhEfficiency);
  TH1F*hFF=(TH1F*)hZSignalData->Clone("hFF");
  hFF->Sumw2();
  hFF->Divide(fhZEfficiency);

  TCanvas*canvas=new TCanvas("canvas","canvas",500,500);
  canvas->cd();
  canvas->SetLogy();
  cout<<"step4"<<endl; 
  TFile* foutput = new TFile(output.Data(),"recreate");
  hSignalData->Write();
  hSignalMC->Write();
  hZSignalData->Write();
  hZSignalMC->Write();
  hJetShape->Write();
  hFF->Write();
  fhEfficiency->Write();
  fhZEfficiency->Write();
  fhNumEfficiency->Write();
  fhDenEfficiency->Write();
  fhZNumEfficiency->Write();
  fhZDenEfficiency->Write();
  foutput->Close();
}



void comparePP_PbPb(int intjetpt_cut=80, int intDptlow_cut=10,int intDpthigh_cut=9999){
 
   TFile* finputPP = new TFile(Form("resultsPP_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
   TFile* finputPbPb = new TFile(Form("resultsPbPb_jet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
   
   TH1F*hJetShapePbPb=(TH1F*)finputPbPb->Get("hJetShape");
   TH1F*hJetShapePP=(TH1F*)finputPP->Get("hJetShape");

   TH1F*ratioPbPbpp=(TH1F*)hJetShapePbPb->Clone("ratioPbPbpp");
   TH1F*hden=(TH1F*)hJetShapePP->Clone("hden");
   ratioPbPbpp->SetName("ratioPbPbpp");
   ratioPbPbpp->Divide(hden);   
   TFile*fouput=new TFile(Form("RatioPbPbppjet%d_Dlow%d_Dhigh%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut),"recreate");
   ratioPbPbpp->Write();
   fouput->Close();
}


void analysis(){
   
   void loop(double,double,double);
   loop(80.,4.,8.);                                  
   loop(80.,10.,999.);   
  
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

}
