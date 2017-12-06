#include "djtclosure.h"

void djtclosure_compjes(std::vector<TString> inputhistwojes, std::vector<TString> inputhistwjes, TString outputname,
                        TString collisionsyst,
                        Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
                        Int_t plotref = 1)
{
  int arguerr(std::vector<TString> inputhistwojes, std::vector<TString> inputhistwjes, TString collisionsyst, Int_t plotref);
  if(arguerr(inputhistwojes, inputhistwjes, collisionsyst, plotref)) return;

  if(createhists("compjes")) return;

  std::vector<TFile*> infhist(nCases*2, 0);
  for(int m=0;m<nCases;m++)
    {
      infhist[m] = new TFile(Form("%s.root",inputhistwojes[m].Data()));
      if(!infhist[m]->IsOpen()) return;
      infhist[nCases+m] = new TFile(Form("%s.root",inputhistwjes[m].Data()));
      if(!infhist[nCases+m]->IsOpen()) return;
    }
  if(gethists(infhist, "compjes")) return;

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
  std::vector<TString>            tname            = {"dr",                      "z"};
  std::vector<std::vector<float>> vxBins           = {vdrBins,                   vzBins};
  std::vector<TH1F**>             hSignalXsubjes      = {(TH1F**)ahSignalRsubjes,      (TH1F**)ahSignalZsubjes};
  std::vector<TH1F**>             hSignalXsubjesPull  = {(TH1F**)ahSignalRsubjesPull,  (TH1F**)ahSignalZsubjesPull};
  std::vector<float>              yPullaxismin     = {0.5,                       0.};
  std::vector<float>              yPullaxismax     = {1.5,                       2.};

  Float_t yaxismin = 1.1e-5, yaxismax = 1.e+3;
  Float_t ypaddiv = 3./4, yPullpaddiv = 1-ypaddiv;

  // calculate pull
  for(int k=0;k<2;k++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int m=0;m<nCases;m++)
            {
              (hSignalXsubjesPull.at(k))[m*nPtBins+i]->Divide((hSignalXsubjes.at(k))[(m+nCases)*nPtBins+i], 
                                                              (hSignalXsubjes.at(k))[m*nPtBins+i]); //
            }
        }
    }

  // plot
  xjjroot::setgstyle();
  std::vector<TString> ytitle = {"with / without analysis level correction", "with / without smearing"};
  for(int k=0;k<2;k++)
    {
      std::vector<TCanvas*> c(2, 0);
      std::vector<TH2F*> hempty(2, 0);
      std::vector<TLegend*> leg(2, 0);
      for(int n=0;n<nScaleorSmear;n++)
        {
          c[n] = new TCanvas(Form("c%d",n), "", 600, 600);
          c[n]->cd();
          hempty[n] = new TH2F(Form("hempty%d",n), Form(";%s;%s",xtitle[k].Data(),ytitle[n].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yPullaxismin[k], yPullaxismax[k]);
          hempty[n]->GetXaxis()->SetNdivisions(505);
          xjjroot::sethempty(hempty[n], 0, 0.5);
          hempty[n]->Draw();
          leg[n] = new TLegend(0.50, 0.88-(nPtBins*2)*0.06, 0.90, 0.88);
          xjjroot::setleg(leg[n]);
        }
      for(int m=0;m<nCases;m++)
        {
          int iCaseJet = tCases[m].Contains("RecoJet")?0:1;
          int iCaseD = tCases[m].Contains("RecoD")?0:1;
          c[iCaseJet]->cd();
          for(int i=0;i<nPtBins;i++)
            {
              TString tpt = ptBins[i+1]>=999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
              xjjroot::setthgrstyle((hSignalXsubjesPull.at(k))[m*nPtBins+i], amcolorJes[i], amstyleJes[iCaseD], 1.2, amcolorJes[i], 1, 1, -1, -1, -1);
              (hSignalXsubjesPull.at(k))[m*nPtBins+i]->Draw("pe same");
              leg[iCaseJet]->AddEntry((hSignalXsubjesPull.at(k))[m*nPtBins+i], Form("%s, %s", tCasesD[iCaseD].Data(), tpt.Data()), "p");
            }
        }
      for(int n=0;n<nScaleorSmear;n++)
        {
          c[n]->cd();
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
          texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), tCasesJet[n].Data());
          if(k) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "#DeltaR < 0.3");
          leg[n]->Draw();
          c[n]->SaveAs(Form("plotjes/ccomjes_subratio_%s_%s_%s.pdf",outputname.Data(),tname[k].Data(),tScaleorSmear[n].Data()));
          delete leg[n];
          delete hempty[n];
          delete c[n];
        }

    }
}

int main(int argc, char* argv[])
{
  if(argc==(nCases*2+6))
    {
      std::vector<TString> inputhistwojes;
      std::vector<TString> inputhistwjes;
      for(int m=0;m<nCases;m++) 
        {
          inputhistwojes.push_back(argv[m+1]);
          inputhistwjes.push_back(argv[nCases+m+1]);
        }
      djtclosure_compjes(inputhistwojes, inputhistwjes, argv[nCases*2+1], argv[nCases*2+2], atof(argv[nCases*2+3]), atof(argv[nCases*2+4]), atof(argv[nCases*2+5]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtclosure_compjes()"<<std::endl;
      return 1;
    }
}

int arguerr(std::vector<TString> inputhistwojes, std::vector<TString> inputhistwjes, TString collisionsyst, Int_t plotref)
{
  if(inputhistwojes.size()!=nCases)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"inputhistwojes\""<<std::endl;
      return 1;
    } 
  if(inputhistwjes.size()!=nCases)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"inputhistwjes\""<<std::endl;
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

