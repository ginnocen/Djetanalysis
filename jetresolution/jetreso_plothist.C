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

  const int NP = 9;
  TString paramfname[NP] = {"ScalePt", "ResoPt", "ResoPtCorr", "ResoPhi", "ResoEta", "ScalePtFfCorr", "ResoPtFfJecCorr", "ResoDrPhi", "ResoDrEta"};
  std::vector<std::vector<std::vector<Float_t>>*> paramf(NP);
  for(int i=0;i<NP;i++)
    paramf.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);
  std::vector<std::vector<std::vector<Float_t>>*> parerrf(NP);
  for(int i=0;i<NP;i++)
    parerrf.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);

  std::vector<std::vector<std::vector<Float_t>>*> existf_pp = {&paramfScalePt_pp, &paramfResoPt_pp, &paramfResoPtCorr_pp, &paramfResoPhi_pp, &paramfResoEta_pp, &paramfScalePtFfCorr_pp, &paramfResoPtFfJecCorr_pp};
  std::vector<std::vector<std::vector<Float_t>>*> existf_PbPb = {&paramfScalePt_PbPb, &paramfResoPt_PbPb, &paramfResoPtCorr_PbPb, &paramfResoPhi_PbPb, &paramfResoEta_PbPb, &paramfScalePtFfCorr_PbPb, &paramfResoPtFfJecCorr_PbPb};
  std::vector<TString> fun = {"[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", 
                              "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", 
                              "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", 
                              "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", 
                              "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", 
                              "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)",
                              "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))" 
  };

  // Scale Pt
  int index = 0;  
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePt = new TCanvas("cScalePt", "", 600, 600);
      TH2F* hemptyScalePt = new TH2F("hemptyScalePt", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.4);
      xjjroot::sethempty(hemptyScalePt, 0, 0.4);
      hemptyScalePt->Draw();
      TLegend* legScalePt = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePt);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hScalePt[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePt[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePt->AddEntry(hScalePt[k][j], tleg.Data(), "p");
        }
      TF1* fScalePt = new TF1("fScalePt", "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", resojtptBins[0], resojtptBins[nResoJtptBins]);
      fScalePt->SetParLimits(0, 0.95, 1.05);
      fScalePt->SetParameter(0, 1);
      fScalePt->SetParameter(1, 0);
      fScalePt->SetParameter(2, 0.5);
      if(ispp) fScalePt->FixParameter(3, 0);
      fScalePt->SetLineWidth(3);
      fScalePt->SetLineColor(kGray+3);
      fScalePt->SetLineStyle(2);
      hScalePt[k][0]->Fit("fScalePt", "L q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);
      hScalePt[k][0]->Fit("fScalePt", "m q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);

      paramf.at(index)->at(k).push_back(fScalePt->GetParameter(0));
      paramf.at(index)->at(k).push_back(fScalePt->GetParameter(1));
      paramf.at(index)->at(k).push_back(fScalePt->GetParameter(2));
      paramf.at(index)->at(k).push_back(fScalePt->GetParameter(3));

      parerrf.at(index)->at(k).push_back(fScalePt->GetParError(0));
      parerrf.at(index)->at(k).push_back(fScalePt->GetParError(1));
      parerrf.at(index)->at(k).push_back(fScalePt->GetParError(2));
      parerrf.at(index)->at(k).push_back(fScalePt->GetParError(3));

      std::vector<std::vector<Float_t>>* existf = ispp?existf_pp[index]:existf_PbPb[index];
      TF1* fReso = new TF1("fReso", fun[index].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
      for(int m=0;m<existf->at(k).size();m++)
        fReso->SetParameter(m, existf->at(k).at(m));
      fReso->SetLineWidth(3);
      fReso->SetLineColor(kRed+3);
      fReso->SetLineStyle(1);
      fReso->Draw("same");

      xjjroot::drawtex(0.22, 0.2, Form("%.2f%s%.2f/#sqrt{x}%s%.2f/x%s%.2f/(x*x)",fScalePt->GetParameter(0),fScalePt->GetParameter(1)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(1)),fScalePt->GetParameter(2)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(2)),fScalePt->GetParameter(3)>=0?"+":"-",TMath::Abs(fScalePt->GetParameter(3))));
      xjjroot::drawCMS(collisionsyst); 
      legScalePt->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      cScalePt->SaveAs(Form("plotresos/cScalePt_%s_%d.pdf",outputname.Data(),k));

      delete fReso;
      delete fScalePt;
      delete legScalePt;
      delete hemptyScalePt;
      delete cScalePt;
    }

  // ResoPt
  index = 1;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPt = new TCanvas("cResoPt", "", 600, 600);
      TH2F* hemptyResoPt = new TH2F("hemptyResoPt", ";Gen jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, 0.6);
      xjjroot::sethempty(hemptyResoPt, 0, 0.4);
      hemptyResoPt->Draw();
      TLegend* legResoPt = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPt);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hResoPt[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPt[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
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

      paramf.at(index)->at(k).push_back(fResoPt->GetParameter(0));
      paramf.at(index)->at(k).push_back(fResoPt->GetParameter(1));
      paramf.at(index)->at(k).push_back(fResoPt->GetParameter(2));
      parerrf.at(index)->at(k).push_back(fResoPt->GetParError(0));
      parerrf.at(index)->at(k).push_back(fResoPt->GetParError(1));
      parerrf.at(index)->at(k).push_back(fResoPt->GetParError(2));

      std::vector<std::vector<Float_t>>* existf = ispp?existf_pp[index]:existf_PbPb[index];
      TF1* fReso = new TF1("fReso", fun[index].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
      for(int m=0;m<existf->at(k).size();m++)
        fReso->SetParameter(m, existf->at(k).at(m));
      fReso->SetLineWidth(3);
      fReso->SetLineColor(kRed+3);
      fReso->SetLineStyle(1);
      fReso->Draw("same");

      xjjroot::drawCMS(collisionsyst);
      legResoPt->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPt->GetParameter(0)),TMath::Abs(fResoPt->GetParameter(1)),TMath::Abs(fResoPt->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoPt->GetParameter(0)),fResoPt->GetParError(0),TMath::Abs(fResoPt->GetParameter(1)),fResoPt->GetParError(1),TMath::Abs(fResoPt->GetParameter(2)),fResoPt->GetParError(2)));
      cResoPt->SaveAs(Form("plotresos/cResoPt_%s_%d.pdf",outputname.Data(),k));

      delete fReso;
      delete fResoPt;
      delete legResoPt;
      delete hemptyResoPt;
      delete cResoPt;
    }

  // ResoPtCorr
  index = 2;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPtCorr = new TCanvas("cResoPtCorr", "", 600, 600);
      TH2F* hemptyResoPtCorr = new TH2F("hemptyResoPtCorr", ";Gen jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, ispp?0.4:0.7);
      xjjroot::sethempty(hemptyResoPtCorr, 0, 0.4);
      hemptyResoPtCorr->Draw();
      TLegend* legResoPtCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPtCorr);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hResoPtCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPtCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPtCorr->AddEntry(hResoPtCorr[k][j], tleg.Data(), "p");
        }
      TF1* fResoPtCorr = new TF1("fResoPtCorr", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      if(!ispp) fResoPtCorr->SetParLimits(0, param0fResoPtCorr_pp_param-param0fResoPtCorr_pp_err, param0fResoPtCorr_pp_param+param0fResoPtCorr_pp_err);
      if(!(ispp || k==(nCentBins-1))) fResoPtCorr->SetParLimits(1, param1fResoPtCorr_peri_param-param1fResoPtCorr_peri_err, param1fResoPtCorr_peri_param+param1fResoPtCorr_peri_err);
      fResoPtCorr->SetParameter(0, ispp?0.060:param0fResoPtCorr_pp_param);
      fResoPtCorr->SetParameter(1, ispp?0.85:param1fResoPtCorr_peri_param);
      if(ispp) fResoPtCorr->FixParameter(2, 0);
      // if(ispp || k==(nCentBins-1)) fResoPtCorr->FixParameter(2, 0);
      fResoPtCorr->SetLineWidth(3);
      fResoPtCorr->SetLineColor(kGray+3);
      fResoPtCorr->SetLineStyle(2);
      hResoPtCorr[k][0]->Fit("fResoPtCorr", "L q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);
      hResoPtCorr[k][0]->Fit("fResoPtCorr", "m q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);

      paramf.at(index)->at(k).push_back(fResoPtCorr->GetParameter(0));
      paramf.at(index)->at(k).push_back(fResoPtCorr->GetParameter(1));
      paramf.at(index)->at(k).push_back(fResoPtCorr->GetParameter(2));
      parerrf.at(index)->at(k).push_back(fResoPtCorr->GetParError(0));
      parerrf.at(index)->at(k).push_back(fResoPtCorr->GetParError(1));
      parerrf.at(index)->at(k).push_back(fResoPtCorr->GetParError(2));

      std::vector<std::vector<Float_t>>* existf = ispp?existf_pp[index]:existf_PbPb[index];
      TF1* fReso = new TF1("fReso", fun[index].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
      for(int m=0;m<existf->at(k).size();m++)
        fReso->SetParameter(m, existf->at(k).at(m));
      fReso->SetLineWidth(3);
      fReso->SetLineColor(kRed+3);
      fReso->SetLineStyle(1);
      fReso->Draw("same");

      xjjroot::drawCMS(collisionsyst);
      legResoPtCorr->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPtCorr->GetParameter(0)),TMath::Abs(fResoPtCorr->GetParameter(1)),TMath::Abs(fResoPtCorr->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoPtCorr->GetParameter(0)),fResoPtCorr->GetParError(0),TMath::Abs(fResoPtCorr->GetParameter(1)),fResoPtCorr->GetParError(1),TMath::Abs(fResoPtCorr->GetParameter(2)),fResoPtCorr->GetParError(2)));
      cResoPtCorr->SaveAs(Form("plotresos/cResoPtCorr_%s_%d.pdf",outputname.Data(),k));

      delete fReso;
      delete fResoPtCorr;
      delete legResoPtCorr;
      delete hemptyResoPtCorr;
      delete cResoPtCorr;
    }

  // ResoPhi
  index = 3;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPhi = new TCanvas("cResoPhi", "", 600, 600);
      TH2F* hemptyResoPhi = new TH2F("hemptyResoPhi", ";Gen jet p_{T} (GeV/c);#sigma(#phi^{reco} - #phi^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, ispp?0.02:0.07);
      xjjroot::sethempty(hemptyResoPhi, 0, 0.4);
      hemptyResoPhi->Draw();
      TLegend* legResoPhi = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPhi);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hResoPhi[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPhi[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPhi->AddEntry(hResoPhi[k][j], tleg.Data(), "p");
        }
      TF1* fResoPhi = new TF1("fResoPhi", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      fResoPhi->SetParameter(0, 0.006);
      fResoPhi->SetParameter(1, 0.1);
      // if(ispp) fResoPhi->FixParameter(2, 0);
      fResoPhi->SetLineWidth(3);
      fResoPhi->SetLineColor(kGray+3);
      fResoPhi->SetLineStyle(2);
      hResoPhi[k][0]->Fit("fResoPhi", "L q", "", resojtptBins[2], resojtptBins[nResoJtptBins]);
      hResoPhi[k][0]->Fit("fResoPhi", "m q", "", resojtptBins[2], resojtptBins[nResoJtptBins]);

      paramf.at(index)->at(k).push_back(fResoPhi->GetParameter(0));
      paramf.at(index)->at(k).push_back(fResoPhi->GetParameter(1));
      paramf.at(index)->at(k).push_back(fResoPhi->GetParameter(2));
      parerrf.at(index)->at(k).push_back(fResoPhi->GetParError(0));
      parerrf.at(index)->at(k).push_back(fResoPhi->GetParError(1));
      parerrf.at(index)->at(k).push_back(fResoPhi->GetParError(2));

      std::vector<std::vector<Float_t>>* existf = ispp?existf_pp[index]:existf_PbPb[index];
      TF1* fReso = new TF1("fReso", fun[index].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
      for(int m=0;m<existf->at(k).size();m++)
        fReso->SetParameter(m, existf->at(k).at(m));
      fReso->SetLineWidth(3);
      fReso->SetLineColor(kRed+3);
      fReso->SetLineStyle(1);
      fReso->Draw("same");

      xjjroot::drawCMS(collisionsyst);
      legResoPhi->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPhi->GetParameter(0)),TMath::Abs(fResoPhi->GetParameter(1)),TMath::Abs(fResoPhi->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoPhi->GetParameter(0)),fResoPhi->GetParError(0),TMath::Abs(fResoPhi->GetParameter(1)),fResoPhi->GetParError(1),TMath::Abs(fResoPhi->GetParameter(2)),fResoPhi->GetParError(2)));
      cResoPhi->SaveAs(Form("plotresos/cResoPhi_%s_%d.pdf",outputname.Data(),k));

      delete fReso;
      delete fResoPhi;
      delete legResoPhi;
      delete hemptyResoPhi;
      delete cResoPhi;
    }

  // ResoEta
  index = 4;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoEta = new TCanvas("cResoEta", "", 600, 600);
      TH2F* hemptyResoEta = new TH2F("hemptyResoEta", ";Gen jet p_{T} (GeV/c);#sigma(#eta^{reco} - #eta^{gen})", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, ispp?0.02:0.07);
      xjjroot::sethempty(hemptyResoEta, 0, 0.4);
      hemptyResoEta->Draw();
      TLegend* legResoEta = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoEta);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hResoEta[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoEta[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoEta->AddEntry(hResoEta[k][j], tleg.Data(), "p");
        }
      TF1* fResoEta = new TF1("fResoEta", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      fResoEta->SetParameter(0, 0.006);
      fResoEta->SetParameter(1, 0.1);
      // if(ispp) fResoEta->Fixparameter(2, 0);
      fResoEta->SetLineWidth(3);
      fResoEta->SetLineColor(kGray+3);
      fResoEta->SetLineStyle(2);
      hResoEta[k][0]->Fit("fResoEta", "L q", "", resojtptBins[2], resojtptBins[nResoJtptBins]);
      hResoEta[k][0]->Fit("fResoEta", "m q", "", resojtptBins[2], resojtptBins[nResoJtptBins]);

      paramf.at(index)->at(k).push_back(fResoEta->GetParameter(0));
      paramf.at(index)->at(k).push_back(fResoEta->GetParameter(1));
      paramf.at(index)->at(k).push_back(fResoEta->GetParameter(2));
      parerrf.at(index)->at(k).push_back(fResoEta->GetParError(0));
      parerrf.at(index)->at(k).push_back(fResoEta->GetParError(1));
      parerrf.at(index)->at(k).push_back(fResoEta->GetParError(2));

      std::vector<std::vector<Float_t>>* existf = ispp?existf_pp[index]:existf_PbPb[index];
      TF1* fReso = new TF1("fReso", fun[index].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
      for(int m=0;m<existf->at(k).size();m++)
        fReso->SetParameter(m, existf->at(k).at(m));
      fReso->SetLineWidth(3);
      fReso->SetLineColor(kRed+3);
      fReso->SetLineStyle(1);
      fReso->Draw("same");

      xjjroot::drawCMS(collisionsyst);
      legResoEta->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoEta->GetParameter(0)),TMath::Abs(fResoEta->GetParameter(1)),TMath::Abs(fResoEta->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoEta->GetParameter(0)),fResoEta->GetParError(0),TMath::Abs(fResoEta->GetParameter(1)),fResoEta->GetParError(1),TMath::Abs(fResoEta->GetParameter(2)),fResoEta->GetParError(2)));
      cResoEta->SaveAs(Form("plotresos/cResoEta_%s_%d.pdf",outputname.Data(),k));

      delete fReso;
      delete fResoEta;
      delete legResoEta;
      delete hemptyResoEta;
      delete cResoEta;
    }

  // ScalePtFfCorr
  index = 5;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePtFfCorr = new TCanvas("cScalePtFfCorr", "", 600, 600);
      TH2F* hemptyScalePtFfCorr = new TH2F("hemptyScalePtFfCorr", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), frag-dep Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.8:0.7, ispp?1.1:1.1);
      xjjroot::sethempty(hemptyScalePtFfCorr, 0, 0.4);
      hemptyScalePtFfCorr->Draw();
      TLegend* legScalePtFfCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtFfCorr);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hScalePtFfCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePtFfCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePtFfCorr->AddEntry(hScalePtFfCorr[k][j], tleg.Data(), "p");
        } 
      TF1* fScalePtFfCorr = new TF1("fScalePtFfCorr", "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", resojtptBins[0], resojtptBins[nResoJtptBins]);
      fScalePtFfCorr->SetParameter(0, 1);
      fScalePtFfCorr->SetParameter(1, 0);
      // fScalePtFfCorr->SetParameter(2, 0.5);
      fScalePtFfCorr->SetParameter(2, 0);
      fScalePtFfCorr->SetParameter(3, 100);
      fScalePtFfCorr->SetLineWidth(3);
      fScalePtFfCorr->SetLineColor(kGray+3);
      fScalePtFfCorr->SetLineStyle(2);
      // hScalePtFfCorr[k][0]->Fit("fScalePtFfCorr", "L q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);
      // hScalePtFfCorr[k][0]->Fit("fScalePtFfCorr", "m q", "", resojtptBins[0], resojtptBins[nResoJtptBins]);
      hScalePtFfCorr[k][0]->Fit("fScalePtFfCorr", "L q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);
      hScalePtFfCorr[k][0]->Fit("fScalePtFfCorr", "m q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);

      paramf.at(index)->at(k).push_back(fScalePtFfCorr->GetParameter(0));
      paramf.at(index)->at(k).push_back(fScalePtFfCorr->GetParameter(1));
      paramf.at(index)->at(k).push_back(fScalePtFfCorr->GetParameter(2));
      paramf.at(index)->at(k).push_back(fScalePtFfCorr->GetParameter(3));
      parerrf.at(index)->at(k).push_back(fScalePtFfCorr->GetParError(0));
      parerrf.at(index)->at(k).push_back(fScalePtFfCorr->GetParError(1));
      parerrf.at(index)->at(k).push_back(fScalePtFfCorr->GetParError(2));
      parerrf.at(index)->at(k).push_back(fScalePtFfCorr->GetParError(3));

      std::vector<std::vector<Float_t>>* existf = ispp?existf_pp[index]:existf_PbPb[index];
      TF1* fReso = new TF1("fReso", fun[index].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
      for(int m=0;m<existf->at(k).size();m++)
        fReso->SetParameter(m, existf->at(k).at(m));
      fReso->SetLineWidth(3);
      fReso->SetLineColor(kRed+3);
      fReso->SetLineStyle(1);
      fReso->Draw("same");

      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtFfCorr->Draw();
      cScalePtFfCorr->SaveAs(Form("plotresos/cScalePtFfCorr_%s_%d.pdf",outputname.Data(),k));

      delete fReso;
      delete fScalePtFfCorr;
      delete legScalePtFfCorr;
      delete hemptyScalePtFfCorr;
      delete cScalePtFfCorr;
    }

  // ResoPtFfJecCorr
  index = 6;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPtFfJecCorr = new TCanvas("cResoPtFfJecCorr", "", 600, 600);
      TH2F* hemptyResoPtFfJecCorr = new TH2F("hemptyResoPtFfJecCorr", ";Gen jet p_{T} (GeV/c);#sigma(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, 0, ispp?0.4:0.7);
      xjjroot::sethempty(hemptyResoPtFfJecCorr, 0, 0.4);
      hemptyResoPtFfJecCorr->Draw();
      TLegend* legResoPtFfJecCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPtFfJecCorr);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hResoPtFfJecCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoPtFfJecCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPtFfJecCorr->AddEntry(hResoPtFfJecCorr[k][j], tleg.Data(), "p");
        }
      TF1* fResoPtFfJecCorr = new TF1("fResoPtFfJecCorr", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resojtptBins[0], resojtptBins[nResoJtptBins]);
      if(!ispp) fResoPtFfJecCorr->SetParLimits(0, param0fResoPtFfJecCorr_pp_param-param0fResoPtFfJecCorr_pp_err, param0fResoPtFfJecCorr_pp_param+param0fResoPtFfJecCorr_pp_err);
      if(!(ispp || k==(nCentBins-1))) fResoPtFfJecCorr->SetParLimits(1, param1fResoPtFfJecCorr_peri_param-param1fResoPtFfJecCorr_peri_err, param1fResoPtFfJecCorr_peri_param+param1fResoPtFfJecCorr_peri_err);
      fResoPtFfJecCorr->SetParameter(0, ispp?0.060:param0fResoPtFfJecCorr_pp_param);
      fResoPtFfJecCorr->SetParameter(1, ispp?0.85:param1fResoPtFfJecCorr_peri_param);
      if(ispp) fResoPtFfJecCorr->FixParameter(2, 0);
      // if(ispp || k==(nCentBins-1)) fResoPtFfJecCorr->FixParameter(2, 0);
      fResoPtFfJecCorr->SetLineWidth(3);
      fResoPtFfJecCorr->SetLineColor(kGray+3);
      fResoPtFfJecCorr->SetLineStyle(2);
      hResoPtFfJecCorr[k][0]->Fit("fResoPtFfJecCorr", "L q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);
      hResoPtFfJecCorr[k][0]->Fit("fResoPtFfJecCorr", "m q", "", resojtptBins[1], resojtptBins[nResoJtptBins]);

      paramf.at(index)->at(k).push_back(fResoPtFfJecCorr->GetParameter(0));
      paramf.at(index)->at(k).push_back(fResoPtFfJecCorr->GetParameter(1));
      paramf.at(index)->at(k).push_back(fResoPtFfJecCorr->GetParameter(2));
      parerrf.at(index)->at(k).push_back(fResoPtFfJecCorr->GetParError(0));
      parerrf.at(index)->at(k).push_back(fResoPtFfJecCorr->GetParError(1));
      parerrf.at(index)->at(k).push_back(fResoPtFfJecCorr->GetParError(2));

      std::vector<std::vector<Float_t>>* existf = ispp?existf_pp[index]:existf_PbPb[index];
      TF1* fReso = new TF1("fReso", fun[index].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
      for(int m=0;m<existf->at(k).size();m++)
        fReso->SetParameter(m, existf->at(k).at(m));
      fReso->SetLineWidth(3);
      fReso->SetLineColor(kRed+3);
      fReso->SetLineStyle(1);
      fReso->Draw("same");

      xjjroot::drawCMS(collisionsyst);
      legResoPtFfJecCorr->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(0.22, 0.2, Form("#sqrt{%.3f^{2}+%.3f^{2}/x+%.3f^{2}/(x*x)}",TMath::Abs(fResoPtFfJecCorr->GetParameter(0)),TMath::Abs(fResoPtFfJecCorr->GetParameter(1)),TMath::Abs(fResoPtFfJecCorr->GetParameter(2))));
      if(verboseonplot) xjjroot::drawtex(0.22, 0.26, Form("[0]=%.3f#pm%.3f, [1]=%.3f#pm%.3f, [2]=%.3f#pm%.3f",TMath::Abs(fResoPtFfJecCorr->GetParameter(0)),fResoPtFfJecCorr->GetParError(0),TMath::Abs(fResoPtFfJecCorr->GetParameter(1)),fResoPtFfJecCorr->GetParError(1),TMath::Abs(fResoPtFfJecCorr->GetParameter(2)),fResoPtFfJecCorr->GetParError(2)));
      cResoPtFfJecCorr->SaveAs(Form("plotresos/cResoPtFfJecCorr_%s_%d.pdf",outputname.Data(),k));

      delete fReso;
      delete fResoPtFfJecCorr;
      delete legResoPtFfJecCorr;
      delete hemptyResoPtFfJecCorr;
      delete cResoPtFfJecCorr;
    }

  // ResoDrPhi
  index = 7;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPhi = new TCanvas("cResoPhi", "", 600, 600);
      TH2F* hemptyResoPhi = new TH2F("hemptyResoPhi", ";#DeltaR < jet, D^{lead}>;#sigma(#phi^{reco} - #phi^{gen})", 10, resojtdrBins[0], resojtdrBins[nResoJtdrBins], 10, 0, ispp?0.02:0.07);
      xjjroot::sethempty(hemptyResoPhi, 0, 0.4);
      hemptyResoPhi->Draw();
      TLegend* legResoPhi = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoPhi);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hResoDrPhi[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoDrPhi[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoPhi->AddEntry(hResoDrPhi[k][j], tleg.Data(), "p");
        }
      TF1* fResoPhi = new TF1("fResoPhi", "pol3", resojtdrBins[0], resojtdrBins[nResoJtdrBins]);
      fResoPhi->SetLineWidth(3);
      fResoPhi->SetLineColor(kGray+3);
      fResoPhi->SetLineStyle(2);
      hResoDrPhi[k][0]->Fit("fResoPhi", "L q", "", resojtdrBins[0], resojtdrBins[nResoJtdrBins]);
      hResoDrPhi[k][0]->Fit("fResoPhi", "m q", "", resojtdrBins[0], resojtdrBins[nResoJtdrBins]);

      paramf.at(index)->at(k).push_back(fResoPhi->GetParameter(0));
      paramf.at(index)->at(k).push_back(fResoPhi->GetParameter(1));
      paramf.at(index)->at(k).push_back(fResoPhi->GetParameter(2));
      paramf.at(index)->at(k).push_back(fResoPhi->GetParameter(3));
      parerrf.at(index)->at(k).push_back(fResoPhi->GetParError(0));
      parerrf.at(index)->at(k).push_back(fResoPhi->GetParError(1));
      parerrf.at(index)->at(k).push_back(fResoPhi->GetParError(2));
      parerrf.at(index)->at(k).push_back(fResoPhi->GetParError(3));

      xjjroot::drawCMS(collisionsyst);
      legResoPhi->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      cResoPhi->SaveAs(Form("plotresos/cResoDrPhi_%s_%d.pdf",outputname.Data(),k));

      delete fResoPhi;
      delete legResoPhi;
      delete hemptyResoPhi;
      delete cResoPhi;
    }


  // ResoDrEta
  index = 8;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoEta = new TCanvas("cResoEta", "", 600, 600);
      TH2F* hemptyResoEta = new TH2F("hemptyResoEta", ";#DeltaR < jet, D^{lead}>;#sigma(#eta^{reco} - #eta^{gen})", 10, resojtdrBins[0], resojtdrBins[nResoJtdrBins], 10, 0, ispp?0.02:0.07);
      xjjroot::sethempty(hemptyResoEta, 0, 0.4);
      hemptyResoEta->Draw();
      TLegend* legResoEta = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legResoEta);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hResoDrEta[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hResoDrEta[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legResoEta->AddEntry(hResoDrEta[k][j], tleg.Data(), "p");
        }
      TF1* fResoEta = new TF1("fResoEta", "pol3", resojtdrBins[0], resojtdrBins[nResoJtdrBins]);
      fResoEta->SetLineWidth(3);
      fResoEta->SetLineColor(kGray+3);
      fResoEta->SetLineStyle(2);
      hResoDrEta[k][0]->Fit("fResoEta", "L q", "", resojtdrBins[0], resojtdrBins[nResoJtdrBins]);
      hResoDrEta[k][0]->Fit("fResoEta", "m q", "", resojtdrBins[0], resojtdrBins[nResoJtdrBins]);

      paramf.at(index)->at(k).push_back(fResoEta->GetParameter(0));
      paramf.at(index)->at(k).push_back(fResoEta->GetParameter(1));
      paramf.at(index)->at(k).push_back(fResoEta->GetParameter(2));
      paramf.at(index)->at(k).push_back(fResoEta->GetParameter(3));
      parerrf.at(index)->at(k).push_back(fResoEta->GetParError(0));
      parerrf.at(index)->at(k).push_back(fResoEta->GetParError(1));
      parerrf.at(index)->at(k).push_back(fResoEta->GetParError(2));
      parerrf.at(index)->at(k).push_back(fResoEta->GetParError(3));

      xjjroot::drawCMS(collisionsyst);
      legResoEta->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      cResoEta->SaveAs(Form("plotresos/cResoDrEta_%s_%d.pdf",outputname.Data(),k));

      delete fResoEta;
      delete legResoEta;
      delete hemptyResoEta;
      delete cResoEta;
    }

  // ScalePtCorr (no fit)
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePtCorr = new TCanvas("cScalePtCorr", "", 600, 600);
      TH2F* hemptyScalePtCorr = new TH2F("hemptyScalePtCorr", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtCorr, 0, 0.4);
      hemptyScalePtCorr->Draw();
      TLegend* legScalePtCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtCorr);
      xjjroot::drawline(resojtptBins[0], 1.02, resojtptBins[nResoJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(resojtptBins[0], 0.98, resojtptBins[nResoJtptBins], 0.98, kGray+3, 2, 3);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hScalePtCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePtCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
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

  // ScalePtRMatGCorr (no fit)
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePtRMatGCorr = new TCanvas("cScalePtRMatGCorr", "", 600, 600);
      TH2F* hemptyScalePtRMatGCorr = new TH2F("hemptyScalePtRMatGCorr", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtRMatGCorr, 0, 0.4);
      hemptyScalePtRMatGCorr->Draw();
      TLegend* legScalePtRMatGCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtRMatGCorr);
      xjjroot::drawline(resojtptBins[0], 1.02, resojtptBins[nResoJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(resojtptBins[0], 0.98, resojtptBins[nResoJtptBins], 0.98, kGray+3, 2, 3);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hScalePtRMatGCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePtRMatGCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePtRMatGCorr->AddEntry(hScalePtRMatGCorr[k][j], tleg.Data(), "p");
        } 
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtRMatGCorr->Draw();
      cScalePtRMatGCorr->SaveAs(Form("plotresos/cScalePtRMatGCorr_%s_%d.pdf",outputname.Data(),k));

      delete legScalePtRMatGCorr;
      delete hemptyScalePtRMatGCorr;
      delete cScalePtRMatGCorr;
    }

  // ScalePtFfJecCorr (no fit)
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePtFfJecCorr = new TCanvas("cScalePtFfJecCorr", "", 600, 600);
      TH2F* hemptyScalePtFfJecCorr = new TH2F("hemptyScalePtFfJecCorr", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), FfJecCorr", 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtFfJecCorr, 0, 0.4);
      hemptyScalePtFfJecCorr->Draw();
      TLegend* legScalePtFfJecCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*(int)hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtFfJecCorr);
      xjjroot::drawline(resojtptBins[0], 1.02, resojtptBins[nResoJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(resojtptBins[0], 0.98, resojtptBins[nResoJtptBins], 0.98, kGray+3, 2, 3);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(j && hidemuleta) continue;
          xjjroot::setthgrstyle(hScalePtFfJecCorr[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePtFfJecCorr[k][j]->Draw("same pe");
          TString tleg = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePtFfJecCorr->AddEntry(hScalePtFfJecCorr[k][j], tleg.Data(), "p");
        } 
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtFfJecCorr->Draw();
      cScalePtFfJecCorr->SaveAs(Form("plotresos/cScalePtFfJecCorr_%s_%d.pdf",outputname.Data(),k));

      delete legScalePtFfJecCorr;
      delete hemptyScalePtFfJecCorr;
      delete cScalePtFfJecCorr;
    }


  //
  const int DeltaNP = 2;
  TString paramfnameDelta[DeltaNP] = {"ResoDeltaPhi", "ResoDeltaEta"};
  std::vector<std::vector<std::vector<Float_t>>*> paramfDelta(DeltaNP);
  for(int i=0;i<DeltaNP;i++)
    paramfDelta.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);
  std::vector<std::vector<std::vector<Float_t>>*> parerrfDelta(DeltaNP);
  for(int i=0;i<DeltaNP;i++)
    parerrfDelta.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);

  std::vector<TString> funDelta = {"TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x)) - TMath::Sqrt([3]*[3]+[4]*[4]/x+[5]*[5]/(x*x))", 
                                   "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x)) - TMath::Sqrt([3]*[3]+[4]*[4]/x+[5]*[5]/(x*x))"
  };

  // ResoDeltaPhi
  index = 0;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoPhi = new TCanvas("cResoPhi", "", 600, 600);
      TH2F* hemptyResoPhi = new TH2F("hemptyResoPhi", ";Gen jet p_{T} (GeV/c);#sigma(#phi^{lead D} - #phi^{jet})", 10, resodeltajtptBins[0], resodeltajtptBins[nResoDeltaJtptBins], 10, 0, 0.06);
      xjjroot::sethempty(hemptyResoPhi, 0, 0.4);
      hemptyResoPhi->Draw();
      TLegend* legResoPhi = new TLegend(0.53, 0.88-5*0.055, 0.85, 0.88);
      xjjroot::setleg(legResoPhi);

      xjjroot::setthgrstyle(hResoGenDeltaPhi[k][0], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      xjjroot::setthgrstyle(hResoRecoDeltaPhi[k][0], kBlack, 20, 1.2, kBlack, 1, 1, -1, -1, -1);
      hResoGenDeltaPhi[k][0]->Draw("same pe");
      hResoRecoDeltaPhi[k][0]->Draw("same pe");
      legResoPhi->AddEntry(hResoRecoDeltaPhi[k][0], "reco D, reco jet", "p");
      legResoPhi->AddEntry(hResoGenDeltaPhi[k][0], "gen D, gen jet", "p");

      TF1* fResoGenPhi = new TF1("fResoGenPhi", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resodeltajtptBins[0], resodeltajtptBins[nResoDeltaJtptBins]);
      fResoGenPhi->SetParameter(0, 0.006);
      fResoGenPhi->SetParameter(1, 0.1);
      fResoGenPhi->SetLineWidth(3);
      fResoGenPhi->SetLineColor(kRed+2);
      fResoGenPhi->SetLineStyle(2);
      hResoGenDeltaPhi[k][0]->Fit("fResoGenPhi", "L q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);
      hResoGenDeltaPhi[k][0]->Fit("fResoGenPhi", "m q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);

      TF1* fResoRecoPhi = new TF1("fResoRecoPhi", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resodeltajtptBins[0], resodeltajtptBins[nResoDeltaJtptBins]);
      fResoRecoPhi->SetParameter(0, 0.006);
      fResoRecoPhi->SetParameter(1, 0.1);
      fResoRecoPhi->SetLineWidth(3);
      fResoRecoPhi->SetLineColor(kRed+2);
      fResoRecoPhi->SetLineStyle(1);
      hResoRecoDeltaPhi[k][0]->Fit("fResoRecoPhi", "L q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);
      hResoRecoDeltaPhi[k][0]->Fit("fResoRecoPhi", "m q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);

      TF1* fResoPhi = new TF1("fResoPhi", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x) - ([3]*[3]+[4]*[4]/x+[5]*[5]/(x*x)))", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);
      fResoPhi->SetParameters(fResoRecoPhi->GetParameter(0), fResoRecoPhi->GetParameter(1), fResoRecoPhi->GetParameter(2), fResoGenPhi->GetParameter(0), fResoGenPhi->GetParameter(1), fResoGenPhi->GetParameter(2));
      fResoPhi->SetLineWidth(3);
      fResoPhi->SetLineColor(kAzure+2);
      fResoPhi->SetLineStyle(1);
      fResoPhi->Draw("same");

      legResoPhi->AddEntry(fResoRecoPhi, "fit on reco", "l");
      legResoPhi->AddEntry(fResoGenPhi, "fit on gen", "l");
      legResoPhi->AddEntry(fResoPhi, "#sigma", "l");

      paramfDelta.at(index)->at(k).push_back(fResoRecoPhi->GetParameter(0));
      paramfDelta.at(index)->at(k).push_back(fResoRecoPhi->GetParameter(1));
      paramfDelta.at(index)->at(k).push_back(fResoRecoPhi->GetParameter(2));
      paramfDelta.at(index)->at(k).push_back(fResoGenPhi->GetParameter(0));
      paramfDelta.at(index)->at(k).push_back(fResoGenPhi->GetParameter(1));
      paramfDelta.at(index)->at(k).push_back(fResoGenPhi->GetParameter(2));
      parerrfDelta.at(index)->at(k).push_back(fResoRecoPhi->GetParError(0));
      parerrfDelta.at(index)->at(k).push_back(fResoRecoPhi->GetParError(1));
      parerrfDelta.at(index)->at(k).push_back(fResoRecoPhi->GetParError(2));
      parerrfDelta.at(index)->at(k).push_back(fResoGenPhi->GetParError(0));
      parerrfDelta.at(index)->at(k).push_back(fResoGenPhi->GetParError(1));
      parerrfDelta.at(index)->at(k).push_back(fResoGenPhi->GetParError(2));

      xjjroot::drawCMS(collisionsyst);
      legResoPhi->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      cResoPhi->SaveAs(Form("plotresos/cResoDeltaPhi_%s_%d.pdf",outputname.Data(),k));

      delete fResoPhi;
      delete fResoGenPhi;
      delete fResoRecoPhi;
      delete legResoPhi;
      delete hemptyResoPhi;
      delete cResoPhi;
    }

  // ResoDeltaEta
  index = 1;
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cResoEta = new TCanvas("cResoEta", "", 600, 600);
      TH2F* hemptyResoEta = new TH2F("hemptyResoEta", ";Gen jet p_{T} (GeV/c);#sigma(#eta^{lead D} - #eta^{jet})", 10, resodeltajtptBins[0], resodeltajtptBins[nResoDeltaJtptBins], 10, 0, 0.06);
      xjjroot::sethempty(hemptyResoEta, 0, 0.4);
      hemptyResoEta->Draw();
      TLegend* legResoEta = new TLegend(0.53, 0.88-5*0.055, 0.85, 0.88);
      xjjroot::setleg(legResoEta);

      xjjroot::setthgrstyle(hResoGenDeltaEta[k][0], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
      xjjroot::setthgrstyle(hResoRecoDeltaEta[k][0], kBlack, 20, 1.2, kBlack, 1, 1, -1, -1, -1);
      hResoGenDeltaEta[k][0]->Draw("same pe");
      hResoRecoDeltaEta[k][0]->Draw("same pe");
      legResoEta->AddEntry(hResoRecoDeltaEta[k][0], "reco D, reco jet", "p");
      legResoEta->AddEntry(hResoGenDeltaEta[k][0], "gen D, gen jet", "p");

      TF1* fResoGenEta = new TF1("fResoGenEta", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resodeltajtptBins[0], resodeltajtptBins[nResoDeltaJtptBins]);
      fResoGenEta->SetParameter(0, 0.006);
      fResoGenEta->SetParameter(1, 0.1);
      fResoGenEta->SetLineWidth(3);
      fResoGenEta->SetLineColor(kRed+2);
      fResoGenEta->SetLineStyle(2);
      hResoGenDeltaEta[k][0]->Fit("fResoGenEta", "L q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);
      hResoGenDeltaEta[k][0]->Fit("fResoGenEta", "m q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);

      TF1* fResoRecoEta = new TF1("fResoRecoEta", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", resodeltajtptBins[0], resodeltajtptBins[nResoDeltaJtptBins]);
      fResoRecoEta->SetParameter(0, 0.006);
      fResoRecoEta->SetParameter(1, 0.1);
      fResoRecoEta->SetLineWidth(3);
      fResoRecoEta->SetLineColor(kRed+2);
      fResoRecoEta->SetLineStyle(1);
      hResoRecoDeltaEta[k][0]->Fit("fResoRecoEta", "L q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);
      hResoRecoDeltaEta[k][0]->Fit("fResoRecoEta", "m q", "", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);

      TF1* fResoEta = new TF1("fResoEta", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x) - ([3]*[3]+[4]*[4]/x+[5]*[5]/(x*x)))", resodeltajtptBins[1], resodeltajtptBins[nResoDeltaJtptBins]);
      fResoEta->SetParameters(fResoRecoEta->GetParameter(0), fResoRecoEta->GetParameter(1), fResoRecoEta->GetParameter(2), fResoGenEta->GetParameter(0), fResoGenEta->GetParameter(1), fResoGenEta->GetParameter(2));
      fResoEta->SetLineWidth(3);
      fResoEta->SetLineColor(kAzure+2);
      fResoEta->SetLineStyle(1);
      fResoEta->Draw("same");

      legResoEta->AddEntry(fResoRecoEta, "fit on reco", "l");
      legResoEta->AddEntry(fResoGenEta, "fit on gen", "l");
      legResoEta->AddEntry(fResoEta, "#sigma", "l");

      paramfDelta.at(index)->at(k).push_back(fResoRecoEta->GetParameter(0));
      paramfDelta.at(index)->at(k).push_back(fResoRecoEta->GetParameter(1));
      paramfDelta.at(index)->at(k).push_back(fResoRecoEta->GetParameter(2));
      paramfDelta.at(index)->at(k).push_back(fResoGenEta->GetParameter(0));
      paramfDelta.at(index)->at(k).push_back(fResoGenEta->GetParameter(1));
      paramfDelta.at(index)->at(k).push_back(fResoGenEta->GetParameter(2));
      parerrfDelta.at(index)->at(k).push_back(fResoRecoEta->GetParError(0));
      parerrfDelta.at(index)->at(k).push_back(fResoRecoEta->GetParError(1));
      parerrfDelta.at(index)->at(k).push_back(fResoRecoEta->GetParError(2));
      parerrfDelta.at(index)->at(k).push_back(fResoGenEta->GetParError(0));
      parerrfDelta.at(index)->at(k).push_back(fResoGenEta->GetParError(1));
      parerrfDelta.at(index)->at(k).push_back(fResoGenEta->GetParError(2));

      xjjroot::drawCMS(collisionsyst);
      legResoEta->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      cResoEta->SaveAs(Form("plotresos/cResoDeltaEta_%s_%d.pdf",outputname.Data(),k));

      delete fResoEta;
      delete fResoGenEta;
      delete fResoRecoEta;
      delete legResoEta;
      delete hemptyResoEta;
      delete cResoEta;
    }

  // TString paramfname[NP] = {"ScalePt", "ResoPt", "ResoPtCorr", "ResoPhi", "ResoEta", "ScalePtFfCorr", "ResoPtFfJecCorr", "ResoDrPhi", "ResoDrEta"};
  std::cout<<std::endl;
  for(int i=0;i<NP;i++)
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

  for(int i=0;i<DeltaNP;i++)
    {
      std::cout<<"std::vector<std::vector<Float_t>> "<<(ispp?Form("paramf%s_pp = {",paramfnameDelta[i].Data()):Form("paramf%s_PbPb = {",paramfnameDelta[i].Data()));
      for(int k=0;k<nCentBins;k++)
        {
          std::cout<<"{";
          for(int j=0;j<paramfDelta.at(i)->at(k).size();j++)
            std::cout<<paramfDelta.at(i)->at(k).at(j)<<(j==paramfDelta.at(i)->at(k).size()-1?"}":", ");
          std::cout<<(k==(nCentBins-1)?"};":",")<<std::endl;
        }
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
