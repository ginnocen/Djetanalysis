#include <TStyle.h>
#include <iostream>
#include <iostream>
  
  const int samples=2; 
  const int nCases=5;
  const int ntriggers=4;
  
  const int nbinsTurnOn=60;
  double bondaries_nbinsTurnOn[nbinsTurnOn+1];
  
  TString labelsamples[samples]={"pp","PbPb"};  
  TString nametriggerselectiontagtriggers[samples][ntriggers]={{"ppHLT40","ppHLT60","ppHLT80","ppHLT100"},{"PbPbHLT40","PbPbHLT60","PbPbHLT80","PbPbHLT100"}};  
  TString nameL1trigger[samples][ntriggers]={{"L1_SingleJet28_BptxAND","L1_SingleJet40_BptxAND","L1_SingleJet48_BptxAND","L1_SingleJet52_BptxAND"},{"L1_MinimumBiasHF2_AND","L1_SingleS1Jet28_BptxAND","L1_SingleJet44_BptxAND","L1_SingleS1Jet56_BptxAND"}};


  //MB samples
  TString namefilesMB[samples]={"/mnt/hadoop/cms/store/user/tatar/MinimumBias6/Run2015E_PromptReco_v1_Run261553_262328_FOREST/0_20170805.root","/mnt/hadoop/cms/store/user/cmcginn/HIMinimumBias2/HIMinimumBias2_ForRandomConeTest_20170307_400Lumi/170307_204032/merged/HiForestAOD_HIMinimumBias2_ForRandomConeTest_20170307_400Lumi_MERGED.root"}; 
  TString eventjetselection[samples]={"(pPAprimaryVertexFilter&&pBeamScrapingFilter&&fabs(vz)<15&&abs(jteta)<2.0)","(pcollisionEventSelection&&HBHENoiseFilterResultRun2Loose&&fabs(vz)<15&&abs(jteta)<2.0)"};
  TString MBselection[samples]={"(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)","(HLT_HIL1MinimumBiasHF1AND_v1)"};  
  TString nametreeMB[samples]={"ak3PFJetAnalyzer/t","akCs3PFJetAnalyzer/t"};
  TString nametreeHLTMB[samples]={"hltanalysis/HltTree","hltanalysis/HltTree"};
  TString nametreeSkimMB[samples]={"skimanalysis/HltTree","skimanalysis/HltTree"};
  TString nametreeEvtMB[samples]={"hiEvtAnalyzer/HiTree","hiEvtAnalyzer/HiTree"};
  TString namevariableMB[samples]={"jtpt","jtpt"};
  TString nametriggerMB[samples][ntriggers]={{"HLT_AK4PFJet40_Eta5p1_v1","HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet80_Eta5p1_v1","HLT_AK4PFJet100_Eta5p1_v1"},{"HLT_HIPuAK4CaloJet40_Eta5p1_v2","HLT_HIPuAK4CaloJet60_Eta5p1_v1","HLT_HIPuAK4CaloJet80_Eta5p1_v1","HLT_HIPuAK4CaloJet100_Eta5p1_v1"}};
  TString nameL1triggerMB[samples][ntriggers]={{"L1_SingleJet28_BptxAND==1","L1_SingleJet40_BptxAND==1","L1_SingleJet48_BptxAND==1","L1_SingleJet52_BptxAND==1"},{"L1_MinimumBiasHF1_AND==1","L1_SingleS1Jet28_BptxAND==1","L1_SingleJet44_BptxAND==1","L1_SingleS1Jet56_BptxAND==1"}};
  TString prescaleL1MB[samples][ntriggers]={{"(L1_SingleJet28_BptxAND_Prescl==1)","(L1_SingleJet40_BptxAND_Prescl==1)","(L1_SingleJet48_BptxAND_Prescl==1)","(L1_SingleJet52_BptxAND_Prescl==1)"},{"1","(L1_SingleS1Jet28_BptxAND_Prescl==1)","(L1_SingleJet44_BptxAND_Prescl==1)","(L1_SingleS1Jet56_BptxAND_Prescl==1)"}};
  TString prescaleselHLTMB[samples][ntriggers]={{"(HLT_AK4PFJet40_Eta5p1_v1_Prescl==1)","(HLT_AK4PFJet60_Eta5p1_v1_Prescl==1)","(HLT_AK4PFJet80_Eta5p1_v1_Prescl==1)","(HLT_AK4PFJet100_Eta5p1_v1_Prescl==1)"},{"HLT_HIPuAK4CaloJet40_Eta5p1_v1_Prescl==1","HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl==1","HLT_HIPuAK4CaloJet80_Eta5p1_v1_Prescl==1","HLT_HIPuAK4CaloJet100_Eta5p1_v1_Prescl==1"}};
  TString prescalecorrHLTMB[samples][ntriggers]={{"(1)","(1)","(1)","(1)"},{"(1)","(1)","(1)","(1)"}};

   double a0L1[samples][ntriggers]={{.0741,.0557,.0474,.05},{-0.921,.0114,.0105,.01}};
  double a1L1[samples][ntriggers]={{-2.061,-2.062,-2.022,-2.},{-240.52,0.158,-1.349,-2.}};
  double a2L1[samples][ntriggers]={{-0.840,-1.226,-1.364,-1.},{712.37,-3,-1.481,-1.}};
  double a3L1[samples][ntriggers]={{71.12,259.81,542.30,300.},{3.362e+06,1532,1731,1600.}};

  double a0HLT[samples][ntriggers]={{.145,.0572,.0714,.05},{.01,.0105,.0157,.01}};
  double a1HLT[samples][ntriggers]={{-211.,-3.263,-5.767,-4.},{1.,-1.678,-2.199,-2.}};
  double a2HLT[samples][ntriggers]={{206.2,-3.472,3.264,1.},{.01,-1.069,-3.125,-1.}};
  double a3HLT[samples][ntriggers]={{3.836e+05,1201,569.2,700.},{100,642.8,725.8,700.}};


  //nTriggers  
  
  TString namehtempMuF[samples][ntriggers];  
  TString namehL1efficiencyden[samples][ntriggers];  
  TString namehL1efficiencynum[samples][ntriggers]; 
  TString namehHLTefficiencyden[samples][ntriggers];  
  TString namehHLTefficiencynum[samples][ntriggers];  
  
  TString namegL1efficiency[samples][ntriggers];  
  TString namegHLTefficiency[samples][ntriggers];  
  TString namehHLTefficiency[samples][ntriggers];  
  
  TString namehjetptspectrumpertrigger[samples][ntriggers];  
  TString namehjetleadingptspectrumpertrigger[samples][ntriggers];  
  TString namehjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
  TString namehjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];  
  
  int coloursTurnOn[ntriggers]={1,2,4,3};
  int markerstyleTurnOn[ntriggers]={21,22,22,20};
  int widthlineTurnOn[ntriggers]={2,2,2,2};

  double nbins[samples]={2000,2000};
  double lowerrangex[samples]={20.,20.};
  double upperrangex[samples]={200.,200.};
  double lowerrangey[samples]={1.,1.};
  double upperrangey[samples]={1e9,1e9};

  TString string_xaxis[samples]={"leading jet offline p_{T}","leading jet offline p_{T}"};
  TString string_yaxis[samples]={"entries","entries"};
  
  double lowerrangeyTurnOn[samples]={0.0,0.0};
  double upperrangeyTurnOn[samples]={2,2};
  TString string_yaxisTurnOnL1[samples]={"L1 efficiency","L1 efficiency"};
  TString string_yaxisTurnOnHLT[samples]={"HLT efficiency","HLT efficiency"};
  
  TString preselectionL1[samples][ntriggers];
  TString preselectionHLT[samples][ntriggers];
  TString selectionL1[samples][ntriggers];
  TString selectionHLT[samples][ntriggers];
  TString selectionanalysis[samples][ntriggers];
  
  TString functionalFormTurnOn= "0.5*TMath::Erf(x*[0]+[1]+TMath::Exp((-x^2+[1])/[3])*[2])+0.5";

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
    for (int i=1;i<=25;i++) {bondaries_nbinsTurnOn[i]=bondaries_nbinsTurnOn[i-1]+2.;}
    for (int i=26;i<=50;i++) {bondaries_nbinsTurnOn[i]=bondaries_nbinsTurnOn[i-1]+4.;}
    for (int i=51;i<=60;i++) {bondaries_nbinsTurnOn[i]=bondaries_nbinsTurnOn[i-1]+10.;}
    
	for (int index=0;index<samples;index++){
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		
		   namehL1efficiencyden[index][indextriggers]="hL1efficiencyden"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehtempMuF[index][indextriggers]="hMuonFraction"+nametriggerselectiontagtriggers[index][indextriggers]+ labelsamples[index];
		   namehL1efficiencynum[index][indextriggers]="hL1efficiencynum"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehHLTefficiencyden[index][indextriggers]="hHLTefficiencyden"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehHLTefficiencynum[index][indextriggers]="hHLTefficiencynum"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namegL1efficiency[index][indextriggers]="gL1efficiency"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namegHLTefficiency[index][indextriggers]="gHLTefficiency"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
	
    }
  }

	for (int index=0;index<samples;index++){		
	  for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
	      preselectionL1[index][indextriggers]=eventjetselection[index]+"&&"+MBselection[index]+"&&"+prescaleL1MB[index][indextriggers];
		  selectionL1[index][indextriggers]=preselectionL1[index][indextriggers]+"&&"+nameL1triggerMB[index][indextriggers];
	      preselectionHLT[index][indextriggers]=eventjetselection[index]+"&&"+MBselection[index]+"&&"+prescaleL1MB[index][indextriggers]+"&&"+prescaleselHLTMB[index][indextriggers]+"&&"+nameL1triggerMB[index][indextriggers];
		  selectionHLT[index][indextriggers]=preselectionHLT[index][indextriggers]+"&&"+nametriggerMB[index][indextriggers];
        }
    }
}