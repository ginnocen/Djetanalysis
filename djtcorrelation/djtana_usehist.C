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

  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };

  std::vector<float> vdrBins, vzBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  for(int j=0;j<sizeof(zBins)/sizeof(zBins[0]);j++) vzBins.push_back(zBins[j]);

  xjjroot::dfitter* dft = new xjjroot::dfitter("S");
  
  std::vector<TString>             tleg                =  {"#DeltaR",                    "p_{T}^{D} / p_{T}^{jet}"};
  std::vector<TString>             tname               =  {"dr",                         "z"};
  std::vector<std::vector<float>>  vxBins              =  {vdrBins,                      vzBins};
  std::vector<TH1F**>              hHistoXMass         =  {(TH1F**)ahHistoRMass,         (TH1F**)ahHistoZMass};
  std::vector<TH1F**>              hHistoXMassSignal   =  {(TH1F**)ahHistoRMassSignal,   (TH1F**)ahHistoZMassSignal};
  std::vector<TH1F**>              hHistoXMassSwapped  =  {(TH1F**)ahHistoRMassSwapped,  (TH1F**)ahHistoZMassSwapped};
  std::vector<TH1F**>              hSignalXraw         =  {(TH1F**)ahSignalRraw,         (TH1F**)ahSignalZraw};
  std::vector<TH1F**>              hSignalX            =  {(TH1F**)ahSignalR,            (TH1F**)ahSignalZ};
  std::vector<TH1F**>              hSignalXsub         =  {(TH1F**)ahSignalRsub,         (TH1F**)ahSignalZsub};
  std::vector<TH1F**>              hSignalXnorm        =  {(TH1F**)ahSignalRnorm,        (TH1F**)ahSignalZnorm};
  std::vector<TH1F**>              hXEfficiency        =  {(TH1F**)ahREfficiency,        (TH1F**)ahZEfficiency};

  for(int k=0;k<2;k++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              if(isrecoD)
                {
                  for(int j=0;j<vxBins[k].size()-1;j++)
                    {
                      vectex.push_back(Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()));
                      vectex.push_back(Form("%s < %s < %s",xjjc::number_remove_zero(vxBins[k].at(j)).c_str(),tleg[k].Data(),xjjc::number_remove_zero(vxBins[k].at(j+1)).c_str()));
                      dft->fit((hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j], (hHistoXMassSignal.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j], (hHistoXMassSwapped.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j], collisionsyst, Form("plotfits/cmass_%s_%s_pt_%d_%s_%d",outputname.Data(),tRef[l].Data(),i,tname[k].Data(),j), vectex);
                      vectex.pop_back();
                      vectex.pop_back();
                      (hSignalXraw.at(k))[l*nPtBins+i]->SetBinContent(j+1, dft->GetY());
                      (hSignalXraw.at(k))[l*nPtBins+i]->SetBinError(j+1, dft->GetY()>0?dft->GetYE():0);
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinContent(j+1, dft->GetY());
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinError(j+1, dft->GetY()>0?dft->GetYE():0);
                      (hSignalXnorm.at(k))[l*nPtBins+i]->SetBinContent(j+1, dft->GetY() / (hSignalXnorm.at(k))[l*nPtBins+i]->GetBinWidth(j+1));
                      (hSignalXnorm.at(k))[l*nPtBins+i]->SetBinError(j+1, (dft->GetY()>0?dft->GetYE():0) / (hSignalXnorm.at(k))[l*nPtBins+i]->GetBinWidth(j+1));
                    }
                  (hSignalX.at(k))[l*nPtBins+i]->Divide((hXEfficiency.at(k))[l*nPtBins+i]);
                  (hSignalXnorm.at(k))[l*nPtBins+i]->Divide((hXEfficiency.at(k))[l*nPtBins+i]);
                }
              else
                {
                  for(int j=0;j<vxBins[k].size()-1;j++) 
                    {
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinContent(j+1, (hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j]->Integral());
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinError(j+1, TMath::Sqrt((hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j]->Integral()));
                      (hSignalXnorm.at(k))[l*nPtBins+i]->SetBinContent(j+1, (hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j]->Integral() / (hSignalXnorm.at(k))[l*nPtBins+i]->GetBinWidth(j+1));
                      (hSignalXnorm.at(k))[l*nPtBins+i]->SetBinError(j+1, TMath::Sqrt((hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j]->Integral()) / (hSignalXnorm.at(k))[l*nPtBins+i]->GetBinWidth(j+1));
                    }
                }
              (hSignalXnorm.at(k))[l*nPtBins+i]->Scale(1./hNjets->GetBinContent(1));
            }        
          (hSignalXsub.at(k))[i]->Add((hSignalXnorm.at(k))[0*nPtBins+i], (hSignalXnorm.at(k))[1*nPtBins+i], 1, -1);
        }
    }
  delete dft;
  
  if(isrecoD)
    {
      for(int k=0;k<2;k++)
        {
          TCanvas* c = new TCanvas("c", "", 600, 600);
          TH2F* hempty = new TH2F("hempty", Form(";%s;%s",tleg[k].Data(),"#alpha x #epsilon_{reco} x #epsilon_{sel}"), 5, vxBins[k].front(), vxBins[k].back(), 10, 0, 1.);
          hempty->GetXaxis()->SetNdivisions(505);
          xjjroot::sethempty(hempty, 0, 0.5);
          hempty->Draw();
          TLegend* leg = new TLegend(0.53, 0.88-nPtBins*nRefBins*0.06, 0.85, 0.88);
          xjjroot::setleg(leg);
          for(int i=0;i<nPtBins;i++)
            {
              for(int l=0;l<nRefBins;l++)
                {
                  xjjroot::setthgrstyle((hXEfficiency.at(k))[l*nPtBins+i], amcolor[i], amstyle[l][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
                  (hXEfficiency.at(k))[l*nPtBins+i]->Draw("pe same");
                  TString tleg = l==1?"#eta reflection":(ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()));
                  leg->AddEntry((hXEfficiency.at(k))[l*nPtBins+i], tleg.Data(), "p");
                }
            }
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
          texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          if(k) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "#DeltaR < 0.3");
          leg->Draw();
          c->SaveAs(Form("ploteff/ceff_%s_%s.pdf",tname[k].Data(),outputname.Data()));
          delete leg;
          delete hempty;
          delete c;
        }
    }

  TFile* outf = new TFile(Form("rootfiles/xsec_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists(Form("usehist %s", isrecoD?"recoD":""))) return;
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

