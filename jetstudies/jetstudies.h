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

TH1F* hJetPtSpectrumInclusive[nRefBins][nPtBins][nDrBins];
TH1F* hJetPtSpectrumDmeson[nRefBins][nPtBins][nDrBins];

//
int createhists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if(opt=="savetpl")
    {
          for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) 
                {
                  hJetPtSpectrumInclusive[l][i][j] = new TH1F(Form("hJetPtSpectrumInclusive_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";pt_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                  hJetPtSpectrumDmeson[l][i][j] = new TH1F(Form("hJetPtSpectrumDmeson_%s_pt_%d_dr_%d",tRef[l].Data(),i,j), ";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})", 60, 1.7, 2.0);
                }
            }
        }
      return 0;
    }
}

int writehists(Option_t* option)
{
  TString opt  = option;
  opt.ToLower();

  if(opt=="savetpl")
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              for(int j=0;j<nDrBins;j++) 
                {
                  hJetPtSpectrumInclusive[l][i][j]->Write();
                  hJetPtSpectrumDmeson[l][i][j]->Write();
                }
            }
        }
      return 0;
    }

  std::cout<<"error: invalid option for writehists()"<<std::endl;
  return 1;
}

#endif

