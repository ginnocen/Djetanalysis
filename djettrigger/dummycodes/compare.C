#include "TFile.h"
#include "TF1.h"
#include "../utilitiesturnonstudy.h"
#include "../triggertables.h"

void compare()
{
	TF1* crossfL1[samples][ntriggers];
	TF1* crossfHLT[samples][ntriggers];
	TF1* originalL1[samples][ntriggers];
	TF1* originalHLT[samples][ntriggers];
	TFile* fc = TFile::Open("fcross.root");
	TFile* fo = TFile::Open("../TurnOnCurves.root");
	TCanvas* cL1[samples][ntriggers];
	TCanvas* cHLT[samples][ntriggers];
	for(int i=0;i<samples;i++)
	{
		for(int j=0;j<ntriggers;j++)
		{
			if(plotturnon[i][j]==0) continue;
			crossfL1[i][j] = (TF1*)fc->Get(Form("myfL1_%s",nametriggerselectiontagtriggers[i][j].Data()));
			if(!crossfL1[i][j]) cout << "bad fcross L1" << i << " " << j << std::endl;
			crossfHLT[i][j] = (TF1*)fc->Get(Form("myfHLT_%s",nametriggerselectiontagtriggers[i][j].Data()));
			if(!crossfHLT[i][j]) cout << "bad fcrossHLT" << i << " " << j << std::endl;
			originalL1[i][j] = (TF1*)fo->Get(Form("fitErfL1_%s",nametriggerselectiontagtriggers[i][j].Data()));
			if(!originalL1[i][j]) cout << "bad original L1" << i << " " << j << std::endl;
			if(i==1 && j==1) originalHLT[i][j] = (TF1*)fo->Get(Form("fitErfHLTExtrapolated_%s",nametriggerselectiontagtriggers[i][j].Data()));
			else originalHLT[i][j] = (TF1*)fo->Get(Form("fitErfHLT_%s",nametriggerselectiontagtriggers[i][j].Data()));
			if(!originalHLT[i][j]) cout << "bad original HLT" << i << " " << j << std::endl;
			
			crossfL1[i][j]->SetLineColor(kBlue);
			crossfHLT[i][j]->SetLineColor(kBlue);
			crossfL1[i][j]->SetLineWidth(5);
			crossfHLT[i][j]->SetLineWidth(5);
			cL1[i][j] = new TCanvas("L1","L1",800,800);
			cHLT[i][j] = new TCanvas("HLT","HLT",800,800);
			cL1[i][j]->cd();
			crossfL1[i][j]->SetTitle(Form("L1_%s",nametriggerselectiontagtriggers[i][j].Data()));
			crossfL1[i][j]->SetRange(0,150);
			crossfL1[i][j]->Draw();
			originalL1[i][j]->Draw("same");
			TLegend* legL1 = new TLegend(0.75,0.75,0.9,0.9);
			legL1->AddEntry(crossfL1[i][j],"fcross","l");
			legL1->AddEntry(originalL1[i][j],"original","l");
			legL1->Draw();
			cL1[i][j]->SaveAs(Form("L1%s_crosscheck.pdf",nametriggerselectiontagtriggers[i][j].Data()));
			cHLT[i][j]->cd();
			crossfHLT[i][j]->SetTitle(Form("HLT_%s",nametriggerselectiontagtriggers[i][j].Data()));
			crossfHLT[i][j]->SetRange(0,150);
			crossfHLT[i][j]->Draw();
			originalHLT[i][j]->Draw("same");
			TLegend* legHLT = new TLegend(0.75,0.75,0.9,0.9);
			legHLT->AddEntry(crossfL1[i][j],"fcross","l");
			legHLT->AddEntry(originalL1[i][j],"original","l");
			legHLT->Draw();
			cHLT[i][j]->SaveAs(Form("HLT%s_crosscheck.pdf",nametriggerselectiontagtriggers[i][j].Data()));
		}
	}
	
	std::cout<<1./(originalL1[1][1]->Eval(60)*originalHLT[1][1]->Eval(60))<<endl;
	std::cout<<efficiencyweight(1,1,60,60,-1.0,1)<<endl;
	
	fc->Close();
	fo->Close();
}