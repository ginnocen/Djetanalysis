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

  for(int i=0;i<nJtptBins;i++)
    {
      TF1* fPt = new TF1("fPt", "[0]*([3]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])+(1-[3])*Gaus(x,[4],[5])/(TMath::Sqrt(2*3.14159265)*[5]))", 0, 2);
      fPt->SetParLimits(0, 0, 1000);
      fPt->SetParLimits(3, 0, 1);
      fPt->SetParLimits(4, 0, 2);
      fPt->SetParLimits(5, 0, 0.3);
      fPt->SetParLimits(1, 0, 2);
      fPt->SetParLimits(2, 0.01, 0.1);
      fPt->SetParameter(0, 1);
      fPt->SetParameter(1, 1);
      fPt->SetParameter(2, 0.08);
      fPt->SetParameter(4, 1);
      fPt->SetParameter(5, 0.2);
      fPt->SetParameter(3, 0.5);
      fPt->SetLineWidth(3);
      TCanvas* cPt = new TCanvas("cPt", "", 600, 600);
      TH2F* hemptyPt = new TH2F("hemptyPt", ";p_{T}^{reco} / p_{T}^{gen};Probability", 10, 0, 2, 10, 0, 0.2);
      xjjroot::sethempty(hemptyPt, 0, 0.4);
      hemptyPt->Draw();
      ahHistoResoPt[i]->Scale(1./ahHistoResoPt[i]->Integral());
      xjjroot::setthgrstyle(ahHistoResoPt[i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahHistoResoPt[i]->Draw("same pe");
      ahHistoResoPt[i]->Fit("fPt", "L q", "", 0, 2);
      ahHistoResoPt[i]->Fit("fPt", "m q", "", 0, 2);
      TF1* fPt1 = new TF1("fPt1", "[0]*[3]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", 0, 2);
      fPt1->SetParameter(0, fPt->GetParameter(0));
      fPt1->SetParameter(1, fPt->GetParameter(1));
      fPt1->SetParameter(2, fPt->GetParameter(2));
      fPt1->SetParameter(3, fPt->GetParameter(3));
      fPt1->SetLineWidth(3);
      fPt1->SetLineColor(kBlue);
      fPt1->Draw("same");
      TF1* fPt2 = new TF1("fPt2", "[0]*(1-[3])*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", 0, 2);
      fPt2->SetParameter(0, fPt->GetParameter(0));
      fPt2->SetParameter(1, fPt->GetParameter(4));
      fPt2->SetParameter(2, fPt->GetParameter(5));
      fPt2->SetParameter(3, fPt->GetParameter(3));
      fPt2->SetLineWidth(3);
      fPt2->SetLineColor(kBlue);
      fPt2->Draw("same");
      fPt->Draw("same");
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]));
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      xjjroot::drawCMS(collisionsyst);
      cPt->SaveAs(Form("plotpulls/cfitPt_%s_%d.pdf",outputname.Data(),i));

      TF1* fPhi = new TF1("fPhi", "[0]*([3]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])+(1-[3])*Gaus(x,[1],[4])/(TMath::Sqrt(2*3.14159265)*[4]))", -0.08, 0.08);
      fPhi->SetParLimits(3, 0, 1);
      fPhi->SetParLimits(2, 0.01, 0.05);
      fPhi->SetParLimits(4, 0.001, 0.01);
      fPhi->SetParameter(0, 0.01);
      fPhi->SetParameter(1, 0);
      fPhi->SetParameter(2, 0.01);
      fPhi->SetParameter(4, 0.005);
      fPhi->SetParameter(3, 0.5);
      fPhi->SetLineWidth(3);
      TCanvas* cPhi = new TCanvas("cPhi", "", 600, 600);
      TH2F* hemptyPhi = new TH2F("hemptyPhi", ";#phi^{reco} - #phi^{gen};Probability", 10, -0.08, 0.08, 10, 0, 0.3);
      xjjroot::sethempty(hemptyPhi, 0, 0.4);
      hemptyPhi->GetXaxis()->SetNdivisions(505);
      hemptyPhi->Draw();
      ahHistoResoPhi[i]->Scale(1./ahHistoResoPhi[i]->Integral());
      xjjroot::setthgrstyle(ahHistoResoPhi[i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahHistoResoPhi[i]->Draw("same pe");
      ahHistoResoPhi[i]->Fit("fPhi", "L q", "", -0.08, 0.08);
      ahHistoResoPhi[i]->Fit("fPhi", "m", "", -0.08, 0.08);
      TF1* fPhi1 = new TF1("fPhi1", "[0]*[3]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
      fPhi1->SetParameter(0, fPhi->GetParameter(0));
      fPhi1->SetParameter(1, fPhi->GetParameter(1));
      fPhi1->SetParameter(2, fPhi->GetParameter(2));
      fPhi1->SetParameter(3, fPhi->GetParameter(3));
      fPhi1->SetLineWidth(3);
      fPhi1->SetLineColor(kBlue);
      fPhi1->Draw("same");
      TF1* fPhi2 = new TF1("fPhi2", "[0]*(1-[3])*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
      fPhi2->SetParameter(0, fPhi->GetParameter(0));
      fPhi2->SetParameter(1, fPhi->GetParameter(1));
      fPhi2->SetParameter(2, fPhi->GetParameter(4));
      fPhi2->SetParameter(3, fPhi->GetParameter(3));
      fPhi2->SetLineWidth(3);
      fPhi2->SetLineColor(kBlue);
      fPhi2->Draw("same");
      fPhi->Draw("same");
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]));
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      xjjroot::drawCMS(collisionsyst);
      cPhi->SaveAs(Form("plotpulls/cfitPhi_%s_%d.pdf",outputname.Data(),i));

      TF1* fEta = new TF1("fEta", "[0]*([3]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])+(1-[3])*Gaus(x,[1],[4])/(TMath::Sqrt(2*3.14159265)*[4]))", -0.08, 0.08);
      fEta->SetParLimits(3, 0, 1);
      fEta->SetParLimits(2, 0.01, 0.05);
      fEta->SetParLimits(4, 0.001, 0.01);
      fEta->SetParameter(0, 0.01);
      fEta->SetParameter(1, 0);
      fEta->SetParameter(2, 0.01);
      fEta->SetParameter(4, 0.005);
      fEta->SetParameter(3, 0.5);
      fEta->SetLineWidth(3);
      TCanvas* cEta = new TCanvas("cEta", "", 600, 600);
      TH2F* hemptyEta = new TH2F("hemptyEta", ";#eta^{reco} - #eta^{gen};Probability", 10, -0.08, 0.08, 10, 0, 0.3);
      xjjroot::sethempty(hemptyEta, 0, 0.4);
      hemptyEta->GetXaxis()->SetNdivisions(505);
      hemptyEta->Draw();
      ahHistoResoEta[i]->Scale(1./ahHistoResoEta[i]->Integral());
      xjjroot::setthgrstyle(ahHistoResoEta[i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahHistoResoEta[i]->Draw("same pe");
      ahHistoResoEta[i]->Fit("fEta", "L q", "", -0.08, 0.08);
      ahHistoResoEta[i]->Fit("fEta", "m", "", -0.08, 0.08);
      TF1* fEta1 = new TF1("fEta1", "[0]*[3]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
      fEta1->SetParameter(0, fEta->GetParameter(0));
      fEta1->SetParameter(1, fEta->GetParameter(1));
      fEta1->SetParameter(2, fEta->GetParameter(2));
      fEta1->SetParameter(3, fEta->GetParameter(3));
      fEta1->SetLineWidth(3);
      fEta1->SetLineColor(kBlue);
      fEta1->Draw("same");
      TF1* fEta2 = new TF1("fEta2", "[0]*(1-[3])*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", -0.08, 0.08);
      fEta2->SetParameter(0, fEta->GetParameter(0));
      fEta2->SetParameter(1, fEta->GetParameter(1));
      fEta2->SetParameter(2, fEta->GetParameter(4));
      fEta2->SetParameter(3, fEta->GetParameter(3));
      fEta2->SetLineWidth(3);
      fEta2->SetLineColor(kBlue);
      fEta2->Draw("same");
      fEta->Draw("same");
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]));
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      xjjroot::drawCMS(collisionsyst);
      cEta->SaveAs(Form("plotpulls/cfitEta_%s_%d.pdf",outputname.Data(),i));

      delete hemptyEta;
      delete cEta;
      delete fEta;
      delete fEta1;
      delete fEta2;
      delete hemptyPhi;
      delete cPhi;
      delete fPhi;
      delete fPhi1;
      delete fPhi2;
      delete hemptyPt;
      delete cPt;
      delete fPt;
      delete fPt1;
      delete fPt2;
    }

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
