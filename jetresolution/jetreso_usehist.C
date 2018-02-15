#include "jetresolution.h"

void jetreso_usehist(TString inputhistname, TString outputname,
                     TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);
  
  xjjroot::setgstyle();

  if(createhists("usehist")) return;
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "usehist")) return;
  TFile* infresolution = new TFile(Form("../includes/Resolution/hist_Djet_reso_%s_ResolutionEtaPhi.root",collisionsyst.Data()));
  if(!infresolution->IsOpen()) return;
  if(gethists(infresolution, "usehistetaphi")) return;

  std::vector<TString> name = {"Pt", "PtCorr", "Phi", "Eta", "PtFfCorr", "PtFfJecCorr", "PtRMatGCorr", "DrPhi", "DrEta"};
  std::vector<TH1F**> ahHistoResoX = {(TH1F**)ahHistoResoPt, (TH1F**)ahHistoResoPtCorr, (TH1F**)ahHistoResoPhi, (TH1F**)ahHistoResoEta, (TH1F**)ahHistoResoPtFfCorr, (TH1F**)ahHistoResoPtFfJecCorr, (TH1F**)ahHistoResoPtRMatGCorr, (TH1F**)ahHistoResoDrPhi, (TH1F**)ahHistoResoDrEta};
  std::vector<TH1F**> hScaleX = {(TH1F**)hScalePt, (TH1F**)hScalePtCorr, (TH1F**)hScalePhi, (TH1F**)hScaleEta, (TH1F**)hScalePtFfCorr, (TH1F**)hScalePtFfJecCorr, (TH1F**)hScalePtRMatGCorr, (TH1F**)hScaleDrPhi, (TH1F**)hScaleDrEta};
  std::vector<TH1F**> hResoX = {(TH1F**)hResoPt, (TH1F**)hResoPtCorr, (TH1F**)hResoPhi, (TH1F**)hResoEta, (TH1F**)hResoPtFfCorr, (TH1F**)hResoPtFfJecCorr, (TH1F**)hResoPtRMatGCorr, (TH1F**)hResoDrPhi, (TH1F**)hResoDrEta};
  std::vector<Int_t> nResoJtXBins = {nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtdrBins, nResoJtdrBins};
  std::vector<TString> xtitle = {"p_{T}^{reco}/p_{T}^{gen}", "p_{T}^{reco}/p_{T}^{gen},Corr", "#phi^{reco}-#phi^{gen}", "#eta^{reco}-#eta^{gen}", "p_{T}^{reco}/p_{T}^{gen},frag-depCorr", "p_{T}^{reco}/p_{T}^{gen},frag-depCorr+JEC", "p_{T}^{reco}/p_{T}^{gen},RMatGCorr", "#phi^{reco}-#phi^{gen}", "#eta^{reco}-#eta^{gen}"};
  std::vector<Float_t> xmin = {0, 0, 0-xrangeAng, 0-xrangeAng, 0, 0, 0, 0-xrangeAng, 0-xrangeAng};
  std::vector<Float_t> xmax = {2, 2, xrangeAng, xrangeAng, 2, 2, 2, xrangeAng, xrangeAng};
  std::vector<Float_t> ymin = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<Float_t> ymax = {0.2, 0.2, (float)(ispp?0.2:0.1), (float)(ispp?0.2:0.1), 0.2, 0.2, 0.2, (float)(ispp?0.2:0.1), (float)(ispp?0.2:0.1)};
  std::vector<Float_t> param0 = {1, 1, 0.01, 0.01, 1, 1, 1, 0.01, 0.01};
  std::vector<Float_t> param1 = {1, 1, 0, 0, 1, 1, 1, 0, 0};
  std::vector<Float_t> param2 = {0.2, 0.2, 0.01, 0.01, 0.2, 0.2, 0.2, 0.01, 0.01};

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      for(int j=0;j<nJtetaBins+1;j++)
        {
          TString texjteta = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f", jtetaBins[j-1], jtetaBins[j]);
          for(int l=0;l<9;l++)
            {
              TCanvas* c15 = new TCanvas("c15", "", 1000, 600);
              c15->Divide(5, 3);
              TH2F* hemptyX = new TH2F("hemptyX", Form(";%s;Probability", xtitle.at(l).Data()), 10, xmin.at(l), xmax.at(l), 10, ymin.at(l), ymax.at(l));
              xjjroot::sethempty(hemptyX, 0, 0.4);
              std::vector<TF1*>* afX = new std::vector<TF1*>(nResoJtXBins[l]);
              std::vector<TF1*>* afX1 = new std::vector<TF1*>(nResoJtXBins[l]);
              for(int i=0;i<nResoJtXBins[l];i++)
                {
                  TString texjtpt = Form("%.0f < p_{T}^{gen jet} < %.0f GeV", resojtptBins[i], resojtptBins[i+1]);
                  TString texjtdr = Form("%.2f < #DeltaR < %.2f", resojtdrBins[i], resojtdrBins[i+1]);

                  TF1* fX = new TF1("fX", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  fX->SetLineWidth(2);
                  fX->SetLineColor(kBlue);
                  fX->SetParLimits(2, 0, 1);
                  fX->SetParameter(0, param0.at(l));
                  fX->SetParameter(1, param1.at(l));
                  fX->SetParameter(2, param2.at(l));
                  TCanvas* cX = new TCanvas("cX", "", 600, 600);
                  cX->cd();
                  hemptyX->Draw();
                  (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Scale(1./(ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Integral());
                  xjjroot::setthgrstyle((ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i], kBlack, 24, 1., kBlack, 1, 1, -1, -1, -1);
                  (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Draw("same pe");
                  (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Fit("fX", "L q", "", xmin.at(l), xmax.at(l));
                  (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Fit("fX", "m q", "", xmin.at(l), xmax.at(l));
                  Float_t meanX = fX->GetParameter(1);
                  Float_t sigmaX = fX->GetParameter(2);
                  TF1* fX1 = new TF1("fX1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  fX1->SetParameter(0, fX->GetParameter(0));
                  fX1->SetParameter(1, fX->GetParameter(1));
                  fX1->SetParameter(2, fX->GetParameter(2));
                  fX1->SetLineWidth(2);
                  fX1->SetLineColor(kRed);
                  fX1->Draw("same");
                  fX->SetParameter(1, param1.at(l));
                  if(l==2||l==3||l==7||l==8) fX->SetParLimits(1, -0.002, 0.002);
                  (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Fit("fX", "L q", "", meanX-((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX, meanX+((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX);
                  (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Fit("fX", "m q", "", meanX-((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX, meanX+((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX);
                  fX->Draw("same");
                  (hScaleX.at(l))[k*(nJtetaBins+1)+j]->SetBinContent(i+1, fX->GetParameter(1));
                  (hScaleX.at(l))[k*(nJtetaBins+1)+j]->SetBinError(i+1, fX->GetParError(1));
                  (hResoX.at(l))[k*(nJtetaBins+1)+j]->SetBinContent(i+1, fX->GetParameter(2));
                  (hResoX.at(l))[k*(nJtetaBins+1)+j]->SetBinError(i+1, fX->GetParError(2));
                  afX->at(i) = xjjroot::copyobject(fX, Form("fX%d",i));
                  afX1->at(i) = xjjroot::copyobject(fX1, Form("fX1%d",i));
                  Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), (l<7?texjtpt:texjtdr));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                  if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fX->GetParameter(2), fX->GetParError(2)));
                  xjjroot::drawCMS(collisionsyst);
                  // cX->SaveAs(Form("plotfits/cfitPt%s_%s_%d_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,j,i));

                  c15->cd(i+1);
                  hemptyX->Draw();
                  (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i]->Draw("same pe");
                  afX1->at(i)->Draw("same");
                  afX->at(i)->Draw("same");
                  texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), (l<7?texjtpt:texjtdr));
                  if(!i)
                    {
                      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                      xjjroot::drawCMS(collisionsyst);
                    }
                  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fX->GetParameter(2), fX->GetParError(2)));

                  delete fX1;
                  delete fX;
                  delete cX;
                }
              c15->SaveAs(Form("plotfitsall/cfitall%s_%s_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,j));

              delete afX1;
              delete afX;
              delete hemptyX;
              delete c15;
            }
        }
    }

  std::vector<TString> nameDelta = {"RecoDeltaPhi", "RecoDeltaEta", "GenDeltaPhi", "GenDeltaEta"};
  std::vector<TH1F**> ahHistoResoDeltaX = {(TH1F**)ahHistoResoRecoDeltaPhi, (TH1F**)ahHistoResoRecoDeltaEta, (TH1F**)ahHistoResoGenDeltaPhi, (TH1F**)ahHistoResoGenDeltaEta};
  std::vector<TH1F**> hScaleDeltaX = {(TH1F**)hScaleRecoDeltaPhi, (TH1F**)hScaleRecoDeltaEta, (TH1F**)hScaleGenDeltaPhi, (TH1F**)hScaleGenDeltaEta};
  std::vector<TH1F**> hResoDeltaX = {(TH1F**)hResoRecoDeltaPhi, (TH1F**)hResoRecoDeltaEta, (TH1F**)hResoGenDeltaPhi, (TH1F**)hResoGenDeltaEta};
  std::vector<Int_t> nResoJtXBinsDelta = {nResoDeltaJtptBins, nResoDeltaJtptBins, nResoDeltaJtptBins, nResoDeltaJtptBins};
  std::vector<TString> xtitleDelta = {"#phi^{lead D}_{reco}-#phi^{jet}_{reco}", "#eta^{lead D}_{reco}-#eta^{jet}_{reco}", "#phi^{lead D}_{gen}-#phi^{jet}_{gen}", "#eta^{lead D}_{gen}-#eta^{jet}_{gen}"};

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      for(int j=0;j<nJtetaBins+1;j++)
        {
          TString texjteta = j==0?"|#eta^{gen jet}| < 1.6":Form("%.1f < |#eta^{gen jet}| < %.1f", jtetaBins[j-1], jtetaBins[j]);
          for(int l=0;l<4;l++)
            {
              TCanvas* c15 = new TCanvas("c15", "", 1000, 600);
              c15->Divide(5, 3);
              TH2F* hemptyX = new TH2F("hemptyX", Form(";%s;Probability", xtitleDelta.at(l).Data()), 10, -0.2, 0.2, 10, 0, 0.2);
              xjjroot::sethempty(hemptyX, 0, 0.4);
              std::vector<TF1*>* afX = new std::vector<TF1*>(nResoJtXBinsDelta[l]);
              for(int i=0;i<nResoJtXBinsDelta[l];i++)
                {
                  TString texjtpt = Form("%.0f < p_{T}^{gen jet} < %.0f GeV", resojtptBins[i], resojtptBins[i+1]);

                  TF1* fX = new TF1("fX", "[0]*([3]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])+(1-[3])*Gaus(x,[1],[4])/(TMath::Sqrt(2*3.14159265)*[4]))+[5]", -0.2, 0.2);
                  fX->SetLineWidth(2);
                  fX->SetLineColor(kBlue);
                  fX->SetParLimits(2, 0, 1);
                  fX->SetParameter(0, 0.01);
                  fX->SetParameter(1, 0);
                  fX->SetParameter(2, 0.05);
                  fX->SetParameter(4, 0.1);
                  fX->SetParameter(3, 0.1);
                  fX->SetParameter(5, 0);
                  fX->SetParLimits(5, 0, 0.1);
                  fX->SetParLimits(3, 0, 1);
                  fX->SetParLimits(2, 0.005, 0.1);
                  fX->SetParLimits(4, 0.005, 0.1);
                  if(nameDelta[l].Contains("Gen") || ispp)
                    {
                      fX->SetParLimits(2, 0.005, 0.06);
                      fX->SetParLimits(4, 0.005, 0.06);
                      fX->SetParameter(2, 0.01);
                      fX->SetParameter(4, 0.05);
                    }
                  TCanvas* cX = new TCanvas("cX", "", 600, 600);
                  cX->cd();
                  hemptyX->Draw();
                  (ahHistoResoDeltaX.at(l))[k*nResoJtXBinsDelta[l]*(nJtetaBins+1)+j*nResoJtXBinsDelta[l]+i]->Scale(1./(ahHistoResoDeltaX.at(l))[k*nResoJtXBinsDelta[l]*(nJtetaBins+1)+j*nResoJtXBinsDelta[l]+i]->Integral());
                  xjjroot::setthgrstyle((ahHistoResoDeltaX.at(l))[k*nResoJtXBinsDelta[l]*(nJtetaBins+1)+j*nResoJtXBinsDelta[l]+i], kBlack, 24, 1., kBlack, 1, 1, -1, -1, -1);
                  (ahHistoResoDeltaX.at(l))[k*nResoJtXBinsDelta[l]*(nJtetaBins+1)+j*nResoJtXBinsDelta[l]+i]->Draw("same pe");
                  (ahHistoResoDeltaX.at(l))[k*nResoJtXBinsDelta[l]*(nJtetaBins+1)+j*nResoJtXBinsDelta[l]+i]->Fit("fX", "L q", "", -0.2, 0.2);
                  (ahHistoResoDeltaX.at(l))[k*nResoJtXBinsDelta[l]*(nJtetaBins+1)+j*nResoJtXBinsDelta[l]+i]->Fit("fX", "m q", "", -0.2, 0.2);
                  Float_t meanX = fX->GetParameter(1);
                  Int_t iXs = fX->GetParameter(2)<fX->GetParameter(4)?2:4;
                  Int_t iXl = fX->GetParameter(2)>fX->GetParameter(4)?2:4;
                  (hScaleDeltaX.at(l))[k*(nJtetaBins+1)+j]->SetBinContent(i+1, fX->GetParameter(1));
                  (hScaleDeltaX.at(l))[k*(nJtetaBins+1)+j]->SetBinError(i+1, fX->GetParError(1));
                  (hResoDeltaX.at(l))[k*(nJtetaBins+1)+j]->SetBinContent(i+1, fX->GetParameter(iXs));
                  (hResoDeltaX.at(l))[k*(nJtetaBins+1)+j]->SetBinError(i+1, fX->GetParError(iXs));
                  afX->at(i) = xjjroot::copyobject(fX, Form("fX%d",i));
                  Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                  if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma_{n} = %.3f #pm %.3f", fX->GetParameter(iXs), fX->GetParError(iXs)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma_{w} = %.3f #pm %.3f", fX->GetParameter(iXl), fX->GetParError(iXl)));
                  xjjroot::drawCMS(collisionsyst);
                  // cX->SaveAs(Form("plotfits/cfitPt%s_%s_%d_%d_%d.pdf",nameDelta.at(l).Data(),outputname.Data(),k,j,i));

                  c15->cd(i+1);
                  hemptyX->Draw();
                  (ahHistoResoDeltaX.at(l))[k*nResoJtXBinsDelta[l]*(nJtetaBins+1)+j*nResoJtXBinsDelta[l]+i]->Draw("same pe");
                  afX->at(i)->Draw("same");
                  texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
                  if(!i)
                    {
                      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                      xjjroot::drawCMS(collisionsyst);
                    }
                  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma_{n} = %.3f #pm %.3f", fX->GetParameter(iXs), fX->GetParError(iXs)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma_{w} = %.3f #pm %.3f", fX->GetParameter(iXl), fX->GetParError(iXl)));

                  delete fX;
                  delete cX;
                }
              c15->SaveAs(Form("plotfitsall/cfitallDelta%s_%s_%d_%d.pdf",nameDelta.at(l).Data(),outputname.Data(),k,j));

              delete afX;
              delete hemptyX;
              delete c15;
            }
        }
    }



  //-------------------------------------------------------------------------//

  /*

    std::vector<TString> nameEtaPhi = {"EtaPhi", "DrEtaPhi"};
    std::vector<TH2F**> ahHistoResoEtaPhiX = {(TH2F**)ahHistoResoEtaPhi, (TH2F**)ahHistoResoDrEtaPhi};
  
    gStyle->SetPadRightMargin(xjjroot::margin_pad_right+0.08);
    gStyle->SetPadLeftMargin(xjjroot::margin_pad_left-0.03);
    for(int k=0;k<nCentBins;k++)
    {
    TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
    for(int l=1;l<2;l++)
    {
    TCanvas* c15 = new TCanvas("c15", "", 1000, 600);
    c15->Divide(5, 3);
    for(int i=0;i<nResoJtdrBins;i++)
    {
    c15->cd(i+1);
    TString texjtdr = Form("%.2f < #DeltaR < %.2f", resojtdrBins[i], resojtdrBins[i+1]);  
    xjjroot::sethempty((ahHistoResoEtaPhiX.at(l))[k*nResoJtdrBins+i]);
    (ahHistoResoEtaPhiX.at(l))[k*nResoJtdrBins+i]->Draw("colz");
    Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
    xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtdr);
    if(!i)
    {
    xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{gen jet}| < 1.6");
    if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
    xjjroot::drawCMS(collisionsyst, -0.03);
    }
    }
    c15->SaveAs(Form("plotfitsall/cfitDrall%s_%s_%d.pdf",nameEtaPhi.at(l).Data(),outputname.Data(),k));
    delete c15;
    }
    }

    gStyle->SetPalette(56);
    // TColor::InvertPalette();
    gStyle->SetPaintTextFormat("1.2f");
    gStyle->SetPadRightMargin(xjjroot::margin_pad_right+0.08);
    gStyle->SetPadLeftMargin(xjjroot::margin_pad_left-0.03);
    std::vector<TString> step = {"hRecoVsGenPt", "hRecoVsGenPtCorr", "hRecoVsGenPtRMatGStep1Corr", "hRecoVsGenPtRMatGCorr", "hRecoVsGenPtFfCorr", "hRecoVsGenPtFfJecCorr", "hGenSmearVsGenPt"};
    std::vector<TH2F*> hist = {hRecoVsGenPt, hRecoVsGenPtCorr, hRecoVsGenPtRMatGStep1Corr, hRecoVsGenPtRMatGCorr, hRecoVsGenPtFfCorr, hRecoVsGenPtFfJecCorr, hGenSmearVsGenPt};
    std::vector<TH2F*> hRatio(step.size()-1);
    std::vector<TH2F*> hRecoNorm(step.size());
    for(int i=0;i<step.size();i++)
    {
    hRecoNorm[i] = (TH2F*)hist[i]->Clone(Form("hRecoNorm_%s",step[i].Data()));
    if(step[i]!="hGenSmearVsGenPt")
    {
    hRatio[i] = (TH2F*)hist[i]->Clone(Form("hRatio_%s",step[i].Data()));
    hRatio[i]->Divide(hGenSmearVsGenPt);
    // hRatio[i] = (TH2F*)hGenSmearVsGenPt->Clone(Form("hRatio_%s",step[i].Data()));
    // hRatio[i]->Divide(hist[i]);
    }
    for(int iy=0;iy<nMapjtptBins;iy++)
    {
    Float_t reconorm = 0;
    for(int ix=0;ix<nMapjtptBins;ix++)
    reconorm += hist[i]->GetBinContent(ix+1, iy+1);
    for(int ix=0;ix<nMapjtptBins;ix++)
    {
    hist[i]->SetBinContent(ix+1, iy+1, hist[i]->GetBinContent(ix+1, iy+1)/hGenPtCorrNorm->GetBinContent(ix+1));
    hist[i]->SetBinError(ix+1, iy+1, hist[i]->GetBinError(ix+1, iy+1)/hGenPtCorrNorm->GetBinError(ix+1));
    hRecoNorm[i]->SetBinContent(ix+1, iy+1, hRecoNorm[i]->GetBinContent(ix+1, iy+1)/reconorm);
    hRecoNorm[i]->SetBinError(ix+1, iy+1, hRecoNorm[i]->GetBinError(ix+1, iy+1)/reconorm);
    if(step[i]!="hGenSmearVsGenPt")
    {
    // if(hRatio[i]->GetBinContent(ix+1, iy+1) > 5) hRatio[i]->SetBinContent(ix+1, iy+1, 0);
    }
    }
    }
    }
  
    for(int i=0;i<step.size();i++)
    {
    gStyle->SetPalette(56);
    TCanvas* cmap = new TCanvas("cmap", "", 600, 600);
    xjjroot::sethempty(hist[i]);
    hist[i]->Draw("colz text");
    xjjroot::drawCMS(collisionsyst, -0.03);
    cmap->SaveAs(Form("plotresos/cmap_%s_%s.pdf",collisionsyst.Data(),step[i].Data()));
    delete cmap;

    TCanvas* cmapreconorm = new TCanvas("cmapreconorm", "", 600, 600);
    xjjroot::sethempty(hRecoNorm[i]);
    hRecoNorm[i]->Draw("colz text");
    xjjroot::drawCMS(collisionsyst, -0.03);
    cmapreconorm->SaveAs(Form("plotresos/cmapreconorm_%s_%s.pdf",collisionsyst.Data(),step[i].Data()));
    delete cmapreconorm;

    if(step[i]=="hGenSmearVsGenPt") continue;

    gStyle->SetPalette(55);
    TCanvas* cratio = new TCanvas("cratio", "", 600, 600);
    // cratio->SetLogz();
    xjjroot::sethempty(hRatio[i]);
    hRatio[i]->Draw("colz text");
    xjjroot::drawCMS(collisionsyst, -0.03);
    cratio->SaveAs(Form("plotresos/cratio_%s_%s.pdf",collisionsyst.Data(),step[i].Data()));
    delete cratio;
    }
  */

  TFile* outf = new TFile(Form("rootfiles/reso_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("usehist")) return;
  outf->Write();
  outf->Close();
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
