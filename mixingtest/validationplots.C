#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include "djetMB.h"
#include "../includes/xjjrootuti.h"

void validationplots()
{
	std::string filename = "/mnt/T2_US_MIT/submit-hi2/scratch/mjpeters/Djet/MC/djetmixfull.root";
	Float_t jetptmin = 20;
	TFile* f = TFile::Open(filename.c_str());
	TTree* t = (TTree*)f->Get("djt");
	TCanvas* c = new TCanvas("c","c",800,800);
	//centempty->Draw();
	t->Draw("MBhiBin:hiBin","","COLZ");
	//xjjroot::sethempty(vzempty,0,0);
	TCanvas* v = new TCanvas("v","v",800,800);
	//vzempty->Draw();
	t->Draw("MBvz:vz","","COLZ");
	//xjjroot::sethempty(evtempty,0,0);
	TCanvas* e = new TCanvas("e","e",800,800);
	//evtempty->Draw();
	t->Draw("MBhiEvtPlanes[8]:hiEvtPlanes[8]","","COLZ");
	c->SaveAs("validhiBin.png");
	v->SaveAs("validvz.png");
	e->SaveAs("validevt.png");
	xjjroot::setgstyle();
	TH1F* djpt = new TH1F("djpt","djpt",100,0,100);
	TH1F* MBpt = new TH1F("MBpt","MBpt",100,0,100);
	TH1F* djeta = new TH1F("djeta","djeta",100,-2,2);
	TH1F* MBeta = new TH1F("MBeta","MBeta",100,-2,2);
	TH1F* djphi = new TH1F("djphi","djphi",100,-4,4);
	TH1F* MBphi = new TH1F("MBphi","MBphi",100,-4,4);
	TH2F* ptempty = new TH2F("pt",";p_{t};#frac{1}{N} #frac{dN}{dp_{t}}",100,0,100,100,pow(10,-5),.1);
	TH2F* etaempty = new TH2F("eta",";#eta;#frac{1}{N} #frac{dN}{d#eta}",100,-2,2,100,0,.05);
	TH2F* phiempty = new TH2F("phi",";#phi;#frac{1}{N} #frac{dN}{d#phi}",100,-4,4,100,0,.03);
	t->Draw("jetpt_akpu3pf>>djpt","jetpt_akpu3pf>20 && fabs(jeteta_akpu3pf)<1.6","0");
	t->Draw("jeteta_akpu3pf>>djeta","jetpt_akpu3pf>20 && fabs(jeteta_akpu3pf)<1.6","0");
	t->Draw("jetphi_akpu3pf>>djphi","jetpt_akpu3pf>20 && fabs(jeteta_akpu3pf)<1.6","0");
	t->Draw("MBjetpt_akpu3pf>>MBpt","MBjetpt_akpu3pf>20 && fabs(MBjeteta_akpu3pf)<1.6","0");
	t->Draw("MBjeteta_akpu3pf>>MBeta","MBjetpt_akpu3pf>20 && fabs(MBjeteta_akpu3pf)<1.6","0");
	t->Draw("MBjetphi_akpu3pf>>MBphi","MBjetpt_akpu3pf>20 && fabs(MBjeteta_akpu3pf)<1.6","0");
	djpt->Sumw2();
	MBpt->Sumw2();
	djeta->Sumw2();
	MBeta->Sumw2();
	djphi->Sumw2();
	MBphi->Sumw2();
	djpt->Scale(1./djpt->GetEntries());
	MBpt->Scale(1./MBpt->GetEntries());
	djeta->Scale(1./djeta->GetEntries());
	MBeta->Scale(1./MBeta->GetEntries());
	djphi->Scale(1./djphi->GetEntries());
	MBphi->Scale(1./MBphi->GetEntries());
	TCanvas* p = new TCanvas("p","p",800,800);
	p->SetLogy();
	xjjroot::sethempty(ptempty,0,0.39);
	ptempty->Draw();
	xjjroot::setthgrstyle(djpt,kBlack,20,1.2,kBlack,20,1,-1,-1,-1);
	xjjroot::setthgrstyle(MBpt,kBlue,21,1.2,kBlue,20,1,-1,-1,-1);
	djpt->Draw("PE same");
	MBpt->Draw("PE same");
	TLegend* lp = new TLegend(0.75,0.75,0.95,0.9);\
	xjjroot::setleg(lp,0.04);
	lp->AddEntry(djpt,"Djet","lp");
	lp->AddEntry(MBpt,"MB","lp");
	lp->Draw("same");
	p->SaveAs("validpt.png");
	TCanvas* et = new TCanvas("et","et",800,800);
	xjjroot::sethempty(etaempty,0,0.39);
	etaempty->Draw();
	xjjroot::setthgrstyle(djeta,kBlack,20,1.2,kBlack,20,1,-1,-1,-1);
	xjjroot::setthgrstyle(MBeta,kBlue,21,1.2,kBlue,20,1,-1,-1,-1);
	djeta->Draw("PE same");
	MBeta->Draw("PE same");
	TLegend* le = new TLegend(0.75,0.75,0.95,0.9);\
	xjjroot::setleg(le,0.04);
	le->AddEntry(djeta,"Djet","lp");
	le->AddEntry(MBeta,"MB","lp");
	le->Draw("same");
	et->SaveAs("valideta.png");
	TCanvas* ph = new TCanvas("ph","ph",800,800);
	xjjroot::sethempty(phiempty,0,0.39);
	phiempty->Draw();
	xjjroot::setthgrstyle(djphi,kBlack,20,1.2,kBlack,20,1,-1,-1,-1);
	xjjroot::setthgrstyle(MBphi,kBlue,21,1.2,kBlue,20,1,-1,-1,-1);
	djphi->Draw("PE same");
	MBphi->Draw("PE same");
	TLegend* lph = new TLegend(0.75,0.75,0.95,0.9);\
	xjjroot::setleg(lph,0.04);
	lph->AddEntry(djphi,"Djet","lp");
	lph->AddEntry(MBphi,"MB","lp");
	lph->Draw("same");
	ph->SaveAs("validphi.png");
}