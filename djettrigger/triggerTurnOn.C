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

void triggerTurnOn(){

    initialise();
    
    TGraphAsymmErrors *gL1efficiency[samples][ntriggers];  
    TGraphAsymmErrors *gHLTefficiency[samples][ntriggers];  
    TGraphAsymmErrors *gTotefficiency[samples][ntriggers];  
    
	TFile*finput=new TFile("foutput.root","read");
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

			legentryHLT[index][indextriggers]=legHLT[index]->AddEntry(gHLTefficiency[index][indextriggers],nametrigger[index][indextriggers].Data(),"pl");
			legentryHLT[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetLineColor(coloursTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetMarkerColor(coloursTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetMarkerStyle(markerstyleTurnOn[indextriggers]);
			gHLTefficiency[index][indextriggers]->SetLineWidth(widthlineTurnOn[indextriggers]);

			legentryTot[index][indextriggers]=legTot[index]->AddEntry(gTotefficiency[index][indextriggers],nametrigger[index][indextriggers].Data(),"pl");
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






