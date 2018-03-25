#include "../includes/xjjrootuti.h"
#include "utilitiescorrectedspectrum.h"
#include <TH2F.h>
#include <TH1F.h>
#include <TLegend.h>

void makespectrumplots()
{
	TFile* fin=new TFile("foutputjetspectrumCorrected.root");
	fin->cd();
    initialise();
	xjjroot::setgstyle();
    const int nplots = 4;
	
    TH1F *hjetptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertrigger[samples][ntriggers];  
    TH1F *hjetptspectrumpertriggerPresclCorr[samples][ntriggers];  
    TH1F *hjetleadingptspectrumpertriggerPresclCorr[samples][ntriggers];
    TH1F *hjetptspectrumpertriggerPresclCorrEffWeighted[samples][ntriggers];
    TH1F *hjetleadingptspectrumpertriggerPresclCorrEffWeighted[samples][ntriggers];

    std::string samplenames[samples] = {"pp","PbPb"};
    std::string triggervalues[ntriggers] = {"HLT40","HLT60","HLT80","HLT100"};

    //get hists
    for(int i=0;i<samples;i++)
    {
    	for(int j=0;j<ntriggers;j++)
    	{
            if(!plotturnon[i][j]) continue;
    		hjetptspectrumpertrigger[i][j] = (TH1F*)fin->Get(namehjetptspectrumpertrigger[i][j]);
            if(!hjetptspectrumpertrigger[i][j]) std::cout << "no hist named " << namehjetptspectrumpertrigger[i][j].Data() << " in file foutputjetspectrumCorrected.root" << std::endl;
    		hjetleadingptspectrumpertrigger[i][j] = (TH1F*)fin->Get(namehjetleadingptspectrumpertrigger[i][j].Data());
    		hjetptspectrumpertriggerPresclCorr[i][j] = (TH1F*)fin->Get(namehjetptspectrumpertriggerPresclCorr[i][j].Data());
    		hjetleadingptspectrumpertriggerPresclCorr[i][j] = (TH1F*)fin->Get(namehjetleadingptspectrumpertriggerPresclCorr[i][j].Data());
            hjetptspectrumpertriggerPresclCorrEffWeighted[i][j] = (TH1F*)fin->Get(namehjetptspectrumpertriggerPresclCorrEffWeighted[i][j].Data());
            hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j] = (TH1F*)fin->Get(namehjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j].Data());
    	}
    }

    //determine min and max y values
    float miny[nplots][samples];
    float maxy[nplots][samples];
	for(int j=0;j<samples;j++)
	{
		for(int i=0;i<nplots;i++) maxy[i][j] = 0;
		for(int k=0;k<ntriggers;k++)
		{
            if(!plotturnon[j][k]) continue;
			if(hjetptspectrumpertrigger[j][k]->GetMaximum()>maxy[0][j]) maxy[0][j] = hjetptspectrumpertrigger[j][k]->GetMaximum();
			if(hjetleadingptspectrumpertrigger[j][k]->GetMaximum()>maxy[1][j]) maxy[1][j] = hjetleadingptspectrumpertrigger[j][k]->GetMaximum();
			if(hjetptspectrumpertriggerPresclCorr[j][k]->GetMaximum()>maxy[2][j]) maxy[2][j] = hjetptspectrumpertriggerPresclCorr[j][k]->GetMaximum();
			if(hjetleadingptspectrumpertriggerPresclCorr[j][k]->GetMaximum()>maxy[3][j]) maxy[3][j] = hjetleadingptspectrumpertriggerPresclCorr[j][k]->GetMaximum();
            if(hjetptspectrumpertriggerPresclCorrEffWeighted[j][k]->GetMaximum()>maxy[2][j]) maxy[2][j] = hjetptspectrumpertriggerPresclCorrEffWeighted[j][k]->GetMaximum();
            if(hjetleadingptspectrumpertriggerPresclCorrEffWeighted[j][k]->GetMaximum()>maxy[3][j]) maxy[3][j] = hjetleadingptspectrumpertriggerPresclCorrEffWeighted[j][k]->GetMaximum();

			miny[0][j] = 10;
            miny[1][j] = 10;
			if(j==0) {miny[2][j] = pow(10,-5); miny[3][j] = pow(10,-5);}
			if(j==1) {miny[2][j] = pow(10,-1); miny[3][j] = pow(10,-1);}
		}
	}


    TH2F* hempties[nplots][samples];
    TCanvas* c[nplots][samples];
    TLegend* leg[nplots][samples];
    std::string titles[nplots] = {"hjetptspectrumpertrigger","hjetleadingptspectrumpertrigger",
                                    "hjetptspectrumpertriggerPresclCorr","hjetleadingptspectrumpertriggerPresclCorr"};
                                    //"hjetptspectrumpertriggerEffWeighted","hjetleadingptspectrumpertriggerEffWeighted"};
    //plot histograms
    for(int i=0;i<samples;i++)
    {
    	for(int k=0;k<nplots;k++)
    	{

    		if(k%2==0) hempties[k][i] = new TH2F("",Form("%s;p_{t};#frac{dN}{dp_{t}}",titles[k].c_str()),1000,0,300,1000,miny[k][i],maxy[k][i]*3);
    		if(k%2==1) hempties[k][i] = new TH2F("",Form("%s;leading p_{t};#frac{dN}{dp_{t}}",titles[k].c_str()),1000,0,300,1000,miny[k][i],maxy[k][i]*3);
    		c[k][i] = new TCanvas(Form("%d%d",k,i),"",800,800);
    		xjjroot::sethempty(hempties[k][i],0,0);
    		hempties[k][i]->Draw();
    		c[k][i]->SetLogy();
    		leg[k][i] = new TLegend(0.6,0.6,0.9,0.9);
    	}
    	for(int j=0;j<ntriggers;j++)
    	{
    		//if(i!=0 || j<3)
    		{
                if(!plotturnon[i][j]) continue;
	    		c[0][i]->cd();
	    		xjjroot::setthgrstyle(hjetptspectrumpertrigger[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
	    		hjetptspectrumpertrigger[i][j]->Draw("PE same");
	    		leg[0][i]->AddEntry(hjetptspectrumpertrigger[i][j],triggervalues[j].c_str(),"lp");
                

	    		c[1][i]->cd();
	    		xjjroot::setthgrstyle(hjetleadingptspectrumpertrigger[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
	    		hjetleadingptspectrumpertrigger[i][j]->Draw("PE same");
	    		leg[1][i]->AddEntry(hjetleadingptspectrumpertrigger[i][j],triggervalues[j].c_str(),"lp");
                
            

	    		c[2][i]->cd();
	    		xjjroot::setthgrstyle(hjetptspectrumpertriggerPresclCorr[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
	    		hjetptspectrumpertriggerPresclCorr[i][j]->Draw("PE same");
	    		leg[2][i]->AddEntry(hjetptspectrumpertriggerPresclCorr[i][j],triggervalues[j].c_str(),"lp");
                xjjroot::setthgrstyle(hjetptspectrumpertriggerPresclCorrEffWeighted[i][j],effcols[j],styles[j],0.8,effcols[j],-1,1,-1,0.1,-1);
                hjetptspectrumpertriggerPresclCorrEffWeighted[i][j]->Draw("PE same");
                leg[2][i]->AddEntry(hjetptspectrumpertriggerPresclCorrEffWeighted[i][j],(triggervalues[j]+"effweighted").c_str(),"lp");
                

	    		c[3][i]->cd();
	    		xjjroot::setthgrstyle(hjetleadingptspectrumpertriggerPresclCorr[i][j],cols[j],styles[j],0.8,cols[j],-1,1,-1,0.1,-1);
	    		hjetleadingptspectrumpertriggerPresclCorr[i][j]->Draw("PE same");
    			leg[3][i]->AddEntry(hjetleadingptspectrumpertriggerPresclCorr[i][j],triggervalues[j].c_str(),"lp");
                xjjroot::setthgrstyle(hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j],effcols[j],styles[j],0.8,effcols[j],-1,1,-1,0.1,-1);
                hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j]->Draw("PE same");
                leg[3][i]->AddEntry(hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j],(triggervalues[j]+"effweighted").c_str(),"lp");
             }   
    	}
    	for(int k=0;k<nplots;k++)
    	{
    		c[k][i]->cd();
            leg[k][i]->SetBorderSize(0);
            leg[k][i]->SetFillStyle(0);
    		leg[k][i]->Draw();
    		xjjroot::drawCMS(samplenames[i].c_str());
    		c[k][i]->SaveAs(Form("plotspectra/%s%s.pdf",titles[k].c_str(),samplenames[i].c_str()));
    	}
    }
}