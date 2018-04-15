#include "jetresolution.h"

void jetreso_usehist(TString inputhistname, TString outputname,
                     TString collisionsyst)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);
  djtcorr::setnCentBins(ispp);

  Bool_t isincl = inputhistname.Contains("incl");
  
  void sethpull(TH1* hist_hpull);
  xjjroot::setgstyle();

  if(createhists("usehist")) return;
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "usehist")) return;
  // TFile* infresolution = new TFile(Form("../includes/Resolution/hist_Djet_reso_%s_ResolutionEtaPhi.root",collisionsyst.Data()));
  // if(!infresolution->IsOpen()) return;
  // if(gethists(infresolution, "usehistetaphi")) return;

  std::vector<TString> name = {"Pt", "PtCorr", "Phi", "Eta", "PtFfCorr", "PtFfJecCorr", "PtRMatGCorr"};
  std::vector<TH1F**> ahHistoResoX = {(TH1F**)ahHistoResoPt, (TH1F**)ahHistoResoPtCorr, (TH1F**)ahHistoResoPhi, (TH1F**)ahHistoResoEta, (TH1F**)ahHistoResoPtFfCorr, (TH1F**)ahHistoResoPtFfJecCorr, (TH1F**)ahHistoResoPtRMatGCorr};
  std::vector<TH1F**> ahHistoPullX = {(TH1F**)ahHistoPullPt, (TH1F**)ahHistoPullPtCorr, (TH1F**)ahHistoPullPhi, (TH1F**)ahHistoPullEta, (TH1F**)ahHistoPullPtFfCorr, (TH1F**)ahHistoPullPtFfJecCorr, (TH1F**)ahHistoPullPtRMatGCorr};
  std::vector<TH1F**> hScaleX = {(TH1F**)hScalePt, (TH1F**)hScalePtCorr, (TH1F**)hScalePhi, (TH1F**)hScaleEta, (TH1F**)hScalePtFfCorr, (TH1F**)hScalePtFfJecCorr, (TH1F**)hScalePtRMatGCorr};
  std::vector<TH1F**> hResoX = {(TH1F**)hResoPt, (TH1F**)hResoPtCorr, (TH1F**)hResoPhi, (TH1F**)hResoEta, (TH1F**)hResoPtFfCorr, (TH1F**)hResoPtFfJecCorr, (TH1F**)hResoPtRMatGCorr};
  std::vector<Int_t> nResoJtXBins = {nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins, nResoJtptBins};
  std::vector<TString> xtitle = {"p_{T}^{reco}/p_{T}^{gen}", "p_{T}^{reco}/p_{T}^{gen},Corr", "#phi^{reco}-#phi^{gen}", "#eta^{reco}-#eta^{gen}", "p_{T}^{reco}/p_{T}^{gen},frag-depCorr", "p_{T}^{reco}/p_{T}^{gen},frag-depCorr+JEC", "p_{T}^{reco}/p_{T}^{gen},RMatGCorr"};
  std::vector<Float_t> xmin = {0, 0, 0-xrangeAng, 0-xrangeAng, 0, 0, 0};
  std::vector<Float_t> xmax = {2, 2, xrangeAng, xrangeAng, 2, 2, 2};
  std::vector<Float_t> ymin = {0, 0, 0, 0, 0, 0, 0};
  std::vector<Float_t> ymax = {0.2, 0.2, (float)(ispp?0.2:0.1), (float)(ispp?0.2:0.1), 0.2, 0.2, 0.2};
  std::vector<Float_t> param0 = {1, 1, 0.01, 0.01, 1, 1, 1};
  std::vector<Float_t> param1 = {1, 1, 0, 0, 1, 1, 1};
  std::vector<Float_t> param2 = {0.2, 0.2, 0.01, 0.01, 0.2, 0.2, 0.2};

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      for(int j=0;j<nJtetaBins+1;j++)
        {
          TString texjteta = j==0?Form("%.1f < |#eta^{gen jet}| < %.1f", jtetaBins[0], jtetaBins[nJtetaBins]):Form("%.1f < |#eta^{gen jet}| < %.1f", jtetaBins[j-1], jtetaBins[j]);
          for(int l=0;l<7;l++)
            {
              TCanvas* c15 = new TCanvas("c15", "", 1200, 1200);
              c15->Divide(4, 4);
              TCanvas* cpull15 = new TCanvas("cpull15", "", 1200, 1200);
              cpull15->Divide(4, 4);
              std::vector<TPad*> pFit(nResoJtXBins[l]);
              std::vector<TPad*> pPull(nResoJtXBins[l]);
              for(int i=0;i<nResoJtXBins[l];i++)
                {
                  cpull15->cd(i+1);
                  pFit[i] = new TPad(Form("pFit%d",i),"",0,0.3,1,1);
                  pFit[i]->SetBottomMargin(0);
                  pFit[i]->Draw();
                  cpull15->cd(i+1);
                  pPull[i] = new TPad(Form("pPull%d",i),"",0,0,1,0.3);
                  pPull[i]->SetTopMargin(0);
                  pPull[i]->SetBottomMargin(0.3);
                  pPull[i]->Draw();
                }
              TH2F* hemptyX = new TH2F("hemptyX", Form(";%s;Probability", xtitle.at(l).Data()), 10, xmin.at(l), xmax.at(l), 10, ymin.at(l), ymax.at(l));
              xjjroot::sethempty(hemptyX, 0, 0.4);
              std::vector<TF1*>* afX = new std::vector<TF1*>(nResoJtXBins[l]);
              std::vector<TF1*>* afX1 = new std::vector<TF1*>(nResoJtXBins[l]);
              for(int i=0;i<nResoJtXBins[l];i++)
                {
                  TString texjtpt = Form("%.0f < p_{T}^{gen jet} < %.0f GeV", resojtptBins[i], resojtptBins[i+1]);
                  TString texjtdr = Form("%.2f < #DeltaR < %.2f", resojtdrBins[i], resojtdrBins[i+1]);

                  TH1F* hfit = (ahHistoResoX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i];
                  TH1F* hpull = (ahHistoPullX.at(l))[k*nResoJtXBins[l]*(nJtetaBins+1)+j*nResoJtXBins[l]+i];

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
                  hfit->Scale(1./hfit->Integral());
                  xjjroot::setthgrstyle(hfit, kBlack, 24, 1., kBlack, 1, 1, -1, -1, -1);
                  hfit->Draw("same pe");
                  hfit->Fit("fX", "L q", "", xmin.at(l), xmax.at(l));
                  hfit->Fit("fX", "m q", "", xmin.at(l), xmax.at(l));
                  Float_t meanX = fX->GetParameter(1);
                  Float_t sigmaX = fX->GetParameter(2);
                  if(i>1 && sigmaX > 0.4) sigmaX = 0.2;
                  TF1* fX1 = new TF1("fX1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  fX1->SetParameter(0, fX->GetParameter(0));
                  fX1->SetParameter(1, fX->GetParameter(1));
                  fX1->SetParameter(2, fX->GetParameter(2));
                  fX1->SetLineWidth(2);
                  fX1->SetLineColor(kRed);
                  fX1->Draw("same");
                  fX->SetParameter(1, param1.at(l));
                  if(l==2||l==3||l==7||l==8) fX->SetParLimits(1, -0.002, 0.002);
                  hfit->Fit("fX", "L q", "", meanX-((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX, meanX+((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX);
                  hfit->Fit("fX", "m q", "", meanX-((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX, meanX+((ispp&&(l==2||l==3||l==7||l==8))?0.5:2)*sigmaX);
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

                  xjjroot::setthgrstyle(hpull, kBlack, 24, 0.7, kBlack, 1, 1, -1, -1, -1);
                  sethpull(hpull);
                  for(int ibin=0;ibin<hfit->GetNbinsX();ibin++)
                    {
                      Float_t nfit = afX->at(i)->Integral(hfit->GetBinLowEdge(ibin+1),hfit->GetBinLowEdge(ibin+1)+hfit->GetBinWidth(ibin+1))/hfit->GetBinWidth(ibin+1);
                      if(hfit->GetBinContent(ibin+1)==0)
                        {
                          hpull->SetBinContent(ibin+1,0.);
                        }
                      else hpull->SetBinContent(ibin+1,(hfit->GetBinContent(ibin+1)-nfit)/hfit->GetBinError(ibin+1));
                      hpull->SetBinError(ibin+1,0);
                    }

                  int istart = (l==0||l==1)?2:((l==2||l==3)?4:0);
                  int ii=i-istart;
                  if(i>=istart)
                    {
                      c15->cd(ii+1);
                      hemptyX->Draw();
                      hfit->Draw("same pe");
                      afX1->at(i)->Draw("same");
                      afX->at(i)->Draw("same");
                      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), (l<7?texjtpt:texjtdr));
                      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                      if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                      xjjroot::drawCMS(collisionsyst);
                      texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
                      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fX->GetParameter(2), fX->GetParError(2)));
                    }
                  // if(i>3)
                  // {
                  cpull15->cd(i+1);
                  pFit[i]->cd();
                  hemptyX->Draw();
                  hfit->Draw("same pe");
                  afX1->at(i)->Draw("same");
                  afX->at(i)->Draw("same");
                  texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), (l<7?texjtpt:texjtdr));
                  // if(!i)
                  // {
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                  if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                  xjjroot::drawCMS(collisionsyst);
                  // }
                  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fX->GetParameter(2), fX->GetParError(2)));
                  cpull15->cd(i+1);
                  pPull[i]->cd();
                  hpull->Draw("p");
                  xjjroot::drawline(xmin.at(l), 0, xmax.at(l), 0, kBlue, 7, 2);
                  hpull->Draw("p same");
                  // }

                  delete fX1;
                  delete fX;
                  delete cX;
                }
              if(isincl) c15->SaveAs(Form("plotfitsall/cfitall%s_%s_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,j));
              if(isincl) cpull15->SaveAs(Form("plotfitspull/cfitall%s_%s_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,j));

              delete afX1;
              delete afX;
              delete hemptyX;
              delete cpull15;
              delete c15;
            }
        }
    }

  //-------------------------------------------------------------------------//

  gStyle->SetPalette(56);
  // TColor::InvertPalette();
  gStyle->SetPaintTextFormat("1.2f");
  gStyle->SetPadRightMargin(xjjroot::margin_pad_right+0.08);
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_left-0.03);
  std::vector<TString> step = {"hRecoVsGenPt", "hRecoVsGenPtCorr", "hRecoVsGenPtRMatGCorr", "hRecoVsGenPtFfCorr", "hRecoVsGenPtFfJecCorr", "hGenSmearVsGenPt"};
  std::vector<TH2F*> hist = {hRecoVsGenPt, hRecoVsGenPtCorr, hRecoVsGenPtRMatGCorr, hRecoVsGenPtFfCorr, hRecoVsGenPtFfJecCorr, hGenSmearVsGenPt};
  std::vector<TH2F*> hRecoNorm(step.size());
  for(int i=0;i<step.size();i++)
    {
      hRecoNorm[i] = (TH2F*)hist[i]->Clone(Form("hRecoNorm_%s",step[i].Data()));
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
            }
        }
    }

  for(int i=0;i<step.size();i++)
    {
      // gStyle->SetPalette(56);
      TCanvas* cmap = new TCanvas("cmap", "", 600, 600);
      xjjroot::sethempty(hist[i]);
      hist[i]->Draw("colz text");
      xjjroot::drawCMS(collisionsyst, -0.03);
      cmap->SaveAs(Form("plotmatrix/cmap_%s_%s.pdf",collisionsyst.Data(),step[i].Data()));
      delete cmap;

      TCanvas* cmapreconorm = new TCanvas("cmapreconorm", "", 600, 600);
      xjjroot::sethempty(hRecoNorm[i]);
      hRecoNorm[i]->Draw("colz text");
      xjjroot::drawCMS(collisionsyst, "5.02", -0.03);
      cmapreconorm->SaveAs(Form("plotmatrix/cmapreconorm_%s_%s.pdf",collisionsyst.Data(),step[i].Data()));
      delete cmapreconorm;
    }

  TFile* outf = new TFile(Form("rootfiles/reso_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("usehist")) return;
  outf->Write();
  outf->Close();
}

void sethpull(TH1* hist_hpull)
{
  hist_hpull->SetMinimum(-4.);
  hist_hpull->SetMaximum(4.);
  hist_hpull->SetYTitle("Pull");
  hist_hpull->GetXaxis()->SetTitleOffset(1.);
  hist_hpull->GetYaxis()->SetTitleOffset(0.65);
  hist_hpull->GetXaxis()->SetLabelOffset(0.007);
  hist_hpull->GetYaxis()->SetLabelOffset(0.007);
  hist_hpull->GetXaxis()->SetTitleSize(0.12);
  hist_hpull->GetYaxis()->SetTitleSize(0.12);
  hist_hpull->GetXaxis()->SetLabelSize(0.1);
  hist_hpull->GetYaxis()->SetLabelSize(0.1);
  hist_hpull->GetYaxis()->SetNdivisions(504);
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
