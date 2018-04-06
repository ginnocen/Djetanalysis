#include "djtana.h"

void djtana_plotratio(TString inputhistname, TString outputname,
                      Int_t isMC,
                      Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                      Int_t plotwosub = 0)
{
  int arguerr();
  if(arguerr()) return;

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plotratio")) return;

  // preparation
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      // Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999?Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  std::vector<float> vdrBins, vzBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  std::vector<TH1F**> hSignalXsubRatio  = {(TH1F**)ahSignalRsubRatio};
  std::vector<TH1F**> hSignalXnormRatio  = {(TH1F**)ahSignalRnormRatio};
  std::vector<TString> xtitle  = {"r"};
  std::vector<TString> ytitle  = {isMC?"#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}_{P+H}/#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}_{P}":"#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}_{PbPb}/#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}_{pp}"};
  std::vector<TString> tname  = {"dr"};
  std::vector<std::vector<float>> vxBins  = {vdrBins};
  Float_t yaxismin = isMC?0.5:0, yaxismax = isMC?1.5:5.e+0;

  // plot
  for(int k=0;k<1;k++)
    {
      TCanvas* c = new TCanvas("c", "", 600, 600);
      // if(!isMC) c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yaxismin, yaxismax);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->GetXaxis()->SetNdivisions(505);
      hempty->Draw();
      xjjroot::drawline(vxBins[k].front(), 1, vxBins[k].back(), 1, kGray+2, 2, 2);
      TLegend* leg = new TLegend(0.53, 0.88-nPtBins*0.06*(1+plotwosub), 0.85, 0.88);
      xjjroot::setleg(leg);
      for(int i=0;i<nPtBins;i++)
        {
          xjjroot::setthgrstyle((hSignalXsubRatio.at(k))[i], amcolor[i], amstyle[0][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
          (hSignalXsubRatio.at(k))[i]->Draw("pe same");
          TString tleg = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
          leg->AddEntry((hSignalXsubRatio.at(k))[i], tleg.Data(), "p");

          if(plotwosub)
            {
              xjjroot::setthgrstyle((hSignalXnormRatio.at(k))[0*nPtBins+i], amcolor[i], amstyle[1][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              (hSignalXnormRatio.at(k))[0*nPtBins+i]->Draw("pe same");
              leg->AddEntry((hSignalXnormRatio.at(k))[0*nPtBins+i], "before bkg sub", "p");
            }

          xjjroot::drawCMS("");
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
          texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          if(k) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "#DeltaR < 0.3");
        }
      leg->Draw();
      c->SaveAs(Form("plotratios/cratio_%s_%s.pdf",tname[k].Data(),outputname.Data()));
      delete leg;
      delete hempty;
      delete c;
    }
}

int main(int argc, char* argv[])
{
  if(argc==8)
    {
      djtana_plotratio(argv[1], argv[2], atoi(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_plotratio()"<<std::endl;
      return 1;
    }
}

int arguerr()
{
  return 0;
}

