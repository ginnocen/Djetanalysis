#include "studySigma.h"

void studySigma_plothist(TString inputname, TString collisionsyst)
{
  xjjroot::setgstyle();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  Int_t ispp = collisionsyst=="pp"?1:0;

  TFile* inf = new TFile(Form("%s.root",inputname.Data()));
  if(gethists(inf, "plothist")) return;
  hDpt_MC->Scale(1./hDpt_MC->GetBinContent(nPtBins));
  hDpt_MC_weight->Scale(1./hDpt_MC_weight->GetBinContent(nPtBins));
  hDpt_data->Scale(1./hDpt_data->GetBinContent(nPtBins));
  hDpt_Ratio->Divide(hDpt_MC, hDpt_data);
  hDpt_Ratio_weight->Divide(hDpt_MC_weight, hDpt_data);

  Float_t axcenter[nPtBins], axlow[nPtBins], axhigh[nPtBins], aycenter_MC[nPtBins], ayerr_MC[nPtBins], aycenter_data[nPtBins], ayerr_data[nPtBins], aycenter_Ratio[nPtBins], ayerr_Ratio[nPtBins], aycenter_Ratio_weight[nPtBins], ayerr_Ratio_weight[nPtBins];
  for(int i=0;i<nPtBins;i++)
    {
      Float_t weightcenter = 0;
      Float_t norm = 0;
      for(int j=ptBins[i]*2;j<ptBins[i+1]*2;j++)
        {
          weightcenter += (j/2.)*hDpt_MC_fine->GetBinContent(j+1);
          norm += hDpt_MC_fine->GetBinContent(j+1);
        }
      weightcenter /= norm;
      axcenter[i] = weightcenter;
      axlow[i] = weightcenter-ptBins[i];
      axhigh[i] = ptBins[i+1] - weightcenter;
      aycenter_MC[i] = hDpt_MC->GetBinContent(i+1);
      ayerr_MC[i] = hDpt_MC->GetBinError(i+1);
      aycenter_data[i] = hDpt_data->GetBinContent(i+1);
      ayerr_data[i] = hDpt_data->GetBinError(i+1);
      aycenter_Ratio[i] = hDpt_Ratio->GetBinContent(i+1);      
      ayerr_Ratio[i] = hDpt_Ratio->GetBinError(i+1);
      aycenter_Ratio_weight[i] = hDpt_Ratio_weight->GetBinContent(i+1);      
      ayerr_Ratio_weight[i] = hDpt_Ratio_weight->GetBinError(i+1);
    }
  TGraphAsymmErrors* gr_MC = new TGraphAsymmErrors(nPtBins, axcenter, aycenter_MC, axlow, axhigh, ayerr_MC, ayerr_MC);
  xjjroot::setthgrstyle(gr_MC, kBlack, 21, 1.2, kBlack, 1, 2);
  TGraphAsymmErrors* gr_data = new TGraphAsymmErrors(nPtBins, axcenter, aycenter_data, axlow, axhigh, ayerr_data, ayerr_data);
  xjjroot::setthgrstyle(gr_data, kAzure-3, 21, 1.2, kAzure-3, 1, 2);
  TGraphAsymmErrors* gr_Ratio = new TGraphAsymmErrors(nPtBins, axcenter, aycenter_Ratio, axlow, axhigh, ayerr_Ratio, ayerr_Ratio);
  xjjroot::setthgrstyle(gr_Ratio, kBlack, 21, 1.2, kBlack, 1, 2);
  TGraphAsymmErrors* gr_Ratio_weight = new TGraphAsymmErrors(nPtBins, axcenter, aycenter_Ratio_weight, axlow, axhigh, ayerr_Ratio_weight, ayerr_Ratio_weight);
  xjjroot::setthgrstyle(gr_Ratio_weight, kRed-3, 21, 1.2, kRed-3, 1, 2);

  TF1* f_data = new TF1("f_data", "[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)", 0, 100);
  f_data->SetLineWidth(3);
  f_data->SetLineColor(kAzure-3);
  f_data->SetParameter(1,6.91);  //best so far
  f_data->SetParameter(2,-0.72);
  f_data->SetParLimits(3,-0.01,0.05);
  f_data->SetParLimits(4,-0.01,0.0012);
  TF1* f_MC = new TF1("f_MC", "[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)", 0, 100);
  f_MC->SetLineWidth(3);
  f_MC->SetLineColor(kBlack);
  f_MC->SetParameter(1,6.91);  //best so far
  f_MC->SetParameter(2,-0.72);
  f_MC->SetParLimits(3,-0.01,0.05);
  f_MC->SetParLimits(4,-0.01,0.0012);

  Float_t ypaddiv = 1./2, yPullpaddiv = 1-ypaddiv;
  TCanvas* c = new TCanvas("c", "", 600, 1000);
  c->cd();
  TPad* pXsec = new TPad("pXsec", "", 0, 1-ypaddiv, 1, 1);
  pXsec->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
  pXsec->Draw();
  pXsec->cd();
  pXsec->SetLogy();
  TH2F* hempty = new TH2F("hempty", ";;", 10, 0, 100, 10, 1.1e-1, 1.e+8);
  hempty->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hempty, 0, 0.3);
  hempty->Draw();
  gr_data->Draw("same pe");
  gr_MC->Draw("same pe");
  // gr_data->Fit(f_data, "m", "", 0, 100);
  // gr_MC->Fit(f_MC, "m", "", 0, 100);
  TLegend* leg = new TLegend(0.58, 0.85-2*0.05, 0.90, 0.85);
  xjjroot::setleg(leg);
  leg->AddEntry(gr_MC, (ispp?"PYTHIA":"PYTHIA+HYDJET"), "pl");
  leg->AddEntry(gr_data, "HIN-16-001", "pl");
  leg->Draw();
  xjjroot::drawCMS(collisionsyst);

  c->cd();
  TPad* pPull = new TPad("pPull", "", 0, 0, 1, yPullpaddiv);
  pPull->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0.07*1/yPullpaddiv, 0);
  pPull->Draw();
  pPull->cd();
  TH2F* hemptyPull = new TH2F("hemptyPull", ";D^{0} p_{T} (GeV/c);Ratio", 10, 0, 100, 10, 0, 10.2);
  hemptyPull->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPull, -0.7, -0);
  hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv) *(1+1.8));
  hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv) *(1+12));
  hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv));
  hemptyPull->Draw();
  xjjroot::drawline(0, 1, 100, 1, kGray+2, 2, 3);
  gr_Ratio->Draw("same p");
  gr_Ratio_weight->Draw("same p");

  TF1* fpar = new TF1("fpar", (ispp?str_weightGpt_pp.Data():str_weightGpt_PbPb.Data()), 2, 100);
  fpar->SetLineWidth(3);
  fpar->SetLineStyle(2);
  fpar->SetLineColor(kAzure-5);
  fpar->Draw("same");

  TF1* f = new TF1("f", "[0]+[1]*x+[2]/x+[3]/(x*x)+[4]/TMath::Sqrt(x)", 2, 100);
  f->SetLineWidth(3);
  f->SetLineColor(kRed-7);
  gr_Ratio->Fit(f, "m", "", 2, 100);
  gr_Ratio->Fit(f, "m", "", 2, 100);
  c->SaveAs(Form("plotDpt/cDpt_%s.pdf",collisionsyst.Data()));

  std::cout<<std::endl;
  std::cout<<Form("%f%s%f*x%s%f/x%s%f/(x*x)%s%f/TMath::Sqrt(x)",
                  f->GetParameter(0),
                  (f->GetParameter(1)>=0?"+":"-"),TMath::Abs(f->GetParameter(1)),
                  (f->GetParameter(2)>=0?"+":"-"),TMath::Abs(f->GetParameter(2)),
                  (f->GetParameter(3)>=0?"+":"-"),TMath::Abs(f->GetParameter(3)),
                  (f->GetParameter(4)>=0?"+":"-"),TMath::Abs(f->GetParameter(4)))<<std::endl;
  // (f->GetParameter(5)>=0?"+":"-"),TMath::Abs(f->GetParameter(5)))<<std::endl;
  std::cout<<std::endl;
}

int main(int argc, char* argv[])
{
  if(argc==3)
    {
      studySigma_plothist(argv[1], argv[2]);
      return 0;
    }
  std::cout<<"  Error: invalid arguments number - studySigma_plothist()"<<std::endl;
  return 1;
}

int arguerr(TString collisionsyst)
{
  if(collisionsyst!="pp" && collisionsyst!="PbPb")
    {
      std::cout<<"error: invalid collisionsyst"<<std::endl;
      return 1;
    }
  return 0;
}

