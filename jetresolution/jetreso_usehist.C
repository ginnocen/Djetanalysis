#include "jetresolution.h"

void jetreso_usehist(TString inputhistname, TString outputname,
                     TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "usehist")) return;

  std::vector<TString> xtitle = {";Gen jet p_{T} (GeV/c);p_{T}^{reco} / p_{T}^{gen}", 
                                 ";Gen jet p_{T} (GeV/c);#phi^{reco} - #phi^{gen}",
                                 ";Gen jet p_{T} (GeV/c);#eta^{reco} - #eta^{gen}"};
  for(int i=0;i<nJtptBins;i++)
    {
      // TF1* fPt = new TF1("fPt", "[0]*Gaus(x,[1],[2])/");
      TCanvas* cPt = new TCanvas("cPt", "", 600, 600);
      TH2F* hemptyPt = new TH2F("hemptyPt", ";p_{T}^{reco} / p_{T}^{gen};Probability", 10, 0, 2, 10, 0, 0.2);
      xjjroot::sethempty(hemptyPt, 0, 0.4);
      hemptyPt->Draw();
      ahHistoResoPt[i]->Scale(1./ahHistoResoPt[i]->Integral());
      xjjroot::setthgrstyle(ahHistoResoPt[i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahHistoResoPt[i]->Draw("same pe");
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]));
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      xjjroot::drawCMS(collisionsyst);
      cPt->SaveAs(Form("plotpulls/cfitPt_%s_%d.pdf",outputname.Data(),i));

      TCanvas* cPhi = new TCanvas("cPhi", "", 600, 600);
      TH2F* hemptyPhi = new TH2F("hemptyPhi", ";#phi^{reco} - #phi^{gen};Probability", 10, -0.08, 0.08, 10, 0, 0.3);
      xjjroot::sethempty(hemptyPhi, 0, 0.4);
      hemptyPhi->GetXaxis()->SetNdivisions(505);
      hemptyPhi->Draw();
      ahHistoResoPhi[i]->Scale(1./ahHistoResoPhi[i]->Integral());
      xjjroot::setthgrstyle(ahHistoResoPhi[i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahHistoResoPhi[i]->Draw("same pe");
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]));
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      xjjroot::drawCMS(collisionsyst);
      cPhi->SaveAs(Form("plotpulls/cfitPhi_%s_%d.pdf",outputname.Data(),i));

      TCanvas* cEta = new TCanvas("cEta", "", 600, 600);
      TH2F* hemptyEta = new TH2F("hemptyEta", ";#eta^{reco} - #eta^{gen};Probability", 10, -0.08, 0.08, 10, 0, 0.3);
      xjjroot::sethempty(hemptyEta, 0, 0.4);
      hemptyEta->GetXaxis()->SetNdivisions(505);
      hemptyEta->Draw();
      ahHistoResoEta[i]->Scale(1./ahHistoResoEta[i]->Integral());
      xjjroot::setthgrstyle(ahHistoResoEta[i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahHistoResoEta[i]->Draw("same pe");
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]));
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      xjjroot::drawCMS(collisionsyst);
      cEta->SaveAs(Form("plotpulls/cfitEta_%s_%d.pdf",outputname.Data(),i));

      delete hemptyEta;
      delete cEta;
      delete hemptyPhi;
      delete cPhi;
      delete hemptyPt;
      delete cPt;
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
