#include "jetsyst.h"

void jetsyst_plothist(TString inputname, std::vector<TString> inputnameReso,
                      TString outputname, TString collisionsyst,
                      Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax)
{
  xjjroot::setgstyle();
  std::vector<TFile*> inf(1, 0);
  inf[0] = new TFile(Form("%s.root", inputname.Data()));
  std::vector<TFile*> infReso(nReso, 0);
  for(int v=0;v<nReso;v++)
    {
      infReso[v] = new TFile(Form("%s.root",inputnameReso[v].Data()));
      if(!infReso[v]->IsOpen()) return;
    }

  if(gethists(inf, "plothist_default")) return;
  if(gethists(infReso, "plothist_reso")) return;

  if(createhists("plothist")) return;

  //
  Float_t maxreso[nPtBins][nDrBins];
  for(int i=0;i<nPtBins;i++)
    {
      for(int v=0;v<nReso;v++)
        {
          ahDevRnormReso[0][i][v]->Add(ahSignalRnormReso[0][i][v], ahSignalRnorm[0][i], 1, -1);
          ahDevRsubReso[i][v]->Add(ahSignalRsubReso[i][v], ahSignalRsub[i], 1, -1);
        }
      for(int j=0;j<nDrBins;j++)
        {
          maxreso[i][j] = 0;
          for(int v=0;v<nReso;v++)
            {
              ahDevRnormReso[0][i][v]->SetBinContent(j+1, ahDevRnormReso[0][i][v]->GetBinContent(j+1) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              ahDevRnormReso[0][i][v]->SetBinError(j+1, ahDevRnormReso[0][i][v]->GetBinError(j+1) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              ahDevRsubReso[i][v]->SetBinContent(j+1, ahDevRsubReso[i][v]->GetBinContent(j+1) / ahSignalRsub[i]->GetBinContent(j+1));
              ahDevRsubReso[i][v]->SetBinError(j+1, ahDevRsubReso[i][v]->GetBinError(j+1) / ahSignalRsub[i]->GetBinContent(j+1));

              if(TMath::Abs(ahDevRsubReso[i][v]->GetBinContent(j+1))>maxreso[i][j]) { maxreso[i][j] = TMath::Abs(ahDevRsubReso[i][v]->GetBinContent(j+1)); }
            }        
        }
    }
  //
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999?Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]>900?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      vectex.push_back(texpt);

      TH2F* hempty = new TH2F("hempty", ";r;Deviation / Default", 10, drBins[0], drBins[nDrBins], 10, -0.3, 0.5);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->GetXaxis()->SetNdivisions(505);

      TCanvas* creso = new TCanvas("creso", "", 600, 600);
      hempty->Draw();
      xjjroot::drawline(drBins[0], 0, drBins[nDrBins], 0, kGray+3, 10, 3);
      TLegend* legreso = new TLegend(0.60, 0.88-(nReso)*0.055, 0.90, 0.88);
      xjjroot::setleg(legreso);
      for(int v=0;v<nReso;v++)
        {
          xjjroot::setthgrstyle(ahDevRsubReso[i][v], colorlist[v], -1, -1, colorlist[v], 2, 3);
          ahDevRsubReso[i][v]->Draw("same e");
          legreso->AddEntry(ahDevRsubReso[i][v], legReso[v].Data(), "l");
        }
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      legreso->Draw();
      creso->SaveAs(Form("plotjetsyst/cresodev_%s_%s_pt_%d.pdf", outputname.Data(),"eta",i));

      delete legreso;
      delete creso;
      delete hempty;

      vectex.pop_back();
    }

  std::cout<<std::string(60,'=')<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(16)<<"   r";
  for(int v=0;v<nReso;v++)
    std::cout<<std::setiosflags(std::ios::left)<<std::setw(8)<<nameReso[v];
  std::cout<<std::endl;
  std::cout<<std::string(60,'-')<<std::endl;
  for(int i=0;i<nPtBins;i++)
    {
      std::cout<<Form("D pt (%.2f, %.2f)",ptBins[i],ptBins[i+1])<<std::endl;
      for(int j=0;j<nDrBins;j++)
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(16)<<Form("[ %.2f, %.2f ]",drBins[j],drBins[j+1]);
          for(int v=0;v<nReso;v++)
            {
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(8)<<Form("%.1f",TMath::Abs(ahDevRsubReso[i][v]->GetBinContent(j+1))*100);
            }
          std::cout<<std::endl;
        }
      std::cout<<std::endl;
    }
  std::cout<<std::string(60,'=')<<std::endl;
  std::cout<<std::endl;

  if(jetetamin<=0 && jetetamax>=1.6)
    {
      std::cout<<"\033[1;36mstd::vector<std::vector<Float_t>> syst"<<Form("%.0f",jetptmin)<<Form("%.0f",jetptmax)<<"_RESO_"<<collisionsyst<<" = {";
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              if(!j) std::cout<<"{";
              std::cout<<Form("%.1f",maxreso[i][j]*100.)<<(j<nDrBins-1?", ":"}");
            }
          if(i<nPtBins-1) std::cout<<","<<std::endl;
        }
      std::cout<<"};\033[0m"<<std::endl;
    }
}

int main(int argc, char* argv[])
{
  if(argc==(1+nReso+7))
    {
      std::vector<TString> inputnameReso;
      for(int m=0;m<nReso;m++) inputnameReso.push_back(argv[m+2]);
      jetsyst_plothist(argv[1], inputnameReso, argv[1+nReso+1], argv[1+nReso+2], atof(argv[1+nReso+3]), atof(argv[1+nReso+4]), atof(argv[1+nReso+5]), atof(argv[1+nReso+6]));
      return 0;
    }
  else
    {
      std::cout<<"error: invalid parameter number - jetsyst_plothist"<<std::endl;
      return 1;
    }
}
