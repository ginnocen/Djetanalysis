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
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>



void triggerTurnOn(int doPP=1, int doPbPb=1){

    initialise();
	TFile *finput[samples];
    TH1F *hL1efficiencyden[samples];  
    TH1F *hL1efficiencynum[samples][ntriggers];  
    TH1F *hHLTefficiencyden[samples][ntriggers];  
    TH1F *hHLTefficiencynum[samples][ntriggers];  

    TGraphAsymmErrors *gL1efficiency[samples][ntriggers];  
    TGraphAsymmErrors *gHLTefficiency[samples][ntriggers];  
    TGraphAsymmErrors *gTotefficiency[samples][ntriggers];  

	for (int index=0;index<samples;index++){
		finput[index]=new TFile(namefilesMB[index].Data(),"read"); 
		TH1F*htemp=new TH1F("htemp","htemp",nbinsTurnOn,bondaries_nbinsTurnOn);
		TTree*ttemp=(TTree*)finput[index]->Get(nametreeMB[index].Data());
		TTree*ttempHLT=(TTree*)finput[index]->Get(nametreeHLTMB[index].Data());
		TTree*ttempSkim=(TTree*)finput[index]->Get(nametreeSkimMB[index].Data());
		TTree*ttempEvt=(TTree*)finput[index]->Get(nametreeEvtMB[index].Data());
		
		ttemp->AddFriend(ttempHLT);
		ttemp->AddFriend(ttempSkim);
		ttemp->AddFriend(ttempEvt);
		
		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;

		ttemp->Draw(Form("Max$(%s)>>htemp",namevariableMB[index].Data()),preselection[index].Data());
		hL1efficiencyden[index]=(TH1F*)htemp->Clone();
		hL1efficiencyden[index]->SetName(namehL1efficiencyden[index].Data());


		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
			  
	      cout<<"index="<<index<<endl;
		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariableMB[index].Data()),L1selection[index][indextriggers]);
		  hL1efficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hL1efficiencynum[index][indextriggers]->SetName(namehL1efficiencynum[index][indextriggers].Data());

          gL1efficiency[index][indextriggers] = new TGraphAsymmErrors;
          gL1efficiency[index][indextriggers]->BayesDivide(hL1efficiencynum[index][indextriggers],hL1efficiencyden[index]);
          gL1efficiency[index][indextriggers]->SetName(namegL1efficiency[index][indextriggers].Data());

		  hHLTefficiencyden[index][indextriggers]=(TH1F*)hL1efficiencynum[index][indextriggers]->Clone();
		  hHLTefficiencyden[index][indextriggers]->SetName(namehHLTefficiencyden[index][indextriggers].Data());

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariableMB[index].Data()),HLTselection[index][indextriggers]);
		  hHLTefficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hHLTefficiencynum[index][indextriggers]->SetName(namehHLTefficiencynum[index][indextriggers].Data());

          gHLTefficiency[index][indextriggers] = new TGraphAsymmErrors;
          gHLTefficiency[index][indextriggers]->BayesDivide(hHLTefficiencynum[index][indextriggers],hHLTefficiencyden[index][indextriggers]);
          gHLTefficiency[index][indextriggers]->SetName(namegHLTefficiency[index][indextriggers].Data());
          
          gTotefficiency[index][indextriggers] = new TGraphAsymmErrors;
          gTotefficiency[index][indextriggers]->BayesDivide(hHLTefficiencynum[index][indextriggers],hL1efficiencyden[index]);
          gTotefficiency[index][indextriggers]->SetName(namegTotefficiency[index][indextriggers].Data());
		}
	}
	
	TFile*foutput=new TFile("foutputTurnOn.root","recreate");
	foutput->cd();
	
	for (int index=0;index<samples;index++){
	
		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;

		hL1efficiencyden[index]->Write();
	
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		  hL1efficiencynum[index][indextriggers]->Write();
		  hHLTefficiencyden[index][indextriggers]->Write();
		  hHLTefficiencynum[index][indextriggers]->Write();
		  gL1efficiency[index][indextriggers]->Write();
		  gHLTefficiency[index][indextriggers]->Write();
		  gTotefficiency[index][indextriggers]->Write();
        }
    }
}


void plot(){

    initialise();
    
    TGraphAsymmErrors *gL1efficiency[samples][ntriggers];  
    TGraphAsymmErrors *gHLTefficiency[samples][ntriggers];  
    TGraphAsymmErrors *gTotefficiency[samples][ntriggers];  
    
	TFile*finput=new TFile("foutputTurnOn.root","read");
	finput->cd();
	for (int index=0;index<samples;index++){
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		  gL1efficiency[index][indextriggers]=(TGraphAsymmErrors*)finput->Get(namegL1efficiency[index][indextriggers].Data());
		  gHLTefficiency[index][indextriggers]=(TGraphAsymmErrors*)finput->Get(namegHLTefficiency[index][indextriggers].Data());
		  gTotefficiency[index][indextriggers]=(TGraphAsymmErrors*)finput->Get(namegTotefficiency[index][indextriggers].Data());
		}
    }
    
	TLegend*legL1[samples];
	TLegend*legHLT[samples];
	TLegend*legTot[samples];
	
	TLegendEntry *legentryL1[samples][ntriggers];
	TLegendEntry *legentryHLT[samples][ntriggers];
	TLegendEntry *legentryTot[samples][ntriggers];

	Plotting*myplot=new Plotting();
	TH2F* hemptyL1[samples];
	TH2F* hemptyHLT[samples];
	TH2F* hemptyTot[samples];
	
	for (int index=0;index<samples;index++){
	
	  TString namehistoempty="hempty"+labelsamples[index];
	  hemptyL1[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxisTurnOnL1[index].Data(),lowerrangex[index],upperrangex[index],lowerrangeyTurnOn[index],upperrangeyTurnOn[index]);
	  hemptyHLT[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxisTurnOnHLT[index].Data(),lowerrangex[index],upperrangex[index],lowerrangeyTurnOn[index],upperrangeyTurnOn[index]);
	  hemptyTot[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxisTurnOnTot[index].Data(),lowerrangex[index],upperrangex[index],lowerrangeyTurnOn[index],upperrangeyTurnOn[index]);
      legL1[index]=(TLegend*)myplot->GetLegend(0.2114094,0.6474695,0.6610738,0.8638743);
      legHLT[index]=(TLegend*)myplot->GetLegend(0.2114094,0.6474695,0.6610738,0.8638743);
      legTot[index]=(TLegend*)myplot->GetLegend(0.2114094,0.6474695,0.6610738,0.8638743);

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

			legentryTot[index][indextriggers]=legTot[index]->AddEntry(gTotefficiency[index][indextriggers],nametriggerMB[index][indextriggers].Data(),"pl");
			legentryTot[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gTotefficiency[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gTotefficiency[index][indextriggers]->SetMarkerColor(coloursTurnOn[indextriggers]);
			gTotefficiency[index][indextriggers]->SetMarkerStyle(markerstyleTurnOn[indextriggers]);
			gTotefficiency[index][indextriggers]->SetLineWidth(widthlineTurnOn[indextriggers]);
		}  
	}

	TCanvas*cL1[samples];
	TString canvasnameL1[samples];

	for (int index=0;index<samples;index++){
		canvasnameL1[index]=Form("plottriggers/canvasL1Jetptplot%s.pdf",labelsamples[index].Data());
		cL1[index]=new TCanvas(canvasnameL1[index].Data(),canvasnameL1[index].Data(),600,600);
		cL1[index]->cd();
		gPad->SetLogx();
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
		canvasnameHLT[index]=Form("plottriggers/canvasHLTJetptplot%s.pdf",labelsamples[index].Data());
		cHLT[index]=new TCanvas(canvasnameHLT[index].Data(),canvasnameHLT[index].Data(),600,600);
		cHLT[index]->cd();
		gPad->SetLogx();
		hemptyHLT[index]->Draw();    
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
			gHLTefficiency[index][indextriggers]->Draw("EPsame");
		}
		legHLT[index]->Draw();
		cHLT[index]->SaveAs(canvasnameHLT[index].Data());
	}

	TCanvas*cTot[samples];
	TString canvasnameTot[samples];

	for (int index=0;index<samples;index++){
		canvasnameTot[index]=Form("plottriggers/canvasTotJetptplot%s.pdf",labelsamples[index].Data());
		cTot[index]=new TCanvas(canvasnameTot[index].Data(),canvasnameTot[index].Data(),600,600);
		cTot[index]->cd();
		gPad->SetLogx();
		hemptyTot[index]->Draw();    
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
			gTotefficiency[index][indextriggers]->Draw("EPsame");
		}
		legTot[index]->Draw();
		cTot[index]->SaveAs(canvasnameTot[index].Data());
	}

}






