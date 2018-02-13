#include "Plotting.cpp"
#include <vector>
#include "utilitiesjetspectrum.h"
#include <TROOT.h>
#include <TStyle.h>
#include <iostream>
#include <iostream>
#include <TF1.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>

void studyjetspectrum(){

	gStyle->SetTextSize(0.05);
	gStyle->SetTextFont(42);
	gStyle->SetPadRightMargin(0.043);
	gStyle->SetPadLeftMargin(0.18);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.145);
	gStyle->SetTitleX(.0f);
	gStyle->SetTitleY(.0f);
	gStyle->SetOptStat(0);
	gStyle->SetMarkerStyle(20);
	gStyle->SetMarkerSize(0.8);


	TH1F *myhistogram[samples][nCases];  
	TFile *finput[samples];

	for (int index=0;index<samples;index++){
		finput[index]=new TFile(namefiles[index].Data(),"read"); 
		TH1F*htemp=new TH1F("htemp","htemp",2000,0,1000);
		TTree*ttemp=(TTree*)finput[index]->Get(nametree[index].Data());
		TTree*ttempHLT=(TTree*)finput[index]->Get(nametreeHLT[index].Data());
		ttemp->AddFriend(ttempHLT);
		for (int indexcases=0;indexcases<nCases;indexcases++){ 
		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),nametriggerselection[index][indexcases].Data());
		  myhistogram[index][indexcases]=(TH1F*)htemp->Clone();
		  TString histoname="hpt"+nametriggerselectiontag[index][indexcases]+labelsamples[index];
		  myhistogram[index][indexcases]->SetName(histoname.Data());
		}
	}
	
	TFile*foutput=new TFile("foutput.root","recreate");
	foutput->cd();
	for (int index=0;index<samples;index++){
		for (int indexcases=0;indexcases<nCases;indexcases++){
		  myhistogram[index][indexcases]->Write();
		}
    }
/*
	TH1F *hRatios[nCases];
	TLegend*leg[nCases];
	TLegendEntry *legentry[samples][nCases];

	Plotting*myplot=new Plotting();
	TH2F* hempty[nCases];

	for (int indexcases=0;indexcases<nCases;indexcases++){ 
		TString namehistoempty="hempty"+labelCases[indexcases];
		hempty[indexcases]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[indexcases].Data(),string_yaxis[indexcases].Data(),lowerrangex[indexcases],upperrangex[indexcases],lowerrangey[indexcases],upperrangey[indexcases]);
        leg[indexcases]=(TLegend*)myplot->GetLegend(0.2114094,0.6474695,0.6610738,0.8638743);
        
		for (int index=0;index<samples-1;index++){
            
			legentry[index][indexcases]=leg[indexcases]->AddEntry(myhistogram[index][indexcases],labelsamples[index].Data(),"pl");
			legentry[index][indexcases]->SetLineColor(colours[index]);
			myhistogram[index][indexcases]->Divide(myhistogram[samples-1][indexcases]);
		}  
	}
	

	TCanvas*c[nCases];
	TString canvasname[nCases];

	for (int indexcases=0;indexcases<nCases;indexcases++){


		canvasname[indexcases]=Form("canvasSpectraplot%s.pdf",labelCases[indexcases].Data());
		c[indexcases]=new TCanvas(canvasname[indexcases].Data(),canvasname[indexcases].Data(),600,600);
		c[indexcases]->cd();
		gPad->SetLogx();
		hempty[indexcases]->Draw();    
		for (int index=0;index<samples-1;index++){
			myhistogram[index][indexcases]->Draw("same");
		}
		leg[indexcases]->Draw();
		c[indexcases]->SaveAs(canvasname[indexcases].Data());
	}
	*/
}


