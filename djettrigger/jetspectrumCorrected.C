#include "Plotting.cpp"
#include <vector>
#include "utilitiescorrectedspectrum.h"
#include "luminosityprescales.h"
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
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>

void jetspectrumCorrected(int doPP=1, int doPbPb=1, int do40=1,int do60=1,int do80=1){

    initialise();

    TFile *finput[samples];

    TH1F *hjetptspectrumTotPresclCorr[samples];
    TH1F *hjetleadingptspectrumTotPresclCorr[samples];  
    TH1F *hjetptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];  
    
      TH1F*htemp=new TH1F("htemp","htemp",2000,0,1000);

    
	for (int index=0;index<samples;index++) { 
      TH1F*htemp=new TH1F("htemp","htemp",2000,0,1000);
	  hjetptspectrumTotPresclCorr[index]=(TH1F*)htemp->Clone(); 
	  hjetptspectrumTotPresclCorr[index]->SetName(namehjetptspectrumTotPresclCorr[index].Data());
	  hjetleadingptspectrumTotPresclCorr[index]=(TH1F*)htemp->Clone(); 
	  hjetleadingptspectrumTotPresclCorr[index]->SetName(namehjetleadingptspectrumTotPresclCorr[index].Data());
	}

	for (int index=0;index<samples;index++){

		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;

		finput[index]=new TFile(namefiles[index].Data(),"read"); 

		TTree*ttemp=(TTree*)finput[index]->Get(nametree[index].Data());
		TTree*ttempHLT=(TTree*)finput[index]->Get(nametreeHLT[index].Data());
		
		ttemp->AddFriend(ttempHLT);

	  for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
         TH1F*htemp=new TH1F("htemp","htemp",2000,0,1000);
		  if (indextriggers==0 && do40==0) continue;
		  if (indextriggers==1 && do60==0) continue;
		  if (indextriggers==2 && do80==0) continue;
		  
		  cout<<"selectionanalysis"<<selectionanalysis[index][indextriggers].Data()<<endl;

		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetptspectrumpertrigger[index][indextriggers]->SetName(namehjetptspectrumpertrigger[index][indextriggers].Data());
		  
		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetleadingptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetleadingptspectrumpertrigger[index][indextriggers]->SetName(namehjetleadingptspectrumpertrigger[index][indextriggers].Data());
		  
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]=(TH1F*)hjetptspectrumpertrigger[index][indextriggers]->Clone();
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->SetName(namehjetptspectrumpertriggerPresclCorr[index][indextriggers].Data());
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]=(TH1F*)hjetleadingptspectrumpertrigger[index][indextriggers]->Clone();
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->SetName(namehjetleadingptspectrumpertriggerPresclCorr[index][indextriggers].Data());
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  
		  hjetptspectrumTotPresclCorr[index]->Add(hjetptspectrumpertriggerPresclCorr[index][indextriggers]);
		  hjetleadingptspectrumTotPresclCorr[index]->Add(hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]);
		
		}
	}

	TFile*foutput=new TFile("foutputjetspectrumCorrected.root","recreate");
	foutput->cd();
	
	for (int index=0;index<samples;index++){
	
		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;
		
		hjetptspectrumTotPresclCorr[index]->Write();
		hjetleadingptspectrumTotPresclCorr[index]->Write();

		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 

	   	  if (indextriggers==0 && do40==0) continue;
		  if (indextriggers==1 && do60==0) continue;
		  if (indextriggers==2 && do80==0) continue;
		  
		  hjetptspectrumpertrigger[index][indextriggers]->Write();
		  hjetleadingptspectrumpertrigger[index][indextriggers]->Write();
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->Write();
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->Write();
		}
    }
    foutput->Close();

}
