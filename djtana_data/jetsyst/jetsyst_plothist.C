#include "jetsyst.h"

void jetsyst_plothist(TString inputname, std::vector<TString> inputnameScale,
                      TString outputname, TString collisionsyst,
                      Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax)
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

  if(gethists(inf, "plothist_default")) return;
  if(gethists(infScale, "plothist_scale")) return;

  if(createhists("plothist")) return;

  //
  Float_t maxQG[nPtBins][nDrBins];
  Float_t maxPM[nPtBins][nDrBins];
  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++)
        {
          maxQG[i][j] = 0;
          maxPM[i][j] = 0;
          for(int v=0;v<nScale;v++)
            {
              ahDevRnormScale[0][i][v]->SetBinContent(j+1, (ahSignalRnormScale[0][i][v]->GetBinContent(j+1)-ahSignalRnorm[0][i]->GetBinContent(j+1)) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              ahDevRnormScale[0][i][v]->SetBinError(j+1, ahSignalRnormScale[0][i][v]->GetBinError(j+1) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              ahDevRsubScale[i][v]->SetBinContent(j+1, (ahSignalRsubScale[i][v]->GetBinContent(j+1)-ahSignalRsub[i]->GetBinContent(j+1)) / ahSignalRsub[i]->GetBinContent(j+1));
              ahDevRsubScale[i][v]->SetBinError(j+1, ahSignalRsubScale[i][v]->GetBinError(j+1) / ahSignalRsub[i]->GetBinContent(j+1));

              // ahDevRnormScale[0][i][v]->SetBinContent(j+1, ahDevRnormScale[0][i][v]->GetBinContent(j+1) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              // ahDevRnormScale[0][i][v]->SetBinError(j+1, ahDevRnormScale[0][i][v]->GetBinError(j+1) / ahSignalRnorm[0][i]->GetBinContent(j+1));
              // ahDevRsubScale[i][v]->SetBinContent(j+1, ahDevRsubScale[i][v]->GetBinContent(j+1) / ahSignalRsub[i]->GetBinContent(j+1));
              // ahDevRsubScale[i][v]->SetBinError(j+1, ahDevRsubScale[i][v]->GetBinError(j+1) / ahSignalRsub[i]->GetBinContent(j+1));

              if((v==2 || v==3) && TMath::Abs(ahDevRsubScale[i][v]->GetBinContent(j+1)) > maxQG[i][j])
                { maxQG[i][j] = TMath::Abs(ahDevRsubScale[i][v]->GetBinContent(j+1)); }
              if((v==0 || v==1) && TMath::Abs(ahDevRsubScale[i][v]->GetBinContent(j+1)) > maxPM[i][j])
                { maxPM[i][j] = TMath::Abs(ahDevRsubScale[i][v]->GetBinContent(j+1)); }
            }
          ahDevRsubtotal[i]->SetBinContent(j+1, TMath::Sqrt(maxQG[i][j]*maxQG[i][j]+maxPM[i][j]*maxPM[i][j]));
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

      TH2F* hempty = new TH2F("hempty", ";r;Deviation / Default", 10, drBins[0], drBins[nDrBins], 10, -0.5, 0.8);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->GetXaxis()->SetNdivisions(505);

      TCanvas* cscale = new TCanvas("cscale", "", 600, 600);
      hempty->Draw();
      xjjroot::drawline(drBins[0], 0, drBins[nDrBins], 0, kGray+3, 10, 3);
      TLegend* legscale = new TLegend(0.60, 0.88-(nScale)*0.053, 0.90, 0.88);
      xjjroot::setleg(legscale);
      for(int v=0;v<nScale;v++)
        {
          xjjroot::setthgrstyle(ahDevRsubScale[i][v], colorlist[v], -1, -1, colorlist[v], 2, 3);
          ahDevRsubScale[i][v]->Draw("same e");
          legscale->AddEntry(ahDevRsubScale[i][v], legScale[v].Data(), "l");
        }
      xjjroot::setthgrstyle(ahDevRsubtotal[i], kGray+1, -1, -1, kGray+1, 7, 7);
      ahDevRsubtotal[i]->Draw("same");
      legscale->AddEntry(ahDevRsubtotal[i], "total", "l");
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      legscale->Draw();
      cscale->SaveAs(Form("plotjetsyst/cscaledev_%s_eta_pt_%d.pdf", outputname.Data(),i));

      delete legscale;
      delete cscale;
      delete hempty;

      vectex.pop_back();
    }

  std::cout<<std::string(90,'=')<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(16)<<"   r";
  for(int v=0;v<nScale;v++)
    { std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<nameScale[v]; }
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<"(max PM)";
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<"(max QG)";
  std::cout<<std::endl;
  std::cout<<std::string(90,'-')<<std::endl;
  for(int i=0;i<nPtBins;i++)
    {
      std::cout<<Form("D pt (%.2f, %.2f)",ptBins[i],ptBins[i+1])<<std::endl;
      for(int j=0;j<nDrBins;j++)
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(16)<<Form("[ %.2f, %.2f ]",drBins[j],drBins[j+1]);
          for(int v=0;v<nScale;v++)
            {
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<Form("%.1f",TMath::Abs(ahDevRsubScale[i][v]->GetBinContent(j+1))*100);
            }
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<Form("%.1f",maxPM[i][j]*100);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<Form("%.1f",maxQG[i][j]*100);
          std::cout<<std::endl;
        }
      std::cout<<std::endl;
    }
  std::cout<<std::string(90,'=')<<std::endl;
  std::cout<<std::endl;

  if(jetetamin<=0 && jetetamax>=1.6)
    {
      std::cout<<"\033[1;36mstd::vector<std::vector<Float_t>> syst"<<Form("%.0f",jetptmin)<<Form("%.0f",jetptmax)<<"_SCALE_"<<collisionsyst<<" = {";
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              if(!j) std::cout<<"{";
              std::cout<<Form("%.1f",TMath::Sqrt(maxPM[i][j]*maxPM[i][j]+maxQG[i][j]*maxQG[i][j])*100.)<<(j<nDrBins-1?", ":"}");
            }
          if(i<nPtBins-1) std::cout<<","<<std::endl;
        }
      std::cout<<"};\033[0m"<<std::endl;
    }

}

int main(int argc, char* argv[])
{
  if(argc==(1+nScale+7))
    {
      std::vector<TString> inputnameScale;
      for(int m=0;m<nScale;m++) inputnameScale.push_back(argv[m+2]);
      jetsyst_plothist(argv[1], inputnameScale, argv[1+nScale+1], argv[1+nScale+2], atof(argv[1+nScale+3]), atof(argv[1+nScale+4]), atof(argv[1+nScale+5]), atof(argv[1+nScale+6]));
      return 0;
    }
  else
    {
      std::cout<<"error: invalid parameter number - jetsyst_plothist"<<std::endl;
      return 1;
    }
}
