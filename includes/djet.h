//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 17 16:35:56 2017 by ROOT version 6.02/13
// from TTree djt/photon jet track tree
// found on file: /export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root
//////////////////////////////////////////////////////////

#ifndef _DJET_H_
#define _DJET_H_

#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <vector>
#include <iostream>

class djet 
{
public:
  TTree*                fChain;   //!pointer to the analyzed TTree or TChain
  TTree*                fHlt;
  
  // Declaration of leaf types
  Int_t                 isPP;
  UInt_t                run;
  ULong64_t             evt;
  UInt_t                lumi;
  Int_t                 hiBin;
  Float_t               vz;
  Float_t               weight;
  Float_t               pthat;
  Float_t               hiEvtPlanes[29];
  Int_t                 njet_akpu3pf;
  std::vector<float>*   jetptCorr_akpu3pf;
  std::vector<float>*   jetpt_akpu3pf;
  std::vector<float>*   jeteta_akpu3pf;
  std::vector<float>*   jetphi_akpu3pf;
  std::vector<float>*   gjetpt_akpu3pf;
  std::vector<float>*   gjeteta_akpu3pf;
  std::vector<float>*   gjetphi_akpu3pf;
  std::vector<int>*     gjetflavor_akpu3pf;
  std::vector<float>*   chargedSum_akpu3pf;
  std::vector<int>*     subid_akpu3pf;
  Int_t                 ngen_akpu3pf;
  std::vector<float>*   genpt_akpu3pf;
  std::vector<float>*   geneta_akpu3pf;
  std::vector<float>*   genphi_akpu3pf;
  std::vector<int>*     gensubid_akpu3pf;
  Int_t                 njet_akpu4pf;
  std::vector<float>*   jetptCorr_akpu4pf;
  std::vector<float>*   jetpt_akpu4pf;
  std::vector<float>*   jeteta_akpu4pf;
  std::vector<float>*   jetphi_akpu4pf;
  std::vector<float>*   gjetpt_akpu4pf;
  std::vector<float>*   gjeteta_akpu4pf;
  std::vector<float>*   gjetphi_akpu4pf;
  std::vector<int>*     gjetflavor_akpu4pf;
  std::vector<float>*   chargedSum_akpu4pf;
  std::vector<int>*     subid_akpu4pf;
  Int_t                 ngen_akpu4pf;
  std::vector<float>*   genpt_akpu4pf;
  std::vector<float>*   geneta_akpu4pf;
  std::vector<float>*   genphi_akpu4pf;
  std::vector<int>*     gensubid_akpu4pf;
  Int_t                 RunNo;
  Int_t                 EvtNo;
  Int_t                 LumiNo;
  Int_t                 Dsize;
  Float_t               PVx;
  Float_t               PVy;
  Float_t               PVz;
  Float_t               PVnchi2;
  Float_t               BSx;
  Float_t               BSy;
  Float_t               BSz;
  Float_t               PVxE;
  Float_t               PVyE;
  Float_t               PVzE;
  Float_t               BSxErr;
  Float_t               BSyErr;
  Float_t               BSzErr;
  Float_t               BSdxdz;
  Float_t               BSdydz;
  Float_t               BSdxdzErr;
  Float_t               BSdydzErr;
  Float_t               BSWidthX;
  Float_t               BSWidthXErr;
  Float_t               BSWidthY;
  Float_t               BSWidthYErr;
  std::vector<int>*     Dindex;
  std::vector<int>*     Dtype;
  std::vector<float>*   Dmass;
  std::vector<float>*   Dpt;
  std::vector<float>*   Deta;
  std::vector<float>*   Dphi;
  std::vector<float>*   Dy;
  std::vector<float>*   DvtxX;
  std::vector<float>*   DvtxY;
  std::vector<float>*   Dd0;
  std::vector<float>*   Dd0Err;
  std::vector<float>*   Ddxyz;
  std::vector<float>*   DdxyzErr;
  std::vector<float>*   Dchi2ndf;
  std::vector<float>*   Dchi2cl;
  std::vector<float>*   Ddtheta;
  std::vector<float>*   Dlxy;
  std::vector<float>*   Dalpha;
  std::vector<float>*   DsvpvDistance;
  std::vector<float>*   DsvpvDisErr;
  std::vector<float>*   DsvpvDistance_2D;
  std::vector<float>*   DsvpvDisErr_2D;
  std::vector<float>*   DtktkRes_chi2ndf;
  std::vector<float>*   DtktkRes_chi2cl;
  std::vector<float>*   DtktkRes_alpha;
  std::vector<float>*   DtktkRes_svpvDistance;
  std::vector<float>*   DtktkRes_svpvDisErr;
  std::vector<float>*   DlxyBS;
  std::vector<float>*   DlxyBSErr;
  std::vector<float>*   DMaxDoca;
  std::vector<float>*   Dtrk1Pt;
  std::vector<float>*   Dtrk2Pt;
  std::vector<float>*   Dtrk1Eta;
  std::vector<float>*   Dtrk2Eta;
  std::vector<float>*   Dtrk1Phi;
  std::vector<float>*   Dtrk2Phi;
  std::vector<float>*   Dtrk1PtErr;
  std::vector<float>*   Dtrk2PtErr;
  std::vector<float>*   Dtrk1Dxy;
  std::vector<float>*   Dtrk2Dxy;
  std::vector<float>*   Dtrk1PixelHit;
  std::vector<float>*   Dtrk2PixelHit;
  std::vector<float>*   Dtrk1StripHit;
  std::vector<float>*   Dtrk2StripHit;
  std::vector<float>*   Dtrk1nStripLayer;
  std::vector<float>*   Dtrk2nStripLayer;
  std::vector<float>*   Dtrk1nPixelLayer;
  std::vector<float>*   Dtrk2nPixelLayer;
  std::vector<float>*   Dtrk1Chi2ndf;
  std::vector<float>*   Dtrk2Chi2ndf;
  std::vector<float>*   Dtrk1MassHypo;
  std::vector<float>*   Dtrk2MassHypo;
  std::vector<int>*     Dtrk1Algo;
  std::vector<int>*     Dtrk2Algo;
  std::vector<int>*     Dtrk1originalAlgo;
  std::vector<int>*     Dtrk2originalAlgo;
  std::vector<bool>*    Dtrk1highPurity;
  std::vector<bool>*    Dtrk2highPurity;
  std::vector<float>*   Dtrk3Pt;
  std::vector<float>*   Dtrk4Pt;
  std::vector<float>*   Dtrk3Eta;
  std::vector<float>*   Dtrk4Eta;
  std::vector<float>*   Dtrk3Phi;
  std::vector<float>*   Dtrk4Phi;
  std::vector<float>*   Dtrk3PtErr;
  std::vector<float>*   Dtrk4PtErr;
  std::vector<float>*   Dtrk3Dxy;
  std::vector<float>*   Dtrk4Dxy;
  std::vector<float>*   Dtrk3PixelHit;
  std::vector<float>*   Dtrk4PixelHit;
  std::vector<float>*   Dtrk3StripHit;
  std::vector<float>*   Dtrk4StripHit;
  std::vector<float>*   Dtrk3nStripLayer;
  std::vector<float>*   Dtrk4nStripLayer;
  std::vector<float>*   Dtrk3nPixelLayer;
  std::vector<float>*   Dtrk4nPixelLayer;
  std::vector<float>*   Dtrk3Chi2ndf;
  std::vector<float>*   Dtrk4Chi2ndf;
  std::vector<float>*   Dtrk3MassHypo;
  std::vector<float>*   Dtrk4MassHypo;
  std::vector<int>*     Dtrk3Algo;
  std::vector<int>*     Dtrk4Algo;
  std::vector<int>*     Dtrk3originalAlgo;
  std::vector<int>*     Dtrk4originalAlgo;
  std::vector<bool>*    Dtrk3highPurity;
  std::vector<bool>*    Dtrk4highPurity;
  std::vector<int>*     Dtrk1Idx;
  std::vector<int>*     Dtrk2Idx;
  std::vector<float>*   Dtrk1EtaErr;
  std::vector<float>*   Dtrk2EtaErr;
  std::vector<float>*   Dtrk1PhiErr;
  std::vector<float>*   Dtrk2PhiErr;
  std::vector<float>*   Dtrk1Y;
  std::vector<float>*   Dtrk2Y;
  std::vector<float>*   Dtrk1D0Err;
  std::vector<float>*   Dtrk2D0Err;
  std::vector<float>*   Dtrk1MVAVal;
  std::vector<float>*   Dtrk2MVAVal;
  std::vector<int>*     Dtrk1Quality;
  std::vector<int>*     Dtrk2Quality;
  std::vector<int>*     Dtrk3Idx;
  std::vector<int>*     Dtrk4Idx;
  std::vector<float>*   Dtrk3EtaErr;
  std::vector<float>*   Dtrk4EtaErr;
  std::vector<float>*   Dtrk3PhiErr;
  std::vector<float>*   Dtrk4PhiErr;
  std::vector<float>*   Dtrk3Y;
  std::vector<float>*   Dtrk4Y;
  std::vector<float>*   Dtrk3D0Err;
  std::vector<float>*   Dtrk4D0Err;
  std::vector<float>*   Dtrk3MVAVal;
  std::vector<float>*   Dtrk4MVAVal;
  std::vector<int>*     Dtrk3Quality;
  std::vector<int>*     Dtrk4Quality;
  std::vector<float>*   DtktkResmass;
  std::vector<float>*   DtktkRespt;
  std::vector<float>*   DtktkReseta;
  std::vector<float>*   DtktkResphi;
  std::vector<float>*   DRestrk1Pt;
  std::vector<float>*   DRestrk1Eta;
  std::vector<float>*   DRestrk1Phi;
  std::vector<float>*   DRestrk1Y;
  std::vector<float>*   DRestrk1Dxy;
  std::vector<float>*   DRestrk1D0Err;
  std::vector<int>*     DRestrk1originalAlgo;
  std::vector<float>*   DRestrk2Pt;
  std::vector<float>*   DRestrk2Eta;
  std::vector<float>*   DRestrk2Phi;
  std::vector<float>*   DRestrk2Y;
  std::vector<float>*   DRestrk2Dxy;
  std::vector<float>*   DRestrk2D0Err;
  std::vector<int>*     DRestrk2originalAlgo;
  std::vector<float>*   DRestrk3Pt;
  std::vector<float>*   DRestrk3Eta;
  std::vector<float>*   DRestrk3Phi;
  std::vector<float>*   DRestrk3Y;
  std::vector<float>*   DRestrk3Dxy;
  std::vector<float>*   DRestrk3D0Err;
  std::vector<int>*     DRestrk3originalAlgo;
  std::vector<float>*   DRestrk4Pt;
  std::vector<float>*   DRestrk4Eta;
  std::vector<float>*   DRestrk4Phi;
  std::vector<float>*   DRestrk4Y;
  std::vector<float>*   DRestrk4Dxy;
  std::vector<float>*   DRestrk4D0Err;
  std::vector<int>*     DRestrk4originalAlgo;
  std::vector<float>*   Dgen;
  std::vector<int>*     DgenIndex;
  std::vector<int>*     DgennDa;
  std::vector<float>*   Dgenpt;
  std::vector<float>*   Dgeneta;
  std::vector<float>*   Dgenphi;
  std::vector<float>*   Dgeny;
  std::vector<int>*     DgencollisionId;
  std::vector<float>*   DgenBAncestorpt;
  std::vector<int>*     DgenBAncestorpdgId;
  Int_t                 Gsize;
  std::vector<float>*   Gy;
  std::vector<float>*   Geta;
  std::vector<float>*   Gphi;
  std::vector<float>*   Gpt;
  std::vector<int>*     GpdgId;
  std::vector<int>*     GcollisionId;
  std::vector<int>*     GisSignal;
  std::vector<float>*   GBAncestorpt;
  std::vector<int>*     GBAncestorpdgId;
  std::vector<float>*   Gtk1pt;
  std::vector<float>*   Gtk1eta;
  std::vector<float>*   Gtk1y;
  std::vector<float>*   Gtk1phi;
  std::vector<float>*   Gtk2pt;
  std::vector<float>*   Gtk2eta;
  std::vector<float>*   Gtk2y;
  std::vector<float>*   Gtk2phi;
  Float_t               pthatweight;
  Float_t               maxDgenpt;

  const static int ncases = 4;
  TString                aDopt[ncases]     =   {"reco",               "gen",                "reco",            "gen"};
  int*                   anD[ncases]       =   {&Dsize,               &Gsize,               &Dsize,            &Gsize};
  std::vector<float>**   aDpt[ncases]      =   {&Dpt,                 &Gpt,                 &Dpt,              &Gpt};
  std::vector<float>**   aDeta[ncases]     =   {&Deta,                &Geta,                &Deta,             &Geta};
  std::vector<float>**   aDphi[ncases]     =   {&Dphi,                &Gphi,                &Dphi,             &Gphi};
  TString                ajetopt[ncases]   =   {"reco",               "reco",               "gen",             "gen"};
  int*                   anjet[ncases]     =   {&njet_akpu3pf,        &njet_akpu3pf,        &ngen_akpu3pf,     &ngen_akpu3pf};
  std::vector<float>**   ajetpt[ncases]    =   {&jetpt_akpu3pf,       &jetpt_akpu3pf,       &genpt_akpu3pf,    &genpt_akpu3pf};
  std::vector<float>**   ajeteta[ncases]   =   {&jeteta_akpu3pf,      &jeteta_akpu3pf,      &geneta_akpu3pf,   &geneta_akpu3pf};
  std::vector<float>**   ajetphi[ncases]   =   {&jetphi_akpu3pf,      &jetphi_akpu3pf,      &genphi_akpu3pf,   &genphi_akpu3pf};
  std::vector<int>**     asubid[ncases]    =   {&subid_akpu3pf,       &subid_akpu3pf,       &gensubid_akpu3pf, &gensubid_akpu3pf};

  Int_t HLT_AK4Jet40;
  Int_t HLT_AK4Jet60;
  Int_t HLT_AK4Jet80;

  // djet(TTree* tree=0);
  djet(TString infname, Int_t ispp, Int_t isMC);
  virtual ~djet();
  virtual void Show(Long64_t entry = -1);

  void settrkcut(Float_t _cut_trkPt, Float_t _cut_trkEta, Float_t _cut_trkPtErr);
  void setDcut(Float_t _cut_Dsvpv, Float_t _cut_Dalpha, Float_t _cut_Dchi2cl, Float_t _cut_Dy);
  void setGcut(Float_t _cut_Gy);
  void setjetcut(Float_t _cut_jetpt_min, Float_t _cut_jeteta_min, Float_t _cut_jeteta_max);
  void setbindepcut(Float_t _cut_Dsvpv, Float_t _cut_Dalpha);
  int isDselected(Int_t j, Option_t* option);
  int isjetselected(Int_t j, Option_t* option);
  int ishltselected(Option_t* option);

  Float_t           cut_trkPt;
  Float_t           cut_trkEta;
  Float_t           cut_trkPtErr;
  Float_t           cut_Dsvpv;
  Float_t           cut_Dalpha;
  Float_t           cut_Dchi2cl;
  Float_t           cut_Dy;
  Float_t           cut_Gy;
  Float_t           cut_jetpt_min;
  Float_t           cut_jeteta_min;
  Float_t           cut_jeteta_max;

private:
  Int_t             fispp;
  Int_t             fisMC;

  Float_t           fsettrkcut;
  Float_t           fsetDcut;
  Float_t           fsetGcut;
  Float_t           fsetjetcut;

  virtual void Init(TTree *tree, TTree *hlt);
  virtual Bool_t Notify();
  virtual void Init_member();

};

/*
  djet::djet(TTree* tree) : fChain(0) 
  {
  Init_member();
  if(tree==0) return;
  Init(tree);
  }
*/

djet::djet(TString infname, Int_t ispp, Int_t isMC) : fChain(0), fHlt(0), fispp(ispp), fisMC(isMC)
{
  TFile* inf = new TFile(infname.Data());
  if(!inf->IsOpen()) return;
  TTree* tree = (TTree*)inf->Get("djt");
  if(!tree) return;
  TTree* hlt = (TTree*)inf->Get("hlt");
  if(!hlt) return;
  Init_member();
  Init(tree, hlt);
}

void djet::Init_member()
{
  fsettrkcut = false;
  cut_trkPt = -99;
  cut_trkEta = -99;
  cut_trkPtErr = -99;

  fsetDcut = false;  
  cut_Dsvpv = -99;
  cut_Dalpha = -99;
  cut_Dchi2cl = -99;
  cut_Dy = -99;

  fsetGcut = false;
  cut_Gy = -99;

  fsetjetcut = false;
  cut_jetpt_min = -99;
  cut_jeteta_min = -99;
  cut_jeteta_max = -99;
}

djet::~djet()
{
  if(!fChain) return;
  delete fChain->GetCurrentFile();
}

void djet::Init(TTree *tree, TTree *hlt)
{
  // Set object pointer
  jetptCorr_akpu3pf = 0;
  jetpt_akpu3pf = 0;
  jeteta_akpu3pf = 0;
  jetphi_akpu3pf = 0;
  gjetpt_akpu3pf = 0;
  gjeteta_akpu3pf = 0;
  gjetphi_akpu3pf = 0;
  gjetflavor_akpu3pf = 0;
  chargedSum_akpu3pf = 0;
  subid_akpu3pf = 0;
  genpt_akpu3pf = 0;
  geneta_akpu3pf = 0;
  genphi_akpu3pf = 0;
  gensubid_akpu3pf = 0;
  jetptCorr_akpu4pf = 0;
  jetpt_akpu4pf = 0;
  jeteta_akpu4pf = 0;
  jetphi_akpu4pf = 0;
  gjetpt_akpu4pf = 0;
  gjeteta_akpu4pf = 0;
  gjetphi_akpu4pf = 0;
  gjetflavor_akpu4pf = 0;
  chargedSum_akpu4pf = 0;
  subid_akpu4pf = 0;
  genpt_akpu4pf = 0;
  geneta_akpu4pf = 0;
  genphi_akpu4pf = 0;
  gensubid_akpu4pf = 0;
  Dindex = 0;
  Dtype = 0;
  Dmass = 0;
  Dpt = 0;
  Deta = 0;
  Dphi = 0;
  Dy = 0;
  DvtxX = 0;
  DvtxY = 0;
  Dd0 = 0;
  Dd0Err = 0;
  Ddxyz = 0;
  DdxyzErr = 0;
  Dchi2ndf = 0;
  Dchi2cl = 0;
  Ddtheta = 0;
  Dlxy = 0;
  Dalpha = 0;
  DsvpvDistance = 0;
  DsvpvDisErr = 0;
  DsvpvDistance_2D = 0;
  DsvpvDisErr_2D = 0;
  DtktkRes_chi2ndf = 0;
  DtktkRes_chi2cl = 0;
  DtktkRes_alpha = 0;
  DtktkRes_svpvDistance = 0;
  DtktkRes_svpvDisErr = 0;
  DlxyBS = 0;
  DlxyBSErr = 0;
  DMaxDoca = 0;
  Dtrk1Pt = 0;
  Dtrk2Pt = 0;
  Dtrk1Eta = 0;
  Dtrk2Eta = 0;
  Dtrk1Phi = 0;
  Dtrk2Phi = 0;
  Dtrk1PtErr = 0;
  Dtrk2PtErr = 0;
  Dtrk1Dxy = 0;
  Dtrk2Dxy = 0;
  Dtrk1PixelHit = 0;
  Dtrk2PixelHit = 0;
  Dtrk1StripHit = 0;
  Dtrk2StripHit = 0;
  Dtrk1nStripLayer = 0;
  Dtrk2nStripLayer = 0;
  Dtrk1nPixelLayer = 0;
  Dtrk2nPixelLayer = 0;
  Dtrk1Chi2ndf = 0;
  Dtrk2Chi2ndf = 0;
  Dtrk1MassHypo = 0;
  Dtrk2MassHypo = 0;
  Dtrk1Algo = 0;
  Dtrk2Algo = 0;
  Dtrk1originalAlgo = 0;
  Dtrk2originalAlgo = 0;
  Dtrk1highPurity = 0;
  Dtrk2highPurity = 0;
  Dtrk3Pt = 0;
  Dtrk4Pt = 0;
  Dtrk3Eta = 0;
  Dtrk4Eta = 0;
  Dtrk3Phi = 0;
  Dtrk4Phi = 0;
  Dtrk3PtErr = 0;
  Dtrk4PtErr = 0;
  Dtrk3Dxy = 0;
  Dtrk4Dxy = 0;
  Dtrk3PixelHit = 0;
  Dtrk4PixelHit = 0;
  Dtrk3StripHit = 0;
  Dtrk4StripHit = 0;
  Dtrk3nStripLayer = 0;
  Dtrk4nStripLayer = 0;
  Dtrk3nPixelLayer = 0;
  Dtrk4nPixelLayer = 0;
  Dtrk3Chi2ndf = 0;
  Dtrk4Chi2ndf = 0;
  Dtrk3MassHypo = 0;
  Dtrk4MassHypo = 0;
  Dtrk3Algo = 0;
  Dtrk4Algo = 0;
  Dtrk3originalAlgo = 0;
  Dtrk4originalAlgo = 0;
  Dtrk3highPurity = 0;
  Dtrk4highPurity = 0;
  Dtrk1Idx = 0;
  Dtrk2Idx = 0;
  Dtrk1EtaErr = 0;
  Dtrk2EtaErr = 0;
  Dtrk1PhiErr = 0;
  Dtrk2PhiErr = 0;
  Dtrk1Y = 0;
  Dtrk2Y = 0;
  Dtrk1D0Err = 0;
  Dtrk2D0Err = 0;
  Dtrk1MVAVal = 0;
  Dtrk2MVAVal = 0;
  Dtrk1Quality = 0;
  Dtrk2Quality = 0;
  Dtrk3Idx = 0;
  Dtrk4Idx = 0;
  Dtrk3EtaErr = 0;
  Dtrk4EtaErr = 0;
  Dtrk3PhiErr = 0;
  Dtrk4PhiErr = 0;
  Dtrk3Y = 0;
  Dtrk4Y = 0;
  Dtrk3D0Err = 0;
  Dtrk4D0Err = 0;
  Dtrk3MVAVal = 0;
  Dtrk4MVAVal = 0;
  Dtrk3Quality = 0;
  Dtrk4Quality = 0;
  DtktkResmass = 0;
  DtktkRespt = 0;
  DtktkReseta = 0;
  DtktkResphi = 0;
  DRestrk1Pt = 0;
  DRestrk1Eta = 0;
  DRestrk1Phi = 0;
  DRestrk1Y = 0;
  DRestrk1Dxy = 0;
  DRestrk1D0Err = 0;
  DRestrk1originalAlgo = 0;
  DRestrk2Pt = 0;
  DRestrk2Eta = 0;
  DRestrk2Phi = 0;
  DRestrk2Y = 0;
  DRestrk2Dxy = 0;
  DRestrk2D0Err = 0;
  DRestrk2originalAlgo = 0;
  DRestrk3Pt = 0;
  DRestrk3Eta = 0;
  DRestrk3Phi = 0;
  DRestrk3Y = 0;
  DRestrk3Dxy = 0;
  DRestrk3D0Err = 0;
  DRestrk3originalAlgo = 0;
  DRestrk4Pt = 0;
  DRestrk4Eta = 0;
  DRestrk4Phi = 0;
  DRestrk4Y = 0;
  DRestrk4Dxy = 0;
  DRestrk4D0Err = 0;
  DRestrk4originalAlgo = 0;
  Dgen = 0;
  DgenIndex = 0;
  DgennDa = 0;
  Dgenpt = 0;
  Dgeneta = 0;
  Dgenphi = 0;
  Dgeny = 0;
  DgencollisionId = 0;
  DgenBAncestorpt = 0;
  DgenBAncestorpdgId = 0;
  Gy = 0;
  Geta = 0;
  Gphi = 0;
  Gpt = 0;
  GpdgId = 0;
  GcollisionId = 0;
  GisSignal = 0;
  GBAncestorpt = 0;
  GBAncestorpdgId = 0;
  Gtk1pt = 0;
  Gtk1eta = 0;
  Gtk1y = 0;
  Gtk1phi = 0;
  Gtk2pt = 0;
  Gtk2eta = 0;
  Gtk2y = 0;
  Gtk2phi = 0;

  // Set branch addresses and branch pointers
  if(!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("isPP", &isPP);
  fChain->SetBranchAddress("run", &run);
  fChain->SetBranchAddress("evt", &evt);
  fChain->SetBranchAddress("lumi", &lumi);
  fChain->SetBranchAddress("hiBin", &hiBin);
  fChain->SetBranchAddress("vz", &vz);
  fChain->SetBranchAddress("weight", &weight);
  fChain->SetBranchAddress("pthat", &pthat);
  fChain->SetBranchAddress("hiEvtPlanes", hiEvtPlanes);
  fChain->SetBranchAddress("njet_akpu3pf", &njet_akpu3pf);
  fChain->SetBranchAddress("jetptCorr_akpu3pf", &jetptCorr_akpu3pf);
  fChain->SetBranchAddress("jetpt_akpu3pf", &jetpt_akpu3pf);
  fChain->SetBranchAddress("jeteta_akpu3pf", &jeteta_akpu3pf);
  fChain->SetBranchAddress("jetphi_akpu3pf", &jetphi_akpu3pf);
  fChain->SetBranchAddress("gjetpt_akpu3pf", &gjetpt_akpu3pf);
  fChain->SetBranchAddress("gjeteta_akpu3pf", &gjeteta_akpu3pf);
  fChain->SetBranchAddress("gjetphi_akpu3pf", &gjetphi_akpu3pf);
  fChain->SetBranchAddress("gjetflavor_akpu3pf", &gjetflavor_akpu3pf);
  fChain->SetBranchAddress("chargedSum_akpu3pf", &chargedSum_akpu3pf);
  fChain->SetBranchAddress("subid_akpu3pf", &subid_akpu3pf);
  fChain->SetBranchAddress("ngen_akpu3pf", &ngen_akpu3pf);
  fChain->SetBranchAddress("genpt_akpu3pf", &genpt_akpu3pf);
  fChain->SetBranchAddress("geneta_akpu3pf", &geneta_akpu3pf);
  fChain->SetBranchAddress("genphi_akpu3pf", &genphi_akpu3pf);
  fChain->SetBranchAddress("gensubid_akpu3pf", &gensubid_akpu3pf);
  fChain->SetBranchAddress("njet_akpu4pf", &njet_akpu4pf);
  fChain->SetBranchAddress("jetptCorr_akpu4pf", &jetptCorr_akpu4pf);
  fChain->SetBranchAddress("jetpt_akpu4pf", &jetpt_akpu4pf);
  fChain->SetBranchAddress("jeteta_akpu4pf", &jeteta_akpu4pf);
  fChain->SetBranchAddress("jetphi_akpu4pf", &jetphi_akpu4pf);
  fChain->SetBranchAddress("gjetpt_akpu4pf", &gjetpt_akpu4pf);
  fChain->SetBranchAddress("gjeteta_akpu4pf", &gjeteta_akpu4pf);
  fChain->SetBranchAddress("gjetphi_akpu4pf", &gjetphi_akpu4pf);
  fChain->SetBranchAddress("gjetflavor_akpu4pf", &gjetflavor_akpu4pf);
  fChain->SetBranchAddress("chargedSum_akpu4pf", &chargedSum_akpu4pf);
  fChain->SetBranchAddress("subid_akpu4pf", &subid_akpu4pf);
  fChain->SetBranchAddress("ngen_akpu4pf", &ngen_akpu4pf);
  fChain->SetBranchAddress("genpt_akpu4pf", &genpt_akpu4pf);
  fChain->SetBranchAddress("geneta_akpu4pf", &geneta_akpu4pf);
  fChain->SetBranchAddress("genphi_akpu4pf", &genphi_akpu4pf);
  fChain->SetBranchAddress("gensubid_akpu4pf", &gensubid_akpu4pf);
  fChain->SetBranchAddress("RunNo", &RunNo);
  fChain->SetBranchAddress("EvtNo", &EvtNo);
  fChain->SetBranchAddress("LumiNo", &LumiNo);
  fChain->SetBranchAddress("Dsize", &Dsize);
  fChain->SetBranchAddress("PVx", &PVx);
  fChain->SetBranchAddress("PVy", &PVy);
  fChain->SetBranchAddress("PVz", &PVz);
  fChain->SetBranchAddress("PVnchi2", &PVnchi2);
  fChain->SetBranchAddress("BSx", &BSx);
  fChain->SetBranchAddress("BSy", &BSy);
  fChain->SetBranchAddress("BSz", &BSz);
  fChain->SetBranchAddress("PVxE", &PVxE);
  fChain->SetBranchAddress("PVyE", &PVyE);
  fChain->SetBranchAddress("PVzE", &PVzE);
  fChain->SetBranchAddress("BSxErr", &BSxErr);
  fChain->SetBranchAddress("BSyErr", &BSyErr);
  fChain->SetBranchAddress("BSzErr", &BSzErr);
  fChain->SetBranchAddress("BSdxdz", &BSdxdz);
  fChain->SetBranchAddress("BSdydz", &BSdydz);
  fChain->SetBranchAddress("BSdxdzErr", &BSdxdzErr);                           
  fChain->SetBranchAddress("BSdydzErr", &BSdydzErr);
  fChain->SetBranchAddress("BSWidthX", &BSWidthX);
  fChain->SetBranchAddress("BSWidthXErr", &BSWidthXErr);
  fChain->SetBranchAddress("BSWidthY", &BSWidthY);
  fChain->SetBranchAddress("BSWidthYErr", &BSWidthYErr);
  fChain->SetBranchAddress("Dindex", &Dindex);
  fChain->SetBranchAddress("Dtype", &Dtype);
  fChain->SetBranchAddress("Dmass", &Dmass);
  fChain->SetBranchAddress("Dpt", &Dpt);
  fChain->SetBranchAddress("Deta", &Deta);
  fChain->SetBranchAddress("Dphi", &Dphi);
  fChain->SetBranchAddress("Dy", &Dy);
  fChain->SetBranchAddress("DvtxX", &DvtxX);
  fChain->SetBranchAddress("DvtxY", &DvtxY);
  fChain->SetBranchAddress("Dd0", &Dd0);
  fChain->SetBranchAddress("Dd0Err", &Dd0Err);
  fChain->SetBranchAddress("Ddxyz", &Ddxyz);
  fChain->SetBranchAddress("DdxyzErr", &DdxyzErr);
  fChain->SetBranchAddress("Dchi2ndf", &Dchi2ndf);
  fChain->SetBranchAddress("Dchi2cl", &Dchi2cl);
  fChain->SetBranchAddress("Ddtheta", &Ddtheta);
  fChain->SetBranchAddress("Dlxy", &Dlxy);
  fChain->SetBranchAddress("Dalpha", &Dalpha);
  fChain->SetBranchAddress("DsvpvDistance", &DsvpvDistance);
  fChain->SetBranchAddress("DsvpvDisErr", &DsvpvDisErr);
  fChain->SetBranchAddress("DsvpvDistance_2D", &DsvpvDistance_2D);
  fChain->SetBranchAddress("DsvpvDisErr_2D", &DsvpvDisErr_2D);
  fChain->SetBranchAddress("DtktkRes_chi2ndf", &DtktkRes_chi2ndf);
  fChain->SetBranchAddress("DtktkRes_chi2cl", &DtktkRes_chi2cl);
  fChain->SetBranchAddress("DtktkRes_alpha", &DtktkRes_alpha);
  fChain->SetBranchAddress("DtktkRes_svpvDistance", &DtktkRes_svpvDistance);
  fChain->SetBranchAddress("DtktkRes_svpvDisErr", &DtktkRes_svpvDisErr);
  fChain->SetBranchAddress("DlxyBS", &DlxyBS);
  fChain->SetBranchAddress("DlxyBSErr", &DlxyBSErr);
  fChain->SetBranchAddress("DMaxDoca", &DMaxDoca);
  fChain->SetBranchAddress("Dtrk1Pt", &Dtrk1Pt);
  fChain->SetBranchAddress("Dtrk2Pt", &Dtrk2Pt);
  fChain->SetBranchAddress("Dtrk1Eta", &Dtrk1Eta);
  fChain->SetBranchAddress("Dtrk2Eta", &Dtrk2Eta);
  fChain->SetBranchAddress("Dtrk1Phi", &Dtrk1Phi);
  fChain->SetBranchAddress("Dtrk2Phi", &Dtrk2Phi);
  fChain->SetBranchAddress("Dtrk1PtErr", &Dtrk1PtErr);
  fChain->SetBranchAddress("Dtrk2PtErr", &Dtrk2PtErr);
  fChain->SetBranchAddress("Dtrk1Dxy", &Dtrk1Dxy);
  fChain->SetBranchAddress("Dtrk2Dxy", &Dtrk2Dxy);
  fChain->SetBranchAddress("Dtrk1PixelHit", &Dtrk1PixelHit);
  fChain->SetBranchAddress("Dtrk2PixelHit", &Dtrk2PixelHit);
  fChain->SetBranchAddress("Dtrk1StripHit", &Dtrk1StripHit);
  fChain->SetBranchAddress("Dtrk2StripHit", &Dtrk2StripHit);
  fChain->SetBranchAddress("Dtrk1nStripLayer", &Dtrk1nStripLayer);
  fChain->SetBranchAddress("Dtrk2nStripLayer", &Dtrk2nStripLayer);
  fChain->SetBranchAddress("Dtrk1nPixelLayer", &Dtrk1nPixelLayer);
  fChain->SetBranchAddress("Dtrk2nPixelLayer", &Dtrk2nPixelLayer);
  fChain->SetBranchAddress("Dtrk1Chi2ndf", &Dtrk1Chi2ndf);
  fChain->SetBranchAddress("Dtrk2Chi2ndf", &Dtrk2Chi2ndf);
  fChain->SetBranchAddress("Dtrk1MassHypo", &Dtrk1MassHypo);
  fChain->SetBranchAddress("Dtrk2MassHypo", &Dtrk2MassHypo);
  fChain->SetBranchAddress("Dtrk1Algo", &Dtrk1Algo);
  fChain->SetBranchAddress("Dtrk2Algo", &Dtrk2Algo);
  fChain->SetBranchAddress("Dtrk1originalAlgo", &Dtrk1originalAlgo);
  fChain->SetBranchAddress("Dtrk2originalAlgo", &Dtrk2originalAlgo);
  fChain->SetBranchAddress("Dtrk1highPurity", &Dtrk1highPurity);
  fChain->SetBranchAddress("Dtrk2highPurity", &Dtrk2highPurity);
  fChain->SetBranchAddress("Dtrk3Pt", &Dtrk3Pt);
  fChain->SetBranchAddress("Dtrk4Pt", &Dtrk4Pt);
  fChain->SetBranchAddress("Dtrk3Eta", &Dtrk3Eta);
  fChain->SetBranchAddress("Dtrk4Eta", &Dtrk4Eta);
  fChain->SetBranchAddress("Dtrk3Phi", &Dtrk3Phi);
  fChain->SetBranchAddress("Dtrk4Phi", &Dtrk4Phi);
  fChain->SetBranchAddress("Dtrk3PtErr", &Dtrk3PtErr);
  fChain->SetBranchAddress("Dtrk4PtErr", &Dtrk4PtErr);
  fChain->SetBranchAddress("Dtrk3Dxy", &Dtrk3Dxy);
  fChain->SetBranchAddress("Dtrk4Dxy", &Dtrk4Dxy);
  fChain->SetBranchAddress("Dtrk3PixelHit", &Dtrk3PixelHit);
  fChain->SetBranchAddress("Dtrk4PixelHit", &Dtrk4PixelHit);
  fChain->SetBranchAddress("Dtrk3StripHit", &Dtrk3StripHit);
  fChain->SetBranchAddress("Dtrk4StripHit", &Dtrk4StripHit);
  fChain->SetBranchAddress("Dtrk3nStripLayer", &Dtrk3nStripLayer);
  fChain->SetBranchAddress("Dtrk4nStripLayer", &Dtrk4nStripLayer);
  fChain->SetBranchAddress("Dtrk3nPixelLayer", &Dtrk3nPixelLayer);
  fChain->SetBranchAddress("Dtrk4nPixelLayer", &Dtrk4nPixelLayer);
  fChain->SetBranchAddress("Dtrk3Chi2ndf", &Dtrk3Chi2ndf);
  fChain->SetBranchAddress("Dtrk4Chi2ndf", &Dtrk4Chi2ndf);
  fChain->SetBranchAddress("Dtrk3MassHypo", &Dtrk3MassHypo);
  fChain->SetBranchAddress("Dtrk4MassHypo", &Dtrk4MassHypo);
  fChain->SetBranchAddress("Dtrk3Algo", &Dtrk3Algo);
  fChain->SetBranchAddress("Dtrk4Algo", &Dtrk4Algo);
  fChain->SetBranchAddress("Dtrk3originalAlgo", &Dtrk3originalAlgo);
  fChain->SetBranchAddress("Dtrk4originalAlgo", &Dtrk4originalAlgo);
  fChain->SetBranchAddress("Dtrk3highPurity", &Dtrk3highPurity);
  fChain->SetBranchAddress("Dtrk4highPurity", &Dtrk4highPurity);
  fChain->SetBranchAddress("Dtrk1Idx", &Dtrk1Idx);
  fChain->SetBranchAddress("Dtrk2Idx", &Dtrk2Idx);
  fChain->SetBranchAddress("Dtrk1EtaErr", &Dtrk1EtaErr);
  fChain->SetBranchAddress("Dtrk2EtaErr", &Dtrk2EtaErr);
  fChain->SetBranchAddress("Dtrk1PhiErr", &Dtrk1PhiErr);
  fChain->SetBranchAddress("Dtrk2PhiErr", &Dtrk2PhiErr);
  fChain->SetBranchAddress("Dtrk1Y", &Dtrk1Y);
  fChain->SetBranchAddress("Dtrk2Y", &Dtrk2Y);
  fChain->SetBranchAddress("Dtrk1D0Err", &Dtrk1D0Err);
  fChain->SetBranchAddress("Dtrk2D0Err", &Dtrk2D0Err);
  fChain->SetBranchAddress("Dtrk1MVAVal", &Dtrk1MVAVal);
  fChain->SetBranchAddress("Dtrk2MVAVal", &Dtrk2MVAVal);
  fChain->SetBranchAddress("Dtrk1Quality", &Dtrk1Quality);
  fChain->SetBranchAddress("Dtrk2Quality", &Dtrk2Quality);
  fChain->SetBranchAddress("Dtrk3Idx", &Dtrk3Idx);
  fChain->SetBranchAddress("Dtrk4Idx", &Dtrk4Idx);
  fChain->SetBranchAddress("Dtrk3EtaErr", &Dtrk3EtaErr);
  fChain->SetBranchAddress("Dtrk4EtaErr", &Dtrk4EtaErr);
  fChain->SetBranchAddress("Dtrk3PhiErr", &Dtrk3PhiErr);
  fChain->SetBranchAddress("Dtrk4PhiErr", &Dtrk4PhiErr);
  fChain->SetBranchAddress("Dtrk3Y", &Dtrk3Y);
  fChain->SetBranchAddress("Dtrk4Y", &Dtrk4Y);
  fChain->SetBranchAddress("Dtrk3D0Err", &Dtrk3D0Err);
  fChain->SetBranchAddress("Dtrk4D0Err", &Dtrk4D0Err);
  fChain->SetBranchAddress("Dtrk3MVAVal", &Dtrk3MVAVal);
  fChain->SetBranchAddress("Dtrk4MVAVal", &Dtrk4MVAVal);
  fChain->SetBranchAddress("Dtrk3Quality", &Dtrk3Quality);
  fChain->SetBranchAddress("Dtrk4Quality", &Dtrk4Quality);
  fChain->SetBranchAddress("DtktkResmass", &DtktkResmass);
  fChain->SetBranchAddress("DtktkRespt", &DtktkRespt);
  fChain->SetBranchAddress("DtktkReseta", &DtktkReseta);
  fChain->SetBranchAddress("DtktkResphi", &DtktkResphi);
  fChain->SetBranchAddress("DRestrk1Pt", &DRestrk1Pt);
  fChain->SetBranchAddress("DRestrk1Eta", &DRestrk1Eta);
  fChain->SetBranchAddress("DRestrk1Phi", &DRestrk1Phi);
  fChain->SetBranchAddress("DRestrk1Y", &DRestrk1Y);
  fChain->SetBranchAddress("DRestrk1Dxy", &DRestrk1Dxy);
  fChain->SetBranchAddress("DRestrk1D0Err", &DRestrk1D0Err);
  fChain->SetBranchAddress("DRestrk1originalAlgo", &DRestrk1originalAlgo);
  fChain->SetBranchAddress("DRestrk2Pt", &DRestrk2Pt);
  fChain->SetBranchAddress("DRestrk2Eta", &DRestrk2Eta);
  fChain->SetBranchAddress("DRestrk2Phi", &DRestrk2Phi);
  fChain->SetBranchAddress("DRestrk2Y", &DRestrk2Y);
  fChain->SetBranchAddress("DRestrk2Dxy", &DRestrk2Dxy);
  fChain->SetBranchAddress("DRestrk2D0Err", &DRestrk2D0Err);
  fChain->SetBranchAddress("DRestrk2originalAlgo", &DRestrk2originalAlgo);
  fChain->SetBranchAddress("DRestrk3Pt", &DRestrk3Pt);
  fChain->SetBranchAddress("DRestrk3Eta", &DRestrk3Eta);
  fChain->SetBranchAddress("DRestrk3Phi", &DRestrk3Phi);
  fChain->SetBranchAddress("DRestrk3Y", &DRestrk3Y);
  fChain->SetBranchAddress("DRestrk3Dxy", &DRestrk3Dxy);
  fChain->SetBranchAddress("DRestrk3D0Err", &DRestrk3D0Err);
  fChain->SetBranchAddress("DRestrk3originalAlgo", &DRestrk3originalAlgo);
  fChain->SetBranchAddress("DRestrk4Pt", &DRestrk4Pt);
  fChain->SetBranchAddress("DRestrk4Eta", &DRestrk4Eta);
  fChain->SetBranchAddress("DRestrk4Phi", &DRestrk4Phi);
  fChain->SetBranchAddress("DRestrk4Y", &DRestrk4Y);
  fChain->SetBranchAddress("DRestrk4Dxy", &DRestrk4Dxy);
  fChain->SetBranchAddress("DRestrk4D0Err", &DRestrk4D0Err);
  fChain->SetBranchAddress("DRestrk4originalAlgo", &DRestrk4originalAlgo);
  fChain->SetBranchAddress("Dgen", &Dgen);
  fChain->SetBranchAddress("DgenIndex", &DgenIndex);
  fChain->SetBranchAddress("DgennDa", &DgennDa);
  fChain->SetBranchAddress("Dgenpt", &Dgenpt);
  fChain->SetBranchAddress("Dgeneta", &Dgeneta);
  fChain->SetBranchAddress("Dgenphi", &Dgenphi);
  fChain->SetBranchAddress("Dgeny", &Dgeny);
  fChain->SetBranchAddress("DgencollisionId", &DgencollisionId);
  fChain->SetBranchAddress("DgenBAncestorpt", &DgenBAncestorpt);
  fChain->SetBranchAddress("DgenBAncestorpdgId", &DgenBAncestorpdgId);
  fChain->SetBranchAddress("Gsize", &Gsize);
  fChain->SetBranchAddress("Gy", &Gy);
  fChain->SetBranchAddress("Geta", &Geta);
  fChain->SetBranchAddress("Gphi", &Gphi);
  fChain->SetBranchAddress("Gpt", &Gpt);
  fChain->SetBranchAddress("GpdgId", &GpdgId);
  fChain->SetBranchAddress("GcollisionId", &GcollisionId);
  fChain->SetBranchAddress("GisSignal", &GisSignal);
  fChain->SetBranchAddress("GBAncestorpt", &GBAncestorpt);
  fChain->SetBranchAddress("GBAncestorpdgId", &GBAncestorpdgId);
  fChain->SetBranchAddress("Gtk1pt", &Gtk1pt);
  fChain->SetBranchAddress("Gtk1eta", &Gtk1eta);
  fChain->SetBranchAddress("Gtk1y", &Gtk1y);
  fChain->SetBranchAddress("Gtk1phi", &Gtk1phi);
  fChain->SetBranchAddress("Gtk2pt", &Gtk2pt);
  fChain->SetBranchAddress("Gtk2eta", &Gtk2eta);
  fChain->SetBranchAddress("Gtk2y", &Gtk2y);
  fChain->SetBranchAddress("Gtk2phi", &Gtk2phi);
  fChain->SetBranchAddress("pthatweight", &pthatweight);
  fChain->SetBranchAddress("maxDgenpt", &maxDgenpt);

  if(!hlt) return;
  fHlt = hlt;
  fHlt->SetMakeClass(1);
  fHlt->SetBranchStatus("*", 0);
  if(fispp)
    {
      fHlt->SetBranchStatus(fisMC?"HLT_AK4PFJet40_Eta5p1ForPPRef_v1":"HLT_AK4PFJet40_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_AK4PFJet60_Eta5p1ForPPRef_v1":"HLT_AK4PFJet60_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_AK4PFJet80_Eta5p1ForPPRef_v1":"HLT_AK4PFJet80_Eta5p1_v1", 1);
      fHlt->SetBranchAddress(fisMC?"HLT_AK4PFJet40_Eta5p1ForPPRef_v1":"HLT_AK4PFJet40_Eta5p1_v1", &HLT_AK4Jet40);
      fHlt->SetBranchAddress(fisMC?"HLT_AK4PFJet60_Eta5p1ForPPRef_v1":"HLT_AK4PFJet60_Eta5p1_v1", &HLT_AK4Jet60);
      fHlt->SetBranchAddress(fisMC?"HLT_AK4PFJet80_Eta5p1ForPPRef_v1":"HLT_AK4PFJet80_Eta5p1_v1", &HLT_AK4Jet80);
    }
  else
    {
      fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet40_Eta5p1_v2":"HLT_HIPuAK4CaloJet40_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet60_Eta5p1_v2":"HLT_HIPuAK4CaloJet60_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet80_Eta5p1_v2":"HLT_HIPuAK4CaloJet80_Eta5p1_v1", 1);
      fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet40_Eta5p1_v2":"HLT_HIPuAK4CaloJet40_Eta5p1_v1", &HLT_AK4Jet40);
      fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet60_Eta5p1_v2":"HLT_HIPuAK4CaloJet60_Eta5p1_v1", &HLT_AK4Jet60);
      fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet80_Eta5p1_v2":"HLT_HIPuAK4CaloJet80_Eta5p1_v1", &HLT_AK4Jet80);      
    }

  Notify();
}

Bool_t djet::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void djet::Show(Long64_t entry)
{
  if(!fChain) return;
  fChain->Show(entry);
}

void djet::settrkcut(Float_t _cut_trkPt, Float_t _cut_trkEta, Float_t _cut_trkPtErr)
{
  cut_trkPt = _cut_trkPt;
  cut_trkEta = _cut_trkEta;
  cut_trkPtErr = _cut_trkPtErr;
  fsettrkcut = true;
}

void djet::setDcut(Float_t _cut_Dsvpv, Float_t _cut_Dalpha, Float_t _cut_Dchi2cl, Float_t _cut_Dy)
{
  cut_Dsvpv = _cut_Dsvpv;
  cut_Dalpha = _cut_Dalpha;
  cut_Dchi2cl = _cut_Dchi2cl;
  cut_Dy = _cut_Dy;
  fsetDcut = true;
}

void djet::setGcut(Float_t _cut_Gy)
{
  cut_Gy = _cut_Gy;
  fsetGcut = true;
}

void djet::setjetcut(Float_t _cut_jetpt_min, Float_t _cut_jeteta_min, Float_t _cut_jeteta_max)
{
  cut_jetpt_min = _cut_jetpt_min;
  cut_jeteta_min = _cut_jeteta_min;
  cut_jeteta_max = _cut_jeteta_max;
  fsetjetcut = true;
}

void djet::setbindepcut(Float_t _cut_Dsvpv, Float_t _cut_Dalpha)
{
  cut_Dsvpv = _cut_Dsvpv;
  cut_Dalpha = _cut_Dalpha;
}

#define _KERROR_SETCUT(obj, Dorjet) {std::cout<<" error: set "<<#obj<<" before judging is"<<#Dorjet<<"selected."<<std::endl; return -1;}

int djet::isDselected(int j, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if((opt.Contains("r") && opt.Contains("g")) || (!opt.Contains("r") && !opt.Contains("g"))) return -2;
  if(opt.Contains("r"))
    {
      if(!fsetDcut) _KERROR_SETCUT(D, D);
      if(!fsettrkcut) _KERROR_SETCUT(trk, D);
      if((*Dtrk1Pt)[j] > cut_trkPt && (*Dtrk2Pt)[j] > cut_trkPt &&
         TMath::Abs((*Dtrk1Eta)[j]) < cut_trkEta && TMath::Abs((*Dtrk2Eta)[j]) < cut_trkEta &&
         ((*Dtrk1PtErr)[j]/(*Dtrk1Pt)[j]) < cut_trkPtErr && ((*Dtrk2PtErr)[j]/(*Dtrk2Pt)[j]) < cut_trkPtErr &&
         (*Dtrk1highPurity)[j] && (*Dtrk2highPurity)[j] &&
         ((*DsvpvDistance)[j]/(*DsvpvDisErr)[j]) > cut_Dsvpv &&
         (*Dalpha)[j] < cut_Dalpha &&
         (*Dchi2cl)[j] >cut_Dchi2cl &&
         TMath::Abs((*Dy)[j]) < cut_Dy) return 1;
      else return 0;
    }
  if(opt.Contains("g"))
    {
      if(!fsetGcut) _KERROR_SETCUT(G, D);
      if(((*GisSignal)[j]==1 || (*GisSignal)[j]==2) &&
         TMath::Abs((*Gy)[j]) < cut_Gy) return 1;
      else return 0;
    }
  return -3;
}

int djet::isjetselected(int j, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if((opt.Contains("r") && opt.Contains("g")) || (!opt.Contains("r") && !opt.Contains("g"))) return -2;
  if(!fsetjetcut) _KERROR_SETCUT(jet, jet);
  if(opt.Contains("r"))
    {
      if((*jetpt_akpu3pf)[j] > cut_jetpt_min && 
         TMath::Abs((*jeteta_akpu3pf)[j]) > cut_jeteta_min && TMath::Abs((*jeteta_akpu3pf)[j]) < cut_jeteta_max) return 1;
      else return 0;
    }
  if(opt.Contains("g"))
    {
      if((*genpt_akpu3pf)[j] > cut_jetpt_min && 
         TMath::Abs((*geneta_akpu3pf)[j]) > cut_jeteta_min && TMath::Abs((*geneta_akpu3pf)[j]) < cut_jeteta_max) return 1;
      else return 0;
    }
  return -3;
}

int djet::ishltselected(Option_t* option)
{
  TString opt = option;
  opt.ToLower();
  
  if(opt=="nohlt") return 1;
  if(opt.Contains("jet40jet60jet80")) return HLT_AK4Jet40||HLT_AK4Jet60||HLT_AK4Jet80;
  if(opt.Contains("jet60jet80") && !opt.Contains("jet40")) return HLT_AK4Jet60||HLT_AK4Jet80;
  if(opt.Contains("jet40jet60") && !opt.Contains("jet80")) return HLT_AK4Jet40||HLT_AK4Jet60;
  if(opt.Contains("jet40") && !opt.Contains("jet60") && !opt.Contains("jet80")) return HLT_AK4Jet40;
  if(opt.Contains("jet60") && !opt.Contains("jet40") && !opt.Contains("jet80")) return HLT_AK4Jet60;
  if(opt.Contains("jet80") && !opt.Contains("jet40") && !opt.Contains("jet60")) return HLT_AK4Jet80;

  std::cout<<"error: invalid option for ishltselected"<<std::endl;
  return -1;

}


#endif
