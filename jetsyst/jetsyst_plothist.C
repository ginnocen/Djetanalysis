#include "jetsyst.h"

void jetsyst_plothist(TString inputname, std::vector<TString> inputnameScale, std::vector<TString> inputnameReso, 
                      TString outputname, TString collisionsyst,
                      Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  xjjroot::setgstyle();
  std::vector<TFile*> inf(1, 0);
  inf[0] = new TFile(Form("%s.root", inputname.Data()));
  std::vector<TFile*> infScale(nScale, 0);
  for(int v=0;v<nScale;v++)
    {
      infScale[v] = new TFile(Form("%s.root",inputnameScale[v].Data()));
      if(!infScale[v]->IsOpen()) return;
    }
  std::vector<TFile*> infReso(nReso, 0);
  for(int v=0;v<nReso;v++)
    {
      infReso[v] = new TFile(Form("%s.root",inputnameReso[v].Data()));
      if(!infReso[v]->IsOpen()) return;
    }

  if(gethists(inf, "plothist_default")) return;
  if(gethists(infScale, "plothist_scale")) return;
  if(gethists(infReso, "plothist_reso")) return;

  if(createhists("plothist")) return;

  //
  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++)
        {
          for(int v=0;v<nScale;v++)
            {
              ahDevRnormScale[0][i][v]->SetBinContent(j+1, (ahSignalRnormScale[0][i][v]->GetBinContent(j+1) - ahSignalRnorm[0][i]->GetBinContent(j+1)) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              ahDevRsubScale[i][v]->SetBinContent(j+1, (ahSignalRsubScale[i][v]->GetBinContent(j+1) - ahSignalRsub[i]->GetBinContent(j+1)) / ahSignalRsub[i]->GetBinContent(j+1));
            }
          for(int v=0;v<nReso;v++)
            {
              ahDevRnormReso[0][i][v]->SetBinContent(j+1, (ahSignalRnormReso[0][i][v]->GetBinContent(j+1) - ahSignalRnorm[0][i]->GetBinContent(j+1)) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              ahDevRsubReso[i][v]->SetBinContent(j+1, (ahSignalRsubReso[i][v]->GetBinContent(j+1) - ahSignalRsub[i]->GetBinContent(j+1)) / ahSignalRsub[i]->GetBinContent(j+1));
            }
        }
    }
  //
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

          TH2F* hempty = new TH2F("hempty", ";#DeltaR;Deviation / Default", 10, drBins[0], drBins[nDrBins], 10, -0.3, 0.5);
          xjjroot::sethempty(hempty, 0, 0.3);
          hempty->GetXaxis()->SetNdivisions(505);

          TCanvas* cscale = new TCanvas("cscale", "", 600, 600);
          hempty->Draw();
          xjjroot::drawline(drBins[0], 0, drBins[nDrBins], 0, kGray+3, 2, 3);
          TLegend* legscale = new TLegend(0.60, 0.88-(nScale)*0.055, 0.90, 0.88);
          xjjroot::setleg(legscale);
          for(int v=0;v<nScale;v++)
            {
              xjjroot::setthgrstyle(ahDevRnormScale[l][i][v], colorlist[v], -1, -1, colorlist[v], 2, 3);
              ahDevRnormScale[l][i][v]->Draw("same");
              legscale->AddEntry(ahDevRnormScale[l][i][v], legScale[v].Data(), "l");
            }
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          legscale->Draw();
          cscale->SaveAs(Form("plotjetsyst/cscaledev_%s_%s_pt_%d.pdf", outputname.Data(),tRef[l].Data(),i));

          delete legscale;
          delete cscale;

          TCanvas* creso = new TCanvas("creso", "", 600, 600);
          hempty->Draw();
          xjjroot::drawline(drBins[0], 0, drBins[nDrBins], 0, kGray+3, 2, 3);
          TLegend* legreso = new TLegend(0.60, 0.88-(nReso)*0.055, 0.90, 0.88);
          xjjroot::setleg(legreso);
          for(int v=0;v<nReso;v++)
            {
              xjjroot::setthgrstyle(ahDevRnormReso[l][i][v], colorlist[v], -1, -1, colorlist[v], 2, 3);
              ahDevRnormReso[l][i][v]->Draw("same");
              legreso->AddEntry(ahDevRnormReso[l][i][v], legReso[v].Data(), "l");
            }
          xjjroot::drawCMS(collisionsyst);
          texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          legreso->Draw();
          creso->SaveAs(Form("plotjetsyst/cresodev_%s_%s_pt_%d.pdf", outputname.Data(),tRef[l].Data(),i));

          delete legreso;
          delete creso;

          delete hempty;

        }
      vectex.pop_back();
    }
}

int main(int argc, char* argv[])
{
  if(argc==(1+nScale+nReso+6))
    {
      std::vector<TString> inputnameScale;
      for(int m=0;m<nScale;m++) inputnameScale.push_back(argv[m+2]);
      std::vector<TString> inputnameReso;
      for(int m=0;m<nReso;m++) inputnameReso.push_back(argv[m+2+nReso]);
      jetsyst_plothist(argv[1], inputnameScale, inputnameReso, argv[1+nScale+nReso+1], argv[1+nScale+nReso+2], atof(argv[1+nScale+nReso+3]), atof(argv[1+nScale+nReso+4]), atof(argv[1+nScale+nReso+5]));
      return 0;
    }
  else
    {
      std::cout<<"error: invalid parameter number - jetsyst_plothist"<<std::endl;
      return 1;
    }
}
