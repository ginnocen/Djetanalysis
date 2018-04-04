#include "jetffscale.h"

void jetffscale_plotpar(TString inputhistname, TString inputcompname, TString outputname,
                        TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);
  djtcorr::setnCentBins(ispp);
  // djtcorr::init(ispp);

  xjjroot::setgstyle();

  std::vector<std::vector<Float_t>>* paramfScalePt = ispp?&paramfScalePt_pp:&paramfScalePt_PbPb;

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plotpar")) return;
  TFile* infhistcomp = new TFile(Form("%s.root",inputcompname.Data()));
  if(!infhistcomp->IsOpen()) return;
  if(gethists(infhistcomp, "plotparcomp")) return;

  TH2F* hemptyScaleP0NpfPt = new TH2F("hemptyScaleP0NpfPt", Form(";jet p_{T}^{reco} (GeV/c);a_{0}"), 10, jtptBins[0], jtptBins[nJtptBins], 10, ispp?50:20, ispp?400:250);
  TH2F* hemptyScaleP1NpfPt = new TH2F("hemptyScaleP1NpfPt", Form(";jet p_{T}^{reco} (GeV/c);a_{1}"), 10, jtptBins[0], jtptBins[nJtptBins], 10, ispp?-0.012:-0.05, ispp?-0.002:0.01);
  xjjroot::sethempty(hemptyScaleP0NpfPt, 0, 0.4);
  xjjroot::sethempty(hemptyScaleP1NpfPt, 0, 0.4);
  std::vector<std::vector<Float_t>> paramfP0(nCentBins);
  std::vector<std::vector<Float_t>> paramfP1(nCentBins);
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      Float_t fitmin = (k==0)?40:30;
      Float_t fitmax = 300;
      xjjroot::setthgrstyle(hScaleP0NpfPt[k], kAzure-6, 24, 1.2, kAzure-6, 1, 1, -1, -1, -1);
      xjjroot::setthgrstyle(hScaleP1NpfPt[k], kAzure-6, 24, 1.2, kAzure-6, 1, 1, -1, -1, -1);
      TF1* fP0 = new TF1("fP0", "[0]+[3]*x-exp([1]+[2]*x)", jtptBins[0], jtptBins[nJtptBins]);
      fP0->SetLineWidth(3);
      fP0->SetLineColor(kOrange-9);
      fP0->SetLineStyle(1);
      TF1* fP1 = new TF1("fP1", "[0]+[3]*x-exp([1]+[2]*x)", jtptBins[0], jtptBins[nJtptBins]);
      fP1->SetLineWidth(3);
      fP1->SetLineColor(kOrange-9);
      fP1->SetLineStyle(1);
      TCanvas* c2 = new TCanvas("c2", "", 600, 1200);
      c2->Divide(1, 2);

      c2->cd(1);
      hemptyScaleP0NpfPt->Draw();
      hScaleP0NpfPt[k]->Draw("same ep");
      fP0->SetParameter(0, 200);
      fP0->SetParLimits(3, 0, 1);
      hScaleP0NpfPt[k]->Fit("fP0", "L q", "", fitmin, fitmax);
      hScaleP0NpfPt[k]->Fit("fP0", "m q", "", fitmin, fitmax);
      hScaleP0NpfPt[k]->Fit("fP0", "m q", "", fitmin, fitmax);
      xjjroot::drawCMS(collisionsyst); 
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6");
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), ispp?"nPF p_{T} > 2 GeV":"nCS p_{T} > 2 GeV");
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("%.3f%s%.3f*x-exp(%s%.3f%s%.3f*x)",
                                       fP0->GetParameter(0),
                                       fP0->GetParameter(3)>=0?"+":"-",TMath::Abs(fP0->GetParameter(3)),
                                       fP0->GetParameter(1)>=0?"+":"-",TMath::Abs(fP0->GetParameter(1)),
                                       fP0->GetParameter(2)>=0?"+":"-",TMath::Abs(fP0->GetParameter(2)))
                       );
      paramfP0[k].push_back(fP0->GetParameter(0));
      paramfP0[k].push_back(fP0->GetParameter(1));
      paramfP0[k].push_back(fP0->GetParameter(2));
      paramfP0[k].push_back(fP0->GetParameter(3));

      c2->cd(2);
      hemptyScaleP1NpfPt->Draw();
      hScaleP1NpfPt[k]->Draw("same ep");
      fP1->SetParameter(0, -0.005);
      fP1->SetParLimits(0, -1, 0);
      fP1->SetParLimits(2, -0.1, 0);
      hScaleP1NpfPt[k]->Fit("fP1", "L q", "", fitmin, fitmax);
      hScaleP1NpfPt[k]->Fit("fP1", "m q", "", fitmin, fitmax);
      hScaleP1NpfPt[k]->Fit("fP1", "m q", "", fitmin, fitmax);
      xjjroot::drawCMS(collisionsyst); 
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6");
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), ispp?"nPF p_{T} > 2 GeV":"nCS p_{T} > 2 GeV");
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("%.4f%s%.4f*x-exp(%s%.4f%s%.4f*x)",
                                       fP1->GetParameter(0),
                                       fP1->GetParameter(3)>=0?"+":"-",TMath::Abs(fP1->GetParameter(3)),
                                       fP1->GetParameter(1)>=0?"+":"-",TMath::Abs(fP1->GetParameter(1)),
                                       fP1->GetParameter(2)>=0?"+":"-",TMath::Abs(fP1->GetParameter(2)))
                       );
      paramfP1[k].push_back(fP1->GetParameter(0));
      paramfP1[k].push_back(fP1->GetParameter(1));
      paramfP1[k].push_back(fP1->GetParameter(2));
      paramfP1[k].push_back(fP1->GetParameter(3));

      c2->SaveAs(Form("plotresos/cScaleParNpfPt_%s_%d.pdf",outputname.Data(),k));
      delete c2;
      delete fP1;
      delete fP0;

      TCanvas* c1 = new TCanvas("c1", "", 600, 600);
      TH2F* hempty = new TH2F("hempty", ";jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", 10, jtptBins[0], jtptBins[nJtptBins], 10, 0.9, 1.3);
      xjjroot::sethempty(hempty, 0, 0.4);
      hempty->Draw();
      TF1* fscale = new TF1("fscale", "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", jtptBins[0], jtptBins[nJtptBins]);
      fscale->SetParameters(paramfScalePt->at(k).at(0), paramfScalePt->at(k).at(1), paramfScalePt->at(k).at(2), paramfScalePt->at(k).at(3));
      fscale->SetLineColor(kAzure+3);
      fscale->SetLineStyle(1);
      fscale->SetLineWidth(3);
      fscale->Draw("same");
      xjjroot::setthgrstyle(hScalePt[k], kRed+3, 24, 1.2, kRed+3, 1, 1);
      hScalePt[k]->Draw("same ep");
      xjjroot::drawCMS(collisionsyst);
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{jet}| < 1.6");
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      TLegend* leg = new TLegend(0.60, 0.88-0.06*2, 0.90, 0.88);
      xjjroot::setleg(leg);
      leg->AddEntry(hScalePt[k], "vs. reco jet p_{T}", "pl");
      leg->AddEntry(fscale, "vs. gen jet p_{T}", "l");
      leg->Draw();
      c1->SaveAs(Form("plotresos/cScaleRecovsGen_%s_%d.pdf",outputname.Data(),k));
      delete leg;
      delete fscale;
      delete hempty;
      delete c1;
    }  
  
  std::cout<<std::endl;
  std::cout<<(ispp?"std::vector<std::vector<Float_t>> paramfP0_pp = {":"std::vector<std::vector<Float_t>> paramfP0_PbPb = {");
  for(int k=0;k<nCentBins;k++)
    std::cout<<"{"<<paramfP0[k].at(0)<<", "<<paramfP0[k].at(1)<<", "<<paramfP0[k].at(2)<<", "<<paramfP0[k].at(3)<<"}"<<(k==(nCentBins-1)?"};":",")<<std::endl;
  std::cout<<(ispp?"std::vector<std::vector<Float_t>> paramfP1_pp = {":"std::vector<std::vector<Float_t>> paramfP1_PbPb = {");
  for(int k=0;k<nCentBins;k++)
    std::cout<<"{"<<paramfP1[k].at(0)<<", "<<paramfP1[k].at(1)<<", "<<paramfP1[k].at(2)<<", "<<paramfP1[k].at(3)<<"}"<<(k==(nCentBins-1)?"};":",")<<std::endl;

  std::cout<<std::endl;
  std::cout<<std::string(30, '>')<<std::endl;
  std::cout<<"std::vector<std::vector<Float_t>> paramRealfP0"<<(ispp?"_pp":"_PbPb")<<" = {";
  for(int k=0;k<nCentBins;k++)
    {
      std::cout<<"{";
      for(int i=0;i<nJtptBins;i++)
        {
          std::cout<<hScaleP0NpfPt[k]->GetBinContent(i+1)<<(i==(nJtptBins-1)?"}":", ");
        }
      std::cout<<(k==(nCentBins-1)?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<std::vector<Float_t>> paramRealfP1"<<(ispp?"_pp":"_PbPb")<<" = {";
  for(int k=0;k<nCentBins;k++)
    {
      std::cout<<"{";
      for(int i=0;i<nJtptBins;i++)
        {
          std::cout<<hScaleP1NpfPt[k]->GetBinContent(i+1)<<(i==(nJtptBins-1)?"}":", ");
        }
      std::cout<<(k==(nCentBins-1)?"};":",")<<std::endl;
    }
  std::cout<<std::string(30, '<')<<std::endl;

}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      jetffscale_plotpar(argv[1], argv[2], argv[3], argv[4]);
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
