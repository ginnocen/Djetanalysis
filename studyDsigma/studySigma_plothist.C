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
  TH1F*ahHistoMeanPtData=(TH1F*)infData->Get("ahHistoMeanPt");
  TH1F*ahHistoSigmaYData=(TH1F*)infData->Get("ahHistoSigmaY");
  TH1F*ahHistoMeanYData=(TH1F*)infData->Get("ahHistoMeanY");
  TH1F*ahHistoSignalYData=(TH1F*)infData->Get("ahHistoSignalY");
  TH1F*ahHistoSignalPtData=(TH1F*)infData->Get("ahHistoSignalPt");

  TH1F*ahHistoSigmaPtMC=(TH1F*)infMC->Get("ahHistoSigmaPt");
  TH1F*ahHistoMeanPtMC=(TH1F*)infMC->Get("ahHistoMeanPt");
  TH1F*ahHistoSigmaYMC=(TH1F*)infMC->Get("ahHistoSigmaY");
  TH1F*ahHistoMeanYMC=(TH1F*)infMC->Get("ahHistoMeanY");
  TH1F*ahHistoSignalYMC=(TH1F*)infMC->Get("ahHistoSignalY");
  TH1F*ahHistoSignalPtMC=(TH1F*)infMC->Get("ahHistoSignalPt");
  
  TH1F*hDmesonYData=(TH1F*)infData->Get("hDmesonY");
  TH1F*hDmesonYMC=(TH1F*)infMC->Get("hDmesonY");

  Float_t ypaddiv = 1./2, yPullpaddiv = 1-ypaddiv;
  TCanvas* c = new TCanvas("c", "", 1500, 1000);
  c->Divide(4,2);
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
  TH2F* hemptyY= new TH2F("hemptyY", ";rapidity; entries all candidates", 10, -3, 3, 10, 0.,0.05);
  hemptyY->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyY, 0, 0.3);
  hemptyY->Draw();
  hDmesonYMC->Scale(1./hDmesonYMC->GetEntries());
  hDmesonYData->Scale(1./hDmesonYData->GetEntries());
  xjjroot::setthgrstyle(hDmesonYData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(hDmesonYMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  hDmesonYData->Draw("same");
  hDmesonYMC->Draw("same");
   c->cd(6);
  TH2F* hemptySignalY= new TH2F("hemptySignalY", ";rapidity; entries signal", 10, -3, 3, 10, 0.,0.3);
  hemptySignalY->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptySignalY, 0, 0.3);
  hemptySignalY->Draw();
  double normData=ahHistoSignalYData->Integral();
  double normMC=ahHistoSignalYMC->Integral();
  std::cout<<normData<<std::endl;
  std::cout<<normMC<<std::endl;
  ahHistoSignalYMC->Scale(1./normMC);
  ahHistoSignalYData->Scale(1./normData);
  xjjroot::setthgrstyle(ahHistoSignalYData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoSignalYMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoSignalYData->Draw("same");
  ahHistoSignalYMC->Draw("same");
   c->cd(7);
  TH2F* hemptySignalPt= new TH2F("hemptySignalPt", ";pt; entries signal", 10, 0,100, 10, 0.,1);
  hemptySignalPt->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptySignalPt, 0, 0.3);
  hemptySignalPt->Draw();
  normData=ahHistoSignalPtData->Integral();
  normMC=ahHistoSignalPtMC->Integral();
  std::cout<<normData<<std::endl;
  std::cout<<normMC<<std::endl;
  ahHistoSignalPtMC->Scale(1./normMC);
  ahHistoSignalPtData->Scale(1./normData);
  xjjroot::setthgrstyle(ahHistoSignalPtData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoSignalPtMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoSignalPtData->Draw("same");
  ahHistoSignalPtMC->Draw("same");

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

