#include "pdfvariation.h"

void pdfvar_plotratio(TString inputnamePP, TString inputnamePbPb, TString outputname,
                      Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax)
{
  xjjroot::setgstyle(1);
  TFile* infPP = new TFile(Form("%s.root", inputnamePP.Data()));
  if(!infPP->IsOpen()) return;
  if(gethists(infPP, "plotratioPP")) return;
  TFile* infPbPb = new TFile(Form("%s.root", inputnamePbPb.Data()));
  if(!infPbPb->IsOpen()) return;
  if(gethists(infPbPb, "plotratioPbPb")) return;

  if(createhists("plotratio")) return;

  //
  Float_t maxsignal[nPtBins][nDrBins];
  Float_t maxbackground[nPtBins][nDrBins];
  for(int i=0;i<nPtBins;i++)
    {
      xjjroot::setthgrstyle(ahSignalRdevtotalRatio[i], kGray+1, -1, -1, kGray+1, 10, 3);
      for(int v=0;v<nVariation;v++)
        {
          ahSignalRrawRatio[i][v]->Divide(ahSignalRrawPbPb[i][v], ahSignalRrawPP[i][v]);
          for(int j=0;j<nDrBins;j++)
            {
              ahSignalRdevRatio[i][v]->SetBinContent(j+1, (ahSignalRrawRatio[i][v]->GetBinContent(j+1)-ahSignalRrawRatio[i][0]->GetBinContent(j+1)) / ahSignalRrawRatio[i][0]->GetBinContent(j+1));
              ahSignalRdevRatio[i][v]->SetBinError(j+1, ahSignalRrawRatio[i][v]->GetBinError(j+1) / ahSignalRrawRatio[i][0]->GetBinContent(j+1));
            }
        }
      for(int j=0;j<nDrBins;j++)
        {
          maxsignal[i][j] = 0;
          maxbackground[i][j] = 0;
          for(int v=0;v<nVariation;v++)
            {
              if(std::find(vsignal, vsignal+nvsignal, v)!=vsignal+nvsignal && TMath::Abs(ahSignalRdevRatio[i][v]->GetBinContent(j+1)) > maxsignal[i][j])
                maxsignal[i][j] = TMath::Abs(ahSignalRdevRatio[i][v]->GetBinContent(j+1));
              if(std::find(vbackground, vbackground+nvbackground, v)!=vbackground+nvbackground && TMath::Abs(ahSignalRdevRatio[i][v]->GetBinContent(j+1)) > maxbackground[i][j])
                maxbackground[i][j] = TMath::Abs(ahSignalRdevRatio[i][v]->GetBinContent(j+1));
            }
          ahSignalRdevtotalRatio[i]->SetBinContent(j+1, TMath::Sqrt(maxsignal[i][j]*maxsignal[i][j]+maxbackground[i][j]*maxbackground[i][j]));
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

      TCanvas* c = new TCanvas("c", "", 600, 600);
      TH2F* hempty = new TH2F("hempty", ";r;Yield deviation (PbPb/pp)", 10, drBins[0], drBins[nDrBins], 10, -0.3, 0.5);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->GetXaxis()->SetNdivisions(505);
      hempty->Draw();
      TLegend* leg = new TLegend(0.60, 0.88-nVariation*0.052, 0.90, 0.88);
      xjjroot::setleg(leg);
      ahSignalRdevtotalRatio[i]->Draw("same e");
      for(int v=0;v<nVariation;v++)
        {
          xjjroot::setthgrstyle(ahSignalRdevRatio[i][v], fitcolor[v], -1, -1, fitcolor[v], 2, 3);
          ahSignalRdevRatio[i][v]->Draw("same");
          leg->AddEntry(ahSignalRdevRatio[i][v], fitleg[v].Data(), "l");
        }
      leg->AddEntry(ahSignalRdevtotalRatio[i], "total", "l");
      xjjroot::drawCMS("");
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c->SaveAs(Form("plotpdfvar/cdevRatio_%s_%s_pt_%d.pdf", outputname.Data(),"eta",i));

      delete leg;
      delete hempty;
      delete c;

      vectex.pop_back();
    }

  std::cout<<std::string(90,'=')<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(16)<<"   r";
  for(int v=0;v<nVariation;v++)
    { std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<fitname[v]; }
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<"(signal)";
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<"(background)";
  std::cout<<std::endl;
  std::cout<<std::string(90,'-')<<std::endl;
  for(int i=0;i<nPtBins;i++)
    {
      std::cout<<Form("D pt (%.2f, %.2f)",ptBins[i],ptBins[i+1])<<std::endl;
      for(int j=0;j<nDrBins;j++)
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(16)<<Form("[ %.2f, %.2f ]",drBins[j],drBins[j+1]);
          for(int v=0;v<nVariation;v++)
            {
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<Form("%.1f",TMath::Abs(ahSignalRdevRatio[i][v]->GetBinContent(j+1))*100);
            }
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<Form("%.1f",maxsignal[i][j]*100);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<Form("%.1f",maxbackground[i][j]*100);
          std::cout<<std::endl;
        }
      std::cout<<std::endl;
    }
  std::cout<<std::string(90,'=')<<std::endl;
  std::cout<<std::endl;
  if(jetetamin<=0 && jetetamax>=1.6)
    {
      std::cout<<"\033[1;36mstd::vector<std::vector<Float_t>> syst"<<Form("%.0f",jetptmin)<<Form("%.0f",jetptmax)<<"_PDF_ratio = {";
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              if(!j) std::cout<<"{";
              std::cout<<Form("%.1f",TMath::Sqrt(maxsignal[i][j]*maxsignal[i][j]+maxbackground[i][j]*maxbackground[i][j])*100)<<(j<nDrBins-1?", ":"}");
            }
          if(i<nPtBins-1) std::cout<<","<<std::endl;
        }
      std::cout<<"};\033[0m"<<std::endl;
    }
}

int main(int argc, char* argv[])
{
  if(argc == 8)
    {
      pdfvar_plotratio(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
      return 0;
    }
  else
    {
      std::cout<<"error: invalid parameter number - pdfvar_plotratio"<<std::endl;
      return 1;
    }
}
