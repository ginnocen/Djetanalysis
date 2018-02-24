#include "Plotting.cpp"
#include "../includes/xjjrootuti.h"
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

void plotTurnOn(TString suffixfile="foutputTurnSelectionOnL1HLTprescale.root"){

    initialise();
    xjjroot::setgstyle();
    
    TF1*fitfunctionErfL1(TGraphAsymmErrors*,int,int);
    TF1*fitfunctionErfHLT(TGraphAsymmErrors*,int,int);
    
    TGraphAsymmErrors *gL1efficiency[samples][ntriggers];  
    TGraphAsymmErrors *gHLTefficiency[samples][ntriggers];  
    
    TF1*fitErfL1[samples][ntriggers];  
    TF1*fitErfHLT[samples][ntriggers];  
    
	TFile*finput=new TFile(suffixfile.Data(),"read");
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

	EColor cols[ntriggers] = {kBlack,kRed,kBlue,kGreen};
	int styles[ntriggers] = {20,21,22,20};
	
	for (int index=0;index<samples;index++){
	
	  TString namehistoempty="hempty"+labelsamples[index];
	  hemptyL1[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxisTurnOnL1[index].Data(),lowerrangex[index],upperrangex[index],lowerrangeyTurnOn[index],upperrangeyTurnOn[index]);
	  hemptyHLT[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxisTurnOnHLT[index].Data(),lowerrangex[index],upperrangex[index],lowerrangeyTurnOn[index],upperrangeyTurnOn[index]);
      legL1[index]=(TLegend*)myplot->GetLegend(0.4597315,0.6328671,0.909396,0.8496503);
      legHLT[index]=(TLegend*)myplot->GetLegend(0.4597315,0.6328671,0.909396,0.8496503);
    
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
	TFile* funcfile = new TFile("TurnOnCurves.root","recreate");
	funcfile->cd();

	for (int index=0;index<samples;index++){
		canvasnameL1[index]=Form("plottriggers/canvasL1Jetptplot%s.png",labelsamples[index].Data());
		cL1[index]=new TCanvas(canvasnameL1[index].Data(),canvasnameL1[index].Data(),600,600);
		cL1[index]->cd();
		xjjroot::sethempty(hemptyL1[index],0,0);
		hemptyL1[index]->Draw();    
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
			xjjroot::setthgrstyle(gL1efficiency[index][indextriggers],cols[indextriggers],styles[indextriggers],1.2,cols[indextriggers],1,1,-1,-1,-1);
			gL1efficiency[index][indextriggers]->Draw("EPsame");
		    fitErfL1[index][indextriggers]=(TF1*)fitfunctionErfL1(gL1efficiency[index][indextriggers],index,indextriggers);
		    fitErfL1[index][indextriggers]->Draw("same");
		    fitErfL1[index][indextriggers]->Write(Form("fitErfL1_%s",nametriggerselectiontagtriggers[index][indextriggers].Data()));
		}
		xjjroot::drawCMS(labelsamples[index]);
		legL1[index]->Draw();
		cL1[index]->SaveAs(canvasnameL1[index].Data());
	}

	TCanvas*cHLT[samples];
	TString canvasnameHLT[samples];

	for (int index=0;index<samples;index++){
		canvasnameHLT[index]=Form("plottriggers/canvasHLTJetptplot%s.png",labelsamples[index].Data());
		cHLT[index]=new TCanvas(canvasnameHLT[index].Data(),canvasnameHLT[index].Data(),600,600);
		cHLT[index]->cd();
		xjjroot::sethempty(hemptyHLT[index],0,0);
		hemptyHLT[index]->Draw();    
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){
			xjjroot::setthgrstyle(gHLTefficiency[index][indextriggers],cols[indextriggers],styles[indextriggers],1.2,cols[indextriggers],1,1,-1,-1,-1); 
			gHLTefficiency[index][indextriggers]->Draw("EPsame");
		    fitErfHLT[index][indextriggers]=(TF1*)fitfunctionErfHLT(gHLTefficiency[index][indextriggers],index,indextriggers);
		    fitErfHLT[index][indextriggers]->Draw("same");
		    fitErfHLT[index][indextriggers]->Write(Form("fitErfHLT_%s",nametriggerselectiontagtriggers[index][indextriggers].Data()));
		}
		xjjroot::drawCMS(labelsamples[index]);
		legHLT[index]->Draw();
		cHLT[index]->SaveAs(canvasnameHLT[index].Data());
	}

	funcfile->Close();
}

TF1*fitfunctionErfL1(TGraphAsymmErrors *gEff, int indexsample, int indextrigger){
  std::cout << "L1" << indexsample << indextrigger << std::endl;
  TF1 *fL1= new TF1("fL1",functionalFormTurnOn.Data());
  //TF1 *fL1=new TF1("fL1","TMath::Erf(x*[1]+[2])+0*[0]");
  fL1->SetParameters(a0L1[indexsample][indextrigger],a1L1[indexsample][indextrigger],a2L1[indexsample][indextrigger],a3L1[indexsample][indextrigger]); 
  gEff->Fit("fL1","M"); 
  gEff->GetFunction("fL1")->SetLineColor(coloursTurnOn[indextrigger]);
  return fL1;
}

TF1*fitfunctionErfHLT(TGraphAsymmErrors *gEff, int indexsample, int indextrigger){
  std::cout << "HLT" << indexsample << indextrigger << std::endl;
  TF1 *fHLT= new TF1("fHLT",functionalFormTurnOn.Data());
  //TF1 *fHLT=new TF1("fHLT","TMath::Erf(x*[1]+[2])+0*[0]");
  fHLT->SetParameters(a0HLT[indexsample][indextrigger],a1HLT[indexsample][indextrigger],a2HLT[indexsample][indextrigger],a3HLT[indexsample][indextrigger]); 
  gEff->Fit("fHLT","M");
  if(indexsample!=1 || indextrigger!=0) gEff->GetFunction("fHLT")->SetLineColor(coloursTurnOn[indextrigger]); 
  return fHLT;
}