#ifndef _JETRESOLUTION_H_
#define _JETRESOLUTION_H_

#include "RtypesCore.h"
Float_t resojtptBins[] = {10, 20, 30, 40, 50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 250, 300};
const int nResoJtptBins = sizeof(resojtptBins)/sizeof(resojtptBins[0])-1;
#define _RESOJTPTBINS
Float_t resodeltajtptBins[] = {10, 30, 50, 70, 100, 140, 200, 300};
const int nResoDeltaJtptBins = sizeof(resodeltajtptBins)/sizeof(resodeltajtptBins[0])-1;
#define _RESODELTAJTPTBINS
Float_t resojtdrBins[] = {0, 0.01, 0.03, 0.05, 0.10, 0.30, 0.50, 0.70};
const int nResoJtdrBins = sizeof(resojtdrBins)/sizeof(resojtdrBins[0])-1;
#define _RESOJTDRBINS

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
#include <TColor.h>
#include <TRandom3.h>

Float_t mapjtptBins[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
const int nMapjtptBins = sizeof(mapjtptBins)/sizeof(mapjtptBins[0])-1;
Float_t jtetaBins[] = {0, 1.0, 1.6};
const int nJtetaBins = sizeof(jtetaBins)/sizeof(jtetaBins[0])-1;
Color_t jtetaColor[] = {kBlack, kBlue, kRed+2};

Float_t xrangeAng;
void setxrangeAng(Int_t ispp) {xrangeAng = ispp?0.05:0.08;} // 0.05:0.08

void init(Int_t ispp) {setnCentBins(ispp); setxrangeAng(ispp);}

TH1F* ahHistoResoPt[NCentBins][nJtetaBins+1][nResoJtptBins];
TH1F* ahHistoResoPtCorr[NCentBins][nJtetaBins+1][nResoJtptBins];
TH1F* ahHistoResoPtRMatGCorr[NCentBins][nJtetaBins+1][nResoJtptBins];
TH1F* ahHistoResoPtFfCorr[NCentBins][nJtetaBins+1][nResoJtptBins];
TH1F* ahHistoResoPtFfJecCorr[NCentBins][nJtetaBins+1][nResoJtptBins];
TH1F* ahHistoResoPhi[NCentBins][nJtetaBins+1][nResoJtptBins];
TH1F* ahHistoResoEta[NCentBins][nJtetaBins+1][nResoJtptBins];
TH2F* ahHistoResoEtaPhi[NCentBins][nJtetaBins+1][nResoJtptBins];

TH1F* ahHistoResoDrPhi[NCentBins][nJtetaBins+1][nResoJtdrBins];
TH1F* ahHistoResoDrEta[NCentBins][nJtetaBins+1][nResoJtdrBins];
TH2F* ahHistoResoDrEtaPhi[NCentBins][nJtetaBins+1][nResoJtdrBins];

TH1F* ahHistoResoRecoDeltaPhi[NCentBins][nJtetaBins+1][nResoDeltaJtptBins];
TH1F* ahHistoResoRecoDeltaEta[NCentBins][nJtetaBins+1][nResoDeltaJtptBins];
TH1F* ahHistoResoGenDeltaPhi[NCentBins][nJtetaBins+1][nResoDeltaJtptBins];
TH1F* ahHistoResoGenDeltaEta[NCentBins][nJtetaBins+1][nResoDeltaJtptBins];

TH1F* hScalePt[NCentBins][nJtetaBins+1];
TH1F* hScalePtCorr[NCentBins][nJtetaBins+1];
TH1F* hScalePtRMatGCorr[NCentBins][nJtetaBins+1];
TH1F* hScalePtFfCorr[NCentBins][nJtetaBins+1];
TH1F* hScalePtFfJecCorr[NCentBins][nJtetaBins+1];
TH1F* hScalePhi[NCentBins][nJtetaBins+1];
TH1F* hScaleEta[NCentBins][nJtetaBins+1];
TH1F* hResoPt[NCentBins][nJtetaBins+1];
TH1F* hResoPtCorr[NCentBins][nJtetaBins+1];
TH1F* hResoPtRMatGCorr[NCentBins][nJtetaBins+1];
TH1F* hResoPtFfCorr[NCentBins][nJtetaBins+1];
TH1F* hResoPtFfJecCorr[NCentBins][nJtetaBins+1];
TH1F* hResoPhi[NCentBins][nJtetaBins+1];
TH1F* hResoEta[NCentBins][nJtetaBins+1];

TH1F* hScaleDrPhi[NCentBins][nJtetaBins+1];
TH1F* hScaleDrEta[NCentBins][nJtetaBins+1];
TH1F* hResoDrPhi[NCentBins][nJtetaBins+1];
TH1F* hResoDrEta[NCentBins][nJtetaBins+1];

TH1F* hScaleRecoDeltaPhi[NCentBins][nJtetaBins+1];
TH1F* hScaleRecoDeltaEta[NCentBins][nJtetaBins+1];
TH1F* hResoRecoDeltaPhi[NCentBins][nJtetaBins+1];
TH1F* hResoRecoDeltaEta[NCentBins][nJtetaBins+1];
TH1F* hScaleGenDeltaPhi[NCentBins][nJtetaBins+1];
TH1F* hScaleGenDeltaEta[NCentBins][nJtetaBins+1];
TH1F* hResoGenDeltaPhi[NCentBins][nJtetaBins+1];
TH1F* hResoGenDeltaEta[NCentBins][nJtetaBins+1];

TH2F* hRecoVsGenPt;
TH2F* hRecoVsGenPtCorr;
TH2F* hRecoVsGenPtRMatGStep1Corr;
TH2F* hRecoVsGenPtRMatGCorr;
TH2F* hRecoVsGenPtFfCorr;
TH2F* hRecoVsGenPtFfJecCorr;
TH2F* hGenSmearVsGenPt;
TH1F* hGenPtCorrNorm;

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
              for(int i=0;i<nResoJtptBins;i++)
                {
                  ahHistoResoPt[k][j][i] = new TH1F(Form("hHistoResoPt_%d_%d_%d",k,j,i), ";p_{T}^{reco} / p_{T}^{gen};", 50, 0, 2);
                  ahHistoResoPt[k][j][i]->Sumw2();
                  ahHistoResoPtCorr[k][j][i] = new TH1F(Form("hHistoResoPtCorr_%d_%d_%d",k,j,i), ";p_{T}^{reco} / p_{T}^{gen}, Corr;", 50, 0, 2);
                  ahHistoResoPtCorr[k][j][i]->Sumw2();
                  ahHistoResoPtRMatGCorr[k][j][i] = new TH1F(Form("hHistoResoPtRMatGCorr_%d_%d_%d",k,j,i), ";p_{T}^{reco} / p_{T}^{gen}, RMatGCorr;", 50, 0, 2);
                  ahHistoResoPtRMatGCorr[k][j][i]->Sumw2();
                  ahHistoResoPtFfCorr[k][j][i] = new TH1F(Form("hHistoResoPtFfCorr_%d_%d_%d",k,j,i), ";p_{T}^{reco} / p_{T}^{gen}, frag-dep Corr;", 50, 0, 2);
                  ahHistoResoPtFfCorr[k][j][i]->Sumw2();
                  ahHistoResoPtFfJecCorr[k][j][i] = new TH1F(Form("hHistoResoPtFfJecCorr_%d_%d_%d",k,j,i), ";p_{T}^{reco} / p_{T}^{gen}, frag-dep Corr;", 50, 0, 2);
                  ahHistoResoPtFfJecCorr[k][j][i]->Sumw2();
                  ahHistoResoPhi[k][j][i] = new TH1F(Form("hHistoResoPhi_%d_%d_%d",k,j,i), ";#phi^{reco} - #phi^{gen};", 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoPhi[k][j][i]->Sumw2();
                  ahHistoResoEta[k][j][i] = new TH1F(Form("hHistoResoEta_%d_%d_%d",k,j,i), ";#eta^{reco} - #eta^{gen};", 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoEta[k][j][i]->Sumw2();
                }
              for(int i=0;i<nResoDeltaJtptBins;i++)
                {
                  ahHistoResoRecoDeltaPhi[k][j][i] = new TH1F(Form("hHistoResoRecoDeltaPhi_%d_%d_%d",k,j,i), ";#phi^{reco} - #phi^{gen};", 50, -0.2, 0.2);
                  ahHistoResoRecoDeltaPhi[k][j][i]->Sumw2();
                  ahHistoResoRecoDeltaEta[k][j][i] = new TH1F(Form("hHistoResoRecoDeltaEta_%d_%d_%d",k,j,i), ";#eta^{reco} - #eta^{gen};", 50, -0.2, 0.2);
                  ahHistoResoRecoDeltaEta[k][j][i]->Sumw2();
                  ahHistoResoGenDeltaPhi[k][j][i] = new TH1F(Form("hHistoResoGenDeltaPhi_%d_%d_%d",k,j,i), ";#phi^{reco} - #phi^{gen};", 50, -0.2, 0.2);
                  ahHistoResoGenDeltaPhi[k][j][i]->Sumw2();
                  ahHistoResoGenDeltaEta[k][j][i] = new TH1F(Form("hHistoResoGenDeltaEta_%d_%d_%d",k,j,i), ";#eta^{reco} - #eta^{gen};", 50, -0.2, 0.2);
                  ahHistoResoGenDeltaEta[k][j][i]->Sumw2();
                }
              for(int i=0;i<nResoJtdrBins;i++)
                {
                  ahHistoResoDrPhi[k][j][i] = new TH1F(Form("hHistoResoDrPhi_%d_%d_%d",k,j,i), ";#phi^{reco} - #phi^{gen};", 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoDrPhi[k][j][i]->Sumw2();
                  ahHistoResoDrEta[k][j][i] = new TH1F(Form("hHistoResoDrEta_%d_%d_%d",k,j,i), ";#eta^{reco} - #eta^{gen};", 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoDrEta[k][j][i]->Sumw2();
                }
            }
        }
      hRecoVsGenPt = new TH2F("hRecoVsGenPt", ";gref jet p_{T} (GeV/c);reco jet p_{T} (GeV)", nMapjtptBins, mapjtptBins, nMapjtptBins, mapjtptBins);
      hRecoVsGenPtCorr = new TH2F("hRecoVsGenPtCorr", ";gref jet p_{T} (GeV/c);reco jet p_{T} (GeV)", nMapjtptBins, mapjtptBins, nMapjtptBins, mapjtptBins);
      hRecoVsGenPtRMatGStep1Corr = new TH2F("hRecoVsGenPtRMatGStep1Corr", ";gref jet p_{T} (GeV/c);reco jet p_{T} (GeV)", nMapjtptBins, mapjtptBins, nMapjtptBins, mapjtptBins);
      hRecoVsGenPtRMatGCorr = new TH2F("hRecoVsGenPtRMatGCorr", ";gref jet p_{T} (GeV/c);reco jet p_{T} (GeV)", nMapjtptBins, mapjtptBins, nMapjtptBins, mapjtptBins);
      hRecoVsGenPtFfCorr = new TH2F("hRecoVsGenPtFfCorr", ";gref jet p_{T} (GeV/c);reco jet p_{T} (GeV)", nMapjtptBins, mapjtptBins, nMapjtptBins, mapjtptBins);
      hRecoVsGenPtFfJecCorr = new TH2F("hRecoVsGenPtFfJecCorr", ";gref jet p_{T} (GeV/c);reco jet p_{T} (GeV)", nMapjtptBins, mapjtptBins, nMapjtptBins, mapjtptBins);
      hGenSmearVsGenPt = new TH2F("hGenSmearVsGenPt", ";gref jet p_{T} (GeV/c);reco jet p_{T} (GeV)", nMapjtptBins, mapjtptBins, nMapjtptBins, mapjtptBins);
      hGenPtCorrNorm = new TH1F("hGenPtCorrNorm", ";gref jet p_{T} (GeV/c);", nMapjtptBins, mapjtptBins);
      return 0;
    }
  if(opt=="savehistetaphi")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              for(int i=0;i<nResoJtptBins;i++)
                {
                  ahHistoResoEtaPhi[k][j][i] = new TH2F(Form("hHistoResoEtaPhi_%d_%d_%d",k,j,i), ";#phi^{reco} - #phi^{gen};#eta^{reco} - #eta^{gen}", 50, 0-xrangeAng, xrangeAng, 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoEtaPhi[k][j][i]->Sumw2();
                } 
              for(int i=0;i<nResoJtdrBins;i++)
                {
                  ahHistoResoDrEtaPhi[k][j][i] = new TH2F(Form("hHistoResoDrEtaPhi_%d_%d_%d",k,j,i), ";#phi^{reco} - #phi^{gen};#eta^{reco} - #eta^{gen}", 50, 0-xrangeAng, xrangeAng, 50, 0-xrangeAng, xrangeAng);
                  ahHistoResoDrEtaPhi[k][j][i]->Sumw2();
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
              hResoPt[k][j] = new TH1F(Form("hResoPt_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen})", nResoJtptBins, resojtptBins);
              hResoPtCorr[k][j] = new TH1F(Form("hResoPtCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), Corr", nResoJtptBins, resojtptBins);
              hResoPtRMatGCorr[k][j] = new TH1F(Form("hResoPtRMatGCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), RMatGCorr", nResoJtptBins, resojtptBins);
              hResoPtFfCorr[k][j] = new TH1F(Form("hResoPtFfCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), frag-dep Corr", nResoJtptBins, resojtptBins);
              hResoPtFfJecCorr[k][j] = new TH1F(Form("hResoPtFfJecCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), frag-dep Corr", nResoJtptBins, resojtptBins);
              hResoPhi[k][j] = new TH1F(Form("hResoPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", nResoJtptBins, resojtptBins);
              hResoEta[k][j] = new TH1F(Form("hResoEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", nResoJtptBins, resojtptBins);
              hScalePt[k][j] = new TH1F(Form("hScalePt_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoJtptBins, resojtptBins);
              hScalePtCorr[k][j] = new TH1F(Form("hScalePtCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", nResoJtptBins, resojtptBins);
              hScalePtRMatGCorr[k][j] = new TH1F(Form("hScalePtRMatGCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), RMatGCorr", nResoJtptBins, resojtptBins);
              hScalePtFfCorr[k][j] = new TH1F(Form("hScalePtFfCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), frag-dep Corr", nResoJtptBins, resojtptBins);
              hScalePtFfJecCorr[k][j] = new TH1F(Form("hScalePtFfJecCorr_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), frag-dep Corr", nResoJtptBins, resojtptBins);
              hScalePhi[k][j] = new TH1F(Form("hScalePhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoJtptBins, resojtptBins);
              hScaleEta[k][j] = new TH1F(Form("hScaleEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoJtptBins, resojtptBins);

              hResoRecoDeltaPhi[k][j] = new TH1F(Form("hResoRecoDeltaPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", nResoDeltaJtptBins, resodeltajtptBins);
              hResoRecoDeltaEta[k][j] = new TH1F(Form("hResoRecoDeltaEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", nResoDeltaJtptBins, resodeltajtptBins);
              hResoGenDeltaPhi[k][j] = new TH1F(Form("hResoGenDeltaPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", nResoDeltaJtptBins, resodeltajtptBins);
              hResoGenDeltaEta[k][j] = new TH1F(Form("hResoGenDeltaEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", nResoDeltaJtptBins, resodeltajtptBins);
              hScaleRecoDeltaPhi[k][j] = new TH1F(Form("hScaleRecoDeltaPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoDeltaJtptBins, resodeltajtptBins);
              hScaleRecoDeltaEta[k][j] = new TH1F(Form("hScaleRecoDeltaEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoDeltaJtptBins, resodeltajtptBins);
              hScaleGenDeltaPhi[k][j] = new TH1F(Form("hScaleGenDeltaPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoDeltaJtptBins, resodeltajtptBins);
              hScaleGenDeltaEta[k][j] = new TH1F(Form("hScaleGenDeltaEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoDeltaJtptBins, resodeltajtptBins);

              hResoDrPhi[k][j] = new TH1F(Form("hResoDrPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", nResoJtdrBins, resojtdrBins);
              hResoDrEta[k][j] = new TH1F(Form("hResoDrEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", nResoJtdrBins, resojtdrBins);
              hScaleDrPhi[k][j] = new TH1F(Form("hScaleDrPhi_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoJtdrBins, resojtdrBins);
              hScaleDrEta[k][j] = new TH1F(Form("hScaleDrEta_%d_%d",k,j), ";Gen Jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", nResoJtdrBins, resojtdrBins);
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
              for(int i=0;i<nResoJtptBins;i++)
                {
                  ahHistoResoPt[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPt_%d_%d_%d",k,j,i));
                  ahHistoResoPtCorr[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPtCorr_%d_%d_%d",k,j,i));
                  ahHistoResoPtRMatGCorr[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPtRMatGCorr_%d_%d_%d",k,j,i));
                  ahHistoResoPtFfCorr[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPtFfCorr_%d_%d_%d",k,j,i));
                  ahHistoResoPtFfJecCorr[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPtFfJecCorr_%d_%d_%d",k,j,i));
                  ahHistoResoPhi[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoPhi_%d_%d_%d",k,j,i));
                  ahHistoResoEta[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoEta_%d_%d_%d",k,j,i));
                }
              for(int i=0;i<nResoDeltaJtptBins;i++)
                {
                  ahHistoResoRecoDeltaPhi[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoRecoDeltaPhi_%d_%d_%d",k,j,i));
                  ahHistoResoRecoDeltaEta[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoRecoDeltaEta_%d_%d_%d",k,j,i));
                  ahHistoResoGenDeltaPhi[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoGenDeltaPhi_%d_%d_%d",k,j,i));
                  ahHistoResoGenDeltaEta[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoGenDeltaEta_%d_%d_%d",k,j,i));
                }
              for(int i=0;i<nResoJtdrBins;i++)
                {
                  ahHistoResoDrPhi[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoDrPhi_%d_%d_%d",k,j,i));
                  ahHistoResoDrEta[k][j][i] = (TH1F*)inf->Get(Form("hHistoResoDrEta_%d_%d_%d",k,j,i));
                }
            }
        }
      hRecoVsGenPt = (TH2F*)inf->Get("hRecoVsGenPt");
      hRecoVsGenPtCorr = (TH2F*)inf->Get("hRecoVsGenPtCorr");
      hRecoVsGenPtRMatGStep1Corr = (TH2F*)inf->Get("hRecoVsGenPtRMatGStep1Corr");
      hRecoVsGenPtRMatGCorr = (TH2F*)inf->Get("hRecoVsGenPtRMatGCorr");
      hRecoVsGenPtFfCorr = (TH2F*)inf->Get("hRecoVsGenPtFfCorr");
      hRecoVsGenPtFfJecCorr = (TH2F*)inf->Get("hRecoVsGenPtFfJecCorr");
      hGenSmearVsGenPt = (TH2F*)inf->Get("hGenSmearVsGenPt");
      hGenPtCorrNorm = (TH1F*)inf->Get("hGenPtCorrNorm");
      return 0;
    }
  if(opt=="usehistetaphi")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              for(int i=0;i<nResoJtptBins;i++)
                {
                  ahHistoResoEtaPhi[k][j][i] = (TH2F*)inf->Get(Form("hHistoResoEtaPhi_%d_%d_%d",k,j,i));
                }
              for(int i=0;i<nResoJtdrBins;i++)
                {
                  ahHistoResoDrEtaPhi[k][j][i] = (TH2F*)inf->Get(Form("hHistoResoDrEtaPhi_%d_%d_%d",k,j,i));
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
              hResoPtRMatGCorr[k][j] = (TH1F*)inf->Get(Form("hResoPtRMatGCorr_%d_%d",k,j));
              hResoPtFfCorr[k][j] = (TH1F*)inf->Get(Form("hResoPtFfCorr_%d_%d",k,j));
              hResoPtFfJecCorr[k][j] = (TH1F*)inf->Get(Form("hResoPtFfJecCorr_%d_%d",k,j));
              hResoPhi[k][j] = (TH1F*)inf->Get(Form("hResoPhi_%d_%d",k,j));
              hResoEta[k][j] = (TH1F*)inf->Get(Form("hResoEta_%d_%d",k,j));
              hScalePt[k][j] = (TH1F*)inf->Get(Form("hScalePt_%d_%d",k,j));
              hScalePtCorr[k][j] = (TH1F*)inf->Get(Form("hScalePtCorr_%d_%d",k,j));
              hScalePtRMatGCorr[k][j] = (TH1F*)inf->Get(Form("hScalePtRMatGCorr_%d_%d",k,j));
              hScalePtFfCorr[k][j] = (TH1F*)inf->Get(Form("hScalePtFfCorr_%d_%d",k,j));
              hScalePtFfJecCorr[k][j] = (TH1F*)inf->Get(Form("hScalePtFfJecCorr_%d_%d",k,j));
              hScalePhi[k][j] = (TH1F*)inf->Get(Form("hScalePhi_%d_%d",k,j));
              hScaleEta[k][j] = (TH1F*)inf->Get(Form("hScaleEta_%d_%d",k,j));

              hResoDrPhi[k][j] = (TH1F*)inf->Get(Form("hResoDrPhi_%d_%d",k,j));
              hResoDrEta[k][j] = (TH1F*)inf->Get(Form("hResoDrEta_%d_%d",k,j));
              hScaleDrPhi[k][j] = (TH1F*)inf->Get(Form("hScaleDrPhi_%d_%d",k,j));
              hScaleDrEta[k][j] = (TH1F*)inf->Get(Form("hScaleDrEta_%d_%d",k,j));

              hResoRecoDeltaPhi[k][j] = (TH1F*)inf->Get(Form("hResoRecoDeltaPhi_%d_%d",k,j));
              hResoRecoDeltaEta[k][j] = (TH1F*)inf->Get(Form("hResoRecoDeltaEta_%d_%d",k,j));
              hResoGenDeltaPhi[k][j] = (TH1F*)inf->Get(Form("hResoGenDeltaPhi_%d_%d",k,j));
              hResoGenDeltaEta[k][j] = (TH1F*)inf->Get(Form("hResoGenDeltaEta_%d_%d",k,j));
              hScaleRecoDeltaPhi[k][j] = (TH1F*)inf->Get(Form("hScaleRecoDeltaPhi_%d_%d",k,j));
              hScaleRecoDeltaEta[k][j] = (TH1F*)inf->Get(Form("hScaleRecoDeltaEta_%d_%d",k,j));
              hScaleGenDeltaPhi[k][j] = (TH1F*)inf->Get(Form("hScaleGenDeltaPhi_%d_%d",k,j));
              hScaleGenDeltaEta[k][j] = (TH1F*)inf->Get(Form("hScaleGenDeltaEta_%d_%d",k,j));
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
              for(int i=0;i<nResoJtptBins;i++)
                {
                  ahHistoResoPt[k][j][i]->Write();
                  ahHistoResoPtCorr[k][j][i]->Write();
                  ahHistoResoPtRMatGCorr[k][j][i]->Write();
                  ahHistoResoPtFfCorr[k][j][i]->Write();
                  ahHistoResoPtFfJecCorr[k][j][i]->Write();
                  ahHistoResoPhi[k][j][i]->Write();
                  ahHistoResoEta[k][j][i]->Write();
                }
              for(int i=0;i<nResoDeltaJtptBins;i++)
                {
                  ahHistoResoRecoDeltaPhi[k][j][i]->Write();
                  ahHistoResoRecoDeltaEta[k][j][i]->Write();
                  ahHistoResoGenDeltaPhi[k][j][i]->Write();
                  ahHistoResoGenDeltaEta[k][j][i]->Write();
                }
              for(int i=0;i<nResoJtdrBins;i++)
                {
                  ahHistoResoDrPhi[k][j][i]->Write();
                  ahHistoResoDrEta[k][j][i]->Write();
                }
            }
        }
      hRecoVsGenPt->Write();
      hRecoVsGenPtCorr->Write();
      hRecoVsGenPtRMatGStep1Corr->Write();
      hRecoVsGenPtRMatGCorr->Write();
      hRecoVsGenPtFfCorr->Write();
      hRecoVsGenPtFfJecCorr->Write();
      hGenSmearVsGenPt->Write();
      hGenPtCorrNorm->Write();
      return 0;
    }
  if(opt=="savehistetaphi")
    {
      for(int k=0;k<nCentBins;k++)
        {
          for(int j=0;j<nJtetaBins+1;j++)
            {
              for(int i=0;i<nResoJtptBins;i++)
                {
                  ahHistoResoEtaPhi[k][j][i]->Write();
                }
              for(int i=0;i<nResoJtdrBins;i++)
                {
                  ahHistoResoDrEtaPhi[k][j][i]->Write();
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
              hResoPtRMatGCorr[k][j]->Write();
              hResoPtFfCorr[k][j]->Write();
              hResoPtFfJecCorr[k][j]->Write();
              hResoPhi[k][j]->Write();
              hResoEta[k][j]->Write();
              hScalePt[k][j]->Write();
              hScalePtCorr[k][j]->Write();
              hScalePtRMatGCorr[k][j]->Write();
              hScalePtFfCorr[k][j]->Write();
              hScalePtFfJecCorr[k][j]->Write();
              hScalePhi[k][j]->Write();
              hScaleEta[k][j]->Write();

              hResoRecoDeltaPhi[k][j]->Write();
              hResoRecoDeltaEta[k][j]->Write();
              hResoGenDeltaPhi[k][j]->Write();
              hResoGenDeltaEta[k][j]->Write();

              hResoDrPhi[k][j]->Write();
              hResoDrEta[k][j]->Write();
              hScaleDrPhi[k][j]->Write();
              hScaleDrEta[k][j]->Write();
            }
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif
