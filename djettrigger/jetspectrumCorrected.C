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

void jetspectrumCorrected(int doPP=1, int doPbPb=1, int do40=1,int do60=1,int do80=1){

    initialise();

    TFile *finput[samples];

    TH1F *hjetptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertrigger[samples][ntriggers];  

	for (int index=0;index<samples;index++){

		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;

		finput[index]=new TFile(namefiles[index].Data(),"read"); 
		TH1F*htemp=new TH1F("htemp","htemp",2000,0,1000);
		TTree*ttemp=(TTree*)finput[index]->Get(nametree[index].Data());
		TTree*ttempHLT=(TTree*)finput[index]->Get(nametreeHLT[index].Data());
		
		ttemp->AddFriend(ttempHLT);
		
	  for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
	  
		  if (indextriggers==0 && do40==0) continue;
		  if (indextriggers==1 && do60==0) continue;
		  if (indextriggers==2 && do80==0) continue;


		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetptspectrumpertrigger[index][indextriggers]->SetName(namehjetptspectrumpertrigger[index][indextriggers].Data());
		  
		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),selectionanalysis[index][indextriggers].Data());
		  hjetleadingptspectrumpertrigger[index][indextriggers]=(TH1F*)htemp->Clone();
		  hjetleadingptspectrumpertrigger[index][indextriggers]->SetName(namehjetleadingptspectrumpertrigger[index][indextriggers].Data());
	    }
	}
	
	TFile*foutput=new TFile("foutputjetspectrumCorrected.root","recreate");
	foutput->cd();
	
	for (int index=0;index<samples;index++){
	
		if (index==0 && doPP==0) continue;
		if (index==1 && doPbPb==0) continue;

		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 

	   	  if (indextriggers==0 && do40==0) continue;
		  if (indextriggers==1 && do60==0) continue;
		  if (indextriggers==2 && do80==0) continue;
		  hjetptspectrumpertrigger[index][indextriggers]->Write();
		  hjetleadingptspectrumpertrigger[index][indextriggers]->Write();
		}
    }
}
/*
void plot(){

    initialise();
    
    TH1F *hjetptspectrum[samples][nCases];  
    TH1F *hjetleadingptspectrum[samples][nCases];  
    
	TFile*finput=new TFile("foutput.root","read");
	finput->cd();
	for (int index=0;index<samples;index++){
		for (int indexcases=0;indexcases<nCases;indexcases++){
		  hjetptspectrum[index][indexcases]=(TH1F*)finput->Get(namehjetptspectrum[index][indexcases].Data());
		  hjetleadingptspectrum[index][indexcases]=(TH1F*)finput->Get(namehjetleadingptspectrum[index][indexcases].Data());
		}
    }

	TLegend*leg[samples];
	TLegendEntry *legentry[samples][nCases];

	Plotting*myplot=new Plotting();
	TH2F* hempty[samples];
	
	for (int index=0;index<samples;index++){
	  TString namehistoempty="hempty"+labelsamples[index];
	  hempty[index]=(TH2F*)myplot->GetEmpty(namehistoempty.Data(),string_xaxis[index].Data(),string_yaxis[index].Data(),lowerrangex[index],upperrangex[index],lowerrangey[index],upperrangey[index]);
      leg[index]=(TLegend*)myplot->GetLegend(0.2114094,0.6474695,0.6610738,0.8638743);

       for (int indexcases=0;indexcases<nCases;indexcases++){ 
			legentry[index][indexcases]=leg[index]->AddEntry(hjetptspectrum[index][indexcases],nametriggerselectiontag[index][indexcases].Data(),"pl");
			legentry[index][indexcases]->SetLineColor(colours[indexcases]);
			hjetptspectrum[index][indexcases]->SetLineColor(colours[indexcases]);
			hjetptspectrum[index][indexcases]->SetMarkerStyle(markerstyle[indexcases]);
			hjetptspectrum[index][indexcases]->SetLineWidth(widthline[indexcases]);
			hjetleadingptspectrum[index][indexcases]->SetLineColor(colours[indexcases]);
			hjetleadingptspectrum[index][indexcases]->SetMarkerStyle(markerstyle[indexcases]);
			hjetleadingptspectrum[index][indexcases]->SetLineWidth(widthline[indexcases]);
		}  
	}

	TCanvas*c[samples];
	TString canvasname[samples];

	for (int index=0;index<samples;index++){
		canvasname[index]=Form("plottriggers/canvasJetptplot%s.pdf",labelsamples[index].Data());
		c[index]=new TCanvas(canvasname[index].Data(),canvasname[index].Data(),600,600);
		c[index]->cd();
		gPad->SetLogx();
		gPad->SetLogy();
		hempty[index]->Draw();    
       for (int indexcases=0;indexcases<nCases;indexcases++){ 
			hjetptspectrum[index][indexcases]->Draw("same");
		}
		leg[index]->Draw();
		c[index]->SaveAs(canvasname[index].Data());
	}

	TCanvas*cleading[samples];
	TString canvasnameleading[samples];

	for (int index=0;index<samples;index++){
		canvasnameleading[index]=Form("plottriggers/canvasleadingJetptplot%s.pdf",labelsamples[index].Data());
		cleading[index]=new TCanvas(canvasnameleading[index].Data(),canvasnameleading[index].Data(),600,600);
		cleading[index]->cd();
		gPad->SetLogx();
		gPad->SetLogy();
		hempty[index]->Draw();    
       for (int indexcases=0;indexcases<nCases;indexcases++){ 
			hjetleadingptspectrum[index][indexcases]->Draw("same");
		}
		leg[index]->Draw();
		cleading[index]->SaveAs(canvasnameleading[index].Data());
	}
}

*/




