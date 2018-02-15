#include "pdfvariation.h"

void pdfvar_usehist(TString inputhistname, TString inputtplname, TString outputname,
                    TString collisionsyst, 
                    Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
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

  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };

  for(int v=0;v<nVariation;v++)
    {
      xjjroot::dfitter_variation* dft = new xjjroot::dfitter_variation(Form("Y %s",fitopt[v].Data()));
      std::cout<<fitname[v]<<std::endl;
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              if(l) continue;
              for(int j=0;j<nDrBins;j++)
                {
                  vectex.push_back(Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()));
                  vectex.push_back(Form("%s < #DeltaR < %s",xjjc::number_remove_zero(drBins[j]).c_str(),xjjc::number_remove_zero(drBins[j+1]).c_str()));
                  dft->fit(ahHistoRMass[l][i][j], ahHistoRMassSignal[l][i][j], ahHistoRMassSwapped[l][i][j], collisionsyst, Form("plotpdfvarfit/cmass_%s_%s_pt_%d_dr_%d_%s",outputname.Data(),tRef[l].Data(),i,j,fitname[v].Data()), vectex);
                  vectex.pop_back();
                  vectex.pop_back();
                  ahSignalRraw[l][i][v]->SetBinContent(j+1, dft->GetY());
                  ahSignalRraw[l][i][v]->SetBinError(j+1, dft->GetY()>0?dft->GetYE():0);
                }
            }
        }
      delete dft;
    }

  for(int v=0;v<nVariation;v++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              if(l) continue;
              for(int j=0;j<nDrBins;j++)
                {
                  ahSignalRdev[l][i][v]->SetBinContent(j+1, (ahSignalRraw[l][i][v]->GetBinContent(j+1)-ahSignalRraw[l][i][0]->GetBinContent(j+1)) / ahSignalRraw[l][i][0]->GetBinContent(j+1));
                  // std::cout<<ahSignalRdev[l][i][v]->GetBinContent(j+1)<<std::endl;
                }
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
  if(argc == 8)
    {
      pdfvar_usehist(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]));
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
