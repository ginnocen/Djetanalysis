#include "jetresolution.h"

Int_t hidemuleta = 1;
Float_t plotxmin = 30;
void jetreso_plothist(TString inputhistname, TString outputname,
                      TString collisionsyst, Int_t verboseonplot=0)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  djtcorr::setnCentBins(ispp);

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;

  // TString paramfname[5] = {"ScalePt", "ResoPt", "ResoPtCorr", "ResoPhi", "ResoEta"};
  TString paramfname[] = {"ScaleRecoPt"};
  const int npar = sizeof(paramfname) / sizeof(paramfname[0]);
  std::vector<std::vector<std::vector<Float_t>>*> paramf(npar);
  for(int i=0;i<npar;i++)
    paramf.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);
  std::vector<std::vector<std::vector<Float_t>>*> parerrf(npar);
  for(int i=0;i<npar;i++)
    parerrf.at(i) = new std::vector<std::vector<Float_t>>(nCentBins);

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePt = new TCanvas("cScalePt", "", 600, 600);
      TH2F* hemptyScalePt = new TH2F("hemptyScalePt", ";Reco jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", 10, plotxmin, resojtptBins[nResoJtptBins], 10, ispp?0.95:0.9, ispp?1.15:1.5);
      xjjroot::sethempty(hemptyScalePt, 0, 0.4);
      hemptyScalePt->Draw();
      TLegend* legScalePt = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePt);
      for(int j=0;j<nJtetaBins+1;j++)
        {
          if(hidemuleta && j) continue;
          xjjroot::setthgrstyle(hScalePt[k][j], jtetaColor[j], 24, 1.2, jtetaColor[j], 1, 1, -1, -1, -1);
          hScalePt[k][j]->Draw("same pe");
          TString tleg = j==0?Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[0],jtetaBins[j]):Form("%.1f < |#eta^{reco jet}| < %.1f",jtetaBins[j-1],jtetaBins[j]);
          legScalePt->AddEntry(hScalePt[k][j], tleg.Data(), "p");
        }
      TF1* fScalePt = new TF1("fScalePt", "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", plotxmin, resojtptBins[nResoJtptBins]);
      fScalePt->SetParLimits(0, 0.98, 1.02);
      fScalePt->SetParameter(0, 1);
      fScalePt->SetParameter(1, 0);
      fScalePt->SetParameter(2, 0.5);
      if(ispp) fScalePt->FixParameter(3, 0);
      fScalePt->SetLineWidth(3);
      fScalePt->SetLineColor(kGray+3);
      fScalePt->SetLineStyle(2);
      hScalePt[k][0]->Fit("fScalePt", "L q", "", resojtptBins[2], resojtptBins[nResoJtptBins]);
      hScalePt[k][0]->Fit("fScalePt", "m q", "", resojtptBins[2], resojtptBins[nResoJtptBins]);

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
      TH2F* hemptyScalePtCorr = new TH2F("hemptyScalePtCorr", ";Reco jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, plotxmin, resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtCorr, 0, 0.4);
      hemptyScalePtCorr->Draw();
      TLegend* legScalePtCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtCorr);
      xjjroot::drawline(plotxmin, 1.02, resojtptBins[nResoJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(plotxmin, 0.98, resojtptBins[nResoJtptBins], 0.98, kGray+3, 2, 3);
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
      TH2F* hemptyScalePtFfCorr = new TH2F("hemptyScalePtFfCorr", ";Reco jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), frag-dep Corr", 10, plotxmin, resojtptBins[nResoJtptBins], 10, ispp?0.9:0.8, ispp?1.1:1.2);
      xjjroot::sethempty(hemptyScalePtFfCorr, 0, 0.4);
      hemptyScalePtFfCorr->Draw();
      TLegend* legScalePtFfCorr = new TLegend(0.53, 0.88-(nJtetaBins+1-nJtetaBins*hidemuleta)*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtFfCorr);
      xjjroot::drawline(plotxmin, 1.02, resojtptBins[nResoJtptBins], 1.02, kGray+3, 2, 3);
      xjjroot::drawline(plotxmin, 0.98, resojtptBins[nResoJtptBins], 0.98, kGray+3, 2, 3);
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

  // TString paramfname[5] = {"ScalePt", "ResoPt", "ResoPtCorr", "ResoPhi", "ResoEta"};
  std::cout<<std::endl;
  for(int i=0;i<npar;i++)
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
