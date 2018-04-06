#include "djtana.h"

void djtana_plothist(TString inputhistname, TString outputname,
                     TString collisionsyst, Int_t isMC,
                     Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                     Int_t signalMC=1)
{
  int arguerr(TString collisionsyst, Int_t isMC);
  if(arguerr(collisionsyst, isMC)) return;

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;

  // preparation
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      // Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999?Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);
  std::vector<float> vdrBins, vzBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  std::vector<TH1F**>              hSignalXnorm  =  {(TH1F**)ahSignalRnorm};
  std::vector<TH1F**>              hSignalXsub   =  {(TH1F**)ahSignalRsub};
  std::vector<TString>             xtitle        =  {"r"};
  std::vector<TString>             ytitle        =  {"#frac{dN_{jD}}{dr}"};
  std::vector<TString>             ytitlesub     =  {"#frac{1}{N_{jD}} #frac{dN_{jD}}{dr}"};
  std::vector<TString>             tname         =  {"dr"};
  std::vector<std::vector<float>>  vxBins        =  {vdrBins};

  // plot
  int k = 0;
  //
  for(int i=0;i<nPtBins;i++)
    {
      Float_t yaxismax = ahSignalRnorm[0][i]->GetBinContent(1) * 1.e+3;
      Float_t yaxismin = ahSignalRnorm[1][i]->GetBinContent(1) * 1.e-2;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      Int_t nline = (isMC && signalMC)?1:2;
      TLegend* leg = new TLegend(0.53, 0.88-nline*0.06, 0.85, 0.88);
      xjjroot::setleg(leg);
      for(int l=0;l<nRefBins;l++)
        {
          if(l && (isMC && signalMC)) continue;
          xjjroot::setthgrstyle((hSignalXnorm.at(k))[l*nPtBins+i], amcolor[i], amstyle[l][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
          (hSignalXnorm.at(k))[l*nPtBins+i]->Draw("pe same");
          TString tleg = l==1?"#eta reflection":(ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()));
          leg->AddEntry((hSignalXnorm.at(k))[l*nPtBins+i], tleg.Data(), "p");
        }
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c->SaveAs(Form("plotxsecs/cxsec_%s_%s_pt_%d.pdf",tname[k].Data(),outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

  //
  for(int i=0;i<nPtBins;i++)
    {
      Float_t yaxismin = ahSignalRsub[i]->GetBinContent(nDrBins-1) * 1.e-2;
      Float_t yaxismax = ahSignalRsub[i]->GetBinContent(1) * 1.e+3;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      TLegend* leg = new TLegend(0.53, 0.88-0.06, 0.85, 0.88);
      xjjroot::setleg(leg);
      xjjroot::setthgrstyle((hSignalXsub.at(k))[i], amcolor[i], amstyle[0][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
      if(hSignalXsub.at(k)[i]->GetBinContent(nDrBins) < 0) hSignalXsub.at(k)[i]->SetBinContent(nDrBins, yaxismin * 1.e-3);
      (hSignalXsub.at(k))[i]->Draw("pe same");
      TString tleg = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      leg->AddEntry((hSignalXsub.at(k))[i], tleg.Data(), "p");
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c->SaveAs(Form("plotxsecs/cxsecsub_%s_%s_pt_%d.pdf",tname[k].Data(),outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

}

int main(int argc, char* argv[])
{
  if(argc==10)
    {
      djtana_plothist(argv[1], argv[2], argv[3], atoi(argv[4]), 
                      atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]),
                      atoi(argv[9]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_plothist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t isMC)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    } 
  if(isMC!=0 && isMC!=1)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"isMC\""<<std::endl;
      return 1;
    }
  return 0;
}

