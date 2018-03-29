#include "djtana.h"
#include "TVector.h"

void djtana_savetpl_corr(TString inputname, TString outputname, 
                    TString collisionsyst, Int_t isMC, Int_t irecogen,
                    Float_t jetptmin, Float_t jetetamin, Float_t jetetamax, Int_t useMB, Int_t maxevt=-1)
{
  Int_t irecoref = irecogen;
  irecogen = 1;
  int arguerr(TString collisionsyst, Int_t irecogen);
  if(arguerr(collisionsyst, irecogen)) return;

  if(createhists("savetpl")) return;
  Int_t ispp = collisionsyst=="pp"?1:0;

  setnCentBins(ispp);
  djtcorr::setParameters(ispp);

  djet djt(inputname, ispp, isMC);
  djt.setjetcut(jetptmin, jetetamin, jetetamax);
  djt.setGcut(cutval_Dy);
  initcutval(collisionsyst);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  int ncountjet = 0;
  int ptreject = 0;
  int ibinreject = 0;
  TVector norm(nPtBins);
  for(int i=0;i<nPtBins;i++)norm[i]=0;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   djtana_savetpl_corr("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(20)<<Form("%sD_%sjet)", djt.aDopt[useMB][irecogen].Data(), djt.ajetopt[useMB][irecogen].Data())<<"\r"<<std::flush<<std::endl;
      //
      djt.fChain->GetEntry(i);
      for(int i=0;i<nPtBins;i++) norm[i]++;
      //
      // to add event selection ...
      int njets = *(djt.anjet[useMB][irecogen]);
      Int_t ibincent = ispp?0:xjjc::findibin(&centBins,(float)djt.hiBin/2);
      for(int jj=0;jj<njets;jj++)
        {
          //int djtjetsel;
          //if(!useMB) djtjetsel = djt.isjetselected(jj, djt.ajetopt[irecogen]);
          //if(useMB) djtjetsel = djt.isjetselected(jj,"m");
          //if(djtjetsel < 0) {std::cout << "bad djtjetsel " << djtjetsel << std::endl; return;}
          //if(!djtjetsel) continue;
          float jetpt = (**djt.ajetpt[useMB][irecogen])[jj];
          if(djtcorr::ptCorr(1.,jetpt,0.,ibincent)) continue;
          if(jetpt<jetptmin || fabs((**djt.ajeteta[useMB][irecogen])[jj])<jetetamin || fabs((**djt.ajeteta[useMB][irecogen])[jj])>jetetamax) continue;
          if(irecoref==3 && (**djt.asubid[useMB][irecogen])[jj]!=0) continue;
          //if(irecoref==4 && (**djt.asubid[irecogen])[jj]==0) continue;
          ncountjet++;
          // reco
          hJetPhi->Fill((**djt.ajetphi[useMB][irecogen])[jj]);
          hJetEta->Fill((**djt.ajeteta[useMB][irecogen])[jj]);
          for(int jd=0;jd<(*djt.anD[useMB][irecogen]);jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[useMB][irecogen])[jd]);
              if(ibinpt<0) {if(jj==0) ibinreject++; continue;} 
                         
              // to add pt-dependent event selection ...
              Float_t deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[useMB][irecogen])[jd] - (**djt.ajetphi[useMB][irecogen])[jj]));
              if(deltaphi>TMath::Pi() || deltaphi<-TMath::Pi()) std::cout << "bad deltaphi, jet " << jj << " D " << jd << " value " << deltaphi << std::endl;
              Float_t deltaeta = (**djt.aDeta[useMB][irecogen])[jd] - (**djt.ajeteta[useMB][irecogen])[jj];
              Float_t deltaetaref = (**djt.aDeta[useMB][irecogen])[jd] + (**djt.ajeteta[useMB][irecogen])[jj];
              Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                          (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
              Float_t zvariable = (**djt.aDpt[useMB][irecogen])[jd]/(**djt.ajetpt[useMB][irecogen])[jj];

              Int_t result_initcutval = initcutval_bindep_flat(collisionsyst,ibinpt);
              if(result_initcutval) return;
              djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
              djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);                  
              Int_t djtDsel = djt.isDselected(jd, djt.aDopt[useMB][irecogen]);
              if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
              if(!djtDsel) continue;
              //if(irecoref==3 && (*djt.GcollisionId)[jd]!=0) continue;

              //if((irecogen==0 || irecogen==2) && jj==0)
              //{
                //hDphivsDtrk1hit[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk1PixelHit)[jd]);
                //hDphivsDtrk2hit[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk2PixelHit)[jd]);
                //hDphivsDtrk1algo[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk1Algo)[jd]);
                //hDphivsDtrk2algo[ibinpt]->Fill((**djt.aDphi[irecogen])[jd],(*djt.Dtrk2Algo)[jd]);
              //}
              //if((**djt.aDpt[irecogen])[jd]>2.0 && fabs((**djt.aDeta[irecogen])[jd])<1.6)
              //{
                //if((!useMB && fabs((**djt.ajeteta[irecogen])[jj]) < 1.6) || (useMB && fabs((**djt.MBajeteta[irecogen])[jj])<1.6))
                //{
                  hDdelPhi[ibinpt]->Fill(deltaphi);
                  hDdelEta[ibinpt]->Fill(deltaeta);
                  hCorr[ibinpt]->Fill(deltaeta,deltaphi);
                //}
              //}
              
              
              for(int l=0;l<nRefBins;l++)
                {
                  Int_t ibindr = xjjc::findibin(&drBins, deltaR[l]);
                  if(ibindr<0) continue;                  
                  Int_t result_initcutval = initcutval_bindep(collisionsyst, ibinpt, ibindr);
                  if(result_initcutval) return;
                  djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
                  djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);                  
                  Int_t djtDsel = djt.isDselected(jd, djt.aDopt[useMB][irecogen]);
                  if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                  if(!djtDsel) continue;
                  ahNumREfficiency[l][ibinpt]->Fill(deltaR[l],1./ahNumREfficiency[l][ibinpt]->GetBinWidth(ibindr+1));
                }
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
        for(int jd=0;jd<(*djt.anD[useMB][irecogen]);jd++)
        {
          Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[useMB][irecogen])[jd]);
          if(ibinpt<0) {ibinreject++; continue;}
          Int_t result_initcutval = initcutval_bindep_flat(collisionsyst,ibinpt);
          if(result_initcutval) return;
          djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
          djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);                  
          Int_t djtDsel = djt.isDselected(jd, djt.aDopt[useMB][irecogen]);
          if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
          if(!djtDsel) continue;
          //if(irecoref==3 && (*djt.GcollisionId)[jd]!=0) continue;
          hDPhi[ibinpt]->Fill((**djt.aDphi[useMB][irecogen])[jd]);
          hDEta[ibinpt]->Fill((**djt.aDeta[useMB][irecogen])[jd]);  
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   djtana_savetpl_corr("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(30)<<Form("%sD_%sjet)", djt.aDopt[useMB][irecogen].Data(), djt.ajetopt[useMB][irecogen].Data())<<std::endl;
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
  norm.Write("nD");
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
