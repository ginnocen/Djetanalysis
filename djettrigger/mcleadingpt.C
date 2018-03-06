#include "../includes/xjjrootuti.h"
#include "utilitiescorrectedspectrum.h"
#include <TH2F.h>
#include <TH1F.h>
#include <TLegend.h>

void mcleadingpt()
{
	TFile* ppin=TFile::Open("triggercorrection/djtana/rootfilesWeight/hist_Djet_ppRaw_woCorr_Signal_MC_GenD_GenJet_jetpt_60p0_999p0_jeteta_0p3_1p6_HLT60test_woScale_woSmearPt_woSmearAng.root");
	TFile* PbPbin=TFile::Open("triggercorrection/djtana/rootfilesWeight/hist_Djet_PbPbRaw_woCorr_Signal_MC_GenD_GenJet_jetpt_60p0_999p0_jeteta_0p3_1p6_HLT60test_woScale_woSmearPt_woSmearAng.root");
    initialise();
	xjjroot::setgstyle();

	TH1F* hleadingptspectrum[samples];
	TH1F* hleadingptspectrumTriggered[samples];
	TH1F* hleadingptspectrumCorrected[samples];
	TH1F* hleadingptspectrumratio[samples];
	TH1F* hleadingptspectrumTratio[samples];

	hleadingptspectrum[0] = (TH1F*)ppin->Get("hleadingptspectrum");
	hleadingptspectrum[1] = (TH1F*)PbPbin->Get("hleadingptspectrum");
	hleadingptspectrumTriggered[0] = (TH1F*)ppin->Get("hleadingptspectrumTriggered");
	hleadingptspectrumTriggered[1] = (TH1F*)PbPbin->Get("hleadingptspectrumTriggered");
	hleadingptspectrumCorrected[0] = (TH1F*)ppin->Get("hleadingptspectrumCorrected");
	hleadingptspectrumCorrected[1] = (TH1F*)PbPbin->Get("hleadingptspectrumCorrected");
	hleadingptspectrumratio[0]=(TH1F*)hleadingptspectrumCorrected[0]->Clone();
	hleadingptspectrumratio[1]=(TH1F*)hleadingptspectrumCorrected[0]->Clone();
	hleadingptspectrumratio[0]->Divide(hleadingptspectrumCorrected[0],hleadingptspectrum[0]);
	hleadingptspectrumratio[1]->Divide(hleadingptspectrumCorrected[1],hleadingptspectrum[1]);
	hleadingptspectrumTratio[0]=(TH1F*)hleadingptspectrumCorrected[0]->Clone();
	hleadingptspectrumTratio[1]=(TH1F*)hleadingptspectrumCorrected[0]->Clone();
	hleadingptspectrumTratio[0]->Divide(hleadingptspectrumTriggered[0],hleadingptspectrum[0]);
	hleadingptspectrumTratio[1]->Divide(hleadingptspectrumTriggered[1],hleadingptspectrum[1]);


	TCanvas *cppratio = new TCanvas("cppratio","pp",800,800);
	TCanvas *cPbPbratio = new TCanvas("cPbPbratio","PbPb",800,800);

	TCanvas *cpp = new TCanvas("cpp","pp",800,800);
	TCanvas *cPbPb = new TCanvas("cPbPb","PbPb",800,800);

	TH2F* hempties[2];
	TH2F* hemptiesr[2];

	hempties[0] = new TH2F("",Form("%s;leading p_{t};#frac{dN}{dp_{t}}","pp MC"),300,0,300,1000,1,pow(10,5));
	hempties[1] = new TH2F("",Form("%s;leading p_{t};#frac{dN}{dp_{t}}","PbPb MC"),300,0,300,1000,1,pow(10,5));

	hemptiesr[0] = new TH2F("",Form("%s;leading p_{t};#frac{dN}{dp_{t}}","pp MC ratio"),300,0,300,1000,0,2);
	hemptiesr[1] = new TH2F("",Form("%s;leading p_{t};#frac{dN}{dp_{t}}","PbPb MC ratio"),300,0,300,1000,0,2);

	cppratio->cd();
	xjjroot::sethempty(hemptiesr[0],0,0);
	hemptiesr[0]->Draw();
	xjjroot::setthgrstyle(hleadingptspectrumratio[0],kBlack,20,0.8,kBlack,-1,1,-1,0.1,-1);
	hleadingptspectrumratio[0]->Draw("PE same");
	xjjroot::drawCMS("pp");
	cppratio->SaveAs("ppMCratio.pdf");

	cPbPbratio->cd();
	xjjroot::sethempty(hemptiesr[1],0,0);
	hemptiesr[1]->Draw();
	xjjroot::setthgrstyle(hleadingptspectrumratio[1],kBlack,20,0.8,kBlack,-1,1,-1,0.1,-1);
	hleadingptspectrumratio[1]->Draw("PE same");
	xjjroot::drawCMS("PbPb");
	cPbPbratio->SaveAs("PbPbMCratio.pdf");

	cpp->cd();
	cpp->SetLogy();
	xjjroot::sethempty(hempties[0],0,0);
	hempties[0]->Draw();
	xjjroot::setthgrstyle(hleadingptspectrum[0],kRed,20,1,kRed,-1,1,-1,0.1,-1);
	xjjroot::setthgrstyle(hleadingptspectrumTriggered[0],kGreen,20,1,kGreen,-1,1,0.1,-1);
	xjjroot::setthgrstyle(hleadingptspectrumCorrected[0],kBlue,20,0.8,kBlue,-1,1,-1,0.1,-1);
	TLegend* legpp = new TLegend(0.33,0.75,0.9,0.9);
	hleadingptspectrum[0]->Draw("PE same");
	hleadingptspectrumTriggered[0]->Draw("PE same");
	hleadingptspectrumCorrected[0]->Draw("PE same");
	legpp->AddEntry(hleadingptspectrum[0],"original","lp");
	legpp->AddEntry(hleadingptspectrumTriggered[0],"trigger-selected","lp");
	legpp->AddEntry(hleadingptspectrumCorrected[0],"trigger-selected and corrected","lp");
	xjjroot::setleg(legpp);
	legpp->Draw("same");
	xjjroot::drawCMS("pp");
	cpp->SaveAs("ppMC.pdf");

	cPbPb->cd();
	cPbPb->SetLogy();
	xjjroot::sethempty(hempties[1],0,0);
	hempties[1]->Draw();
	xjjroot::setthgrstyle(hleadingptspectrum[1],kRed,20,1,kRed,-1,1,-1,0.1,-1);
	xjjroot::setthgrstyle(hleadingptspectrumTriggered[1],kGreen,20,1,kGreen,-1,1,0.1,-1);
	xjjroot::setthgrstyle(hleadingptspectrumCorrected[1],kBlue,20,0.8,kBlue,-1,1,-1,0.1,-1);
	TLegend* legpbpb = new TLegend(0.33,0.75,0.9,0.9);
	hleadingptspectrum[1]->Draw("PE same");
	hleadingptspectrumTriggered[1]->Draw("PE same");
	hleadingptspectrumCorrected[1]->Draw("PE same");
	legpbpb->AddEntry(hleadingptspectrum[1],"original","lp");
	legpbpb->AddEntry(hleadingptspectrumTriggered[1],"trigger-selected","lp");
	legpbpb->AddEntry(hleadingptspectrumCorrected[1],"trigger-selected and corrected","lp");
	xjjroot::setleg(legpbpb);
	legpbpb->Draw("same");
	xjjroot::drawCMS("PbPb");
	cPbPb->SaveAs("PbPbMC.pdf");


}