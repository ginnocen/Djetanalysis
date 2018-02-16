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

void studyjetspectrum(){

    initialise();

	TFile *finput[samples];
    TH1F *hjetptspectrum[samples][nCases];  
    TH1F *hjetleadingptspectrum[samples][nCases];  
    
    TH1F *hL1efficiencyden[samples][ntriggers];  
    TH1F *hL1efficiencynum[samples][ntriggers];  
    TH1F *hHLTefficiencyden[samples][ntriggers];  
    TH1F *hHLTefficiencynum[samples][ntriggers];  

    TGraphAsymmErrors *gL1efficiency[samples][ntriggers];  
    TGraphAsymmErrors *gHLTefficiency[samples][ntriggers];  

	for (int index=0;index<samples;index++){
		finput[index]=new TFile(namefiles[index].Data(),"read"); 
		TH1F*htemp=new TH1F("htemp","htemp",2000,0,1000);
		TTree*ttemp=(TTree*)finput[index]->Get(nametree[index].Data());
		TTree*ttempHLT=(TTree*)finput[index]->Get(nametreeHLT[index].Data());
		ttemp->AddFriend(ttempHLT);
		
		for (int indexcases=0;indexcases<nCases;indexcases++){ 

		  ttemp->Draw(Form("%s>>htemp",namevariable[index].Data()),nametriggerselection[index][indexcases].Data());
		  hjetptspectrum[index][indexcases]=(TH1F*)htemp->Clone();
		  hjetptspectrum[index][indexcases]->SetName(namehjetptspectrum[index][indexcases].Data());
		  
		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),nametriggerselection[index][indexcases].Data());
		  hjetleadingptspectrum[index][indexcases]=(TH1F*)htemp->Clone();
		  hjetleadingptspectrum[index][indexcases]->SetName(namehjetleadingptspectrum[index][indexcases].Data());
	    }
	    
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
		
		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),MBselection[index].Data());
		  hL1efficiencyden[index][indextriggers]=(TH1F*)htemp->Clone();
		  hL1efficiencyden[index][indextriggers]->SetName(namehL1efficiencyden[index][indextriggers].Data());
	  
	      cout<<"index="<<index<<endl;
		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),Form("%s&&%s",MBselection[index].Data(),nameL1trigger[index][indextriggers].Data()));
		  hL1efficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hL1efficiencynum[index][indextriggers]->SetName(namehL1efficiencynum[index][indextriggers].Data());

          gL1efficiency[index][indextriggers] = new TGraphAsymmErrors;
          gL1efficiency[index][indextriggers]->BayesDivide(hL1efficiencynum[index][indextriggers],hL1efficiencyden[index][indextriggers]);
          gL1efficiency[index][indextriggers]->SetName(namegL1efficiency[index][indextriggers].Data());

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),MBselection[index].Data());
		  hHLTefficiencyden[index][indextriggers]=(TH1F*)htemp->Clone();
		  hHLTefficiencyden[index][indextriggers]->SetName(namehHLTefficiencyden[index][indextriggers].Data());

		  ttemp->Draw(Form("Max$(%s)>>htemp",namevariable[index].Data()),Form("%s&&%s",MBselection[index].Data(),nametrigger[index][indextriggers].Data()));
		  hHLTefficiencynum[index][indextriggers]=(TH1F*)htemp->Clone();
		  hHLTefficiencynum[index][indextriggers]->SetName(namehHLTefficiencynum[index][indextriggers].Data());

          gHLTefficiency[index][indextriggers] = new TGraphAsymmErrors;
          gHLTefficiency[index][indextriggers]->BayesDivide(hHLTefficiencynum[index][indextriggers],hHLTefficiencyden[index][indextriggers]);
          gHLTefficiency[index][indextriggers]->SetName(namegHLTefficiency[index][indextriggers].Data());
		}
	}
	
	TFile*foutput=new TFile("foutput.root","recreate");
	foutput->cd();
	
	for (int index=0;index<samples;index++){
		for (int indexcases=0;indexcases<nCases;indexcases++){
		  hjetptspectrum[index][indexcases]->Write();
		  hjetleadingptspectrum[index][indexcases]->Write();
		}
		for (int indextriggers=0;indextriggers<ntriggers;indextriggers++){ 
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


