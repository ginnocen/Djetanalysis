
#include "../utilitiesturnonstudy.h"


void fitTurnOn(TString mystring="gL1efficiencyppHLT40pp"){


  TGraphAsymmErrors *gEff;  
  TString suffixfile="../foutputTurnSelectionOnL1HLTprescale.root";
  TFile*finput=new TFile(suffixfile.Data(),"read");
  finput->cd();
  gEff=(TGraphAsymmErrors*)finput->Get(mystring.Data());
  TH1F*hempty=new TH1F("hempty","hempty",1000,0,1000);
  TF1 *fL1=new TF1("fL1","[3]*TMath::Erf(x*[1]+[2])*0.5*(1-[0])+0.5*(1+[0])",0,1000);
  fL1->SetParameters(7.0734e-2,6.76907e-2,-2.31850,1.); 
  hempty->Draw();
  gEff->Draw("same");
  gEff->Fit("fL1","M0",0,150); 
  fL1->Draw("same");
  //delete gEff;
  //delete fL1;
    
  }
