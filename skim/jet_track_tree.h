#ifndef _PHOTON_JET_TRACK_TREE_H
#define _PHOTON_JET_TRACK_TREE_H

#include "TTree.h"

#include <vector>

const int nEventsToMix = 24;

class jetTrackTree {
  public:
    jetTrackTree() {
        isPP = 0;
        run = 0;
        evt = 0;
        lumi = 0;
        hiBin = -1;
        vz = -99;
        weight = -1;

        njet = 0;
        ngen = 0;
        nTrk = 0;
        mult = 0;

        nmix = 0;
        nlooped = 0;

        njet_mix = 0;
        ngen_mix = 0;
        nTrk_mix = 0;
        mult_mix = 0;
    }
    ~jetTrackTree() {};

    jetTrackTree(TTree* t) : jetTrackTree() {
        this->create_tree(t);
    }

    // void read_tree(TTree* t);
    void create_tree(TTree* t);
    void clear_vectors();

    int isPP;
    uint32_t run;
    unsigned long long evt;
    uint32_t lumi;
    int hiBin;
    float vz;
    float weight;

    float hiEvtPlanes[29];

    int njet;
    std::vector<float> jetptCorr;
    std::vector<float> jetptCorr_zjet;
    std::vector<float> jetpt;
    std::vector<float> jeteta;
    std::vector<float> jetphi;
    std::vector<float> gjetpt;
    std::vector<float> gjeteta;
    std::vector<float> gjetphi;
    std::vector<int> subid;
    std::vector<int> gjetflavor;
    std::vector<float> rawpt;
    std::vector<float> chargedSum;
    std::vector<float> neutralSum;
    std::vector<float> photonSum;
    std::vector<float> eSum;
    std::vector<float> chargedMax;
    std::vector<int> chargedN;
    std::vector<int> neutralN;
    std::vector<int> photonN;
    std::vector<int> eN;
    std::vector<int> muN;
    std::vector<bool> jetID;

    int ngen;
    std::vector<int> genmatchindex;
    std::vector<float> genpt;
    std::vector<float> geneta;
    std::vector<float> genphi;
    std::vector<int> gensubid;

    int nTrk;
    std::vector<float> trkPt;
    std::vector<float> trkPtError;
    std::vector<uint8_t> trkNHit;
    std::vector<uint8_t> trkNlayer;
    std::vector<float> trkEta;
    std::vector<float> trkPhi;
    std::vector<int> trkCharge;
    std::vector<bool> highPurity;
    std::vector<float> trkChi2;
    std::vector<uint8_t> trkNdof;
    std::vector<float> trkDxy1;
    std::vector<float> trkDxyError1;
    std::vector<float> trkDz1;
    std::vector<float> trkDzError1;
    std::vector<float> pfEcal;
    std::vector<float> pfHcal;
    std::vector<float> trkWeight;

    int mult;
    std::vector<float> pt;
    std::vector<float> eta;
    std::vector<float> phi;
    std::vector<int> pdg;
    std::vector<int> chg;
    std::vector<int> matchingID;
    std::vector<int> sube;

    int nmix;
    int nlooped;
    float dvz_mix[nEventsToMix];
    int dhiBin_mix[nEventsToMix];
    float dhiEvtPlanes_mix[nEventsToMix];

    int njet_mix;
    std::vector<float> jetptCorr_mix;
    std::vector<float> jetptCorr_zjet_mix;
    std::vector<float> jetpt_mix;
    std::vector<float> jeteta_mix;
    std::vector<float> jetphi_mix;
    std::vector<float> gjetpt_mix;
    std::vector<float> gjeteta_mix;
    std::vector<float> gjetphi_mix;
    std::vector<int> subid_mix;
    std::vector<float> rawpt_mix;
    std::vector<float> chargedSum_mix;
    std::vector<float> neutralSum_mix;
    std::vector<float> photonSum_mix;
    std::vector<float> eSum_mix;
    std::vector<float> chargedMax_mix;
    std::vector<int> chargedN_mix;
    std::vector<int> neutralN_mix;
    std::vector<int> photonN_mix;
    std::vector<int> eN_mix;
    std::vector<int> muN_mix;
    std::vector<bool> jetID_mix;
    std::vector<int> nmixEv_mix;

    int ngen_mix;
    std::vector<float> genpt_mix;
    std::vector<float> geneta_mix;
    std::vector<float> genphi_mix;
    std::vector<int> gensubid_mix;
    std::vector<int> genev_mix;

    int nTrk_mix;
    std::vector<int> trkFromEv_mix;
    std::vector<float> trkPt_mix;
    std::vector<float> trkEta_mix;
    std::vector<float> trkPhi_mix;
    std::vector<float> trkWeight_mix;

    int mult_mix;
    std::vector<float> pt_mix;
    std::vector<float> eta_mix;
    std::vector<float> phi_mix;
    std::vector<int> pdg_mix;
    std::vector<int> chg_mix;
    std::vector<int> nev_mix;
};

void jetTrackTree::create_tree(TTree* t) {
    t->Branch("isPP", &isPP, "isPP/I");
    t->Branch("run", &run, "run/i");
    t->Branch("evt", &evt, "evt/l");
    t->Branch("lumi", &lumi, "lumi/i");
    t->Branch("hiBin", &hiBin, "hiBin/I");
    t->Branch("vz", &vz, "vz/F");
    t->Branch("weight", &weight, "weight/F");

    t->Branch("hiEvtPlanes", hiEvtPlanes, "hiEvtPlanes[29]/F");

    t->Branch("njet", &njet, "njet/I");
    t->Branch("jetptCorr", &jetptCorr);
    t->Branch("jetptCorr_zjet", &jetptCorr_zjet);
    t->Branch("jetpt", &jetpt);
    t->Branch("jeteta", &jeteta);
    t->Branch("jetphi", &jetphi);
    t->Branch("gjetpt", &gjetpt);
    t->Branch("gjeteta", &gjeteta);
    t->Branch("gjetphi", &gjetphi);
    t->Branch("subid", &subid);
    t->Branch("gjetflavor", &gjetflavor);
    t->Branch("rawpt", &rawpt);
    t->Branch("chargedSum", &chargedSum);
    t->Branch("neutralSum", &neutralSum);
    t->Branch("photonSum", &photonSum);
    t->Branch("eSum", &eSum);
    t->Branch("chargedMax", &chargedMax);
    t->Branch("chargedN", &chargedN);
    t->Branch("neutralN", &neutralN);
    t->Branch("photonN", &photonN);
    t->Branch("eN", &eN);
    t->Branch("muN", &muN);
    t->Branch("jetID", &jetID);

    t->Branch("ngen", &ngen, "ngen/I");
    t->Branch("genmatchindex", &genmatchindex);
    t->Branch("genpt", &genpt);
    t->Branch("geneta", &geneta);
    t->Branch("genphi", &genphi);
    t->Branch("gensubid", &gensubid);

    t->Branch("nTrk", &nTrk, "nTrk/I");
    t->Branch("trkPt", &trkPt);
    t->Branch("trkEta", &trkEta);
    t->Branch("trkPhi", &trkPhi);
    t->Branch("trkCharge", &trkCharge);
    t->Branch("trkPtError", &trkPtError);
    t->Branch("trkNHit", &trkNHit);
    t->Branch("trkNlayer", &trkNlayer);
    t->Branch("highPurity", &highPurity);
    t->Branch("trkChi2", &trkChi2);
    t->Branch("trkNdof", &trkNdof);
    t->Branch("trkDxy1", &trkDxy1);
    t->Branch("trkDxyError1", &trkDxyError1);
    t->Branch("trkDz1", &trkDz1);
    t->Branch("trkDzError1", &trkDzError1);
    t->Branch("pfEcal", &pfEcal);
    t->Branch("pfHcal", &pfHcal);
    t->Branch("trkWeight", &trkWeight);

    t->Branch("mult", &mult, "mult/I");
    t->Branch("pt", &pt);
    t->Branch("eta", &eta);
    t->Branch("phi", &phi);
    t->Branch("pdg", &pdg);
    t->Branch("chg", &chg);
    t->Branch("matchingID", &matchingID);
    t->Branch("sube", &sube);

    t->Branch("nmix", &nmix, "nmix/I");
    t->Branch("nlooped", &nlooped, "nlooped/I");
    t->Branch("dvz_mix", dvz_mix, "dvz_mix[nmix]/F");
    t->Branch("dhiBin_mix", dhiBin_mix, "dhiBin_mix[nmix]/I");
    t->Branch("dhiEvtPlanes_mix", dhiEvtPlanes_mix, "dhiEvtPlanes_mix[nmix]/F");

    t->Branch("njet_mix", &njet_mix, "njet_mix/I");
    t->Branch("jetptCorr_mix", &jetptCorr_mix);
    t->Branch("jetptCorr_zjet_mix", &jetptCorr_zjet_mix);
    t->Branch("jetpt_mix", &jetpt_mix);
    t->Branch("jeteta_mix", &jeteta_mix);
    t->Branch("jetphi_mix", &jetphi_mix);
    t->Branch("gjetpt_mix", &gjetpt_mix);
    t->Branch("gjeteta_mix", &gjeteta_mix);
    t->Branch("gjetphi_mix", &gjetphi_mix);
    t->Branch("subid_mix", &subid_mix);
    t->Branch("rawpt_mix", &rawpt_mix);
    t->Branch("chargedSum_mix", &chargedSum_mix);
    t->Branch("neutralSum_mix", &neutralSum_mix);
    t->Branch("photonSum_mix", &photonSum_mix);
    t->Branch("eSum_mix", &eSum_mix);
    t->Branch("chargedMax_mix", &chargedMax_mix);
    t->Branch("chargedN_mix", &chargedN_mix);
    t->Branch("neutralN_mix", &neutralN_mix);
    t->Branch("photonN_mix", &photonN_mix);
    t->Branch("eN_mix", &eN_mix);
    t->Branch("muN_mix", &muN_mix);
    t->Branch("jetID_mix", &jetID_mix);
    t->Branch("nmixEv_mix", &nmixEv_mix);

    t->Branch("ngen_mix", &ngen_mix, "ngen_mix/I");
    t->Branch("genpt_mix", &genpt_mix);
    t->Branch("geneta_mix", &geneta_mix);
    t->Branch("genphi_mix", &genphi_mix);
    t->Branch("gensubid_mix", &gensubid_mix);
    t->Branch("genev_mix", &genev_mix);

    t->Branch("nTrk_mix", &nTrk_mix, "nTrk_mix/I");
    t->Branch("trkFromEv_mix", &trkFromEv_mix);
    t->Branch("trkPt_mix", &trkPt_mix);
    t->Branch("trkEta_mix", &trkEta_mix);
    t->Branch("trkPhi_mix", &trkPhi_mix);
    t->Branch("trkWeight_mix", &trkWeight_mix);

    t->Branch("mult_mix", &mult_mix, "mult_mix/I");
    t->Branch("pt_mix", &pt_mix);
    t->Branch("eta_mix", &eta_mix);
    t->Branch("phi_mix", &phi_mix);
    t->Branch("pdg_mix", &pdg_mix);
    t->Branch("chg_mix", &chg_mix);
    t->Branch("nev_mix", &nev_mix);
}

void jetTrackTree::clear_vectors() {
    jetptCorr.clear();
    jetptCorr_zjet.clear();
    jetpt.clear();
    jeteta.clear();
    jetphi.clear();
    gjetpt.clear();
    gjeteta.clear();
    gjetphi.clear();
    subid.clear();
    gjetflavor.clear();
    rawpt.clear();
    chargedSum.clear();
    neutralSum.clear();
    photonSum.clear();
    eSum.clear();
    chargedMax.clear();
    chargedN.clear();
    neutralN.clear();
    photonN.clear();
    eN.clear();
    muN.clear();
    jetID.clear();

    genmatchindex.clear();
    genpt.clear();
    geneta.clear();
    genphi.clear();
    gensubid.clear();

    trkPt.clear();
    trkPtError.clear();
    trkNHit.clear();
    trkNlayer.clear();
    trkEta.clear();
    trkPhi.clear();
    trkCharge.clear();
    highPurity.clear();
    trkChi2.clear();
    trkNdof.clear();
    trkDxy1.clear();
    trkDxyError1.clear();
    trkDz1.clear();
    trkDzError1.clear();
    pfEcal.clear();
    pfHcal.clear();
    trkWeight.clear();

    pt.clear();
    eta.clear();
    phi.clear();
    pdg.clear();
    chg.clear();
    matchingID.clear();
    sube.clear();

    jetptCorr_mix.clear();
    jetptCorr_zjet_mix.clear();
    jetpt_mix.clear();
    jeteta_mix.clear();
    jetphi_mix.clear();
    gjetpt_mix.clear();
    gjeteta_mix.clear();
    gjetphi_mix.clear();
    subid_mix.clear();
    rawpt_mix.clear();
    chargedSum_mix.clear();
    neutralSum_mix.clear();
    photonSum_mix.clear();
    eSum_mix.clear();
    chargedMax_mix.clear();
    chargedN_mix.clear();
    neutralN_mix.clear();
    photonN_mix.clear();
    eN_mix.clear();
    muN_mix.clear();
    jetID_mix.clear();
    nmixEv_mix.clear();

    genpt_mix.clear();
    geneta_mix.clear();
    genphi_mix.clear();
    gensubid_mix.clear();
    genev_mix.clear();

    trkFromEv_mix.clear();
    trkPt_mix.clear();
    trkEta_mix.clear();
    trkPhi_mix.clear();
    trkWeight_mix.clear();

    pt_mix.clear();
    eta_mix.clear();
    phi_mix.clear();
    pdg_mix.clear();
    chg_mix.clear();
    nev_mix.clear();
}

#endif
