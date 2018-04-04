#include "jetresolution.h"

Float_t plotxaxismin = 30;
// Float_t plotxaxismin = resojtptBins[0];
void jetreso_plothistqg(TString inputhistname, TString inputhistnameQ, TString inputhistnameG,
                        TString outputname, TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  djtcorr::setnCentBins(ispp);

  Bool_t isincl = inputhistname.Contains("incl");

  xjjroot::setgstyle();

  const int NP = 3;
  std::vector<TFile*> inf;
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  inf.push_back(infhist);
  TFile* infhistQ = new TFile(Form("%s.root",inputhistnameQ.Data()));
  if(!infhistQ->IsOpen()) return;
  inf.push_back(infhistQ);
  TFile* infhistG = new TFile(Form("%s.root",inputhistnameG.Data()));
  if(!infhistG->IsOpen()) return;
  inf.push_back(infhistG);

  std::vector<std::vector<std::vector<Float_t>>*> existf_pp = {&paramfScalePt_pp, &paramfScalePtQ_pp, &paramfScalePtG_pp};
  std::vector<std::vector<std::vector<Float_t>>*> existf_PbPb = {&paramfScalePt_PbPb, &paramfScalePtQ_PbPb, &paramfScalePtG_PbPb};
  std::vector<std::vector<std::vector<Float_t>>*>* existf = ispp?&existf_pp:&existf_PbPb;

  // std::vector<TString> qgname = {"incl", "quark", "gluon"};
  std::vector<Color_t> mcol = {kBlack, kAzure-6, kRed-2};
  std::vector<Color_t> lcol = {kGray+2, kAzure-4, kRed-9};
  std::vector<TString> legtex = {"Incl.", "Quark", "Gluon"};

  std::vector<TF1*> fScale(NP);

  TH1F* hqgScalePt[NP][NCentBins];
  TH1F* hqgScalePtCorr[NP][NCentBins];
  TH1F* hqgScalePtRMatGCorr[NP][NCentBins];
  for(int n=0;n<NP;n++)
    {
      fScale[n] = new TF1(Form("fScale%d",n), "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", plotxaxismin, resojtptBins[nResoJtptBins]);
      fScale[n]->SetLineWidth(3);
      fScale[n]->SetLineColor(lcol[n]);
      fScale[n]->SetLineStyle(9);
      for(int k=0;k<nCentBins;k++)
        {
          hqgScalePt[n][k] = (TH1F*)inf[n]->Get(Form("hScalePt_%d_%d",k,0));
          hqgScalePt[n][k]->SetName(Form("hScalePt_%d_%d",k,n)); 
          xjjroot::setthgrstyle(hqgScalePt[n][k], mcol[n], 24, 1.2, mcol[n], 1, 1, -1, -1, -1);         
          hqgScalePtCorr[n][k] = (TH1F*)inf[n]->Get(Form("hScalePtCorr_%d_%d",k,0));
          hqgScalePtCorr[n][k]->SetName(Form("hScalePtCorr_%d_%d",k,n));
          xjjroot::setthgrstyle(hqgScalePtCorr[n][k], mcol[n], 24, 1.2, mcol[n], 1, 1, -1, -1, -1);         
          hqgScalePtRMatGCorr[n][k] = (TH1F*)inf[n]->Get(Form("hScalePtRMatGCorr_%d_%d",k,0));
          hqgScalePtRMatGCorr[n][k]->SetName(Form("hScalePtRMatGCorr_%d_%d",k,n));
          xjjroot::setthgrstyle(hqgScalePtRMatGCorr[n][k], mcol[n], 24, 1.2, mcol[n], 1, 1, -1, -1, -1);         
        }
    }

  // Scale Pt
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePt = new TCanvas("cScalePt", "", 600, 600);
      TH2F* hemptyScalePt = new TH2F("hemptyScalePt", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen})", 10, plotxaxismin, resojtptBins[nResoJtptBins], 10, ispp?0.9:0.85, ispp?1.15:1.2);
      xjjroot::sethempty(hemptyScalePt, 0, 0.4);
      hemptyScalePt->Draw();
      TLegend* legScalePt = new TLegend(0.58, 0.88-NP*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePt);
      for(int n=0;n<NP;n++)
        {
          hqgScalePt[n][k]->Draw("same pe");
          legScalePt->AddEntry(hqgScalePt[n][k], legtex[n].Data(), "p");
          for(int m=0;m<existf->at(n)->at(k).size();m++)
            fScale[n]->SetParameter(m, existf->at(n)->at(k).at(m));
          fScale[n]->Draw("same");
        }
      xjjroot::drawCMS(collisionsyst); 
      legScalePt->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[0],jtetaBins[nJtetaBins]));
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), ispp?"PYTHIA":"PYTHIA + HYDJET");
      cScalePt->SaveAs(Form("plotqg/cScalePt_%s_%d.pdf",outputname.Data(),k));

      delete legScalePt;
      delete hemptyScalePt;
      delete cScalePt;
    }

  // ScalePtCorr (no fit)
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePtCorr = new TCanvas("cScalePtCorr", "", 600, 600);
      TH2F* hemptyScalePtCorr = new TH2F("hemptyScalePtCorr", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, plotxaxismin, resojtptBins[nResoJtptBins], 10, ispp?0.9:0.85, ispp?1.15:1.2);
      xjjroot::sethempty(hemptyScalePtCorr, 0, 0.4);
      hemptyScalePtCorr->Draw();
      TLegend* legScalePtCorr = new TLegend(0.58, 0.88-NP*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtCorr);
      xjjroot::drawline(plotxaxismin, 1.00, resojtptBins[nResoJtptBins], 1.00, kGray+2, 10, 3);
      xjjroot::drawline(plotxaxismin, 1.05, resojtptBins[nResoJtptBins], 1.05, kGray, 10, 3);
      xjjroot::drawline(plotxaxismin, 0.95, resojtptBins[nResoJtptBins], 0.95, kGray, 10, 3);
      for(int n=0;n<NP;n++)
        {
          hqgScalePtCorr[n][k]->Draw("same pe");
          legScalePtCorr->AddEntry(hqgScalePtCorr[n][k], legtex[n].Data(), "p");
        }
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[0],jtetaBins[nJtetaBins]));
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtCorr->Draw();
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), ispp?"PYTHIA":"PYTHIA + HYDJET");
      cScalePtCorr->SaveAs(Form("plotqg/cScalePtCorr_%s_%d.pdf",outputname.Data(),k));

      delete legScalePtCorr;
      delete hemptyScalePtCorr;
      delete cScalePtCorr;
    }

  // ScalePtRMatGCorr (no fit)
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* cScalePtRMatGCorr = new TCanvas("cScalePtRMatGCorr", "", 600, 600);
      TH2F* hemptyScalePtRMatGCorr = new TH2F("hemptyScalePtRMatGCorr", ";Gen jet p_{T} (GeV/c);#mu(p_{T}^{reco} / p_{T}^{gen}), Corr", 10, plotxaxismin, resojtptBins[nResoJtptBins], 10, ispp?0.9:0.85, ispp?1.15:1.2);
      xjjroot::sethempty(hemptyScalePtRMatGCorr, 0, 0.4);
      hemptyScalePtRMatGCorr->Draw();
      TLegend* legScalePtRMatGCorr = new TLegend(0.58, 0.88-NP*0.06, 0.85, 0.88);
      xjjroot::setleg(legScalePtRMatGCorr);
      xjjroot::drawline(plotxaxismin, 1.00, resojtptBins[nResoJtptBins], 1.00, kGray+2, 10, 3);
      xjjroot::drawline(plotxaxismin, 1.05, resojtptBins[nResoJtptBins], 1.05, kGray, 10, 3);
      xjjroot::drawline(plotxaxismin, 0.95, resojtptBins[nResoJtptBins], 0.95, kGray, 10, 3);
      for(int n=0;n<NP;n++)
        {
          hqgScalePtRMatGCorr[n][k]->Draw("same pe");
          legScalePtRMatGCorr->AddEntry(hqgScalePtRMatGCorr[n][k], legtex[n].Data(), "p");
        }
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("%.1f < |#eta^{gen jet}| < %.1f",jtetaBins[0],jtetaBins[nJtetaBins]));
      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
      xjjroot::drawCMS(collisionsyst); 
      legScalePtRMatGCorr->Draw();
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), ispp?"PYTHIA":"PYTHIA + HYDJET");
      cScalePtRMatGCorr->SaveAs(Form("plotqg/cScalePtRMatGCorr_%s_%d.pdf",outputname.Data(),k));

      delete legScalePtRMatGCorr;
      delete hemptyScalePtRMatGCorr;
      delete cScalePtRMatGCorr;
    }
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      jetreso_plothistqg(argv[1], argv[2], argv[3], argv[4], argv[5]);
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
