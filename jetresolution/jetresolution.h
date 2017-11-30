#ifndef _JETRESOLUTION_H_
#define _JETRESOLUTION_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/paramCorr.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TF1.h>

Float_t jtptBins[] = {30, 40, 50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 250, 300};
const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;
Float_t jtetaBins[] = {0, 1.0, 1.6};
const int nJtetaBins = sizeof(jtetaBins)/sizeof(jtetaBins[0])-1;
Color_t jtetaColor[] = {kBlack, kBlue, kRed+2};
Float_t centBins[] = {0, 30, 100};
const int NCentBins = sizeof(centBins)/sizeof(centBins[0])-1;
int nCentBins = 0;
void setnCentBins(Int_t ispp) {nCentBins = ispp?1:NCentBins;}
Float_t xrangeAng;
void setxrangeAng(Int_t ispp) {xrangeAng = ispp?0.05:0.08;}

void init(Int_t ispp) {setnCentBins(ispp); setxrangeAng(ispp);}

TH1F* ahHistoResoPt[NCentBins][nJtetaBins+1][nJtptBins];
TH1F* ahHistoResoPtCorr[NCentBins][nJtetaBins+1][nJtptBins];
TH1F* ahHistoResoPhi[NCentBins][nJtetaBins+1][nJtptBins];
TH1F* ahHistoResoEta[NCentBins][nJtetaBins+1][nJtptBins];

TH1F* hScalePt[NCentBins][nJtetaBins+1];
TH1F* hScalePtCorr[NCentBins][nJtetaBins+1];
TH1F* hScalePhi[NCentBins][nJtetaBins+1];
TH1F* hScaleEta[NCentBins][nJtetaBins+1];
TH1F* hResoPt[NCentBins][nJtetaBins+1];
TH1F* hResoPtCorr[NCentBins][nJtetaBins+1];
TH1F* hResoPhi[NCentBins][nJtetaBins+1];
TH1F* hResoEta[NCentBins][nJtetaBins+1];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              for(int i=0;i<nJtptBins;i++)
                {
                  ahHistoResoPt[k][j][i] = new TH1F(Form("hHistoResoPt_%d_%d_%d",k,j,i), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
                  ahHistoResoPt[k][j][i]->Sumw2();
                  ahHistoResoPtCorr[k][j][i] = new TH1F(Form("hHistoResoPtCorr_%d_%d_%d",k,j,i), ";p_{T}^{reco} / p_{T}^{gen}, Corr;", 50, 0, 2);
                  ahHistoResoPtCorr[k][j][i]->Sumw2();
                  ahHistoResoPhi[k][j][i] = new TH1F(Form("hHistoResoPhi_%d_%d_%d",k,j,i), ";#phi^{reco} - #phi^{gen};", 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoPhi[k][j][i]->Sumw2();
                  ahHistoResoEta[k][j][i] = new TH1F(Form("hHistoResoEta_%d_%d_%d",k,j,i), ";#eta^{reco} - #eta^{gen};", 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoEta[k][j][i]->Sumw2();
                }
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              hResoPt[k][j] = new TH1F(Form("hResoPt_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen})", nJtptBins, jtptBins);
              hResoPtCorr[k][j] = new TH1F(Form("hResoPtCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), Corr", nJtptBins, jtptBins);
              hResoPhi[k][j] = new TH1F(Form("hResoPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", nJtptBins, jtptBins);
              hResoEta[k][j] = new TH1F(Form("hResoEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", nJtptBins, jtptBins);
              hScalePt[k][j] = new TH1F(Form("hScalePt_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nJtptBins, jtptBins);
              hScalePtCorr[k][j] = new TH1F(Form("hScalePtCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", nJtptBins, jtptBins);
              hScalePhi[k][j] = new TH1F(Form("hScalePhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nJtptBins, jtptBins);
              hScaleEta[k][j] = new TH1F(Form("hScaleEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nJtptBins, jtptBins);
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for createhists()"<<std::endl;
  return 1;
}

int gethists(TFile* inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="usehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              for(int i=0;i<nJtptBins;i++)
                {
                  ahHistoResoPt[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPt_%d_%d_%d",k,j,i));
                  ahHistoResoPtCorr[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPtCorr_%d_%d_%d",k,j,i));
                  ahHistoResoPhi[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPhi_%d_%d_%d",k,j,i));
                  ahHistoResoEta[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoEta_%d_%d_%d",k,j,i));
                }
            }
        }
      return 0;
    }
  if(opt=="plothist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              hResoPt[k][j] = (TH1F*)inf->Get(Form("hResoPt_%d_%d",k,j));
              hResoPtCorr[k][j] = (TH1F*)inf->Get(Form("hResoPtCorr_%d_%d",k,j));
              hResoPhi[k][j] = (TH1F*)inf->Get(Form("hResoPhi_%d_%d",k,j));
              hResoEta[k][j] = (TH1F*)inf->Get(Form("hResoEta_%d_%d",k,j));
              hScalePt[k][j] = (TH1F*)inf->Get(Form("hScalePt_%d_%d",k,j));
              hScalePtCorr[k][j] = (TH1F*)inf->Get(Form("hScalePtCorr_%d_%d",k,j));
              hScalePhi[k][j] = (TH1F*)inf->Get(Form("hScalePhi_%d_%d",k,j));
              hScaleEta[k][j] = (TH1F*)inf->Get(Form("hScaleEta_%d_%d",k,j));
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}

int writehists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              for(int i=0;i<nJtptBins;i++)
                {
                  ahHistoResoPt[k][j][i]->Write();
                  ahHistoResoPtCorr[k][j][i]->Write();
                  ahHistoResoPhi[k][j][i]->Write();
                  ahHistoResoEta[k][j][i]->Write();
                }
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              hResoPt[k][j]->Write();
              hResoPtCorr[k][j]->Write();
              hResoPhi[k][j]->Write();
              hResoEta[k][j]->Write();
              hScalePt[k][j]->Write();
              hScalePtCorr[k][j]->Write();
              hScalePhi[k][j]->Write();
              hScaleEta[k][j]->Write();
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
