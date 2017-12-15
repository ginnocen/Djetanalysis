#ifndef _DJTANA_H_
#define _DJTANA_H_

#include "../includes/djet.h"
#include "../includes/prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/dfitter.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>

const Float_t DZERO_MASS = 1.8649;

//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

Color_t amcolor[nPtBins] = {kBlack, kRed};
Style_t amstyle[nRefBins][nPtBins] = {{20,     21},   {24,     25}};

TH1F* ahHistoRMass[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSignal[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoRMassSwapped[nRefBins][nPtBins][nDrBins];
TH1F* ahHistoZMass[nRefBins][nPtBins][nZBins];
TH1F* ahHistoZMassSignal[nRefBins][nPtBins][nZBins];
TH1F* ahHistoZMassSwapped[nRefBins][nPtBins][nZBins];
    
TH1F* hNjets;
TH1F* ahREfficiency[nRefBins][nPtBins];
TH1F* ahNumREfficiency[nRefBins][nPtBins];
TH1F* ahDenREfficiency[nRefBins][nPtBins];
TH1F* ahZEfficiency[nRefBins][nPtBins];
TH1F* ahNumZEfficiency[nRefBins][nPtBins];
TH1F* ahDenZEfficiency[nRefBins][nPtBins];

TH1F* ahSignalRraw[nRefBins][nPtBins];
TH1F* ahSignalZraw[nRefBins][nPtBins];
TH1F* ahSignalR[nRefBins][nPtBins];
TH1F* ahSignalZ[nRefBins][nPtBins];
TH1F* ahSignalRnorm[nRefBins][nPtBins];
TH1F* ahSignalZnorm[nRefBins][nPtBins];
TH1F* ahSignalRsub[nPtBins];
TH1F* ahSignalZsub[nPtBins];

TH1F* ahSignalRnormP[2][nRefBins][nPtBins];
TH1F* ahSignalZnormP[2][nRefBins][nPtBins];
TH1F* ahSignalRnormRatio[nRefBins][nPtBins];
TH1F* ahSignalZnormRatio[nRefBins][nPtBins];
TH1F* ahSignalRsubP[2][nPtBins];
TH1F* ahSignalZsubP[2][nPtBins];
TH1F* ahSignalRsubRatio[nPtBins];
TH1F* ahSignalZsubRatio[nPtBins];

// histograms for correlation studies

TH1F* hJetPhi;
TH1F* hJetEta;
TH1F* hDPhi[nPtBins];
TH1F* hDEta[nPtBins];
TH1F* hDdelPhi[nPtBins];
TH1F* hDdelEta[nPtBins];
TH2F* hCorr[nPtBins];
TH2F* hDphivsDtrk1hit[nPtBins];
TH2F* hDphivsDtrk2hit[nPtBins];
TH2F* hDphivsDtrk1algo[nPtBins];
TH2F* hDphivsDtrk2algo[nPtBins];
//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savetpl")
    { 
      hJetPhi=new TH1F("hJetPhi", ";#phi;",50,0., TMath::Pi());
      hJetEta=new TH1F("hJetEta", ";#eta;",50,-2.,2.);
      hNjets = new TH1F("hNjets", "", 1, 0, 1); // ... is it necessary
      for(int i=0;i<nPtBins;i++)
        {
          hDPhi[i]=new TH1F(Form("hDPhi_pt_%d",i),";#phi;",50,-TMath::Pi(),TMath::Pi());
          hDEta[i]=new TH1F(Form("hDEta_pt_%d",i),";#eta;",50,-2.,2.);
          hDdelPhi[i]=new TH1F(Form("hDdelPhi_pt_%d",i),";#Delta#phi;",50,0.,TMath::Pi());
          hDdelEta[i]=new TH1F(Form("hDdelEta_pt_%d",i),";#Delta#eta;",50,-4.,4.);
          hCorr[i]=new TH2F(Form("hCorr_pt_%d",i),";#Delta#eta;#Delta#phi;",50,-4.,4.,50,0.,TMath::Pi());
          hDphivsDtrk1hit[i]=new TH2F(Form("hDphivsDtrk1hit_pt_%d",i),";#phi;Dtrk1PixelHit",50,-TMath::Pi(),TMath::Pi(),50,0.,50.);
          hDphivsDtrk2hit[i]=new TH2F(Form("hDphivsDtrk2hit_pt_%d",i),";#phi;Dtrk2PixelHit",50,-TMath::Pi(),TMath::Pi(),50,0.,50.);
          hDphivsDtrk1algo[i]=new TH2F(Form("hDphivsDtrk1algo_pt_%d",i),";#phi;Dtrk1Algo",50,-TMath::Pi(),TMath::Pi(),50,0.,50.);
          hDphivsDtrk2algo[i]=new TH2F(Form("hDphivsDtrk2algo_pt_%d",i),";#phi;Dtrk2Algo",50,-TMath::Pi(),TMath::Pi(),50,0.,50.);
          for(int l=0;l<nRefBins;l++)
            {
              ahREfficiency[l][i] = new TH1F(Form("hREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahNumREfficiency[l][i] = new TH1F(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahDenREfficiency[l][i] = new TH1F(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahZEfficiency[l][i] = new TH1F(Form("hZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahNumZEfficiency[l][i] = new TH1F(Form("hNumZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahDenZEfficiency[l][i] = new TH1F(Form("hDenZEfficiency_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j] = new TH1F(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  ahHistoRMassSwapped[l][i][j] = new TH1F(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                }
              for(int j=0;j<nZBins;j++) 
                {
                  ahHistoZMassSignal[l][i][j] = new TH1F(Form("hHistoZMassSignal_%s_pt_%d_z_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  ahHistoZMassSwapped[l][i][j] = new TH1F(Form("hHistoZMassSwapped_%s_pt_%d_z_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                }
            }
        }
      return 0;
    }
  if(opt=="savehist")
    {
      hNjets = new TH1F("hNjets", "", 1, 0, 1);
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = new TH1F(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
              for(int j=0;j<nZBins;j++) ahHistoZMass[l][i][j] = new TH1F(Form("hHistoZMass_%s_pt_%d_z_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
            }
        }
      return 0;
    }
  if(opt=="usehist")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRraw[l][i] = new TH1F(Form("hSignalRraw_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahSignalZraw[l][i] = new TH1F(Form("hSignalZraw_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahSignalR[l][i] = new TH1F(Form("hSignalR_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahSignalZ[l][i] = new TH1F(Form("hSignalZ_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
              ahSignalRnorm[l][i] = new TH1F(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahSignalZnorm[l][i] = new TH1F(Form("hSignalZnorm_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
            }
          ahSignalRsub[i] = new TH1F(Form("hSignalRsub_pt_%d",i), ";#DeltaR;", nDrBins, drBins);
          ahSignalZsub[i] = new TH1F(Form("hSignalZsub_pt_%d",i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
        }
      return 0;
    }
  if(opt=="saveratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormRatio[l][i] = new TH1F(Form("hSignalRnormRatio_%s_pt_%d",tRef[l].Data(),i), ";#DeltaR;", nDrBins, drBins);
              ahSignalZnormRatio[l][i] = new TH1F(Form("hSignalZnormRatio_%s_pt_%d",tRef[l].Data(),i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
            }
          ahSignalRsubRatio[i] = new TH1F(Form("hSignalRsubRatio_pt_%d",i), ";#DeltaR;", nDrBins, drBins);
          ahSignalZsubRatio[i] = new TH1F(Form("hSignalZsubRatio_pt_%d",i), ";p_{T}^{D} / p_{T}^{jet};", nZBins, zBins);
        }
      return 0;
    }
  std::cout<<"error: invalid option for createhists()"<<std::endl;
  return 1;
}

int writehists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();

  if(opt=="savetpl")
    {
      hNjets->Write(); // ... is it necessary
      hJetPhi->Write();
      hJetEta->Write();
      for(int i=0;i<nPtBins;i++)
        {
          hDPhi[i]->Write();
          hDEta[i]->Write();
          hDdelPhi[i]->Write();
          hDdelEta[i]->Write();
          hCorr[i]->Write();
          hDphivsDtrk1hit[i]->Write();
          hDphivsDtrk2hit[i]->Write();
          hDphivsDtrk1algo[i]->Write();
          hDphivsDtrk2algo[i]->Write();
          for(int l=0;l<nRefBins;l++)
            {
              ahREfficiency[l][i]->Write();
              ahNumREfficiency[l][i]->Write();
              ahDenREfficiency[l][i]->Write();
              ahZEfficiency[l][i]->Write();
              ahNumZEfficiency[l][i]->Write();
              ahDenZEfficiency[l][i]->Write();
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j]->Write();
                  ahHistoRMassSwapped[l][i][j]->Write();
                }
              for(int j=0;j<nZBins;j++) 
                {
                  ahHistoZMassSignal[l][i][j]->Write();
                  ahHistoZMassSwapped[l][i][j]->Write();
                }
            }
        }
      return 0;
    }
  if(opt=="savehist")
    {
      hNjets->Write();
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j]->Write();
              for(int j=0;j<nZBins;j++) ahHistoZMass[l][i][j]->Write();
            }
        }
      return 0;
    }
  if(opt.Contains("usehist"))
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRraw[l][i]->Write();
              ahSignalZraw[l][i]->Write();
              ahSignalR[l][i]->Write();
              ahSignalZ[l][i]->Write();
              ahSignalRnorm[l][i]->Write();
              ahSignalZnorm[l][i]->Write();
            }
          ahSignalRsub[i]->Write();
          ahSignalZsub[i]->Write();
        }
      return 0;
    }
  if(opt=="saveratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormRatio[l][i]->Write();
              ahSignalZnormRatio[l][i]->Write();
            }
          ahSignalRsubRatio[i]->Write();
          ahSignalZsubRatio[i]->Write();
        }
      return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

int gethists(TFile* inf, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="hist")
    {
      hJetPhi= (TH1F*)inf->Get("hJetPhi");
      hNjets = (TH1F*)inf->Get("hNjets");
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) ahHistoRMass[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMass_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
              for(int j=0;j<nZBins;j++) ahHistoZMass[l][i][j] = (TH1F*)inf->Get(Form("hHistoZMass_%s_pt_%d_z_%d",tRef[l].Data(),i,j));
            }
        }
      return 0;
    }
  if(opt=="tpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahREfficiency[l][i] = (TH1F*)inf->Get(Form("hREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahDenREfficiency[l][i] = (TH1F*)inf->Get(Form("hDenREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahNumREfficiency[l][i] = (TH1F*)inf->Get(Form("hNumREfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahZEfficiency[l][i] = (TH1F*)inf->Get(Form("hZEfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahNumZEfficiency[l][i] = (TH1F*)inf->Get(Form("hNumZEfficiency_%s_pt_%d",tRef[l].Data(),i));
              ahDenZEfficiency[l][i] = (TH1F*)inf->Get(Form("hDenZEfficiency_%s_pt_%d",tRef[l].Data(),i));
              for(int j=0;j<nDrBins;j++) 
                {
                  ahHistoRMassSignal[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSignal_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                  ahHistoRMassSwapped[l][i][j] = (TH1F*)inf->Get(Form("hHistoRMassSwapped_%s_pt_%d_dr_%d",tRef[l].Data(),i,j));
                }
              for(int j=0;j<nZBins;j++) 
                {
                  ahHistoZMassSignal[l][i][j] = (TH1F*)inf->Get(Form("hHistoZMassSignal_%s_pt_%d_z_%d",tRef[l].Data(),i,j));
                  ahHistoZMassSwapped[l][i][j] = (TH1F*)inf->Get(Form("hHistoZMassSwapped_%s_pt_%d_z_%d",tRef[l].Data(),i,j));
                }
            }
        }
      return 0;
    }
  if(opt.Contains("plothist"))
    {
      hJetPhi = (TH1F*)inf->Get("hJetPhi");
      hJetEta = (TH1F*)inf->Get("hJetEta");
      for(int i=0;i<nPtBins;i++)
        {
          hDEta[i] = (TH1F*)inf->Get(Form("hDEta_pt_%d",i));
          hDPhi[i] = (TH1F*)inf->Get(Form("hDPhi_pt_%d",i));
          hDdelPhi[i] = (TH1F*)inf->Get(Form("hDdelPhi_pt_%d",i));
          hDdelEta[i] = (TH1F*)inf->Get(Form("hDdelEta_pt_%d",i));
          hCorr[i] = (TH2F*)inf->Get(Form("hCorr_pt_%d",i));
          hDphivsDtrk1hit[i] = (TH2F*)inf->Get(Form("hDphivsDtrk1hit_pt_%d",i));
          hDphivsDtrk2hit[i] = (TH2F*)inf->Get(Form("hDphivsDtrk2hit_pt_%d",i));
          hDphivsDtrk1algo[i] = (TH2F*)inf->Get(Form("hDphivsDtrk1algo_pt_%d",i));
          hDphivsDtrk2algo[i] = (TH2F*)inf->Get(Form("hDphivsDtrk2algo_pt_%d",i));
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnorm[l][i] = (TH1F*)inf->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
              ahSignalZnorm[l][i] = (TH1F*)inf->Get(Form("hSignalZnorm_%s_pt_%d",tRef[l].Data(),i));
            }
          ahSignalRsub[i] = (TH1F*)inf->Get(Form("hSignalRsub_pt_%d",i));
          ahSignalZsub[i] = (TH1F*)inf->Get(Form("hSignalZsub_pt_%d",i));
        }
      return 0;
    }
  if(opt.Contains("saveratio") && (opt.Contains("pp")||opt.Contains("pbpb")))
    {
      Int_t isPbPb = opt.Contains("pp")?0:1;
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormP[isPbPb][l][i] = (TH1F*)inf->Get(Form("hSignalRnorm_%s_pt_%d",tRef[l].Data(),i));
              ahSignalRnormP[isPbPb][l][i]->SetName(Form("hSignalRnorm_%s_pt_%d_%s",tRef[l].Data(),i,tPbPb[isPbPb].Data()));
              ahSignalZnormP[isPbPb][l][i] = (TH1F*)inf->Get(Form("hSignalZnorm_%s_pt_%d",tRef[l].Data(),i));
              ahSignalZnormP[isPbPb][l][i]->SetName(Form("hSignalZnorm_%s_pt_%d_%s",tRef[l].Data(),i,tPbPb[isPbPb].Data()));
            }
          ahSignalRsubP[isPbPb][i] = (TH1F*)inf->Get(Form("hSignalRsub_pt_%d",i));
          ahSignalRsubP[isPbPb][i]->SetName(Form("hSignalRsub_pt_%d_%s",i,tPbPb[isPbPb].Data()));
          ahSignalZsubP[isPbPb][i] = (TH1F*)inf->Get(Form("hSignalZsub_pt_%d",i));
          ahSignalZsubP[isPbPb][i]->SetName(Form("hSignalZsub_pt_%d_%s",i,tPbPb[isPbPb].Data()));
        }
      return 0;
    }
  if(opt=="plotratio")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              ahSignalRnormRatio[l][i] = (TH1F*)inf->Get(Form("hSignalRnormRatio_%s_pt_%d",tRef[l].Data(),i));
              ahSignalZnormRatio[l][i] = (TH1F*)inf->Get(Form("hSignalZnormRatio_%s_pt_%d",tRef[l].Data(),i));
            }
          ahSignalRsubRatio[i] = (TH1F*)inf->Get(Form("hSignalRsubRatio_pt_%d",i));
          ahSignalZsubRatio[i] = (TH1F*)inf->Get(Form("hSignalZsubRatio_pt_%d",i));
        }
      return 0;
    }
  std::cout<<"error: invalid option for gethists()"<<std::endl;
  return 1;
}



#endif
