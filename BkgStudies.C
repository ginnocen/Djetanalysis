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

  TFile* finputPP = new TFile(Form("resultsPP_jet%d_Dlow%d_Dhigh%d_genIndex0_indexBkg0.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
  TFile* finputPPBkg= new TFile(Form("resultsPP_jet%d_Dlow%d_Dhigh%d_genIndex0_indexBkg1.root",intjetpt_cut,intDptlow_cut,intDpthigh_cut));
  
  TH1F*hSignalDataPPBkg=(TH1F*)finputPPBkg->Get("hSignalData");
  TH1F*hSignalDataPP=(TH1F*)finputPP->Get("hSignalData");


  hSignalDataPPBkg->Divide(hSignalDataPP);
  hSignalDataPPBkg->Draw();

}

