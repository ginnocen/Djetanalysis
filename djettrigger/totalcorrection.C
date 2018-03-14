#include <TF1.h>
#include "utilitiesturnonstudy.h"
#include "../includes/xjjrootuti.h"

void totalcorrection()
{
	xjjroot::setgstyle();
	TFile* fcross = TFile::Open("dummycodes/fcross.root");
	TF1* totalturnon[samples][ntriggers];
	TH2F* hempties[samples][ntriggers];
	TCanvas* c[samples][ntriggers];

	for(int i=0;i<samples;i++)
	{
		for(int j=0;j<ntriggers;j++)
		{
			if(!plotturnon[i][j]) continue;
			totalturnon[i][j] = (TF1*)fcross->Get(Form("myTotal_%s",nametriggerselectiontagtriggers[i][j].Data()));
			hempties[i][j] = new TH2F(nametriggerselectiontagtriggers[i][j].Data(),"asdf;leading jet p_{t};total efficiency",1000,0,300,1000,0,1);
			xjjroot::sethempty<TH2F>(hempties[i][j],0,0);
			c[i][j] = new TCanvas(Form("%d%d",i,j),Form("%d%d",i,j),800,800);
			hempties[i][j]->Draw();
			TF1* temp = (TF1*)totalturnon[i][j]->Clone();
			temp->SetRange(0,300);
			temp->Draw("same");
			c[i][j]->SaveAs(Form("total_%s.pdf",nametriggerselectiontagtriggers[i][j].Data()));
		}
	}


}