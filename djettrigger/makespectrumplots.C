#include "../includes/xjjrootuti.h"
#include "utilitiescorrectedspectrum.h"
#include <TH2F.h>
#include <TH1F.h>
#include <TLegend.h>

void makespectrumplots()
{
	TFile* fin=new TFile("foutputjetspectrumCorrected.root");
	fin->cd();
	xjjroot::setgstyle();
	
    TH1F *hjetptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];

    std::string samplenames[samples] = {"pp","PbPb"};
    std::string triggervalues[ntriggers] = {"HLT40","HLT60","HLT80","HLT100"};

    //get hists
    for(int i=0;i<samples;i++)
    {
    	for(int j=0;j<ntriggers;j++)
    	{
    		hjetptspectrumpertrigger[i][j] = (TH1F*)fin->Get(Form("hjetptspectrumpertrigger%s%s%s",samplenames[i].c_str(),triggervalues[j].c_str(),samplenames[i].c_str()));
    		hjetleadingptspectrumpertrigger[i][j] = (TH1F*)fin->Get(Form("hjetleadingptspectrumpertrigger%s%s%s",samplenames[i].c_str(),triggervalues[j].c_str(),samplenames[i].c_str()));
    		hjetptspectrumpertriggerPresclCorr[i][j] = (TH1F*)fin->Get(Form("hjetptspectrumpertriggerPresclCorr%s%s%s",samplenames[i].c_str(),triggervalues[j].c_str(),samplenames[i].c_str()));
    		hjetleadingptspectrumpertriggerPresclCorr[i][j] = (TH1F*)fin->Get(Form("hjetleadingptspectrumpertriggerPresclCorr%s%s%s",samplenames[i].c_str(),triggervalues[j].c_str(),samplenames[i].c_str()));
    	}
    }

    //determine min and max y values
    float miny[4][samples];
    float maxy[4][samples];
    for(int i=0;i<4;i++)
    {
    	for(int j=0;j<samples;j++)
    	{
    		maxy[i][j] = 0;
    		for(int k=0;k<ntriggers;k++)
    		{
    			if(hjetptspectrumpertrigger[j][k]->GetMaximum()>maxy[0][j]) maxy[0][j] = hjetptspectrumpertrigger[j][k]->GetMaximum();
    			if(hjetleadingptspectrumpertrigger[j][k]->GetMaximum()>maxy[1][j]) maxy[1][j] = hjetleadingptspectrumpertrigger[j][k]->GetMaximum();
    			if(hjetptspectrumpertriggerPresclCorr[j][k]->GetMaximum()>maxy[2][j]) maxy[2][j] = hjetptspectrumpertriggerPresclCorr[j][k]->GetMaximum();
    			if(hjetleadingptspectrumpertriggerPresclCorr[j][k]->GetMaximum()>maxy[3][j]) maxy[3][j] = hjetleadingptspectrumpertriggerPresclCorr[j][k]->GetMaximum();

    			if((i==0 || i==1)) miny[i][j] = 10;
    			else if((i==2 || i==3) && j==0) miny[i][j] = pow(10,-5);
    			else if((i==2 || i==3) && j==1) miny[i][j] = pow(10,-1);
    		}
    	}
    }


    TH2F* hempties[4][samples];
    TCanvas* c[4][samples];
    TLegend* leg[4][samples];
    std::string titles[4] = {"hjetptspectrumpertrigger","hjetleadingptspectrumpertrigger","hjetptspectrumpertriggerPresclCorr","hjetleadingptspectrumpertriggerPresclCorr"};
    //plot histograms
    for(int i=0;i<samples;i++)
    {
    	for(int k=0;k<4;k++)
    	{
    		if(k==0 || k==2) hempties[k][i] = new TH2F("",Form("%s;p_{t};#frac{dN}{dp_{t}}",titles[k].c_str()),1000,0,500,1000,miny[k][i],maxy[k][i]*3);
    		if(k==1 || k==3) hempties[k][i] = new TH2F("",Form("%s;leading p_{t};#frac{dN}{dp_{t}}",titles[k].c_str()),1000,0,500,1000,miny[k][i],maxy[k][i]*3);
    		c[k][i] = new TCanvas(Form("%d%d",k,i),"",800,800);
    		xjjroot::sethempty(hempties[k][i],0,0.3);
    		hempties[k][i]->Draw();
    		c[k][i]->SetLogy();
    		leg[k][i] = new TLegend(0.65,0.65,0.9,0.9);
    	}
    	for(int j=0;j<ntriggers;j++)
    	{

    		c[0][i]->cd();
    		xjjroot::setthgrstyle(hjetptspectrumpertrigger[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
    		hjetptspectrumpertrigger[i][j]->SetLineColorAlpha(cols[j],0.5);
    		hjetptspectrumpertrigger[i][j]->Draw("pe same");
    		leg[0][i]->AddEntry(hjetptspectrumpertrigger[i][j],triggervalues[j].c_str(),"lp");

    		c[1][i]->cd();
    		xjjroot::setthgrstyle(hjetleadingptspectrumpertrigger[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
    		hjetleadingptspectrumpertrigger[i][j]->SetLineColorAlpha(cols[j],0.5);
    		hjetleadingptspectrumpertrigger[i][j]->Draw("pe same");
    		leg[1][i]->AddEntry(hjetleadingptspectrumpertrigger[i][j],triggervalues[j].c_str(),"lp");

    		c[2][i]->cd();
    		xjjroot::setthgrstyle(hjetptspectrumpertriggerPresclCorr[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
    		hjetptspectrumpertriggerPresclCorr[i][j]->SetLineColorAlpha(cols[j],0.5);
    		hjetptspectrumpertriggerPresclCorr[i][j]->Draw("pe same");
    		leg[2][i]->AddEntry(hjetptspectrumpertriggerPresclCorr[i][j],triggervalues[j].c_str(),"lp");

    		c[3][i]->cd();
    		xjjroot::setthgrstyle(hjetleadingptspectrumpertriggerPresclCorr[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
    		hjetleadingptspectrumpertriggerPresclCorr[i][j]->SetLineColorAlpha(cols[j],0.5);
    		hjetleadingptspectrumpertriggerPresclCorr[i][j]->Draw("pe same");
			leg[3][i]->AddEntry(hjetleadingptspectrumpertriggerPresclCorr[i][j],triggervalues[j].c_str(),"lp");
    	}
    	for(int k=0;k<4;k++)
    	{
    		c[k][i]->cd();
            leg[k][i]->SetBorderSize(0);
            leg[k][i]->SetFillStyle(0);
    		leg[k][i]->Draw();
    		xjjroot::drawCMS(samplenames[i].c_str());
    		c[k][i]->SaveAs(Form("%s%s.pdf",titles[k].c_str(),samplenames[i].c_str()));
    	}
    }
}