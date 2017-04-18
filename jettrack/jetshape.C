#include "TRandom3.h"
#include "TH1.h"

#include "jettrack.h"

#define _NSMEAR 1

TRandom3 smear_rand(12345);

float getTrkWeight(int trkindex, std::vector<float>* trkweight, std::string jet_part) {
  if (part_type_is("gen", jet_part) || part_type_is("gen0", jet_part))
    return 1;
  return (*trkweight)[trkindex];
}

void jettrack::jetshape(std::string label, int centmin, int centmax, float jetptcut, std::string jet_part, float trkptmin) {
  if (fChain == 0) return;
  int64_t nentries = fChain->GetEntriesFast();

  TFile* fout = new TFile(Form("%s_%s_%d_%d.root", label.data(), jet_part.data(), int(jetptcut), int(trkptmin)), "recreate");

  TH1D* hjetpt = new TH1D(Form("hjetpt_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";jet p_{T};"), 20, 0, 500);
  TH1D* hjetptjetmix = new TH1D(Form("hjetptjetmix_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";jet p_{T};"), 20, 0, 500);
  TH1D* hjetshape = new TH1D(Form("hjetshape_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hjetshapejetmix = new TH1D(Form("hjetshapejetmix_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hjetshapejetmixue = new TH1D(Form("hjetshapejetmixue_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hjetshapeue = new TH1D(Form("hjetshapeue_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);

  // iterators
  int ij = -1, ij_mix = -1, ip = -1, ip_mix = -1;
  int nij = -1, nij_mix = -1, nip = -1, nip_mix = -1;
  std::vector<int> j_ev_mix;
  std::vector<int> p_ev_mix;

  std::vector<float> j_pt;
  std::vector<float> j_pt_mix;
  std::vector<float> p_pt;
  std::vector<float> p_pt_mix;
  std::vector<float> j_eta;
  std::vector<float> j_eta_mix;
  std::vector<float> p_eta;
  std::vector<float> p_eta_mix;
  std::vector<float> j_phi;
  std::vector<float> j_phi_mix;
  std::vector<float> p_phi;
  std::vector<float> p_phi_mix;

  //! (2) Loop
  for (int64_t jentry = 0; jentry < nentries; jentry++) {
    if (jentry % 10000 == 0) { printf("%li/%li\n", jentry, nentries); }
    int64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    fChain->GetEntry(jentry);

    //! (2.1) Event selections
    if (!isPP) {
      if (hiBin < centmin || hiBin >= centmax) continue;
    }

    int njets_perevent = 0;
    int njets_permixevent = 0;

    if (jet_type_is("reco", jet_part) || jet_type_is("sreco", jet_part)) {
      nij = njet;
      j_pt = *jetptCorr;
      j_eta = *jeteta;
      j_phi = *jetphi;
      nij_mix = njet_mix;
      j_pt_mix = *jetptCorr_mix;
      j_eta_mix = *jeteta_mix;
      j_phi_mix = *jetphi_mix;
      j_ev_mix = *nmixEv_mix;
    } else {
      nij = ngen;
      j_pt = *genpt;
      j_eta = *geneta;
      j_phi = *genphi;
      nij_mix = ngen_mix;
      j_pt_mix = *genpt_mix;
      j_eta_mix = *geneta_mix;
      j_phi_mix = *genphi_mix;
      j_ev_mix = *genev_mix;
    }

    if (part_type_is("reco", jet_part)) {
      nip = nTrk;
      p_pt = *trkPt;
      p_eta = *trkEta;
      p_phi = *trkPhi;
      nip_mix = nTrk_mix;
      p_pt_mix = *trkPt_mix;
      p_eta_mix = *trkEta_mix;
      p_phi_mix = *trkPhi_mix;
      p_ev_mix = *trkFromEv_mix;
    } else {
      nip = mult;
      p_pt = *pt;
      p_eta = *eta;
      p_phi = *phi;
      nip_mix = mult_mix;
      p_pt_mix = *pt_mix;
      p_eta_mix = *eta_mix;
      p_phi_mix = *phi_mix;
      p_ev_mix = *nev_mix;
    }

    //! Jet loop
    for (ij = 0; ij < nij; ij++) {
      if (jet_type_is("gen0", jet_part)) {
        if ((*gensubid)[ij] != 0) continue;
      }

      float tmpjetpt = j_pt[ij];
      float tmpjeteta = j_eta[ij];
      float tmpjetphi = j_phi[ij];

      int nsmear = 1;
      float res_pt = 0;
      float res_phi = 0;

      if (!isPP) {
        if (jet_type_is("sgen", jet_part)) {
          int resolutionBin = getResolutionBin(centmin);
          res_pt = getResolutionHI(tmpjetpt, resolutionBin);
          res_phi = getPhiResolutionHI(tmpjetpt, resolutionBin);
          nsmear = _NSMEAR;
        }
      }

      //! apply smearing if pp
      if (isPP) {
        if (jet_type_is("sreco", jet_part)) {
          res_pt = getSigmaRelPt(centmin, tmpjetpt);
          res_phi = getSigmaRelPhi(centmin, tmpjetpt);
          nsmear = _NSMEAR;
        } else if (jet_type_is("sgen", jet_part)) {
          res_pt = getResolutionPP(tmpjetpt);
          res_phi = getPhiResolutionPP(tmpjetpt);
          nsmear = _NSMEAR;
        }
      }

      float smear_weight = 1. / nsmear;
      for (int is = 0; is < nsmear; ++is) {
        tmpjetpt = j_pt[ij] * smear_rand.Gaus(1, res_pt);
        tmpjetphi = j_phi[ij] + smear_rand.Gaus(0, res_phi);

        //! jet selections
        if (tmpjetpt < jetptcut) continue;
        if (fabs(tmpjeteta) > 1.6) continue;

        hjetpt->Fill(tmpjetpt, smear_weight);
        njets_perevent++;

        // raw jet
        for (ip = 0; ip < nip; ++ip) {
          if (part_type_is("gen0", jet_part)) {
            if ((*sube)[ip] != 0) continue;
            if ((*chg)[ip] == 0) continue;
          }
          if (part_type_is("gen", jet_part)) {
            if ((*chg)[ip] == 0) continue;
          }

          if (p_pt[ip] < trkptmin) continue;
          float dphi = acos(cos(tmpjetphi - p_phi[ip]));
          float deta = fabs(tmpjeteta - p_eta[ip]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            hjetshape->Fill(deltar, getTrkWeight(ip, trkWeight, jet_part) * smear_weight);
          }
        }

        if (isPP) continue;
        if (part_type_is("gen0", jet_part)) continue;

        // raw jet ue
        float nmixedUEevents = (nmix + 1) / 2;
        for (ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if (part_type_is("gen", jet_part)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if ((p_ev_mix[ip_mix]) % 2 != 0) continue;
          if (p_pt_mix[ip_mix] < trkptmin) continue;

          float dphi = acos(cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs(tmpjeteta - p_eta_mix[ip_mix]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            hjetshapeue->Fill(deltar, getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedUEevents);
          }
        }
      }
    }

    if (isPP) continue;
    if (jet_type_is("gen0", jet_part)) continue;
    if (part_type_is("gen0", jet_part)) continue;

    //! (2.4) Mix jet loop
    float nmixedjetevents = nmix / 2;
    for (ij_mix = 0; ij_mix < nij_mix; ij_mix++) {
      if (j_ev_mix[ij_mix] % 2 != 1) continue;

      float tmpjetpt = j_pt_mix[ij_mix];
      float tmpjeteta = j_eta_mix[ij_mix];
      float tmpjetphi = j_phi_mix[ij_mix];

      int nsmear = 1;
      float res_pt = 0;
      float res_phi = 0;

      if (jet_type_is("sgen", jet_part)) {
        int resolutionBin = getResolutionBin(centmin);
        res_pt = getResolutionHI(tmpjetpt, resolutionBin);
        res_phi = getPhiResolutionHI(tmpjetpt, resolutionBin);
        nsmear = _NSMEAR;
      }

      float smear_weight = 1. / nsmear;
      for (int is = 0; is < nsmear; ++is) {
        tmpjetpt = j_pt_mix[ij_mix] * smear_rand.Gaus(1, res_pt);
        tmpjetphi = j_phi_mix[ij_mix] + smear_rand.Gaus(0, res_phi);

        if (tmpjetpt < jetptcut) continue;
        if (fabs(tmpjeteta) > 1.6) continue;
        hjetptjetmix->Fill(tmpjetpt, smear_weight / nmixedjetevents);
        njets_permixevent++;

        // mix jet
        for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if (part_type_is("gen0", jet_part)) {
            if ((*sube)[ip_mix] != 0) continue;
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if (part_type_is("gen", jet_part)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if (j_ev_mix[ij_mix] != p_ev_mix[ip_mix]) continue; // tracks and jet come from same mixed event
          if (p_pt_mix[ip_mix] < trkptmin) continue;

          float dphi = acos(cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs(tmpjeteta - p_eta_mix[ip_mix]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            hjetshapejetmix->Fill(deltar, getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedjetevents);
          }
        }

        if (part_type_is("gen0", jet_part)) continue;

        // mix jet ue
        for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if (part_type_is("gen", jet_part)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if (j_ev_mix[ij_mix] != (p_ev_mix[ip_mix] + 1)) continue;
          if (p_pt_mix[ip_mix] < trkptmin) continue;

          float dphi = acos(cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs(tmpjeteta - p_eta_mix[ip_mix]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            hjetshapejetmixue->Fill(deltar, getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedjetevents);
          }
        }
      }
    }
  }

  fout->Write();
  fout->Close();
}

int main(int argc, char* argv[]) {
  if (argc > 8 || argc < 3) {
    printf("usage: ./jetshape [input] [label] [centmin centmax] [jetptcut] [jet_part] [trkptmin]\n");
    return 1;
  }

  jettrack* t = new jettrack(argv[1]);
  if (argc == 3)
    t->jetshape(argv[2]);
  else if (argc == 5)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]));
  else if (argc == 6)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]));
  else if (argc == 7)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), argv[6]);
  else if (argc == 8)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), argv[6], std::atof(argv[7]));

  return 0;
}
