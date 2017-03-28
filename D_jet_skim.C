#include "TRandom3.h"
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"

#include "D_jet_tree.h"
#include "D_tree.h"
#include "jet_tree.h"

#include "L2L3ResidualWFits.h"

#include <stdlib.h>
#include <stdint.h>
#include <functional>
#include <algorithm>

static const double pi = 3.141592653589793238462643383279502884;

int D_jet_skim(std::string input, std::string output, bool isPP, bool isMC, float jetptmin = 10, int start = 0, int end = -1) {
  bool isHI = !isPP;

  /**********************************************************
  * CREATE OUTPUT TREE
  **********************************************************/
  TFile* foutput = new TFile(output.c_str(), "recreate");

  TTree* outtree = new TTree("djt", "photon jet track tree");
  DJetTree djt(outtree);

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
  int hiNevtPlane;
  float hiEvtPlanes[29];
  _SET_BRANCH_ADDRESS(event_tree, run, djt.run);
  _SET_BRANCH_ADDRESS(event_tree, evt, djt.evt);
  _SET_BRANCH_ADDRESS(event_tree, lumi, djt.lumi);
  _SET_BRANCH_ADDRESS(event_tree, hiBin, hiBin);
  _SET_BRANCH_ADDRESS(event_tree, vz, vz);
  _SET_BRANCH_ADDRESS(event_tree, weight, djt.weight);
  _SET_BRANCH_ADDRESS(event_tree, hiNevtPlane, hiNevtPlane);
  _SET_BRANCH_ADDRESS(event_tree, hiEvtPlanes, hiEvtPlanes);

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
  int HLT_HISinglePhoton40_Eta1p5_v2;
  int HLT_HISinglePhoton40_Eta1p5ForPPRef_v1;
  _SET_BRANCH_ADDRESS(hlt_tree, HLT_HISinglePhoton40_Eta1p5_v1, HLT_HISinglePhoton40_Eta1p5_v1);
  _SET_BRANCH_ADDRESS(hlt_tree, HLT_HISinglePhoton40_Eta1p5_v2, HLT_HISinglePhoton40_Eta1p5_v2);
  _SET_BRANCH_ADDRESS(hlt_tree, HLT_HISinglePhoton40_Eta1p5ForPPRef_v1, HLT_HISinglePhoton40_Eta1p5ForPPRef_v1);

  TTree* D_tree = (TTree*)finput->Get("Dfinder/ntDkpi");
  if (!D_tree) {printf("Could not access D tree!\n"); return 1; }
  D_tree->SetBranchStatus("*", 0);
  DTree dt(D_tree);

  TTree* jet_tree_akpu3pf = (TTree*)finput->Get("akPu3PFJetAnalyzer/t");
  if (!jet_tree_akpu3pf) { printf("Could not access jet tree!\n"); return 1; }
  jet_tree_akpu3pf->SetBranchStatus("*", 0);
  jetTree jt_akpu3pf(jet_tree_akpu3pf);

  TTree* jet_tree_akpu4pf = (TTree*)finput->Get("akPu4PFJetAnalyzer/t");
  if (!jet_tree_akpu4pf) { printf("Could not access jet tree!\n"); return 1; }
  jet_tree_akpu4pf->SetBranchStatus("*", 0);
  jetTree jt_akpu4pf(jet_tree_akpu4pf);

  /**********************************************************
  * OPEN CORRECTION FILES
  **********************************************************/

  L2L3ResidualWFits* jet_corr = new L2L3ResidualWFits();
  jet_corr->setL2L3Residual(3, 3, false);

  TF1* jetResidualFunction[4];
  if (isHI) {
    TFile* jetResidualFile = TFile::Open("Corrections/merged_Pythia8_Photon50_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1_0_20160801_pthat_50_RESIDUALCORR.root");
    jetResidualFunction[3] = ((TH1F*)jetResidualFile->Get("resCorr_cent50to100_h"))->GetFunction("f1_p");
    jetResidualFunction[2] = ((TH1F*)jetResidualFile->Get("resCorr_cent30to50_h"))->GetFunction("f1_p");
    jetResidualFunction[1] = ((TH1F*)jetResidualFile->Get("resCorr_cent10to30_h"))->GetFunction("f1_p");
    jetResidualFunction[0] = ((TH1F*)jetResidualFile->Get("resCorr_cent0to10_h"))->GetFunction("f1_p");
  } else {
    jetResidualFunction[0] = new TF1("f1_p", "(1+.5/x)", 5, 300);
  }

  /**********************************************************
  * BEGIN EVENT LOOP
  **********************************************************/
  int nevents = event_tree->GetEntries();
  for (int j = start; j < nevents; j++) {
    djt.clear_vectors();

    skim_tree->GetEntry(j);
    event_tree->GetEntry(j);

    hlt_tree->GetEntry(j);
    if (j % 1000 == 0) { printf("processing event: %i / %i\n", j, nevents); }
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

    //! D cuts and selection
    D_tree->GetEntry(j);
    for (int id = 0; id < dt.Dsize; ++id) {
      djt.copy_index(dt, id);
    }
    djt.copy_variables(dt);

    //! Jet cuts and selection
    int centBin = 0;
    if (isHI) {
      int centBins[4] = {20, 60, 100, 200};
      for (; hiBin > centBins[centBin]; ++centBin);
    }

    jet_tree_akpu3pf->GetEntry(j);

    int njet_akpu3pf = 0;
    for (int ij = 0; ij < jt_akpu3pf.nref; ij++) {
      if (jt_akpu3pf.jtpt[ij] > jetptmin && fabs(jt_akpu3pf.jteta[ij]) < 1.6) {
        // jet energy correction
        double xmin, xmax;
        jetResidualFunction[centBin]->GetRange(xmin, xmax);
        float jetpt_corr = jt_akpu3pf.jtpt[ij];
        if (jetpt_corr > xmin && jetpt_corr < xmax) {
          jetpt_corr = jetpt_corr / jetResidualFunction[centBin]->Eval(jetpt_corr);
        }

        jetpt_corr = jet_corr->get_corrected_pt(jetpt_corr, jt_akpu3pf.jteta[ij]);
        if (jetpt_corr < 30) continue; // njet is not incremented

        djt.jetptCorr_akpu3pf.push_back(jetpt_corr);
        djt.jetpt_akpu3pf.push_back(jt_akpu3pf.jtpt[ij]);
        djt.jeteta_akpu3pf.push_back(jt_akpu3pf.jteta[ij]);
        djt.jetphi_akpu3pf.push_back(jt_akpu3pf.jtphi[ij]);
        djt.gjetpt_akpu3pf.push_back(jt_akpu3pf.refpt[ij]);
        djt.gjeteta_akpu3pf.push_back(jt_akpu3pf.refeta[ij]);
        djt.gjetphi_akpu3pf.push_back(jt_akpu3pf.refphi[ij]);
        djt.gjetflavor_akpu3pf.push_back(jt_akpu3pf.refparton_flavor[ij]);
        djt.subid_akpu3pf.push_back(jt_akpu3pf.subid[ij]);
        djt.chargedSum_akpu3pf.push_back(jt_akpu3pf.chargedSum[ij]);
        njet_akpu3pf++;
      }
    }
    djt.njet_akpu3pf = njet_akpu3pf;

    int njet_akpu4pf = 0;
    for (int ij = 0; ij < jt_akpu4pf.nref; ij++) {
      if (jt_akpu4pf.jtpt[ij] > 30 && fabs(jt_akpu4pf.jteta[ij]) < 1.6) {
        float jetpt_corr = jt_akpu4pf.jtpt[ij];
        djt.jetptCorr_akpu4pf.push_back(jetpt_corr);
        djt.jetpt_akpu4pf.push_back(jt_akpu4pf.jtpt[ij]);
        djt.jeteta_akpu4pf.push_back(jt_akpu4pf.jteta[ij]);
        djt.jetphi_akpu4pf.push_back(jt_akpu4pf.jtphi[ij]);
        djt.gjetpt_akpu4pf.push_back(jt_akpu4pf.refpt[ij]);
        djt.gjeteta_akpu4pf.push_back(jt_akpu4pf.refeta[ij]);
        djt.gjetphi_akpu4pf.push_back(jt_akpu4pf.refphi[ij]);
        djt.gjetflavor_akpu4pf.push_back(jt_akpu4pf.refparton_flavor[ij]);
        djt.subid_akpu4pf.push_back(jt_akpu4pf.subid[ij]);
        djt.chargedSum_akpu4pf.push_back(jt_akpu4pf.chargedSum[ij]);
        njet_akpu4pf++;
      }
    }
    djt.njet_akpu4pf = njet_akpu4pf;
    //! End jet selection

    djt.isPP = isPP;
    djt.hiBin = hiBin;
    djt.vz = vz;
    djt.hiNevtPlane = hiNevtPlane;
    memcpy(djt.hiEvtPlanes, hiEvtPlanes, 29 * sizeof(float));

    outtree->Fill();
  }

  foutput->cd();
  outtree->Write("", TObject::kOverwrite);
  foutput->Write("", TObject::kOverwrite);
  foutput->Close();

  return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 6)
        return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    else if (argc == 7)
        return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    else if (argc == 8)
        return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
    else
        printf("Usage: ./D_jet_skim.exe [input] [output] [isPP] [isMC] [jetptmin] [start] [end]\n");

    return 1;
}
