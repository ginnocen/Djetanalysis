#include "djtana.h"

void djtana_usehist(TString inputhistname, TString inputtplname, TString outputname, 
                    TString collisionsyst, Int_t irecogen,
                    Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  int arguerr(TString collisionsyst, Int_t irecogen);
  if(arguerr(collisionsyst, irecogen)) return;

  if(createhists("usehist")) return;
  Bool_t isrecoD = irecogen%2==0;

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "hist")) return;
  if(isrecoD)
    {
      TFile* inftpl = new TFile(Form("%s.root",inputtplname.Data()));
      if(!inftpl->IsOpen()) return;
      if(gethists(inftpl, "tpl")) return;
    }

  std::vector<float> vdrBins, vzBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  for(int j=0;j<sizeof(zBins)/sizeof(zBins[0]);j++) vzBins.push_back(zBins[j]);

  xjjroot::dfitter* dft = new xjjroot::dfitter("");
  
  for(int l=0;l<nRefBins;l++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          TString               tleg[2]          =  {"#DeltaR",            "p_{T}^{D} / p_{T}^{jet}"};
          TString               tname[2]         =  {"dr",                 "z"};
          std::vector<float>    vxBins[2]         = {vdrBins,              vzBins};
          TH1F*                 hSignalXraw[2]   =  {ahSignalRraw[l][i],   ahSignalZraw[l][i]};
          TH1F*                 hSignalX[2]      =  {ahSignalR[l][i],      ahSignalZ[l][i]};
          TH1F*                 hSignalXnorm[2]  =  {ahSignalRnorm[l][i],  ahSignalZnorm[l][i]};
          TH1F*                 hXEfficiency[2]  =  {ahREfficiency[l][i],  ahZEfficiency[l][i]};
          for(int k=0;k<2;k++)
            {
              if(isrecoD)
                {
                  for(int j=0;j<vxBins[k].size()-1;j++)
                    {
                      TH1F* hHistoXMass = k==0?ahHistoRMass[l][i][j]:ahHistoZMass[l][i][j];
                      TH1F* hHistoXMassSignal = k==0?ahHistoRMassSignal[l][i][j]:ahHistoZMassSignal[l][i][j];
                      TH1F* hHistoXMassSwapped = k==0?ahHistoRMassSwapped[l][i][j]:ahHistoZMassSwapped[l][i][j];
                      std::vector<TString> vectex = 
                        {
                          Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()),
                          "|y^{D}| < 2",
                          Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
                          Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
                          Form("%s < %s < %s",xjjc::number_remove_zero(vxBins[k].at(j)).c_str(),tleg[k].Data(),xjjc::number_remove_zero(vxBins[k].at(j+1)).c_str())
                        };
                      dft->fit(hHistoXMass, hHistoXMassSignal, hHistoXMassSwapped, collisionsyst, Form("plotfits/cmass_%s_%s_pt_%d_%s_%d",outputname.Data(),tRef[l].Data(),i,tname[k].Data(),j), vectex);
                      hSignalXraw[k]->SetBinContent(j+1, dft->GetY());
                      hSignalXraw[k]->SetBinError(j+1, dft->GetYE());
                      hSignalX[k]->SetBinContent(j+1, dft->GetY());
                      hSignalX[k]->SetBinError(j+1, dft->GetYE());
                      hSignalXnorm[k]->SetBinContent(j+1, dft->GetY() / hSignalXnorm[k]->GetBinWidth(j+1));
                      hSignalXnorm[k]->SetBinError(j+1, dft->GetYE() / hSignalXnorm[k]->GetBinWidth(j+1));
                    }
                  hSignalX[k]->Divide(hXEfficiency[k]);
                  hSignalXnorm[k]->Divide(hXEfficiency[k]);
                }
              else
                {
                  for(int j=0;j<vxBins[k].size()-1;j++) 
                    {
                      TH1F* hHistoXMass = k==0?ahHistoRMass[l][i][j]:ahHistoZMass[l][i][j];
                      hSignalX[k]->SetBinContent(j+1, hHistoXMass->Integral());
                      hSignalXnorm[k]->SetBinContent(j+1, hHistoXMass->Integral() / hSignalXnorm[k]->GetBinWidth(j+1));
                    }
                }
              hSignalXnorm[k]->Scale(1./hNjets->GetBinContent(1));
            }
        }
    }
  delete dft;
  

  TFile* outf = new TFile(Form("rootfiles/xsec_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("usehist")) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==9)
    {
      djtana_usehist(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_usehist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t irecogen)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  if(irecogen<0 && irecogen>3)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"irecogen\""<<std::endl;
      return 1;
    }
  return 0;
}

