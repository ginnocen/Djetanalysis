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

  std::vector<TString>  name          =  {"Pt",                        "PtCorr",                         "Phi",                     "Eta",                     "PtFfCorr"};
  std::vector<TH1F**>   ahHistoResoX  =  {(TH1F**)ahHistoResoPt,       (TH1F**)ahHistoResoPtCorr,        (TH1F**)ahHistoResoPhi,    (TH1F**)ahHistoResoEta,    (TH1F**)ahHistoResoPtFfCorr};
  std::vector<TH1F**>   hScaleX       =  {(TH1F**)hScalePt,            (TH1F**)hScalePtCorr,             (TH1F**)hScalePhi,         (TH1F**)hScaleEta,         (TH1F**)hScalePtFfCorr};
  std::vector<TH1F**>   hResoX        =  {(TH1F**)hResoPt,             (TH1F**)hResoPtCorr,              (TH1F**)hResoPhi,          (TH1F**)hResoEta,          (TH1F**)hResoPtFfCorr};
  std::vector<TString>  xtitle        =  {"p_{T}^{reco}/p_{T}^{gen}",  "p_{T}^{reco}/p_{T}^{gen},Corr",  "#phi^{reco}-#phi^{gen}",  "#eta^{reco}-#eta^{gen}",  "p_{T}^{reco}/p_{T}^{gen},frag-depCorr"};
  std::vector<Float_t>  xmin          =  {0,                           0,                                0-xrangeAng,               0-xrangeAng,               0};
  std::vector<Float_t>  xmax          =  {2,                           2,                                xrangeAng,                 xrangeAng,                 2};
  std::vector<Float_t>  ymin          =  {0,                           0,                                0,                         0,                         0};
  std::vector<Float_t>  ymax          =  {0.2,                         0.2,                              (float)(ispp?0.2:0.1),    (float)(ispp?0.2:0.1),    0.2};
  std::vector<Float_t>  param0        =  {1,                           1,                                0.01,                      0.01,                      1};
  std::vector<Float_t>  param1        =  {1,                           1,                                0,                         0,                         1};
  std::vector<Float_t>  param2        =  {0.2,                         0.2,                              0.01,                      0.01,                      0.2};

  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      for(int j=0;j<nJtetaBins+1;j++)
        {
          TString texjteta = j==0?"Incl. #eta":Form("%.1f < |#eta^{reco jet}| < %.1f", jtetaBins[j-1], jtetaBins[j]);
          for(int l=0;l<5;l++)
            {
              TCanvas* c15 = new TCanvas("c15", "", 1000, 600);
              c15->Divide(5, 3);
              TH2F* hemptyX = new TH2F("hemptyX", Form(";%s;Probability", xtitle.at(l).Data()), 10, xmin.at(l), xmax.at(l), 10, ymin.at(l), ymax.at(l));
              xjjroot::sethempty(hemptyX, 0, 0.4);
              std::vector<TF1*>* afX = new std::vector<TF1*>(nResoJtptBins);
              std::vector<TF1*>* afX1 = new std::vector<TF1*>(nResoJtptBins);
              for(int i=0;i<nResoJtptBins;i++)
                {
                  TString texjtpt = Form("%.0f < p_{T}^{reco jet} < %.0f GeV", resojtptBins[i], resojtptBins[i+1]);
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
                  (ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Scale(1./(ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Integral());
                  xjjroot::setthgrstyle((ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i], kBlack, 24, 1., kBlack, 1, 1, -1, -1, -1);
                  (ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Draw("same pe");
                  (ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Fit("fX", "L q", "", xmin.at(l), xmax.at(l));
                  (ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Fit("fX", "m q", "", xmin.at(l), xmax.at(l));
                  Float_t meanX = fX->GetParameter(1); 
                  if(!(l==2||l==3) && (meanX < 0.5 || meanX > 1.7)) meanX = 1;
                  Float_t sigmaX = fX->GetParameter(2);
                  if(sigmaX < 0.01) sigmaX = 0.2;
                  TF1* fX1 = new TF1("fX1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  fX1->SetParameter(0, fX->GetParameter(0));
                  fX1->SetParameter(1, fX->GetParameter(1));
                  fX1->SetParameter(2, fX->GetParameter(2));
                  fX1->SetLineWidth(2);
                  fX1->SetLineColor(kRed);
                  fX1->Draw("same");
                  (ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Fit("fX", "L q", "", meanX-((ispp&&(l==2||l==3))?0.5:2)*sigmaX, meanX+((ispp&&(l==2||l==3))?0.5:2)*sigmaX);
                  (ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Fit("fX", "m q", "", meanX-((ispp&&(l==2||l==3))?0.5:2)*sigmaX, meanX+((ispp&&(l==2||l==3))?0.5:2)*sigmaX);
                  fX->Draw("same");
                  (hScaleX.at(l))[k*(nJtetaBins+1)+j]->SetBinContent(i+1, fX->GetParameter(1));
                  (hScaleX.at(l))[k*(nJtetaBins+1)+j]->SetBinError(i+1, fX->GetParError(1));
                  (hResoX.at(l))[k*(nJtetaBins+1)+j]->SetBinContent(i+1, fX->GetParameter(2));
                  (hResoX.at(l))[k*(nJtetaBins+1)+j]->SetBinError(i+1, fX->GetParError(2));
                  afX->at(i) = xjjroot::copyobject(fX, Form("fX%d",i));
                  afX1->at(i) = xjjroot::copyobject(fX1, Form("fX%d",i));
                  Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                  if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fX->GetParameter(2), fX->GetParError(2)));
                  xjjroot::drawCMS(collisionsyst);
                  // cX->SaveAs(Form("plotfits/cfit%s_%s_%d_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,j,i));

                  c15->cd(i+1);
                  hemptyX->Draw();
                  (ahHistoResoX.at(l))[k*nResoJtptBins*(nJtetaBins+1)+j*nResoJtptBins+i]->Draw("same pe");
                  afX1->at(i)->Draw("same");
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
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fX->GetParameter(2), fX->GetParError(2)));

                  delete fX1;
                  delete cX;
                  delete fX;
                }
              c15->SaveAs(Form("plotfitsall/cfitall%s_%s_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,j));

              delete afX1;
              delete afX;
              delete hemptyX;
              delete c15;
            }
        }
    }

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
