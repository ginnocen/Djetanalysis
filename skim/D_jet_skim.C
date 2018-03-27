 #include "TRandom3.h"
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TMath.h"

#include "D_jet_tree.h"
#include "D_tree.h"
#include "G_tree.h"
#include "jet_tree.h"

#include "Corrections/L2L3/L2L3ResidualWFits.h"

#include <stdlib.h>
#include <stdint.h>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>

const int nHiBins = 200;
const int nVzBins = 30;
const int nEventPlaneBins = 16;

static const double pi = 3.141592653589793238462643383279502884;

int D_jet_skim(std::string input, std::string output, bool isPP, bool isMC, float jetptmin = 10, int start = 0, int end = -1, std::string mixing_file = "listmixing.list",int jobIndex = -1) {
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

#define _SET_BRANCH_ADDRESS(tree, branch, var) {        \
    tree->SetBranchStatus(#branch, 1);                  \
    tree->SetBranchAddress(#branch, &var);              \
  }

  TTree* event_tree = (TTree*)finput->Get("hiEvtAnalyzer/HiTree");
  if (!event_tree) { printf("Could not access event tree!\n"); return 1; }
  event_tree->SetBranchStatus("*", 0);
  int hiBin;
  float vz;
  float hiEvtPlanes[29];
  _SET_BRANCH_ADDRESS(event_tree, run, djt.run);
  _SET_BRANCH_ADDRESS(event_tree, evt, djt.evt);
  _SET_BRANCH_ADDRESS(event_tree, lumi, djt.lumi);
  _SET_BRANCH_ADDRESS(event_tree, hiBin, hiBin);
  _SET_BRANCH_ADDRESS(event_tree, vz, vz);
  _SET_BRANCH_ADDRESS(event_tree, weight, djt.weight);
  _SET_BRANCH_ADDRESS(event_tree, pthat, djt.pthat);
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
  djt.set_hlt_tree(hlt_tree,isPP);
  foutput->cd();  
  TTree* hlt_new = hlt_tree->CloneTree(0);
  hlt_new->SetName("hlt");

  TTree* D_tree = (TTree*)finput->Get("Dfinder/ntDkpi");
  if (!D_tree) {printf("Could not access D tree!\n"); return 1; }
  D_tree->SetBranchStatus("*", 0);
  DTree dt(D_tree);

  TTree* G_tree = (TTree*)finput->Get("Dfinder/ntGen");
  if (!G_tree) {printf("Could not access G tree!\n"); return 1; }
  G_tree->SetBranchStatus("*", 0);
  GTree gt(G_tree);

  TTree* jet_tree_akpu3pf = 0;
  if (isPP) jet_tree_akpu3pf = (TTree*)finput->Get("ak3PFJetAnalyzer/t");
  else jet_tree_akpu3pf = (TTree*)finput->Get("akPu3PFJetAnalyzer/t");
  if (!jet_tree_akpu3pf) { printf("Could not access jet tree!\n"); return 1; }
  jet_tree_akpu3pf->SetBranchStatus("*", 0);
  jetTree jt_akpu3pf(jet_tree_akpu3pf);

  TTree* jet_tree_akpu4pf = 0;
  if (isPP) jet_tree_akpu4pf = (TTree*)finput->Get("ak4PFJetAnalyzer/t");
  else jet_tree_akpu4pf = (TTree*)finput->Get("akPu4PFJetAnalyzer/t");
  if (!jet_tree_akpu4pf) { printf("Could not access jet tree!\n"); return 1; }
  jet_tree_akpu4pf->SetBranchStatus("*", 0);
  jetTree jt_akpu4pf(jet_tree_akpu4pf);

  TTree* pfcand_tree = 0;
  if (isPP) pfcand_tree = (TTree*)finput->Get("pfcandAnalyzer/pfTree");
  else pfcand_tree = (TTree*)finput->Get("pfcandAnalyzerCS/pfTree");
  if (!pfcand_tree) { printf("Could not access pfcand tree!\n"); return 1; }
  pfcand_tree->SetBranchStatus("*", 0);
  int nPFpart;
  std::vector<float>* pfPt = 0;
  std::vector<float>* pfEta = 0;
  std::vector<float>* pfPhi = 0;
  _SET_BRANCH_ADDRESS(pfcand_tree, nPFpart, nPFpart);
  _SET_BRANCH_ADDRESS(pfcand_tree, pfPt, pfPt);
  _SET_BRANCH_ADDRESS(pfcand_tree, pfEta, pfEta);
  _SET_BRANCH_ADDRESS(pfcand_tree, pfPhi, pfPhi);

  /**********************************************************
  * OPEN MINBIAS MIXING FILE
  **********************************************************/
  std::vector<std::string> mixing_list;

  if (!isPP && !mixing_file.empty() && mixing_file != "null") {
    std::ifstream file_stream(mixing_file);
     if (!file_stream) return 1;

    std::string line;
    while (std::getline(file_stream, line))
      mixing_list.push_back(line);
  }

  int nMixFiles = (int)mixing_list.size();
  std::cout<<"number of files"<<nMixFiles<<std::endl;
  

  TFile* fmixing[nMixFiles] = {0};
  TTree* event_tree_mix[nMixFiles] = {0};
  TTree* skim_tree_mix[nMixFiles] = {0};
  TTree* jet_tree_akpu3pf_mix[nMixFiles] = {0};

  jetTree jt_akpu3pf_mix[nMixFiles];

  int hiBin_mix;
  float vz_mix;
  float hiEvtPlanes_mix[29];
  UInt_t run_mix;
  ULong64_t evt_mix;
  UInt_t lumi_mix;

  int pcollisionEventSelection_mix;
  int HBHENoiseFilterResultRun2Loose_mix;
  int pPAprimaryVertexFilter_mix;
  int pBeamScrapingFilter_mix;


  if (!isPP && !mixing_file.empty() && mixing_file != "null") {
    for (int jmbfile = 0; jmbfile < nMixFiles; ++jmbfile) {
      fmixing[jmbfile] = TFile::Open(mixing_list[jmbfile].c_str(), "read");

      event_tree_mix[jmbfile] = (TTree*)fmixing[jmbfile]->Get("hiEvtAnalyzer/HiTree");
      if (!event_tree_mix[jmbfile]) { printf("Could not access event tree!\n"); return 1; }
      event_tree_mix[jmbfile]->SetBranchStatus("*", 0);
      _SET_BRANCH_ADDRESS(event_tree_mix[jmbfile], hiBin, hiBin_mix);
      _SET_BRANCH_ADDRESS(event_tree_mix[jmbfile], vz, vz_mix);
      _SET_BRANCH_ADDRESS(event_tree_mix[jmbfile], hiEvtPlanes, hiEvtPlanes_mix);
      _SET_BRANCH_ADDRESS(event_tree_mix[jmbfile], run, run_mix);
      _SET_BRANCH_ADDRESS(event_tree_mix[jmbfile], evt, evt_mix);
      _SET_BRANCH_ADDRESS(event_tree_mix[jmbfile], lumi, lumi_mix);

      skim_tree_mix[jmbfile] = (TTree*)fmixing[jmbfile]->Get("skimanalysis/HltTree");
      if (!skim_tree_mix[jmbfile]) { printf("Could not access skim tree!\n"); return 1; }
      skim_tree_mix[jmbfile]->SetBranchStatus("*", 0);
      _SET_BRANCH_ADDRESS(skim_tree_mix[jmbfile], pcollisionEventSelection, pcollisionEventSelection_mix);
      _SET_BRANCH_ADDRESS(skim_tree_mix[jmbfile], HBHENoiseFilterResultRun2Loose, HBHENoiseFilterResultRun2Loose_mix);
      _SET_BRANCH_ADDRESS(skim_tree_mix[jmbfile], pPAprimaryVertexFilter, pPAprimaryVertexFilter_mix);
      _SET_BRANCH_ADDRESS(skim_tree_mix[jmbfile], pBeamScrapingFilter, pBeamScrapingFilter_mix);



      if (isPP) jet_tree_akpu3pf_mix[jmbfile] = (TTree*)fmixing[jmbfile]->Get("ak3PFJetAnalyzer/t");
      else jet_tree_akpu3pf_mix[jmbfile] = (TTree*)fmixing[jmbfile]->Get("akPu3PFJetAnalyzer/t");
      if (!jet_tree_akpu3pf_mix[jmbfile]) { printf("Could not access jet tree!\n"); return 1; }
      jet_tree_akpu3pf_mix[jmbfile]->SetBranchStatus("*", 0);
      jt_akpu3pf_mix[jmbfile].read_tree(jet_tree_akpu3pf_mix[jmbfile]);
    }
  }


  Long64_t initialMixFile = 0;
  Long64_t initialMixEvent = 0;
  if (jobIndex >= 0 && event_tree_mix[0] != 0) {
      TRandom3 rand(jobIndex); // random number seed should be fixed or reproducible
      initialMixFile = rand.Integer(nMixFiles);
      Long64_t nEventMixTmp = event_tree_mix[initialMixFile]->GetEntries();
      initialMixEvent = rand.Integer(nEventMixTmp); // Integer(imax) Returns a random integer on [0, imax-1].
  }

  int startMixFile[nHiBins][nVzBins][nEventPlaneBins];
  Long64_t startMixEvent[nHiBins][nVzBins][nEventPlaneBins];
  bool usedAllMixEvents[nHiBins][nVzBins][nEventPlaneBins];
  bool rolledBack[nHiBins][nVzBins][nEventPlaneBins];
  for (int i1 = 0; i1 < nHiBins; ++i1) {
      for (int i2 = 0; i2 < nVzBins; ++i2) {
          for (int i3 = 0; i3 < nEventPlaneBins; ++i3) {
              startMixFile[i1][i2][i3] = initialMixFile;
              startMixEvent[i1][i2][i3] = initialMixEvent;
              usedAllMixEvents[i1][i2][i3] = false;
              rolledBack[i1][i2][i3] = false;
          }
      }
  }
  
  int test=startMixEvent[0][0][0]+startMixFile[0][0][0]+usedAllMixEvents[0][0][0]+rolledBack[nHiBins][nVzBins][nEventPlaneBins];
  test=test+2;
  /**********************************************************
   * OPEN CORRECTION FILES
   **********************************************************/

  L2L3ResidualWFits* jet_corr = new L2L3ResidualWFits();
  jet_corr->setL2L3Residual(3, 3, false);

  // TF1* jetResidualFunction[4];
  // if (isHI) {
  //   TFile* jetResidualFile = TFile::Open("Corrections/merged_Pythia8_Photon50_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1_0_20160801_pthat_50_RESIDUALCORR.root");
  //   jetResidualFunction[3] = ((TH1F*)jetResidualFile->Get("resCorr_cent50to100_h"))->GetFunction("f1_p");
  //   jetResidualFunction[2] = ((TH1F*)jetResidualFile->Get("resCorr_cent30to50_h"))->GetFunction("f1_p");
  //   jetResidualFunction[1] = ((TH1F*)jetResidualFile->Get("resCorr_cent10to30_h"))->GetFunction("f1_p");
  //   jetResidualFunction[0] = ((TH1F*)jetResidualFile->Get("resCorr_cent0to10_h"))->GetFunction("f1_p");
  // } else {
  //   jetResidualFunction[0] = new TF1("f1_p", "(1+.5/x)", 5, 300);
  // }

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

    //! Gen cuts and selection
    G_tree->GetEntry(j);
    for (int id = 0; id < gt.Gsize; ++id) {
      djt.copy_index_gen(gt, id);
    }
    djt.copy_variables_gen(gt);

    //! Jet cuts and selection
    int centBin = 0;
    if (isHI) {
      int centBins[4] = {20, 60, 100, 200};
      for (; hiBin > centBins[centBin]; ++centBin);
    }

    jet_tree_akpu3pf->GetEntry(j);
    pfcand_tree->GetEntry(j);

    int njet_akpu3pf = 0;
    for (int ij = 0; ij < jt_akpu3pf.nref; ij++) {
      if (jt_akpu3pf.jtpt[ij] > jetptmin && fabs(jt_akpu3pf.jteta[ij]) < 2.0) {

        // jet energy correction
        // double xmin, xmax;
        // jetResidualFunction[centBin]->GetRange(xmin, xmax);
        float jetpt_corr = jt_akpu3pf.jtpt[ij];
        // if (jetpt_corr > xmin && jetpt_corr < xmax) {
        //   jetpt_corr = jetpt_corr / jetResidualFunction[centBin]->Eval(jetpt_corr);
        // }

        // jetpt_corr = jet_corr->get_corrected_pt(jetpt_corr, jt_akpu3pf.jteta[ij]);
        // if (jetpt_corr < 30) continue; // njet is not incremented

        int npfpart = 0;
        for(int ip=0; ip<nPFpart; ip++)
          {
            if((*pfPt)[ip] < 2) continue;
            float deltaphi = TMath::ACos(TMath::Cos((*pfPhi)[ip] - jt_akpu3pf.jtphi[ij]));
            float deltaeta = (*pfEta)[ip] - jt_akpu3pf.jteta[ij];
            float deltaR = TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
            if(deltaR < 0.3) npfpart++;
          }
        djt.jetptCorr_akpu3pf.push_back(jetpt_corr);
        djt.jetnpfpart_akpu3pf.push_back(npfpart);
        djt.jetpt_akpu3pf.push_back(jt_akpu3pf.jtpt[ij]);
        djt.jetrawpt_akpu3pf.push_back(jt_akpu3pf.rawpt[ij]);
        djt.jeteta_akpu3pf.push_back(jt_akpu3pf.jteta[ij]);
        djt.jetphi_akpu3pf.push_back(jt_akpu3pf.jtphi[ij]);
        djt.gjetpt_akpu3pf.push_back(jt_akpu3pf.refpt[ij]);
        djt.gjeteta_akpu3pf.push_back(jt_akpu3pf.refeta[ij]);
        djt.gjetphi_akpu3pf.push_back(jt_akpu3pf.refphi[ij]);
        djt.gjetflavor_akpu3pf.push_back(jt_akpu3pf.refparton_flavor[ij]);
        djt.subid_akpu3pf.push_back(jt_akpu3pf.subid[ij]);
        djt.chargedMax_akpu3pf.push_back(jt_akpu3pf.chargedMax[ij]);
        djt.chargedSum_akpu3pf.push_back(jt_akpu3pf.chargedSum[ij]);
        djt.chargedN_akpu3pf.push_back(jt_akpu3pf.chargedN[ij]);
        djt.photonMax_akpu3pf.push_back(jt_akpu3pf.photonMax[ij]);
        djt.photonSum_akpu3pf.push_back(jt_akpu3pf.photonSum[ij]);
        djt.photonN_akpu3pf.push_back(jt_akpu3pf.photonN[ij]);
        djt.neutralMax_akpu3pf.push_back(jt_akpu3pf.neutralMax[ij]);
        djt.neutralSum_akpu3pf.push_back(jt_akpu3pf.neutralSum[ij]);
        djt.neutralN_akpu3pf.push_back(jt_akpu3pf.neutralN[ij]);
        djt.eMax_akpu3pf.push_back(jt_akpu3pf.eMax[ij]);
        djt.eSum_akpu3pf.push_back(jt_akpu3pf.eSum[ij]);
        djt.eN_akpu3pf.push_back(jt_akpu3pf.eN[ij]);
        djt.muMax_akpu3pf.push_back(jt_akpu3pf.muMax[ij]);
        djt.muSum_akpu3pf.push_back(jt_akpu3pf.muSum[ij]);
        djt.muN_akpu3pf.push_back(jt_akpu3pf.muN[ij]);
        njet_akpu3pf++;
      }
    }
    djt.njet_akpu3pf = njet_akpu3pf;


    djt.ngen_akpu3pf = jt_akpu3pf.ngen;
    for (int igen = 0; igen < jt_akpu3pf.ngen; ++igen) {
      djt.genpt_akpu3pf.push_back(jt_akpu3pf.genpt[igen]);
      djt.geneta_akpu3pf.push_back(jt_akpu3pf.geneta[igen]);
      djt.genphi_akpu3pf.push_back(jt_akpu3pf.genphi[igen]);
      djt.gensubid_akpu3pf.push_back(jt_akpu3pf.gensubid[igen]);
    }

    jet_tree_akpu4pf->GetEntry(j);

    int njet_akpu4pf = 0;
    for (int ij = 0; ij < jt_akpu4pf.nref; ij++) {
      if (jt_akpu4pf.jtpt[ij] > jetptmin && fabs(jt_akpu4pf.jteta[ij]) < 2.0) {
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
    memcpy(djt.hiEvtPlanes, hiEvtPlanes, 29 * sizeof(float));

    outtree->Fill();
    hlt_new->Fill();
  }

  foutput->cd();
  outtree->Write("", TObject::kOverwrite);
  hlt_new->Write("", TObject::kOverwrite);
  foutput->Write("", TObject::kOverwrite);
  foutput->Close();

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 5)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
  else if (argc == 6)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[5]));
  else if (argc == 7)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[5]), atoi(argv[6]));
  else if (argc == 8)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[5]), atoi(argv[6]), atoi(argv[7]));
  else if (argc == 9)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[5]), atoi(argv[6]), atoi(argv[7]),argv[8]);
  else
    printf("Usage: ./D_jet_skim.exe [input] [output] [isPP] [isMC] [jetptmin] [start] [end]\n");

  return 1;
}
