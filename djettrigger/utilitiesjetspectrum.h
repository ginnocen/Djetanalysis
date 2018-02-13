  const int samples=2; 
  const int nCases=4;
  const int ntriggers=2;

  TString namefiles[samples]={"/export/d00/scratch/jwang/Djets/data/DjetFiles_20171120_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root","/export/d00/scratch/jwang/Djets/data/DjetFiles_20171120_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"};
  TString labelsamples[samples]={"pp","PbPb"};  
  
  TString nametree[samples]={"djt","djt"};
  TString nametreeHLT[samples]={"hlt","hlt"};
  TString namevariable[samples]={"jetptCorr_akpu3pf","jetptCorr_akpu3pf"};
  TString nametrigger[samples][ntriggers]={{"HLT_AK4PFJet40_Eta5p1_v1","HLT_AK4PFJet60_Eta5p1_v1"},{"HLT_AK4PFJet40_Eta5p1_v1","HLT_AK4PFJet60_Eta5p1_v1"}};
  TString nametriggerselection[samples][nCases]={{"HLT_AK4PFJet40_Eta5p1_v1&&!HLT_AK4PFJet60_Eta5p1_v1","!HLT_AK4PFJet40_Eta5p1_v1&&HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet40_Eta5p1_v1&&HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet40_Eta5p1_v1||HLT_AK4PFJet60_Eta5p1_v1"},{"HLT_AK4PFJet40_Eta5p1_v1&&!HLT_AK4PFJet60_Eta5p1_v1", "!HLT_AK4PFJet40_Eta5p1_v1&&HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet40_Eta5p1_v1&&HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet40_Eta5p1_v1||HLT_AK4PFJet60_Eta5p1_v1"}};
  TString nametriggerselectiontag[samples][nCases]={{"HLT40only","HLT60only","HLT40_AND_HLT60","HLT40_OR_HLT60"},{"HLT40only","HLT60only","HLT40_AND_HLT60","HLT40_OR_HLT60"}};
  /*
  TString nameHistoInput[nCases]={"hSignalRraw_eta_pt_0","hSignalRraw_eta_pt_1"};
  TString labelCases[nCases]={"Dpt4","Dpt20"};  
  
  int colours[samples]={1,2,3,4,};
  int markerstyle[samples]={21,22,23,24};
  int widthline[samples]={2,2,2,2};
    
  double nbins[nCases]={2000,2000};
  double lowerrangex[nCases]={0.,0.};
  double upperrangex[nCases]={1.0,1.0};
  double lowerrangey[nCases]={0.,0.};
  double upperrangey[nCases]={4,4};

  TString string_xaxis[nCases]={"#Delta (R)","#Delta (R)"};
  TString string_yaxis[nCases]={"fraction of events/no HLT p_{T}>4","fraction of events/no HLT p_{T}>20"};
*/