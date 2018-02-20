#include "jetffscale.h"

void jetffscale_usehist(TString inputhistname, TString outputname,
                        TString collisionsyst)
{
  int fitscale(TH1F* hHistoReso, TF1* fX, TF1* fX1, std::vector<Float_t> vparam, Float_t fitmin, Float_t fitmax, Float_t &par1, Float_t &par1err, std::vector<TString> vtex);

  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);
  
  xjjroot::setgstyle();

  if(createhists("usehist")) return;
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "usehist")) return;

  std::vector<TString>  name             =  {"Pt",                        "PtCorr"};
  std::vector<TH1F**>   ahHistoResoNpfX  =  {(TH1F**)ahHistoResoNpfPt,    (TH1F**)ahHistoResoNpfPtCorr};
  std::vector<TH1F**>   hScaleNpfX       =  {(TH1F**)hScaleNpfPt,         (TH1F**)hScaleNpfPtCorr};
  std::vector<TString>  xtitle           =  {"p_{T}^{reco}/p_{T}^{gen}",  "p_{T}^{reco}/p_{T}^{gen},Corr"};
  std::vector<Float_t>  xmin             =  {0,                           0};
  std::vector<Float_t>  xmax             =  {2,                           2};
  std::vector<Float_t>  ymin             =  {0,                           0};
  std::vector<Float_t>  ymax             =  {0.2,                         0.2};
  std::vector<Float_t>  param0           =  {1,                           1};
  std::vector<Float_t>  param1           =  {1,                           1};
  std::vector<Float_t>  param2           =  {0.2,                         0.2};
  std::vector<TH1F**>   ahHistoResoX     =  {(TH1F**)ahHistoResoPt,       (TH1F**)ahHistoResoPtCorr};
  std::vector<TH1F**>   hScaleX          =  {(TH1F**)hScalePt,            (TH1F**)hScalePtCorr};

  TString texjteta = "|#eta^{reco jet}| < 1.6";
  for(int l=0;l<2;l++)
    {
      TH2F* hemptyX = new TH2F("hemptyX", Form(";%s;Probability", xtitle.at(l).Data()), 10, xmin.at(l), xmax.at(l), 10, ymin.at(l), ymax.at(l));
      xjjroot::sethempty(hemptyX, 0, 0.4);
      std::vector<Float_t> vparam = {param0.at(l), param1.at(l), param2.at(l)};
      for(int k=0;k<nCentBins;k++)
        {
          TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
          for(int i=0;i<nJtptBins;i++)
            {
              TString texjtpt = Form("%.0f < p_{T}^{reco jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]);

              TCanvas* c40 = new TCanvas("c40", "", 1600, 1000);
              c40->Divide(8, 5);
              //
              c40->cd(1);
              hemptyX->Draw();
              TF1* fInc = new TF1("fInc", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
              TF1* fInc1 = new TF1("fInc1", "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
              std::vector<TString> vtexInc = {texjtpt, texjteta};
              if(!ispp) vtexInc.push_back(texcent);
              Float_t meanInc=0, meanIncerr=0;
              fitscale((ahHistoResoX.at(l))[k*nJtptBins+i], fInc, fInc1, vparam, xmin.at(l), xmax.at(l), meanInc, meanIncerr, vtexInc);
              xjjroot::drawCMS(collisionsyst);
              if(meanInc > 0)
                {
                  (hScaleX.at(l))[k]->SetBinContent(i+1, meanInc);
                  (hScaleX.at(l))[k]->SetBinError(i+1, meanIncerr);
                }
              //
              std::vector<TF1*>* afX = new std::vector<TF1*>(nJtnpfBins);
              std::vector<TF1*>* afX1 = new std::vector<TF1*>(nJtnpfBins);
              for(int j=0;j<nJtnpfBins;j++)
                {
                  TString texjtnpf = Form("nPFcand = %.0f", jtnpfBins[j]);
                  c40->cd(j+2);
                  hemptyX->Draw();
                  afX->at(j) = new TF1(Form("fX%d",j), "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  afX1->at(j) = new TF1(Form("fX1%d",j), "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  std::vector<TString> vtex = {texjtpt, texjteta, texjtnpf};
                  if(!ispp) vtex.push_back(texcent);
                  Float_t mean=0, meanerr=0;
                  fitscale((ahHistoResoNpfX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j], afX->at(j), afX1->at(j), vparam, xmin.at(l), xmax.at(l), mean, meanerr, vtex);
                  xjjroot::drawCMS(collisionsyst);
                  if(mean > 0)
                    {
                      (hScaleNpfX.at(l))[k*nJtptBins+i]->SetBinContent(j+1, mean);
                      (hScaleNpfX.at(l))[k*nJtptBins+i]->SetBinError(j+1, meanerr);
                    }
                }
              c40->SaveAs(Form("plotfits/cfit%s_%s_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,i));

              delete afX1;
              delete afX;
              delete fInc1;
              delete fInc;
              delete c40;
            }
        }
      delete hemptyX;
    }

  TFile* outf = new TFile(Form("rootfiles/reso_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("usehist")) return;
  outf->Write();
  outf->Close();
}

int fitscale(TH1F* hHistoReso, TF1* fX, TF1* fX1, std::vector<Float_t> vparam, Float_t fitmin, Float_t fitmax, Float_t &par1, Float_t &par1err, std::vector<TString> vtex)
{
  fX->SetLineWidth(2);
  fX->SetLineColor(kBlue);
  fX->SetParLimits(1, 0.7, 1.3);
  fX->SetParLimits(2, 0, 1);
  fX->SetParameter(0, vparam[0]);
  fX->SetParameter(1, vparam[1]);
  fX->SetParameter(2, vparam[2]);
  hHistoReso->Scale(1./hHistoReso->Integral());
  xjjroot::setthgrstyle(hHistoReso, kBlack, 24, 1., kBlack, 1, 1, -1, -1, -1);
  hHistoReso->Draw("same pe");
  hHistoReso->Fit(fX->GetName(), "L q", "", fitmin, fitmax);
  hHistoReso->Fit(fX->GetName(), "m q", "", fitmin, fitmax);
  Float_t sigmaX = fX->GetParameter(2);
  fX1->SetParameter(0, fX->GetParameter(0));
  fX1->SetParameter(1, fX->GetParameter(1));
  fX1->SetParameter(2, fX->GetParameter(2));
  fX1->SetLineWidth(2);
  fX1->SetLineColor(kRed);
  fX1->Draw("same");
  if(sigmaX < 0.01) sigmaX = 0.2;
  hHistoReso->Fit(fX->GetName(), "L q", "", fX1->GetParameter(1)-2*sigmaX, fX1->GetParameter(1)+2*sigmaX);
  hHistoReso->Fit(fX->GetName(), "m q", "", fX1->GetParameter(1)-2*sigmaX, fX1->GetParameter(1)+2*sigmaX);
  fX->Draw("same");
  par1 = fX->GetParameter(1);
  par1err = fX->GetParError(1);
  if(fX->GetParameter(2) < 0.005) par1err = 0.5;
  Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
  for(std::vector<TString>::const_iterator it=vtex.begin(); it!=vtex.end(); it++)
    xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", fX->GetParameter(1), fX->GetParError(1)));
  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", fX->GetParameter(2), fX->GetParError(2)));

  return 0;
}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      jetffscale_usehist(argv[1], argv[2], argv[3]);
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
