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



void studySigma_plothist(TString inputnameData="rootfiles/xsec_pp_Data", TString inputnameMC="rootfiles/xsec_pp_MC", TString collisionsyst="pp",TString label="")
{
  xjjroot::setgstyle();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  Int_t ispp = collisionsyst=="pp"?1:0;

  TFile* infData = new TFile(Form("%s.root",inputnameData.Data()));
  TFile* infMC = new TFile(Form("%s.root",inputnameMC.Data()));
  
  TH1F*ahHistoSigmaPtData=(TH1F*)infData->Get("ahHistoSigmaPt");
  TH1F*ahHistoSigmaPtMC=(TH1F*)infMC->Get("ahHistoSigmaPt");
  TH1F*ahHistoSigmaYData=(TH1F*)infData->Get("ahHistoSigmaY");
  TH1F*ahHistoSigmaYMC=(TH1F*)infMC->Get("ahHistoSigmaY");
  TH1F*ahHistoMeanPtData=(TH1F*)infData->Get("ahHistoMeanPt");
  TH1F*ahHistoMeanPtMC=(TH1F*)infMC->Get("ahHistoMeanPt");
  TH1F*ahHistoMeanYData=(TH1F*)infData->Get("ahHistoMeanY");
  TH1F*ahHistoMeanYMC=(TH1F*)infMC->Get("ahHistoMeanY");
  TH1F*hDmesonYData=(TH1F*)infData->Get("hDmesonY");
  TH1F*hDmesonYMC=(TH1F*)infMC->Get("hDmesonY");
  TH1F*hDmesonYPthatData=(TH1F*)infData->Get("hDmesonYPthat");
  TH1F*hDmesonYPthatMC=(TH1F*)infMC->Get("hDmesonYPthat");

  Float_t ypaddiv = 1./2, yPullpaddiv = 1-ypaddiv;
  TCanvas* c = new TCanvas("c", "", 1500, 1000);
  c->Divide(3,2);
  c->cd(1);
  TH2F* hempty = new TH2F("hempty", ";rapidity;#sigma (GeV)", 10, -3, 3, 10, 0.,0.1);
  hempty->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hempty, 0, 0.3);
  hempty->Draw();
  xjjroot::setthgrstyle(ahHistoSigmaYData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoSigmaYMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoSigmaYData->Draw("same");
  ahHistoSigmaYMC->Draw("same");
  c->cd(2);
  TH2F* hemptyPt = new TH2F("hemptyPt", ";p_{T} (GeV) ;#sigma (GeV)", 10, 0, 100, 10, 0.,0.1);
  hemptyPt->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPt, 0, 0.3);
  hemptyPt->Draw();
  xjjroot::setthgrstyle(ahHistoSigmaPtData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoSigmaPtMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoSigmaPtData->Draw("same");
  ahHistoSigmaPtMC->Draw("same");
  c->cd(3);
  TH2F* hemptyMean = new TH2F("hemptyMean", ";rapidity;#mu (GeV)", 10, -3, 3, 10, 1.84,1.89);
  hemptyMean->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyMean, 0, 0.3);
  hemptyMean->Draw();
  xjjroot::setthgrstyle(ahHistoMeanYData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoMeanYMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoMeanYData->Draw("same");
  ahHistoMeanYMC->Draw("same");
  c->cd(4);
  TH2F* hemptyMeanPt = new TH2F("hemptyMeanPt", ";p_{T} (GeV) ;#mu (GeV)", 10, 0, 100, 10, 1.84,1.89);
  hemptyMeanPt->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyMeanPt, 0, 0.3);
  hemptyMeanPt->Draw();
  xjjroot::setthgrstyle(ahHistoMeanPtData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoMeanPtMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoMeanPtData->Draw("same");
  ahHistoMeanPtMC->Draw("same");
   c->cd(5);
  TH2F* hemptyY= new TH2F("hemptyY", ";rapidity; entries", 10, -3, 3, 10, 0.,0.05);
  hemptyY->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyY, 0, 0.3);
  hemptyY->Draw();
  hDmesonYMC->Scale(1./hDmesonYMC->GetEntries());
  hDmesonYData->Scale(1./hDmesonYData->GetEntries());
  xjjroot::setthgrstyle(hDmesonYData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(hDmesonYMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  hDmesonYData->Draw("same");
  hDmesonYMC->Draw("same");
  /*
   c->cd(6);
  TH2F* hemptyYPthat= new TH2F("hemptYPthatY", ";rapidity pthat; entries", 10, -3, 3, 10, 0.,1);
  hemptyYPthat->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyYPthat, 0, 0.3);
  hemptyYPthat->Draw();
  hDmesonYPthatMC->Scale(1./hDmesonYPthatMC->Integral());
  hDmesonYPthatData->Scale(1./hDmesonYPthatData->Integral());
  xjjroot::setthgrstyle(hDmesonYPthatData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(hDmesonYPthatMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  hDmesonYPthatData->Draw("same");
  hDmesonYPthatMC->Draw("same");
  */

  c->SaveAs(Form("plotsSigma/canvasMeanSigma%s.png",label.Data()));
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

