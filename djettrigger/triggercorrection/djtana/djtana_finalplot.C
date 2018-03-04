#include "djtana.h"

void djtana_finalplot(TString inputnamePP, TString inputnamePbPb, TString inputnameRatio, TString outputname,
                      Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  xjjroot::setgstyle();

  TFile* infhistPP = new TFile(Form("%s.root",inputnamePP.Data()));
  if(!infhistPP->IsOpen()) return;
  if(gethists(infhistPP, "saveratiopp")) return;
  TFile* infhistPbPb = new TFile(Form("%s.root",inputnamePbPb.Data()));
  if(!infhistPbPb->IsOpen()) return;
  if(gethists(infhistPbPb, "saveratiopbpb")) return;
  TFile* infhistRatio = new TFile(Form("%s.root",inputnameRatio.Data()));
  if(!infhistRatio->IsOpen()) return;
  if(gethists(infhistRatio, "plotratio")) return;

  for(int i=0;i<nPtBins;i++)
    {
      Float_t ax[nDrBins], ayPP[nDrBins], ayPbPb[nDrBins], ayRatio[nDrBins], aex[nDrBins], aeyPP[nDrBins], aeyPbPb[nDrBins], aeyRatio[nDrBins];
      for(int j=0;j<nDrBins;j++)
        {
          ax[j] = (drBins[j+1]+drBins[j]) / 2.;
          aex[j] = (drBins[j+1]-drBins[j]) / 2.;
          ayPP[j] = ahSignalRsubP[0][i]->GetBinContent(j+1);
          aeyPP[j] = ayPP[j] * djtsyst::getsyst(i, j, "pp");
          ayPbPb[j] = ahSignalRsubP[1][i]->GetBinContent(j+1);
          aeyPbPb[j] = ayPbPb[j] * djtsyst::getsyst(i, j, "PbPb");
          ayRatio[j] = ahSignalRsubRatio[i]->GetBinContent(j+1);
          aeyRatio[j] = ayRatio[j] * djtsyst::getsyst(i, j, "ratio");
        }
      agSignalRsubP[0][i] = new TGraphErrors(nDrBins, ax, ayPP, aex, aeyPP);
      agSignalRsubP[0][i]->SetName(Form("agSignalRsubPP_%d",i));
      agSignalRsubP[1][i] = new TGraphErrors(nDrBins, ax, ayPbPb, aex, aeyPbPb);
      agSignalRsubP[1][i]->SetName(Form("agSignalRsubPbPb_%d",i));
      agSignalRsubRatio[i] = new TGraphErrors(nDrBins, ax, ayRatio, aex, aeyRatio);
      agSignalRsubRatio[i]->SetName(Form("agSignalRsubRatio_%d",i));
    }
  //
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };

  Float_t yaxismin[nPtBins] = {2.e-2, 2.e-3}; 
  Float_t yaxismax[nPtBins] = {5.e+2, 5.e+3};
  Float_t ypaddiv = 2./3, yPullpaddiv = 1-ypaddiv;

  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]>900?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      vectex.push_back(texpt);

      TCanvas* c = new TCanvas("c", "", 600, 800);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      TPad* pXsec = new TPad("pXsec", "", 0, 1-ypaddiv, 1, 1);
      pXsec->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
      pXsec->Draw();
      pXsec->cd();
      pXsec->SetLogy();
      TH2F* hempty = new TH2F("hempty", ";r;#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}", 5, drBins[0], drBins[nDrBins], 10, yaxismin[i], yaxismax[i]);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.2);
      hempty->Draw();
      TLegend* leg = new TLegend(0.65, 0.85-2*0.065, 1.1, 0.85);
      xjjroot::setleg(leg);

      xjjroot::setthgrstyle(ahSignalRsubP[1][i], fmcolor[1], fmstyle[1], 1.2, fmcolor[1], 1, 1, -1, -1, -1);
      xjjroot::setthgrstyle(agSignalRsubP[1][i], fmcolor[1], fmstyle[1], 1.2, 0, 1, 1, ffcolor[1], 0.5, 1001);
      agSignalRsubP[1][i]->Draw("2 same");
      ahSignalRsubP[1][i]->Draw("pe same");
      leg->AddEntry(agSignalRsubP[1][i], fleg[1], "pf");

      xjjroot::setthgrstyle(ahSignalRsubP[0][i], fmcolor[0], fmstyle[0], 1.2, fmcolor[0], 1, 1, -1, -1, -1);
      xjjroot::setthgrstyle(agSignalRsubP[0][i], fmcolor[0], fmstyle[0], 1.2, 0, 1, 1, ffcolor[0], 0.5, 1001);
      agSignalRsubP[0][i]->Draw("2 same");
      ahSignalRsubP[0][i]->Draw("pe same");
      leg->AddEntry(agSignalRsubP[0][i], fleg[0], "pf");

      xjjroot::drawCMS("");
      Float_t texxpos = 0.24, texypos = 0.84, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();

      c->cd();
      TPad* pPull = new TPad("pPull", "", 0, 0, 1, yPullpaddiv);
      pPull->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0.07*1/yPullpaddiv, 0);
      pPull->Draw();
      pPull->cd();
      TH2F* hemptyPull = new TH2F("hemptyPull", ";r;PbPb / pp", 5, drBins[0], drBins[nDrBins], 10, 0, 3.2);
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

      xjjroot::drawline(drBins[0], 1, drBins[nDrBins], 1, kGray+3, 2, 2);
      xjjroot::setthgrstyle(ahSignalRsubRatio[i], kBlack, fmstyle[1], 1.2, kBlack, 1, 1, -1, -1, -1);
      xjjroot::setthgrstyle(agSignalRsubRatio[i], kBlack, fmstyle[1], 1.2, 0, 1, 1, kGray+1, 0.5, 1001);
      agSignalRsubRatio[i]->Draw("2 same");
      ahSignalRsubRatio[i]->Draw("pe same");

      c->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));

      delete leg;
      delete hemptyPull;
      delete hempty;
      delete pPull;
      delete pXsec;
      delete c;

      vectex.pop_back();
    }

}

int main(int argc, char* argv[])
{
  if(argc == 8)
    {
      djtana_finalplot(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]));
      return 0;
    }
  else
    {
      std::cout<<"error: invalid parameter number - djtana_finalplot"<<std::endl;
      return 1;
    }
}
