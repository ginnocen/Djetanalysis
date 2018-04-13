#include <iostream>
#include <iomanip>
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/dfitter.h"
#include "../includes/djet.h"
#include "../includes/djtweight.h"
#include <TGraphAsymmErrors.h> 
#include <TFile.h>
#include <TCanvas.h>
#include <TH2F.h>
#include <TF1.h>
#include <TString.h>

  
int const nptBins=5;
Float_t ptBins[nptBins+1] = {4., 10., 20., 40., 60., 100.};

int const nyBins=8;
Float_t yBins[nyBins+1] = {-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0};

TH1F* ahHistoMassPt[nptBins];
TH1F* ahHistoMassPtSignal[nptBins];
TH1F* ahHistoMassPtSwapped[nptBins];
TH1F* ahHistoMassY[nyBins];
TH1F* ahHistoMassYSignal[nyBins];
TH1F* ahHistoMassYSwapped[nyBins];

const int nsample=2;
const int nvariables=3;
TString variablename[nvariables]={"Mean","Sigma","Signal"};
TString variablelabel[nvariables]={"#mu","#sigma","signal"};
TString samplename[nsample]={"Data","MC"};

TH1F* ahHistoPt[nvariables];
TH1F* ahHistoY[nvariables];
TH1F* ahHistoPtMCData[nsample][nvariables];
TH1F* ahHistoYMCData[nsample][nvariables];

TH1F* hDmesonY;
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
     hDmesonY = new TH1F("hDmesonY", ";rapidity;Entries",60,-3.,3.);

    for(int j=0;j<nptBins;j++) {
      ahHistoMassPt[j] = new TH1F(Form("ahHistoMassPt_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassPt[j]->Sumw2();
      ahHistoMassPtSignal[j] = new TH1F(Form("ahHistoMassPtSignal_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassPtSignal[j]->Sumw2();
      ahHistoMassPtSwapped[j] = new TH1F(Form("ahHistoMassPtSwapped_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassPtSwapped[j]->Sumw2();
    }
    for(int j=0;j<nyBins;j++) {
      ahHistoMassY[j] = new TH1F(Form("ahHistoMassY_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassY[j]->Sumw2();
      ahHistoMassYSignal[j] = new TH1F(Form("ahHistoMassYSignal_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassYSignal[j]->Sumw2();
      ahHistoMassYSwapped[j] = new TH1F(Form("ahHistoMassYSwapped_%d",j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
      ahHistoMassYSwapped[j]->Sumw2();
    }
   return 0;
  }
  if(opt=="usehist"){
  for (int i=0;i<nvariables;i++){
    ahHistoPt[i]=new TH1F(Form("ahHisto%sPt",variablename[i].Data()), Form(";p_{T} (GeV/c); %s",variablelabel[i].Data()), nptBins, ptBins);
    ahHistoY[i]=new TH1F(Form("ahHisto%sY",variablename[i].Data()), Form(";rapidity; %s",variablelabel[i].Data()), nyBins, yBins);
  }
   return 0;
  }

}

int writehists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int j=0;j<nptBins;j++) {
      ahHistoMassPt[j]->Write();
      ahHistoMassPtSignal[j]->Write();
      ahHistoMassPtSwapped[j]->Write();
      }
      for(int j=0;j<nyBins;j++) {
      ahHistoMassY[j]->Write();
      ahHistoMassYSignal[j]->Write();
      ahHistoMassYSwapped[j]->Write();
      }
     hDmesonY->Write();

      return 0;
    }
  if(opt=="usehist"){
  
    for (int i=0;i<nvariables;i++){
    ahHistoPt[i]->Write();
    ahHistoY[i]->Write();
  }
    hDmesonY->Write();
    return 0;
  }

  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

int gethists(TFile* inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="hist"){
    for(int j=0;j<nptBins;j++) {
      ahHistoMassPt[j] = (TH1F*)inf->Get(Form("ahHistoMassPt_%d",j));
    }
    for(int j=0;j<nyBins;j++) {
      ahHistoMassY[j] = (TH1F*)inf->Get(Form("ahHistoMassY_%d",j));
    }
    hDmesonY = (TH1F*)inf->Get("hDmesonY");
    return 0;
    }
    
  if(opt=="tpl"){
    for(int j=0;j<nptBins;j++) {
      ahHistoMassPtSignal[j] = (TH1F*)inf->Get(Form("ahHistoMassPtSignal_%d",j));
      ahHistoMassPtSwapped[j] = (TH1F*)inf->Get(Form("ahHistoMassPtSwapped_%d",j));
    }
    for(int j=0;j<nyBins;j++) {
      ahHistoMassYSignal[j] = (TH1F*)inf->Get(Form("ahHistoMassYSignal_%d",j));
      ahHistoMassYSwapped[j] = (TH1F*)inf->Get(Form("ahHistoMassYSwapped_%d",j));
    }
    return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

