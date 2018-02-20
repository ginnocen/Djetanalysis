#include "jetffscale.h"

void jetffscale_plothist(TString inputhistname, TString inputscale, TString outputname,
                         TString collisionsyst, Int_t plotCorr=0)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);

  xjjroot::setgstyle();

  if(createhists("plothist")) return;
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;
  TFile* infscale = new TFile(Form("%s.root",inputscale.Data()));
  if(!infscale->IsOpen()) return;
  if(gethists(infscale, "plothistscale")) return;

  TH2F* hemptyScaleNpfPt = new TH2F("hemptyScaleNpfPt", Form(";%s;#mu(p_{T}^{reco} / p_{T}^{gen})", ispp?"nPF":"nCS"), 10, minJtnpfBins, maxJtnpfBins, 10, ispp?0.8:0.8, ispp?1.2:1.4);
  xjjroot::sethempty(hemptyScaleNpfPt, 0, 0.4);
  Float_t vfitmin[nJtptBins] = {0., 0., 2., 4., 4., 4.,     4., 4.,   4., 4.,   4., 4., 4., 4.,     4., 4., 4., 4.,     2., 2., 2., 2., 2., 2., 2., 2.,         5., 5., 5.};
  Float_t vfitmax[nJtptBins] = {6., 8., 10., 15., 15., 15., 18., 18., 20., 20., 20., 20., 25., 25., 28., 27., 28., 28., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30.};
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* c32 = new TCanvas("c32", "", 1600, 800);
      c32->Divide(8, 4);
      std::vector<TF1*>* afScaleNpfPt = new std::vector<TF1*>(nJtptBins);
      for(int i=0;i<nJtptBins;i++)
        {
          TString texpt = Form("%s < p_{T}^{reco jet} < %s", xjjc::number_remove_zero(jtptBins[i]).c_str(), xjjc::number_remove_zero(jtptBins[i+1]).c_str());
          Float_t fitmin = vfitmin[i], fitmax = vfitmax[i];
          c32->cd(i+1);
          hemptyScaleNpfPt->Draw();
          xjjroot::setthgrstyle(hScaleNpfPt[k][i], kBlack, 24, 1., kBlack, 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(hScaleNpfPtCorr[k][i], kRed+2, 24, 1., kRed+2, 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(hvScalePt[k][i], kOrange-9, -1, -1, -1, -1, -1, -1, -1, -1);
          if(plotCorr) xjjroot::drawbox(minJtnpfBins, 0.95, maxJtnpfBins, 1.05, kGray, 0.4, 1001);
          xjjroot::drawline(minJtnpfBins, 1.0, maxJtnpfBins, 1.0, kGray+3, 2, 3);
          if(!plotCorr) xjjroot::drawbox(minJtnpfBins, hScalePt[k]->GetBinContent(i+1)-hScalePt[k]->GetBinError(i+1), maxJtnpfBins, hScalePt[k]->GetBinContent(i+1)+hScalePt[k]->GetBinError(i+1), kGreen-2, 0.4, 1001);
          if(!plotCorr) xjjroot::drawline(minJtnpfBins, hScalePt[k]->GetBinContent(i+1), maxJtnpfBins, hScalePt[k]->GetBinContent(i+1), kGreen+3, 6, 2);
          else xjjroot::drawline(minJtnpfBins, hScalePtCorr[k]->GetBinContent(i+1), maxJtnpfBins, hScalePtCorr[k]->GetBinContent(i+1), kGreen+3, 6, 2);
          if(plotCorr)
            hvScalePt[k][i]->Draw("same");

          hScaleNpfPt[k][i]->Draw("same pe");
          afScaleNpfPt->at(i) = new TF1(Form("fScaleNpfPt%d",i), "[1]*(x-[0])", minJtnpfBins, maxJtnpfBins);
          afScaleNpfPt->at(i)->SetParameter(0, 20);
          afScaleNpfPt->at(i)->SetParameter(1, -0.12);
          afScaleNpfPt->at(i)->SetLineWidth(2);
          afScaleNpfPt->at(i)->SetLineColor(kAzure-6);
          afScaleNpfPt->at(i)->SetLineStyle(1);
          hScaleNpfPt[k][i]->Fit(Form("fScaleNpfPt%d",i), "L q", "", fitmin, fitmax/*maxJtnpfBins*/);
          hScaleNpfPt[k][i]->Fit(Form("fScaleNpfPt%d",i), "m q", "", fitmin, fitmax/*maxJtnpfBins*/);
          hScaleNpfPt[k][i]->Fit(Form("fScaleNpfPt%d",i), "m q", "", fitmin, fitmax/*maxJtnpfBins*/);
          hScaleP0NpfPt[k]->SetBinContent(i+1, afScaleNpfPt->at(i)->GetParameter(0));
          hScaleP0NpfPt[k]->SetBinError(i+1, afScaleNpfPt->at(i)->GetParError(0));
          hScaleP1NpfPt[k]->SetBinContent(i+1, afScaleNpfPt->at(i)->GetParameter(1));
          hScaleP1NpfPt[k]->SetBinError(i+1, afScaleNpfPt->at(i)->GetParError(1));
          if(plotCorr)
            hScaleNpfPtCorr[k][i]->Draw("same pe");              
          xjjroot::drawCMS(collisionsyst); 
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6");
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texpt.Data());
          if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
        }
      TLegend* leg = new TLegend();
      TH1F* thleg = new TH1F("thleg", "", 10, 0, 10);
      xjjroot::setthgrstyle(thleg, -1, -1, -1, kOrange-9, -1, -1, kOrange-9, -1, 1001);
      if(nJtptBins < 40)
        {
          c32->cd(nJtptBins+1);
          Float_t texxpos = 0.03, texypos = 0.90, texdypos = 0.13; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), collisionsyst, 0.13);
          if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent, 0.13);
          leg = new TLegend(0.00, 0.67-(2+(int)plotCorr)*0.18, 0.89, 0.67);
          xjjroot::setleg(leg, 0.13);
          leg->AddEntry(hScaleNpfPt[0][0], "Pre-Corr", "pl");
          leg->AddEntry(afScaleNpfPt->at(0), "Linear fit", "l");
          if(plotCorr)
            {
              leg->AddEntry(hScaleNpfPtCorr[0][0], "Corrected", "pl");
              leg->AddEntry(thleg, "Scales applied", "f");
            }
          leg->Draw();
        }
      c32->SaveAs(Form("plotresos/cScaleNpfPt%s_%s_%d.pdf",(plotCorr?"Corr":""),outputname.Data(),k));
      delete afScaleNpfPt;
      delete leg;
      delete thleg;
      delete c32;
    }
  TFile* outf = new TFile(Form("rootfiles/scalepar_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("plothist")) return;
  outf->Write();
  outf->Close();
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      jetffscale_plothist(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]));
      return 0;
    }
  else if(argc==5)
    {
      jetffscale_plothist(argv[1], argv[2], argv[3], argv[4]);
      return 0;
    }
  return 1;
}

int arguerr(TString collisionsyst)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  return 0;
}
