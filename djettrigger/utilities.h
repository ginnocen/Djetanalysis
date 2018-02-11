  const int samples=4; 
  const int nCases=2;

  TString namefiles[samples]={"rootfiles/xsec_Djet_pp_data_RecoD_RecoJet_jetpt_40p0_jeteta_0p3_1p6_HLTJet40_woScale_woSmear.root","rootfiles/xsec_Djet_pp_data_RecoD_RecoJet_jetpt_40p0_jeteta_0p3_1p6_HLTJet60_woScale_woSmear.root","rootfiles/xsec_Djet_pp_data_RecoD_RecoJet_jetpt_40p0_jeteta_0p3_1p6_HLTJet40Jet60_woScale_woSmear.root","rootfiles/xsec_Djet_pp_data_RecoD_RecoJet_jetpt_40p0_jeteta_0p3_1p6_noHLT_woScale_woSmear.root"};
  TString labelsamples[samples]={"Jet40","Jet60","Jet40AND60","NoSelection"};  
  
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
