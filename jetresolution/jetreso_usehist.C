#include "jetresolution.h"

void jetreso_usehist(TString inputhistname, TString outputname,
                     TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  xjjroot::setgstyle();

  if(createhists("usehist")) return;
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "usehist")) return;

  for(int j=0;j<nJtetaBins+1;j++)
    {
      TString texjteta = j==0?"Incl. #eta":Form("%.1f < |#eta^{gen jet}| < %.1f", jtetaBins[j-1], jtetaBins[j]);
      for(int i=0;i<nJtptBins;i++)
        {
          TString texjtpt = Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]);

          TF1* fPt = new TF1("fPt", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", 0, 2);
          fPt->SetLineWidth(3);
          fPt->SetLineColor(kBlue);
          fPt->SetParLimits(2, 0, 1);
          fPt->SetParameter(0, 1);
          fPt->SetParameter(1, 1);
          fPt->SetParameter(2, 0.2);
          TCanvas* cPt = new TCanvas("cPt", "", 600, 600);
          TH2F* hemptyPt = new TH2F("hemptyPt", ";p_{T}^{reco} / p_{T}^{gen};Probability", 10, 0, 2, 10, 0, 0.2);
          xjjroot::sethempty(hemptyPt, 0, 0.4);
          hemptyPt->Draw();
          ahHistoResoPt[j][i]->Scale(1./ahHistoResoPt[j][i]->Integral());
          xjjroot::setthgrstyle(ahHistoResoPt[j][i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
          ahHistoResoPt[j][i]->Draw("same pe");
          ahHistoResoPt[j][i]->Fit("fPt", "L q", "", 0, 2);
          ahHistoResoPt[j][i]->Fit("fPt", "m q", "", 0, 2);
          Float_t sigmaPt = fPt->GetParameter(2);
          TF1* fPt1 = new TF1("fPt1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", 0, 2);
          fPt1->SetParameter(0, fPt->GetParameter(0));
          fPt1->SetParameter(1, fPt->GetParameter(1));
          fPt1->SetParameter(2, fPt->GetParameter(2));
          fPt1->SetLineWidth(3);
          fPt1->SetLineColor(kRed);
          fPt1->Draw("same");
          ahHistoResoPt[j][i]->Fit("fPt", "L q", "", 1-sigmaPt, 1+sigmaPt);
          ahHistoResoPt[j][i]->Fit("fPt", "m q", "", 1-sigmaPt, 1+sigmaPt);
          fPt->Draw("same");
          hScalePt[j]->SetBinContent(i+1, fPt->GetParameter(1));
          hScalePt[j]->SetBinError(i+1, fPt->GetParError(1));
          hResoPt[j]->SetBinContent(i+1, fPt->GetParameter(2));
          hResoPt[j]->SetBinError(i+1, fPt->GetParError(2));
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
          texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fPt->GetParameter(1), fPt->GetParError(1)));
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fPt->GetParameter(2), fPt->GetParError(2)));
          xjjroot::drawCMS(collisionsyst);
          cPt->SaveAs(Form("plotpulls/cfitPt_%s_%d_%d.pdf",outputname.Data(),j,i));

          TF1* fPtCorr = new TF1("fPtCorr", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", 0, 2);
          fPtCorr->SetLineWidth(3);
          fPtCorr->SetLineColor(kBlue);
          fPtCorr->SetParLimits(2, 0, 1);
          fPtCorr->SetParameter(0, 1);
          fPtCorr->SetParameter(1, 1);
          fPtCorr->SetParameter(2, 0.2);
          TCanvas* cPtCorr = new TCanvas("cPtCorr", "", 600, 600);
          TH2F* hemptyPtCorr = new TH2F("hemptyPtCorr", ";p_{T}^{reco} / p_{T}^{gen};Probability", 10, 0, 2, 10, 0, 0.2);
          xjjroot::sethempty(hemptyPtCorr, 0, 0.4);
          hemptyPtCorr->Draw();
          ahHistoResoPtCorr[j][i]->Scale(1./ahHistoResoPtCorr[j][i]->Integral());
          xjjroot::setthgrstyle(ahHistoResoPtCorr[j][i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
          ahHistoResoPtCorr[j][i]->Draw("same pe");
          ahHistoResoPtCorr[j][i]->Fit("fPtCorr", "L q", "", 0, 2);
          ahHistoResoPtCorr[j][i]->Fit("fPtCorr", "m q", "", 0, 2);
          Float_t sigmaPtCorr = fPtCorr->GetParameter(2);
          TF1* fPtCorr1 = new TF1("fPtCorr1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", 0, 2);
          fPtCorr1->SetParameter(0, fPtCorr->GetParameter(0));
          fPtCorr1->SetParameter(1, fPtCorr->GetParameter(1));
          fPtCorr1->SetParameter(2, fPtCorr->GetParameter(2));
          fPtCorr1->SetLineWidth(3);
          fPtCorr1->SetLineColor(kRed);
          fPtCorr1->Draw("same");
          ahHistoResoPtCorr[j][i]->Fit("fPtCorr", "L q", "", 1-sigmaPtCorr, 1+sigmaPtCorr);
          ahHistoResoPtCorr[j][i]->Fit("fPtCorr", "m q", "", 1-sigmaPtCorr, 1+sigmaPtCorr);
          fPtCorr->Draw("same");
          hScalePtCorr[j]->SetBinContent(i+1, fPtCorr->GetParameter(1));
          hScalePtCorr[j]->SetBinError(i+1, fPtCorr->GetParError(1));
          texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
          texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fPtCorr->GetParameter(1), fPtCorr->GetParError(1)));
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fPtCorr->GetParameter(2), fPtCorr->GetParError(2)));
          xjjroot::drawCMS(collisionsyst);
          cPtCorr->SaveAs(Form("plotpulls/cfitPtCorr_%s_%d_%d.pdf",outputname.Data(),j,i));

          TF1* fPhi = new TF1("fPhi", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
          fPhi->SetLineWidth(3);
          fPhi->SetLineColor(kBlue);
          fPhi->SetParameter(0, 0.01);
          fPhi->SetParameter(1, 0);
          fPhi->SetParameter(2, 0.01);
          TCanvas* cPhi = new TCanvas("cPhi", "", 600, 600);
          TH2F* hemptyPhi = new TH2F("hemptyPhi", ";#phi^{reco} - #phi^{gen};Probability", 10, -0.08, 0.08, 10, 0, 0.3);
          xjjroot::sethempty(hemptyPhi, 0, 0.4);
          hemptyPhi->GetXaxis()->SetNdivisions(505);
          hemptyPhi->Draw();
          ahHistoResoPhi[j][i]->Scale(1./ahHistoResoPhi[j][i]->Integral());
          xjjroot::setthgrstyle(ahHistoResoPhi[j][i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
          ahHistoResoPhi[j][i]->Draw("same pe");
          ahHistoResoPhi[j][i]->Fit("fPhi", "L q", "", -0.08, 0.08);
          ahHistoResoPhi[j][i]->Fit("fPhi", "m q", "", -0.08, 0.08);
          Float_t sigmaPhi = fPhi->GetParameter(2);
          TF1* fPhi1 = new TF1("fPhi1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
          fPhi1->SetParameter(0, fPhi->GetParameter(0));
          fPhi1->SetParameter(1, fPhi->GetParameter(1));
          fPhi1->SetParameter(2, fPhi->GetParameter(2));
          fPhi1->SetLineWidth(3);
          fPhi1->SetLineColor(kRed);
          fPhi1->Draw("same");
          ahHistoResoPhi[j][i]->Fit("fPhi", "L q", "", 0-sigmaPhi, 0+sigmaPhi);
          ahHistoResoPhi[j][i]->Fit("fPhi", "m q", "", 0-sigmaPhi, 0+sigmaPhi);
          fPhi->Draw("same");
          hResoPhi[j]->SetBinContent(i+1, fPhi->GetParameter(2));
          hResoPhi[j]->SetBinError(i+1, fPhi->GetParError(2));
          texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
          texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fPhi->GetParameter(1), fPhi->GetParError(1)));
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fPhi->GetParameter(2), fPhi->GetParError(2)));
          xjjroot::drawCMS(collisionsyst);
          cPhi->SaveAs(Form("plotpulls/cfitPhi_%s_%d_%d.pdf",outputname.Data(),j,i));

          TF1* fEta = new TF1("fEta", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
          fEta->SetLineWidth(3);
          fEta->SetLineColor(kBlue);
          fEta->SetParameter(0, 0.01);
          fEta->SetParameter(1, 0);
          fEta->SetParameter(2, 0.01);
          TCanvas* cEta = new TCanvas("cEta", "", 600, 600);
          TH2F* hemptyEta = new TH2F("hemptyEta", ";#phi^{reco} - #phi^{gen};Probability", 10, -0.08, 0.08, 10, 0, 0.3);
          xjjroot::sethempty(hemptyEta, 0, 0.4);
          hemptyEta->GetXaxis()->SetNdivisions(505);
          hemptyEta->Draw();
          ahHistoResoEta[j][i]->Scale(1./ahHistoResoEta[j][i]->Integral());
          xjjroot::setthgrstyle(ahHistoResoEta[j][i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
          ahHistoResoEta[j][i]->Draw("same pe");
          ahHistoResoEta[j][i]->Fit("fEta", "L q", "", -0.08, 0.08);
          ahHistoResoEta[j][i]->Fit("fEta", "m q", "", -0.08, 0.08);
          Float_t sigmaEta = fEta->GetParameter(2);
          TF1* fEta1 = new TF1("fEta1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
          fEta1->SetParameter(0, fEta->GetParameter(0));
          fEta1->SetParameter(1, fEta->GetParameter(1));
          fEta1->SetParameter(2, fEta->GetParameter(2));
          fEta1->SetLineWidth(3);
          fEta1->SetLineColor(kRed);
          fEta1->Draw("same");
          ahHistoResoEta[j][i]->Fit("fEta", "L q", "", 0-sigmaEta, 0+sigmaEta);
          ahHistoResoEta[j][i]->Fit("fEta", "m q", "", 0-sigmaEta, 0+sigmaEta);
          fEta->Draw("same");
          hResoEta[j]->SetBinContent(i+1, fEta->GetParameter(2));
          hResoEta[j]->SetBinError(i+1, fEta->GetParError(2));
          texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
          texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fEta->GetParameter(1), fEta->GetParError(1)));
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fEta->GetParameter(2), fEta->GetParError(2)));
          xjjroot::drawCMS(collisionsyst);
          cEta->SaveAs(Form("plotpulls/cfitEta_%s_%d_%d.pdf",outputname.Data(),j,i));

          delete hemptyEta;
          delete cEta;
          delete fEta;
          delete fEta1;
          delete hemptyPhi;
          delete cPhi;
          delete fPhi;
          delete fPhi1;
          delete hemptyPt;
          delete cPt;
          delete fPt;
          delete fPt1;
          delete hemptyPtCorr;
          delete cPtCorr;
          delete fPtCorr;
          delete fPtCorr1;
        }
    }
  TFile* outf = new TFile(Form("rootfiles/reso_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("usehist")) return;
  outf->Write();
  outf->Close();
}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      jetreso_usehist(argv[1], argv[2], argv[3]);
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
