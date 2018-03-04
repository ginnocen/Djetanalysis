#include "Plotting.cpp"
#include <vector>
#include "utilitiescorrectedspectrum.h"
#include "luminosityprescales.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TCut.h>
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

void jetspectrumCorrected(int doPP=1, int doPbPb=0, int do40=1,int do60=0,int do80=0){

    initialise();

    TFile *finput[samples];
    TF1*fitErfL1[samples][ntriggers];  
    TF1*fitErfHLT[samples][ntriggers];  
    
	TFile*fFit=new TFile("TurnOnCurves.root","read");
	fFit->cd();
	for (int index=0;index<samples;index++){
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		  fitErfL1[index][indextriggers]=(TF1*)fFit->Get(Form("fitErfL1_%s",nametriggerselectiontagtriggers[index][indextriggers].Data()));
		  fitErfHLT[index][indextriggers]=(TF1*)fFit->Get(Form("fitErfHLT_%s",nametriggerselectiontagtriggers[index][indextriggers].Data()));
		}
    }


    TH1F *hjetptspectrumTotPresclCorr[samples];
    TH1F *hjetleadingptspectrumTotPresclCorr[samples];  
    TH1F *hjetptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetptspectrumpertriggerEffWeighted[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerEffWeighted[samples][ntriggers];  
    TH1F *hjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];
    TH1F *hjetptspectrumpertriggerPresclEffCorr[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerPresclEffCorr[samples][ntriggers];  

    TH1F*htemptemplate=new TH1F("htemp","htemp",2000,0,1000);
    htemptemplate->Sumw2();
    
	for (int index=0;index<samples;index++) { 
      TH1F*htemp=(TH1F*)htemptemplate->Clone("htemp"); 
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
          TH1F*htemp=(TH1F*)htemptemplate->Clone("htemp"); 
		  if (indextriggers==0 && do40==0) continue;
		  if (indextriggers==1 && do60==0) continue;
		  if (indextriggers==2 && do80==0) continue;

          TString l1weight=Form(stringweight.Data(),fitErfL1[index][indextriggers]->GetParameter(0),fitErfL1[index][indextriggers]->GetParameter(1),fitErfL1[index][indextriggers]->GetParameter(1),fitErfL1[index][indextriggers]->GetParameter(3),fitErfL1[index][indextriggers]->GetParameter(2));
          TString hltweight=Form(stringweight.Data(),fitErfHLT[index][indextriggers]->GetParameter(0),fitErfHLT[index][indextriggers]->GetParameter(1),fitErfHLT[index][indextriggers]->GetParameter(1),fitErfHLT[index][indextriggers]->GetParameter(3),fitErfHLT[index][indextriggers]->GetParameter(2));
                  
		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetptspectrumpertrigger[index][indextriggers]->SetName(namehjetptspectrumpertrigger[index][indextriggers].Data());
		  
		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetleadingptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetleadingptspectrumpertrigger[index][indextriggers]->SetName(namehjetleadingptspectrumpertrigger[index][indextriggers].Data());
       /*   
		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),selectionanalysisweightrange[index][indextriggers].Data()*TCut(l1weight)*TCut(hltweight));
		  hjetptspectrumpertriggerEffWeighted[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetptspectrumpertriggerEffWeighted[index][indextriggers]->SetName(namehjetptspectrumpertriggerEffWeighted[index][indextriggers].Data());

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data()*TCut(l1weight)*TCut(hltweight));
		  hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]->SetName(namehjetleadingptspectrumpertriggerEffWeighted[index][indextriggers].Data());
		  */
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]=(TH1F*)hjetptspectrumpertrigger[index][indextriggers]->Clone();
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->SetName(namehjetptspectrumpertriggerPresclCorr[index][indextriggers].Data());
		  hjetptspectrumpertriggerPresclCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]=(TH1F*)hjetleadingptspectrumpertrigger[index][indextriggers]->Clone();
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->SetName(namehjetleadingptspectrumpertriggerPresclCorr[index][indextriggers].Data());
		  hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  /*  
		  hjetptspectrumpertriggerPresclEffCorr[index][indextriggers]=(TH1F*)hjetptspectrumpertriggerEffWeighted[index][indextriggers]->Clone();
		  hjetptspectrumpertriggerPresclEffCorr[index][indextriggers]->SetName(namehjetptspectrumpertriggerPresclEffCorr[index][indextriggers].Data());
		  hjetptspectrumpertriggerPresclEffCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);
		  
		  hjetleadingptspectrumpertriggerPresclEffCorr[index][indextriggers]=(TH1F*)hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]->Clone();
		  hjetleadingptspectrumpertriggerPresclEffCorr[index][indextriggers]->SetName(namehjetleadingptspectrumpertriggerPresclEffCorr[index][indextriggers].Data());
		  hjetleadingptspectrumpertriggerPresclEffCorr[index][indextriggers]->Scale(1./dataluminosity[index][indextriggers]);

		  hjetptspectrumTotPresclCorr[index]->Add(hjetptspectrumpertriggerPresclCorr[index][indextriggers]);
		  hjetleadingptspectrumTotPresclCorr[index]->Add(hjetleadingptspectrumpertriggerPresclCorr[index][indextriggers]);
          */
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
		  
		  //hjetptspectrumpertriggerPresclEffCorr[index][indextriggers]->Write();
		  //hjetleadingptspectrumpertriggerPresclEffCorr[index][indextriggers]->Write();
		  //hjetptspectrumpertriggerEffWeighted[index][indextriggers]->Write();
		  //hjetleadingptspectrumpertriggerEffWeighted[index][indextriggers]->Write();
		}
    }
}
