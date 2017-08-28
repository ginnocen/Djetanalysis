#include "djtclosure.h"

void djtclosure_plothist(std::vector<TString> inputhistname, TString outputname,
                         TString collisionsyst,
                         Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
                         Int_t plotref = 1)
{
  int arguerr(std::vector<TString>inputhistname, TString collisionsyst, Int_t plotref);
  if(arguerr(inputhistname, collisionsyst, plotref)) return;

  xjjroot::setgstyle();

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
  TString             xtitle[2]        =  {"#DeltaR",            "z = p_{T}^{D} / p_{T}^{jet}"};
  TString             ytitle[2]        =  {"#rho(#DeltaR)",      "#rho(z)"};
  TString             tname[2]         =  {"dr",                 "z"};
  std::vector<float>  vxBins[2]        =  {vdrBins,              vzBins};
  Float_t yaxismin = 1.e-5, yaxismax = 1.e+3;

  // plot
  for(int k=0;k<2;k++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          TCanvas* c = new TCanvas("c", "", 600, 600);
          c->SetLogy();
          TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yaxismin, yaxismax);
          hempty->GetXaxis()->SetNdivisions(505);
          xjjroot::sethempty(hempty, 0, 0.5);
          hempty->Draw();
          TLegend* leg = new TLegend(0.53, 0.88-nCases*0.06, 0.85, 0.88);
          xjjroot::setleg(leg);
          TLegend* legref = new TLegend(0.55, 0.17, 1.27, 0.23);
          xjjroot::setleg(legref);
          legref->SetNColumns(nCases);
          for(int l=0;l<nRefBins;l++)
            {
              if(l && !plotref) continue;
              for(int m=0;m<nCases;m++)
                {                  
                  TH1F* hSignalXnorm = k==0?ahSignalRnorm[m][l][i]:ahSignalZnorm[m][l][i];
                  xjjroot::setthgrstyle(hSignalXnorm, amcolor[m], amstyle[l], 1.2, amcolor[m], 1, 1, -1, -1, -1);
                  hSignalXnorm->Draw("pe same");
                  if(!l) leg->AddEntry(hSignalXnorm, legCases[m].Data(), "p");
                  else legref->AddEntry(hSignalXnorm, m==(nCases-1)?"#eta reflection":"", "p");
                }
            }
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.90, texdypos = 0.053;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          TString tpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), tpt.Data());
          leg->Draw();
          legref->Draw();
          c->SaveAs(Form("plotxsecs/cclosure_xsec_%s_%s_pt_%s_%s.pdf",outputname.Data(),tname[k].Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));
          delete leg;
          delete hempty;
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

