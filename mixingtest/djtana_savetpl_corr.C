#include "djtana.h"

void djtana_savetpl_corr(TString inputname, TString outputname, 
                    TString collisionsyst, Int_t isMC, Int_t irecogen,
                    Float_t jetptmin, Float_t jetetamin, Float_t jetetamax, Int_t useMB, Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst, Int_t irecogen);
  if(arguerr(collisionsyst, irecogen)) return;

  if(createhists("savetpl")) return;
  Int_t ispp = collisionsyst=="pp"?1:0;

  djet djt(inputname, ispp, isMC);
  djt.setjetcut(jetptmin, jetetamin, jetetamax);
  djt.setGcut(cutval_Dy);
  initcutval(collisionsyst);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  int ncountjet = 0;
  int ptreject = 0;
  int ibinreject = 0;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   djtana_savetpl_corr("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(20)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<"\r"<<std::flush<<std::endl;
      //
      djt.fChain->GetEntry(i);
      //
      // to add event selection ...
      int njets;
      if(!useMB) njets = *(djt.anjet[irecogen]);
      else njets = *(djt.MBanjet[irecogen]);
      std::cout << i << " " << njets << std::endl;
      for(int jj=0;jj<njets;jj++)
        {
          int djtjetsel = djt.isjetselected(jj, djt.ajetopt[irecogen]);
          if(djtjetsel < 0) return;
          if(!djtjetsel) continue;
          //if(!useMB && ((**djt.ajetpt[irecogen])[jj]<jetptmin || fabs((**djt.ajeteta[irecogen])[jj])>2.0)) {ptreject++; continue;}
          //if(useMB && ((**djt.MBajetpt[irecogen])[jj]<jetptmin || fabs((**djt.MBajeteta[irecogen])[jj])>2.0)) {ptreject++; continue;}
          ncountjet++;
          // reco
          if(!useMB)
          {
            hJetPhi->Fill((**djt.ajetphi[irecogen])[jj]);
            hJetEta->Fill((**djt.ajeteta[irecogen])[jj]);
          }
          else
          {
            hJetPhi->Fill((**djt.MBajetphi[irecogen])[jj]);
            hJetEta->Fill((**djt.MBajeteta[irecogen])[jj]);
          }
          std::cout << "jetetaphi" << std::endl;
          for(int jd=0;jd<*(djt.anD[irecogen]);jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[irecogen])[jd]);
              if(ibinpt<0) {if(jj==0) ibinreject++; continue;}   
                         
              // to add pt-dependent event selection ...
              Float_t deltaphi;
              if(!useMB) deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[irecogen])[jd] - (**djt.ajetphi[irecogen])[jj]));
              else deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[irecogen])[jd] - (**djt.MBajetphi[irecogen])[jj]));
              if(deltaphi>TMath::Pi() || deltaphi<-TMath::Pi()) std::cout << "bad deltaphi, jet " << jj << " D " << jd << " value " << deltaphi << std::endl;
              Float_t deltaeta = (**djt.aDeta[irecogen])[jd] - (**djt.ajeteta[irecogen])[jj];
              Float_t deltaetaref = (**djt.aDeta[irecogen])[jd] + (**djt.ajeteta[irecogen])[jj];
              Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                          (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
              Float_t zvariable = (**djt.aDpt[irecogen])[jd]/(**djt.ajetpt[irecogen])[jj];

              //Int_t result_initcutval = initcutval_bindep_flat(collisionsyst,ibinpt);
              //if(result_initcutval) return;
              //djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
              //djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);                  
              //Int_t djtDsel = djt.isDselected(jd, djt.aDopt[irecogen]);
              //if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
              //if(!djtDsel) continue;
              

              if((irecogen==0 || irecogen==2) && jj==0)
              {
                hDphivsDtrk1hit[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk1PixelHit)[jd]);
                hDphivsDtrk2hit[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk2PixelHit)[jd]);
                hDphivsDtrk1algo[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk1Algo)[jd]);
                hDphivsDtrk2algo[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk2Algo)[jd]);
              }
              if((**djt.aDpt[irecogen])[jd]>4.0 && fabs((**djt.aDeta[irecogen])[jd])<2.0)
              {
                if(jj==0) 
                {
                  hDPhi[ibinpt]->Fill((**djt.aDphi[irecogen])[jd]);
                  hDEta[ibinpt]->Fill((**djt.aDeta[irecogen])[jd]);
                }
                if(fabs((**djt.ajeteta[irecogen])[jj]) < 2.0)
                {
                  hDdelPhi[ibinpt]->Fill(deltaphi);
                  hDdelEta[ibinpt]->Fill(deltaeta);
                  hCorr[ibinpt]->Fill(deltaeta,deltaphi);
                }
              }
              
              /*
              for(int l=0;l<nRefBins;l++)
                {
                  Int_t ibindr = xjjc::findibin(&drBins, deltaR[l]);
                  if(ibindr<0) continue;                  
                  Int_t result_initcutval = initcutval_bindep(collisionsyst, ibinpt, ibindr);
                  if(result_initcutval) return;
                  djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
                  djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);                  
                  Int_t djtDsel = djt.isDselected(jd, djt.aDopt[irecogen]);
                  if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                  if(!djtDsel) continue;
                  if((*djt.Dgen)[jd]==23333) 
                    {
                      ahHistoRMassSignal[l][ibinpt][ibindr]->Fill((*djt.Dmass)[jd]);
                      ahNumREfficiency[l][ibinpt]->Fill(deltaR[l]);
                    }
                  if((*djt.Dgen)[jd]==23344) ahHistoRMassSwapped[l][ibinpt][ibindr]->Fill((*djt.Dmass)[jd]);

                  if(deltaR[l]>0.3) continue; // ... to discuss
                  Int_t ibinz = xjjc::findibin(&zBins, zvariable);
                  if(ibinz<0) continue;
                  if((*djt.Dgen)[jd]==23333) 
                    {
                      ahHistoZMassSignal[l][ibinpt][ibinz]->Fill((*djt.Dmass)[jd]);
                      ahNumZEfficiency[l][ibinpt]->Fill(zvariable);
                    }
                  if((*djt.Dgen)[jd]==23344) ahHistoZMassSwapped[l][ibinpt][ibinz]->Fill((*djt.Dmass)[jd]);
                }
                */
            }
          // gen
          /*
          for(int jd=0;jd<*(djt.anD[irecogen+1]);jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[irecogen+1])[jd]);
              if(ibinpt<0) continue;              
              
              // to add pt-dependent event selection ...
              
              Float_t deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[irecogen+1])[jd] - (**djt.ajetphi[irecogen+1])[jj]));
              Float_t deltaeta = (**djt.aDeta[irecogen+1])[jd] - (**djt.ajeteta[irecogen+1])[jj];
              Float_t deltaetaref = (**djt.aDeta[irecogen+1])[jd] + (**djt.ajeteta[irecogen+1])[jj];
              Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                          (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
              Float_t zvariable = (**djt.aDpt[irecogen+1])[jd]/(**djt.ajetpt[irecogen+1])[jj];
              
              for(int l=0;l<nRefBins;l++)
                {
                  Int_t djtDsel = djt.isDselected(jd, djt.aDopt[irecogen+1]);
                  if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                  if(!djtDsel) continue;
                  ahDenREfficiency[l][ibinpt]->Fill(deltaR[l]);
                  
                  if(deltaR[l]>0.3) continue; // ... to discuss
                  ahDenZEfficiency[l][ibinpt]->Fill(zvariable);
                }
            }
            */
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   djtana_savetpl_corr("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(30)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<std::endl;
  std::cout<<std::endl;

  hNjets->SetBinContent(1, ncountjet);
  /*for(int l=0;l<nRefBins;l++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          ahNumREfficiency[l][i]->Sumw2();
          ahDenREfficiency[l][i]->Sumw2();
          ahNumZEfficiency[l][i]->Sumw2();
          ahDenZEfficiency[l][i]->Sumw2();
          ahREfficiency[l][i]->Divide(ahNumREfficiency[l][i], ahDenREfficiency[l][i]);
          ahZEfficiency[l][i]->Divide(ahNumZEfficiency[l][i], ahDenZEfficiency[l][i]);
        }
    }
  */

  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savetpl")) return;
  outf->Write();
  outf->Close();
  std::cout << inputname << " " << irecogen << " " << "ptreject " << ptreject << std::endl;
  std::cout << inputname << " " << irecogen << " " << "ibinreject " << ibinreject << std::endl;
}

int main(int argc, char* argv[])
{
  if(argc==11)
    {
      djtana_savetpl_corr(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atoi(argv[9]), atoi(argv[10]));
      return 0;
    }
  if(argc==10)
    {
      djtana_savetpl_corr(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atoi(argv[9]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_savetpl_corr()"<<std::endl;
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
  if(irecogen<0 || irecogen>3)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"irecogen\""<<std::endl;
      return 1;
    }
/*
  if(irecogen==1 || irecogen==3)
    {
      std::cout<<"\"irecogen\" indicates genD, skip djtana_savetpl_corr()."<<std::endl;
      return 2;
    }
*/
  return 0;
}
