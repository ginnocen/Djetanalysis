#include "../includes/xjjrootuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include "studySigma.h"


void studySigma_plothist(TString inputnameData="rootfiles/xsec_pp_Data", TString inputnameMC="rootfiles/xsec_pp_MC", TString collisionsyst="pp",TString label="")
{
  xjjroot::setgstyle();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  int mycolors_sample[2]={1,2};
  
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  
  if(createhists("usehist")) return;
  
  TFile* infData = new TFile(Form("%s.root",inputnameData.Data()));
  TFile* infMC = new TFile(Form("%s.root",inputnameMC.Data()));
  if(!infData->IsOpen()) return;
  if(!infMC->IsOpen()) return;
  if(gethistsDataMC(infData,infMC, "plothist")) return;
  
  TH1F*hDmesonYData=(TH1F*)infData->Get("hDmesonY");
  TH1F*hDmesonYMC=(TH1F*)infMC->Get("hDmesonY");

   TH2F* hempty[6];
   hempty[0]= new TH2F("hempty0", ";p_{T};#mu (GeV)", 10, 0, 100, 10, 1.8,1.9);
   hempty[1]= new TH2F("hempty1", ";p_{T};#sigma (GeV)", 10, 0, 100, 10, 0.,0.1);
   hempty[2]= new TH2F("hempty2", ";p_{T};signal", 10, 0, 100, 10, 0.,1);
   hempty[3]= new TH2F("hempty3", ";rapidity;#mu (GeV)", 10, -3, 3, 10, 1.8,1.9);
   hempty[4]= new TH2F("hempty4", ";rapidity;#sigma (GeV)", 10, -3, 3, 10, 0.,0.1);
   hempty[5]= new TH2F("hempty5", ";rapidity;signal", 10, -3, 3, 10, 0.,1);

   TH2F* hemptyRatio[6];
   hemptyRatio[0]= new TH2F("hemptyRatio0", ";p_{T};#mu Data/MC", 10, 0, 100, 10, 0.9,1.1);
   hemptyRatio[1]= new TH2F("hemptyRatio1", ";p_{T};#sigma Data/MC", 10, 0, 100, 10, 0.,2);
   hemptyRatio[2]= new TH2F("hemptyRatio2", ";p_{T};signal Data/MC", 10, 0, 100, 10, 0.,2);
   hemptyRatio[3]= new TH2F("hemptyRatio3", ";rapidity;#mu Data/MC", 10, -3, 3, 10, 0.9,1.1);
   hemptyRatio[4]= new TH2F("hemptyRatio4", ";rapidity;#sigma Data/MC", 10, -3, 3, 10, 0.,2);
   hemptyRatio[5]= new TH2F("hemptyRatio5", ";rapidity;signal Data/MC", 10, -3, 3, 10, 0.,2);

  TLatex *texData = new TLatex(30,1.85,"Data");
   texData->SetTextColor(mycolors_sample[0]);
   texData->SetTextAlign(22); texData->SetTextSize(0.1);
  TLatex *texMC = new TLatex(60,1.85,"MC");
   texMC->SetTextColor(mycolors_sample[1]);
   texMC->SetTextAlign(22); texMC->SetTextSize(0.1);

  TLegend* leg = new TLegend(0.53, 0.88, 0.85, 0.88);
  xjjroot::setleg(leg);

  TCanvas* c= new TCanvas("c", "", 1500, 1000);
  c->Divide(3,2);
  for (int i=0;i<3;i++){
    c->cd(i+1);
    hempty[i]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hempty[i], 0, 0.3);
    hempty[i]->Draw();
    xjjroot::setthgrstyle(ahHistoPtsample[i][0], mycolors_sample[0], 1, 1.2, mycolors_sample[0], 1, 1, -1, -1, -1);
    xjjroot::setthgrstyle(ahHistoPtsample[i][1], mycolors_sample[1], 1, 1.2, mycolors_sample[1], 1, 1, -1, -1, -1);
    ahHistoPtsample[i][0]->Draw("same");
    ahHistoPtsample[i][1]->Draw("same");
    texData->Draw();
    texMC->Draw();
  }
  for (int i=0;i<3;i++){
    c->cd(i+4);
    hempty[i+3]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hempty[i+3], 0, 0.3);
    hempty[i+3]->Draw();
    xjjroot::setthgrstyle(ahHistoYsample[i][0], mycolors_sample[0], 1, 1.2, mycolors_sample[0], 1, 1, -1, -1, -1);
    xjjroot::setthgrstyle(ahHistoYsample[i][1], mycolors_sample[1], 1, 1.2, mycolors_sample[1], 1, 1, -1, -1, -1);
    ahHistoYsample[i][0]->Draw("same");
    ahHistoYsample[i][1]->Draw("same");
  }
  c->SaveAs(Form("plotsSigma/canvasMeanSigma%s.png",label.Data()));


  TCanvas* cRatio = new TCanvas("cRatio", "", 1500, 1000);
  cRatio->Divide(3,2);
  for (int i=0;i<3;i++){
    cRatio->cd(i+1);
    hemptyRatio[i]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hemptyRatio[i], 0, 0.3);
    hemptyRatio[i]->Draw();
    xjjroot::setthgrstyle(ahRatioPtDataOverMC[i], 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
    ahRatioPtDataOverMC[i]->Draw("same");
  }
  for (int i=0;i<3;i++){
    cRatio->cd(i+4);
    hemptyRatio[i+3]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hemptyRatio[i+3], 0, 0.3);
    hemptyRatio[i+3]->Draw();
    xjjroot::setthgrstyle(ahRatioYDataOverMC[i], 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
    ahRatioYDataOverMC[i]->Draw("same");
  }
  cRatio->SaveAs(Form("plotsSigma/cRatioanvasMeanSigma%s.png",label.Data()));

}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      studySigma_plothist(argv[1], argv[2], argv[3],argv[4]);
      return 0;
    }
  std::cout<<"  Error: invalid arguments number - studySigma_plothist()"<<std::endl;
  return 1;
}

int arguerr(TString collisionsyst)
{
  if(collisionsyst!="pp" && collisionsyst!="PbPb")
    {
      std::cout<<"error: invalid collisionsyst"<<std::endl;
      return 1;
    }
  return 0;
}

