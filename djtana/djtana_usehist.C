#include "djtana.h"

void djtana_usehist(TString inputhistname, TString inputtplname, TString outputname, 
                    TString collisionsyst, Int_t irecogen,
                    Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                    Int_t signalMC, Int_t corrReso, Int_t corrNclo)
{
  int arguerr(TString collisionsyst, Int_t irecogen);
  if(arguerr(collisionsyst, irecogen)) return;

  xjjroot::setgstyle();

  if(createhists("usehist")) return;
  Bool_t isrecoD = irecogen%2==0;
  Bool_t ispp = collisionsyst=="pp";
  Bool_t isMC = inputhistname.Contains("MC");
  djtcorr::setParameters(ispp);

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

  xjjroot::dfitter* dft = new xjjroot::dfitter("S");
  
  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]<999?Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()):Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str());
      // eta ref
      for(int l=0;l<nRefBins;l++)
        {
          if(isrecoD)
            {
              if(!l) // regular cone
                {
                  TCanvas* c = new TCanvas("c", "", 600*nDrBins, 600);
                  c->Divide(nDrBins, 1);
                  TCanvas* cpull = new TCanvas("cpull", "", 600*nDrBins, 700);
                  cpull->Divide(nDrBins, 1);
                  std::vector<TPad*> pFit(nDrBins);
                  std::vector<TPad*> pPull(nDrBins);
                  for(int j=0;j<nDrBins;j++)
                    {
                      cpull->cd(j+1);
                      pFit[j] = new TPad(Form("pFit%d",j),"",0,0.3,1,1);
                      pFit[j]->SetBottomMargin(0);
                      pFit[j]->Draw();
                      cpull->cd(j+1);
                      pPull[j] = new TPad(Form("pPull%d",j),"",0,0,1,0.3);
                      pPull[j]->SetTopMargin(0);
                      pPull[j]->SetBottomMargin(0.3);
                      pPull[j]->Draw();
                    }
                  for(int j=0;j<nDrBins;j++)
                    {
                      c->cd(j+1);
                      vectex.push_back(texpt);
                      vectex.push_back(Form("%s < %s < %s",xjjc::number_remove_zero(drBins[j]).c_str(),"r",xjjc::number_remove_zero(drBins[j+1]).c_str()));
                      dft->fit(ahHistoRMass[l][i][j], ahHistoRMassSignal[i][j], ahHistoRMassSwapped[i][j], collisionsyst, vectex);
                      ahSignalRraw[l][i]->SetBinContent(j+1, dft->GetY());
                      ahSignalRraw[l][i]->SetBinError(j+1, dft->GetY()>0?dft->GetYE():0);
                      cpull->cd(j+1);
                      pFit[j]->cd();
                      if(dft->drawfit(collisionsyst, vectex)) return;
                      cpull->cd(j+1);
                      pPull[j]->cd();
                      if(dft->drawpull()) return;
                      vectex.pop_back();
                      vectex.pop_back();
                    }
                  c->SaveAs(Form("plotfits/cmass_%s_%s_pt_%d_%s.pdf",outputname.Data(),tRef[l].Data(),i,"dr"));
                  cpull->SaveAs(Form("plotfitspull/cmasspull_%s_%s_pt_%d_%s.pdf",outputname.Data(),tRef[l].Data(),i,"dr"));
                  for(int j=0;j<nDrBins;j++) { delete pFit[j]; delete pPull[j]; }
                  delete cpull;
                  delete c;
                }
              else // reflected cone
                {
                  TCanvas* c = new TCanvas("c", "", 600, 600);
                  vectex.push_back(texpt);
                  vectex.push_back(Form("0 < %s < 0.3","r"));
                  dft->fit(ahHistoRMassRef[i], ahHistoRMassSignalRef[i], ahHistoRMassSwappedRef[i], collisionsyst, vectex);
                  vectex.pop_back();
                  vectex.pop_back();
                  c->SaveAs(Form("plotfits/cmass_%s_%s_pt_%d_%s.pdf",outputname.Data(),tRef[l].Data(),i,"dr"));
                  ahSignalRrawRef[i]->SetBinContent(1, dft->GetY());
                  ahSignalRrawRef[i]->SetBinError(1, dft->GetY()>0?dft->GetYE():0);
                  // ahSignalRRef[i]->SetBinContent(1, ahSignalRrawRef[i]->GetBinContent(1));
                  // ahSignalRRef[i]->SetBinError(1, ahSignalRrawRef[i]->GetBinError(1));
                  // ahSignalRRef[i]->Divide(ahREfficiencyRef[i]);
                  Double_t density = ahSignalRrawRef[i]->GetBinContent(1);
                  Double_t densityError = ahSignalRrawRef[i]->GetBinError(1);
                  Double_t dennorm = 0;
                  for(int j=0;j<nDrBins-1;j++) { dennorm += (drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j])*ahREfficiency[0][i]->GetBinContent(j+1); }
                  for(int j=0;j<nDrBins;j++) 
                    {
                      Float_t area = (drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j])*ahREfficiency[0][i]->GetBinContent(j+1);
                      ahSignalRraw[l][i]->SetBinContent(j+1, density * area / dennorm);
                      ahSignalRraw[l][i]->SetBinError(j+1, densityError * area / dennorm);
                    }
                  delete c;
                }
              for(int j=0;j<nDrBins;j++)
                {
                  ahSignalR[l][i]->SetBinContent(j+1, ahSignalRraw[l][i]->GetBinContent(j+1));
                  ahSignalR[l][i]->SetBinError(j+1, ahSignalRraw[l][i]->GetBinError(j+1));
                }
              ahSignalR[l][i]->Divide(ahREfficiency[0][i]);
            }
          else
            {
              if(!l)
                {
                  for(int j=0;j<nDrBins;j++) 
                    {
                      ahSignalR[l][i]->SetBinContent(j+1, ahHistoRMass[l][i][j]->GetBinContent(33));
                      ahSignalR[l][i]->SetBinError(j+1, ahHistoRMass[l][i][j]->GetBinError(33));
                    }
                }
              else
                {
                  Double_t density = ahHistoRMassRef[i]->GetBinContent(33);
                  Double_t densityError = ahHistoRMassRef[i]->GetBinError(33);
                  for(int j=0;j<nDrBins;j++)
                    {
                      Float_t area = drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j];
                      ahSignalR[l][i]->SetBinContent(j+1, density * area / (0.3*0.3));
                      ahSignalR[l][i]->SetBinError(j+1, densityError * area / (0.3*0.3));
                    }
                }
            }
          for(int j=0;j<nDrBins;j++) 
            {
              ahSignalRnorm[l][i]->SetBinContent(j+1, ahSignalR[l][i]->GetBinContent(j+1) / ahSignalRnorm[l][i]->GetBinWidth(j+1));
              ahSignalRnorm[l][i]->SetBinError(j+1, ahSignalR[l][i]->GetBinError(j+1) / ahSignalRnorm[l][i]->GetBinWidth(j+1));
            }
        }

      // mixing event
      if(isrecoD)
        {
          TCanvas* c = new TCanvas("c", "", 600*nMeBins, 600);
          c->Divide(nMeBins, 1);
          TCanvas* cpull = new TCanvas("cpull", "", 600*nMeBins, 700);
          cpull->Divide(nMeBins, 1);
          std::vector<TPad*> pFit(nMeBins);
          std::vector<TPad*> pPull(nMeBins);
          for(int l=0;l<nMeBins;l++)
            {
              cpull->cd(l+1);
              pFit[l] = new TPad(Form("pFit%d",l),"",0,0.3,1,1);
              pFit[l]->SetBottomMargin(0);
              pFit[l]->Draw();
              cpull->cd(l+1);
              pPull[l] = new TPad(Form("pPull%d",l),"",0,0,1,0.3);
              pPull[l]->SetTopMargin(0);
              pPull[l]->SetBottomMargin(0.3);
              pPull[l]->Draw();
            }
          for(int l=0;l<nMeBins;l++)
            {
              c->cd(l+1);
              vectex.push_back(texpt);
              vectex.push_back(Form("0 < %s < 0.5","r"));
              dft->fit(ahHistoRMassMe[l][i], ahHistoRMassSignalMe[i], ahHistoRMassSwappedMe[i], collisionsyst, vectex);
              cpull->cd(l+1);
              pFit[l]->cd();
              if(dft->drawfit(collisionsyst, vectex)) return;
              cpull->cd(l+1);
              pPull[l]->cd();
              if(dft->drawpull()) return;
              vectex.pop_back();
              vectex.pop_back();
              Double_t density = dft->GetY();
              Double_t densityError = dft->GetY()>0?dft->GetYE():0;
              Double_t dennorm = 0;
              for(int j=0;j<nDrBins;j++) { dennorm += (drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j])*ahREfficiency[0][i]->GetBinContent(j+1); }
              for(int j=0;j<nDrBins;j++) 
                {
                  Float_t area = (drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j])*ahREfficiency[0][i]->GetBinContent(j+1);
                  ahSignalRrawMe[l][i]->SetBinContent(j+1, density * area / dennorm);
                  ahSignalRrawMe[l][i]->SetBinError(j+1, densityError * area / dennorm);
                  ahSignalRMe[l][i]->SetBinContent(j+1, density * area / dennorm);
                  ahSignalRMe[l][i]->SetBinError(j+1, densityError * area / dennorm);
                }
              ahSignalRMe[l][i]->Divide(ahREfficiency[0][i]);
            }
          c->SaveAs(Form("plotfits/cmass_%s_Me_pt_%d_%s.pdf",outputname.Data(),i,"dr"));
          cpull->SaveAs(Form("plotfitspull/cmasspull_%s_Me_pt_%d_%s.pdf",outputname.Data(),i,"dr"));
          for(int l=0;l<nMeBins;l++) { delete pFit[l]; delete pPull[l]; }
          delete cpull;
          delete c;
        }
      else
        {
          for(int l=0;l<nMeBins;l++)
            {
              Double_t density = ahHistoRMassMe[l][i]->GetBinContent(33);
              Double_t densityError = ahHistoRMassMe[l][i]->GetBinError(33);
              for(int j=0;j<nDrBins;j++)
                {
                  Float_t area = drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j];
                  ahSignalRMe[l][i]->SetBinContent(j+1, density * area / (0.3*0.3));
                  ahSignalRMe[l][i]->SetBinError(j+1, densityError * area / (0.3*0.3));
                }
            }
        }
      for(int l=0;l<nMeBins;l++)
        {
          for(int j=0;j<nDrBins;j++) 
            {
              ahSignalRnormMe[l][i]->SetBinContent(j+1, ahSignalRMe[l][i]->GetBinContent(j+1) / ahSignalRnormMe[l][i]->GetBinWidth(j+1));
              ahSignalRnormMe[l][i]->SetBinError(j+1, ahSignalRMe[l][i]->GetBinError(j+1) / ahSignalRnormMe[l][i]->GetBinWidth(j+1));
            }
        }

      // subtraction
      if(isMC && signalMC) 
        {
          ahSignalRsub[i] = (TH1F*)ahSignalRnorm[0][i]->Clone(ahSignalRsub[i]->GetName());
          ahSignalRsubMe[i] = (TH1F*)ahSignalRnorm[0][i]->Clone(ahSignalRsubMe[i]->GetName());
        }
      else 
        {
          ahSignalRsub[i]->Add(ahSignalRnorm[0][i], ahSignalRnorm[1][i], 1, -1);
          ahSignalRsubMe[i]->Add(ahSignalRnorm[0][i], ahSignalRnormMe[0][i], 1, -1);
          ahSignalRsubMe[i]->Add(ahSignalRnormMe[1][i], -1);
          ahSignalRsubMe[i]->Add(ahSignalRnormMe[2][i], 1);
        }
      ahSignalRsub[i]->Scale(1./ahSignalRsub[i]->Integral(1, 3, "width"));
      ahSignalRsubUncorr[i] = (TH1F*)ahSignalRsub[i]->Clone(ahSignalRsubUncorr[i]->GetName());
      ahSignalRsubMe[i]->Scale(1./ahSignalRsubMe[i]->Integral(1, 3, "width"));
      ahSignalRsubUncorrMe[i] = (TH1F*)ahSignalRsubMe[i]->Clone(ahSignalRsubUncorrMe[i]->GetName());
      for(int j=0;j<nDrBins;j++)
        {
          Float_t corrfactor = 1., corrfactorSg = 1;
          if(corrNclo)
            { if(djtcorr::getcorrFactor(corrfactor, i, j, jetptmin, jetptmax)) return; }
          if(corrReso)
            { if(djtcorr::getcorrFactorSg(corrfactorSg, i, j, jetptmin, jetptmax)) return; }
          ahSignalRsub[i]->SetBinContent(j+1, ahSignalRsubUncorr[i]->GetBinContent(j+1) / (corrfactor*corrfactorSg));
          ahSignalRsub[i]->SetBinError(j+1, ahSignalRsubUncorr[i]->GetBinError(j+1) / (corrfactor*corrfactorSg));
          ahSignalRsubMe[i]->SetBinContent(j+1, ahSignalRsubUncorrMe[i]->GetBinContent(j+1) / (corrfactor*corrfactorSg));
          ahSignalRsubMe[i]->SetBinError(j+1, ahSignalRsubUncorrMe[i]->GetBinError(j+1) / (corrfactor*corrfactorSg));
        }
    }

  delete dft;

  if(isrecoD) { verbose_stat(jetptmin, jetptmax); }

  if(isrecoD)
    {
      for(int i=0;i<nPtBins;i++)
        {
          TString texpythia = ispp?"PYTHIA":"PYTHIA + HYDJET";
          vectex.push_back(texpythia);
          TCanvas* c = new TCanvas("c", "", 600, 600);
          TCanvas* c3 = new TCanvas("c3", "", 1800, 600);
          c3->Divide(3, 1);
          TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#alpha x #epsilon_{reco} x #epsilon_{sel}"), 5, drBins[0], drBins[nDrBins], 10, 0, 1.);
          hempty->GetXaxis()->SetNdivisions(505);
          xjjroot::sethempty(hempty, 0, 0.5);
          TH2F* hemptyAcc = new TH2F("hemptyAcc", Form(";%s;%s","r","#alpha"), 5, drBins[0], drBins[nDrBins], 10, 0, 1.);
          hemptyAcc->GetXaxis()->SetNdivisions(505);
          xjjroot::sethempty(hemptyAcc, 0, 0.5);
          TH2F* hemptyEff = new TH2F("hemptyEff", Form(";%s;%s","r","#epsilon_{reco} x #epsilon_{sel}"), 5, drBins[0], drBins[nDrBins], 10, 0, 1.);
          hemptyEff->GetXaxis()->SetNdivisions(505);
          xjjroot::sethempty(hemptyEff, 0, 0.5);
          c->cd();
          hempty->Draw();
          c3->cd(1);
          hempty->Draw();
          c3->cd(2);
          hemptyAcc->Draw();
          c3->cd(3);
          hemptyEff->Draw();
          // TLegend* leg = new TLegend(0.53, 0.88-nPtBins*nRefBins*0.06, 0.85, 0.88);
          TLegend* leg = new TLegend(0.53, 0.88-0.06, 0.85, 0.88);
          xjjroot::setleg(leg);
          for(int l=0;l<nRefBins;l++)
            {
              xjjroot::setthgrstyle(ahREfficiency[l][i], amcolor[i], amstyle[l], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              xjjroot::setthgrstyle(ahREff[l][i], amcolor[i], amstyle[l], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              xjjroot::setthgrstyle(ahRAcceptance[l][i], amcolor[i], amstyle[l], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              TString tleg = l==1?"#eta reflection":(ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()));
              if(l) 
                {
                  xjjroot::setthgrstyle(ahREfficiencyRef[i], amcolor[i], amstyle[l], 1.2, amcolor[i], 1, 1, -1, -1, -1);
                  xjjroot::setthgrstyle(ahREffRef[i], amcolor[i], amstyle[l], 1.2, amcolor[i], 1, 1, -1, -1, -1);
                  xjjroot::setthgrstyle(ahRAcceptanceRef[i], amcolor[i], amstyle[l], 1.2, amcolor[i], 1, 1, -1, -1, -1);
                  continue;
                }
              leg->AddEntry(ahREfficiency[l][i], tleg.Data(), "p");
            }
          c->cd();
          for(int l=0;l<nRefBins;l++)
            {
              if(l) 
                {
                  ahREfficiencyRef[i]->Draw("pe same");
                  continue;
                }
              ahREfficiency[l][i]->Draw("pe same");
            }
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          leg->Draw();
          c->SaveAs(Form("ploteff/ceff_%s_%s_%d.pdf","dr",outputname.Data(),i));

          for(int l=0;l<nRefBins;l++)
            {
              if(l) continue;
              c3->cd(1);
              ahREfficiency[l][i]->Draw("pe same");
              ahREfficiencyRef[i]->Draw("pe same");              
              c3->cd(2);
              ahRAcceptance[l][i]->Draw("pe same");
              ahRAcceptanceRef[i]->Draw("pe same");
              c3->cd(3);
              ahREff[l][i]->Draw("pe same");
              ahREffRef[i]->Draw("pe same");
            }
          c3->cd(1);
          xjjroot::drawCMS(collisionsyst);
          texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          leg->Draw();
          c3->SaveAs(Form("ploteff/cacceff_%s_%s_%d.pdf","dr",outputname.Data(),i));

          delete leg;
          delete hemptyEff;
          delete hemptyAcc;
          delete hempty;
          delete c3;
          delete c;
          vectex.pop_back();
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
  if(argc==13)
    {
      djtana_usehist(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]),
                     atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]),
                     atoi(argv[10]), atoi(argv[11]), atoi(argv[12]));
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

