#include "../triggertables.h"
#include "../utilitiescorrectedspectrum.h"
#include "../../includes/xjjrootuti.h"

void checktrigger(){

  TString presel = "abs(jeteta_akpu3pf[0])<1.6&&jetpt_akpu3pf[0]>%d&&%s%d_Eta5p1_v1&&%s%d_Eta5p1_v1_Prescl==1&&L1_%s%d_BptxAND_Prescl==1";
  TString sel = "&&%s%d_Eta5p1_v1==1";
  Int_t L1thresholds[samples][ntriggers] = {{28,40,48,52},{-1,28,44,56}};
  TString HLTnames[samples][ntriggers] = {{"fileno==0&&HLT_AK4PFJet","fileno==0&&HLT_AK4PFJet","fileno==1&&HLT_AK4PFJet","fileno==1&&HLT_AK4PFJet"},{"HLT_HIPuAK4CaloJet","HLT_HIPuAK4CaloJet","HLT_HIPuAK4CaloJet","HLT_HIPuAK4CaloJet"}};
  TString L1addl[samples][ntriggers] = {{"SingleJet","SingleJet","SingleJet","SingleJet"},{"","SingleS1Jet","SingleJet","SingleS1Jet"}};
  Int_t HLTthresholds[samples][ntriggers] = {{40,60,80,100},{40,60,80,100}};
  TH2F* hempty = new TH2F("hempty",";leading p_{t};Ratio",150,0,150,150,0,2);
  xjjroot::setgstyle();
  xjjroot::sethempty(hempty,0,0);
  initialiseWeights();
  TCanvas* c[samples];
  TLegend* l[samples];
  for(int i=0;i<samples;i++)
  {
    c[i] = new TCanvas(labelsamples[i].Data(),labelsamples[i].Data(),800,800); 
    hempty->Draw();
    l[i] = new TLegend(0.75,0.75,0.9,0.9);
    for(int j=1;j<ntriggers;j++) // starting at 1 on purpose: 60/40, 80/60, 100/80, etc.
    {
      if(plotratio[i][j]==0 || plotratio[i][j-1]==0) continue;
      std::cout << i << " " << j << std::endl;

      TFile *finput=new TFile(namefiles[i],"read"); 
      TTree*ttemp=(TTree*)finput->Get(nametree[i].Data());
      TTree*ttempHLT=(TTree*)finput->Get(nametreeHLT[i].Data());
      ttemp->AddFriend(ttempHLT);
      
      TH1F*hnum=new TH1F("hnum","hnum",300,0,300);
      TH1F*hden=new TH1F("hden","hden",300,0,300);
      
      TString presel1= Form(presel.Data(),HLTthresholds[i][j],HLTnames[i][j-1].Data(),HLTthresholds[i][j-1],HLTnames[i][j].Data(),HLTthresholds[i][j],L1addl[i][j].Data(),L1thresholds[i][j]);
      //std::cout << presel1 << std::endl;
      TString addl = Form(sel.Data(),HLTnames[i][j].Data(),HLTthresholds[i][j]);
      TString sel1 = presel1+addl;
      std::cout << "strings" << std::endl;
      cout<<expmyweightL1final[i][j]<<endl;
      cout<<expmyweightHLTfinal[i][j]<<endl;
      ttemp->Draw("jetpt_akpu3pf[0]>>hden",TCut(presel1.Data()),"goff");
      ttemp->Draw("jetpt_akpu3pf[0]>>hnum",TCut(sel1.Data())*TCut(expmyweightL1final[i][j])*TCut(expmyweightHLTfinal[i][j]),"goff");

      c[i]->cd();
      TH1F*hRatio=(TH1F*)hnum->Clone("hRatio");
      hRatio->SetName("hRatio");
      hnum->Sumw2();
      hden->Sumw2();
      hRatio->Divide(hden);
      xjjroot::setthgrstyle(hRatio,cols[j],styles[j],1.2,cols[j],styles[j],1,-1,-1,-1);
      hRatio->Draw("EP same");
      l[i]->AddEntry(hRatio,Form("HLT%d/HLT%d",HLTthresholds[i][j],HLTthresholds[i][j-1]),"lp");
    }
    l[i]->Draw();
    c[i]->SaveAs(Form("HLTRatio%s.pdf",labelsamples[i].Data()));
  }
}