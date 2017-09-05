#include "djtclosure.h"

void djtclosure_plothist(std::vector<TString> inputhistname, TString outputname,
                         TString collisionsyst,
                         Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
                         Int_t plotref = 1)
{
  int arguerr(std::vector<TString>inputhistname, TString collisionsyst, Int_t plotref);
  if(arguerr(inputhistname, collisionsyst, plotref)) return;

  if(createhists("plothist")) return;

  std::vector<TFile*> infhist(nCases, 0);
  for(int m=0;m<nCases;m++)
    {
      infhist[m] = new TFile(Form("%s.root",inputhistname[m].Data()));
      if(!infhist[m]->IsOpen()) return;
    }
  if(gethists(infhist, "plothist")) return;

  // preparation
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  std::vector<float> vdrBins, vzBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  for(int j=0;j<sizeof(zBins)/sizeof(zBins[0]);j++) vzBins.push_back(zBins[j]);
  std::vector<TString>            xtitle           = {"#DeltaR",                 "z = p^{D}_{T} / p^{jet}_{T}"};
  std::vector<TString>            ytitle           = {"#rho(#DeltaR)",           "#rho(z)"};
  std::vector<TString>            tname            = {"dr",                      "z"};
  std::vector<std::vector<float>> vxBins           = {vdrBins,                   vzBins};
  std::vector<TH1F**>             hSignalXnorm     = {(TH1F**)ahSignalRnorm,     (TH1F**)ahSignalZnorm};
  std::vector<TH1F**>             hSignalXnormPull = {(TH1F**)ahSignalRnormPull, (TH1F**)ahSignalZnormPull};

  Float_t yaxismin = 1.1e-5, yaxismax = 1.e+3;
  Float_t yPullaxismin = 1-1, yPullaxismax = 1+1;
  Float_t ypaddiv = 3./4, yPullpaddiv = 1-ypaddiv;

  // calculate pull
  for(int k=0;k<2;k++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int m=0;m<nCases;m++)
            {
              for(int l=0;l<nRefBins;l++)
                {
                  if(l && !plotref) continue;
                  (hSignalXnormPull.at(k))[(m*nRefBins+l)*nPtBins+i]->Divide((hSignalXnorm.at(k))[(m*nRefBins+l)*nPtBins+i], 
                                                                             (hSignalXnorm.at(k))[((nCases-1)*nRefBins+l)*nPtBins+i]); // hSignalXnorm[nCases-1][l][i] is truth
                }
            }
        }
    }

  // plot
  for(int k=0;k<2;k++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          TCanvas* c = new TCanvas("c", "", 600, 600 / ypaddiv);
          TPad* pXsec = new TPad("pXsec", "", 0, 1-ypaddiv, 1, 1);
          pXsec->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
          pXsec->Draw();
          pXsec->cd();
          pXsec->SetLogy();
          TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yaxismin, yaxismax);
          hempty->GetXaxis()->SetNdivisions(505);
          xjjroot::sethempty(hempty, 0, 0.5);
          hempty->Draw();
          TLegend* leg = new TLegend(0.58, 0.88-nCases*0.06, 0.90, 0.88);
          xjjroot::setleg(leg);
          TLegend* legref = new TLegend(0.56, 0.17-xjjroot::margin_pad_bottom, 1.30, 0.23-xjjroot::margin_pad_bottom);
          xjjroot::setleg(legref);
          legref->SetNColumns(nCases);
          for(int l=0;l<nRefBins;l++)
            {
              if(l && !plotref) continue;
              for(int m=0;m<nCases;m++)
                {
                  xjjroot::setthgrstyle((hSignalXnorm.at(k))[(m*nRefBins+l)*nPtBins+i], amcolor[m], amstyle[l], 1.2, amcolor[m], 1, 1, -1, -1, -1);
                  (hSignalXnorm.at(k))[(m*nRefBins+l)*nPtBins+i]->Draw("pe same");
                  if(!l) leg->AddEntry((hSignalXnorm.at(k))[(m*nRefBins+l)*nPtBins+i], legCases[m].Data(), "p");
                  else legref->AddEntry((hSignalXnorm.at(k))[(m*nRefBins+l)*nPtBins+i], m==(nCases-1)?"#eta reflection":"", "p");
                }
            }
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
          texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          TString tpt = ptBins[i+1]>=999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), tpt.Data());
          if(k) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "#DeltaR < 0.3");
          leg->Draw();
          legref->Draw();

          c->cd();
          TPad* pPull = new TPad("pPull", "", 0, 0, 1, yPullpaddiv);
          pPull->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, xjjroot::margin_pad_top*1/yPullpaddiv, 0);
          pPull->Draw();
          pPull->cd();
          TH2F* hemptyPull = new TH2F("hemptyPull", Form(";%s;%s",xtitle[k].Data(),"X / truth"), 5, vxBins[k].front(), vxBins[k].back(), 10, yPullaxismin, yPullaxismax);
          hemptyPull->GetXaxis()->SetNdivisions(505);
          hemptyPull->GetYaxis()->SetNdivisions(504);
          xjjroot::sethempty(hemptyPull, 0, 0.5);
          hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
          hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
          hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
          hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
          hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv));
          hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv) *(1+1.8));
          hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv) *(1+12));
          hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv));
          hemptyPull->Draw();
          for(int l=0;l<nRefBins;l++)
            {
              if(l && !plotref) continue;
              for(int m=0;m<nCases;m++)
                {
                  if(m==nCases-1) continue;
                  xjjroot::setthgrstyle((hSignalXnormPull.at(k))[(m*nRefBins+l)*nPtBins+i], amcolor[m], amstyle[l], 1.2, amcolor[m], 1, 1, -1, -1, -1);
                  (hSignalXnormPull.at(k))[(m*nRefBins+l)*nPtBins+i]->Draw("pe same");
                }
            }
          TBox* box = new TBox(-0.07, 1.8, -0.01, 2.0);
          box->SetFillColor(kWhite);
          box->Draw();

          c->SaveAs(Form("plotxsecs/cclosure_xsec_%s_%s_pt_%s_%s.pdf",outputname.Data(),tname[k].Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));

          delete box;
          delete leg;
          delete hemptyPull;
          delete hempty;
          delete pPull;
          delete pXsec;
          delete c;
        }
    }
}

int main(int argc, char* argv[])
{
  if(argc==(nCases+6))
    {
      std::vector<TString> inputhistname;
      for(int m=0;m<nCases;m++) inputhistname.push_back(argv[m+1]);
      djtclosure_plothist(inputhistname, argv[nCases+1], argv[nCases+2], atof(argv[nCases+3]), atof(argv[nCases+4]), atof(argv[nCases+5]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtclosure_plothist()"<<std::endl;
      return 1;
    }
}

int arguerr(std::vector<TString>inputhistname, TString collisionsyst, Int_t plotref)
{
  if(inputhistname.size()!=nCases)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"inputhistname\""<<std::endl;
      return 1;
    } 
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    } 
  if(plotref!=0 && plotref!=1)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"plotref\""<<std::endl;
      return 1;
    }
  return 0;
}

