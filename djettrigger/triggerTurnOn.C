#include "Plotting.cpp"
#include <vector>
#include "utilitiesjetspectrum.h"
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


void triggerTurnOn(TString suffixfile="SelectionOnL1HLTprescale",int doPP=1, int doPbPb=1, int do40=1,int do60=1){
     
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
		  std::cout<<"sample="<<index<<std::endl;
		  std::cout<<"indextriggers="<<indextriggers<<std::endl;

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariableMB[index].Data()),preselectionL1[index][indextriggers].Data());
		  hL1efficiencyden[index][indextriggers]=(TH1F*)htemp->Clone();
		  hL1efficiencyden[index][indextriggers]->SetName(namehL1efficiencyden[index][indextriggers].Data());
		  hL1efficiencyden[index][indextriggers]->Sumw2();

	
		  std::cout<<"step1="<<std::endl;

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariableMB[index].Data()),selectionL1[index][indextriggers]);
		  hL1efficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hL1efficiencynum[index][indextriggers]->SetName(namehL1efficiencynum[index][indextriggers].Data());
		  hL1efficiencynum[index][indextriggers]->Sumw2();

		  std::cout<<"step2="<<std::endl;

          gL1efficiency[index][indextriggers] = new TGraphAsymmErrors;
          gL1efficiency[index][indextriggers]->BayesDivide(hL1efficiencynum[index][indextriggers],hL1efficiencyden[index][indextriggers]);
          gL1efficiency[index][indextriggers]->SetName(namegL1efficiency[index][indextriggers].Data());

		  std::cout<<"step3="<<std::endl;

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariableMB[index].Data()),preselectionHLT[index][indextriggers].Data());
		  hHLTefficiencyden[index][indextriggers]=(TH1F*)htemp->Clone();
		  hHLTefficiencyden[index][indextriggers]->SetName(namehHLTefficiencyden[index][indextriggers].Data());
		  hHLTefficiencyden[index][indextriggers]->Sumw2();

		  std::cout<<"step4="<<std::endl;

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariableMB[index].Data()),TCut(prescalecorrHLTMB[index][indextriggers].Data()*TCut(selectionHLT[index][indextriggers].Data())));
		  hHLTefficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hHLTefficiencynum[index][indextriggers]->SetName(namehHLTefficiencynum[index][indextriggers].Data());
		  hHLTefficiencynum[index][indextriggers]->Sumw2();
		  
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

    	  hL1efficiencyden[index][indextriggers]->Write();
		  hL1efficiencynum[index][indextriggers]->Write();
		  hHLTefficiencyden[index][indextriggers]->Write();
		  hHLTefficiencynum[index][indextriggers]->Write();
		  gL1efficiency[index][indextriggers]->Write();
		  gHLTefficiency[index][indextriggers]->Write();
        }
    }
}


void plot(){

    initialise();
    
    TGraphAsymmErrors *gL1efficiency[samples][ntriggers];  
    TGraphAsymmErrors *gHLTefficiency[samples][ntriggers];  
    
	TFile*finput=new TFile("foutputTurnOn.root","read");
	finput->cd();
	for (int index=0;index<samples;index++){
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		  gL1efficiency[index][indextriggers]=(TGraphAsymmErrors*)finput->Get(namegL1efficiency[index][indextriggers].Data());
		  gHLTefficiency[index][indextriggers]=(TGraphAsymmErrors*)finput->Get(namegHLTefficiency[index][indextriggers].Data());
		}
    }
    
	TLegend*legL1[samples];
	TLegend*legHLT[samples];
	
	TLegendEntry *legentryL1[samples][ntriggers];
	TLegendEntry *legentryHLT[samples][ntriggers];

	Plotting*myplot=new Plotting();
	TH2F* hemptyL1[samples];
	TH2F* hemptyHLT[samples];
	
	for (int index=0;index<samples;index++){
	
	  TString namehistoempty="hempty"+labelsamples[index];
	  hemptyL1[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxisTurnOnL1[index].Data(),lowerrangex[index],upperrangex[index],lowerrangeyTurnOn[index],upperrangeyTurnOn[index]);
	  hemptyHLT[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxisTurnOnHLT[index].Data(),lowerrangex[index],upperrangex[index],lowerrangeyTurnOn[index],upperrangeyTurnOn[index]);
      legL1[index]=(TLegend*)myplot->GetLegend(0.2114094,0.6474695,0.6610738,0.8638743);
      legHLT[index]=(TLegend*)myplot->GetLegend(0.2114094,0.6474695,0.6610738,0.8638743);

		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		
			legentryL1[index][indextriggers]=legL1[index]->AddEntry(gL1efficiency[index][indextriggers],nameL1trigger[index][indextriggers].Data(),"pl");
			legentryL1[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gL1efficiency[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gL1efficiency[index][indextriggers]->SetMarkerColor(coloursTurnOn[indextriggers]);
			gL1efficiency[index][indextriggers]->SetMarkerStyle(markerstyleTurnOn[indextriggers]);
			gL1efficiency[index][indextriggers]->SetLineWidth(widthlineTurnOn[indextriggers]);

			legentryHLT[index][indextriggers]=legHLT[index]->AddEntry(gHLTefficiency[index][indextriggers],nametriggerMB[index][indextriggers].Data(),"pl");
			legentryHLT[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetMarkerColor(coloursTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetMarkerStyle(markerstyleTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetLineWidth(widthlineTurnOn[indextriggers]);
		}  
	}

	TCanvas*cL1[samples];
	TString canvasnameL1[samples];

	for (int index=0;index<samples;index++){
		canvasnameL1[index]=Form("plottriggers/canvasL1Jetptplot%s.png",labelsamples[index].Data());
		cL1[index]=new TCanvas(canvasnameL1[index].Data(),canvasnameL1[index].Data(),600,600);
		cL1[index]->cd();
		gPad->SetLogx();
		gPad->SetLogy();
		hemptyL1[index]->Draw();    
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
			gL1efficiency[index][indextriggers]->Draw("EPsame");
		}
		legL1[index]->Draw();
		cL1[index]->SaveAs(canvasnameL1[index].Data());
	}

	TCanvas*cHLT[samples];
	TString canvasnameHLT[samples];

	for (int index=0;index<samples;index++){
		canvasnameHLT[index]=Form("plottriggers/canvasHLTJetptplot%s.png",labelsamples[index].Data());
		cHLT[index]=new TCanvas(canvasnameHLT[index].Data(),canvasnameHLT[index].Data(),600,600);
		cHLT[index]->cd();
		gPad->SetLogx();
		gPad->SetLogy();
		hemptyHLT[index]->Draw();    
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
			gHLTefficiency[index][indextriggers]->Draw("EPsame");
		}
		legHLT[index]->Draw();
		cHLT[index]->SaveAs(canvasnameHLT[index].Data());
	}

}






