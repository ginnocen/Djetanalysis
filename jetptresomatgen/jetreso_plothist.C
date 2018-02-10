#include "jetresolution.h"

Int_t hidemuleta = 1;
void jetreso_plothist(TString inputhistname, TString outputname,
                      TString collisionsyst, Int_t verboseonplot=0)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  setnCentBins(ispp);

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;

  TString paramfname[5] = {"ScalePt", "ResoPt", "ResoPtCorr", "ResoPhi", "ResoEta"};
  std::vector<std::vector<std::vector<Float_t>>*> paramf(5);
  for(int i=0;i<5;i++)
    paramf.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);
  std::vector<std::vector<std::vector<Float_t>>*> parerrf(5);
  for(int i=0;i<5;i++)
    parerrf.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePt = new TCanvas("cScalePt", "", 600, 600);
      TH2F* hemptyScalePt = new TH2F("hemptyScalePt", ";Reco jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.95:0.9, ispp?1.15:1.5);
      xjjroot::sethempty(hemptyScalePt, 0, 0.4);
      hemptyScalePt->Draw();
      TLegend* legScalePt = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePt);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hScalePt[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePt[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{reco jet}| < 1.6":Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePt->AddEntry(hScalePt[k][j], tleg.Data(), "p");
        }
      TF1* fScalePt = new TF1("fScalePt", "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", resojtptBins[0], resojtptBins[nResoJtptBins]);
      fScalePt->SetParLimits(0, 0.98, 1.02);
      fScalePt->SetParameter(0, 1);
      fScalePt->SetParameter(1, 0);
      fScalePt->SetParameter(2, 0.5);
      if(ispp) fScalePt->FixParameter(3, 0);
      fScalePt->SetLineWidth(3);
      fScalePt->SetLineColor(kGray+3);
      fScalePt->SetLineStyle(2);
      hScalePt[k][0]->Fit("fScalePt", "L q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);
      hScalePt[k][0]->Fit("fScalePt", "m q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);

      paramf.at(0)->at(k).push_back(fScalePt->GetParameter(0));
      paramf.at(0)->at(k).push_back(fScalePt->GetParameter(1));
      paramf.at(0)->at(k).push_back(fScalePt->GetParameter(2));
      paramf.at(0)->at(k).push_back(fScalePt->GetParameter(3));

      parerrf.at(0)->at(k).push_back(fScalePt->GetParError(0));
      parerrf.at(0)->at(k).push_back(fScalePt->GetParError(1));
      parerrf.at(0)->at(k).push_back(fScalePt->GetParError(2));
      parerrf.at(0)->at(k).push_back(fScalePt->GetParError(3));

      xjjroot::drawtex(0.22, 0.2, Form("%.2f%s%.2f/#sqrt{x}%s%.2f/x%s%.2f/(x*x)",fScalePt->GetParameter(0),fScalePt->GetParameter(1)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(1)),fScalePt->GetParameter(2)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(2)),fScalePt->GetParameter(3)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(3))));
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
      TH2F* hemptyScalePtCorr = new TH2F("hemptyScalePtCorr", ";Reco jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtCorr, 0, 0.4);
      hemptyScalePtCorr->Draw();
      TLegend* legScalePtCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtCorr);
      xjjroot::drawline(resojtptBins[0], 1.02, resojtptBins[nResoJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(resojtptBins[0], 0.98, resojtptBins[nResoJtptBins], 0.98, kGray+3, 2, 3);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hScalePtCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePtCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{reco jet}| < 1.6":Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePtCorr->AddEntry(hScalePtCorr[k][j], tleg.Data(), "p");
        } 
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtCorr->Draw();
      cScalePtCorr->SaveAs(Form("plotresos/cScalePtCorr_%s_%d.pdf",outputname.Data(),k));

      TCanvas* cScalePtFfCorr = new TCanvas("cScalePtFfCorr", "", 600, 600);
      TH2F* hemptyScalePtFfCorr = new TH2F("hemptyScalePtFfCorr", ";Reco jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), frag-dep Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtFfCorr, 0, 0.4);
      hemptyScalePtFfCorr->Draw();
      TLegend* legScalePtFfCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtFfCorr);
      xjjroot::drawline(resojtptBins[0], 1.02, resojtptBins[nResoJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(resojtptBins[0], 0.98, resojtptBins[nResoJtptBins], 0.98, kGray+3, 2, 3);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hScalePtFfCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePtFfCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{reco jet}| < 1.6":Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePtFfCorr->AddEntry(hScalePtFfCorr[k][j], tleg.Data(), "p");
        } 
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtFfCorr->Draw();
      cScalePtFfCorr->SaveAs(Form("plotresos/cScalePtFfCorr_%s_%d.pdf",outputname.Data(),k));

      delete legScalePtFfCorr;
      delete hemptyScalePtFfCorr;
      delete cScalePtFfCorr;
      delete legScalePtCorr;
      delete hemptyScalePtCorr;
      delete cScalePtCorr;
    }

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPt = new TCanvas("cResoPt", "", 600, 600);
      TH2F* hemptyResoPt = new TH2F("hemptyResoPt", ";Reco jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, 0.4);
      xjjroot::sethempty(hemptyResoPt, 0, 0.4);
      hemptyResoPt->Draw();
      TLegend* legResoPt = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPt);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hResoPt[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPt[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{reco jet}| < 1.6":Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPt->AddEntry(hResoPt[k][j], tleg.Data(), "p");
        }
      TF1* fResoPt = new TF1("fResoPt", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      if(!ispp) fResoPt->SetParLimits(0, param0fResoPt_pp_param-param0fResoPt_pp_err, param0fResoPt_pp_param+param0fResoPt_pp_err);
      if(!(ispp || k==(nCentBins-1))) fResoPt->SetParLimits(1, param1fResoPt_peri_param-param1fResoPt_peri_err, param1fResoPt_peri_param+param1fResoPt_peri_err);
      fResoPt->SetParameter(0, ispp?0.060:param0fResoPt_pp_param);
      fResoPt->SetParameter(1, ispp?0.85:param1fResoPt_peri_param);
      if(ispp || k==(nCentBins-1)) fResoPt->FixParameter(2, 0);
      fResoPt->SetLineWidth(3);
      fResoPt->SetLineColor(kGray+3);
      fResoPt->SetLineStyle(2);
      hResoPt[k][0]->Fit("fResoPt", "L q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);
      hResoPt[k][0]->Fit("fResoPt", "m q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);

      paramf.at(1)->at(k).push_back(fResoPt->GetParameter(0));
      paramf.at(1)->at(k).push_back(fResoPt->GetParameter(1));
      paramf.at(1)->at(k).push_back(fResoPt->GetParameter(2));

      parerrf.at(1)->at(k).push_back(fResoPt->GetParError(0));
      parerrf.at(1)->at(k).push_back(fResoPt->GetParError(1));
      parerrf.at(1)->at(k).push_back(fResoPt->GetParError(2));

      xjjroot::drawCMS(collisionsyst);
      legResoPt->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPt->GetParameter(0)),TMath::Abs(fResoPt->GetParameter(1)),TMath::Abs(fResoPt->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoPt->GetParameter(0)),fResoPt->GetParError(0),TMath::Abs(fResoPt->GetParameter(1)),fResoPt->GetParError(1),TMath::Abs(fResoPt->GetParameter(2)),fResoPt->GetParError(2)));
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
      TH2F* hemptyResoPtCorr = new TH2F("hemptyResoPtCorr", ";Reco jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, 0.4);
      xjjroot::sethempty(hemptyResoPtCorr, 0, 0.4);
      hemptyResoPtCorr->Draw();
      TLegend* legResoPtCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPtCorr);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hResoPtCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPtCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{reco jet}| < 1.6":Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPtCorr->AddEntry(hResoPtCorr[k][j], tleg.Data(), "p");
        }
      TF1* fResoPtCorr = new TF1("fResoPtCorr", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      if(!ispp) fResoPtCorr->SetParLimits(0, param0fResoPtCorr_pp_param-param0fResoPtCorr_pp_err, param0fResoPtCorr_pp_param+param0fResoPtCorr_pp_err);
      if(!(ispp || k==(nCentBins-1))) fResoPtCorr->SetParLimits(1, param1fResoPtCorr_peri_param-param1fResoPtCorr_peri_err, param1fResoPtCorr_peri_param+param1fResoPtCorr_peri_err);
      fResoPtCorr->SetParameter(0, ispp?0.060:param0fResoPtCorr_pp_param);
      fResoPtCorr->SetParameter(1, ispp?0.85:param1fResoPtCorr_peri_param);
      if(ispp || k==(nCentBins-1)) fResoPtCorr->FixParameter(2, 0);
      fResoPtCorr->SetLineWidth(3);
      fResoPtCorr->SetLineColor(kGray+3);
      fResoPtCorr->SetLineStyle(2);
      hResoPtCorr[k][0]->Fit("fResoPtCorr", "L q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);
      hResoPtCorr[k][0]->Fit("fResoPtCorr", "m q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);

      paramf.at(2)->at(k).push_back(fResoPtCorr->GetParameter(0));
      paramf.at(2)->at(k).push_back(fResoPtCorr->GetParameter(1));
      paramf.at(2)->at(k).push_back(fResoPtCorr->GetParameter(2));

      parerrf.at(2)->at(k).push_back(fResoPtCorr->GetParError(0));
      parerrf.at(2)->at(k).push_back(fResoPtCorr->GetParError(1));
      parerrf.at(2)->at(k).push_back(fResoPtCorr->GetParError(2));

      xjjroot::drawCMS(collisionsyst);
      legResoPtCorr->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPtCorr->GetParameter(0)),TMath::Abs(fResoPtCorr->GetParameter(1)),TMath::Abs(fResoPtCorr->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoPtCorr->GetParameter(0)),fResoPtCorr->GetParError(0),TMath::Abs(fResoPtCorr->GetParameter(1)),fResoPtCorr->GetParError(1),TMath::Abs(fResoPtCorr->GetParameter(2)),fResoPtCorr->GetParError(2)));
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
      TH2F* hemptyResoPhi = new TH2F("hemptyResoPhi", ";Reco jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, ispp?0.02:0.05);
      xjjroot::sethempty(hemptyResoPhi, 0, 0.4);
      hemptyResoPhi->Draw();
      TLegend* legResoPhi = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPhi);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hResoPhi[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPhi[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{reco jet}| < 1.6":Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPhi->AddEntry(hResoPhi[k][j], tleg.Data(), "p");
        }
      TF1* fResoPhi = new TF1("fResoPhi", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      fResoPhi->SetParameter(0, 0.006);
      fResoPhi->SetParameter(1, 0.1);
      // if(ispp) fResoPhi->FixParameter(2, 0);
      fResoPhi->SetLineWidth(3);
      fResoPhi->SetLineColor(kGray+3);
      fResoPhi->SetLineStyle(2);
      hResoPhi[k][0]->Fit("fResoPhi", "L q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);
      hResoPhi[k][0]->Fit("fResoPhi", "m q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);

      paramf.at(3)->at(k).push_back(fResoPhi->GetParameter(0));
      paramf.at(3)->at(k).push_back(fResoPhi->GetParameter(1));
      paramf.at(3)->at(k).push_back(fResoPhi->GetParameter(2));

      parerrf.at(3)->at(k).push_back(fResoPhi->GetParError(0));
      parerrf.at(3)->at(k).push_back(fResoPhi->GetParError(1));
      parerrf.at(3)->at(k).push_back(fResoPhi->GetParError(2));

      xjjroot::drawCMS(collisionsyst);
      legResoPhi->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPhi->GetParameter(0)),TMath::Abs(fResoPhi->GetParameter(1)),TMath::Abs(fResoPhi->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoPhi->GetParameter(0)),fResoPhi->GetParError(0),TMath::Abs(fResoPhi->GetParameter(1)),fResoPhi->GetParError(1),TMath::Abs(fResoPhi->GetParameter(2)),fResoPhi->GetParError(2)));
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
      TH2F* hemptyResoEta = new TH2F("hemptyResoEta", ";Reco jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, ispp?0.02:0.05);
      xjjroot::sethempty(hemptyResoEta, 0, 0.4);
      hemptyResoEta->Draw();
      TLegend* legResoEta = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoEta);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hResoEta[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoEta[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{reco jet}| < 1.6":Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoEta->AddEntry(hResoEta[k][j], tleg.Data(), "p");
        }
      TF1* fResoEta = new TF1("fResoEta", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      fResoEta->SetParameter(0, 0.006);
      fResoEta->SetParameter(1, 0.1);
      // if(ispp) fResoEta->Fixparameter(2, 0);
      fResoEta->SetLineWidth(3);
      fResoEta->SetLineColor(kGray+3);
      fResoEta->SetLineStyle(2);
      hResoEta[k][0]->Fit("fResoEta", "L q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);
      hResoEta[k][0]->Fit("fResoEta", "m q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);

      paramf.at(4)->at(k).push_back(fResoEta->GetParameter(0));
      paramf.at(4)->at(k).push_back(fResoEta->GetParameter(1));
      paramf.at(4)->at(k).push_back(fResoEta->GetParameter(2));

      parerrf.at(4)->at(k).push_back(fResoEta->GetParError(0));
      parerrf.at(4)->at(k).push_back(fResoEta->GetParError(1));
      parerrf.at(4)->at(k).push_back(fResoEta->GetParError(2));

      xjjroot::drawCMS(collisionsyst);
      legResoEta->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoEta->GetParameter(0)),TMath::Abs(fResoEta->GetParameter(1)),TMath::Abs(fResoEta->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoEta->GetParameter(0)),fResoEta->GetParError(0),TMath::Abs(fResoEta->GetParameter(1)),fResoEta->GetParError(1),TMath::Abs(fResoEta->GetParameter(2)),fResoEta->GetParError(2)));
      cResoEta->SaveAs(Form("plotresos/cResoEta_%s_%d.pdf",outputname.Data(),k));
      delete fResoEta;
      delete legResoEta;
      delete hemptyResoEta;
      delete cResoEta;
    }

  // TString paramfname[5] = {"ScalePt", "ResoPt", "ResoPtCorr", "ResoPhi", "ResoEta"};
  std::cout<<std::endl;
  for(int i=0;i<5;i++)
    {
      std::cout<<"std::vector<std::vector<Float_t>> "<<(ispp?Form("paramf%s_pp = {",paramfname[i].Data()):Form("paramf%s_PbPb = {",paramfname[i].Data()));
      for(int k=0;k<nCentBins;k++)
        {
          std::cout<<"{";
          for(int j=0;j<paramf.at(i)->at(k).size();j++)
            std::cout<<paramf.at(i)->at(k).at(j)<<(j==paramf.at(i)->at(k).size()-1?"}":", ");
          std::cout<<(k==(nCentBins-1)?"};":",")<<std::endl;
        }
    }
  if(ispp)
    {
      std::cout<<std::endl<<std::string(30, '>')<<std::endl;
      std::cout<<"Float_t param0fResoPt_pp_param = "<<paramf.at(1)->at(0).at(0)<<";"<<std::endl;
      std::cout<<"Float_t param0fResoPt_pp_err = "<<parerrf.at(1)->at(0).at(0)<<";"<<std::endl;
      std::cout<<"Float_t param0fResoPtCorr_pp_param = "<<paramf.at(2)->at(0).at(0)<<";"<<std::endl;
      std::cout<<"Float_t param0fResoPtCorr_pp_err = "<<parerrf.at(2)->at(0).at(0)<<";"<<std::endl;
      std::cout<<std::string(30, '<')<<std::endl;
    }
  else
    {
      std::cout<<std::endl<<std::string(30, '>')<<std::endl;
      std::cout<<"Float_t param1fResoPt_peri_param = "<<paramf.at(1)->at(1).at(1)<<";"<<std::endl;
      std::cout<<"Float_t param1fResoPt_peri_err = "<<parerrf.at(1)->at(1).at(1)<<";"<<std::endl;
      std::cout<<"Float_t param1fResoPtCorr_peri_param = "<<paramf.at(2)->at(1).at(1)<<";"<<std::endl;
      std::cout<<"Float_t param1fResoPtCorr_peri_err = "<<parerrf.at(2)->at(1).at(1)<<";"<<std::endl;
      std::cout<<std::string(30, '<')<<std::endl;      
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
