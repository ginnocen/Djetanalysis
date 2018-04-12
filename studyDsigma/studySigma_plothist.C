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

  Float_t ypaddiv = 1./2, yPullpaddiv = 1-ypaddiv;
  TCanvas* c = new TCanvas("c", "", 1000, 500);
  c->Divide(2,1);
  c->cd(1);
  TH2F* hempty = new TH2F("hempty", ";;", 10, -3, 3, 10, 0.,0.1);
  hempty->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hempty, 0, 0.3);
  hempty->Draw();
  xjjroot::setthgrstyle(ahHistoSigmaYData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoSigmaYMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoSigmaYData->Draw("same");
  ahHistoSigmaYMC->Draw("same");
  c->cd(2);
  TH2F* hemptyPt = new TH2F("hemptyPt", ";;", 10, 0, 100, 10, 0.,0.1);
  hemptyPt->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hempty, 0, 0.3);
  hemptyPt->Draw();
  xjjroot::setthgrstyle(ahHistoSigmaPtData, 1, 1, 1.2, 1, 1, 1, -1, -1, -1);
  xjjroot::setthgrstyle(ahHistoSigmaPtMC, 2, 1, 1.2, 2, 1, 1, -1, -1, -1);
  ahHistoSigmaPtData->Draw("same");
  ahHistoSigmaPtMC->Draw("same");
  c->SaveAs(Form("plotsSigma/canvasSigma%s",label.Data()));
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

