void check(int option){

  TString namefilesMB="/mnt/hadoop/cms/store/user/tatar/HIMinimumBias2/HIRun2015-PromptReco-v1-Run263233-263284-FOREST/0.root";
  //TString namefilesMB="/mnt/hadoop/cms/store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root";
  TString nametreeMB="akPu3PFJetAnalyzer/t";
  TString nametreeHLTMB="hltanalysis/HltTree";
  TString nametreeSkimMB="skimanalysis/HltTree";
  TString nametreeEvtMB="hiEvtAnalyzer/HiTree";
  TString namevariableMB="jtpt";

  TFile *finput=new TFile(namefilesMB,"read"); 
  TTree*ttemp=(TTree*)finput->Get(nametreeMB.Data());
  TTree*ttempHLT=(TTree*)finput->Get(nametreeHLTMB.Data());
  TTree*ttempSkim=(TTree*)finput->Get(nametreeSkimMB.Data());
  TTree*ttempEvt=(TTree*)finput->Get(nametreeEvtMB.Data());
		
  ttemp->AddFriend(ttempHLT);
  ttemp->AddFriend(ttempSkim);
  ttemp->AddFriend(ttempEvt);

  TH1F*hempty=new TH1F("hnum","hnum",300,0,300);
  TH1F*hnum=new TH1F("hnum","hnum",300,0,300);
  TH1F*hden=new TH1F("hden","hden",300,0,300);
  TH1F*hmeanL1=new TH1F("hmeanL1","hmeanL1",300,0,300);
  TH1F*hmeanHLT=new TH1F("hmeanHLT","hmeanHLT",300,0,300);
  
  if(option==0){// simple turn on curve efficiency
  ttemp->Draw("jtpt[0]>>hden","abs(jteta[0])<1.6");
  ttemp->Draw("jtpt[0]>>hnum","L1_SingleJet44_BptxAND==1&&abs(jteta[0])<1.6");
  }


  if(option==1){// use weights
  ttemp->Draw("jtpt[0]>>hden","L1_SingleS1Jet28_BptxAND_Prescl==1&&abs(jteta[0])<1.6");
  ttemp->Draw("jtpt[0]>>hnum",TCut("L1_SingleS1Jet28_BptxAND_Prescl==1&&abs(jteta[0])<1.6&&HLT_HIPuAK4CaloJet60_Eta5p1_v1==1")*TCut("HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl"));
  }
  
  
  if(option==2){// use average
  ttemp->Draw("jtpt[0]>>hden","L1_SingleS1Jet28_BptxAND_Prescl==1&&L1_SingleS1Jet28_BptxAND==1&&abs(jteta[0])<1.6");
  ttemp->Draw("jtpt[0]>>hnum","L1_SingleS1Jet28_BptxAND_Prescl==1&&L1_SingleS1Jet28_BptxAND==1&&abs(jteta[0])<1.6&&HLT_HIPuAK4CaloJet60_Eta5p1_v1==1");
  ttemp->Draw("HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl>>hmeanHLT");
  hnum->Scale(hmeanHLT->GetMean());

  TGraphAsymmErrors* gHLTefficiency = new TGraphAsymmErrors;
  for (int i=1;i<=hnum->GetNbinsX();i++){
    double numv=hnum->GetBinContent(i);
    double denv=hden->GetBinContent(i);
    double enumv=hnum->GetBinError(i);
    double edenv=hden->GetBinError(i);
      if(numv>denv) { 
        hnum->SetBinContent(i,denv);
        hnum->SetBinError(i,edenv);
      }
   }
  gHLTefficiency->Divide(hnum,hden);
  hempty->Draw();
  gHLTefficiency->Draw("same");
  }
  

  if(option==3){// use average
  
    ttemp->Draw("jtpt[0]>>hden","L1_MinimumBiasHF2_AND==1&&abs(jteta[0])<1.6");
    ttemp->Draw("jtpt[0]>>hnum",TCut("L1_MinimumBiasHF2_AND==1&&abs(jteta[0])<1.6&&HLT_HIPuAK4CaloJet40_Eta5p1_v2==1"));
    ttemp->Draw("HLT_HIPuAK4CaloJet40_Eta5p1_v2_Prescl>>hmeanHLT");
    hnum->Scale(hmeanHLT->GetMean());

    TGraphAsymmErrors* gHLTefficiency = new TGraphAsymmErrors;
    for (int i=1;i<=hnum->GetNbinsX();i++){
    double numv=hnum->GetBinContent(i);
    double denv=hden->GetBinContent(i);
    double enumv=hnum->GetBinError(i);
    double edenv=hden->GetBinError(i);
      if(numv>denv) { 
        hnum->SetBinContent(i,denv);
        hnum->SetBinError(i,edenv);
      }
   }
    gHLTefficiency->BayesDivide(hnum,hden);
    hempty->Draw();
   gHLTefficiency->Draw("same");

  }


  if(option==4){// check
   //ttemp->Draw("1","HLT_HIPuAK4CaloJet40_Eta5p1_v1&&L1_MinimumBiasHF2_AND==1");
   ttemp->Draw("1","L1_MinimumBiasHF2_AND==1");
   ttemp->Draw("1","L1_MinimumBiasHF1_AND==1");
  }



}

