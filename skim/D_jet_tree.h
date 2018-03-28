#ifndef _D_JET_TREE_H
#define _D_JET_TREE_H

#include "TTree.h"

#include "D_tree.h"
#include "G_tree.h"

#include <vector>

const int nEventsToMix = 1;

class DJetTree {
  public:
    DJetTree() {
        isPP = 0;
        run = 0;
        evt = 0;
        lumi = 0;
        hiBin = -1;
        vz = -99;
        weight = -1;
	pthat = -1;

        njet_akpu3pf = 0;
        njet_akpu4pf = 0;
        
        nmix = 0;
        njet_akpu3pf_mix = 0;
        ngen_akpu3pf_mix = 0;

        RunNo = -99;
        EvtNo = -99;
        LumiNo = -99;
        Dsize = -99;
        PVx = -99;
        PVy = -99;
        PVz = -99;
        PVnchi2 = -99;
        BSx = -99;
        BSy = -99;
        BSz = -99;
        PVxE = -99;
        PVyE = -99;
        PVzE = -99;
        BSxErr = -99;
        BSyErr = -99;
        BSzErr = -99;
        BSdxdz = -99;
        BSdydz = -99;
        BSdxdzErr = -99;
        BSdydzErr = -99;
        BSWidthX = -99;
        BSWidthXErr = -99;
        BSWidthY = -99;
        BSWidthYErr = -99;
        
        RunNo_mix = -99;
        EvtNo_mix = -99;
        LumiNo_mix = -99;
        Dsize_mix = -99;
        PVx_mix = -99;
        PVy_mix = -99;
        PVz_mix = -99;
        PVnchi2_mix = -99;
        BSx_mix = -99;
        BSy_mix = -99;
        BSz_mix = -99;
        PVxE_mix = -99;
        PVyE_mix = -99;
        PVzE_mix = -99;
        BSxErr_mix = -99;
        BSyErr_mix = -99;
        BSzErr_mix = -99;
        BSdxdz_mix = -99;
        BSdydz_mix = -99;
        BSdxdzErr_mix = -99;
        BSdydzErr_mix = -99;
        BSWidthX_mix = -99;
        BSWidthXErr_mix = -99;
        BSWidthY_mix = -99;
        BSWidthYErr_mix = -99;

    }
    ~DJetTree() {};

    DJetTree(TTree* t) : DJetTree() {
        this->create_tree(t);
    }

    void create_tree(TTree* t);

    void set_hlt_tree(TTree* ht, Bool_t isPP);

    void clear_vectors();
    void copy_variables(DTree dt);
    void copy_variables_mix(DTree dt);
    void copy_variables_gen(GTree gt);
    void copy_variables_gen_mix(GTree gt);
    void copy_index(DTree dt, int i);
    void copy_index_mix(DTree dt, int i);
    void copy_index_gen(GTree gt, int i);
    void copy_index_gen_mix(GTree gt, int i);

    int isPP;
    uint32_t run;
    unsigned long long evt;
    uint32_t lumi;
    int hiBin;
    float vz;
    float weight;
    float pthat;

    float hiEvtPlanes[29];

    int njet_akpu3pf;
    std::vector<float> jetptCorr_akpu3pf;
    std::vector<float> jetrawpt_akpu3pf;
    std::vector<float> jetpt_akpu3pf;
    std::vector<float> jeteta_akpu3pf;
    std::vector<float> jetphi_akpu3pf;
    std::vector<int> jetnpfpart_akpu3pf;
    std::vector<float> gjetpt_akpu3pf;
    std::vector<float> gjeteta_akpu3pf;
    std::vector<float> gjetphi_akpu3pf;
    std::vector<int> gjetflavor_akpu3pf;
    std::vector<int> subid_akpu3pf;
    std::vector<float> chargedMax_akpu3pf;
    std::vector<float> chargedSum_akpu3pf;
    std::vector<int> chargedN_akpu3pf;
    std::vector<float> photonMax_akpu3pf;
    std::vector<float> photonSum_akpu3pf;
    std::vector<int> photonN_akpu3pf;
    std::vector<float> neutralMax_akpu3pf;
    std::vector<float> neutralSum_akpu3pf;
    std::vector<int> neutralN_akpu3pf;
    std::vector<float> eMax_akpu3pf;
    std::vector<float> eSum_akpu3pf;
    std::vector<int> eN_akpu3pf;
    std::vector<float> muMax_akpu3pf;
    std::vector<float> muSum_akpu3pf;
    std::vector<int> muN_akpu3pf;

    int ngen_akpu3pf;
    std::vector<float> genpt_akpu3pf;
    std::vector<float> geneta_akpu3pf;
    std::vector<float> genphi_akpu3pf;
    std::vector<int> gensubid_akpu3pf;

    int njet_akpu4pf;
    std::vector<float> jetptCorr_akpu4pf;
    std::vector<float> jetpt_akpu4pf;
    std::vector<float> jeteta_akpu4pf;
    std::vector<float> jetphi_akpu4pf;
    std::vector<float> gjetpt_akpu4pf;
    std::vector<float> gjeteta_akpu4pf;
    std::vector<float> gjetphi_akpu4pf;
    std::vector<int> gjetflavor_akpu4pf;
    std::vector<float> chargedSum_akpu4pf;
    std::vector<int> subid_akpu4pf;

    int ngen_akpu4pf;
    std::vector<float> genpt_akpu4pf;
    std::vector<float> geneta_akpu4pf;
    std::vector<float> genphi_akpu4pf;
    std::vector<int> gensubid_akpu4pf;

    int           RunNo;
    int           EvtNo;
    int           LumiNo;
    int           Dsize;
    float         PVx;
    float         PVy;
    float         PVz;
    float         PVnchi2;
    float         BSx;
    float         BSy;
    float         BSz;
    float         PVxE;
    float         PVyE;
    float         PVzE;
    float         BSxErr;
    float         BSyErr;
    float         BSzErr;
    float         BSdxdz;
    float         BSdydz;
    float         BSdxdzErr;
    float         BSdydzErr;
    float         BSWidthX;
    float         BSWidthXErr;
    float         BSWidthY;
    float         BSWidthYErr;

    std::vector<int>       Dindex;
    std::vector<int>       Dtype;
    std::vector<float>     Dmass;
    std::vector<float>     Dpt;
    std::vector<float>     Deta;
    std::vector<float>     Dphi;
    std::vector<float>     Dy;
    std::vector<float>     DvtxX;
    std::vector<float>     DvtxY;
    std::vector<float>     Dd0;
    std::vector<float>     Dd0Err;
    std::vector<float>     Ddxyz;
    std::vector<float>     DdxyzErr;
    std::vector<float>     Dchi2ndf;
    std::vector<float>     Dchi2cl;
    std::vector<float>     Ddtheta;
    std::vector<float>     Dlxy;
    std::vector<float>     Dalpha;
    std::vector<float>     DsvpvDistance;
    std::vector<float>     DsvpvDisErr;
    std::vector<float>     DsvpvDistance_2D;
    std::vector<float>     DsvpvDisErr_2D;
    std::vector<float>     DlxyBS;
    std::vector<float>     DlxyBSErr;
    std::vector<float>     DMaxDoca;
    std::vector<float>     Dtrk1Pt;
    std::vector<float>     Dtrk2Pt;
    std::vector<float>     Dtrk1Eta;
    std::vector<float>     Dtrk2Eta;
    std::vector<float>     Dtrk1Phi;
    std::vector<float>     Dtrk2Phi;
    std::vector<float>     Dtrk1PtErr;
    std::vector<float>     Dtrk2PtErr;
    std::vector<float>     Dtrk1Dxy;
    std::vector<float>     Dtrk2Dxy;
    std::vector<float>     Dtrk1PixelHit;
    std::vector<float>     Dtrk2PixelHit;
    std::vector<float>     Dtrk1StripHit;
    std::vector<float>     Dtrk2StripHit;
    std::vector<float>     Dtrk1nStripLayer;
    std::vector<float>     Dtrk2nStripLayer;
    std::vector<float>     Dtrk1nPixelLayer;
    std::vector<float>     Dtrk2nPixelLayer;
    std::vector<float>     Dtrk1Chi2ndf;
    std::vector<float>     Dtrk2Chi2ndf;
    std::vector<float>     Dtrk1MassHypo;
    std::vector<float>     Dtrk2MassHypo;
    std::vector<int>       Dtrk1Algo;
    std::vector<int>       Dtrk2Algo;
    std::vector<int>       Dtrk1originalAlgo;
    std::vector<int>       Dtrk2originalAlgo;
    std::vector<bool>      Dtrk1highPurity;
    std::vector<bool>      Dtrk2highPurity;
    std::vector<int>       Dtrk1Idx;
    std::vector<int>       Dtrk2Idx;
    std::vector<float>     Dtrk1EtaErr;
    std::vector<float>     Dtrk2EtaErr;
    std::vector<float>     Dtrk1PhiErr;
    std::vector<float>     Dtrk2PhiErr;
    std::vector<float>     Dtrk1Y;
    std::vector<float>     Dtrk2Y;
    std::vector<float>     Dtrk1D0Err;
    std::vector<float>     Dtrk2D0Err;
    std::vector<float>     Dtrk1MVAVal;
    std::vector<float>     Dtrk2MVAVal;
    std::vector<int>       Dtrk1Quality;
    std::vector<int>       Dtrk2Quality;
    std::vector<float>     Dgen;
    std::vector<int>       DgenIndex;
    std::vector<int>       DgennDa;
    std::vector<float>     Dgenpt;
    std::vector<float>     Dgeneta;
    std::vector<float>     Dgenphi;
    std::vector<float>     Dgeny;
    std::vector<int>       DgencollisionId;
    std::vector<float>     DgenBAncestorpt;
    std::vector<int>       DgenBAncestorpdgId;

    int                    Gsize;
    std::vector<float>     Gy;
    std::vector<float>     Geta;
    std::vector<float>     Gphi;
    std::vector<float>     Gpt;
    std::vector<int>       GpdgId;
    std::vector<int>       GcollisionId;
    std::vector<int>       GisSignal;
    std::vector<float>     GBAncestorpt;
    std::vector<int>       GBAncestorpdgId;
    std::vector<float>     Gtk1pt;
    std::vector<float>     Gtk1eta;
    std::vector<float>     Gtk1y;
    std::vector<float>     Gtk1phi;
    std::vector<float>     Gtk2pt;
    std::vector<float>     Gtk2eta;
    std::vector<float>     Gtk2y;
    std::vector<float>     Gtk2phi;
    
    
    int nmix;
    float dvz_mix[nEventsToMix];
    int dhiBin_mix[nEventsToMix];
    float dhiEvtPlanes_mix[nEventsToMix];
    UInt_t run_mix[nEventsToMix];
    ULong64_t evt_mix[nEventsToMix];
    UInt_t lumi_mix[nEventsToMix];


    int           RunNo_mix;
    int           EvtNo_mix;
    int           LumiNo_mix;
    int           Dsize_mix;
    float         PVx_mix;
    float         PVy_mix;
    float         PVz_mix;
    float         PVnchi2_mix;
    float         BSx_mix;
    float         BSy_mix;
    float         BSz_mix;
    float         PVxE_mix;
    float         PVyE_mix;
    float         PVzE_mix;
    float         BSxErr_mix;
    float         BSyErr_mix;
    float         BSzErr_mix;
    float         BSdxdz_mix;
    float         BSdydz_mix;
    float         BSdxdzErr_mix;
    float         BSdydzErr_mix;
    float         BSWidthX_mix;
    float         BSWidthXErr_mix;
    float         BSWidthY_mix;
    float         BSWidthYErr_mix;



    int njet_akpu3pf_mix;
    std::vector<float> jetptCorr_akpu3pf_mix;
    std::vector<float> jetrawpt_akpu3pf_mix;
    std::vector<float> jetpt_akpu3pf_mix;
    std::vector<float> jeteta_akpu3pf_mix;
    std::vector<float> jetphi_akpu3pf_mix;
    std::vector<int> jetnpfpart_akpu3pf_mix;
    std::vector<float> gjetpt_akpu3pf_mix;
    std::vector<float> gjeteta_akpu3pf_mix;
    std::vector<float> gjetphi_akpu3pf_mix;
    std::vector<int> gjetflavor_akpu3pf_mix;
    std::vector<int> subid_akpu3pf_mix;
    std::vector<float> chargedMax_akpu3pf_mix;
    std::vector<float> chargedSum_akpu3pf_mix;
    std::vector<int> chargedN_akpu3pf_mix;
    std::vector<float> photonMax_akpu3pf_mix;
    std::vector<float> photonSum_akpu3pf_mix;
    std::vector<int> photonN_akpu3pf_mix;
    std::vector<float> neutralMax_akpu3pf_mix;
    std::vector<float> neutralSum_akpu3pf_mix;
    std::vector<int> neutralN_akpu3pf_mix;
    std::vector<float> eMax_akpu3pf_mix;
    std::vector<float> eSum_akpu3pf_mix;
    std::vector<int> eN_akpu3pf_mix;
    std::vector<float> muMax_akpu3pf_mix;
    std::vector<float> muSum_akpu3pf_mix;
    std::vector<int> muN_akpu3pf_mix;
    std::vector<int> nmixEv_mix;
    
    int ngen_akpu3pf_mix;
    std::vector<float> genpt_akpu3pf_mix;
    std::vector<float> geneta_akpu3pf_mix;
    std::vector<float> genphi_akpu3pf_mix;
    std::vector<int> gensubid_akpu3pf_mix;
    std::vector<int> genev_mix;
    


    std::vector<int>       Dindex_mix;
    std::vector<int>       Dtype_mix;
    std::vector<float>     Dmass_mix;
    std::vector<float>     Dpt_mix;
    std::vector<float>     Deta_mix;
    std::vector<float>     Dphi_mix;
    std::vector<float>     Dy_mix;
    std::vector<float>     DvtxX_mix;
    std::vector<float>     DvtxY_mix;
    std::vector<float>     Dd0_mix;
    std::vector<float>     Dd0Err_mix;
    std::vector<float>     Ddxyz_mix;
    std::vector<float>     DdxyzErr_mix;
    std::vector<float>     Dchi2ndf_mix;
    std::vector<float>     Dchi2cl_mix;
    std::vector<float>     Ddtheta_mix;
    std::vector<float>     Dlxy_mix;
    std::vector<float>     Dalpha_mix;
    std::vector<float>     DsvpvDistance_mix;
    std::vector<float>     DsvpvDisErr_mix;
    std::vector<float>     DsvpvDistance_2D_mix;
    std::vector<float>     DsvpvDisErr_2D_mix;
    std::vector<float>     DlxyBS_mix;
    std::vector<float>     DlxyBSErr_mix;
    std::vector<float>     DMaxDoca_mix;
    std::vector<float>     Dtrk1Pt_mix;
    std::vector<float>     Dtrk2Pt_mix;
    std::vector<float>     Dtrk1Eta_mix;
    std::vector<float>     Dtrk2Eta_mix;
    std::vector<float>     Dtrk1Phi_mix;
    std::vector<float>     Dtrk2Phi_mix;
    std::vector<float>     Dtrk1PtErr_mix;
    std::vector<float>     Dtrk2PtErr_mix;
    std::vector<float>     Dtrk1Dxy_mix;
    std::vector<float>     Dtrk2Dxy_mix;
    std::vector<float>     Dtrk1PixelHit_mix;
    std::vector<float>     Dtrk2PixelHit_mix;
    std::vector<float>     Dtrk1StripHit_mix;
    std::vector<float>     Dtrk2StripHit_mix;
    std::vector<float>     Dtrk1nStripLayer_mix;
    std::vector<float>     Dtrk2nStripLayer_mix;
    std::vector<float>     Dtrk1nPixelLayer_mix;
    std::vector<float>     Dtrk2nPixelLayer_mix;
    std::vector<float>     Dtrk1Chi2ndf_mix;
    std::vector<float>     Dtrk2Chi2ndf_mix;
    std::vector<float>     Dtrk1MassHypo_mix;
    std::vector<float>     Dtrk2MassHypo_mix;
    std::vector<int>       Dtrk1Algo_mix;
    std::vector<int>       Dtrk2Algo_mix;
    std::vector<int>       Dtrk1originalAlgo_mix;
    std::vector<int>       Dtrk2originalAlgo_mix;
    std::vector<bool>      Dtrk1highPurity_mix;
    std::vector<bool>      Dtrk2highPurity_mix;
    std::vector<int>       Dtrk1Idx_mix;
    std::vector<int>       Dtrk2Idx_mix;
    std::vector<float>     Dtrk1EtaErr_mix;
    std::vector<float>     Dtrk2EtaErr_mix;
    std::vector<float>     Dtrk1PhiErr_mix;
    std::vector<float>     Dtrk2PhiErr_mix;
    std::vector<float>     Dtrk1Y_mix;
    std::vector<float>     Dtrk2Y_mix;
    std::vector<float>     Dtrk1D0Err_mix;
    std::vector<float>     Dtrk2D0Err_mix;
    std::vector<float>     Dtrk1MVAVal_mix;
    std::vector<float>     Dtrk2MVAVal_mix;
    std::vector<int>       Dtrk1Quality_mix;
    std::vector<int>       Dtrk2Quality_mix;
    std::vector<float>     Dgen_mix;
    std::vector<int>       DgenIndex_mix;
    std::vector<int>       DgennDa_mix;
    std::vector<float>     Dgenpt_mix;
    std::vector<float>     Dgeneta_mix;
    std::vector<float>     Dgenphi_mix;
    std::vector<float>     Dgeny_mix;
    std::vector<int>       DgencollisionId_mix;
    std::vector<float>     DgenBAncestorpt_mix;
    std::vector<int>       DgenBAncestorpdgId_mix;

    int                    Gsize_mix;
    std::vector<float>     Gy_mix;
    std::vector<float>     Geta_mix;
    std::vector<float>     Gphi_mix;
    std::vector<float>     Gpt_mix;
    std::vector<int>       GpdgId_mix;
    std::vector<int>       GcollisionId_mix;
    std::vector<int>       GisSignal_mix;
    std::vector<float>     GBAncestorpt_mix;
    std::vector<int>       GBAncestorpdgId_mix;
    std::vector<float>     Gtk1pt_mix;
    std::vector<float>     Gtk1eta_mix;
    std::vector<float>     Gtk1y_mix;
    std::vector<float>     Gtk1phi_mix;
    std::vector<float>     Gtk2pt_mix;
    std::vector<float>     Gtk2eta_mix;
    std::vector<float>     Gtk2y_mix;
    std::vector<float>     Gtk2phi_mix;



};

void DJetTree::create_tree(TTree* t) {
    t->Branch("isPP", &isPP, "isPP/I");
    t->Branch("run", &run, "run/i");
    t->Branch("evt", &evt, "evt/l");
    t->Branch("lumi", &lumi, "lumi/i");
    t->Branch("hiBin", &hiBin, "hiBin/I");
    t->Branch("vz", &vz, "vz/F");
    t->Branch("weight", &weight, "weight/F");
    t->Branch("pthat", &pthat, "pthat/F");

    t->Branch("hiEvtPlanes", hiEvtPlanes, "hiEvtPlanes[29]/F");

    t->Branch("njet_akpu3pf", &njet_akpu3pf, "njet_akpu3pf/I");
    t->Branch("jetptCorr_akpu3pf", &jetptCorr_akpu3pf);
    t->Branch("jetpt_akpu3pf", &jetpt_akpu3pf);
    t->Branch("jetrawpt_akpu3pf", &jetrawpt_akpu3pf);
    t->Branch("jeteta_akpu3pf", &jeteta_akpu3pf);
    t->Branch("jetphi_akpu3pf", &jetphi_akpu3pf);
    t->Branch("jetnpfpart_akpu3pf", &jetnpfpart_akpu3pf);
    t->Branch("gjetpt_akpu3pf", &gjetpt_akpu3pf);
    t->Branch("gjeteta_akpu3pf", &gjeteta_akpu3pf);
    t->Branch("gjetphi_akpu3pf", &gjetphi_akpu3pf);
    t->Branch("gjetflavor_akpu3pf", &gjetflavor_akpu3pf);
    t->Branch("subid_akpu3pf", &subid_akpu3pf);
    t->Branch("chargedMax_akpu3pf", &chargedMax_akpu3pf);
    t->Branch("chargedSum_akpu3pf", &chargedSum_akpu3pf);
    t->Branch("chargedN_akpu3pf", &chargedN_akpu3pf);
    t->Branch("photonMax_akpu3pf", &photonMax_akpu3pf);
    t->Branch("photonSum_akpu3pf", &photonSum_akpu3pf);
    t->Branch("photonN_akpu3pf", &photonN_akpu3pf);
    t->Branch("neutralMax_akpu3pf", &neutralMax_akpu3pf);
    t->Branch("neutralSum_akpu3pf", &neutralSum_akpu3pf);
    t->Branch("neutralN_akpu3pf", &neutralN_akpu3pf);
    t->Branch("eMax_akpu3pf", &eMax_akpu3pf);
    t->Branch("eSum_akpu3pf", &eSum_akpu3pf);
    t->Branch("eN_akpu3pf", &eN_akpu3pf);
    t->Branch("muMax_akpu3pf", &muMax_akpu3pf);
    t->Branch("muSum_akpu3pf", &muSum_akpu3pf);
    t->Branch("muN_akpu3pf", &muN_akpu3pf);
    t->Branch("nmixEv_mix", &nmixEv_mix);


    t->Branch("ngen_akpu3pf", &ngen_akpu3pf, "ngen_akpu3pf/I");
    t->Branch("genpt_akpu3pf", &genpt_akpu3pf);
    t->Branch("geneta_akpu3pf", &geneta_akpu3pf);
    t->Branch("genphi_akpu3pf", &genphi_akpu3pf);
    t->Branch("gensubid_akpu3pf", &gensubid_akpu3pf);
    t->Branch("genev_mix", &genev_mix);


    t->Branch("njet_akpu4pf", &njet_akpu4pf, "njet_akpu4pf/I");
    t->Branch("jetptCorr_akpu4pf", &jetptCorr_akpu4pf);
    t->Branch("jetpt_akpu4pf", &jetpt_akpu4pf);
    t->Branch("jeteta_akpu4pf", &jeteta_akpu4pf);
    t->Branch("jetphi_akpu4pf", &jetphi_akpu4pf);
    t->Branch("gjetpt_akpu4pf", &gjetpt_akpu4pf);
    t->Branch("gjeteta_akpu4pf", &gjeteta_akpu4pf);
    t->Branch("gjetphi_akpu4pf", &gjetphi_akpu4pf);
    t->Branch("gjetflavor_akpu4pf", &gjetflavor_akpu4pf);
    t->Branch("chargedSum_akpu4pf", &chargedSum_akpu4pf);
    t->Branch("subid_akpu4pf", &subid_akpu4pf);

    t->Branch("ngen_akpu4pf", &ngen_akpu4pf, "ngen_akpu4pf/I");
    t->Branch("genpt_akpu4pf", &genpt_akpu4pf);
    t->Branch("geneta_akpu4pf", &geneta_akpu4pf);
    t->Branch("genphi_akpu4pf", &genphi_akpu4pf);
    t->Branch("gensubid_akpu4pf", &gensubid_akpu4pf);

    t->Branch("RunNo", &RunNo, "RunNo/I");
    t->Branch("EvtNo", &EvtNo, "EvtNo/I");
    t->Branch("LumiNo", &LumiNo, "LumiNo/I");
    t->Branch("Dsize", &Dsize, "Dsize/I");
    t->Branch("PVx", &PVx, "PVx/F");
    t->Branch("PVy", &PVy, "PVy/F");
    t->Branch("PVz", &PVz, "PVz/F");
    t->Branch("PVnchi2", &PVnchi2, "PVnchi2/F");
    t->Branch("BSx", &BSx, "BSx/F");
    t->Branch("BSy", &BSy, "BSy/F");
    t->Branch("BSz", &BSz, "BSz/F");
    t->Branch("PVxE", &PVxE, "PVxE/F");
    t->Branch("PVyE", &PVyE, "PVyE/F");
    t->Branch("PVzE", &PVzE, "PVzE/F");
    t->Branch("BSxErr", &BSxErr, "BSxErr/F");
    t->Branch("BSyErr", &BSyErr, "BSyErr/F");
    t->Branch("BSzErr", &BSzErr, "BSzErr/F");
    t->Branch("BSdxdz", &BSdxdz, "BSdxdz/F");
    t->Branch("BSdydz", &BSdydz, "BSdydz/F");
    t->Branch("BSdxdzErr", &BSdxdzErr, "BSdxdzErr/F");
    t->Branch("BSdydzErr", &BSdydzErr, "BSdydzErr/F");
    t->Branch("BSWidthX", &BSWidthX, "BSWidthX/F");
    t->Branch("BSWidthXErr", &BSWidthXErr, "BSWidthXErr/F");
    t->Branch("BSWidthY", &BSWidthY, "BSWidthY/F");
    t->Branch("BSWidthYErr", &BSWidthYErr, "BSWidthYErr/F");

    t->Branch("Dindex", &Dindex);
    t->Branch("Dtype", &Dtype);
    t->Branch("Dmass", &Dmass);
    t->Branch("Dpt", &Dpt);
    t->Branch("Deta", &Deta);
    t->Branch("Dphi", &Dphi);
    t->Branch("Dy", &Dy);
    t->Branch("DvtxX", &DvtxX);
    t->Branch("DvtxY", &DvtxY);
    t->Branch("Dd0", &Dd0);
    t->Branch("Dd0Err", &Dd0Err);
    t->Branch("Ddxyz", &Ddxyz);
    t->Branch("DdxyzErr", &DdxyzErr);
    t->Branch("Dchi2ndf", &Dchi2ndf);
    t->Branch("Dchi2cl", &Dchi2cl);
    t->Branch("Ddtheta", &Ddtheta);
    t->Branch("Dlxy", &Dlxy);
    t->Branch("Dalpha", &Dalpha);
    t->Branch("DsvpvDistance", &DsvpvDistance);
    t->Branch("DsvpvDisErr", &DsvpvDisErr);
    t->Branch("DsvpvDistance_2D", &DsvpvDistance_2D);
    t->Branch("DsvpvDisErr_2D", &DsvpvDisErr_2D);
    t->Branch("DlxyBS", &DlxyBS);
    t->Branch("DlxyBSErr", &DlxyBSErr);
    t->Branch("DMaxDoca", &DMaxDoca);
    t->Branch("Dtrk1Pt", &Dtrk1Pt);
    t->Branch("Dtrk2Pt", &Dtrk2Pt);
    t->Branch("Dtrk1Eta", &Dtrk1Eta);
    t->Branch("Dtrk2Eta", &Dtrk2Eta);
    t->Branch("Dtrk1Phi", &Dtrk1Phi);
    t->Branch("Dtrk2Phi", &Dtrk2Phi);
    t->Branch("Dtrk1PtErr", &Dtrk1PtErr);
    t->Branch("Dtrk2PtErr", &Dtrk2PtErr);
    t->Branch("Dtrk1Dxy", &Dtrk1Dxy);
    t->Branch("Dtrk2Dxy", &Dtrk2Dxy);
    t->Branch("Dtrk1PixelHit", &Dtrk1PixelHit);
    t->Branch("Dtrk2PixelHit", &Dtrk2PixelHit);
    t->Branch("Dtrk1StripHit", &Dtrk1StripHit);
    t->Branch("Dtrk2StripHit", &Dtrk2StripHit);
    t->Branch("Dtrk1nStripLayer", &Dtrk1nStripLayer);
    t->Branch("Dtrk2nStripLayer", &Dtrk2nStripLayer);
    t->Branch("Dtrk1nPixelLayer", &Dtrk1nPixelLayer);
    t->Branch("Dtrk2nPixelLayer", &Dtrk2nPixelLayer);
    t->Branch("Dtrk1Chi2ndf", &Dtrk1Chi2ndf);
    t->Branch("Dtrk2Chi2ndf", &Dtrk2Chi2ndf);
    t->Branch("Dtrk1MassHypo", &Dtrk1MassHypo);
    t->Branch("Dtrk2MassHypo", &Dtrk2MassHypo);
    t->Branch("Dtrk1Algo", &Dtrk1Algo);
    t->Branch("Dtrk2Algo", &Dtrk2Algo);
    t->Branch("Dtrk1originalAlgo", &Dtrk1originalAlgo);
    t->Branch("Dtrk2originalAlgo", &Dtrk2originalAlgo);
    t->Branch("Dtrk1highPurity", &Dtrk1highPurity);
    t->Branch("Dtrk2highPurity", &Dtrk2highPurity);
    t->Branch("Dtrk1Idx", &Dtrk1Idx);
    t->Branch("Dtrk2Idx", &Dtrk2Idx);
    t->Branch("Dtrk1EtaErr", &Dtrk1EtaErr);
    t->Branch("Dtrk2EtaErr", &Dtrk2EtaErr);
    t->Branch("Dtrk1PhiErr", &Dtrk1PhiErr);
    t->Branch("Dtrk2PhiErr", &Dtrk2PhiErr);
    t->Branch("Dtrk1Y", &Dtrk1Y);
    t->Branch("Dtrk2Y", &Dtrk2Y);
    t->Branch("Dtrk1D0Err", &Dtrk1D0Err);
    t->Branch("Dtrk2D0Err", &Dtrk2D0Err);
    t->Branch("Dtrk1MVAVal", &Dtrk1MVAVal);
    t->Branch("Dtrk2MVAVal", &Dtrk2MVAVal);
    t->Branch("Dtrk1Quality", &Dtrk1Quality);
    t->Branch("Dtrk2Quality", &Dtrk2Quality);
    t->Branch("Dgen", &Dgen);
    t->Branch("DgenIndex", &DgenIndex);
    t->Branch("DgennDa", &DgennDa);
    t->Branch("Dgenpt", &Dgenpt);
    t->Branch("Dgeneta", &Dgeneta);
    t->Branch("Dgenphi", &Dgenphi);
    t->Branch("Dgeny", &Dgeny);
    t->Branch("DgencollisionId", &DgencollisionId);
    t->Branch("DgenBAncestorpt", &DgenBAncestorpt);
    t->Branch("DgenBAncestorpdgId", &DgenBAncestorpdgId);

    t->Branch("Gsize",&Gsize,"Gsize/I");
    t->Branch("Gy",&Gy);
    t->Branch("Geta",&Geta);
    t->Branch("Gphi",&Gphi);
    t->Branch("Gpt",&Gpt);
    t->Branch("GpdgId",&GpdgId);
    t->Branch("GcollisionId",&GcollisionId);
    t->Branch("GisSignal",&GisSignal);
    t->Branch("GBAncestorpt",&GBAncestorpt);
    t->Branch("GBAncestorpdgId",&GBAncestorpdgId);
    t->Branch("Gtk1pt",&Gtk1pt);
    t->Branch("Gtk1eta",&Gtk1eta);
    t->Branch("Gtk1y",&Gtk1y);
    t->Branch("Gtk1phi",&Gtk1phi);
    t->Branch("Gtk2pt",&Gtk2pt);
    t->Branch("Gtk2eta",&Gtk2eta);
    t->Branch("Gtk2y",&Gtk2y);
    t->Branch("Gtk2phi",&Gtk2phi);
    
    t->Branch("nmix", &nmix, "nmix/I");
    t->Branch("dvz_mix", dvz_mix, "dvz_mix[nmix]/F");
    t->Branch("dhiBin_mix", dhiBin_mix, "dhiBin_mix[nmix]/I");
    t->Branch("dhiEvtPlanes_mix", dhiEvtPlanes_mix, "dhiEvtPlanes_mix[nmix]/F");
    t->Branch("run_mix", run_mix, "run_mix[nmix]/i");
    t->Branch("evt_mix", evt_mix, "evt_mix[nmix]/l");
    t->Branch("lumi_mix", lumi_mix, "lumi_mix[nmix]/i");


    t->Branch("njet_akpu3pf_mix", &njet_akpu3pf_mix, "njet_akpu3pf_mix/I");
    t->Branch("jetptCorr_akpu3pf_mix", &jetptCorr_akpu3pf_mix);
    t->Branch("jetpt_akpu3pf_mix", &jetpt_akpu3pf_mix);
    t->Branch("jetrawpt_akpu3pf_mix", &jetrawpt_akpu3pf_mix);
    t->Branch("jeteta_akpu3pf_mix", &jeteta_akpu3pf_mix);
    t->Branch("jetphi_akpu3pf_mix", &jetphi_akpu3pf_mix);
    t->Branch("jetnpfpart_akpu3pf_mix", &jetnpfpart_akpu3pf_mix);
    t->Branch("gjetpt_akpu3pf_mix", &gjetpt_akpu3pf_mix);
    t->Branch("gjeteta_akpu3pf_mix", &gjeteta_akpu3pf_mix);
    t->Branch("gjetphi_akpu3pf_mix", &gjetphi_akpu3pf_mix);
    t->Branch("gjetflavor_akpu3pf_mix", &gjetflavor_akpu3pf_mix);
    t->Branch("subid_akpu3pf_mix", &subid_akpu3pf_mix);
    t->Branch("chargedMax_akpu3pf_mix", &chargedMax_akpu3pf_mix);
    t->Branch("chargedSum_akpu3pf_mix", &chargedSum_akpu3pf_mix);
    t->Branch("chargedN_akpu3pf_mix", &chargedN_akpu3pf_mix);
    t->Branch("photonMax_akpu3pf_mix", &photonMax_akpu3pf_mix);
    t->Branch("photonSum_akpu3pf_mix", &photonSum_akpu3pf_mix);
    t->Branch("photonN_akpu3pf_mix", &photonN_akpu3pf_mix);
    t->Branch("neutralMax_akpu3pf_mix", &neutralMax_akpu3pf_mix);
    t->Branch("neutralSum_akpu3pf_mix", &neutralSum_akpu3pf_mix);
    t->Branch("neutralN_akpu3pf_mix", &neutralN_akpu3pf_mix);
    t->Branch("eMax_akpu3pf_mix", &eMax_akpu3pf_mix);
    t->Branch("eSum_akpu3pf_mix", &eSum_akpu3pf_mix);
    t->Branch("eN_akpu3pf_mix", &eN_akpu3pf_mix);
    t->Branch("muMax_akpu3pf_mix", &muMax_akpu3pf_mix);
    t->Branch("muSum_akpu3pf_mix", &muSum_akpu3pf_mix);
    t->Branch("muN_akpu3pf_mix", &muN_akpu3pf_mix);

    t->Branch("ngen_akpu3pf_mix", &ngen_akpu3pf_mix, "ngen_akpu3pf_mix/I");
    t->Branch("genpt_akpu3pf_mix", &genpt_akpu3pf_mix);
    t->Branch("geneta_akpu3pf_mix", &geneta_akpu3pf_mix);
    t->Branch("genphi_akpu3pf_mix", &genphi_akpu3pf_mix);
    t->Branch("gensubid_akpu3pf_mix", &gensubid_akpu3pf_mix);
    
    t->Branch("Dindex_mix", &Dindex_mix);
    t->Branch("Dtype_mix", &Dtype_mix);
    t->Branch("Dmass_mix", &Dmass_mix);
    t->Branch("Dpt_mix", &Dpt_mix);
    t->Branch("Deta_mix", &Deta_mix);
    t->Branch("Dphi_mix", &Dphi_mix);
    t->Branch("Dy_mix", &Dy_mix);
    t->Branch("DvtxX_mix", &DvtxX_mix);
    t->Branch("DvtxY_mix", &DvtxY_mix);
    t->Branch("Dd0_mix", &Dd0_mix);
    t->Branch("Dd0Err_mix", &Dd0Err_mix);
    t->Branch("Ddxyz_mix", &Ddxyz_mix);
    t->Branch("DdxyzErr_mix", &DdxyzErr_mix);
    t->Branch("Dchi2ndf_mix", &Dchi2ndf_mix);
    t->Branch("Dchi2cl_mix", &Dchi2cl_mix);
    t->Branch("Ddtheta_mix", &Ddtheta_mix);
    t->Branch("Dlxy_mix", &Dlxy_mix);
    t->Branch("Dalpha_mix", &Dalpha_mix);
    t->Branch("DsvpvDistance_mix", &DsvpvDistance_mix);
    t->Branch("DsvpvDisErr_mix", &DsvpvDisErr_mix);
    t->Branch("DsvpvDistance_2D_mix", &DsvpvDistance_2D_mix);
    t->Branch("DsvpvDisErr_2D_mix", &DsvpvDisErr_2D_mix);
    t->Branch("DlxyBS_mix", &DlxyBS_mix);
    t->Branch("DlxyBSErr_mix", &DlxyBSErr_mix);
    t->Branch("DMaxDoca_mix", &DMaxDoca_mix);
    t->Branch("Dtrk1Pt_mix", &Dtrk1Pt_mix);
    t->Branch("Dtrk2Pt_mix", &Dtrk2Pt_mix);
    t->Branch("Dtrk1Eta_mix", &Dtrk1Eta_mix);
    t->Branch("Dtrk2Eta_mix", &Dtrk2Eta_mix);
    t->Branch("Dtrk1Phi_mix", &Dtrk1Phi_mix);
    t->Branch("Dtrk2Phi_mix", &Dtrk2Phi_mix);
    t->Branch("Dtrk1PtErr_mix", &Dtrk1PtErr_mix);
    t->Branch("Dtrk2PtErr_mix", &Dtrk2PtErr_mix);
    t->Branch("Dtrk1Dxy_mix", &Dtrk1Dxy_mix);
    t->Branch("Dtrk2Dxy_mix", &Dtrk2Dxy_mix);
    t->Branch("Dtrk1PixelHit_mix", &Dtrk1PixelHit_mix);
    t->Branch("Dtrk2PixelHit_mix", &Dtrk2PixelHit_mix);
    t->Branch("Dtrk1StripHit_mix", &Dtrk1StripHit_mix);
    t->Branch("Dtrk2StripHit_mix", &Dtrk2StripHit_mix);
    t->Branch("Dtrk1nStripLayer_mix", &Dtrk1nStripLayer_mix);
    t->Branch("Dtrk2nStripLayer_mix", &Dtrk2nStripLayer_mix);
    t->Branch("Dtrk1nPixelLayer_mix", &Dtrk1nPixelLayer_mix);
    t->Branch("Dtrk2nPixelLayer_mix", &Dtrk2nPixelLayer_mix);
    t->Branch("Dtrk1Chi2ndf_mix", &Dtrk1Chi2ndf_mix);
    t->Branch("Dtrk2Chi2ndf_mix", &Dtrk2Chi2ndf_mix);
    t->Branch("Dtrk1MassHypo_mix", &Dtrk1MassHypo_mix);
    t->Branch("Dtrk2MassHypo_mix", &Dtrk2MassHypo_mix);
    t->Branch("Dtrk1Algo_mix", &Dtrk1Algo_mix);
    t->Branch("Dtrk2Algo_mix", &Dtrk2Algo_mix);
    t->Branch("Dtrk1originalAlgo_mix", &Dtrk1originalAlgo_mix);
    t->Branch("Dtrk2originalAlgo_mix", &Dtrk2originalAlgo_mix);
    t->Branch("Dtrk1highPurity_mix", &Dtrk1highPurity_mix);
    t->Branch("Dtrk2highPurity_mix", &Dtrk2highPurity_mix);
    t->Branch("Dtrk1Idx_mix", &Dtrk1Idx_mix);
    t->Branch("Dtrk2Idx_mix", &Dtrk2Idx_mix);
    t->Branch("Dtrk1EtaErr_mix", &Dtrk1EtaErr_mix);
    t->Branch("Dtrk2EtaErr_mix", &Dtrk2EtaErr_mix);
    t->Branch("Dtrk1PhiErr_mix", &Dtrk1PhiErr_mix);
    t->Branch("Dtrk2PhiErr_mix", &Dtrk2PhiErr_mix);
    t->Branch("Dtrk1Y_mix", &Dtrk1Y_mix);
    t->Branch("Dtrk2Y_mix", &Dtrk2Y_mix);
    t->Branch("Dtrk1D0Err_mix", &Dtrk1D0Err_mix);
    t->Branch("Dtrk2D0Err_mix", &Dtrk2D0Err_mix);
    t->Branch("Dtrk1MVAVal_mix", &Dtrk1MVAVal_mix);
    t->Branch("Dtrk2MVAVal_mix", &Dtrk2MVAVal_mix);
    t->Branch("Dtrk1Quality_mix", &Dtrk1Quality_mix);
    t->Branch("Dtrk2Quality_mix", &Dtrk2Quality_mix);
    t->Branch("Dgen_mix", &Dgen_mix);
    t->Branch("DgenIndex_mix", &DgenIndex_mix);
    t->Branch("DgennDa_mix", &DgennDa_mix);
    t->Branch("Dgenpt_mix", &Dgenpt_mix);
    t->Branch("Dgeneta_mix", &Dgeneta_mix);
    t->Branch("Dgenphi_mix", &Dgenphi_mix);
    t->Branch("Dgeny_mix", &Dgeny_mix);
    t->Branch("DgencollisionId_mix", &DgencollisionId_mix);
    t->Branch("DgenBAncestorpt_mix", &DgenBAncestorpt_mix);
    t->Branch("DgenBAncestorpdgId_mix", &DgenBAncestorpdgId_mix);

    t->Branch("Gsize_mix", &Gsize_mix,"Gsize_mix/I");
    t->Branch("Gy_mix", &Gy_mix);
    t->Branch("Geta_mix", &Geta_mix);
    t->Branch("Gphi_mix", &Gphi_mix);
    t->Branch("Gpt_mix", &Gpt_mix);
    t->Branch("GpdgId_mix", &GpdgId_mix);
    t->Branch("GcollisionId_mix", &GcollisionId_mix);
    t->Branch("GisSignal_mix", &GisSignal_mix);
    t->Branch("GBAncestorpt_mix", &GBAncestorpt_mix);
    t->Branch("GBAncestorpdgId_mix", &GBAncestorpdgId_mix);
    t->Branch("Gtk1pt_mix", &Gtk1pt_mix);
    t->Branch("Gtk1eta_mix", &Gtk1eta_mix);
    t->Branch("Gtk1y_mix", &Gtk1y_mix);
    t->Branch("Gtk1phi_mix", &Gtk1phi_mix);
    t->Branch("Gtk2pt_mix", &Gtk2pt_mix);
    t->Branch("Gtk2eta_mix", &Gtk2eta_mix);
    t->Branch("Gtk2y_mix", &Gtk2y_mix);
    t->Branch("Gtk2phi_mix", &Gtk2phi_mix);
    
    t->Branch("RunNo_mix", &RunNo_mix, "RunNo_mix/I");
    t->Branch("EvtNo_mix", &EvtNo_mix, "EvtNo_mix/I");
    t->Branch("LumiNo_mix", &LumiNo_mix, "LumiNo_mix/I");
    t->Branch("Dsize_mix", &Dsize_mix, "Dsize_mix/I");
    t->Branch("PVx_mix", &PVx_mix, "PVx_mix/F");
    t->Branch("PVy_mix", &PVy_mix, "PVy_mix/F");
    t->Branch("PVz_mix", &PVz_mix, "PVz_mix/F");
    t->Branch("PVnchi2_mix", &PVnchi2_mix, "PVnchi2_mix/F");
    t->Branch("BSx_mix", &BSx_mix, "BSx_mix/F");
    t->Branch("BSy_mix", &BSy_mix, "BSy_mix/F");
    t->Branch("BSz_mix", &BSz_mix, "BSz_mix/F");
    t->Branch("PVxE_mix", &PVxE_mix, "PVxE_mix/F");
    t->Branch("PVyE_mix", &PVyE_mix, "PVyE_mix/F");
    t->Branch("PVzE_mix", &PVzE_mix, "PVzE_mix/F");
    t->Branch("BSxErr_mix", &BSxErr_mix, "BSxErr_mix/F");
    t->Branch("BSyErr_mix", &BSyErr_mix, "BSyErr_mix/F");
    t->Branch("BSzErr_mix", &BSzErr_mix, "BSzErr_mix/F");
    t->Branch("BSdxdz_mix", &BSdxdz_mix, "BSdxdz_mix/F");
    t->Branch("BSdydz_mix", &BSdydz_mix, "BSdydz_mix/F");
    t->Branch("BSdxdzErr_mix", &BSdxdzErr_mix, "BSdxdzErr_mix/F");
    t->Branch("BSdydzErr_mix", &BSdydzErr_mix, "BSdydzErr_mix/F");
    t->Branch("BSWidthX_mix", &BSWidthX_mix, "BSWidthX_mix/F");
    t->Branch("BSWidthXErr_mix", &BSWidthXErr_mix, "BSWidthXErr_mix/F");
    t->Branch("BSWidthY_mix", &BSWidthY_mix, "BSWidthY_mix/F");
    t->Branch("BSWidthYErr_mix", &BSWidthYErr_mix, "BSWidthYErr_mix/F");


}

void DJetTree::copy_variables_gen(GTree gt)
{
  Gsize = gt.Gsize;
}


void DJetTree::copy_variables_gen_mix(GTree gt)
{
  Gsize_mix = gt.Gsize;
}


void DJetTree::copy_variables_mix(DTree dt) {
    RunNo_mix = dt.RunNo;
    EvtNo_mix = dt.EvtNo;
    LumiNo_mix = dt.LumiNo;
    Dsize_mix = dt.Dsize;
    PVx_mix = dt.PVx;
    PVy_mix = dt.PVy;
    PVz_mix = dt.PVz;
    PVnchi2_mix = dt.PVnchi2;
    BSx_mix = dt.BSx;
    BSy_mix = dt.BSy;
    BSz_mix = dt.BSz;
    PVxE_mix = dt.PVxE;
    PVyE_mix = dt.PVyE;
    PVzE_mix = dt.PVzE;
    BSxErr_mix = dt.BSxErr;
    BSyErr_mix = dt.BSyErr;
    BSzErr_mix = dt.BSzErr;
    BSdxdz_mix = dt.BSdxdz;
    BSdydz_mix = dt.BSdydz;
    BSdxdzErr_mix = dt.BSdxdzErr;
    BSdydzErr_mix = dt.BSdydzErr;
    BSWidthX_mix = dt.BSWidthX;
    BSWidthXErr_mix = dt.BSWidthXErr;
    BSWidthY_mix = dt.BSWidthY;
    BSWidthYErr_mix = dt.BSWidthYErr;
}

void DJetTree::copy_variables(DTree dt) {
    RunNo = dt.RunNo;
    EvtNo = dt.EvtNo;
    LumiNo = dt.LumiNo;
    Dsize = dt.Dsize;
    PVx = dt.PVx;
    PVy = dt.PVy;
    PVz = dt.PVz;
    PVnchi2 = dt.PVnchi2;
    BSx = dt.BSx;
    BSy = dt.BSy;
    BSz = dt.BSz;
    PVxE = dt.PVxE;
    PVyE = dt.PVyE;
    PVzE = dt.PVzE;
    BSxErr = dt.BSxErr;
    BSyErr = dt.BSyErr;
    BSzErr = dt.BSzErr;
    BSdxdz = dt.BSdxdz;
    BSdydz = dt.BSdydz;
    BSdxdzErr = dt.BSdxdzErr;
    BSdydzErr = dt.BSdydzErr;
    BSWidthX = dt.BSWidthX;
    BSWidthXErr = dt.BSWidthXErr;
    BSWidthY = dt.BSWidthY;
    BSWidthYErr = dt.BSWidthYErr;
}



void DJetTree::copy_index_gen(GTree gt, int i)
{
  Gy.push_back(gt.Gy[i]);
  Geta.push_back(gt.Geta[i]);
  Gphi.push_back(gt.Gphi[i]);
  Gpt.push_back(gt.Gpt[i]);
  GpdgId.push_back(gt.GpdgId[i]);
  GcollisionId.push_back(gt.GcollisionId[i]);
  GisSignal.push_back(gt.GisSignal[i]);
  GBAncestorpt.push_back(gt.GBAncestorpt[i]);
  GBAncestorpdgId.push_back(gt.GBAncestorpdgId[i]);
  Gtk1pt.push_back(gt.Gtk1pt[i]);
  Gtk1eta.push_back(gt.Gtk1eta[i]);
  Gtk1y.push_back(gt.Gtk1y[i]);
  Gtk1phi.push_back(gt.Gtk1phi[i]);
  Gtk2pt.push_back(gt.Gtk2pt[i]);
  Gtk2eta.push_back(gt.Gtk2eta[i]);
  Gtk2y.push_back(gt.Gtk2y[i]);
  Gtk2phi.push_back(gt.Gtk2phi[i]);
}


void DJetTree::copy_index_gen_mix(GTree gt, int i)
{
  Gy_mix.push_back(gt.Gy[i]);
  Geta_mix.push_back(gt.Geta[i]);
  Gphi_mix.push_back(gt.Gphi[i]);
  Gpt_mix.push_back(gt.Gpt[i]);
  GpdgId_mix.push_back(gt.GpdgId[i]);
  GcollisionId_mix.push_back(gt.GcollisionId[i]);
  GisSignal_mix.push_back(gt.GisSignal[i]);
  GBAncestorpt_mix.push_back(gt.GBAncestorpt[i]);
  GBAncestorpdgId_mix.push_back(gt.GBAncestorpdgId[i]);
  Gtk1pt_mix.push_back(gt.Gtk1pt[i]);
  Gtk1eta_mix.push_back(gt.Gtk1eta[i]);
  Gtk1y_mix.push_back(gt.Gtk1y[i]);
  Gtk1phi_mix.push_back(gt.Gtk1phi[i]);
  Gtk2pt_mix.push_back(gt.Gtk2pt[i]);
  Gtk2eta_mix.push_back(gt.Gtk2eta[i]);
  Gtk2y_mix.push_back(gt.Gtk2y[i]);
  Gtk2phi_mix.push_back(gt.Gtk2phi[i]);
}


void DJetTree::copy_index(DTree dt, int i) {
    Dindex.push_back(dt.Dindex[i]);
    Dtype.push_back(dt.Dtype[i]);
    Dmass.push_back(dt.Dmass[i]);
    Dpt.push_back(dt.Dpt[i]);
    Deta.push_back(dt.Deta[i]);
    Dphi.push_back(dt.Dphi[i]);
    Dy.push_back(dt.Dy[i]);
    DvtxX.push_back(dt.DvtxX[i]);
    DvtxY.push_back(dt.DvtxY[i]);
    Dd0.push_back(dt.Dd0[i]);
    Dd0Err.push_back(dt.Dd0Err[i]);
    Ddxyz.push_back(dt.Ddxyz[i]);
    DdxyzErr.push_back(dt.DdxyzErr[i]);
    Dchi2ndf.push_back(dt.Dchi2ndf[i]);
    Dchi2cl.push_back(dt.Dchi2cl[i]);
    Ddtheta.push_back(dt.Ddtheta[i]);
    Dlxy.push_back(dt.Dlxy[i]);
    Dalpha.push_back(dt.Dalpha[i]);
    DsvpvDistance.push_back(dt.DsvpvDistance[i]);
    DsvpvDisErr.push_back(dt.DsvpvDisErr[i]);
    DsvpvDistance_2D.push_back(dt.DsvpvDistance_2D[i]);
    DsvpvDisErr_2D.push_back(dt.DsvpvDisErr_2D[i]);
    DlxyBS.push_back(dt.DlxyBS[i]);
    DlxyBSErr.push_back(dt.DlxyBSErr[i]);
    DMaxDoca.push_back(dt.DMaxDoca[i]);
    Dtrk1Pt.push_back(dt.Dtrk1Pt[i]);
    Dtrk2Pt.push_back(dt.Dtrk2Pt[i]);
    Dtrk1Eta.push_back(dt.Dtrk1Eta[i]);
    Dtrk2Eta.push_back(dt.Dtrk2Eta[i]);
    Dtrk1Phi.push_back(dt.Dtrk1Phi[i]);
    Dtrk2Phi.push_back(dt.Dtrk2Phi[i]);
    Dtrk1PtErr.push_back(dt.Dtrk1PtErr[i]);
    Dtrk2PtErr.push_back(dt.Dtrk2PtErr[i]);
    Dtrk1Dxy.push_back(dt.Dtrk1Dxy[i]);
    Dtrk2Dxy.push_back(dt.Dtrk2Dxy[i]);
    Dtrk1PixelHit.push_back(dt.Dtrk1PixelHit[i]);
    Dtrk2PixelHit.push_back(dt.Dtrk2PixelHit[i]);
    Dtrk1StripHit.push_back(dt.Dtrk1StripHit[i]);
    Dtrk2StripHit.push_back(dt.Dtrk2StripHit[i]);
    Dtrk1nStripLayer.push_back(dt.Dtrk1nStripLayer[i]);
    Dtrk2nStripLayer.push_back(dt.Dtrk2nStripLayer[i]);
    Dtrk1nPixelLayer.push_back(dt.Dtrk1nPixelLayer[i]);
    Dtrk2nPixelLayer.push_back(dt.Dtrk2nPixelLayer[i]);
    Dtrk1Chi2ndf.push_back(dt.Dtrk1Chi2ndf[i]);
    Dtrk2Chi2ndf.push_back(dt.Dtrk2Chi2ndf[i]);
    Dtrk1MassHypo.push_back(dt.Dtrk1MassHypo[i]);
    Dtrk2MassHypo.push_back(dt.Dtrk2MassHypo[i]);
    Dtrk1Algo.push_back(dt.Dtrk1Algo[i]);
    Dtrk2Algo.push_back(dt.Dtrk2Algo[i]);
    Dtrk1originalAlgo.push_back(dt.Dtrk1originalAlgo[i]);
    Dtrk2originalAlgo.push_back(dt.Dtrk2originalAlgo[i]);
    Dtrk1highPurity.push_back(dt.Dtrk1highPurity[i]);
    Dtrk2highPurity.push_back(dt.Dtrk2highPurity[i]);
    Dtrk1Idx.push_back(dt.Dtrk1Idx[i]);
    Dtrk2Idx.push_back(dt.Dtrk2Idx[i]);
    Dtrk1EtaErr.push_back(dt.Dtrk1EtaErr[i]);
    Dtrk2EtaErr.push_back(dt.Dtrk2EtaErr[i]);
    Dtrk1PhiErr.push_back(dt.Dtrk1PhiErr[i]);
    Dtrk2PhiErr.push_back(dt.Dtrk2PhiErr[i]);
    Dtrk1Y.push_back(dt.Dtrk1Y[i]);
    Dtrk2Y.push_back(dt.Dtrk2Y[i]);
    Dtrk1D0Err.push_back(dt.Dtrk1D0Err[i]);
    Dtrk2D0Err.push_back(dt.Dtrk2D0Err[i]);
    Dtrk1MVAVal.push_back(dt.Dtrk1MVAVal[i]);
    Dtrk2MVAVal.push_back(dt.Dtrk2MVAVal[i]);
    Dtrk1Quality.push_back(dt.Dtrk1Quality[i]);
    Dtrk2Quality.push_back(dt.Dtrk2Quality[i]);
    Dgen.push_back(dt.Dgen[i]);
    DgenIndex.push_back(dt.DgenIndex[i]);
    DgennDa.push_back(dt.DgennDa[i]);
    Dgenpt.push_back(dt.Dgenpt[i]);
    Dgeneta.push_back(dt.Dgeneta[i]);
    Dgenphi.push_back(dt.Dgenphi[i]);
    Dgeny.push_back(dt.Dgeny[i]);
    DgencollisionId.push_back(dt.DgencollisionId[i]);
    DgenBAncestorpt.push_back(dt.DgenBAncestorpt[i]);
    DgenBAncestorpdgId.push_back(dt.DgenBAncestorpdgId[i]);
}


void DJetTree::copy_index_mix(DTree dt, int i) {
    Dindex_mix.push_back(dt.Dindex[i]);
    Dtype_mix.push_back(dt.Dtype[i]);
    Dmass_mix.push_back(dt.Dmass[i]);
    Dpt_mix.push_back(dt.Dpt[i]);
    Deta_mix.push_back(dt.Deta[i]);
    Dphi_mix.push_back(dt.Dphi[i]);
    Dy_mix.push_back(dt.Dy[i]);
    DvtxX_mix.push_back(dt.DvtxX[i]);
    DvtxY_mix.push_back(dt.DvtxY[i]);
    Dd0_mix.push_back(dt.Dd0[i]);
    Dd0Err_mix.push_back(dt.Dd0Err[i]);
    Ddxyz_mix.push_back(dt.Ddxyz[i]);
    DdxyzErr_mix.push_back(dt.DdxyzErr[i]);
    Dchi2ndf_mix.push_back(dt.Dchi2ndf[i]);
    Dchi2cl_mix.push_back(dt.Dchi2cl[i]);
    Ddtheta_mix.push_back(dt.Ddtheta[i]);
    Dlxy_mix.push_back(dt.Dlxy[i]);
    Dalpha_mix.push_back(dt.Dalpha[i]);
    DsvpvDistance_mix.push_back(dt.DsvpvDistance[i]);
    DsvpvDisErr_mix.push_back(dt.DsvpvDisErr[i]);
    DsvpvDistance_2D_mix.push_back(dt.DsvpvDistance_2D[i]);
    DsvpvDisErr_2D_mix.push_back(dt.DsvpvDisErr_2D[i]);
    DlxyBS_mix.push_back(dt.DlxyBS[i]);
    DlxyBSErr_mix.push_back(dt.DlxyBSErr[i]);
    DMaxDoca_mix.push_back(dt.DMaxDoca[i]);
    Dtrk1Pt_mix.push_back(dt.Dtrk1Pt[i]);
    Dtrk2Pt_mix.push_back(dt.Dtrk2Pt[i]);
    Dtrk1Eta_mix.push_back(dt.Dtrk1Eta[i]);
    Dtrk2Eta_mix.push_back(dt.Dtrk2Eta[i]);
    Dtrk1Phi_mix.push_back(dt.Dtrk1Phi[i]);
    Dtrk2Phi_mix.push_back(dt.Dtrk2Phi[i]);
    Dtrk1PtErr_mix.push_back(dt.Dtrk1PtErr[i]);
    Dtrk2PtErr_mix.push_back(dt.Dtrk2PtErr[i]);
    Dtrk1Dxy_mix.push_back(dt.Dtrk1Dxy[i]);
    Dtrk2Dxy_mix.push_back(dt.Dtrk2Dxy[i]);
    Dtrk1PixelHit_mix.push_back(dt.Dtrk1PixelHit[i]);
    Dtrk2PixelHit_mix.push_back(dt.Dtrk2PixelHit[i]);
    Dtrk1StripHit_mix.push_back(dt.Dtrk1StripHit[i]);
    Dtrk2StripHit_mix.push_back(dt.Dtrk2StripHit[i]);
    Dtrk1nStripLayer_mix.push_back(dt.Dtrk1nStripLayer[i]);
    Dtrk2nStripLayer_mix.push_back(dt.Dtrk2nStripLayer[i]);
    Dtrk1nPixelLayer_mix.push_back(dt.Dtrk1nPixelLayer[i]);
    Dtrk2nPixelLayer_mix.push_back(dt.Dtrk2nPixelLayer[i]);
    Dtrk1Chi2ndf_mix.push_back(dt.Dtrk1Chi2ndf[i]);
    Dtrk2Chi2ndf_mix.push_back(dt.Dtrk2Chi2ndf[i]);
    Dtrk1MassHypo_mix.push_back(dt.Dtrk1MassHypo[i]);
    Dtrk2MassHypo_mix.push_back(dt.Dtrk2MassHypo[i]);
    Dtrk1Algo_mix.push_back(dt.Dtrk1Algo[i]);
    Dtrk2Algo_mix.push_back(dt.Dtrk2Algo[i]);
    Dtrk1originalAlgo_mix.push_back(dt.Dtrk1originalAlgo[i]);
    Dtrk2originalAlgo_mix.push_back(dt.Dtrk2originalAlgo[i]);
    Dtrk1highPurity_mix.push_back(dt.Dtrk1highPurity[i]);
    Dtrk2highPurity_mix.push_back(dt.Dtrk2highPurity[i]);
    Dtrk1Idx_mix.push_back(dt.Dtrk1Idx[i]);
    Dtrk2Idx_mix.push_back(dt.Dtrk2Idx[i]);
    Dtrk1EtaErr_mix.push_back(dt.Dtrk1EtaErr[i]);
    Dtrk2EtaErr_mix.push_back(dt.Dtrk2EtaErr[i]);
    Dtrk1PhiErr_mix.push_back(dt.Dtrk1PhiErr[i]);
    Dtrk2PhiErr_mix.push_back(dt.Dtrk2PhiErr[i]);
    Dtrk1Y_mix.push_back(dt.Dtrk1Y[i]);
    Dtrk2Y_mix.push_back(dt.Dtrk2Y[i]);
    Dtrk1D0Err_mix.push_back(dt.Dtrk1D0Err[i]);
    Dtrk2D0Err_mix.push_back(dt.Dtrk2D0Err[i]);
    Dtrk1MVAVal_mix.push_back(dt.Dtrk1MVAVal[i]);
    Dtrk2MVAVal_mix.push_back(dt.Dtrk2MVAVal[i]);
    Dtrk1Quality_mix.push_back(dt.Dtrk1Quality[i]);
    Dtrk2Quality_mix.push_back(dt.Dtrk2Quality[i]);
    Dgen_mix.push_back(dt.Dgen[i]);
    DgenIndex_mix.push_back(dt.DgenIndex[i]);
    DgennDa_mix.push_back(dt.DgennDa[i]);
    Dgenpt_mix.push_back(dt.Dgenpt[i]);
    Dgeneta_mix.push_back(dt.Dgeneta[i]);
    Dgenphi_mix.push_back(dt.Dgenphi[i]);
    Dgeny_mix.push_back(dt.Dgeny[i]);
    DgencollisionId_mix.push_back(dt.DgencollisionId[i]);
    DgenBAncestorpt_mix.push_back(dt.DgenBAncestorpt[i]);
    DgenBAncestorpdgId_mix.push_back(dt.DgenBAncestorpdgId[i]);
}


void DJetTree::clear_vectors() {
    jetptCorr_akpu3pf.clear();
    jetpt_akpu3pf.clear();
    jetrawpt_akpu3pf.clear();
    jeteta_akpu3pf.clear();
    jetphi_akpu3pf.clear();
    jetnpfpart_akpu3pf.clear();
    gjetpt_akpu3pf.clear();
    gjeteta_akpu3pf.clear();
    gjetphi_akpu3pf.clear();
    gjetflavor_akpu3pf.clear();
    subid_akpu3pf.clear();
    chargedMax_akpu3pf.clear();
    chargedSum_akpu3pf.clear();
    chargedN_akpu3pf.clear();
    photonMax_akpu3pf.clear();
    photonSum_akpu3pf.clear();
    photonN_akpu3pf.clear();
    neutralMax_akpu3pf.clear();
    neutralSum_akpu3pf.clear();
    neutralN_akpu3pf.clear();
    eMax_akpu3pf.clear();
    eSum_akpu3pf.clear();
    eN_akpu3pf.clear();
    muMax_akpu3pf.clear();
    muSum_akpu3pf.clear();
    muN_akpu3pf.clear();
    nmixEv_mix.clear();


    genpt_akpu3pf.clear();
    geneta_akpu3pf.clear();
    genphi_akpu3pf.clear();
    gensubid_akpu3pf.clear();
    genev_mix.clear();

    jetptCorr_akpu4pf.clear();
    jetpt_akpu4pf.clear();
    jeteta_akpu4pf.clear();
    jetphi_akpu4pf.clear();
    gjetpt_akpu4pf.clear();
    gjeteta_akpu4pf.clear();
    gjetphi_akpu4pf.clear();
    gjetflavor_akpu4pf.clear();
    chargedSum_akpu4pf.clear();
    subid_akpu4pf.clear();

    genpt_akpu4pf.clear();
    geneta_akpu4pf.clear();
    genphi_akpu4pf.clear();
    gensubid_akpu4pf.clear();

    Dindex.clear();
    Dtype.clear();
    Dmass.clear();
    Dpt.clear();
    Deta.clear();
    Dphi.clear();
    Dy.clear();
    DvtxX.clear();
    DvtxY.clear();
    Dd0.clear();
    Dd0Err.clear();
    Ddxyz.clear();
    DdxyzErr.clear();
    Dchi2ndf.clear();
    Dchi2cl.clear();
    Ddtheta.clear();
    Dlxy.clear();
    Dalpha.clear();
    DsvpvDistance.clear();
    DsvpvDisErr.clear();
    DsvpvDistance_2D.clear();
    DsvpvDisErr_2D.clear();
    DlxyBS.clear();
    DlxyBSErr.clear();
    DMaxDoca.clear();
    Dtrk1Pt.clear();
    Dtrk2Pt.clear();
    Dtrk1Eta.clear();
    Dtrk2Eta.clear();
    Dtrk1Phi.clear();
    Dtrk2Phi.clear();
    Dtrk1PtErr.clear();
    Dtrk2PtErr.clear();
    Dtrk1Dxy.clear();
    Dtrk2Dxy.clear();
    Dtrk1PixelHit.clear();
    Dtrk2PixelHit.clear();
    Dtrk1StripHit.clear();
    Dtrk2StripHit.clear();
    Dtrk1nStripLayer.clear();
    Dtrk2nStripLayer.clear();
    Dtrk1nPixelLayer.clear();
    Dtrk2nPixelLayer.clear();
    Dtrk1Chi2ndf.clear();
    Dtrk2Chi2ndf.clear();
    Dtrk1MassHypo.clear();
    Dtrk2MassHypo.clear();
    Dtrk1Algo.clear();
    Dtrk2Algo.clear();
    Dtrk1originalAlgo.clear();
    Dtrk2originalAlgo.clear();
    Dtrk1highPurity.clear();
    Dtrk2highPurity.clear();
    Dtrk1Idx.clear();
    Dtrk2Idx.clear();
    Dtrk1EtaErr.clear();
    Dtrk2EtaErr.clear();
    Dtrk1PhiErr.clear();
    Dtrk2PhiErr.clear();
    Dtrk1Y.clear();
    Dtrk2Y.clear();
    Dtrk1D0Err.clear();
    Dtrk2D0Err.clear();
    Dtrk1MVAVal.clear();
    Dtrk2MVAVal.clear();
    Dtrk1Quality.clear();
    Dtrk2Quality.clear();
    Dgen.clear();
    DgenIndex.clear();
    DgennDa.clear();
    Dgenpt.clear();
    Dgeneta.clear();
    Dgenphi.clear();
    Dgeny.clear();
    DgencollisionId.clear();
    DgenBAncestorpt.clear();
    DgenBAncestorpdgId.clear();

    Gy.clear();
    Geta.clear();
    Gphi.clear();
    Gpt.clear();
    GpdgId.clear();
    GcollisionId.clear();
    GisSignal.clear();
    GBAncestorpt.clear();
    GBAncestorpdgId.clear();
    Gtk1pt.clear();
    Gtk1eta.clear();
    Gtk1y.clear();
    Gtk1phi.clear();
    Gtk2pt.clear();
    Gtk2eta.clear();
    Gtk2y.clear();
    Gtk2phi.clear();
    
    jetptCorr_akpu3pf_mix.clear();
    jetpt_akpu3pf_mix.clear();
    jetrawpt_akpu3pf_mix.clear();
    jeteta_akpu3pf_mix.clear();
    jetphi_akpu3pf_mix.clear();
    jetnpfpart_akpu3pf_mix.clear();
    gjetpt_akpu3pf_mix.clear();
    gjeteta_akpu3pf_mix.clear();
    gjetphi_akpu3pf_mix.clear();
    gjetflavor_akpu3pf_mix.clear();
    subid_akpu3pf_mix.clear();
    chargedMax_akpu3pf_mix.clear();
    chargedSum_akpu3pf_mix.clear();
    chargedN_akpu3pf_mix.clear();
    photonMax_akpu3pf_mix.clear();
    photonSum_akpu3pf_mix.clear();
    photonN_akpu3pf_mix.clear();
    neutralMax_akpu3pf_mix.clear();
    neutralSum_akpu3pf_mix.clear();
    neutralN_akpu3pf_mix.clear();
    eMax_akpu3pf_mix.clear();
    eSum_akpu3pf_mix.clear();
    eN_akpu3pf_mix.clear();
    muMax_akpu3pf_mix.clear();
    muSum_akpu3pf_mix.clear();
    muN_akpu3pf_mix.clear();

    genpt_akpu3pf_mix.clear();
    geneta_akpu3pf_mix.clear();
    genphi_akpu3pf_mix.clear();
    gensubid_akpu3pf_mix.clear();
    
}

void DJetTree::set_hlt_tree(TTree* ht, Bool_t isPP)
{
  ht->SetBranchStatus("*", 0);
  if(isPP) //pp
    {
      ht->SetBranchStatus("HLT_L1MinimumBias*",1);
      ht->SetBranchStatus("HLT_AK4*",1);
      ht->SetBranchStatus("HLT_Dmeson*",1);
      ht->SetBranchStatus("L1_SingleJet*",1);
    }
  else //PbPb
    {
      ht->SetBranchStatus("HLT_HIL1MinimumBias*",1);
      ht->SetBranchStatus("HLT_HIDmeson*",1);
      ht->SetBranchStatus("HLT_HIPuAK4*",1);
      ht->SetBranchStatus("L1_MinimumBiasHF*",1);
      ht->SetBranchStatus("L1_SingleS1Jet*",1);
      ht->SetBranchStatus("L1_SingleJet*",1);
    }

}

#endif
