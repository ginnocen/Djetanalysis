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
#include <TCut.h>
#include <TGraphAsymmErrors.h>
#include "triggertables.h"

void jetspectrumCorrected(){

    initialise();
    initialiseWeights();

    TFile *finput[samples];

    TH1F *hjetptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
    TH1F *hjetptspectrumpertriggerEffWeighted[samples][ntriggers];
    TH1F *hjetptspectrumpertriggerPresclCorrEffWeighted[samples][ntriggers];

    TH1F *hjetleadingptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerEffWeighted[samples][ntriggers];
    TH1F *hjetleadingptspectrumpertriggerPresclCorrEffWeighted[samples][ntriggers];


 
	for (int index=0;index<samples;index++){
		finput[index]=new TFile(namefiles[index].Data(),"read"); 
		TTree*ttemp=(TTree*)finput[index]->Get(nametree[index].Data());
		TTree*ttempHLT=(TTree*)finput[index]->Get(nametreeHLT[index].Data());
		
		ttemp->AddFriend(ttempHLT);

	  for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
	  	 if 	(dospectrum[index][indextriggers]==0) continue;
	  	  TH1F*htemp=new TH1F("htemp","htemp",2000,0,1000);

		  cout<<"selectionanalysis"<<selectionanalysis[index][indextriggers].Data()<<endl;
		  cout<<"expmyweightL1final"<<expmyweightL1final[index][indextriggers].Data()<<endl;
		  cout<<"expmyweightL1final"<<expmyweightHLTfinal[index][indextriggers].Data()<<endl;

		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetptspectrumpertrigger[index][indextriggers]->SetName(namehjetptspectrumpertrigger[index][indextriggers].Data());
		  
		  ttemp->Draw(Form("%s>>htemp",namevariableMB[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetleadingptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetleadingptspectrumpertrigger[index][indextriggers]->SetName(namehjetleadingptspectrumpertrigger[index][indextriggers].Data());
		
		  
		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data()*TCut(expmyweightL1final[index][indextriggers])*TCut(expmyweightHLTfinal[index][indextriggers]));
		  hjetptspectrumpertriggerEffWeighted[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetptspectrumpertriggerEffWeighted[index][indextriggers]->SetName(namehjetptspectrumpertriggerEffWeighted[index][indextriggers].Data());

		  ttemp->Draw(Form("%s>>htemp",namevariableMB[index].Data()),selectionanalysis[index][indextriggers].Data()*TCut(expmyweightL1final[index][indextriggers])*TCut(expmyweightHLTfinal[index][indextriggers]));
		  hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]->SetName(namehjetleadingptspectrumpertriggerEffWeighted[index][indextriggers].Data());

		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]=(TH1F*)hjetptspectrumpertrigger[index][indextriggers]->Clone();
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->SetName(namehjetptspectrumpertriggerPresclCorr[index][indextriggers].Data());
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->Sumw2();
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]=(TH1F*)hjetleadingptspectrumpertrigger[index][indextriggers]->Clone();
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->SetName(namehjetleadingptspectrumpertriggerPresclCorr[index][indextriggers].Data());
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->Sumw2();
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);

		  hjetptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]=(TH1F*)hjetptspectrumpertriggerEffWeighted[index][indextriggers]->Clone();
		  hjetptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->SetName(namehjetptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers].Data());
		  hjetptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->Sumw2();
		  hjetptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  
		  hjetleadingptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]=(TH1F*)hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]->Clone();
		  hjetleadingptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->SetName(namehjetleadingptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers].Data());
		  hjetleadingptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->Sumw2();
		  hjetleadingptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  		
		}
	}

	TFile*foutput=new TFile("foutputjetspectrumCorrected.root","recreate");
	foutput->cd();
	
	for (int index=0;index<samples;index++){		
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 

	  	 if 	(dospectrum[index][indextriggers]==0) continue;

		  hjetptspectrumpertrigger[index][indextriggers]->Write();
		  hjetleadingptspectrumpertrigger[index][indextriggers]->Write();
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->Write();
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->Write();
		  hjetptspectrumpertriggerEffWeighted[index][indextriggers]->Write();
		  hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]->Write();
		  hjetptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->Write();
		  hjetleadingptspectrumpertriggerPresclCorrEffWeighted[index][indextriggers]->Write();

		}
    }
    foutput->Close();

}
