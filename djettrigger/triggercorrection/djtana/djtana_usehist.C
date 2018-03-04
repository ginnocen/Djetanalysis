#include "djtana.h"

void djtana_usehist(TString inputhistname, TString inputtplname, TString outputname, 
                    TString collisionsyst, Int_t irecogen,
                    Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                    Int_t signalMC=1)
{
  int arguerr(TString collisionsyst, Int_t irecogen);
  if(arguerr(collisionsyst, irecogen)) return;

  if(createhists("usehist")) return;
  Bool_t isrecoD = irecogen%2==0;
  Bool_t ispp = collisionsyst=="pp";
  Bool_t isMC = inputhistname.Contains("MC");

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
    };
  TString texjetpt = jetptmax<999?Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  std::vector<float> vdrBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  xjjroot::dfitter* dft = new xjjroot::dfitter("");
  
  std::vector<TString>             tleg                   =  {"r"};
  std::vector<TString>             tname                  =  {"dr"};
  std::vector<std::vector<float>>  vxBins                 =  {vdrBins};
  std::vector<TH1F**>              hHistoXMass            =  {(TH1F**)ahHistoRMass};
  std::vector<TH1F**>              hHistoXMassSignal      =  {(TH1F**)ahHistoRMassSignal};
  std::vector<TH1F**>              hHistoXMassSwapped     =  {(TH1F**)ahHistoRMassSwapped};
  std::vector<TH1F**>              hSignalXraw            =  {(TH1F**)ahSignalRraw};
  std::vector<TH1F**>              hSignalX               =  {(TH1F**)ahSignalR};
  std::vector<TH1F**>              hSignalXsub            =  {(TH1F**)ahSignalRsub};
  std::vector<TH1F**>              hSignalXnorm           =  {(TH1F**)ahSignalRnorm};
  std::vector<TH1F**>              hXEfficiency           =  {(TH1F**)ahREfficiency};
  std::vector<TH1F**>              hHistoXMassRef         =  {(TH1F**)ahHistoRMassRef};
  std::vector<TH1F**>              hHistoXMassSignalRef   =  {(TH1F**)ahHistoRMassSignalRef};
  std::vector<TH1F**>              hHistoXMassSwappedRef  =  {(TH1F**)ahHistoRMassSwappedRef};
  std::vector<TH1F**>              hXEfficiencyRef        =  {(TH1F**)ahREfficiencyRef};
  std::vector<TH1F**>              hSignalXRef            =  {(TH1F**)ahSignalRRef};

  int k = 0;
  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]<999?Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()):Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str());
      for(int l=0;l<nRefBins;l++)
        {
          if(isrecoD)
            {
              if(!l)
                {
                  for(int j=0;j<vxBins[k].size()-1;j++)
                    {
                      vectex.push_back(texpt);
                      vectex.push_back(Form("%s < %s < %s",xjjc::number_remove_zero(vxBins[k].at(j)).c_str(),tleg[k].Data(),xjjc::number_remove_zero(vxBins[k].at(j+1)).c_str()));
                      dft->fit((hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j], (hHistoXMassSignal.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j], (hHistoXMassSwapped.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j], collisionsyst, Form("plotfits/cmass_%s_%s_pt_%d_%s_%d",outputname.Data(),tRef[l].Data(),i,tname[k].Data(),j), vectex);
                      vectex.pop_back();
                      vectex.pop_back();
                      (hSignalXraw.at(k))[l*nPtBins+i]->SetBinContent(j+1, dft->GetY());
                      (hSignalXraw.at(k))[l*nPtBins+i]->SetBinError(j+1, dft->GetY()>0?dft->GetYE():0);
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinContent(j+1, dft->GetY());
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinError(j+1, dft->GetY()>0?dft->GetYE():0);
                    }
                  (hSignalX.at(k))[l*nPtBins+i]->Divide((hXEfficiency.at(k))[l*nPtBins+i]);
                }
              else
                {
                  vectex.push_back(texpt);
                  vectex.push_back(Form("0 < %s < 0.3",tleg[k].Data()));
                  dft->fit((hHistoXMassRef.at(k))[i], (hHistoXMassSignalRef.at(k))[i], (hHistoXMassSwappedRef.at(k))[i], collisionsyst, Form("plotfits/cmass_%s_%s_pt_%d_%s",outputname.Data(),tRef[l].Data(),i,tname[k].Data()), vectex);
                  vectex.pop_back();
                  vectex.pop_back();
                  (hSignalXRef.at(k))[i]->SetBinContent(1, dft->GetY());
                  (hSignalXRef.at(k))[i]->SetBinError(1, dft->GetY()>0?dft->GetYE():0);
                  (hSignalXRef.at(k))[i]->Divide((hXEfficiencyRef.at(k))[i]);
                  Double_t density = (hSignalXRef.at(k))[i]->GetBinContent(1);
                  Double_t densityError = (hSignalXRef.at(k))[i]->GetBinError(1);
                  // Double_t densityError;
                  // Double_t density = (hSignalX.at(k))[l*nPtBins+i]->IntegralAndError(1, 3, densityError);
                  for(int j=0;j<vxBins[k].size()-1;j++) 
                    {
                      Float_t area = drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j];
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinContent(j+1, density * area / (0.3*0.3));
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinError(j+1, densityError * area / (0.3*0.3));
                    }
                }
            }
          else
            {
              if(!l)
                {
                  for(int j=0;j<vxBins[k].size()-1;j++) 
                    {
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinContent(j+1, (hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j]->GetBinContent(33));
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinError(j+1, (hHistoXMass.at(k))[(l*nPtBins+i)*(vxBins[k].size()-1)+j]->GetBinError(33));
                    }
                }
              else
                {
                  Double_t density = (hHistoXMassRef.at(k))[i]->GetBinContent(33);
                  Double_t densityError = (hHistoXMassRef.at(k))[i]->GetBinError(33);
                  for(int j=0;j<vxBins[k].size()-1;j++)
                    {
                      Float_t area = drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j];
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinContent(j+1, density * area / (0.3*0.3));
                      (hSignalX.at(k))[l*nPtBins+i]->SetBinError(j+1, densityError * area / (0.3*0.3));
                    }
                }
            }
          for(int j=0;j<vxBins[k].size()-1;j++) 
            {
              (hSignalXnorm.at(k))[l*nPtBins+i]->SetBinContent(j+1, (hSignalX.at(k))[l*nPtBins+i]->GetBinContent(j+1) / (hSignalXnorm.at(k))[l*nPtBins+i]->GetBinWidth(j+1));
              (hSignalXnorm.at(k))[l*nPtBins+i]->SetBinError(j+1, (hSignalX.at(k))[l*nPtBins+i]->GetBinError(j+1) / (hSignalXnorm.at(k))[l*nPtBins+i]->GetBinWidth(j+1));
            }
        }
      // if(isMC && signalMC) (hSignalXsub.at(k))[i] = (TH1F*)(hSignalXnorm.at(k))[0*nPtBins+i]->Clone((hSignalXsub.at(k))[i]->GetName());
      // else (hSignalXsub.at(k))[i]->Add((hSignalXnorm.at(k))[0*nPtBins+i], (hSignalXnorm.at(k))[1*nPtBins+i], 1, -1);
      (hSignalXsub.at(k))[i]->Add((hSignalXnorm.at(k))[0*nPtBins+i], (hSignalXnorm.at(k))[1*nPtBins+i], 1, -1);
      (hSignalXsub.at(k))[i]->Scale(1./(hSignalXsub.at(k))[i]->Integral("width"));
    }
  delete dft;

  if(isrecoD)
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
      leg->Draw();
      c->SaveAs(Form("ploteff/ceff_%s_%s.pdf",tname[k].Data(),outputname.Data()));
      delete leg;
      delete hempty;
      delete c;
    }

  TFile* outf = new TFile(Form("rootfiles/xsec_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists(Form("usehist %s", isrecoD?"recoD":""))) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==11)
    {
      djtana_usehist(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]),
                     atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]),
                     atoi(argv[10]));
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

