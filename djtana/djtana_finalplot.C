#include "djtana.h"

void djtana_finalplot(TString inputnamePP, TString inputnamePbPb, TString inputnameRatio, TString outputname,
                      Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                      Int_t plotPYTHIA=0, TString inputnamePYTHIA="")
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

  // TFile* infhistPYTHIA;
  if(plotPYTHIA)
    {
      if(createhists("pythia")) return;
      TFile* infhistPYTHIA = new TFile(Form("%s.root",inputnamePYTHIA.Data()));
      // infhistPYTHIA = new TFile(Form("%s.root",inputnamePYTHIA.Data()));
      if(!infhistPYTHIA->IsOpen()) return;
      if(gethists(infhistPYTHIA, "pythia")) return;
      for(int i=0;i<nPtBins;i++) 
        { 
          ahSignalRsubRatioPYTHIA[i]->Divide(ahSignalRsubP[1][i], ahSignalRsubPYTHIA[i]);
          ahSignalRsubRatioPYTHIAMe[i]->Divide(ahSignalRsubMeP[1][i], ahSignalRsubPYTHIA[i]);
        }
    }

  if(djtsyst::initsyst(jetptmin, jetptmax)) return;
  std::vector<TString> tname = {"", "_Me"};
  std::vector<TH1F**> hSignalXsubP = {(TH1F**)ahSignalRsubP, (TH1F**)ahSignalRsubMeP};
  std::vector<TH1F**> hSignalXsubRatio = {(TH1F**)ahSignalRsubRatio, (TH1F**)ahSignalRsubRatioMe};
  std::vector<TH1F**> hSignalXsubRatioPYTHIA = {(TH1F**)ahSignalRsubRatioPYTHIA, (TH1F**)ahSignalRsubRatioPYTHIAMe};
  std::vector<TGraphErrors**> gSignalXsubP = {(TGraphErrors**)agSignalRsubP, (TGraphErrors**)agSignalRsubMeP};
  std::vector<TGraphErrors**> gSignalXsubRatio = {(TGraphErrors**)agSignalRsubRatio, (TGraphErrors**)agSignalRsubRatioMe};
  std::vector<TGraphErrors**> gSignalXsubRatioPYTHIA = {(TGraphErrors**)agSignalRsubRatioPYTHIA, (TGraphErrors**)agSignalRsubRatioPYTHIAMe};

  for(int i=0;i<nPtBins;i++)
    {
      Float_t ax[nDrBins], aex[nDrBins], ayPYTHIA[nDrBins], aeyPYTHIA[nDrBins];
      for(int j=0;j<nDrBins;j++)
        {
          ax[j] = (drBins[j+1]+drBins[j]) / 2.;
          aex[j] = (drBins[j+1]-drBins[j]) / 2.;
          if(plotPYTHIA)
            {
              ayPYTHIA[j] = ahSignalRsubPYTHIA[i]->GetBinContent(j+1);
              aeyPYTHIA[j] = ahSignalRsubPYTHIA[i]->GetBinError(j+1);
            }
        }
      agSignalRsubPYTHIA[i] = new TGraphErrors(nDrBins, ax, ayPYTHIA, aex, aeyPYTHIA);
      agSignalRsubPYTHIA[i]->SetName(Form("agSignalRsubPYTHIA_%d",i));
      for(int l=0;l<2;l++)
        {
          if((hSignalXsubP.at(l))[1*nPtBins+i]->GetBinContent(nDrBins)<=0 || !l)
            {
              (hSignalXsubP.at(l))[1*nPtBins+i]->SetBinContent(nDrBins, 1.e-10);
              (hSignalXsubRatio.at(l))[i]->SetBinContent(nDrBins, -10);
            }
          Float_t ayPP[nDrBins], ayPbPb[nDrBins], ayRatio[nDrBins], ayRatioPYTHIA[nDrBins], aeyPP[nDrBins], aeyPbPb[nDrBins], aeyRatio[nDrBins], aeyRatioPYTHIA[nDrBins];
          for(int j=0;j<nDrBins;j++)
            {
              ax[j] = (drBins[j+1]+drBins[j]) / 2.;
              aex[j] = (drBins[j+1]-drBins[j]) / 2.;
              ayPP[j] = (hSignalXsubP.at(l))[0*nPtBins+i]->GetBinContent(j+1);
              aeyPP[j] = ayPP[j] * djtsyst::getsyst(i, j, "pp");
              ayPbPb[j] = (hSignalXsubP.at(l))[1*nPtBins+i]->GetBinContent(j+1);
              aeyPbPb[j] = ayPbPb[j] * djtsyst::getsyst(i, j, "PbPb");
              ayRatio[j] = (hSignalXsubRatio.at(l))[i]->GetBinContent(j+1);
              aeyRatio[j] = ayRatio[j] * djtsyst::getsyst(i, j, "ratio");
              if(plotPYTHIA)
                {
                  ayRatioPYTHIA[j] = (hSignalXsubRatioPYTHIA.at(l))[i]->GetBinContent(j+1);
                  aeyRatioPYTHIA[j] = ayRatioPYTHIA[j] * djtsyst::getsyst(i, j, "PbPb");
                }
            }
          (gSignalXsubP.at(l))[0*nPtBins+i] = new TGraphErrors(nDrBins, ax, ayPP, aex, aeyPP);
          (gSignalXsubP.at(l))[0*nPtBins+i]->SetName(Form("agSignalRsubPP_%d%s",i,tname[l].Data()));
          (gSignalXsubP.at(l))[1*nPtBins+i] = new TGraphErrors(nDrBins, ax, ayPbPb, aex, aeyPbPb);
          (gSignalXsubP.at(l))[1*nPtBins+i]->SetName(Form("agSignalRsubPbPb_%d%s",i,tname[l].Data()));
          (gSignalXsubRatio.at(l))[i] = new TGraphErrors(nDrBins, ax, ayRatio, aex, aeyRatio);
          (gSignalXsubRatio.at(l))[i]->SetName(Form("agSignalRsubRatio_%d%s",i,tname[l].Data()));
          if(plotPYTHIA)
            {
              (gSignalXsubRatioPYTHIA.at(l))[i] = new TGraphErrors(nDrBins, ax, ayRatioPYTHIA, aex, aeyRatioPYTHIA);
              (gSignalXsubRatioPYTHIA.at(l))[i]->SetName(Form("agSignalRsubRatioPYTHIA_%d%s",i,tname[l].Data()));
            }
        }
    }
  //
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999?Form("%s < |p_{T}^{jet}| < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("|p_{T}^{jet}| > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);
  Float_t yaxismin[] = {2.e-3, 2.e-3}; 
  Float_t yaxismax[] = {5.e+3, 5.e+3};
  Float_t ypaddiv = 2./3, yPullpaddiv = 1-ypaddiv;

  for(int l=0;l<2;l++)
    {
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

          xjjroot::setthgrstyle((hSignalXsubP.at(l))[1*nPtBins+i], fmcolor[1], fmstyle[1], 1.2, fmcolor[1], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle((gSignalXsubP.at(l))[1*nPtBins+i], fmcolor[1], fmstyle[1], 1.2, 0, 1, 1, ffcolor[1], 0.7, 1001);
          (gSignalXsubP.at(l))[1*nPtBins+i]->Draw("2 same");
          (hSignalXsubP.at(l))[1*nPtBins+i]->Draw("pe same");
          leg->AddEntry((gSignalXsubP.at(l))[1*nPtBins+i], fleg[1], "pf");

          xjjroot::setthgrstyle((hSignalXsubP.at(l))[0*nPtBins+i], fmcolor[0], fmstyle[0], 1.2, fmcolor[0], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle((gSignalXsubP.at(l))[0*nPtBins+i], fmcolor[0], fmstyle[0], 1.2, 0, 1, 1, ffcolor[0], 0.7, 1001);
          (gSignalXsubP.at(l))[0*nPtBins+i]->Draw("2 same");
          (hSignalXsubP.at(l))[0*nPtBins+i]->Draw("pe same");
          leg->AddEntry((gSignalXsubP.at(l))[0*nPtBins+i], fleg[0], "pf");

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
          TH2F* hemptyPull = new TH2F("hemptyPull", ";r;PbPb / pp", 5, drBins[0], drBins[nDrBins], 10, 0, 4.2);
          hemptyPull->GetXaxis()->SetNdivisions(505);
          hemptyPull->GetYaxis()->SetNdivisions(505);
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
          xjjroot::setthgrstyle((hSignalXsubRatio.at(l))[i], kBlack, fmstyle[1], 1.2, kBlack, 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle((gSignalXsubRatio.at(l))[i], kBlack, fmstyle[1], 1.2, 0, 1, 1, kGray+1, 0.7, 1001);
          (gSignalXsubRatio.at(l))[i]->Draw("2 same");
          (hSignalXsubRatio.at(l))[i]->Draw("pe same");
          if(l || jetetamin>=0.3)c->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s%s.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str(),tname[l].Data()));

          delete leg;
          delete hemptyPull;
          delete hempty;
          delete pPull;
          delete pXsec;
          delete c;

          vectex.pop_back();
        }
    }

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
      TLegend* leg = new TLegend(0.65, 0.85-(2+2*int(jetetamin>=0.3)+plotPYTHIA)*0.06, 1.1, 0.85);
      xjjroot::setleg(leg);

      (gSignalXsubP.at(1))[1*nPtBins+i]->Draw("2 same");
      (hSignalXsubP.at(1))[1*nPtBins+i]->Draw("pe same");
      leg->AddEntry((gSignalXsubP.at(1))[1*nPtBins+i], fleg[1], "pf");

      (gSignalXsubP.at(1))[0*nPtBins+i]->Draw("2 same");
      (hSignalXsubP.at(1))[0*nPtBins+i]->Draw("pe same");
      leg->AddEntry((gSignalXsubP.at(1))[0*nPtBins+i], fleg[0], "pf");

      if(jetetamin>=0.3)
        {
          xjjroot::setthgrstyle((hSignalXsubP.at(0))[1*nPtBins+i], kViolet-7, fmstyle[1]+4, 1.2, kViolet-7, 1, 1, -1, -1, -1);
          (hSignalXsubP.at(0))[1*nPtBins+i]->Draw("pe same");
          leg->AddEntry((hSignalXsubP.at(0))[1*nPtBins+i], Form("%s #eta-ref", fleg[1].Data()), "p");
          xjjroot::setthgrstyle((hSignalXsubP.at(0))[0*nPtBins+i], kViolet-7, fmstyle[0]+4, 1.2, kViolet-7, 1, 1, -1, -1, -1);
          (hSignalXsubP.at(0))[0*nPtBins+i]->Draw("pe same");
          leg->AddEntry((hSignalXsubP.at(0))[0*nPtBins+i], Form("%s #eta-ref", fleg[0].Data()), "p");
        }
      if(plotPYTHIA)
        {
          xjjroot::setthgrstyle(ahSignalRsubPYTHIA[i], fmcolor[2], fmstyle[2], 1.2, fmcolor[2], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(agSignalRsubPYTHIA[i], fmcolor[2], fmstyle[2], 1.2, 0, 1, 1, ffcolor[2], 0.7, 1001);
          agSignalRsubPYTHIA[i]->Draw("2 same");
          ahSignalRsubPYTHIA[i]->Draw("pe same");
          leg->AddEntry(agSignalRsubPYTHIA[i], fleg[2], "pf");
        }

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
      TH2F* hemptyPull = new TH2F("hemptyPull", ";r;PbPb / pp", 5, drBins[0], drBins[nDrBins], 10, 0, 4.2);
      hemptyPull->GetXaxis()->SetNdivisions(505);
      hemptyPull->GetYaxis()->SetNdivisions(505);
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
      xjjroot::setthgrstyle((hSignalXsubRatio.at(1))[i], kBlack, fmstyle[1], 1.2, kBlack, 1, 1, -1, -1, -1);
      xjjroot::setthgrstyle((gSignalXsubRatio.at(1))[i], kBlack, fmstyle[1], 1.2, 0, 1, 1, kGray+1, 0.7, 1001);
      (gSignalXsubRatio.at(1))[i]->Draw("2 same");
      (hSignalXsubRatio.at(1))[i]->Draw("pe same");
      if(jetetamin >= 0.3)
        {
          xjjroot::setthgrstyle((hSignalXsubRatio.at(0))[i], kViolet-7, fmstyle[1]+4, 1.2, kViolet-7, 1, 1, -1, -1, -1);
          (hSignalXsubRatio.at(0))[i]->Draw("pe same");
        }
      if(plotPYTHIA)
        {
          xjjroot::setthgrstyle((hSignalXsubRatioPYTHIA.at(1))[i], fmcolor[2], fmstyle[2], 1.2, fmcolor[2], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle((gSignalXsubRatioPYTHIA.at(1))[i], fmcolor[2], fmstyle[2], 1.2, 0, 1, 1, ffcolor[2], 0.7, 1001);
          // (gSignalXsubRatioPYTHIA.at(1))[i]->Draw("2 same");
          (hSignalXsubRatioPYTHIA.at(1))[i]->Draw("pe same");
        }
      TLegend* legPull = new TLegend(0.21, 0.95-(1+int(jetetamin>=0.3)+plotPYTHIA)*0.09, 0.55, 0.95);
      xjjroot::setleg(legPull, 0.09);
      legPull->AddEntry((hSignalXsubRatio.at(1))[i], "event-mixing", "p");
      legPull->AddEntry((hSignalXsubRatioPYTHIA.at(1))[i], "PbPb / PYTHIA", "p");
      if(jetetamin >= 0.3) legPull->AddEntry((hSignalXsubRatio.at(0))[i], "#eta-ref", "p");
      legPull->Draw();
      if(jetetamin>=0.3) c->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s_comp.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));

      delete legPull;
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
  if(argc == 11)
    {
      djtana_finalplot(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atoi(argv[9]), argv[10]);
      return 0;
    }
  if(argc == 9)
    {
      djtana_finalplot(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
      return 0;
    }
  std::cout<<"error: invalid parameter number - djtana_finalplot"<<std::endl;
  return 1;
}
