  #include <TStyle.h>

  
  const int samples=2; 
  const int nCases=5;
  const int ntriggers=2;
  
  const int nbinsTurnOn=60;
  float bondaries_nbinsTurnOn[nbinsTurnOn];
  
  TString labelsamples[samples]={"pp","PbPb"};  

    //Triggered samples
  TString namefiles[samples]={"/export/d00/scratch/jwang/Djets/data/DjetFiles_20171120_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root","/export/d00/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080.root"}; 
  TString nametree[samples]={"djt","djt"};
  TString nametreeHLT[samples]={"hlt","hlt"};
  TString namevariable[samples]={"jetptCorr_akpu3pf","jetptCorr_akpu3pf"};
  
  //MB samples
  TString namefilesMB[samples]={"/mnt/hadoop/cms/store/user/tatar/MinimumBias6/Run2015E_PromptReco_v1_Run261553_262328_FOREST/0_20170805.root","/mnt/hadoop/cms/store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/0.root"}; 
  TString eventjetselection[samples]={"(pPAprimaryVertexFilter&&pBeamScrapingFilter&&fabs(vz)<15&&abs(jteta)<2.0)","(pcollisionEventSelection&&HBHENoiseFilterResultRun2Loose&&fabs(vz)<15&&abs(jteta)<2.0)"};
  TString MBselection[samples]={"(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)","(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"};  
  TString nametriggerMB[samples][ntriggers]={{"HLT_AK4PFJet40_Eta5p1_v1","HLT_AK4PFJet60_Eta5p1_v1"},{"(HLT_HIPuAK4CaloJet40_Eta5p1_v1||HLT_HIPuAK4CaloJet40_Eta5p1_v2)","HLT_HIPuAK4CaloJet60_Eta5p1_v1"}};
  TString nameL1triggerMB[samples][ntriggers]={{"L1_SingleJet28_BptxAND","L1_SingleJet40_BptxAND"},{"L1_MinimumBiasHF2_AND","L1_SingleS1Jet28_BptxAND"}};
  TString nametreeMB[samples]={"ak3PFJetAnalyzer/t","akPu3PFJetAnalyzer/t"};
  TString nametreeHLTMB[samples]={"hltanalysis/HltTree","hltanalysis/HltTree"};
  TString nametreeSkimMB[samples]={"skimanalysis/HltTree","skimanalysis/HltTree"};
  TString nametreeEvtMB[samples]={"hiEvtAnalyzer/HiTree","hiEvtAnalyzer/HiTree"};
  TString namevariableMB[samples]={"jtpt","jtpt"};
  
  //nTriggers  

  TString nametrigger[samples][ntriggers]={{"HLT_AK4PFJet40_Eta5p1_v1","HLT_AK4PFJet60_Eta5p1_v1"},{"HLT_HIPuAK4CaloJet40_Eta5p1_v1","HLT_HIPuAK4CaloJet60_Eta5p1_v1"}};
  TString nameL1trigger[samples][ntriggers]={{"L1_SingleJet28_BptxAND","L1_SingleJet40_BptxAND"},{"L1_MinimumBiasHF2_AND","L1_SingleS1Jet28_BptxAND"}};
  
  TString namehL1efficiencyden[samples];  
  TString namehL1efficiencynum[samples][ntriggers];  
  TString namehHLTefficiencyden[samples][ntriggers];  
  TString namehHLTefficiencynum[samples][ntriggers];  
  
  TString namegL1efficiency[samples][ntriggers];  
  TString namegHLTefficiency[samples][ntriggers];  
  TString namegTotefficiency[samples][ntriggers];  

  int coloursTurnOn[ntriggers]={1,2};
  int markerstyleTurnOn[ntriggers]={21,22};
  int widthlineTurnOn[ntriggers]={2,2};

  double nbins[samples]={2000,2000};
  double lowerrangex[samples]={20.,20.};
  double upperrangex[samples]={1000.,1000.};
  double lowerrangey[samples]={1.,1.};
  double upperrangey[samples]={1e9,1e9};

  TString string_xaxis[samples]={"jet offline p_{T}","jet offline p_{T}"};
  TString string_yaxis[samples]={"entries","entries"};
  
  double lowerrangeyTurnOn[samples]={0.0001,0.0001};
  double upperrangeyTurnOn[samples]={2,2};
  TString string_yaxisTurnOnL1[samples]={"L1 efficiency","L1 efficiency"};
  TString string_yaxisTurnOnHLT[samples]={"HLT efficiency","HLT efficiency"};
  TString string_yaxisTurnOnTot[samples]={"Total efficiency","Total efficiency"};
  
  
  TString preselection[samples];
  TString L1selection[samples][ntriggers];
  TString HLTselection[samples][ntriggers];


  //nCases
  TString nametriggerselection[samples][nCases]={{"HLT_AK4PFJet40_Eta5p1_v1&&!HLT_AK4PFJet60_Eta5p1_v1","!HLT_AK4PFJet40_Eta5p1_v1&&HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet40_Eta5p1_v1&&HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet40_Eta5p1_v1||HLT_AK4PFJet60_Eta5p1_v1","1"},{"HLT_HIPuAK4CaloJet40_Eta5p1_v1&&!HLT_HIPuAK4CaloJet60_Eta5p1_v1", "!HLT_HIPuAK4CaloJet40_Eta5p1_v1&&HLT_HIPuAK4CaloJet60_Eta5p1_v1","HLT_HIPuAK4CaloJet40_Eta5p1_v1&&HLT_HIPuAK4CaloJet60_Eta5p1_v1","HLT_HIPuAK4CaloJet40_Eta5p1_v1||HLT_HIPuAK4CaloJet60_Eta5p1_v1","1"}};
  TString nametriggerselectiontag[samples][nCases]={{"HLT40only","HLT60only","HLT40_AND_HLT60","HLT40_OR_HLT60","All"},{"HLT40only","HLT60only","HLT40_AND_HLT60","HLT40_OR_HLT60","All"}};
  TString namehjetptspectrum[samples][nCases];  
  TString namehjetleadingptspectrum[samples][nCases];  
  
  int colours[nCases]={1,2,3,4,7};
  int markerstyle[nCases]={21,22,23,24,24};
  int widthline[nCases]={2,2,2,2,2};


void initialise(){


	gStyle->SetTextSize(0.05);
	gStyle->SetTextFont(42);
	gStyle->SetPadRightMargin(0.043);
	gStyle->SetPadLeftMargin(0.18);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.145);
	gStyle->SetTitleX(.0f);
	gStyle->SetTitleY(.0f);
	gStyle->SetOptStat(0);
	gStyle->SetMarkerStyle(20);
	gStyle->SetMarkerSize(0.8);
    
    
    bondaries_nbinsTurnOn[0]=0.;
    for (int i=1;i<=25;i++) bondaries_nbinsTurnOn[i]=bondaries_nbinsTurnOn[i-1]+2.;
    for (int i=26;i<=50;i++) bondaries_nbinsTurnOn[i]=bondaries_nbinsTurnOn[i-1]+4.;
    for (int i=51;i<=60;i++) bondaries_nbinsTurnOn[i]=bondaries_nbinsTurnOn[i-1]+10.;
    
    
    
	for (int index=0;index<samples;index++){
		namehL1efficiencyden[index]="hL1efficiencyden"+labelsamples[index];

		for (int indexcases=0;indexcases<nCases;indexcases++){ 
		   namehjetptspectrum[index][indexcases]="hjetptspectrum"+nametriggerselectiontag[index][indexcases]+labelsamples[index];
		   namehjetleadingptspectrum[index][indexcases]="hjetleadingptspectrum"+nametriggerselectiontag[index][indexcases]+labelsamples[index];
        }
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		   namehL1efficiencynum[index][indextriggers]="hL1efficiencynum"+nametriggerselectiontag[index][indextriggers]+labelsamples[index];
		   namehHLTefficiencyden[index][indextriggers]="hHLTefficiencyden"+nametriggerselectiontag[index][indextriggers]+labelsamples[index];
		   namehHLTefficiencynum[index][indextriggers]="hHLTefficiencynum"+nametriggerselectiontag[index][indextriggers]+labelsamples[index];
		   namegL1efficiency[index][indextriggers]="gL1efficiency"+nametriggerselectiontag[index][indextriggers]+labelsamples[index];
		   namegHLTefficiency[index][indextriggers]="gHLTefficiency"+nametriggerselectiontag[index][indextriggers]+labelsamples[index];
		   namegTotefficiency[index][indextriggers]="gTotefficiency"+nametriggerselectiontag[index][indextriggers]+labelsamples[index];
    }
  }
  
	for (int index=0;index<samples;index++){
		preselection[index]=Form("%s&&%s",eventjetselection[index].Data(),MBselection[index].Data());
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		  L1selection[index][indextriggers]=Form("%s&&%s",preselection[index].Data(),nameL1triggerMB[index][indextriggers].Data());
		  HLTselection[index][indextriggers]=Form("%s&&%s",L1selection[index][indextriggers].Data(),nametriggerMB[index][indextriggers].Data());
        }
    }
}