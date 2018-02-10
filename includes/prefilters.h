#ifndef _PREFILTERS_H_
#define _PREFILTERS_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <TString.h>
#include "centweight.h"

#ifndef _JTPTBINS
#define _JTPTBINS
Float_t jtptBins[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 1000};
const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;
#endif
#ifndef _RESOJTPTBINS
#define _RESOJTPTBINS
Float_t resojtptBins[] = {10, 20, 30, 40, 50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 250, 300};
const int nResoJtptBins = sizeof(resojtptBins)/sizeof(resojtptBins[0])-1;
#endif
#ifndef _RESOJTDRBINS
#define _RESOJTDRBINS
Float_t resojtdrBins[] = {0, 0.01, 0.03, 0.05, 0.07, 0.1, 0.15, 0.20, 0.25, 0.30, 0.40, 0.50, 0.60, 0.70};
const int nResoJtdrBins = sizeof(resojtdrBins)/sizeof(resojtdrBins[0])-1;
#endif
#ifndef _DRBINS
#define _DRBINS
Float_t drBins[] = {0, 0.05, 0.10, 0.30, 0.50};
const int nDrBins = sizeof(drBins)/sizeof(drBins[0])-1;
#endif

Float_t ptBins[] = {4, 20, 999};
// Float_t drBins[] = {0, 0.05, 0.1, 0.2, 0.3, 0.5};
Float_t zBins[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.90, 1.0};
const int nCoBins = 2;
std::map<TString, int> collsyst_list = {{"pp", 0}, {"PbPb", 1}};
TString tMC[] = {"data", "MC"};
TString tPbPb[] = {"pp", "PbPb"};
Float_t centBins[] = {0, 30, 100};
const int NCentBins = sizeof(centBins)/sizeof(centBins[0])-1;
int nCentBins = 0;
void setnCentBins(Int_t ispp) {nCentBins = ispp?1:NCentBins;}

//
const int nPtBins = sizeof(ptBins)/sizeof(ptBins[0])-1;
const int nZBins = sizeof(zBins)/sizeof(zBins[0])-1;

std::vector<TString> cutval_list_skim[nCoBins] = {{"pBeamScrapingFilter", "pPAprimaryVertexFilter"}, 
                                                  {"pclusterCompatibilityFilter", "pprimaryVertexFilter", "phfCoincFilter3"}};

Float_t cutval_Dy = 2.0;
/*
  {
  // ----- dR bin -----
  {{xx, xx, xx, xx, xx},  // pp 4-20 GeV
  {xx, xx, xx, xx, xx}}, // pp 20-999 GeV
  {{xx, xx, xx, xx, xx},  // PbPb 4-20 GeV
  {xx, xx, xx, xx, xx}}  // PbPb 20-999 GeV
  };
*/
Float_t cutval_list_Dsvpv[nCoBins][nPtBins][nDrBins] = 
  {
    {{3.00, 3.00, 3.00, 3.00},
     {3.00, 3.00, 3.00, 3.00}},
    {{3.00, 3.00, 3.00, 3.00},
     {3.00, 3.00, 3.00, 3.00}}
  };
Float_t cutval_list_Dalpha[nCoBins][nPtBins][nDrBins] = 
  {
    {{0.04, 0.04, 0.04, 0.04},
     {0.04, 0.04, 0.04, 0.04}},
    {{0.04, 0.04, 0.04, 0.04},
     {0.04, 0.04, 0.04, 0.04}}
  };
Float_t cutval_list_Dchi2cl[nCoBins][nPtBins][nDrBins] = 
  {
    {{0.05, 0.05, 0.05, 0.05},
     {0.05, 0.05, 0.05, 0.05}},
    {{0.05, 0.05, 0.05, 0.05},
     {0.05, 0.05, 0.05, 0.05}}
  };
Float_t cutval_list_trkPt[nCoBins][nPtBins][nDrBins] = 
  {
    {{2.00, 2.00, 2.00, 2.00},
     {2.00, 2.00, 2.00, 2.00}},
    {{2.00, 2.00, 2.00, 2.00},
     {2.00, 2.00, 2.00, 2.00}}
  };
Float_t cutval_list_trkEta[nCoBins][nPtBins][nDrBins] = 
  {
    {{2.00, 2.00, 2.00, 2.00},
     {2.00, 2.00, 2.00, 2.00}},
    {{2.00, 2.00, 2.00, 2.00},
     {2.00, 2.00, 2.00, 2.00}}
  };
Float_t cutval_list_trkPtErr[nCoBins][nPtBins][nDrBins] = 
  {
    {{0.30, 0.30, 0.30, 0.30},
     {0.30, 0.30, 0.30, 0.30}},
    {{0.30, 0.30, 0.30, 0.30},
     {0.30, 0.30, 0.30, 0.30}}
  };

//

Float_t cutval_trkPt;
Float_t cutval_trkEta;
Float_t cutval_trkPtErr;
Float_t cutval_Dsvpv;
Float_t cutval_Dalpha;
Float_t cutval_Dchi2cl;
std::vector<TString> cutval_skim;
std::vector<TString> cutval_hlt;

int initcutval(TString collisionsyst)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\" - initcutval()"<<std::endl;
      return 1;
    }
  int icollsyst = collsyst_list[collisionsyst];
  cutval_skim = cutval_list_skim[icollsyst];
  return 0;
}

int initcutval_bindep(TString collisionsyst, int ipt, int idr)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\" - initcutval()"<<std::endl;
      return 1;
    }
  if(ipt<0 || idr<0 || ipt>=nPtBins || idr>=nDrBins) return 2;

  int icollsyst = collsyst_list[collisionsyst];
  cutval_trkPt = cutval_list_trkPt[icollsyst][ipt][idr];
  cutval_trkEta = cutval_list_trkEta[icollsyst][ipt][idr];
  cutval_trkPtErr = cutval_list_trkPtErr[icollsyst][ipt][idr];
  cutval_Dsvpv = cutval_list_Dsvpv[icollsyst][ipt][idr];
  cutval_Dalpha = cutval_list_Dalpha[icollsyst][ipt][idr];
  cutval_Dchi2cl = cutval_list_Dchi2cl[icollsyst][ipt][idr];
  return 0;
}

int initcutval_bindep_flat(TString collisionsyst, int ipt)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\" - initcutval()"<<std::endl;
      return 1;
    }
  if(ipt<0 || ipt>=nPtBins) return 2;

  int icollsyst = collsyst_list[collisionsyst];
  cutval_trkPt = cutval_list_trkPt[icollsyst][ipt][0];
  cutval_trkEta = cutval_list_trkEta[icollsyst][ipt][0];
  cutval_trkPtErr = cutval_list_trkPtErr[icollsyst][ipt][0];
  cutval_Dsvpv = cutval_list_Dsvpv[icollsyst][ipt][0];
  cutval_Dalpha = cutval_list_Dalpha[icollsyst][ipt][0];
  cutval_Dchi2cl = cutval_list_Dchi2cl[icollsyst][ipt][0];
  return 0;
}

#endif
