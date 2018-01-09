#include "jetffscale.h"

void jetffscale_plotpar(TString inputhistname, TString outputname,
                        TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plotpar")) return;

  TH2F* hemptyScaleP0NpfPt = new TH2F("hemptyScaleP0NpfPt", Form(";jet p_{T}^{reco} (GeV/c);a_{0}"), 10, jtptBins[0], jtptBins[nJtptBins], 10, ispp?50:20, ispp?400:250);
  TH2F* hemptyScaleP1NpfPt = new TH2F("hemptyScaleP1NpfPt", Form(";jet p_{T}^{reco} (GeV/c);a_{1}"), 10, jtptBins[0], jtptBins[nJtptBins], 10, ispp?-0.012:-0.05, ispp?-0.002:0);
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
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("%.3f-exp(%s%.3f%s%.3f*x)",
                                       fP0->GetParameter(0),
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
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("%.4f-exp(%s%.4f%s%.4f*x)",
                                       fP1->GetParameter(0),
                                       fP1->GetParameter(1)>=0?"+":"-",TMath::Abs(fP1->GetParameter(1)),
                                       fP1->GetParameter(2)>=0?"+":"-",TMath::Abs(fP1->GetParameter(2)))
                       );
      paramfP1[k].push_back(fP1->GetParameter(0));
      paramfP1[k].push_back(fP1->GetParameter(1));
      paramfP1[k].push_back(fP1->GetParameter(2));
      paramfP1[k].push_back(fP1->GetParameter(3));
      // paramfP1[k].push_back(0.);

      c2->SaveAs(Form("plotresos/cScaleParNpfPt_%s_%d.pdf",outputname.Data(),k));
      delete c2;
      delete fP1;
      delete fP0;
    }
  
  std::cout<<std::endl;
  std::cout<<(ispp?"std::vector<std::vector<Float_t>> paramfP0_pp = {":"std::vector<std::vector<Float_t>> paramfP0_PbPb = {");
  for(int k=0;k<nCentBins;k++)
    // std::cout<<"{"<<paramfP0[k].at(0)<<", "<<paramfP0[k].at(1)<<", "<<paramfP0[k].at(2)<<"}"<<(k==(nCentBins-1)?"};":",")<<std::endl;
    std::cout<<"{"<<paramfP0[k].at(0)<<", "<<paramfP0[k].at(1)<<", "<<paramfP0[k].at(2)<<", "<<paramfP0[k].at(3)<<"}"<<(k==(nCentBins-1)?"};":",")<<std::endl;
  std::cout<<(ispp?"std::vector<std::vector<Float_t>> paramfP1_pp = {":"std::vector<std::vector<Float_t>> paramfP1_PbPb = {");
  for(int k=0;k<nCentBins;k++)
    std::cout<<"{"<<paramfP1[k].at(0)<<", "<<paramfP1[k].at(1)<<", "<<paramfP1[k].at(2)<<", "<<paramfP1[k].at(3)<<"}"<<(k==(nCentBins-1)?"};":",")<<std::endl;
    // std::cout<<"{"<<paramfP1[k].at(0)<<", "<<paramfP1[k].at(1)<<", "<<paramfP1[k].at(2)<<"}"<<(k==(nCentBins-1)?"};":",")<<std::endl;
}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      jetffscale_plotpar(argv[1], argv[2], argv[3]);
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
