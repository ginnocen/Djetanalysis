#include "jetffscale.h"

void jetffscale_plothist_comb(TString inputhistnamepp, TString inputhistnamepbpb, TString inputscalepp, TString inputscalepbpb, TString outputname,
                              Int_t plotCorr=0)
{
  xjjroot::setgstyle();

  init(1);
  TFile* infpp = new TFile(Form("%s.root",inputhistnamepp.Data()));
  if(!infpp->IsOpen()) return;
  if(gethists(infpp, "plothistpp")) return;
  TFile* infscalepp = new TFile(Form("%s.root",inputscalepp.Data()));
  if(!infscalepp->IsOpen()) return;
  if(gethists(infscalepp, "plothistscalepp")) return;

  init(0);
  TFile* infpbpb = new TFile(Form("%s.root",inputhistnamepbpb.Data()));
  if(!infpbpb->IsOpen()) return;
  if(gethists(infpbpb, "plothistpbpb")) return;
  TFile* infscalepbpb = new TFile(Form("%s.root",inputscalepbpb.Data()));
  if(!infscalepbpb->IsOpen()) return;
  if(gethists(infscalepbpb, "plothistscalepbpb")) return;

  TH2F* hemptyScaleNpfPtPP = new TH2F("hemptyScaleNpfPtPP", Form(";%s;#mu(p_{T}^{reco} / p_{T}^{gen})", "nPF"), 10, minJtnpfBins, maxJtnpfBins, 10, 0.8, 1.2);
  xjjroot::sethempty(hemptyScaleNpfPtPP, 0, 0.4);
  TH2F* hemptyScaleNpfPtPbPb = new TH2F("hemptyScaleNpfPtPbPb", Form(";%s;#mu(p_{T}^{reco} / p_{T}^{gen})", "nCS"), 10, minJtnpfBins, maxJtnpfBins, 10, 0.8, 1.4);
  Float_t vfitmin[nJtptBins] = {0., 0., 2., 4., 4., 4.,     4., 4.,   4., 4.,   4., 4., 4., 4.,     4., 4., 4., 4.,     2., 2., 2., 2., 2., 2., 2., 2.,         5., 5., 5.};
  Float_t vfitmax[nJtptBins] = {6., 8., 10., 15., 15., 15., 18., 18., 20., 20., 20., 20., 25., 25., 28., 27., 28., 28., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30.};
  for(int i=0;i<nJtptBins;i++)
    {
      TCanvas* c4 = new TCanvas("c4", "", 2400, 600);
      c4->Divide(4, 1);
      std::vector<TF1*>* afScaleNpfPt = new std::vector<TF1*>(3);
      TString texpt = Form("%s < p_{T}^{reco jet} < %s", xjjc::number_remove_zero(jtptBins[i]).c_str(), xjjc::number_remove_zero(jtptBins[i+1]).c_str());
      Float_t fitmin = vfitmin[i], fitmax = vfitmax[i];
      
      std::vector<TH1F*> vhScaleNpfPt = {hScaleNpfPtPP[0][i], hScaleNpfPtPbPb[0][i], hScaleNpfPtPbPb[1][i]};
      std::vector<TH1F*> vhScaleNpfPtCorr = {hScaleNpfPtCorrPP[0][i], hScaleNpfPtCorrPbPb[0][i], hScaleNpfPtCorrPbPb[1][i]};
      std::vector<TH2F*> vhvScalePt = {hvScalePtPP[0][i], hvScalePtPbPb[0][i], hvScalePtPbPb[1][i]};
      std::vector<Float_t> vpfP0 = {paramRealfP0_pp.at(0).at(i), paramRealfP0_PbPb.at(0).at(i), paramRealfP0_PbPb.at(1).at(i)};
      std::vector<Float_t> vpfP1 = {paramRealfP1_pp.at(0).at(i), paramRealfP1_PbPb.at(0).at(i), paramRealfP1_PbPb.at(1).at(i)};
      std::vector<TString> vcollisionsyst = {"pp", "PbPb", "PbPb"};
      std::vector<TString> vtexcent = {"", Form("Cent. %.0f - %.0f%s", centBins[0], centBins[1], "%"), Form("Cent. %.0f - %.0f%s", centBins[1], centBins[2], "%")};      
      std::vector<TH2F*> vhempty = {hemptyScaleNpfPtPP, hemptyScaleNpfPtPbPb, hemptyScaleNpfPtPbPb};
      for(int k=0;k<3;k++)
        {
          c4->cd(k+1);
          xjjroot::sethempty(vhempty[k], 0, 0.4);
          vhempty[k]->Draw();

          xjjroot::setthgrstyle(vhScaleNpfPt[k], kBlack, 24, 1., kBlack, 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(vhScaleNpfPtCorr[k], kRed+2, 24, 1., kRed+2, 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(vhvScalePt[k], kOrange-9, -1, -1, -1, -1, -1, -1, -1, -1);
          if(plotCorr) xjjroot::drawbox(minJtnpfBins, 0.95, maxJtnpfBins, 1.05, kGray, 0.4, 1001);
          xjjroot::drawline(minJtnpfBins, 1.0, maxJtnpfBins, 1.0, kGray+3, 2, 3);
          if(plotCorr)
            vhvScalePt[k]->Draw("same");
          vhScaleNpfPt[k]->Draw("same pe");
          afScaleNpfPt->at(k) = new TF1(Form("fScaleNpfPt%d",k), "[1]*(x-[0])", fitmin, fitmax);
          afScaleNpfPt->at(k)->SetParameters(vpfP0[k], vpfP1[k]);
          afScaleNpfPt->at(k)->SetLineWidth(2);
          afScaleNpfPt->at(k)->SetLineColor(kAzure-6);
          afScaleNpfPt->at(k)->SetLineStyle(1);
          afScaleNpfPt->at(k)->Draw("same");
          if(plotCorr)
            vhScaleNpfPtCorr[k]->Draw("same pe");
          xjjroot::drawCMS(vcollisionsyst[k]); 
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6");
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texpt.Data());
          if(k) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), vtexcent[k].Data());
        }

      TLegend* leg = new TLegend();
      TH1F* thleg = new TH1F("thleg", "", 10, 0, 10);
      xjjroot::setthgrstyle(thleg, -1, -1, -1, kOrange-9, -1, -1, kOrange-9, -1, 1001);
      c4->cd(4);
      Float_t texxpos = 0.03, texypos = 0.90, texdypos = 0.13; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texpt.Data(), 0.1);
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6", 0.1);
      leg = new TLegend(0.00, 0.67-(2+(int)plotCorr)*0.18, 0.89, 0.67);
      xjjroot::setleg(leg, 0.1);
      leg->AddEntry(vhScaleNpfPt[0], "Pre-Corr", "pl");
      leg->AddEntry(afScaleNpfPt->at(0), "Linear fit", "l");
      if(plotCorr)
        {
          leg->AddEntry(vhScaleNpfPtCorr[0], "Corrected", "pl");
          leg->AddEntry(thleg, "Scales applied", "f");
        }
      leg->Draw();

      c4->SaveAs(Form("plotresopts/cScaleNpfPt%s_%s_%d.pdf",(plotCorr?"Corr":""),outputname.Data(),i));

      delete afScaleNpfPt;
      delete leg;
      delete thleg;
      delete c4;
    }
}

int main(int argc, char* argv[])
{
  if(argc==7)
    {
      jetffscale_plothist_comb(argv[1], argv[2], argv[3], argv[4], argv[5], atoi(argv[6]));
      return 0;
    }
  else if(argc==6)
    {
      jetffscale_plothist_comb(argv[1], argv[2], argv[3], argv[4], argv[5]);
      return 0;
    }
  return 1;
}

