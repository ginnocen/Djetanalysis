#include "pdfvariation.h"

void pdfvar_usehist(TString inputhistname, TString inputtplname, TString inputtplscalename, TString outputname,
                    TString collisionsyst, 
                    Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  if(createhists("usehist")) return;

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "hist")) return;
  TFile* inftpl = new TFile(Form("%s.root",inputtplname.Data()));
  if(!inftpl->IsOpen()) return;
  if(gethists(inftpl, "tpl")) return;
  TFile* inftplscale = new TFile(Form("%s.root",inputtplscalename.Data()));
  if(!inftplscale->IsOpen()) return;
  if(gethists(inftplscale, "tplscale")) return;

  xjjroot::setgstyle();

  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999?Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]<999?Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()):Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str());
      for(int j=0;j<nDrBins;j++)
        {
          TCanvas* c = new TCanvas("c", "", 600*nVariation, 600);
          c->Divide(nVariation, 1);
          TH1F* hMassSignal[nVariation] = {(TH1F*)ahHistoRMassSignal[i][j], (TH1F*)ahHistoRMassSignal[i][j], (TH1F*)ahHistoRMassSignal[i][j], (TH1F*)ahHistoRMassSignallow[i][j], (TH1F*)ahHistoRMassSignalhigh[i][j]};
          TH1F* hMassSwapped[nVariation] = {(TH1F*)ahHistoRMassSwapped[i][j], (TH1F*)ahHistoRMassSwapped[i][j], (TH1F*)ahHistoRMassSwapped[i][j], (TH1F*)ahHistoRMassSwappedlow[i][j], (TH1F*)ahHistoRMassSwappedhigh[i][j]};
          for(int v=0;v<nVariation;v++)
            {
              c->cd(v+1);
              xjjroot::dfitter_variation* dft = new xjjroot::dfitter_variation(Form("Y %s",fitopt[v].Data()));
              std::cout<<fitname[v]<<std::endl;
              vectex.push_back(texpt);
              vectex.push_back(Form("%s < r < %s",xjjc::number_remove_zero(drBins[j]).c_str(),xjjc::number_remove_zero(drBins[j+1]).c_str()));
              // dft->fit(ahHistoRMass[i][j], ahHistoRMassSignal[i][j], ahHistoRMassSwapped[i][j], collisionsyst, vectex);
              dft->fit(ahHistoRMass[i][j], hMassSignal[v], hMassSwapped[v], collisionsyst, vectex);
              Float_t texVxpos = 0.22, texVypos = 0.30, texVdypos = 0.053;
              xjjroot::drawtex(texVxpos, texVypos=(texVypos-texVdypos), fitleg[v].Data());
              vectex.pop_back();
              vectex.pop_back();
              ahSignalRraw[i][v]->SetBinContent(j+1, dft->GetY());
              ahSignalRraw[i][v]->SetBinError(j+1, dft->GetY()>0?dft->GetYE():0);
              delete dft;
            }
          c->SaveAs(Form("plotpdfvarfit/cmass_%s_%s_pt_%d_dr_%d.pdf",outputname.Data(),"eta",i,j));
          delete c;
        }
    }

  for(int v=0;v<nVariation;v++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          // ahSignalRdev[i][v]->Add(ahSignalRraw[i][v], ahSignalRraw[i], 1, -1);
          // ahSignalRdev[i][v]->Divide(ahSignalRraw[i][v], ahSignalRraw[i]);
          for(int j=0;j<nDrBins;j++)
            {
              ahSignalRdev[i][v]->SetBinContent(j+1, ahSignalRraw[i][v]->GetBinContent(j+1) / ahSignalRraw[i][0]->GetBinContent(j+1));
              ahSignalRdev[i][v]->SetBinError(j+1, ahSignalRraw[i][v]->GetBinError(j+1) / ahSignalRraw[i][0]->GetBinContent(j+1));
            }
          for(int j=0;j<nDrBins;j++)
            {
              // std::cout<<v<<" "<<ahSignalRraw[i][v]->GetBinContent(j+1)<<" "<<ahSignalRraw[i][0]->GetBinContent(j+1)<<" "<<ahSignalRdev[i][v]->GetBinContent(j+1)<<" "<<ahSignalRdev[i][v]->GetBinError(j+1)<<std::endl;
              if(v==0)
                {
                  ahSignalRdev[i][v]->SetBinContent(j+1, 1);
                  ahSignalRdev[i][v]->SetBinError(j+1, 0);
                }
              ahSignalRdev[i][v]->SetBinContent(j+1, ahSignalRdev[i][v]->GetBinContent(j+1) -1);
              // ahSignalRdev[i][v]->SetBinError(j+1, ahSignalRdev[i][v]->GetBinError(j+1) / ahSignalRraw[i][0]->GetBinContent(j+1));
            }
        }
    }

  TFile* output = new TFile(Form("rootfiles/pdfvar_%s.root", outputname.Data()), "recreate");
  output->cd();
  if(writehists("usehist")) return;
  output->Write();
  output->Close();

}


int main(int argc, char* argv[])
{
  if(argc == 10)
    {
      pdfvar_usehist(argv[1], argv[2], argv[3], argv[4], argv[5], atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]));
      return 0;
    }
  else
    {
      std::cout<<"error: invalid parameter number - pdfvar_usehist"<<std::endl;
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
