#ifndef _JETSTUDIES_H_
#define _JETSTUDIES_H_

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


//
const Float_t DZERO_MASS = 1.8649;
//
const int nRefBins = 2;
TString tRef[nRefBins] = {"eta", "etaref"};

Color_t amcolor[nPtBins] = {kBlack, kRed};
Style_t amstyle[nRefBins][nPtBins] = {{20,     21},   {24,     25}};

TH1F* hJetPtSpectrumInclusive;
TH1F* hJetPtSpectrumDmeson[nRefBins][nPtBins];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  
  if(opt=="savehist")
    {
      hJetPtSpectrumInclusive = new TH1F("hJetPtSpectrumInclusive", ";pt_{inclusive jet};", 1000, 0,1000.0);
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
          {
             hJetPtSpectrumDmeson[l][i] = new TH1F(Form("hJetPtSpectrumDmeson_%s_pt_%d",tRef[l].Data(),i), ";pt_{inclusive jet};", 1000, 0,1000.0);
          }
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
      hJetPtSpectrumInclusive->Write();
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
          {
             hJetPtSpectrumDmeson[l][i]->Write();
          }
       }
       return 0;
    }
  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif

