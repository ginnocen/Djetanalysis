#include "jetresolution.h"

void jetreso_plothist(TString inputhistname, TString outputname,
                      TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  setnCentBins(ispp);

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePt = new TCanvas("cScalePt", "", 600, 600);
      TH2F* hemptyScalePt = new TH2F("hemptyScalePt", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", 10, jtptBins[0], jtptBins[nJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePt, 0, 0.4);
      hemptyScalePt->Draw();
      TLegend* legScalePt = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePt);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          xjjroot::setthgrstyle(hScalePt[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePt[k][j]->Draw("same pe");
          TString tleg = j==0?"Incl. #eta":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePt->AddEntry(hScalePt[k][j], tleg.Data(), "p");
        }
      TF1* fScalePt = new TF1("fScalePt", "[0]+[1]/TMath::Sqrt(x)+[2]/x", jtptBins[0], jtptBins[nJtptBins]);
      fScalePt->SetParameter(0, 1);
      fScalePt->SetParameter(1, 0);
      fScalePt->SetParameter(2, 0.5);
      // if(ispp) fScalePt->FixParameter(3, 0);
      fScalePt->SetLineWidth(3);
      fScalePt->SetLineColor(kGray+3);
      fScalePt->SetLineStyle(2);
      hScalePt[k][0]->Fit("fScalePt", "L q", "", jtptBins[0], jtptBins[nJtptBins]);
      hScalePt[k][0]->Fit("fScalePt", "m", "", jtptBins[0], jtptBins[nJtptBins]);
      xjjroot::drawtex(0.22, 0.2, Form("%.2f%s%.2f/#sqrt{x}%s%.2f/x",fScalePt->GetParameter(0),fScalePt->GetParameter(1)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(1)),fScalePt->GetParameter(2)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(2))));
      xjjroot::drawCMS(collisionsyst); 
      legScalePt->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      cScalePt->SaveAs(Form("plotresos/cScalePt_%s_%d.pdf",outputname.Data(),k));
      delete fScalePt;
      delete legScalePt;
      delete hemptyScalePt;
      delete cScalePt;
    }

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePtCorr = new TCanvas("cScalePtCorr", "", 600, 600);
      TH2F* hemptyScalePtCorr = new TH2F("hemptyScalePtCorr", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, jtptBins[0], jtptBins[nJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtCorr, 0, 0.4);
      hemptyScalePtCorr->Draw();
      TLegend* legScalePtCorr = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtCorr);
      xjjroot::drawline(jtptBins[0], 1.02, jtptBins[nJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(jtptBins[0], 0.98, jtptBins[nJtptBins], 0.98, kGray+3, 2, 3);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          xjjroot::setthgrstyle(hScalePtCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePtCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"Incl. #eta":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePtCorr->AddEntry(hScalePtCorr[k][j], tleg.Data(), "p");
        } 
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtCorr->Draw();
      cScalePtCorr->SaveAs(Form("plotresos/cScalePtCorr_%s_%d.pdf",outputname.Data(),k));
      delete legScalePtCorr;
      delete hemptyScalePtCorr;
      delete cScalePtCorr;
    }

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPt = new TCanvas("cResoPt", "", 600, 600);
      TH2F* hemptyResoPt = new TH2F("hemptyResoPt", ";Gen jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen})", 10, jtptBins[0], jtptBins[nJtptBins], 10, 0, 0.4);
      xjjroot::sethempty(hemptyResoPt, 0, 0.4);
      hemptyResoPt->Draw();
      TLegend* legResoPt = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPt);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          xjjroot::setthgrstyle(hResoPt[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPt[k][j]->Draw("same pe");
          TString tleg = j==0?"Incl. #eta":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPt->AddEntry(hResoPt[k][j], tleg.Data(), "p");
        }
      TF1* fResoPt = new TF1("fResoPt", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", jtptBins[0], jtptBins[nJtptBins]);
      fResoPt->SetParameter(0, 0.06);
      // if(ispp) fResoPt->SetParameter(0, 0.06);
      // else fResoPt->FixParameter(0, 0.073);
      fResoPt->SetParameter(1, 0.95);
      // if(ispp || k==(nCentBins-1)) fResoPt->SetParameter(1, 0.95);
      // else fResoPt->FixParameter(1, 1.141);
      if(ispp || k==(nCentBins-1)) fResoPt->FixParameter(2, 0);
      fResoPt->SetLineWidth(3);
      fResoPt->SetLineColor(kGray+3);
      fResoPt->SetLineStyle(2);
      hResoPt[k][0]->Fit("fResoPt", "L q", "", jtptBins[0], jtptBins[nJtptBins]);
      hResoPt[k][0]->Fit("fResoPt", "m q", "", jtptBins[0], jtptBins[nJtptBins]);
      xjjroot::drawCMS(collisionsyst);
      legResoPt->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPt->GetParameter(0)),TMath::Abs(fResoPt->GetParameter(1)),TMath::Abs(fResoPt->GetParameter(2))));
      cResoPt->SaveAs(Form("plotresos/cResoPt_%s_%d.pdf",outputname.Data(),k));
      delete fResoPt;
      delete legResoPt;
      delete hemptyResoPt;
      delete cResoPt;
    }

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPtCorr = new TCanvas("cResoPtCorr", "", 600, 600);
      TH2F* hemptyResoPtCorr = new TH2F("hemptyResoPtCorr", ";Gen jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, jtptBins[0], jtptBins[nJtptBins], 10, 0, 0.4);
      xjjroot::sethempty(hemptyResoPtCorr, 0, 0.4);
      hemptyResoPtCorr->Draw();
      TLegend* legResoPtCorr = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPtCorr);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          xjjroot::setthgrstyle(hResoPtCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPtCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"Incl. #eta":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPtCorr->AddEntry(hResoPtCorr[k][j], tleg.Data(), "p");
        }
      TF1* fResoPtCorr = new TF1("fResoPtCorr", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", jtptBins[0], jtptBins[nJtptBins]);
      fResoPtCorr->SetParameter(0, 0.06);
      // if(ispp) fResoPtCorr->SetParameter(0, 0.06);
      // else fResoPtCorr->FixParameter(0, 0.082);
      fResoPtCorr->SetParameter(1, 0.95);
      // if(ispp || k==(nCentBins-1)) fResoPtCorr->SetParameter(1, 0.95);
      // else fResoPtCorr->FixParameter(1, 1.091);
      if(ispp || k==(nCentBins-1)) fResoPtCorr->FixParameter(2, 0);
      fResoPtCorr->SetLineWidth(3);
      fResoPtCorr->SetLineColor(kGray+3);
      fResoPtCorr->SetLineStyle(2);
      hResoPtCorr[k][0]->Fit("fResoPtCorr", "L q", "", jtptBins[0], jtptBins[nJtptBins]);
      hResoPtCorr[k][0]->Fit("fResoPtCorr", "m q", "", jtptBins[0], jtptBins[nJtptBins]);
      xjjroot::drawCMS(collisionsyst);
      legResoPtCorr->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPtCorr->GetParameter(0)),TMath::Abs(fResoPtCorr->GetParameter(1)),TMath::Abs(fResoPtCorr->GetParameter(2))));
      cResoPtCorr->SaveAs(Form("plotresos/cResoPtCorr_%s_%d.pdf",outputname.Data(),k));
      delete fResoPtCorr;
      delete legResoPtCorr;
      delete hemptyResoPtCorr;
      delete cResoPtCorr;
    }

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPhi = new TCanvas("cResoPhi", "", 600, 600);
      TH2F* hemptyResoPhi = new TH2F("hemptyResoPhi", ";Gen jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", 10, jtptBins[0], jtptBins[nJtptBins], 10, 0, ispp?0.02:0.05);
      xjjroot::sethempty(hemptyResoPhi, 0, 0.4);
      hemptyResoPhi->Draw();
      TLegend* legResoPhi = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPhi);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          xjjroot::setthgrstyle(hResoPhi[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPhi[k][j]->Draw("same pe");
          TString tleg = j==0?"Incl. #eta":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPhi->AddEntry(hResoPhi[k][j], tleg.Data(), "p");
        }
      TF1* fResoPhi = new TF1("fResoPhi", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", jtptBins[0], jtptBins[nJtptBins]);
      fResoPhi->SetParameter(0, 0.006);
      fResoPhi->SetParameter(1, 0.1);
      if(ispp) fResoPhi->FixParameter(2, 0);
      fResoPhi->SetLineWidth(3);
      fResoPhi->SetLineColor(kGray+3);
      fResoPhi->SetLineStyle(2);
      hResoPhi[k][0]->Fit("fResoPhi", "L q", "", jtptBins[0], jtptBins[nJtptBins]);
      hResoPhi[k][0]->Fit("fResoPhi", "m q", "", jtptBins[0], jtptBins[nJtptBins]);
      xjjroot::drawCMS(collisionsyst);
      legResoPhi->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPhi->GetParameter(0)),TMath::Abs(fResoPhi->GetParameter(1)),TMath::Abs(fResoPhi->GetParameter(2))));
      cResoPhi->SaveAs(Form("plotresos/cResoPhi_%s_%d.pdf",outputname.Data(),k));
      delete fResoPhi;
      delete legResoPhi;
      delete hemptyResoPhi;
      delete cResoPhi;
    }

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoEta = new TCanvas("cResoEta", "", 600, 600);
      TH2F* hemptyResoEta = new TH2F("hemptyResoEta", ";Gen jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", 10, jtptBins[0], jtptBins[nJtptBins], 10, 0, ispp?0.02:0.05);
      xjjroot::sethempty(hemptyResoEta, 0, 0.4);
      hemptyResoEta->Draw();
      TLegend* legResoEta = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoEta);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          xjjroot::setthgrstyle(hResoEta[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoEta[k][j]->Draw("same pe");
          TString tleg = j==0?"Incl. #eta":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoEta->AddEntry(hResoEta[k][j], tleg.Data(), "p");
        }
      TF1* fResoEta = new TF1("fResoEta", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", jtptBins[0], jtptBins[nJtptBins]);
      fResoEta->SetParameter(0, 0.006);
      fResoEta->SetParameter(1, 0.1);
      if(ispp) fResoEta->FixParameter(2, 0);
      fResoEta->SetLineWidth(3);
      fResoEta->SetLineColor(kGray+3);
      fResoEta->SetLineStyle(2);
      hResoEta[k][0]->Fit("fResoEta", "L q", "", jtptBins[0], jtptBins[nJtptBins]);
      hResoEta[k][0]->Fit("fResoEta", "m q", "", jtptBins[0], jtptBins[nJtptBins]);
      xjjroot::drawCMS(collisionsyst);
      legResoEta->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoEta->GetParameter(0)),TMath::Abs(fResoEta->GetParameter(1)),TMath::Abs(fResoEta->GetParameter(2))));
      cResoEta->SaveAs(Form("plotresos/cResoEta_%s_%d.pdf",outputname.Data(),k));
      delete fResoEta;
      delete legResoEta;
      delete hemptyResoEta;
      delete cResoEta;
    }
}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      jetreso_plothist(argv[1], argv[2], argv[3]);
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
