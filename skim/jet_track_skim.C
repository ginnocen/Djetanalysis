#include "TRandom3.h"
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"

#include "jet_track_tree.h"
#include "jet_tree.h"
#include "track_tree.h"
#include "genpart_tree.h"

#include "Corrections/L2L3/L2L3ResidualWFits.h"
#include "Corrections/getTrkCorr.h"

#include <stdlib.h>
#include <stdint.h>
#include <functional>
#include <algorithm>

static const double pi = 3.141592653589793238462643383279502884;

double getAngleToEP(double angle);
float getTrkWeight(TrkCorr* trkCorr, int itrk, int hiBin, jetTree* jt_trkcorr, trackTree* tt);

int jet_track_skim(std::string input, std::string output, std::string jet_algo, bool isPP, float weight, std::string mixing_file = "", float jetptmin = 50, int start = 0, int end = -1) {
  // start each file at a different index in the minbias mix tree
  // index is random but deterministic
  uint32_t filehash = std::hash<std::string>()(input) % UINT32_MAX;
  srand(filehash);

  int minbias_start = 0;

  bool isHI = !isPP;
  bool isMC = true;

  /**********************************************************
  * CREATE OUTPUT TREE
  **********************************************************/
  TFile* foutput = new TFile(output.c_str(), "recreate");

  TTree* outtree = new TTree("jtt", "jet track tree");
  jetTrackTree jtt(outtree);

  /**********************************************************
  * OPEN INPUT FILES
  **********************************************************/
  TFile* finput = TFile::Open(input.c_str(), "read");

#define _SET_BRANCH_ADDRESS(tree, branch, var) {    \
  tree->SetBranchStatus(#branch, 1);                \
  tree->SetBranchAddress(#branch, &var);            \
}

  TTree* event_tree = (TTree*)finput->Get("hiEvtAnalyzer/HiTree");
  if (!event_tree) { printf("Could not access event tree!\n"); return 1; }
  event_tree->SetBranchStatus("*", 0);
  int hiBin;
  float vz;
  float hiEvtPlanes[29];
  float pthat;
  _SET_BRANCH_ADDRESS(event_tree, run, jtt.run);
  _SET_BRANCH_ADDRESS(event_tree, evt, jtt.evt);
  _SET_BRANCH_ADDRESS(event_tree, lumi, jtt.lumi);
  _SET_BRANCH_ADDRESS(event_tree, hiBin, hiBin);
  _SET_BRANCH_ADDRESS(event_tree, vz, vz);
  _SET_BRANCH_ADDRESS(event_tree, hiEvtPlanes, hiEvtPlanes);
  _SET_BRANCH_ADDRESS(event_tree, pthat, pthat);

  TTree* skim_tree = (TTree*)finput->Get("skimanalysis/HltTree");
  if (!skim_tree) { printf("Could not access skim tree!\n"); return 1; }
  skim_tree->SetBranchStatus("*", 0);
  int pcollisionEventSelection;
  int HBHENoiseFilterResultRun2Loose;
  int pPAprimaryVertexFilter;
  int pBeamScrapingFilter;
  _SET_BRANCH_ADDRESS(skim_tree, pcollisionEventSelection, pcollisionEventSelection);
  _SET_BRANCH_ADDRESS(skim_tree, HBHENoiseFilterResultRun2Loose, HBHENoiseFilterResultRun2Loose);
  _SET_BRANCH_ADDRESS(skim_tree, pPAprimaryVertexFilter, pPAprimaryVertexFilter);
  _SET_BRANCH_ADDRESS(skim_tree, pBeamScrapingFilter, pBeamScrapingFilter);

  TTree* hlt_tree = (TTree*)finput->Get("hltanalysis/HltTree");
  if (!hlt_tree) { printf("Could not access hlt tree!\n"); return 1; }
  hlt_tree->SetBranchStatus("*", 0);
  int HLT_HISinglePhoton40_Eta1p5_v1;
  _SET_BRANCH_ADDRESS(hlt_tree, HLT_HISinglePhoton40_Eta1p5_v1, HLT_HISinglePhoton40_Eta1p5_v1);

  TTree* jet_tree = (TTree*)finput->Get(Form("%s/t", jet_algo.c_str()));
  if (!jet_tree) { printf("Could not access jet tree!\n"); return 1; }
  jet_tree->SetBranchStatus("*", 0);
  jetTree jt(jet_tree);

  TTree* jet_tree_for_trk_corr = isPP ? (TTree*)finput->Get("ak4CaloJetAnalyzer/t") : (TTree*)finput->Get("akPu4CaloJetAnalyzer/t");
  if (!jet_tree_for_trk_corr) { printf("Could not access jet tree for track corrections!\n"); return 1; }
  jet_tree_for_trk_corr->SetBranchStatus("*", 0);
  jetTree jt_trkcorr(jet_tree_for_trk_corr);

  TTree* track_tree = isPP ? (TTree*)finput->Get("ppTrack/trackTree") : (TTree*)finput->Get("anaTrack/trackTree");
  if (!track_tree) { printf("Could not access track tree!\n"); return 1; }
  track_tree->SetBranchStatus("*", 0);
  trackTree tt(track_tree);

  TTree* genpart_tree = (TTree*)finput->Get("HiGenParticleAna/hi");
  if (!genpart_tree) { printf("Could not access gen tree!\n"); isMC = false; }
  genpartTree gpt;
  if (isMC) {
    genpart_tree->SetBranchStatus("*", 0);
    gpt.read_tree(genpart_tree);
  }
  /**********************************************************
  * OPEN MINBIAS MIXING FILE
  **********************************************************/
  TFile* fmixing = 0;
  TTree* event_tree_mix = 0;
  TTree* skim_tree_mix = 0;
  TTree* jet_tree_mix = 0;
  TTree* jet_tree_for_trk_corr_mix = 0;
  TTree* track_tree_mix = 0;
  TTree* genpart_tree_mix = 0;

  jetTree jt_mix;
  jetTree jt_trkcorr_mix;
  trackTree tt_mix;
  genpartTree gpt_mix;

  int hiBin_mix;
  float vz_mix;
  float hiEvtPlanes_mix[29];

  int pcollisionEventSelection_mix;
  int HBHENoiseFilterResultRun2Loose_mix;
  int pPAprimaryVertexFilter_mix;
  int pBeamScrapingFilter_mix;

  if (!isPP && !mixing_file.empty() && mixing_file.compare("null") != 0) {
    fmixing = TFile::Open(mixing_file.c_str(), "read");

    event_tree_mix = (TTree*)fmixing->Get("hiEvtAnalyzer/HiTree");
    if (!event_tree_mix) { printf("Could not access event tree!\n"); return 1; }
    event_tree_mix->SetBranchStatus("*", 0);
    _SET_BRANCH_ADDRESS(event_tree_mix, hiBin, hiBin_mix);
    _SET_BRANCH_ADDRESS(event_tree_mix, vz, vz_mix);
    _SET_BRANCH_ADDRESS(event_tree_mix, hiEvtPlanes, hiEvtPlanes_mix);

    skim_tree_mix = (TTree*)fmixing->Get("skimanalysis/HltTree");
    if (!skim_tree_mix) { printf("Could not access skim tree!\n"); return 1; }
    skim_tree_mix->SetBranchStatus("*", 0);
    _SET_BRANCH_ADDRESS(skim_tree_mix, pcollisionEventSelection, pcollisionEventSelection_mix);
    _SET_BRANCH_ADDRESS(skim_tree_mix, HBHENoiseFilterResultRun2Loose, HBHENoiseFilterResultRun2Loose_mix);
    _SET_BRANCH_ADDRESS(skim_tree_mix, pPAprimaryVertexFilter, pPAprimaryVertexFilter_mix);
    _SET_BRANCH_ADDRESS(skim_tree_mix, pBeamScrapingFilter, pBeamScrapingFilter_mix);

    jet_tree_mix = (TTree*)fmixing->Get(Form("%s/t", jet_algo.c_str()));
    if (!jet_tree_mix) { printf("Could not access jet tree!\n"); return 1; }
    jet_tree_mix->SetBranchStatus("*", 0);
    jt_mix.read_tree(jet_tree_mix);

    jet_tree_for_trk_corr_mix = isPP ? (TTree*)fmixing->Get("ak4CaloJetAnalyzer/t") : (TTree*)fmixing->Get("akPu4CaloJetAnalyzer/t");
    if (!jet_tree_for_trk_corr_mix) { printf("Could not access jet tree for track corrections!\n"); return 1; }
    jet_tree_for_trk_corr_mix->SetBranchStatus("*", 0);
    jt_trkcorr_mix.read_tree(jet_tree_for_trk_corr_mix);

    track_tree_mix = isPP ? (TTree*)fmixing->Get("ppTrack/trackTree") : (TTree*)fmixing->Get("anaTrack/trackTree");
    if (!track_tree_mix) { printf("Could not access track tree!\n"); return 1; }
    track_tree_mix->SetBranchStatus("*", 0);
    tt_mix.read_tree(track_tree_mix);

    if (isMC) {
      genpart_tree_mix = (TTree*)fmixing->Get("HiGenParticleAna/hi");
      if (!genpart_tree_mix) { printf("Could not access track tree!\n"); return 1; }
      genpart_tree_mix->SetBranchStatus("*", 0);
      gpt_mix.read_tree(genpart_tree_mix);
    }
  }

  /**********************************************************
  * OPEN CORRECTION FILES
  **********************************************************/
  L2L3ResidualWFits* jet_corr = new L2L3ResidualWFits();
  jet_corr->setL2L3Residual(3, 3, false);

  TF1* jetResidualFunction[4] = {0};
  if (isHI) {
    TFile* jetResidualFile = TFile::Open("Corrections/merged_Pythia8_Photon50_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1_0_20160801_pthat_50_RESIDUALCORR.root");
    jetResidualFunction[3] = ((TH1F*)jetResidualFile->Get("resCorr_cent50to100_h"))->GetFunction("f1_p");
    jetResidualFunction[2] = ((TH1F*)jetResidualFile->Get("resCorr_cent30to50_h"))->GetFunction("f1_p");
    jetResidualFunction[1] = ((TH1F*)jetResidualFile->Get("resCorr_cent10to30_h"))->GetFunction("f1_p");
    jetResidualFunction[0] = ((TH1F*)jetResidualFile->Get("resCorr_cent0to10_h"))->GetFunction("f1_p");
  } else {
    jetResidualFunction[0] = new TF1("f1_p", "(1+.5/x)", 5, 300);
  }

  TrkCorr* trkCorr;
  if (isHI)
    trkCorr = new TrkCorr("Corrections/TrkCorr_Jun7_Iterative_PbPb_etaLT2p4/");
  else
    trkCorr = new TrkCorr("Corrections/TrkCorr_July22_Iterative_pp_eta2p4/");

  /**********************************************************
  * BEGIN EVENT LOOP
  **********************************************************/
  int nevents = event_tree->GetEntries();
  for (int j = start; j < nevents; j++) {
    jtt.clear_vectors();

    skim_tree->GetEntry(j);
    event_tree->GetEntry(j);
    hlt_tree->GetEntry(j);

    if (j % 100 == 0) { printf("processing event: %i / %i\n", j, end); }
    if (j == end) { printf("done: %i\n", end); break; }

    if (fabs(vz) > 15) continue;
    if (!isPP) {  // HI event selection
      if ((pcollisionEventSelection < 1)) continue;
      if (!isMC) {
        if (HBHENoiseFilterResultRun2Loose < 1) continue;
      }
    } else {      // pp event selection
      if (pPAprimaryVertexFilter < 1 || pBeamScrapingFilter < 1) continue;
    }

    int centBin = 0;
    if (isHI) {
      int centBins[4] = {20, 60, 100, 200};
      for (; hiBin > centBins[centBin]; ++centBin);
    }

    //! (2.3) Begin jet cuts and selection
    jet_tree->GetEntry(j);

    int njet = 0;
    int nTrk = 0;

    for (int ij = 0; ij < jt.nref; ij++) {
      if (jt.jtpt[ij] > jetptmin && fabs(jt.jteta[ij]) < 1.6) {
        float jetpt_corr = jt.jtpt[ij];

        // jet energy correction
        double xmin, xmax;
        jetResidualFunction[centBin]->GetRange(xmin, xmax);
        if (jetpt_corr > xmin && jetpt_corr < xmax) {
          jetpt_corr = jetpt_corr / jetResidualFunction[centBin]->Eval(jetpt_corr);
        }

        jetpt_corr = jet_corr->get_corrected_pt(jetpt_corr, jt.jteta[ij]);
        if (jetpt_corr < 80) continue; // njet is not incremented

        jtt.jetptCorr.push_back(jetpt_corr);
        jtt.jetpt.push_back(jt.jtpt[ij]);
        jtt.jeteta.push_back(jt.jteta[ij]);
        jtt.jetphi.push_back(jt.jtphi[ij]);
        jtt.gjetpt.push_back(jt.refpt[ij]);
        jtt.gjeteta.push_back(jt.refeta[ij]);
        jtt.gjetphi.push_back(jt.refphi[ij]);
        jtt.gjetflavor.push_back(jt.refparton_flavor[ij]);
        jtt.subid.push_back(jt.subid[ij]);
        jtt.rawpt.push_back(jt.rawpt[ij]);
        jtt.chargedSum.push_back(jt.chargedSum[ij]);
        njet++;
      }
    }
    if (njet == 0) continue;

    jtt.njet = njet;
    //! End jet selection

    jet_tree_for_trk_corr->GetEntry(j);
    float maxJetPt = -999;
    for (int k = 0; k < jt_trkcorr.nref; k++) {
      if (TMath::Abs(jt_trkcorr.jteta[k]) > 2) continue;
      if (jt_trkcorr.jtpt[k] > maxJetPt) maxJetPt = jt_trkcorr.jtpt[k];
    }

    float maxTrkPt = -999;
    //! (2.4) Begin track cuts and selection
    track_tree->GetEntry(j);
    for (int itrk = 0; itrk < tt.nTrk; ++itrk) {
      if (tt.trkPt[itrk] < 1 || tt.trkPt[itrk] > 300 || fabs(tt.trkEta[itrk]) > 2.4) continue;
      if (tt.highPurity[itrk] != 1) continue;
      if (tt.trkPtError[itrk] / tt.trkPt[itrk] > 0.1 || TMath::Abs(tt.trkDz1[itrk] / tt.trkDzError1[itrk]) > 3 || TMath::Abs(tt.trkDxy1[itrk] / tt.trkDxyError1[itrk]) > 3) continue;
      if (!isPP && tt.trkChi2[itrk] / (float)tt.trkNdof[itrk] / (float)tt.trkNlayer[itrk] > 0.15) continue;
      if (!isPP && tt.trkNHit[itrk] < 11) continue;

      float Et = (tt.pfHcal[itrk] + tt.pfEcal[itrk]) / TMath::CosH(tt.trkEta[itrk]);
      if (!(tt.trkPt[itrk] < 20 || (Et > 0.5 * tt.trkPt[itrk]))) continue;
      if (tt.trkPt[itrk] > maxTrkPt) maxTrkPt = tt.trkPt[itrk];
      float trkWeight = 0;
      if (isPP) trkWeight = getTrkWeight(trkCorr, itrk, 0, &jt_trkcorr, &tt);
      else trkWeight = getTrkWeight(trkCorr, itrk, hiBin, &jt_trkcorr, &tt);

      jtt.trkPt.push_back(tt.trkPt[itrk]);
      jtt.trkPtError.push_back(tt.trkPtError[itrk]);
      jtt.trkNHit.push_back(tt.trkNHit[itrk]);
      jtt.trkNlayer.push_back(tt.trkNlayer[itrk]);
      jtt.trkEta.push_back(tt.trkEta[itrk]);
      jtt.trkPhi.push_back(tt.trkPhi[itrk]);
      jtt.trkCharge.push_back(tt.trkCharge[itrk]);
      jtt.highPurity.push_back(tt.highPurity[itrk]);
      jtt.trkChi2.push_back(tt.trkChi2[itrk]);
      jtt.trkNdof.push_back(tt.trkNdof[itrk]);
      jtt.trkDxy1.push_back(tt.trkDxy1[itrk]);
      jtt.trkDxyError1.push_back(tt.trkDxyError1[itrk]);
      jtt.trkDz1.push_back(tt.trkDz1[itrk]);
      jtt.trkDzError1.push_back(tt.trkDzError1[itrk]);
      jtt.pfEcal.push_back(tt.pfEcal[itrk]);
      jtt.pfHcal.push_back(tt.pfHcal[itrk]);
      jtt.trkWeight.push_back(trkWeight);
      nTrk++;
    }
    jtt.nTrk = nTrk;
    //! End track selection

    jtt.ngen = jt.ngen;
    for (int igen = 0; igen < jt.ngen; ++igen) {
      if (jt.genpt[igen] < 60) continue;
      if (fabs(jt.geneta[igen]) > 1.6) continue;
      jtt.genpt.push_back(jt.genpt[igen]);
      jtt.geneta.push_back(jt.geneta[igen]);
      jtt.genphi.push_back(jt.genphi[igen]);
      jtt.gensubid.push_back(jt.gensubid[igen]);
    }

    if (isMC) {
      genpart_tree->GetEntry(j);
      jtt.mult = gpt.mult;
      for (int igenp = 0; igenp < gpt.mult; ++igenp) {
        jtt.pt.push_back((*gpt.pt)[igenp]);
        jtt.eta.push_back((*gpt.eta)[igenp]);
        jtt.phi.push_back((*gpt.phi)[igenp]);
        jtt.pdg.push_back((*gpt.pdg)[igenp]);
        jtt.chg.push_back((*gpt.chg)[igenp]);
        jtt.matchingID.push_back((*gpt.matchingID)[igenp]);
        jtt.sube.push_back((*gpt.sube)[igenp]);
      }
    }

    int nmix = 0;
    int nlooped = 0;
    int njet_mix = 0;
    int ngen_mix = 0;
    int nTrk_mix = 0;
    int mult_mix = 0;

    //! (2.5) Begin minbias mixing criteria machinery
    if (!isPP && !mixing_file.empty() && mixing_file.compare("null") != 0) {
      int minbias_end = minbias_start;

      bool wraparound = false;

      // Start looping through the mixed event starting where we left off, so we don't always mix same events
      const int nevent_mix = event_tree_mix->GetEntries();
      for (int iminbias = minbias_start; iminbias <= nevent_mix; ++iminbias) {
        // this part lets us wrap around to the beginning if we reach the last event
        if (iminbias == nevent_mix) {
          wraparound = true;
          iminbias = -1;
          continue;
        }
        if (wraparound && iminbias == minbias_start) break; // came back to start, done mixing
        nlooped++;

        event_tree_mix->GetEntry(iminbias);
        if (fabs(vz_mix) > 15) continue;
        skim_tree_mix->GetEntry(iminbias);
        if (!isPP) { // HI event selection
          if ((pcollisionEventSelection_mix < 1))  continue;
          if (!isMC) {
            if (HBHENoiseFilterResultRun2Loose_mix < 1) continue;
          }
        } else { // pp event selection
          if (pPAprimaryVertexFilter_mix < 1 || pBeamScrapingFilter_mix < 1)  continue;
        }

        //! (2.51) HiBin, vz, eventplane selection
        if (abs(hiBin - hiBin_mix) > 0) continue;
        if (fabs(vz - vz_mix) > 1) continue;
        float dphi_evplane = acos(cos(fabs(hiEvtPlanes[8] - hiEvtPlanes_mix[8])));
        if (dphi_evplane > TMath::Pi() / 16.0) continue;
        // now we are within 0.5% centrality, 5cm vz and pi/16 angle of the original event

        jet_tree_for_trk_corr_mix->GetEntry(iminbias);

        float maxJetPt_mix = -999;
        for (int k = 0; k < jt_trkcorr_mix.nref; k++) {
          if (TMath::Abs(jt_trkcorr_mix.jteta[k]) > 2) continue;
          if (jt_trkcorr_mix.jtpt[k] > maxJetPt_mix) maxJetPt_mix = jt_trkcorr_mix.jtpt[k];
        }

        //! (2.52) Jets from mixed events
        jet_tree_mix->GetEntry(iminbias);
        for (int ijetmix = 0; ijetmix < jt_mix.nref; ++ijetmix) {
          if (jt_mix.jtpt[ijetmix] < jetptmin) continue;
          if (fabs(jt_mix.jteta[ijetmix]) > 1.6) continue;

          float jetpt_corr_mix = jt_mix.jtpt[ijetmix];

          // jet energy correction
          double xmin, xmax;
          jetResidualFunction[centBin]->GetRange(xmin, xmax);
          if (jetpt_corr_mix > xmin && jetpt_corr_mix < xmax) {
            jetpt_corr_mix = jetpt_corr_mix / jetResidualFunction[centBin]->Eval(jetpt_corr_mix);
          }

          jetpt_corr_mix = jet_corr->get_corrected_pt(jetpt_corr_mix, jt_mix.jteta[ijetmix]);
          if (jetpt_corr_mix < 80) continue; // njet_mix is not incremented

          jtt.jetptCorr_mix.push_back(jetpt_corr_mix);
          jtt.jetpt_mix.push_back(jt_mix.jtpt[ijetmix]);
          jtt.jeteta_mix.push_back(jt_mix.jteta[ijetmix]);
          jtt.jetphi_mix.push_back(jt_mix.jtphi[ijetmix]);
          jtt.gjetpt_mix.push_back(jt_mix.refpt[ijetmix]);
          jtt.gjeteta_mix.push_back(jt_mix.refeta[ijetmix]);
          jtt.gjetphi_mix.push_back(jt_mix.refphi[ijetmix]);
          jtt.subid_mix.push_back(jt_mix.subid[ijetmix]);
          jtt.rawpt_mix.push_back(jt_mix.rawpt[ijetmix]);
          jtt.chargedSum_mix.push_back(jt_mix.chargedSum[ijetmix]);
          jtt.nmixEv_mix.push_back(nmix);
          njet_mix++;
        }

        if (isMC) {
          for (int igenj_mix = 0; igenj_mix < jt_mix.ngen; igenj_mix++) {
            if (jt_mix.genpt[igenj_mix] < 80) continue;
            if (fabs(jt_mix.geneta[igenj_mix]) > 1.6) continue;
            jtt.genpt_mix.push_back(jt_mix.genpt[igenj_mix]);
            jtt.geneta_mix.push_back(jt_mix.geneta[igenj_mix]);
            jtt.genphi_mix.push_back(jt_mix.genphi[igenj_mix]);
            jtt.gensubid_mix.push_back(jt_mix.gensubid[igenj_mix]);
            jtt.genev_mix.push_back(nmix);
            ngen_mix++;
          }
        }

        //! (2.54) Tracks from jet and cones in mixed events
        track_tree_mix->GetEntry(iminbias);
        for (int itrkmix = 0; itrkmix < tt_mix.nTrk; ++itrkmix) {
          if (tt_mix.trkPt[itrkmix] < 1 || tt_mix.trkPt[itrkmix] > 300 || fabs(tt_mix.trkEta[itrkmix]) > 2.4) continue;

          if (tt_mix.highPurity[itrkmix] != 1) continue;
          if (tt_mix.trkPtError[itrkmix] / tt_mix.trkPt[itrkmix] > 0.1 || TMath::Abs(tt_mix.trkDz1[itrkmix] / tt_mix.trkDzError1[itrkmix]) > 3 || TMath::Abs(tt_mix.trkDxy1[itrkmix] / tt_mix.trkDxyError1[itrkmix]) > 3) continue;
          if (tt_mix.trkChi2[itrkmix] / (float)tt_mix.trkNdof[itrkmix] / (float)tt_mix.trkNlayer[itrkmix] > 0.15) continue;
          if (tt_mix.trkNHit[itrkmix] < 11 && tt_mix.trkPt[itrkmix] > 0.7) continue;
          if ((maxJetPt_mix > 50 && tt_mix.trkPt[itrkmix] > maxJetPt_mix) || (maxJetPt_mix < 50 && tt_mix.trkPt[itrkmix] > 50)) continue;

          float Et = (tt_mix.pfHcal[itrkmix] + tt_mix.pfEcal[itrkmix]) / TMath::CosH(tt_mix.trkEta[itrkmix]);
          if (!(tt_mix.trkPt[itrkmix] < 20 || (Et > 0.5 * tt_mix.trkPt[itrkmix]))) continue;

          float trkweight_mix = 0;
          if (isPP) trkweight_mix = getTrkWeight(trkCorr, itrkmix, 0, &jt_trkcorr_mix, &tt_mix);
          else trkweight_mix = getTrkWeight(trkCorr, itrkmix, hiBin_mix, &jt_trkcorr_mix, &tt_mix);

          jtt.trkFromEv_mix.push_back(nmix);
          jtt.trkPt_mix.push_back(tt_mix.trkPt[itrkmix]);
          jtt.trkEta_mix.push_back(tt_mix.trkEta[itrkmix]);
          jtt.trkPhi_mix.push_back(tt_mix.trkPhi[itrkmix]);
          jtt.trkWeight_mix.push_back(trkweight_mix);
          nTrk_mix++;
        }

        if (isMC) {
          genpart_tree_mix->GetEntry(iminbias);
          for (int igenp = 0; igenp < gpt_mix.mult; ++igenp) {
            if ((*gpt_mix.pt)[igenp] < 1 || (*gpt_mix.pt)[igenp] > 300 || fabs((*gpt_mix.eta)[igenp]) > 2.4) continue;
            if ((*gpt_mix.chg)[igenp] == 0) continue;
            if ((*gpt_mix.pt)[igenp] < 1) continue;

            jtt.pt_mix.push_back((*gpt_mix.pt)[igenp]);
            jtt.eta_mix.push_back((*gpt_mix.eta)[igenp]);
            jtt.phi_mix.push_back((*gpt_mix.phi)[igenp]);
            jtt.pdg_mix.push_back((*gpt_mix.pdg)[igenp]);
            jtt.chg_mix.push_back((*gpt_mix.chg)[igenp]);
            jtt.nev_mix.push_back(nmix);
            mult_mix++;
          }
        }

        jtt.dvz_mix[nmix] = fabs(vz - vz_mix);
        jtt.dhiBin_mix[nmix] = abs(hiBin - hiBin_mix);
        jtt.dhiEvtPlanes_mix[nmix] = dphi_evplane;

        minbias_end = iminbias;
        nmix++;

        if (nmix >= nEventsToMix) break; // done mixing
      }
      minbias_start = minbias_end;
    }
    //! End minbias mixing

    jtt.nmix = nmix;
    jtt.nlooped = nlooped;
    jtt.njet_mix = njet_mix;
    jtt.ngen_mix = ngen_mix;
    jtt.nTrk_mix = nTrk_mix;
    jtt.mult_mix = mult_mix;

    jtt.isPP = isPP;
    jtt.hiBin = hiBin;
    jtt.vz = vz;
    memcpy(jtt.hiEvtPlanes, hiEvtPlanes, 29 * sizeof(float));

    outtree->Fill();
  }

  foutput->cd();
  outtree->Write("", TObject::kOverwrite);
  foutput->Write("", TObject::kOverwrite);
  foutput->Close();

  printf("done\n");

  return 0;
}

double getAngleToEP(double angle) {
  angle = (angle > TMath::Pi()) ? 2 * TMath::Pi() - angle : angle;
  return (angle > TMath::Pi() / 2) ? TMath::Pi() - angle : angle;
}

float getTrkWeight(TrkCorr* trkCorr, int itrk, int hiBin, jetTree* jt_trkcorr, trackTree* tt) {
  float rmin = 999;
  for (int k = 0; k < jt_trkcorr->nref; k++) {
    if (jt_trkcorr->jtpt[k] < 50) break;
    if ((TMath::Abs(jt_trkcorr->chargedSum[k] / jt_trkcorr->rawpt[k]) < 0.01) || (TMath::Abs(jt_trkcorr->jteta[k] > 2))) continue;
    float R = TMath::Power(jt_trkcorr->jteta[k] - tt->trkEta[itrk], 2) + TMath::Power(TMath::ACos(TMath::Cos(jt_trkcorr->jtphi[k] - tt->trkPhi[itrk])), 2);
    if (rmin * rmin > R) rmin = TMath::Power(R, 0.5);
  }

  return trkCorr->getTrkCorr(tt->trkPt[itrk], tt->trkEta[itrk], tt->trkPhi[itrk], hiBin, rmin);
}

int main(int argc, char* argv[]) {
    if (argc == 6)
        return jet_track_skim(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));
    else if (argc == 7)
        return jet_track_skim(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), argv[6]);
    else if (argc == 8)
        return jet_track_skim(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), argv[6], atoi(argv[7]));
    else if (argc == 9)
        return jet_track_skim(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), argv[6], atoi(argv[7]), atoi(argv[8]));
    else if (argc == 10)
        return jet_track_skim(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), argv[6], atoi(argv[7]), atoi(argv[8]), atoi(argv[9]));
    else
        return 1;
}
