#include "djtana.h"

void djtana_corrhist(TString inputhistname, TString inputhistnameSignal, TString outputname,
                     TString collisionsyst,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  if(createhists("plothist")) return;

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;
  TFile* infhistSignal = new TFile(Form("%s.root",inputhistnameSignal.Data()));
  if(!infhistSignal->IsOpen()) return;

  TH1F* ahSignalRSignalref[nPtBins];
  TH1F* ahSignalRPHsubCorr[nPtBins];
  for(int i=0;i<nPtBins;i++)
    {
      ahSignalRSignalref[i] = (TH1F*)infhistSignal->Get(Form("hSignalRPH_%s_%d",tRef[1].Data(),i));
      ahSignalRSignalref[i]->SetName(Form("hSignalRSignalref_%d",i));
      ahSignalRPHsubCorr[i] = (TH1F*)ahSignalRPHsub[i]->Clone(Form("hSignalRPHsubCorr_%d",i));
      ahSignalRPHsubCorr[i]->Add(ahSignalRSignalref[i]);
    }
  // preparation
  for(int i=0;i<nPtBins;i++)
    {
      ahSignalRPH[0][i]->Scale(1, "width");
      ahSignalRPH[1][i]->Scale(1, "width");
      ahSignalRP[i]->Scale(1, "width");
      ahSignalRPHsub[i]->Scale(1, "width");
      ahSignalRPHbkg[i]->Scale(1, "width");
      ahSignalRPHsubCorr[i]->Scale(1, "width");
      ahSignalRatio[i]->Divide(ahSignalRPHsubCorr[i], ahSignalRP[i]);
    }

  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };

  // Float_t yaxismin = 1.1e-5, yaxismax = 1.e+3;
  Float_t ypaddiv = 2./3, yPullpaddiv = 1-ypaddiv;

  for(int i=0;i<nPtBins;i++)
    {
      Float_t yaxismin = ahSignalRPH[1][i]->GetBinContent(1) / 5.;
      Float_t yaxismax = ahSignalRPH[0][i]->GetBinContent(1) * 50.;
      TCanvas* c = new TCanvas("c", "", 600, 800);
      TPad* pXsec = new TPad("pXsec", "", 0, 1-ypaddiv, 1, 1);
      pXsec->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
      pXsec->Draw();
      pXsec->cd();
      pXsec->SetLogy();
      TH2F* hempty = new TH2F("hempty", ";#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}", 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0);
      hempty->Draw();
      TLegend* leg = new TLegend(0.58, 0.88-2*0.055, 0.90, 0.88);
      xjjroot::setleg(leg);

      // xjjroot::setthgrstyle(ahSignalRPH[0][i], kRed-9, 24, 1.2, kRed-9, 2, 1, -1, -1, -1);
      // ahSignalRPH[0][i]->Draw("pe same");
      // xjjroot::setthgrstyle(ahSignalRPH[1][i], kRed-9, 25, 1.2, kRed-9, 1, 1, -1, -1, -1);
      // ahSignalRPH[1][i]->Draw("pe same");
      xjjroot::setthgrstyle(ahSignalRP[i], kBlack, 25, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahSignalRP[i]->Draw("pe same");
      xjjroot::setthgrstyle(ahSignalRPHsubCorr[i], kRed+3, 20, 1.2, kRed+3, 1, 1, -1, -1, -1);
      ahSignalRPHsubCorr[i]->Draw("pe same");
      // xjjroot::setthgrstyle(ahSignalRPHbkg[i], kBlack, 20, 1.2, kBlack, 1, 1, -1, -1, -1);
      // ahSignalRPHbkg[i]->Draw("pe same");

      // leg->AddEntry(ahSignalRPH[0][i], "regular cone", "p");
      leg->AddEntry(ahSignalRP[i], "subid = 0", "p");
      leg->AddEntry(ahSignalRPHsub[i], "bkg sub Corr", "p");
      // leg->AddEntry(ahSignalRPHbkg[i], "real bkg", "p");
      // leg->AddEntry(ahSignalRPH[1][i], "#eta-reflected cone", "p");

      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      TString tpt = ptBins[i+1]>=999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), tpt.Data());
      leg->Draw();

      c->cd();
      TPad* pPull = new TPad("pPull", "", 0, 0, 1, yPullpaddiv);
      pPull->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0.07*1/yPullpaddiv, 0);
      pPull->Draw();
      pPull->cd();
      TH2F* hemptyPull = new TH2F("hemptyPull", ";r;bkg sub / subid=0", 5, drBins[0], drBins[nDrBins], 10, 0, 2);
      hemptyPull->GetXaxis()->SetNdivisions(505);
      hemptyPull->GetYaxis()->SetNdivisions(504);
      xjjroot::sethempty(hemptyPull, -0.5, -0);
      hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv));
      hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv) *(1+1.8));
      hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv) *(1+12));
      hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv));
      hemptyPull->Draw();
      xjjroot::drawbox(drBins[0], 0.90, drBins[nDrBins], 1.10, kGray, 0.4);
      xjjroot::drawline(drBins[0], 1.00, drBins[nDrBins], 1.00, kGray+2, 2, 4);
      xjjroot::setthgrstyle(ahSignalRatio[i], kRed+3, 20, 1.2, kRed+3, 1, 1, -1, -1, -1);
      ahSignalRatio[i]->Draw("pe same");

      c->SaveAs(Form("plotbkgsub/cbkgclosureCorr_xsec_dr_%s_pt_%s_%s.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));

      delete leg;
      delete hemptyPull;
      delete hempty;
      delete pPull;
      delete pXsec;
      delete c;
    }
}

int main(int argc, char* argv[])
{
  if(argc==8)
    {
      djtana_corrhist(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_corrhist()"<<std::endl;
      return 1;
    }
}


