#include "pdfvariation.h"

void pdfvar_plothist(TString inputname, TString outputname, TString collisionsyst,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  xjjroot::setgstyle();
  TFile* inf = new TFile(Form("%s.root", inputname.Data()));
  if(!inf->IsOpen()) return;
  if(gethists(inf, "plothist")) return;

  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };

  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]>900?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      vectex.push_back(texpt);
      for(int l=0;l<nRefBins;l++)
        {
          if(l) continue;
          TCanvas* c = new TCanvas("c", "", 600, 600);
          TH2F* hempty = new TH2F("hempty", ";#DeltaR;Yield deviation", 10, drBins[0], drBins[nDrBins], 10, -0.3, 0.5);
          xjjroot::sethempty(hempty, 0, 0.3);
          hempty->GetXaxis()->SetNdivisions(505);
          hempty->Draw();
          TLegend* leg = new TLegend(0.60, 0.88-(nVariation-1)*0.055, 0.90, 0.88);
          xjjroot::setleg(leg);
          for(int v=0;v<nVariation;v++)
            {
              if(fitname[v]=="EXP") continue;
              xjjroot::setthgrstyle(ahSignalRdev[l][i][v], fitcolor[v], -1, -1, fitcolor[v], 2, 3);
              ahSignalRdev[l][i][v]->Draw("same");
              leg->AddEntry(ahSignalRdev[l][i][v], fitleg[v].Data(), "l");
            }
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          leg->Draw();
          c->SaveAs(Form("plotpdfvar/cdev_%s_%s_pt_%d.pdf", outputname.Data(),tRef[l].Data(),i));

          delete leg;
          delete hempty;
          delete c;
        }
      vectex.pop_back();
    }
}

int main(int argc, char* argv[])
{
  if(argc == 7)
    {
      pdfvar_plothist(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else
    {
      std::cout<<"error: invalid parameter number - pdfvar_plothist"<<std::endl;
      return 1;
    }
}
