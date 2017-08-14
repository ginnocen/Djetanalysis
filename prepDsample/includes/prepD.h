#ifndef _PREPD_H
#define _PREPD_H

#include <TTree.h>
#include "d_jet.h"

class prepD
{
public:

  Int_t                  isPP;
  Int_t                  isgenjet;
  Int_t                  hiBin;
  Float_t                vz;
  Float_t                weight;
  Float_t                pthat;
  Int_t                  RunNo;
  Int_t                  EvtNo;
  Int_t                  LumiNo;
  Float_t                PVx;
  Float_t                PVy;
  Float_t                PVz;
  Float_t                PVnchi2;   
  Float_t                pthatweight;
  Float_t                maxDgenpt;

  Int_t                  Dsize;
  std::vector<Float_t>   Dmass;
  std::vector<Float_t>   Dpt;
  std::vector<Float_t>   Deta;
  std::vector<Float_t>   Dphi;
  std::vector<Float_t>   Dy;
  std::vector<Float_t>   Dchi2cl;
  std::vector<Float_t>   Dalpha;
  std::vector<Float_t>   DsvpvDistance;
  std::vector<Float_t>   DsvpvDisErr;
  std::vector<Float_t>   DlxyBS;
  std::vector<Float_t>   DlxyBSErr;
  std::vector<Float_t>   Dtrk1Pt;
  std::vector<Float_t>   Dtrk2Pt;
  std::vector<Float_t>   Dtrk1Eta;
  std::vector<Float_t>   Dtrk2Eta;
  std::vector<Float_t>   Dtrk1Phi;
  std::vector<Float_t>   Dtrk2Phi;
  std::vector<Bool_t>    Dtrk1highPurity;
  std::vector<Bool_t>    Dtrk2highPurity;
  std::vector<Float_t>   Dtrk1PtErr;
  std::vector<Float_t>   Dtrk2PtErr;
  std::vector<Float_t>   Dtrk1EtaErr;
  std::vector<Float_t>   Dtrk2EtaErr;
  std::vector<Float_t>   Dtrk1PhiErr;
  std::vector<Float_t>   Dtrk2PhiErr;
  std::vector<Float_t>   Dtrk1Y;
  std::vector<Float_t>   Dtrk2Y;
  std::vector<Float_t>   Dgen;
  std::vector<Int_t>     DgencollisionId;
  std::vector<Float_t>   Djetpt;
  std::vector<Float_t>   Djeteta;
  std::vector<Float_t>   Djetphi;
  std::vector<Float_t>   DdeltaR;
  std::vector<Float_t>   DdeltaRref;
  std::vector<Float_t>   Dzvariable;

  Int_t                  Gsize;
  std::vector<Int_t>     GpdgId;
  std::vector<Int_t>     GisSignal;
  std::vector<Float_t>   Gy;
  std::vector<Float_t>   Geta;
  std::vector<Float_t>   Gphi;
  std::vector<Float_t>   Gpt;
  std::vector<Float_t>   Gjetpt;
  std::vector<Float_t>   Gjeteta;
  std::vector<Float_t>   Gjetphi;
  std::vector<Float_t>   GdeltaR;
  std::vector<Float_t>   GdeltaRref;
  std::vector<Float_t>   Gzvariable;

  // constructors
  prepD(Int_t isGenjet) : isgenjet(isGenjet)
  {
    isPP = 0;
    hiBin = -1;
    vz = -99;
    weight = -1;
    pthat = -1;
      
    RunNo = -99;
    EvtNo = -99;
    LumiNo = -99;
    PVx = -99;
    PVy = -99;
    PVz = -99;
    PVnchi2 = -99;
    pthatweight = -1;
    maxDgenpt = -1;

    Dsize = -99;
    Gsize = -99;
  }
  
  prepD(TTree* t, Int_t isGenjet) : prepD(isGenjet) 
  {
    this->create_tree(t);
  }
  
  ~prepD() {};
  
  void create_tree(TTree* t);
  void copy_variables(djet& dt, Int_t dsize, Int_t gsize);
  void copy_gen_index(djet& dt, Int_t jd, Int_t jj, Float_t dR, Float_t dRref, Float_t z);
  void copy_index(djet& dt, Int_t jd, Int_t jj, Float_t dR, Float_t dRref, Float_t z);
  void clear_vectors();

};

void prepD::create_tree(TTree* t) 
{
  t->Branch("isPP", &isPP, "isPP/I");
  t->Branch("isgenjet", &isgenjet, "isgenjet/I");
  t->Branch("hiBin", &hiBin, "hiBin/I");
  t->Branch("vz", &vz, "vz/F");
  t->Branch("weight", &weight, "weight/F");
  t->Branch("pthat", &pthat, "pthat/F");
  t->Branch("RunNo", &RunNo, "RunNo/I");
  t->Branch("EvtNo", &EvtNo, "EvtNo/I");
  t->Branch("LumiNo", &LumiNo, "LumiNo/I");
  t->Branch("PVx", &PVx, "PVx/F");
  t->Branch("PVy", &PVy, "PVy/F");
  t->Branch("PVz", &PVz, "PVz/F");
  t->Branch("PVnchi2", &PVnchi2, "PVnchi2/F");
  t->Branch("pthatweight", &pthatweight, "pthatweight/F");
  t->Branch("maxDgenpt", &maxDgenpt, "maxDgenpt/F");

  t->Branch("Dsize", &Dsize, "Dsize/I");
  t->Branch("Dmass", &Dmass);
  t->Branch("Dpt", &Dpt);
  t->Branch("Deta", &Deta);
  t->Branch("Dphi", &Dphi);
  t->Branch("Dy", &Dy);
  t->Branch("Dchi2cl", &Dchi2cl);
  t->Branch("Dalpha", &Dalpha);
  t->Branch("DsvpvDistance", &DsvpvDistance);
  t->Branch("DsvpvDisErr", &DsvpvDisErr);
  t->Branch("DlxyBS", &DlxyBS);
  t->Branch("DlxyBSErr", &DlxyBSErr);
  t->Branch("Dtrk1Pt", &Dtrk1Pt);
  t->Branch("Dtrk2Pt", &Dtrk2Pt);
  t->Branch("Dtrk1Eta", &Dtrk1Eta);
  t->Branch("Dtrk2Eta", &Dtrk2Eta);
  t->Branch("Dtrk1Phi", &Dtrk1Phi);
  t->Branch("Dtrk2Phi", &Dtrk2Phi);
  t->Branch("Dtrk1PtErr", &Dtrk1PtErr);
  t->Branch("Dtrk2PtErr", &Dtrk2PtErr);
  t->Branch("Dtrk1highPurity", &Dtrk1highPurity);
  t->Branch("Dtrk2highPurity", &Dtrk2highPurity);
  t->Branch("Dtrk1EtaErr", &Dtrk1EtaErr);
  t->Branch("Dtrk2EtaErr", &Dtrk2EtaErr);
  t->Branch("Dtrk1PhiErr", &Dtrk1PhiErr);
  t->Branch("Dtrk2PhiErr", &Dtrk2PhiErr);
  t->Branch("Dtrk1Y", &Dtrk1Y);
  t->Branch("Dtrk2Y", &Dtrk2Y);
  t->Branch("Dgen", &Dgen);
  t->Branch("DgencollisionId", &DgencollisionId);
  t->Branch("Djetpt", &Djetpt);
  t->Branch("Djeteta", &Djeteta);
  t->Branch("Djetphi", &Djetphi);
  t->Branch("DdeltaR", &DdeltaR);
  t->Branch("DdeltaRref", &DdeltaRref);
  t->Branch("Dzvariable", &Dzvariable);

  t->Branch("Gsize", &Gsize, "Gsize/I");
  t->Branch("GpdgId", &GpdgId);
  t->Branch("GisSignal", &GisSignal);
  t->Branch("Gy", &Gy);
  t->Branch("Geta", &Geta);
  t->Branch("Gphi", &Gphi);
  t->Branch("Gpt", &Gpt);
  t->Branch("Gjetpt", &Gjetpt);
  t->Branch("Gjeteta", &Gjeteta);
  t->Branch("Gjetphi", &Gjetphi);
  t->Branch("GdeltaR", &GdeltaR);
  t->Branch("GdeltaRref", &GdeltaRref);
  t->Branch("Gzvariable", &Gzvariable);

}

void prepD::copy_variables(djet& dt, Int_t dsize, Int_t gsize)
{
  isPP = dt.isPP;
  hiBin = dt.hiBin;
  vz = dt.vz;
  weight = dt.weight;
  pthat = dt.pthat;
  RunNo = dt.RunNo;
  EvtNo = dt.EvtNo;
  LumiNo = dt.LumiNo;
  PVx = dt.PVx;
  PVy = dt.PVy;
  PVz = dt.PVz;
  PVnchi2 = dt.PVnchi2;
  pthatweight = dt.pthatweight;
  maxDgenpt = dt.maxDgenpt;

  Dsize = dsize;
  Gsize = gsize;
}

void prepD::copy_gen_index(djet& dt, Int_t jd, Int_t jj, Float_t dR, Float_t dRref, Float_t z)
{
  GpdgId.push_back((*dt.GpdgId)[jd]);
  GisSignal.push_back((*dt.GisSignal)[jd]);
  Gy.push_back((*dt.Gy)[jd]);
  Geta.push_back((*dt.Geta)[jd]);
  Gphi.push_back((*dt.Gphi)[jd]);
  Gpt.push_back((*dt.Gpt)[jd]);

  Float_t jetpt = isgenjet?(*dt.genpt_akpu3pf)[jj]:(*dt.jetptCorr_akpu3pf)[jj];
  Float_t jeteta = isgenjet?(*dt.geneta_akpu3pf)[jj]:(*dt.jeteta_akpu3pf)[jj];
  Float_t jetphi = isgenjet?(*dt.genphi_akpu3pf)[jj]:(*dt.jetphi_akpu3pf)[jj];

  Gjetpt.push_back(jetpt);
  Gjeteta.push_back(jeteta);
  Gjetphi.push_back(jetphi);

  GdeltaR.push_back(dR);
  GdeltaRref.push_back(dRref);
  Gzvariable.push_back(z);
}

void prepD::copy_index(djet& dt, Int_t jd, Int_t jj, Float_t dR, Float_t dRref, Float_t z)
{
  Dmass.push_back((*dt.Dmass)[jd]);
  Dpt.push_back((*dt.Dpt)[jd]);
  Deta.push_back((*dt.Deta)[jd]);
  Dphi.push_back((*dt.Dphi)[jd]);
  Dy.push_back((*dt.Dy)[jd]);
  Dchi2cl.push_back((*dt.Dchi2cl)[jd]);
  Dalpha.push_back((*dt.Dalpha)[jd]);
  DsvpvDistance.push_back((*dt.DsvpvDistance)[jd]);
  DsvpvDisErr.push_back((*dt.DsvpvDisErr)[jd]);
  DlxyBS.push_back((*dt.DlxyBS)[jd]);
  DlxyBSErr.push_back((*dt.DlxyBSErr)[jd]);
  Dtrk1Pt.push_back((*dt.Dtrk1Pt)[jd]);
  Dtrk2Pt.push_back((*dt.Dtrk2Pt)[jd]);
  Dtrk1Eta.push_back((*dt.Dtrk1Eta)[jd]);
  Dtrk2Eta.push_back((*dt.Dtrk2Eta)[jd]);
  Dtrk1Phi.push_back((*dt.Dtrk1Phi)[jd]);
  Dtrk2Phi.push_back((*dt.Dtrk2Phi)[jd]);
  Dtrk1PtErr.push_back((*dt.Dtrk1PtErr)[jd]);
  Dtrk2PtErr.push_back((*dt.Dtrk2PtErr)[jd]);
  Dtrk1highPurity.push_back((*dt.Dtrk1highPurity)[jd]);
  Dtrk2highPurity.push_back((*dt.Dtrk2highPurity)[jd]);
  Dtrk1EtaErr.push_back((*dt.Dtrk1EtaErr)[jd]);
  Dtrk2EtaErr.push_back((*dt.Dtrk2EtaErr)[jd]);
  Dtrk1PhiErr.push_back((*dt.Dtrk1PhiErr)[jd]);
  Dtrk2PhiErr.push_back((*dt.Dtrk2PhiErr)[jd]);
  Dtrk1Y.push_back((*dt.Dtrk1Y)[jd]);
  Dtrk2Y.push_back((*dt.Dtrk2Y)[jd]);
  Dgen.push_back((*dt.Dgen)[jd]);
  DgencollisionId.push_back((*dt.DgencollisionId)[jd]);

  Float_t jetpt = isgenjet?(*dt.genpt_akpu3pf)[jj]:(*dt.jetptCorr_akpu3pf)[jj];
  Float_t jeteta = isgenjet?(*dt.geneta_akpu3pf)[jj]:(*dt.jeteta_akpu3pf)[jj];
  Float_t jetphi = isgenjet?(*dt.genphi_akpu3pf)[jj]:(*dt.jetphi_akpu3pf)[jj];

  Djetpt.push_back(jetpt);
  Djeteta.push_back(jeteta);
  Djetphi.push_back(jetphi);

  DdeltaR.push_back(dR);
  DdeltaRref.push_back(dRref);
  Dzvariable.push_back(z);
}

void prepD::clear_vectors()
{
  Dmass.clear();
  Dpt.clear();
  Deta.clear();
  Dphi.clear();
  Dy.clear();
  Dchi2cl.clear();
  Dalpha.clear();
  DsvpvDistance.clear();
  DsvpvDisErr.clear();
  DlxyBS.clear();
  DlxyBSErr.clear();

  Dtrk1Pt.clear();
  Dtrk2Pt.clear();
  Dtrk1Eta.clear();
  Dtrk2Eta.clear();
  Dtrk1Phi.clear();
  Dtrk2Phi.clear();
  Dtrk1PtErr.clear();
  Dtrk2PtErr.clear();
  Dtrk1highPurity.clear();
  Dtrk2highPurity.clear();
  Dtrk1EtaErr.clear();
  Dtrk2EtaErr.clear();
  Dtrk1PhiErr.clear();
  Dtrk2PhiErr.clear();
  Dtrk1Y.clear();
  Dtrk2Y.clear();

  Dgen.clear();
  DgencollisionId.clear();

  Djetpt.clear();
  Djeteta.clear();
  Djetphi.clear();

  DdeltaR.clear();
  DdeltaRref.clear();
  Dzvariable.clear();
  
  GpdgId.clear();
  GisSignal.clear();
  Gy.clear();
  Geta.clear();
  Gphi.clear();
  Gpt.clear();

  Gjetpt.clear();
  Gjeteta.clear();
  Gjetphi.clear();

  GdeltaR.clear();
  GdeltaRref.clear();
  Gzvariable.clear();
  
}

#endif
