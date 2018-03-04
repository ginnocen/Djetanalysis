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
//resultsPP_jet80_Dlow4_Dhigh999_genIndex0_indexBkg0.root:
void BkgStudies(int intjetpt_cut=80, int intDptlow_cut=4,int intDpthigh_cut=999){


   static const int nRedges=5;
   double Redges[nRedges+1]={0.,0.05,0.1,0.2,0.3,0.5};     //different R ranges
   double Area[nRedges+1];
   for (int i=0;i<nRedges;i++){
     Area[i]=(Redges[i+1]-Redges[i])*(Redges[i+1]-Redges[i])*3.14;
     cout<<"area="<<Area[i]<<endl;
   }


  TFile* finputPP = new TFile(Form("resultsPP_jet%d_Dlow%d_Dhigh%d_genIndex0_indexBkg0.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
  TFile* finputPPBkg= new TFile(Form("resultsPP_jet%d_Dlow%d_Dhigh%d_genIndex0_indexBkg1.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
  
  TH1F*hSignalDataPPBkg=(TH1F*)finputPPBkg->Get("hSignalData");
  TH1F*hSignalDataPP=(TH1F*)finputPP->Get("hSignalData");

  //hSignalDataPPBkg->Divide(hSignalDataPP);
  for (int i=0;i<nRedges;i++){
    hSignalDataPPBkg->SetBinContent(i+1,hSignalDataPPBkg->GetBinContent(i+1)/Area[i]);
    hSignalDataPPBkg->SetBinError(i+1,hSignalDataPPBkg->GetBinError(i+1)/Area[i]);
  }
  hSignalDataPPBkg->Draw();

}

