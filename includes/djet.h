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
  TTree*                fChain; //!pointer to the analyzed TTree or TChain
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
  std::vector<float>*   jetpt_akpu3pf;
  std::vector<float>*   jeteta_akpu3pf;
  std::vector<float>*   jetphi_akpu3pf;
  std::vector<int>*     jetnpfpart_akpu3pf;
  std::vector<float>*   gjetpt_akpu3pf;
  std::vector<float>*   gjeteta_akpu3pf;
  std::vector<float>*   gjetphi_akpu3pf;
  std::vector<int>*     gjetflavor_akpu3pf;
  std::vector<int>*     subid_akpu3pf;

  Int_t                 ngen_akpu3pf;
  std::vector<float>*   genpt_akpu3pf;
  std::vector<float>*   geneta_akpu3pf;
  std::vector<float>*   genphi_akpu3pf;
  std::vector<int>*     gensubid_akpu3pf;

  Int_t                 Dsize;
  std::vector<float>*   Dmass;
  std::vector<float>*   Dpt;
  std::vector<float>*   Deta;
  std::vector<float>*   Dphi;
  std::vector<float>*   Dy;
  std::vector<float>*   Dchi2cl;
  std::vector<float>*   Dalpha;
  std::vector<float>*   DsvpvDistance;
  std::vector<float>*   DsvpvDisErr;
  std::vector<float>*   Dtrk1Pt;
  std::vector<float>*   Dtrk2Pt;
  std::vector<float>*   Dtrk1Eta;
  std::vector<float>*   Dtrk2Eta;
  std::vector<float>*   Dtrk1PtErr;
  std::vector<float>*   Dtrk2PtErr;
  std::vector<bool>*    Dtrk1highPurity;
  std::vector<bool>*    Dtrk2highPurity;
  std::vector<float>*   Dgen;
  std::vector<float>*   Dgenpt;
  std::vector<int>*     DgencollisionId;

  Int_t                 Gsize;
  std::vector<float>*   Gy;
  std::vector<float>*   Geta;
  std::vector<float>*   Gphi;
  std::vector<float>*   Gpt;
  std::vector<int>*     GpdgId;
  std::vector<int>*     GcollisionId;
  std::vector<int>*     GisSignal;
  std::vector<float>*   Gtk1pt;
  std::vector<float>*   Gtk1eta;
  std::vector<float>*   Gtk2pt;
  std::vector<float>*   Gtk2eta;

  Float_t               pthatweight;
  Float_t               maxDgenpt;

  int                   nmix;

  int                   njet_akpu3pf_mix;
  std::vector<float>*   jetpt_akpu3pf_mix;
  std::vector<float>*   jeteta_akpu3pf_mix;
  std::vector<float>*   jetphi_akpu3pf_mix;
  std::vector<int>*     jetnpfpart_akpu3pf_mix;
  std::vector<float>*   gjetpt_akpu3pf_mix;
  std::vector<float>*   gjeteta_akpu3pf_mix;
  std::vector<float>*   gjetphi_akpu3pf_mix;
  std::vector<int>*     gjetflavor_akpu3pf_mix;
  std::vector<int>*     subid_akpu3pf_mix;

  int                   ngen_akpu3pf_mix;
  std::vector<float>*   genpt_akpu3pf_mix;
  std::vector<float>*   geneta_akpu3pf_mix;
  std::vector<float>*   genphi_akpu3pf_mix;
  std::vector<int>*     gensubid_akpu3pf_mix;

  int                   Dsize_mix;
  std::vector<float>*   Dmass_mix;
  std::vector<float>*   Dpt_mix;
  std::vector<float>*   Deta_mix;
  std::vector<float>*   Dphi_mix;
  std::vector<float>*   Dy_mix;
  std::vector<float>*   Dchi2cl_mix;
  std::vector<float>*   Dalpha_mix;
  std::vector<float>*   DsvpvDistance_mix;
  std::vector<float>*   DsvpvDisErr_mix;
  std::vector<float>*   Dtrk1Pt_mix;
  std::vector<float>*   Dtrk2Pt_mix;
  std::vector<float>*   Dtrk1Eta_mix;
  std::vector<float>*   Dtrk2Eta_mix;
  std::vector<float>*   Dtrk1PtErr_mix;
  std::vector<float>*   Dtrk2PtErr_mix;
  std::vector<bool>*    Dtrk1highPurity_mix;
  std::vector<bool>*    Dtrk2highPurity_mix;
  std::vector<float>*   Dgen_mix;
  std::vector<float>*   Dgenpt_mix;
  std::vector<int>*     DgencollisionId_mix;

  int                   Gsize_mix;
  std::vector<float>*   Gy_mix;
  std::vector<float>*   Geta_mix;
  std::vector<float>*   Gphi_mix;
  std::vector<float>*   Gpt_mix;
  std::vector<int>*     GpdgId_mix;
  std::vector<int>*     GcollisionId_mix;
  std::vector<int>*     GisSignal_mix;
  std::vector<float>*   Gtk1pt_mix;
  std::vector<float>*   Gtk1eta_mix;
  std::vector<float>*   Gtk2pt_mix;
  std::vector<float>*   Gtk2eta_mix;

  const static int ncases = 4;
  TString               aDopt[ncases]              =  {"reco",                "gen",                "reco",                "gen"};
  int*                  anD[ncases]                =  {&Dsize,                &Gsize,               &Dsize,                &Gsize};
  std::vector<float>**  aDpt[ncases]               =  {&Dpt,                  &Gpt,                 &Dpt,                  &Gpt};
  std::vector<float>**  aDeta[ncases]              =  {&Deta,                 &Geta,                &Deta,                 &Geta};
  std::vector<float>**  aDphi[ncases]              =  {&Dphi,                 &Gphi,                &Dphi,                 &Gphi};
  std::vector<float>**  aDgenpt[ncases]            =  {&Dgenpt,               &Gpt,                 &Dgenpt,               &Gpt};
  std::vector<int>**    aDcollisionId[ncases]      =  {&DgencollisionId,      &GcollisionId,        &DgencollisionId,      &GcollisionId};

  int*                  anD_mix[ncases]            =  {&Dsize_mix,            &Gsize_mix,           &Dsize_mix,            &Gsize_mix};
  std::vector<float>**  aDpt_mix[ncases]           =  {&Dpt_mix,              &Gpt_mix,             &Dpt_mix,              &Gpt_mix};
  std::vector<float>**  aDeta_mix[ncases]          =  {&Deta_mix,             &Geta_mix,            &Deta_mix,             &Geta_mix};
  std::vector<float>**  aDphi_mix[ncases]          =  {&Dphi_mix,             &Gphi_mix,            &Dphi_mix,             &Gphi_mix};
  std::vector<float>**  aDgenpt_mix[ncases]        =  {&Dgenpt_mix,           &Gpt_mix,             &Dgenpt_mix,           &Gpt_mix};
  std::vector<int>**    aDcollisionId_mix[ncases]  =  {&DgencollisionId_mix,  &GcollisionId_mix,    &DgencollisionId_mix,  &GcollisionId_mix};

  TString               ajetopt[ncases]            =  {"reco",                "reco",               "gen",                 "gen"};
  int*                  anjet[ncases]              =  {&njet_akpu3pf,         &njet_akpu3pf,        &njet_akpu3pf,         &njet_akpu3pf};
  std::vector<float>**  ajetpt[ncases]             =  {&jetpt_akpu3pf,        &jetpt_akpu3pf,       &gjetpt_akpu3pf,       &gjetpt_akpu3pf};
  std::vector<float>**  ajeteta[ncases]            =  {&jeteta_akpu3pf,       &jeteta_akpu3pf,      &gjeteta_akpu3pf,      &gjeteta_akpu3pf};
  std::vector<float>**  ajetphi[ncases]            =  {&jetphi_akpu3pf,       &jetphi_akpu3pf,      &gjetphi_akpu3pf,      &gjetphi_akpu3pf};
  std::vector<int>**    asubid[ncases]             =  {&subid_akpu3pf,        &subid_akpu3pf,       &subid_akpu3pf,        &subid_akpu3pf};

  int*                  anjet_mix[ncases]          =  {&njet_akpu3pf_mix,     &njet_akpu3pf_mix,    &njet_akpu3pf_mix,     &njet_akpu3pf_mix};
  std::vector<float>**  ajetpt_mix[ncases]         =  {&jetpt_akpu3pf_mix,    &jetpt_akpu3pf_mix,   &gjetpt_akpu3pf_mix,   &gjetpt_akpu3pf_mix};
  std::vector<float>**  ajeteta_mix[ncases]        =  {&jeteta_akpu3pf_mix,   &jeteta_akpu3pf_mix,  &gjeteta_akpu3pf_mix,  &gjeteta_akpu3pf_mix};
  std::vector<float>**  ajetphi_mix[ncases]        =  {&jetphi_akpu3pf_mix,   &jetphi_akpu3pf_mix,  &gjetphi_akpu3pf_mix,  &gjetphi_akpu3pf_mix};
  std::vector<int>**    asubid_mix[ncases]         =  {&subid_akpu3pf_mix,    &subid_akpu3pf_mix,   &subid_akpu3pf_mix,    &subid_akpu3pf_mix};

  // int*                   anjet[ncases]     =   {&njet_akpu3pf,        &njet_akpu3pf,        &ngen_akpu3pf,     &ngen_akpu3pf};
  // std::vector<float>**   ajetpt[ncases]    =   {&jetpt_akpu3pf,       &jetpt_akpu3pf,       &genpt_akpu3pf,    &genpt_akpu3pf};
  // std::vector<float>**   ajeteta[ncases]   =   {&jeteta_akpu3pf,      &jeteta_akpu3pf,      &geneta_akpu3pf,   &geneta_akpu3pf};
  // std::vector<float>**   ajetphi[ncases]   =   {&jetphi_akpu3pf,      &jetphi_akpu3pf,      &genphi_akpu3pf,   &genphi_akpu3pf};
  // std::vector<int>**     asubid[ncases]    =   {&subid_akpu3pf,       &subid_akpu3pf,       &gensubid_akpu3pf, &gensubid_akpu3pf};

  Int_t HLT_AK4Jet40;
  Int_t HLT_AK4Jet60;
  Int_t HLT_AK4Jet80;
  Int_t HLT_AK4Jet100;

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
  int isDselected_mix(Int_t j, Option_t* option);
  // int isjetselected(Int_t j, Option_t* option);
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
  void setbranchaddress(const char* bname, void* addr);
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
  jetpt_akpu3pf = 0;
  jeteta_akpu3pf = 0;
  jetphi_akpu3pf = 0;
  jetnpfpart_akpu3pf = 0;
  gjetpt_akpu3pf = 0;
  gjeteta_akpu3pf = 0;
  gjetphi_akpu3pf = 0;
  gjetflavor_akpu3pf = 0;
  subid_akpu3pf = 0;
  genpt_akpu3pf = 0;
  geneta_akpu3pf = 0;
  genphi_akpu3pf = 0;
  gensubid_akpu3pf = 0;

  Dmass = 0;
  Dpt = 0;
  Deta = 0;
  Dphi = 0;
  Dy = 0;
  Dchi2cl = 0;
  Dalpha = 0;
  DsvpvDistance = 0;
  DsvpvDisErr = 0;
  Dtrk1Pt = 0;
  Dtrk2Pt = 0;
  Dtrk1Eta = 0;
  Dtrk2Eta = 0;
  Dtrk1PtErr = 0;
  Dtrk2PtErr = 0;
  Dtrk1highPurity = 0;
  Dtrk2highPurity = 0;
  Dgen = 0;
  Dgenpt = 0;
  DgencollisionId = 0;

  Gy = 0;
  Geta = 0;
  Gphi = 0;
  Gpt = 0;
  GpdgId = 0;
  GcollisionId = 0;
  GisSignal = 0;
  Gtk1pt = 0;
  Gtk1eta = 0;
  Gtk2pt = 0;
  Gtk2eta = 0;

  jetpt_akpu3pf_mix = 0;
  jeteta_akpu3pf_mix = 0;
  jetphi_akpu3pf_mix = 0;
  jetnpfpart_akpu3pf_mix = 0;
  gjetpt_akpu3pf_mix = 0;
  gjeteta_akpu3pf_mix = 0;
  gjetphi_akpu3pf_mix = 0;
  gjetflavor_akpu3pf_mix = 0;
  subid_akpu3pf_mix = 0;
  genpt_akpu3pf_mix = 0;
  geneta_akpu3pf_mix = 0;
  genphi_akpu3pf_mix = 0;
  gensubid_akpu3pf_mix = 0;

  Dmass_mix = 0;
  Dpt_mix = 0;
  Deta_mix = 0;
  Dphi_mix = 0;
  Dy_mix = 0;
  Dchi2cl_mix = 0;
  Dalpha_mix = 0;
  DsvpvDistance_mix = 0;
  DsvpvDisErr_mix = 0;
  Dtrk1Pt_mix = 0;
  Dtrk2Pt_mix = 0;
  Dtrk1Eta_mix = 0;
  Dtrk2Eta_mix = 0;
  Dtrk1PtErr_mix = 0;
  Dtrk2PtErr_mix = 0;
  Dtrk1highPurity_mix = 0;
  Dtrk2highPurity_mix = 0;
  Dgen_mix = 0;
  Dgenpt_mix = 0;
  DgencollisionId_mix = 0;

  Gy_mix = 0;
  Geta_mix = 0;
  Gphi_mix = 0;
  Gpt_mix = 0;
  GpdgId_mix = 0;
  GcollisionId_mix = 0;
  GisSignal_mix = 0;
  Gtk1pt_mix = 0;
  Gtk1eta_mix = 0;
  Gtk2pt_mix = 0;
  Gtk2eta_mix = 0;

  // Set branch addresses and branch pointers
  if(!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);
  fChain->SetBranchStatus("*", 0);

  setbranchaddress("isPP", &isPP);
  setbranchaddress("run", &run);
  setbranchaddress("evt", &evt);
  setbranchaddress("lumi", &lumi);
  setbranchaddress("hiBin", &hiBin);
  setbranchaddress("vz", &vz);
  setbranchaddress("weight", &weight);
  setbranchaddress("pthat", &pthat);
  setbranchaddress("hiEvtPlanes", hiEvtPlanes);

  setbranchaddress("njet_akpu3pf", &njet_akpu3pf);
  setbranchaddress("jetpt_akpu3pf", &jetpt_akpu3pf);
  setbranchaddress("jeteta_akpu3pf", &jeteta_akpu3pf);
  setbranchaddress("jetphi_akpu3pf", &jetphi_akpu3pf);
  setbranchaddress("jetnpfpart_akpu3pf", &jetnpfpart_akpu3pf);
  if(fisMC)
    {
      setbranchaddress("gjetpt_akpu3pf", &gjetpt_akpu3pf);
      setbranchaddress("gjeteta_akpu3pf", &gjeteta_akpu3pf);
      setbranchaddress("gjetphi_akpu3pf", &gjetphi_akpu3pf);
      setbranchaddress("gjetflavor_akpu3pf", &gjetflavor_akpu3pf);
      setbranchaddress("subid_akpu3pf", &subid_akpu3pf);
      setbranchaddress("ngen_akpu3pf", &ngen_akpu3pf);
      setbranchaddress("genpt_akpu3pf", &genpt_akpu3pf);
      setbranchaddress("geneta_akpu3pf", &geneta_akpu3pf);
      setbranchaddress("genphi_akpu3pf", &genphi_akpu3pf);
      setbranchaddress("gensubid_akpu3pf", &gensubid_akpu3pf);
    }
  setbranchaddress("Dsize", &Dsize);
  setbranchaddress("Dmass", &Dmass);
  setbranchaddress("Dpt", &Dpt);
  setbranchaddress("Deta", &Deta);
  setbranchaddress("Dphi", &Dphi);
  setbranchaddress("Dy", &Dy);
  setbranchaddress("Dchi2cl", &Dchi2cl);
  setbranchaddress("Dalpha", &Dalpha);
  setbranchaddress("DsvpvDistance", &DsvpvDistance);
  setbranchaddress("DsvpvDisErr", &DsvpvDisErr);
  setbranchaddress("Dtrk1Pt", &Dtrk1Pt);
  setbranchaddress("Dtrk2Pt", &Dtrk2Pt);
  setbranchaddress("Dtrk1Eta", &Dtrk1Eta);
  setbranchaddress("Dtrk2Eta", &Dtrk2Eta);
  setbranchaddress("Dtrk1PtErr", &Dtrk1PtErr);
  setbranchaddress("Dtrk2PtErr", &Dtrk2PtErr);
  setbranchaddress("Dtrk1highPurity", &Dtrk1highPurity);
  setbranchaddress("Dtrk2highPurity", &Dtrk2highPurity);
  setbranchaddress("Dgen", &Dgen);
  setbranchaddress("Dgenpt", &Dgenpt);
  setbranchaddress("DgencollisionId", &DgencollisionId);

  if(fisMC)
    {
      setbranchaddress("Gsize", &Gsize);
      setbranchaddress("Gy", &Gy);
      setbranchaddress("Geta", &Geta);
      setbranchaddress("Gphi", &Gphi);
      setbranchaddress("Gpt", &Gpt);
      setbranchaddress("GpdgId", &GpdgId);
      setbranchaddress("GcollisionId", &GcollisionId);
      setbranchaddress("GisSignal", &GisSignal);
      setbranchaddress("Gtk1pt", &Gtk1pt);
      setbranchaddress("Gtk1eta", &Gtk1eta);
      setbranchaddress("Gtk2pt", &Gtk2pt);
      setbranchaddress("Gtk2eta", &Gtk2eta);

      setbranchaddress("pthatweight", &pthatweight);
      setbranchaddress("maxDgenpt", &maxDgenpt);
    }
  if(!fispp)
    {
      setbranchaddress("njet_akpu3pf_mix", &njet_akpu3pf_mix);
      setbranchaddress("jetpt_akpu3pf_mix", &jetpt_akpu3pf_mix);
      setbranchaddress("jeteta_akpu3pf_mix", &jeteta_akpu3pf_mix);
      setbranchaddress("jetphi_akpu3pf_mix", &jetphi_akpu3pf_mix);
      setbranchaddress("jetnpfpart_akpu3pf_mix", &jetnpfpart_akpu3pf_mix);
      if(fisMC)
        {
          setbranchaddress("gjetpt_akpu3pf_mix", &gjetpt_akpu3pf_mix);
          setbranchaddress("gjeteta_akpu3pf_mix", &gjeteta_akpu3pf_mix);
          setbranchaddress("gjetphi_akpu3pf_mix", &gjetphi_akpu3pf_mix);
          setbranchaddress("gjetflavor_akpu3pf_mix", &gjetflavor_akpu3pf_mix);
          setbranchaddress("subid_akpu3pf_mix", &subid_akpu3pf_mix);
          setbranchaddress("ngen_akpu3pf_mix", &ngen_akpu3pf_mix);
          setbranchaddress("genpt_akpu3pf_mix", &genpt_akpu3pf_mix);
          setbranchaddress("geneta_akpu3pf_mix", &geneta_akpu3pf_mix);
          setbranchaddress("genphi_akpu3pf_mix", &genphi_akpu3pf_mix);
          setbranchaddress("gensubid_akpu3pf_mix", &gensubid_akpu3pf_mix);
        }
      setbranchaddress("Dsize_mix", &Dsize_mix);
      setbranchaddress("Dmass_mix", &Dmass_mix);
      setbranchaddress("Dpt_mix", &Dpt_mix);
      setbranchaddress("Deta_mix", &Deta_mix);
      setbranchaddress("Dphi_mix", &Dphi_mix);
      setbranchaddress("Dy_mix", &Dy_mix);
      setbranchaddress("Dchi2cl_mix", &Dchi2cl_mix);
      setbranchaddress("Dalpha_mix", &Dalpha_mix);
      setbranchaddress("DsvpvDistance_mix", &DsvpvDistance_mix);
      setbranchaddress("DsvpvDisErr_mix", &DsvpvDisErr_mix);
      setbranchaddress("Dtrk1Pt_mix", &Dtrk1Pt_mix);
      setbranchaddress("Dtrk2Pt_mix", &Dtrk2Pt_mix);
      setbranchaddress("Dtrk1Eta_mix", &Dtrk1Eta_mix);
      setbranchaddress("Dtrk2Eta_mix", &Dtrk2Eta_mix);
      setbranchaddress("Dtrk1PtErr_mix", &Dtrk1PtErr_mix);
      setbranchaddress("Dtrk2PtErr_mix", &Dtrk2PtErr_mix);
      setbranchaddress("Dtrk1highPurity_mix", &Dtrk1highPurity_mix);
      setbranchaddress("Dtrk2highPurity_mix", &Dtrk2highPurity_mix);
      setbranchaddress("Dgen_mix", &Dgen_mix);
      setbranchaddress("Dgenpt_mix", &Dgenpt_mix);
      setbranchaddress("DgencollisionId_mix", &DgencollisionId_mix);
      if(fisMC)
        {
          setbranchaddress("Gsize_mix", &Gsize_mix);
          setbranchaddress("Gy_mix", &Gy_mix);
          setbranchaddress("Geta_mix", &Geta_mix);
          setbranchaddress("Gphi_mix", &Gphi_mix);
          setbranchaddress("Gpt_mix", &Gpt_mix);
          setbranchaddress("GpdgId_mix", &GpdgId_mix);
          setbranchaddress("GcollisionId_mix", &GcollisionId_mix);
          setbranchaddress("GisSignal_mix", &GisSignal_mix);
          setbranchaddress("Gtk1pt_mix", &Gtk1pt_mix);
          setbranchaddress("Gtk1eta_mix", &Gtk1eta_mix);
          setbranchaddress("Gtk2pt_mix", &Gtk2pt_mix);
          setbranchaddress("Gtk2eta_mix", &Gtk2eta_mix);
        }
    }
  if(!hlt) return;
  fHlt = hlt;
  fHlt->SetMakeClass(1);
  fHlt->SetBranchStatus("*", 0);
  if(fispp)
    {
      fHlt->SetBranchStatus(fisMC?"HLT_AK4PFJet40_Eta5p1ForPPRef_v1":"HLT_AK4PFJet40_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_AK4PFJet60_Eta5p1ForPPRef_v1":"HLT_AK4PFJet60_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_AK4PFJet80_Eta5p1ForPPRef_v1":"HLT_AK4PFJet80_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_AK4PFJet100_Eta5p1ForPPRef_v1":"HLT_AK4PFJet100_Eta5p1_v1", 1);
      fHlt->SetBranchAddress(fisMC?"HLT_AK4PFJet40_Eta5p1ForPPRef_v1":"HLT_AK4PFJet40_Eta5p1_v1", &HLT_AK4Jet40);
      fHlt->SetBranchAddress(fisMC?"HLT_AK4PFJet60_Eta5p1ForPPRef_v1":"HLT_AK4PFJet60_Eta5p1_v1", &HLT_AK4Jet60);
      fHlt->SetBranchAddress(fisMC?"HLT_AK4PFJet80_Eta5p1ForPPRef_v1":"HLT_AK4PFJet80_Eta5p1_v1", &HLT_AK4Jet80);
      fHlt->SetBranchAddress(fisMC?"HLT_AK4PFJet100_Eta5p1ForPPRef_v1":"HLT_AK4PFJet100_Eta5p1_v1", &HLT_AK4Jet100);
    }
  else
    {
      fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet40_Eta5p1_v2":"HLT_HIPuAK4CaloJet40_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet60_Eta5p1_v2":"HLT_HIPuAK4CaloJet60_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet80_Eta5p1_v2":"HLT_HIPuAK4CaloJet80_Eta5p1_v1", 1);
      fHlt->SetBranchStatus(fisMC?"HLT_HIPuAK4CaloJet100_Eta5p1_v2":"HLT_HIPuAK4CaloJet100_Eta5p1_v1", 1);
      fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet40_Eta5p1_v2":"HLT_HIPuAK4CaloJet40_Eta5p1_v1", &HLT_AK4Jet40);
      fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet60_Eta5p1_v2":"HLT_HIPuAK4CaloJet60_Eta5p1_v1", &HLT_AK4Jet60);
      fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet80_Eta5p1_v2":"HLT_HIPuAK4CaloJet80_Eta5p1_v1", &HLT_AK4Jet80);      
      fHlt->SetBranchAddress(fisMC?"HLT_HIPuAK4CaloJet100_Eta5p1_v2":"HLT_HIPuAK4CaloJet100_Eta5p1_v1", &HLT_AK4Jet100);      
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

// void djet::setjetcut(Float_t _cut_jetpt_min, Float_t _cut_jeteta_min, Float_t _cut_jeteta_max)
// {
//   cut_jetpt_min = _cut_jetpt_min;
//   cut_jeteta_min = _cut_jeteta_min;
//   cut_jeteta_max = _cut_jeteta_max;
//   fsetjetcut = true;
// }

void djet::setbindepcut(Float_t _cut_Dsvpv, Float_t _cut_Dalpha)
{
  cut_Dsvpv = _cut_Dsvpv;
  cut_Dalpha = _cut_Dalpha;
}

#define _KERROR_SETCUT(obj, Dorjet) { std::cout<<" error: set "<<#obj<<" before judging is"<<#Dorjet<<"selected."<<std::endl; return -1; }

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
         TMath::Abs((*Dy)[j]) < cut_Dy
         ) return 1;
      else return 0;
    }
  if(opt.Contains("g"))
    {
      if(!fsetGcut) _KERROR_SETCUT(G, D);
      if(((*GisSignal)[j]==1 || (*GisSignal)[j]==2) &&
         TMath::Abs((*Gy)[j]) < cut_Gy
         ) return 1;
      else return 0;
    }
  std::cout<<"error: invalid option for isDselected()"<<std::endl;
  return -3;
}

int djet::isDselected_mix(int j, Option_t* option)
{
  TString opt  = option;
  opt.ToLower();
  if((opt.Contains("r") && opt.Contains("g")) || (!opt.Contains("r") && !opt.Contains("g"))) return -2;
  if(opt.Contains("r"))
    {
      if(!fsetDcut) _KERROR_SETCUT(D, D);
      if(!fsettrkcut) _KERROR_SETCUT(trk, D);
      if((*Dtrk1Pt_mix)[j] > cut_trkPt && (*Dtrk2Pt_mix)[j] > cut_trkPt &&
         TMath::Abs((*Dtrk1Eta_mix)[j]) < cut_trkEta && TMath::Abs((*Dtrk2Eta_mix)[j]) < cut_trkEta &&
         ((*Dtrk1PtErr_mix)[j]/(*Dtrk1Pt_mix)[j]) < cut_trkPtErr && ((*Dtrk2PtErr_mix)[j]/(*Dtrk2Pt_mix)[j]) < cut_trkPtErr &&
         (*Dtrk1highPurity_mix)[j] && (*Dtrk2highPurity_mix)[j] &&
         ((*DsvpvDistance_mix)[j]/(*DsvpvDisErr_mix)[j]) > cut_Dsvpv &&
         (*Dalpha_mix)[j] < cut_Dalpha &&
         (*Dchi2cl_mix)[j] >cut_Dchi2cl &&
         TMath::Abs((*Dy_mix)[j]) < cut_Dy
         ) return 1;
      else return 0;
    }
  if(opt.Contains("g"))
    {
      if(!fsetGcut) _KERROR_SETCUT(G, D);
      if(((*GisSignal_mix)[j]==1 || (*GisSignal_mix)[j]==2) &&
         TMath::Abs((*Gy_mix)[j]) < cut_Gy
         ) return 1;
      else return 0;
    }
  std::cout<<"error: invalid option for isDselected_mix()"<<std::endl;
  return -3;
}

// int djet::isjetselected(int j, Option_t* option)
// {
//   TString opt  = option;
//   opt.ToLower();
//   if((opt.Contains("r") && opt.Contains("g")) || (!opt.Contains("r") && !opt.Contains("g"))) return -2;
//   if(!fsetjetcut) _KERROR_SETCUT(jet, jet);
//   if(opt.Contains("r"))
//     {
//       if((*jetpt_akpu3pf)[j] > cut_jetpt_min && 
//          TMath::Abs((*jeteta_akpu3pf)[j]) > cut_jeteta_min && TMath::Abs((*jeteta_akpu3pf)[j]) < cut_jeteta_max) return 1;
//       else return 0;
//     }
//   if(opt.Contains("g"))
//     {
//       if((*genpt_akpu3pf)[j] > cut_jetpt_min && 
//          TMath::Abs((*geneta_akpu3pf)[j]) > cut_jeteta_min && TMath::Abs((*geneta_akpu3pf)[j]) < cut_jeteta_max) return 1;
//       else return 0;
//     }
//   return -3;
// }

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

void djet::setbranchaddress(const char* bname, void* addr)
{
  fChain->SetBranchStatus(bname, 1);
  fChain->SetBranchAddress(bname, addr);
}
#endif
