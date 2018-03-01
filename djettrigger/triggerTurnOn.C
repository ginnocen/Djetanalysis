#include "Plotting.cpp"
#include <vector>
#include "utilitiesturnonstudy.h"
#include <TROOT.h>
#include <TStyle.h>
#include <iostream>
#include <iostream>
#include <TF1.h>
#include <TH1F.h>
#include <TTree.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TCut.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>


void triggerTurnOn(TString suffixfile="SelectionOnL1HLTprescale",int doPP=1, int doPbPb=1, int do40=1,int do60=1,int do80=1,int do100=1){
     
    initialise();
	TFile *finput[samples];

   TH1F *hL1efficiencyden[samples][ntriggers];  
   TH1F *hL1efficiencynum[samples][ntriggers];  
   TH1F *hHLTefficiencyden[samples][ntriggers];  
   TH1F *hHLTefficiencynum[samples][ntriggers];  
   TGraphAsymmErrors *gL1efficiency[samples][ntriggers];  
    TGraphAsymmErrors *gHLTefficiency[samples][ntriggers];  

	for (int index=0;index<samples;index++){
		finput[index]=new TFile(namefilesMB[index].Data(),"read"); 
		TH1F*htemp=new TH1F("htemp","htemp",nbinsTurnOn,bondaries_nbinsTurnOn);
		TH1F*hprescaleHLT=new TH1F("hprescaleHLT","hprescaleHLT",100,0,1000);
		htemp->Sumw2();
		TTree*ttemp=(TTree*)finput[index]->Get(nametreeMB[index].Data());
		TTree*ttempHLT=(TTree*)finput[index]->Get(nametreeHLTMB[index].Data());
		TTree*ttempSkim=(TTree*)finput[index]->Get(nametreeSkimMB[index].Data());
		TTree*ttempEvt=(TTree*)finput[index]->Get(nametreeEvtMB[index].Data());
		
		ttemp->AddFriend(ttempHLT);
		ttemp->AddFriend(ttempSkim);
		ttemp->AddFriend(ttempEvt);
		
		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;

		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
					  
	   	  if (indextriggers==0 && do40==0) continue;
		  if (indextriggers==1 && do60==0) continue;
		  if (indextriggers==2 && do80==0) continue;
		  if (indextriggers==3 && do100==0) continue;
		  
		  std::cout<<"sample="<<index<<std::endl;
		  std::cout<<"indextriggers="<<indextriggers<<std::endl;

		  ttemp->Draw(Form("(%s)>>htemp",namevariableMB[index].Data()),preselectionL1[index][indextriggers].Data());
		  hL1efficiencyden[index][indextriggers]=(TH1F*)htemp->Clone();
		  hL1efficiencyden[index][indextriggers]->SetName(namehL1efficiencyden[index][indextriggers].Data());
		  hL1efficiencyden[index][indextriggers]->Sumw2();

	
		  std::cout<<"step1="<<std::endl;

		  ttemp->Draw(Form("(%s)>>htemp",namevariableMB[index].Data()),selectionL1[index][indextriggers]);
		  hL1efficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hL1efficiencynum[index][indextriggers]->SetName(namehL1efficiencynum[index][indextriggers].Data());
		  hL1efficiencynum[index][indextriggers]->Sumw2();

		  std::cout<<"step2="<<std::endl;

          gL1efficiency[index][indextriggers] = new TGraphAsymmErrors;
          gL1efficiency[index][indextriggers]->BayesDivide(hL1efficiencynum[index][indextriggers],hL1efficiencyden[index][indextriggers]);
          gL1efficiency[index][indextriggers]->SetName(namegL1efficiency[index][indextriggers].Data());

		  std::cout<<"step3="<<std::endl;

		  ttemp->Draw(Form("(%s)>>htemp",namevariableMB[index].Data()),preselectionHLT[index][indextriggers].Data());
		  hHLTefficiencyden[index][indextriggers]=(TH1F*)htemp->Clone();
		  hHLTefficiencyden[index][indextriggers]->SetName(namehHLTefficiencyden[index][indextriggers].Data());
		  hHLTefficiencyden[index][indextriggers]->Sumw2();

		  std::cout<<"step4="<<std::endl;

		  ttemp->Draw(Form("(%s)>>htemp",namevariableMB[index].Data()),selectionHLT[index][indextriggers].Data());
		  hHLTefficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hHLTefficiencynum[index][indextriggers]->SetName(namehHLTefficiencynum[index][indextriggers].Data());
		  hHLTefficiencynum[index][indextriggers]->Sumw2();
		  
		  ttemp->Draw(Form("(%s)>>hprescaleHLT",prescalecorrHLTMB[index][indextriggers].Data()),"1");
		  double averageHLTprescale=hprescaleHLT->GetMean();
		  hHLTefficiencynum[index][indextriggers]->Scale(averageHLTprescale);
		  
          for (int i=1;i<=hHLTefficiencynum[index][indextriggers]->GetNbinsX();i++){
             double numv=hHLTefficiencynum[index][indextriggers]->GetBinContent(i);
             double denv=hHLTefficiencyden[index][indextriggers]->GetBinContent(i);
             double enumv=hHLTefficiencynum[index][indextriggers]->GetBinError(i);
             double edenv=hHLTefficiencyden[index][indextriggers]->GetBinError(i);
             if(numv>denv) { 
               hHLTefficiencynum[index][indextriggers]->SetBinContent(i,denv);
               hHLTefficiencynum[index][indextriggers]->SetBinError(i,edenv);
             }
          }
          
          gHLTefficiency[index][indextriggers] = new TGraphAsymmErrors;
          gHLTefficiency[index][indextriggers]->BayesDivide(hHLTefficiencynum[index][indextriggers],hHLTefficiencyden[index][indextriggers]);
          gHLTefficiency[index][indextriggers]->SetName(namegHLTefficiency[index][indextriggers].Data());
          
		}
	}
	
	
	TString filenameouptut=Form("foutputTurn%s.root",suffixfile.Data());
	TFile*foutput=new TFile(filenameouptut.Data(),"recreate");
	foutput->cd();
	
	for (int index=0;index<samples;index++){
	
		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;

		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 

	   	  if (indextriggers==0 && do40==0) continue;
		  if (indextriggers==1 && do60==0) continue;
		  if (indextriggers==2 && do80==0) continue;
		  if (indextriggers==3 && do100==0) continue;

    	  hL1efficiencyden[index][indextriggers]->Write();
		  hL1efficiencynum[index][indextriggers]->Write();
		  hHLTefficiencyden[index][indextriggers]->Write();
		  hHLTefficiencynum[index][indextriggers]->Write();
		  gL1efficiency[index][indextriggers]->Write();
		  gHLTefficiency[index][indextriggers]->Write();
        }
    }
}






