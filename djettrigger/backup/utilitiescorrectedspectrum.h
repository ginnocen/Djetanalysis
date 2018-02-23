#include <TStyle.h>
#include <iostream>
  
  const int samples=2; 
  const int ntriggers=3;

  TString namegL1efficiency[samples][ntriggers];  
  TString namegHLTefficiency[samples][ntriggers];  
  TString namehHLTefficiency[samples][ntriggers];  

  TString stringweight="1./(0.5*TMath::Erf(Max$(jetptCorr_akpu3pf)*%f+%f+TMath::Exp((-Max$(jetptCorr_akpu3pf)^2+%f)/(%f))*(%f))+0.5)";  //[0],[1],[1],[3],[2]
  double thresholdslow[ntriggers]={40.,60.,80.};
  double thresholdshigh[ntriggers]={100.,120.,140.};
  TString labelsamples[samples]={"pp","PbPb"};  
  TString nametriggerselectiontagtriggers[samples][ntriggers]={{"ppHLT40","ppHLT60","ppHLT80"},{"PbPbHLT40","PbPbHLT60","PbPbHLT80"}};

    //Triggered samples
  TString namefiles[samples]={"/export/d00/scratch/jwang/Djets/data/DjetFiles_20180214_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root","/export/d00/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080.root"}; 
  TString nametree[samples]={"djt","djt"};
  TString nametreeHLT[samples]={"hlt","hlt"};
  TString namevariable[samples]={"jetptCorr_akpu3pf","jetptCorr_akpu3pf"};
  TString nametrigger[samples][ntriggers]={{"HLT_AK4PFJet40_Eta5p1_v1","HLT_AK4PFJet60_Eta5p1_v1","HLT_AK4PFJet80_Eta5p1_v1"},{"HLT_HIPuAK4CaloJet40_Eta5p1_v1","HLT_HIPuAK4CaloJet60_Eta5p1_v1","HLT_HIPuAK4CaloJet80_Eta5p1_v1"}};
  TString nameL1trigger[samples][ntriggers]={{"L1_SingleJet28_BptxAND","L1_SingleJet40_BptxAND","L1_SingleJet48_BptxAND"},{"L1_MinimumBiasHF2_AND","L1_SingleS1Jet28_BptxAND","L1_SingleJet44_BptxAND"}};

  TString namehjetptspectrumpertrigger[samples][ntriggers];  
  TString namehjetleadingptspectrumpertrigger[samples][ntriggers];  
  TString namehjetptspectrumpertriggerEffWeighted[samples][ntriggers];  
  TString namehjetleadingptspectrumpertriggerEffWeighted[samples][ntriggers];  
  TString namehjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
  TString namehjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];  
  TString namehjetptspectrumpertriggerPresclEffCorr[samples][ntriggers];  
  TString namehjetleadingptspectrumpertriggerPresclEffCorr[samples][ntriggers];  

  TString namehjetptspectrumTotPresclCorr[samples];  
  TString namehjetleadingptspectrumTotPresclCorr[samples];  

  double nbins[samples]={2000,2000};
  double lowerrangex[samples]={20.,20.};
  double upperrangex[samples]={200.,200.};
  double lowerrangey[samples]={1.,1.};
  double upperrangey[samples]={1e9,1e9};

  TString string_xaxis[samples]={"leading jet offline p_{T}","leading jet offline p_{T}"};
  TString string_yaxis[samples]={"entries","entries"};
  
  TString selectionanalysis[samples][ntriggers];
  TString selectionanalysisweightrange[samples][ntriggers];

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
        
    
	for (int index=0;index<samples;index++){
	
		   namehjetptspectrumTotPresclCorr[index]="hjetptspectrumTotPresclCorr"+labelsamples[index];
		   namehjetleadingptspectrumTotPresclCorr[index]="hjetleadingptspectrumTotPresclCorr"+labelsamples[index];

		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		
		   namehjetptspectrumpertriggerPresclEffCorr[index][indextriggers]="hjetptspectrumpertriggerPresclEffCorr"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetleadingptspectrumpertriggerPresclEffCorr[index][indextriggers]="hjetleadingptspectrumpertriggerPresclEffCorr"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetptspectrumpertriggerPresclCorr[index][indextriggers]="hjetptspectrumpertriggerPresclCorr"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]="hjetleadingptspectrumpertriggerPresclCorr"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetptspectrumpertrigger[index][indextriggers]="hjetptspectrumpertrigger"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetleadingptspectrumpertrigger[index][indextriggers]="hjetleadingptspectrumpertrigger"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];	
		   namehjetptspectrumpertriggerEffWeighted[index][indextriggers]="hjetptspectrumpertriggerEffWeighted"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]="hjetleadingptspectrumpertriggerEffWeighted"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];	
		   selectionanalysis[index][indextriggers]=nametrigger[index][indextriggers]+"&&abs(jeteta_akpu3pf)<2.0";
		   selectionanalysisweightrange[index][indextriggers]=selectionanalysisweightrange[index][indextriggers]+Form("(Max$(%s)>%f&&Max$(%s)<%f)",namevariable[index].Data(),thresholdslow[indextriggers],namevariable[index].Data(),thresholdshigh[indextriggers]);
    }
  }
}