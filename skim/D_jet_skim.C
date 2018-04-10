#include "TRandom3.h"
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TMath.h"

#include "D_jet_tree.h"
#include "D_tree.h"
#include "G_tree.h"
#include "jet_tree.h"

#include <stdlib.h>
#include <stdint.h>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>

const int nHiBins = 100;
const int nVzBins = 30;
const int nEventPlaneBins = 16;

int getVzBin(float vz);
int getEventPlaneBin(double eventPlaneAngle);
int gethiBinBin(int hiBin);

static const double pi = 3.141592653589793238462643383279502884;

int D_jet_skim(std::string input, std::string output, bool isPP, bool isMC, float jetptmin, int start = 0, int end = -1, int jobIndex=1, std::string mixing_file="listmixing.list", bool runpfcand=false){

  if(200%nHiBins != 0) { std::cout<<"error: invalid nHiBins."<<std::endl; return 1; }
  bool isHI = !isPP;

  /**********************************************************
   * CREATE OUTPUT TREE
   **********************************************************/
  std::cout<<"  -- Creating output file"<<std::endl;
  TFile* foutput = new TFile(output.c_str(), "recreate");
  TTree* outtree = new TTree("djt", "photon jet track tree");
  DJetTree djt(outtree);

  std::cout<<"  -- Opening input file"<<std::endl;
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
  Int_t HLT_AK4Jet40;
  Int_t HLT_AK4Jet60;
  Int_t HLT_AK4Jet80;
  Int_t HLT_AK4Jet100;
  if(isPP)
    {
      hlt_tree->SetBranchAddress(isMC?"HLT_AK4PFJet40_Eta5p1ForPPRef_v1":"HLT_AK4PFJet40_Eta5p1_v1", &HLT_AK4Jet40);
      hlt_tree->SetBranchAddress(isMC?"HLT_AK4PFJet60_Eta5p1ForPPRef_v1":"HLT_AK4PFJet60_Eta5p1_v1", &HLT_AK4Jet60);
      hlt_tree->SetBranchAddress(isMC?"HLT_AK4PFJet80_Eta5p1ForPPRef_v1":"HLT_AK4PFJet80_Eta5p1_v1", &HLT_AK4Jet80);
      hlt_tree->SetBranchAddress(isMC?"HLT_AK4PFJet100_Eta5p1ForPPRef_v1":"HLT_AK4PFJet100_Eta5p1_v1", &HLT_AK4Jet100);
    }
  else
    {
      hlt_tree->SetBranchAddress(isMC?"HLT_HIPuAK4CaloJet40_Eta5p1_v2":"HLT_HIPuAK4CaloJet40_Eta5p1_v1", &HLT_AK4Jet40);
      hlt_tree->SetBranchAddress(isMC?"HLT_HIPuAK4CaloJet60_Eta5p1_v2":"HLT_HIPuAK4CaloJet60_Eta5p1_v1", &HLT_AK4Jet60);
      hlt_tree->SetBranchAddress(isMC?"HLT_HIPuAK4CaloJet80_Eta5p1_v2":"HLT_HIPuAK4CaloJet80_Eta5p1_v1", &HLT_AK4Jet80);
      hlt_tree->SetBranchAddress(isMC?"HLT_HIPuAK4CaloJet100_Eta5p1_v2":"HLT_HIPuAK4CaloJet100_Eta5p1_v1", &HLT_AK4Jet100);
    }
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

  TTree* pfcand_tree = 0;
  int nPFpart;
  std::vector<float>* pfPt = 0;
  std::vector<float>* pfEta = 0;
  std::vector<float>* pfPhi = 0;
  if(runpfcand)
    {
      if (isPP) pfcand_tree = (TTree*)finput->Get("pfcandAnalyzer/pfTree");
      else pfcand_tree = (TTree*)finput->Get("pfcandAnalyzerCS/pfTree");
      if (!pfcand_tree) { printf("Could not access pfcand tree!\n"); return 1; }
      pfcand_tree->SetBranchStatus("*", 0);
      _SET_BRANCH_ADDRESS(pfcand_tree, nPFpart, nPFpart);
      _SET_BRANCH_ADDRESS(pfcand_tree, pfPt, pfPt);
      _SET_BRANCH_ADDRESS(pfcand_tree, pfEta, pfEta);
      _SET_BRANCH_ADDRESS(pfcand_tree, pfPhi, pfPhi);
    }

  /**********************************************************
   * OPEN MINBIAS MIXING FILE
   **********************************************************/
  std::cout<<"  -- Opening mixing file"<<std::endl;

  std::vector<std::string> mixing_list;

  if (!isPP && !mixing_file.empty() && mixing_file != "null") {
    std::ifstream file_stream(mixing_file);
    if (!file_stream) return 1;

    std::string line;
    while (std::getline(file_stream, line))
      mixing_list.push_back(line);
  }

  int nMixFiles = (int)mixing_list.size();
  std::cout<<"  Number of files: "<<nMixFiles<<std::endl;

  TFile* fmixing[nMixFiles] = {0};
  TTree* event_tree_mix[nMixFiles] = {0};
  TTree* skim_tree_mix[nMixFiles] = {0};
  TTree* jet_tree_akpu3pf_mix[nMixFiles] = {0};

  TTree* D_tree_mix[nMixFiles] = {0};
  TTree* G_tree_mix[nMixFiles] = {0};

  jetTree jt_akpu3pf_mix[nMixFiles];
  DTree dt_mix[nMixFiles];
  GTree gt_mix[nMixFiles];

  /**************************************** should be array *****************************************/
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
  /**************************************** should be array *****************************************/

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

      D_tree_mix[jmbfile] = (TTree*)fmixing[jmbfile]->Get("Dfinder/ntDkpi");
      if (!D_tree_mix[jmbfile]) {printf("Could not access D tree!\n"); return 1; }
      D_tree_mix[jmbfile]->SetBranchStatus("*", 0);
      dt_mix[jmbfile].read_tree(D_tree_mix[jmbfile]);

      G_tree_mix[jmbfile] = (TTree*)fmixing[jmbfile]->Get("Dfinder/ntGen");
      if (!G_tree_mix[jmbfile]) {printf("Could not access G tree!\n"); return 1; }
      G_tree_mix[jmbfile]->SetBranchStatus("*", 0);
      gt_mix[jmbfile].read_tree(G_tree_mix[jmbfile]);
    }
  }

  std::cout<<"  -- Filling mixing map"<<std::endl;
  // std::vector<int> mapFileMix[nHiBins][nVzBins][nEventPlaneBins]; 
  std::vector<int> mapEvtMix[nMixFiles][nHiBins][nVzBins][nEventPlaneBins];
  if(!isPP)
    {
      for(int i=0;i<nMixFiles;i++)
        {
          for(int j=0;j<event_tree_mix[i]->GetEntries();j++)
            {
              event_tree_mix[i]->GetEntry(j);
              if (fabs(vz_mix) > 15) continue;
              skim_tree_mix[i]->GetEntry(j);
              if ((pcollisionEventSelection_mix < 1))  continue;
              if (!isMC) {
                if (HBHENoiseFilterResultRun2Loose_mix < 1) continue;
              }
              int ihiBin_mix = gethiBinBin(hiBin_mix);
              int ivz_mix = getVzBin(vz_mix);
              int iEventPlane_mix = getEventPlaneBin(hiEvtPlanes_mix[8]);
              if(ihiBin_mix < 0 || ivz_mix < 0 || iEventPlane_mix < 0) continue;
              mapEvtMix[i][ihiBin_mix][ivz_mix][iEventPlane_mix].push_back(j);
            }
        }
    }
  
  std::cout<<"  -- Initialization"<<std::endl;
  Long64_t initialMixFile = 0;
  Long64_t initialMixEvent[nHiBins][nVzBins][nEventPlaneBins];
  // if (jobIndex >= 0 && event_tree_mix[0] != 0) {
  //   TRandom3 rand(jobIndex); // random number seed should be fixed or reproducible
  //   initialMixFile = rand.Integer(nMixFiles);
  //   Long64_t nEventMixTmp = event_tree_mix[initialMixFile]->GetEntries();
  //   initialMixEvent = rand.Integer(nEventMixTmp); // Integer(imax) Returns a random integer on [0, imax-1].
  // }

  TRandom3 rand(jobIndex); // random number seed should be fixed or reproducible
  initialMixFile = rand.Integer(nMixFiles);

  int startMixFile[nHiBins][nVzBins][nEventPlaneBins];
  Long64_t startMixEvent[nHiBins][nVzBins][nEventPlaneBins];
  bool usedAllMixEvents[nHiBins][nVzBins][nEventPlaneBins];
  bool rolledBack[nHiBins][nVzBins][nEventPlaneBins];
  if(!isPP)
    {
      for (int i1 = 0; i1 < nHiBins; ++i1) {
        for (int i2 = 0; i2 < nVzBins; ++i2) {
          for (int i3 = 0; i3 < nEventPlaneBins; ++i3) {
            initialMixEvent[i1][i2][i3] = 0;
            Long64_t nEventMixTmp = mapEvtMix[initialMixFile][i1][i2][i3].size();
            if(nEventMixTmp>0) initialMixEvent[i1][i2][i3] = rand.Integer(nEventMixTmp); // Integer(imax) Returns a random integer on [0, imax-1].
            startMixFile[i1][i2][i3] = initialMixFile;
            startMixEvent[i1][i2][i3] = initialMixEvent[i1][i2][i3];
            usedAllMixEvents[i1][i2][i3] = false;
            rolledBack[i1][i2][i3] = false;
          }
        }
      }
    }

  int test=startMixEvent[0][0][0]+startMixFile[0][0][0]+usedAllMixEvents[0][0][0]+rolledBack[nHiBins][nVzBins][nEventPlaneBins];
  test=test+2;

  /**********************************************************
   * BEGIN EVENT LOOP
   **********************************************************/
  std::cout<<"  -- Begin event loop"<<std::endl;

  int nevents = event_tree->GetEntries();
  for (int j = start; j < nevents; j++) {
    djt.clear_vectors();

    skim_tree->GetEntry(j);
    event_tree->GetEntry(j);

    hlt_tree->GetEntry(j);
    if (j % 10 == 0) { printf("processing event: %i / %i\n", j, nevents); }
    if (j == end) { printf("done: %i\n", end); break; }

    // if(!HLT_AK4Jet40 && !HLT_AK4Jet60 && !HLT_AK4Jet80 && !HLT_AK4Jet100) { /*std::cout<<j<<" test: not pass hlt"<<std::endl;*/ continue; }
    if(!isMC && !HLT_AK4Jet60 && !HLT_AK4Jet80 && !HLT_AK4Jet100) { /*std::cout<<j<<" test: not pass hlt"<<std::endl;*/ continue; }

    if (fabs(vz) > 15) continue;
    if (!isPP) {  // HI event selection
      if ((pcollisionEventSelection < 1)) continue;
      if (!isMC) {
        if (HBHENoiseFilterResultRun2Loose < 1) continue;
      }
    } else {      // pp event selection
      if (pPAprimaryVertexFilter < 1 || pBeamScrapingFilter < 1) continue;
    }

    // std::cout<<j<<" test: passing evt sel"<<std::endl;

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
    if(runpfcand) pfcand_tree->GetEntry(j);

    int njet_akpu3pf = 0;
    for (int ij = 0; ij < jt_akpu3pf.nref; ij++) {
      if (jt_akpu3pf.jtpt[ij] > jetptmin && fabs(jt_akpu3pf.jteta[ij]) < 2.0) {

        float jetpt_corr = jt_akpu3pf.jtpt[ij];
        int npfpart = 0;
        if(runpfcand)
          {
            for(int ip=0; ip<nPFpart; ip++)
              {
                if((*pfPt)[ip] < 2) continue;
                float deltaphi = TMath::ACos(TMath::Cos((*pfPhi)[ip] - jt_akpu3pf.jtphi[ij]));
                float deltaeta = (*pfEta)[ip] - jt_akpu3pf.jteta[ij];
                float deltaR = TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                if(deltaR < 0.3) npfpart++;
              }
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

    //! End jet selection

    int nmix = 0;
    int njet_akpu3pf_mix = 0;
    int ngen_akpu3pf_mix = 0;
    
    std::cout<<j<<"th evt going into mixing"<<std::endl;

    //! (2.5) Begin minbias mixing criteria machinery
    if(!isPP)
      {
        if(mixing_file.empty() || mixing_file == "null") { std::cout<<"error: invalid mixing MB file"<<std::endl; return 3; }

        // extract the characteristic bins to be used for event mixing
        int ivz = getVzBin(vz);
        int iEventPlane = getEventPlaneBin(hiEvtPlanes[8]);
        int ihiBin = gethiBinBin(hiBin);

        if (ivz < 0) continue;
        if (iEventPlane < 0) continue;
        if (ihiBin < 0) { std::cout<<"error: something wrong for gethiBinBin"<<std::endl; return 3; }

        int iMixFile = startMixFile[ihiBin][ivz][iEventPlane];
        // Long64_t iMixEvent = startMixEvent[ihiBin][ivz][iEventPlane];
        int iMixEventIndex = startMixEvent[ihiBin][ivz][iEventPlane];
        std::cout<<j<<" start evtindex: "<<iMixEventIndex<<" "<<iMixFile<<std::endl;

        for (; iMixFile < nMixFiles; ++iMixFile) {
          if(usedAllMixEvents[ihiBin][ivz][iEventPlane])  break; // do not reuse the used mix events.
          // Start looping through the mixed event starting where we left off, so we don't always mix same events
          if(mapEvtMix[iMixFile][ihiBin][ivz][iEventPlane].size()==0) continue;

          // Long64_t nMixEvents = event_tree_mix[iMixFile]->GetEntries();
          Long64_t nMixEvents = mapEvtMix[iMixFile][ihiBin][ivz][iEventPlane].size();
          for (; iMixEventIndex < nMixEvents; ++iMixEventIndex) {
            // The mix events for this bin are exhausted.
            if (rolledBack[ihiBin][ivz][iEventPlane] && iMixFile == initialMixFile && iMixEventIndex == initialMixEvent[ihiBin][ivz][iEventPlane]) {
              usedAllMixEvents[ihiBin][ivz][iEventPlane] = true;
              break;
            }

            std::cout<<j<<" "<<iMixEventIndex<<" "<<nMixEvents<<" "<<initialMixEvent[ihiBin][ivz][iEventPlane]<<std::endl;
            Long64_t iMixEvent = mapEvtMix[iMixFile][ihiBin][ivz][iEventPlane].at(iMixEventIndex);
            std::cout<<j<<" "<<iMixEventIndex<<" "<<nMixEvents<<" "<<iMixEvent<<std::endl;

            event_tree_mix[iMixFile]->GetEntry(iMixEvent);
            djt.hiBin_mix[nmix] = hiBin_mix;
            djt.vz_mix[nmix] = vz_mix;
            djt.hiEvtPlanes_mix[nmix] = hiEvtPlanes_mix[8];
            djt.dhiBin_mix[nmix] = abs(hiBin - hiBin_mix);
            djt.dhiEvtPlanes_mix[nmix] = acos(cos(fabs(hiEvtPlanes[8] - hiEvtPlanes_mix[8])));
            djt.run_mix[nmix] = run_mix;
            djt.evt_mix[nmix] = evt_mix;
            djt.lumi_mix[nmix] = lumi_mix;

            // skim_tree_mix[iMixFile]->GetEntry(iMixEvent);
          
            //! (2.52) Jets from mixed events
            jet_tree_akpu3pf_mix[iMixFile]->GetEntry(iMixEvent);
            for (int ijetmix = 0; ijetmix < jt_akpu3pf_mix[iMixFile].nref; ++ijetmix) {
              if (jt_akpu3pf_mix[iMixFile].jtpt[ijetmix] < jetptmin) continue;
              if (fabs(jt_akpu3pf_mix[iMixFile].jteta[ijetmix]) > 2) continue;

              float jetptCorr_mix = jt_akpu3pf_mix[iMixFile].jtpt[ijetmix];
              djt.jetptCorr_akpu3pf_mix.push_back(jetptCorr_mix);
              djt.jetpt_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].jtpt[ijetmix]);
              djt.jeteta_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].jteta[ijetmix]);
              djt.jetphi_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].jtphi[ijetmix]);
              djt.gjetpt_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].refpt[ijetmix]);
              djt.gjeteta_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].refeta[ijetmix]);
              djt.gjetphi_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].refphi[ijetmix]);
              djt.subid_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].subid[ijetmix]);
              djt.nmixEv_mix.push_back(nmix);
              njet_akpu3pf_mix++;
            } //end of loop over ijetmix
            if (isMC) {
              for (int igenj_mix = 0; igenj_mix < jt_akpu3pf_mix[iMixFile].ngen; igenj_mix++) {
                if (jt_akpu3pf_mix[iMixFile].genpt[igenj_mix] < 5) continue;
                if (fabs(jt_akpu3pf_mix[iMixFile].geneta[igenj_mix]) > 2) continue;
                djt.genpt_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].genpt[igenj_mix]);
                djt.geneta_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].geneta[igenj_mix]);
                djt.genphi_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].genphi[igenj_mix]);
                djt.gensubid_akpu3pf_mix.push_back(jt_akpu3pf_mix[iMixFile].gensubid[igenj_mix]);
                djt.genev_mix.push_back(nmix);
                ngen_akpu3pf_mix++;
              }
            }
            //! D cuts and selection
            D_tree_mix[iMixFile]->GetEntry(iMixEvent);
            for (int id = 0; id < dt_mix[iMixFile].Dsize; ++id) {
              djt.copy_index_mix(dt_mix[iMixFile], id);
            }
            djt.copy_variables_mix(dt_mix[iMixFile]);

            G_tree_mix[iMixFile]->GetEntry(iMixEvent);
            for (int id = 0; id < gt_mix[iMixFile].Gsize; ++id) {
              djt.copy_index_gen_mix(gt_mix[iMixFile], id);
            }
            djt.copy_variables_gen_mix(gt_mix[iMixFile]);

            nmix++;
            if (nmix >= nEventsToMix) break; // done mixing
          }// end of loop over mixed events in a single file
          if (nmix >= nEventsToMix) break; // done mixing
          // did not collect enough events after this file, go to next file

          iMixEventIndex = 0;
          if (iMixFile == nMixFiles - 1) {
            // roll back to the first file
            iMixFile = -1;
            rolledBack[ihiBin][ivz][iEventPlane] = true;
          }
        } //end of the loop over mixing files

        startMixEvent[ihiBin][ivz][iEventPlane] = iMixEventIndex + 1;
        startMixFile[ihiBin][ivz][iEventPlane] = iMixFile;        
      } //end of the entire mixing procedure
    //! End minbias mixing

    djt.nmix = nmix;
    djt.njet_akpu3pf_mix = njet_akpu3pf_mix;
    djt.ngen_akpu3pf_mix = ngen_akpu3pf_mix;

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

int getVzBin(float vz)
{
  for (int i = 0; i < nVzBins; ++i){
    if ((i-15) <= vz && vz < (i-14)) return i;
  }
  if (vz == 15) return 29;
  return -1;
}

int gethiBinBin(int hiBin)
{
  int div = 200 / nHiBins;
  if(hiBin < 0 || hiBin > 200) return -1;
  return hiBin/div;
}

int getEventPlaneBin(double eventPlaneAngle)
{
  for (int i = 0; i < nEventPlaneBins; ++i){
    if ((double)i*pi/nEventPlaneBins <= eventPlaneAngle + 0.5*pi && eventPlaneAngle + 0.5*pi < (double)(i+1)*pi/nEventPlaneBins) return i;
  }
  if (eventPlaneAngle + 0.5*pi == (double)pi) return 15;
  return -1;
}

int main(int argc, char* argv[]) {
  if (argc == 6)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[5]));
  else if (argc == 8)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[5]), atoi(argv[6]), atoi(argv[7]));
  else if (argc == 10)
    return D_jet_skim(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), argv[9]);
  printf("Usage: ./D_jet_skim.exe [input] [output] [isPP] [isMC] [jetptmin] [start] [end]\n");
  return 1;
}
