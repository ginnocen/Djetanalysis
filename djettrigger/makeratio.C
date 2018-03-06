#include "../includes/xjjrootuti.h"
#include "utilitiescorrectedspectrum.h"
#include <TH2F.h>
#include <TH1F.h>
#include <TLegend.h>

void makeratio()
{
	TFile* fin=new TFile("foutputjetspectrumCorrected.root");
	fin->cd();
    initialise();
	xjjroot::setgstyle();

	const int nplots = 1;

    TH1F *hjetleadingptspectrumpertriggerPresclCorrEffWeighted[samples][ntriggers];

    TH1F *hjetleadingptspectrumpertriggerPresclCorrEffWeighted8060ratio[samples];
    TH1F *hjetleadingptspectrumpertriggerPresclCorrEffWeighted10080ratio[samples];

    std::string samplenames[samples] = {"pp","PbPb"};

    //get hists
    for(int i=0;i<samples;i++)
    {
    	for(int j=0;j<ntriggers;j++)
    	{
            if(!plotturnon[i][j]) continue;
            std::cout << namehjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j] << std::endl;
            hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j] = (TH1F*)fin->Get(namehjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][j].Data());
    	}
    	hjetleadingptspectrumpertriggerPresclCorrEffWeighted8060ratio[i] = (TH1F*)hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][1]->Clone();
    	hjetleadingptspectrumpertriggerPresclCorrEffWeighted10080ratio[i] = (TH1F*)hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][1]->Clone();
    	if(plotturnon[i][2]==1 && plotturnon[i][1]==1) hjetleadingptspectrumpertriggerPresclCorrEffWeighted8060ratio[i]->Divide(hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][2],hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][1]);
    	if(plotturnon[i][3]==1 && plotturnon[i][2]==1) hjetleadingptspectrumpertriggerPresclCorrEffWeighted10080ratio[i]->Divide(hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][3],hjetleadingptspectrumpertriggerPresclCorrEffWeighted[i][2]);
    }

    TH2F* hempties[nplots][samples];
    TCanvas* c[nplots][samples];
    TLegend* leg[nplots][samples];
    std::string titles[nplots] = {"60/80 and 80/100 ratios"};

    for(int i=0;i<samples;i++)
    {
    	for(int k=0;k<nplots;k++)
    	{

    		if(i%2==0) hempties[k][i] = new TH2F("",Form("%s;p_{t};#frac{dN}{dp_{t}}",titles[k].c_str()),1000,0,300,1000,0,2);
    		if(i%2==1) hempties[k][i] = new TH2F("",Form("%s;leading p_{t};#frac{dN}{dp_{t}}",titles[k].c_str()),1000,0,300,1000,0,2);
    		c[k][i] = new TCanvas(Form("%d%d",k,i),"",800,800);
    		xjjroot::sethempty(hempties[k][i],0,0);
    		hempties[k][i]->Draw();
    		leg[k][i] = new TLegend(0.75,0.75,0.9,0.9);
    	}

    	c[0][i]->cd();
    	xjjroot::setthgrstyle(hjetleadingptspectrumpertriggerPresclCorrEffWeighted8060ratio[i],kBlack,20,1.2,20,-1,1,-1,0.1,-1);
    	xjjroot::setthgrstyle(hjetleadingptspectrumpertriggerPresclCorrEffWeighted10080ratio[i],kBlue,20,1.2,20,-1,1,-1,0.1,-1);
	    if(plotturnon[i][2]==1 && plotturnon[i][1]==1) hjetleadingptspectrumpertriggerPresclCorrEffWeighted8060ratio[i]->Draw("PE same");
	    if(plotturnon[i][3]==1 && plotturnon[i][2]==1) hjetleadingptspectrumpertriggerPresclCorrEffWeighted10080ratio[i]->Draw("PE same");
	    if(plotturnon[i][2]==1 && plotturnon[i][1]==1) leg[0][i]->AddEntry(hjetleadingptspectrumpertriggerPresclCorrEffWeighted8060ratio[i],"HLT80/HLT60","lp");
	    if(plotturnon[i][3]==1 && plotturnon[i][2]==1) leg[0][i]->AddEntry(hjetleadingptspectrumpertriggerPresclCorrEffWeighted10080ratio[i],"HLT100/HLT80","lp");

	    for(int k=0;k<nplots;k++)
    	{
    		c[k][i]->cd();
            leg[k][i]->SetBorderSize(0);
            leg[k][i]->SetFillStyle(0);
    		leg[k][i]->Draw();
    		xjjroot::drawCMS(samplenames[i].c_str());
    		c[k][i]->SaveAs(Form("ratio%s.pdf",samplenames[i].c_str()));
    	}
    }
}