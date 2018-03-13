#include <TStyle.h>
#include <iostream>
  
  const int samples=2; 
  const int ntriggers=4;
    
  TString labelsamples[samples]={"pp","PbPb"};  
  TString nametriggerselectiontagtriggers[samples][ntriggers]={{"ppHLT40","ppHLT60","ppHLT80","ppHLT100"},{"PbPbHLT40","PbPbHLT60","PbPbHLT80","PbPbHLT100"}};

  EColor cols[ntriggers] = {kBlack,kBlue,kRed,kGreen};
  int effcols[ntriggers] = {920,432,807,845};
  int styles[ntriggers] = {20,21,22,20};
  
  int plotturnon[samples][ntriggers]={{1,1,1,0},{1,1,1,0}};


    //Triggered samples
  TString namefiles[samples]={"/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/data/DjetFiles_20180214_pp_5TeV_HighPtLowerJetsHighPtJet80_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root","/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080.root"}; 
  //TString namefiles[samples]={"/mnt/hadoop/cms/store/user/jwang/Djetsgfal/DjetFiles_20180214_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614/skim_djet_HiForestAOD_1325.root","/mnt/hadoop/cms/store/user/jwang/Djetsgfal/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1_26March_20170326/skim_djet_HiForestAOD_1000.root"}; 

  TString nametree[samples]={"djt","djt"};
  TString nametreeHLT[samples]={"hlt","hlt"};
  TString namevariable[samples]={"jetpt_akpu3pf","jetpt_akpu3pf"};
  TString namevariableMB[samples]={"jetpt_akpu3pf[0]","jetpt_akpu3pf[0]"};

  
  TString stringweight="1./(0.5*TMath::Erf((jetpt_akpu3pf[0])*%f+%f+TMath::Exp((-(jetpt_akpu3pf[0])^2+%f)/(%f))*(%f))+0.5)";  //[0],[1],[1],[3],[2]
  TString etaselection="abs(jeteta_akpu3pf)<1.6";
  //TString nametrigger[samples][ntriggers]={{"fileno==0&&HLT_AK4PFJet40_Eta5p1_v1&&jetpt_akpu3pf>40","fileno==0&&HLT_AK4PFJet60_Eta5p1_v1&&jetpt_akpu3pf>60","fileno==1&&HLT_AK4PFJet80_Eta5p1_v1&&jetpt_akpu3pf>80","fileno==1&&HLT_AK4PFJet100_Eta5p1_v1&&jetpt_akpu3pf>100"},{"HLT_HIPuAK4CaloJet40_Eta5p1_v1&&jetpt_akpu3pf>40","HLT_HIPuAK4CaloJet60_Eta5p1_v1&&jetpt_akpu3pf>60","HLT_HIPuAK4CaloJet80_Eta5p1_v1&&jetpt_akpu3pf>80","HLT_HIPuAK4CaloJet100_Eta5p1_v1&&jetpt_akpu3pf>100"}};
  TString nametrigger[samples][ntriggers]={{"fileno==0&&HLT_AK4PFJet40_Eta5p1_v1&&jetpt_akpu3pf>40","fileno==0&&HLT_AK4PFJet60_Eta5p1_v1&&jetpt_akpu3pf>60","fileno==1&&HLT_AK4PFJet80_Eta5p1_v1&&jetpt_akpu3pf>80","fileno==1&&HLT_AK4PFJet100_Eta5p1_v1&&jetpt_akpu3pf>100"},{"HLT_HIPuAK4CaloJet40_Eta5p1_v1&&jetpt_akpu3pf>40","HLT_HIPuAK4CaloJet60_Eta5p1_v1&&jetpt_akpu3pf>60","HLT_HIPuAK4CaloJet80_Eta5p1_v1&&jetpt_akpu3pf>80","HLT_HIPuAK4CaloJet100_Eta5p1_v1&&jetpt_akpu3pf>100"}};
  TString triggerrangecorrectionsel[samples][ntriggers]={{"abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>40)","abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>60","abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>80","abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>100"},{"abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>40)","abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>60","abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>80","abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>100"}};
  
  TString namehjetptspectrumpertrigger[samples][ntriggers];  
  TString namehjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
  TString namehjetptspectrumpertriggerEffWeighted[samples][ntriggers]; 
  TString namehjetptspectrumpertriggerPresclCorrEffWeighted[samples][ntriggers];  
   
  TString namehjetleadingptspectrumpertrigger[samples][ntriggers];  
  TString namehjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];  
  TString namehjetleadingptspectrumpertriggerEffWeighted[samples][ntriggers];  
  TString namehjetleadingptspectrumpertriggerPresclCorrEffWeighted[samples][ntriggers];  
  

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
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		
		   namehjetptspectrumpertrigger[index][indextriggers]="hjetptspectrumpertrigger"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetptspectrumpertriggerPresclCorr[index][indextriggers]="hjetptspectrumpertriggerPresclCorr"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetptspectrumpertriggerEffWeighted[index][indextriggers]="hjetptspectrumpertriggerEffWeighted"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
       namehjetptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]="hjetptspectrumpertriggerPresclCorrEffWeighted"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];

		   namehjetleadingptspectrumpertrigger[index][indextriggers]="hjetleadingptspectrumpertrigger"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];	
		   namehjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]="hjetleadingptspectrumpertriggerPresclCorr"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
		   namehjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]="hjetleadingptspectrumpertriggerEffWeighted"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index];
       namehjetleadingptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]="hjetleadingptspectrumpertriggerPresclCorrEffWeighted"+nametriggerselectiontagtriggers[index][indextriggers]+labelsamples[index]; 
	
		   selectionanalysis[index][indextriggers]=nametrigger[index][indextriggers]+"&&"+etaselection;
		   selectionanalysisweightrange[index][indextriggers]=nametrigger[index][indextriggers]+"&&"+etaselection+"&&"+triggerrangecorrectionsel[index][indextriggers];
    }
  }
}
