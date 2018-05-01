#ifndef _SYSTSUMMARY_H_
#define _SYSTSUMMARY_H_

#include "prefilters.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/systmetics.h"
#include <TString.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

Color_t colorlist[] = {kRed-6, kAzure-5, kGreen-5, kMagenta-5, kOrange-8, kCyan+2};

TH1F* hsystSCALE[nPtBins];
TH1F* hsystRESO[nPtBins];
TH1F* hsystTRIGGER[nPtBins];
TH1F* hsystPDF[nPtBins];
TH1F* hsystCUT[nPtBins];
TH1F* hsystNONCLOSURE[nPtBins];
TH1F* hsystTOTAL[nPtBins];

std::vector<std::vector<Float_t>>* syst_SCALE;
std::vector<std::vector<Float_t>>* syst_RESO;
std::vector<std::vector<Float_t>>* syst_TRIGGER;
std::vector<std::vector<Float_t>>* syst_PDF;
std::vector<std::vector<Float_t>>* syst_NONCLOSURE;
std::vector<Float_t>* syst_CUT;

int createhist(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="plotsyst")
    {
      for(int i=0;i<nPtBins;i++)
        {
          hsystSCALE[i] = new TH1F(Form("hsystSCALE_%d",i), "", nDrBins, drBins);
          hsystRESO[i] = new TH1F(Form("hsystRESO_%d",i), "", nDrBins, drBins);
          hsystTRIGGER[i] = new TH1F(Form("hsystTRIGGER_%d",i), "", nDrBins, drBins);
          hsystPDF[i] = new TH1F(Form("hsystPDF_%d",i), "", nDrBins, drBins);
          hsystCUT[i] = new TH1F(Form("hsystCUT_%d",i), "", nDrBins, drBins);
          hsystNONCLOSURE[i] = new TH1F(Form("hsystNONCLOSURE_%d",i), "", nDrBins, drBins);
          hsystTOTAL[i] = new TH1F(Form("hsystTOTAL_%d",i), "", nDrBins, drBins);
        }
      return 0;
    }
  std::cout<<"error: invalid option - createhist"<<std::endl;
  return 1;
}

int setsyst(Bool_t ispp)
{
  if(ispp)
    {
      syst_SCALE = djtsyst::syst_SCALE_pp;
      syst_RESO = djtsyst::syst_RESO_pp;
      syst_TRIGGER = djtsyst::syst_TRIGGER_pp;
      syst_PDF = djtsyst::syst_PDF_pp;
      syst_NONCLOSURE = djtsyst::syst_NONCLOSURE_pp;
      syst_CUT = &djtsyst::syst_CUT_pp;
      return 0;
    }
  else
    {
      syst_SCALE = djtsyst::syst_SCALE_PbPb;
      syst_RESO = djtsyst::syst_RESO_PbPb;
      syst_TRIGGER = djtsyst::syst_TRIGGER_PbPb;
      syst_PDF = djtsyst::syst_PDF_PbPb;
      syst_NONCLOSURE = djtsyst::syst_NONCLOSURE_PbPb;
      syst_CUT = &djtsyst::syst_CUT_PbPb;
      return 0;
    }
  return 1;
}

#endif
