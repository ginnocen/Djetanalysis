#include "djtana.h"

void djtana_plothist(TString inputhistname, TString outputname,
                     TString collisionsyst,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
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
  TString             xtitle[2]        =  {"#DeltaR",            "z = p_{T}^{D} / p_{T}^{jet}"};
  TString             ytitle[2]        =  {"#rho(#DeltaR)",      "#rho(z)"};
  TString             tname[2]         =  {"dr",                 "z"};
  std::vector<float>  vxBins[2]        =  {vdrBins,              vzBins};

  Float_t             yaxismax[2][nRefBins] = {{0, 0}, {0, 0}};
  for(int k=0;k<2;k++)
    {
      for(int l=0;l<nRefBins;l++)
        {
          for(int i=0;i<nPtBins;i++)
            {
              TH1F* hSignalXnorm = k==0?ahSignalRnorm[l][i]:ahSignalZnorm[l][i];
              if(hSignalXnorm->GetMaximum()>yaxismax[k][l]) yaxismax[k][l] = hSignalXnorm->GetMaximum();
            }
        }
    }

  // plot
  for(int k=0;k<2;k++)
    {
      for(int l=0;l<nRefBins;l++)
        {
          TCanvas* c = new TCanvas("c", "", 600, 600);
          TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, 0, yaxismax[k][l]*2.);
          xjjroot::sethempty(hempty, 0, 0.5);
          hempty->Draw();
          TLegend* leg = new TLegend(0.53, 0.88-nPtBins*0.06, 0.85, 0.88);
          xjjroot::setleg(leg);
          for(int i=0;i<nPtBins;i++)
            {
              TH1F* hSignalXnorm = k==0?ahSignalRnorm[l][i]:ahSignalZnorm[l][i];
              xjjroot::setthgrstyle(hSignalXnorm, amcolor[i], amstyle[i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              hSignalXnorm->Draw("pe same");
              leg->AddEntry(hSignalXnorm, Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()), "p");
              xjjroot::drawCMS(collisionsyst);
              Float_t texxpos = 0.22, texypos = 0.90, texdypos = 0.053;
              for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
                xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
            }
          leg->Draw();
          c->SaveAs(Form("plotxsecs/cxsec_%s_%s_%s.pdf",outputname.Data(),tRef[l].Data(),tname[k].Data()));
          delete leg;
          delete hempty;
          delete c;
        }
    }
}

int main(int argc, char* argv[])
{
  if(argc==7)
    {
      djtana_plothist(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_plothist()"<<std::endl;
      return 1;
    }
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

