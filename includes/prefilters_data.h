#ifndef _PREFILTERS_H_
#define _PREFILTERS_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <TString.h>

Float_t ptBins[] = {4, 999};
Float_t drBins[] = {0, 0.05, 0.1, 0.30, 0.50};
Float_t zBins[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.90, 1.0};
const int nCoBins = 2;
std::map<TString, int> collsyst_list = {{"pp", 0}, {"PbPb", 1}};
TString tMC[] = {"data", "MC"};
TString tPbPb[] = {"pp", "PbPb"};

//
const int nPtBins = sizeof(ptBins)/sizeof(ptBins[0])-1;
const int nDrBins = sizeof(drBins)/sizeof(drBins[0])-1;
const int nZBins = sizeof(zBins)/sizeof(zBins[0])-1;

std::vector<TString> cutval_list_skim[nCoBins] = {{"pBeamScrapingFilter", "pPAprimaryVertexFilter"}, 
                                                  {"pclusterCompatibilityFilter", "pprimaryVertexFilter", "phfCoincFilter3"}};

Float_t ptselBins[] = {4, 20, 999};
const int nPtSelBins = sizeof(ptselBins)/sizeof(ptselBins[0])-1;

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
Float_t cutval_list_Dsvpv[nCoBins][nPtSelBins][nDrBins] = 
  {
    {{3.26,  3.26,  3.23,  3.23},
     {2.86,  2.86,  2.34,  2.34}},
    {{4.44,  4.44,  4.34,  4.34},
     {2.68,  2.68,  2.08,  2.08}}
  };
Float_t cutval_list_Dalpha[nCoBins][nPtSelBins][nDrBins] = 
  {
    {{0.039,  0.039,  0.046,  0.046},
     {0.037,  0.037,  0.039,  0.039}},
    {{0.040,  0.040,  0.043,  0.043},
     {0.038,  0.038,  0.107,  0.107}}
  };
Float_t cutval_list_Dchi2cl[nCoBins][nPtSelBins][nDrBins] = 
  {
    {{0.05,  0.05,  0.05,  0.05},
     {0.05,  0.05,  0.05,  0.05}},
    {{0.05,  0.05,  0.05,  0.05},
     {0.05,  0.05,  0.05,  0.05}}
  };
Float_t cutval_list_trkPt[nCoBins][nPtSelBins][nDrBins] = 
  {
    {{2.0,  2.0,  2.0,  2.0},
     {2.0,  2.0,  2.0,  2.0}},
    {{2.0,  2.0,  2.0,  2.0},
     {2.0,  2.0,  2.0,  2.0}}
  };
Float_t cutval_list_trkEta[nCoBins][nPtSelBins][nDrBins] = 
  {
    {{2.0,  2.0,  2.0,  2.0},
     {2.0,  2.0,  2.0,  2.0}},
    {{2.0,  2.0,  2.0,  2.0},
     {2.0,  2.0,  2.0,  2.0}}
  };
Float_t cutval_list_trkPtErr[nCoBins][nPtSelBins][nDrBins] = 
  {
    {{0.3,  0.3,  0.3,  0.3},
     {0.3,  0.3,  0.3,  0.3}},
    {{0.3,  0.3,  0.3,  0.3},
     {0.3,  0.3,  0.3,  0.3}}
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
  if(ipt<0 || idr<0 || ipt>=nPtSelBins || idr>=nDrBins) return 2;

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
  if(ipt<0 || ipt>=nPtSelBins) return 2;

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
