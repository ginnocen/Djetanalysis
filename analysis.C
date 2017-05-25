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


void analysis(bool doloop=false, bool doloopreflection=true, bool doFit=false, bool doFitreflection=true){
 
   bool doPPData=true;
   bool doPPMC=true;
   bool doPbPbData=true;
   bool doPbPbMC=true;
 
  // void runFit(int isPP=1,int intjetpt_cut=80, int intDptlow_cut=4,int intDpthigh_cut=999){

   void loop(bool,bool,bool,bool,double,double,double,double,double);
   void runFit(int,int,int,int,int,int);
   
   if(doloop){
       loop(doPPData,doPPMC,doPbPbData,doPbPbMC,80,6,999,0,20);
       loop(doPPData,doPPMC,doPbPbData,doPbPbMC,80,20,999,0,20);
   }

   if(doloopreflection){
       loop(doPPData,doPPMC,doPbPbData,doPbPbMC,80,6,999,3,16);
       loop(doPPData,doPPMC,doPbPbData,doPbPbMC,80,20,999,3,16);
   }
   if(doFit){
     runFit(1,80,6,999,0,20);
     runFit(0,80,6,999,0,20);
     runFit(1,80,20,999,0,20);
     runFit(0,80,20,999,0,20);
   }
   if(doFitreflection){
     runFit(1,80,6,999,3,16);
     runFit(0,80,6,999,3,16);
     runFit(1,80,20,999,3,16);
     runFit(0,80,20,999,3,16);
   }
} 


void loop(bool doPPData=false,bool doPPMC=true,bool doPbPbData=false,bool doPbPbMC=false,double jetpt_cut=80.,double Dptlow_cut=4.,double Dpthigh_cut=999.,double jetetamin_cut=3.,double jetetamax_cut=16.){
   double Dy_cut=2.0;
  double decaylength_cut=4.06;//4.06
  double decaylength_cutPbPb=6.0;//4.06
  double Dalpha_cut=0.12;
  double trkptmin_cut=2.0;
  double trketa_cut=2.0;
  double trkpterr_cut=0.3;
  double chi2cl_cut=0.1;
  
    
  int intjetpt_cut=(int)(jetpt_cut);
  int intDptlow_cut=(int)(Dptlow_cut);
  int intDpthigh_cut=(int)(Dpthigh_cut);  
  int intjetetamin_cut=(int)(jetetamin_cut);
  int intjetetamax_cut=(int)(jetetamax_cut); 

 
  jetetamin_cut=jetetamin_cut/10.;
  jetetamax_cut=jetetamax_cut/10.;

  if(doPbPbData){
    djet* tData = new djet("/export/d00/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1/merged_total.root");
    tData->SetJetPtCutEta(jetpt_cut,jetetamin_cut,jetetamax_cut);
    tData->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
    tData->SetDmesonCuts(decaylength_cutPbPb,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut);
    tData->loop(1);
    tData->d_jet(Form("Files/myDataPbPbtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut));
  }

  if(doPbPbMC){
    djet* tMC = new djet("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root");
    tMC->SetJetPtCutEta(jetpt_cut,jetetamin_cut,jetetamax_cut);
    tMC->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
    tMC->SetDmesonCuts(decaylength_cutPbPb,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut);
    tMC->loop(0);
    tMC->d_jet(Form("Files/myMCPbPbtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut));
  }

  if(doPPData){
    djet* tpp = new djet("/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/merged.root");
    tpp->SetJetPtCutEta(jetpt_cut,jetetamin_cut,jetetamax_cut);
    tpp->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
    tpp->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut);
    tpp->loop(1);
    tpp->d_jet(Form("Files/myDataPPtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut));
  }

  if(doPPMC){
    djet* tMCpp = new djet("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root");
    tMCpp->SetJetPtCutEta(jetpt_cut,jetetamin_cut,jetetamax_cut);
    tMCpp->SetDmesonPtMinMaxRapidity(Dptlow_cut,Dpthigh_cut,Dy_cut);
    tMCpp->SetDmesonCuts(decaylength_cut,Dalpha_cut,chi2cl_cut,trkptmin_cut,trketa_cut,trkpterr_cut); 
    tMCpp->loop(0);
    tMCpp->d_jet(Form("Files/myMCPPtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut));
  }
}

void runFit(int isPP=1,int intjetpt_cut=80, int intDptlow_cut=4,int intDpthigh_cut=999,int intjetetamin_cut=0,int intjetetamax_cut=2){
 
   djet* tempty = new djet("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root");
   const int nRedges=tempty->GetnRedges();
   double Redges[nRedges+1];
   for (int m=0;m<nRedges+1;m++) Redges[m]=tempty->GetRedgesEdges(m);

   const int nZedges=tempty->GetnZedges();
   double Zedges[nZedges+1];
   for (int m=0;m<nZedges+1;m++) Zedges[m]=tempty->GetZedgesEdges(m);

   static const int indexGenRecoMass=2;
   static const int indexBkgReflection=2;

   TString file,fileMC,output;
   
   if(isPP){
     file=Form("Files/myDataPPtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
     fileMC=Form("Files/myMCPPtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
     output=Form("Files/resultsPP_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
   }
   
   if(!isPP){
     file=Form("Files/myDataPbPbtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
     fileMC=Form("Files/myMCPbPbtest_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
     output=Form("Files/resultsPbPb_jet%d_Dlow%d_Dhigh%d_jetetamin%d_jetetamax%d.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut);
   }
 
   TH1F *hHistoMassData[nRedges][indexBkgReflection];
   TH1F *hHistoZMassData[nRedges][indexBkgReflection];

   TH1F *hHistoMassMC[nRedges][indexBkgReflection];
   TH1F* hHistoMassMCGenSignal[nRedges][indexBkgReflection];
   TH1F* hHistoMassMCGenSwapped[nRedges][indexBkgReflection];

   TH1F *hHistoZMassMC[nZedges][indexBkgReflection];
   TH1F* hHistoZMassMCGenSignal[nZedges][indexBkgReflection];
   TH1F* hHistoZMassMCGenSwapped[nZedges][indexBkgReflection];

   TH1F*hSignalData[indexBkgReflection];
   TH1F*hSignalZData[indexBkgReflection];
   TH1F*hSignalMC[indexBkgReflection];
   TH1F*hSignalZMC[indexBkgReflection];

   for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
     hSignalData[indexBkg]=new TH1F(Form("hSignalData_indexBkg%d",indexBkg),Form("hSignalData_indexBkg%d",indexBkg),nRedges,Redges);
     hSignalZData[indexBkg]=new TH1F(Form("hSignalZData_indexBkg%d",indexBkg),Form("hSignalData_indexBkg%d",indexBkg),nZedges,Zedges);
     hSignalMC[indexBkg]=new TH1F(Form("hSignalMC_indexBkg%d",indexBkg),Form("hSignalMC_indexBkg%d",indexBkg),nRedges,Redges);
     hSignalZMC[indexBkg]=new TH1F(Form("hSignalZMC_indexBkg%d",indexBkg),Form("hSignalData_indexBkg%d",indexBkg),nZedges,Zedges);
     hSignalData[indexBkg]->SetName(Form("hSignalData_indexBkg%d",indexBkg));
     hSignalMC[indexBkg]->SetName(Form("hSignalMC_indexBkg%d",indexBkg));
     hSignalZData[indexBkg]->SetName(Form("hSignalZData_indexBkg%d",indexBkg));
     hSignalZMC[indexBkg]->SetName(Form("hSignalZMC_indexBkg%d",indexBkg));
  }

   TFile* finput = new TFile(file.Data());
   TFile* finputMC = new TFile(fileMC.Data());

   Dfitter *fitData[nRedges][indexBkgReflection];   
   Dfitter *fitMC[nRedges][indexBkgReflection];   
   Dfitter *fitZData[nZedges][indexBkgReflection];
   Dfitter *fitZMC[nZedges][indexBkgReflection];

   TString canvasData;
   TString canvasMC;
  
   TH1F*hNjetsData=(TH1F*)finput->Get("hNjets");
   TH1F*hNjetsMC=(TH1F*)finputMC->Get("hNjets");
   hNjetsData->SetName("hNjetsData");
   hNjetsMC->SetName("hNjetsMC");
   
   for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
     for (int i=0;i<nRedges;i++){
       if (isPP){
         canvasData=Form("PlotsFits/DataPP/ResultsDataJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Rindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
         canvasMC=Form("PlotsFits/MCPP/ResultsMCJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Rindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
       } else {
         canvasData=Form("PlotsFits/DataPbPb/ResultsDataJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Rindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
         canvasMC=Form("PlotsFits/MCPbPb/ResultsMCJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Rindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
       }
       hHistoMassData[i][indexBkg]=(TH1F*)finput->Get(Form("fhHistoMass_indexGen0_R%d_indexBkg%d",i,indexBkg));
       hHistoMassMC[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhHistoMass_indexGen0_R%d_indexBkg%d",i,indexBkg));
       hHistoMassMCGenSignal[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhHistoGenSignal_indexGen0_R%d_indexBkg%d",i,indexBkg));
       hHistoMassMCGenSwapped[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhHistoGenSwapped_indexGen0_R%d_indexBkg%d",i,indexBkg));
       fitData[i][indexBkg]=new Dfitter(hHistoMassData[i][indexBkg],hHistoMassMCGenSignal[i][indexBkg],hHistoMassMCGenSwapped[i][indexBkg],canvasData);
       fitMC[i][indexBkg]=new Dfitter(hHistoMassMC[i][indexBkg],hHistoMassMCGenSignal[i][indexBkg],hHistoMassMCGenSwapped[i][indexBkg],canvasMC);
       hSignalData[indexBkg]->SetBinContent(i+1,fitData[i][indexBkg]->GetSignal()); 
       hSignalData[indexBkg]->SetBinError(i+1,fitData[i][indexBkg]->GetSignalError());
       hSignalMC[indexBkg]->SetBinContent(i+1,fitMC[i][indexBkg]->GetSignal());
       hSignalMC[indexBkg]->SetBinError(i+1,fitMC[i][indexBkg]->GetSignalError());


     }
     for (int i=0;i<nZedges;i++){
       if(isPP){
         canvasData=Form("PlotsFits/DataPP/ResultsDataJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Zindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
         canvasMC=Form("PlotsFits/MCPP/ResultsMCJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Zindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
       } else {
         canvasData=Form("PlotsFits/DataPbPb/ResultsDataJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Zindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
         canvasMC=Form("PlotsFits/MCPbPb/ResultsMCJetPt%d_Dptmin%d_Dptmax%d_jetetamin%d_jetetamax%d_isPP%d_Zindex%d_indexBkg%d",intjetpt_cut,intDptlow_cut,intDpthigh_cut,intjetetamin_cut,intjetetamax_cut,isPP,i,indexBkg);
       }
       hHistoZMassData[i][indexBkg]=(TH1F*)finput->Get(Form("fhHistoZMass_indexGen0_Z%d_indexBkg%d",i,indexBkg));
       hHistoZMassMC[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhHistoZMass_indexGen0_Z%d_indexBkg%d",i,indexBkg));
       hHistoZMassMCGenSignal[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhHistoZGenSignal_indexGen0_Z%d_indexBkg%d",i,indexBkg));
       hHistoZMassMCGenSwapped[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhHistoZGenSwapped_indexGen0_Z%d_indexBkg%d",i,indexBkg));
       fitZData[i][indexBkg]=new Dfitter(hHistoZMassData[i][indexBkg],hHistoZMassMCGenSignal[i][indexBkg],hHistoZMassMCGenSwapped[i][indexBkg],canvasData);
       fitZMC[i][indexBkg]=new Dfitter(hHistoZMassMC[i][indexBkg],hHistoZMassMCGenSignal[i][indexBkg],hHistoZMassMCGenSwapped[i][indexBkg],canvasMC); 
       hSignalZData[indexBkg]->SetBinContent(i+1,fitZData[i][indexBkg]->GetSignal());
       hSignalZData[indexBkg]->SetBinError(i+1,fitZData[i][indexBkg]->GetSignalError());
       hSignalZMC[indexBkg]->SetBinContent(i+1,fitZMC[i][indexBkg]->GetSignal());
       hSignalZMC[indexBkg]->SetBinError(i+1,fitZMC[i][indexBkg]->GetSignalError());
     }
   }

   TH1F*fhDenEfficiency[indexGenRecoMass][indexBkgReflection];
   TH1F*fhNumEfficiency[indexGenRecoMass][indexBkgReflection];
   TH1F*fhEfficiency[indexGenRecoMass][indexBkgReflection];
   TH1F*fhZDenEfficiency[indexGenRecoMass][indexBkgReflection];
   TH1F*fhZNumEfficiency[indexGenRecoMass][indexBkgReflection];
   TH1F*fhZEfficiency[indexGenRecoMass][indexBkgReflection];

   double normJetsDataReco=hNjetsData->GetBinContent(1);
   double normJetsMC[2];
   normJetsMC[0]=hNjetsMC->GetBinContent(1);
   normJetsMC[1]=hNjetsMC->GetBinContent(2);

   for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
     for (int i=0;i<indexGenRecoMass;i++){

       fhDenEfficiency[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhDenEfficiency_%d_indexBkg%d",i,indexBkg));
       fhNumEfficiency[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhNumEfficiency_%d_indexBkg%d",i,indexBkg));
       fhEfficiency[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhEfficiency_%d_indexBkg%d",i,indexBkg));
       fhZDenEfficiency[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhZDenEfficiency_%d_indexBkg%d",i,indexBkg));
       fhZNumEfficiency[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhZNumEfficiency_%d_indexBkg%d",i,indexBkg));
       fhZEfficiency[i][indexBkg]=(TH1F*)finputMC->Get(Form("fhZEfficiency_%d_indexBkg%d",i,indexBkg));
       divideBinWidth(fhDenEfficiency[i][indexBkg]);
       divideBinWidth(fhNumEfficiency[i][indexBkg]);
       divideBinWidth(fhZDenEfficiency[i][indexBkg]);
       divideBinWidth(fhZNumEfficiency[i][indexBkg]);
       fhNumEfficiency[i][indexBkg]->Scale(1/normJetsMC[i]);
       fhDenEfficiency[i][indexBkg]->Scale(1/normJetsMC[i]);
       fhZNumEfficiency[i][indexBkg]->Scale(1/normJetsMC[i]);
       fhZDenEfficiency[i][indexBkg]->Scale(1/normJetsMC[i]);
     }
   }

   for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
       divideBinWidth(hSignalMC[indexBkg]);
       divideBinWidth(hSignalData[indexBkg]);
       divideBinWidth(hSignalZMC[indexBkg]);
       divideBinWidth(hSignalZData[indexBkg]);
       hSignalMC[indexBkg]->Scale(1/normJetsMC[0]);
       hSignalData[indexBkg]->Scale(1/normJetsDataReco);
       hSignalZMC[indexBkg]->Scale(1/normJetsMC[0]);
       hSignalZData[indexBkg]->Scale(1/normJetsDataReco);
   }


  TFile* foutput = new TFile(output.Data(),"recreate");
  for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
    for (int i=0;i<indexGenRecoMass;i++){
     fhDenEfficiency[i][indexBkg]->Write();
     fhNumEfficiency[i][indexBkg]->Write();
     fhEfficiency[i][indexBkg]->Write();
     fhZNumEfficiency[i][indexBkg]->Write();
     fhZDenEfficiency[i][indexBkg]->Write();
     fhZEfficiency[i][indexBkg]->Write();
    }
  }
  for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
    hSignalMC[indexBkg]->Write();
    hSignalData[indexBkg]->Write();
    hSignalZMC[indexBkg]->Write();
    hSignalZData[indexBkg]->Write();
  }
  hNjetsData->Write();
  hNjetsMC->Write();
  foutput->Close();

}



