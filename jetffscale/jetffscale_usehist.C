#include "jetffscale.h"

void jetffscale_usehist(TString inputhistname, TString outputname,
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

  std::vector<TString>  name          =  {"Pt",                        "PtCorr"};
  std::vector<TH1F**>   ahHistoResoX  =  {(TH1F**)ahHistoResoNpfPt,    (TH1F**)ahHistoResoNpfPtCorr};
  std::vector<TH1F**>   hScaleX       =  {(TH1F**)hScaleNpfPt,         (TH1F**)hScaleNpfPtCorr};
  std::vector<TString>  xtitle        =  {"p_{T}^{reco}/p_{T}^{gen}",  "p_{T}^{reco}/p_{T}^{gen},Corr"};
  std::vector<Float_t>  xmin          =  {0,                           0};
  std::vector<Float_t>  xmax          =  {2,                           2};
  std::vector<Float_t>  ymin          =  {0,                           0};
  std::vector<Float_t>  ymax          =  {0.2,                         0.2};
  std::vector<Float_t>  param0        =  {1,                           1};
  std::vector<Float_t>  param1        =  {1,                           1};
  std::vector<Float_t>  param2        =  {0.2,                         0.2};

  TString texjteta = "|#eta^{reco jet}| < 1.6";
  for(int l=0;l<2;l++)
    {
      TH2F* hemptyX = new TH2F("hemptyX", Form(";%s;Probability", xtitle.at(l).Data()), 10, xmin.at(l), xmax.at(l), 10, ymin.at(l), ymax.at(l));
      xjjroot::sethempty(hemptyX, 0, 0.4);
      for(int k=0;k<nCentBins;k++)
        {
          TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
          for(int i=0;i<nJtptBins;i++)
            {
              TString texjtpt = Form("%.0f < p_{T}^{gen jet} < %.0f GeV", jtptBins[i], jtptBins[i+1]);
              TCanvas* c40 = new TCanvas("c40", "", 1600, 1000);
              c40->Divide(8, 5);
              std::vector<TF1*>* afX = new std::vector<TF1*>(nJtnpfBins);
              std::vector<TF1*>* afX1 = new std::vector<TF1*>(nJtnpfBins);
              for(int j=0;j<nJtnpfBins;j++)
                {
                  c40->cd(j+1);
                  hemptyX->Draw();
                  afX->at(j) = new TF1(Form("fX%d",j), "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  afX->at(j)->SetLineWidth(3);
                  afX->at(j)->SetLineColor(kBlue);
                  afX->at(j)->SetParLimits(1, 0.7, 1.3);
                  afX->at(j)->SetParLimits(2, 0, 1);
                  afX->at(j)->SetParameter(0, param0.at(l));
                  afX->at(j)->SetParameter(1, param1.at(l));
                  afX->at(j)->SetParameter(2, param2.at(l));
                  (ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j]->Scale(1./(ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j]->Integral());
                  xjjroot::setthgrstyle((ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
                  (ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j]->Draw("same pe");
                  (ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j]->Fit(Form("fX%d",j), "L q", "", xmin.at(l), xmax.at(l));
                  (ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j]->Fit(Form("fX%d",j), "m q", "", xmin.at(l), xmax.at(l));
                  Float_t sigmaX = afX->at(j)->GetParameter(2);
                  afX1->at(j) = new TF1(Form("fX1%d",j), "[0]*Gaus(x,[1],[2])/(TMath::Sqrt(2*3.14159265)*[2])", xmin.at(l), xmax.at(l));
                  afX1->at(j)->SetParameter(0, afX->at(j)->GetParameter(0));
                  afX1->at(j)->SetParameter(1, afX->at(j)->GetParameter(1));
                  afX1->at(j)->SetParameter(2, afX->at(j)->GetParameter(2));
                  afX1->at(j)->SetLineWidth(3);
                  afX1->at(j)->SetLineColor(kRed);
                  afX1->at(j)->Draw("same");
                  (ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j]->Fit(Form("fX%d",j), "L q", "", afX1->at(j)->GetParameter(1)-2*sigmaX, afX1->at(j)->GetParameter(1)+2*sigmaX);
                  (ahHistoResoX.at(l))[k*nJtnpfBins*nJtptBins+i*nJtnpfBins+j]->Fit(Form("fX%d",j), "m q", "", afX1->at(j)->GetParameter(1)-2*sigmaX, afX1->at(j)->GetParameter(1)+2*sigmaX);
                  afX->at(j)->Draw("same");
                  if(afX->at(j)->GetParameter(1)>0)
                    {
                      (hScaleX.at(l))[k*nJtptBins+i]->SetBinContent(j+1, afX->at(j)->GetParameter(1));
                      (hScaleX.at(l))[k*nJtptBins+i]->SetBinError(j+1, afX->at(j)->GetParError(1));
                    }
                  Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjtpt);
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texjteta);
                  if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
                  texxpos = 0.65; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#mu = %.3f #pm %.3f", afX->at(j)->GetParameter(1), afX->at(j)->GetParError(1)));
                  xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), Form("#sigma = %.3f #pm %.3f", afX->at(j)->GetParameter(2), afX->at(j)->GetParError(2)));
                  xjjroot::drawCMS(collisionsyst);
                }
              c40->SaveAs(Form("plotfits/cfit%s_%s_%d_%d.pdf",name.at(l).Data(),outputname.Data(),k,i));
              delete afX1;
              delete afX;
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
