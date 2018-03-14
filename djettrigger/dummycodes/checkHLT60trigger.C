#include "../triggertables.h"

void checkHLT60trigger(int option=1){

  TString namefiles="/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080.root";
  TString nametree="djt";
  TString nametreeHLT="hlt";
  TString namevariableleading="jetpt_akpu3pf[0]";

  TFile *finput=new TFile(namefiles,"read"); 
  TTree*ttemp=(TTree*)finput->Get(nametree.Data());
  TTree*ttempHLT=(TTree*)finput->Get(nametreeHLT.Data());
  ttemp->AddFriend(ttempHLT);
  
  
  TH1F*hnum=new TH1F("hnum","hnum",300,0,300);
  TH1F*hden=new TH1F("hden","hden",300,0,300);
  
  
  TString presel1="abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>40&&HLT_HIPuAK4CaloJet40_Eta5p1_v1&&HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl==1&&L1_SingleS1Jet28_BptxAND_Prescl==1";
  TString sel1=presel1+"&&HLT_HIPuAK4CaloJet60_Eta5p1_v1==1";
  
  if(option==0){// simple turn on curve efficiency
  ttemp->Draw("jetpt_akpu3pf[0]>>hden",TCut(presel1.Data()));
  ttemp->Draw("jetpt_akpu3pf[0]>>hnum",TCut(sel1.Data()));
  }
  initialiseWeights();
  if(option==1){// simple turn on curve efficiency
  cout<<expmyweightL1final[1][1]<<endl;
  cout<<expmyweightHLTfinal[1][1]<<endl;
  ttemp->Draw("jetpt_akpu3pf[0]>>hden",TCut(presel1.Data()));
  ttemp->Draw("jetpt_akpu3pf[0]>>hnum",TCut(sel1.Data())*TCut(expmyweightL1final[1][1])*TCut(expmyweightHLTfinal[1][1]));
  }
  
  
    if(option==2){// simple turn on curve efficiency
  ttemp->Draw("jetpt_akpu3pf[0]>>hden",TCut(presel1.Data()));
  ttemp->Draw("jetpt_akpu3pf[0]>>hnum",TCut(sel1.Data())*TCut("3"));
  }

  TH1F*hRatio60Over40=(TH1F*)hnum->Clone("hRatio60Over40");
  hRatio60Over40->SetName("hRatio60Over40");
  hRatio60Over40->Divide(hden);
  hRatio60Over40->Draw();
}

