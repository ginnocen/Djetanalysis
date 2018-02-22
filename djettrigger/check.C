void check(){

  const int samples=2; 
  const int nCases=5;
  const int ntriggers=2;

  TString namefilesMB="/mnt/hadoop/cms/store/user/tatar/MinimumBias6/Run2015E_PromptReco_v1_Run261553_262328_FOREST/0_20170805.root";
  TString eventjetselection="(pPAprimaryVertexFilter&&pBeamScrapingFilter&&fabs(vz)<15&&abs(jteta)<2.0)";
  TString MBselection="(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)";
  TString nameL1triggerMB="L1_SingleJet28_BptxAND";
  TString nametreeMB="ak3PFJetAnalyzer/t";
  TString nametreeHLTMB="hltanalysis/HltTree";
  TString nametreeSkimMB="skimanalysis/HltTree";
  TString nametreeEvtMB="hiEvtAnalyzer/HiTree";
  TString namevariableMB="jtpt";
  
  TString total="!L1_SingleJet28_BptxAND&&jtpt>70&&(pPAprimaryVertexFilter&&pBeamScrapingFilter&&fabs(vz)<15&&abs(jteta)<2.0)&&(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)";
  TString total1="L1_SingleJet28_BptxAND&&(pPAprimaryVertexFilter&&pBeamScrapingFilter&&fabs(vz)<15&&abs(jteta)<2.0)&&(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)";
  

  TFile *finput=new TFile(namefilesMB,"read"); 
  TTree*ttemp=(TTree*)finput->Get(nametreeMB.Data());
  TTree*ttempHLT=(TTree*)finput->Get(nametreeHLTMB.Data());
  TTree*ttempSkim=(TTree*)finput->Get(nametreeSkimMB.Data());
  TTree*ttempEvt=(TTree*)finput->Get(nametreeEvtMB.Data());
		
  ttemp->AddFriend(ttempHLT);
  ttemp->AddFriend(ttempSkim);
  ttemp->AddFriend(ttempEvt);
   
  ttemp->Scan("jtpt","!L1_SingleJet28_BptxAND&&jtpt>70&&(pPAprimaryVertexFilter&&pBeamScrapingFilter&&fabs(vz)<15&&abs(jteta)<2.0)&&(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)");



TFile f("/export/d00/scratch/jwang/Djets/data/DjetFiles_20171120_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"
djt->AddFriend(hlt)
TH1F*hyes=new TH1F("hyes","hyes",1000,0,1000);
TH1F*hno=new TH1F("hno","hno",1000,0,1000);
djt->Draw("jetptCorr_akpu3pf","HLT_AK4PFJet40_Eta5p1_v1==1"*TCut("0.5*TMath::Erf(Max$(jetptCorr_akpu3pf)*0.074089+-2.061318+TMath::Exp((-Max$(jetptCorr_akpu3pf)^2+-2.061318)/(71.143148))*(-0.839758))+0.5"));
djt->Draw("jetptCorr_akpu3pf","HLT_AK4PFJet40_Eta5p1_v1==1");
}

