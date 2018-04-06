#include "djtana.h"

void djtana_savetpl(TString inputname, TString outputname, 
                    TString collisionsyst, Int_t isMC, Int_t irecogen,
                    Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax, 
                    Int_t jescale=0, Int_t gensmearpt=0, Int_t gensmearphi=0, 
                    Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst, Int_t irecogen, Int_t gensmearpt, Int_t gensmearphi);
  if(arguerr(collisionsyst, irecogen, gensmearpt, gensmearphi)) return;

  if(createhists("savetpl")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  djtcorr::setParameters(ispp);
  djtweight::init();

  djet djt(inputname, ispp, 1);
  // djt.setjetcut(jetptmin, jetetamin, jetetamax);
  djt.setGcut(cutval_Dy);
  initcutval(collisionsyst);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  int ncountjet = 0;
  int NSMEAR=15;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   djtana_savetpl("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(20)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //

      if(djt.pthat < 30) continue;

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) {std::cout<<"wrong ibincent"<<std::endl; return;}
      // Float_t cweight = ispp?1.:djtweight::getcentweight(djt.hiBin);
      Float_t cweight = 1.;
      Float_t evtweight = djt.pthatweight*cweight;
      
      for(int jj=0;jj<*(djt.anjet[irecogen]);jj++)
        {
          if((**djt.asubid[irecogen])[jj]!=0) continue;

          Float_t jetpt = (**djt.ajetpt[irecogen])[jj];
          Float_t jetphi = (**djt.ajetphi[irecogen])[jj];
          Float_t jeteta = (**djt.ajeteta[irecogen])[jj];
          Float_t jetnpdfpart = 0;
          if(jescale==2) jetnpdfpart = (*djt.jetnpfpart_akpu3pf)[jj];

          // JEC
          if(djt.ajetopt[irecogen]=="reco" && jescale)
            if(djtcorr::ptCorr(jescale, jetpt, jetnpdfpart, ibincent)) return;

          // smear pt
          std::vector<float>* vjetpt = new std::vector<float>();
          if(djt.ajetopt[irecogen]=="gen" && gensmearpt)
            {
              for(int n=0;n<NSMEAR;n++)
                {
                  float sjetpt = jetpt;
                  if(djtcorr::ptSmear(sjetpt, ibincent)) return;
                  vjetpt->push_back(sjetpt);
                }
            }
          else
            { vjetpt->push_back(jetpt); }

          // smear angle
          std::vector<float>* vjetphi = new std::vector<float>();
          std::vector<float>* vjeteta = new std::vector<float>();
          if(djt.ajetopt[irecogen]=="gen" && gensmearphi)
            {
              for(int n=0;n<NSMEAR;n++)
                {
                  float sjetphi = jetphi, sjeteta = jeteta;
                  if(djtcorr::angleSmear(gensmearphi, sjeteta, sjetphi, vjetpt->at(n), ibincent)) return;
                  vjetphi->push_back(sjetphi);
                  vjeteta->push_back(sjeteta);
                }
            }
          else
            {
              vjetphi->push_back(jetphi);
              vjeteta->push_back(jeteta);
            }

          Bool_t issmear = djt.ajetopt[irecogen]=="gen" && (gensmearpt || gensmearphi);

          // reco
          for(int jd=0;jd<*(djt.anD[irecogen]);jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[irecogen])[jd]);
              if(ibinpt<0) continue;
              Int_t ibinselpt = xjjc::findibin(&ptselBins, (**djt.aDpt[irecogen])[jd]);

              if((**djt.aDcollisionId[irecogen])[jd] != 0) continue;

              Float_t Dgenpt = (**djt.aDgenpt[irecogen])[jd];
              Float_t weightDgen = djtweight::getDptweight(Dgenpt, ispp);

              int nsjet = vjetpt->size();
              if(nsjet!=vjeteta->size() || nsjet!=vjetphi->size() || nsjet!=(issmear?NSMEAR:1)) { std::cout<<"error: wrong number of jet in vector."<<std::endl; return; }
              for(int s=0;s<nsjet;s++)
                {
                  if(vjetpt->at(s) < jetptmin || vjetpt->at(s) > jetptmax) continue;
                  if(!(TMath::Abs(vjeteta->at(s)) > jetetamin && TMath::Abs(vjeteta->at(s)) < jetetamax)) continue;

                  Float_t deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[irecogen])[jd] - vjetphi->at(s)));
                  Float_t deltaeta = (**djt.aDeta[irecogen])[jd] - vjeteta->at(s);
                  Float_t deltaetaref = (**djt.aDeta[irecogen])[jd] + vjeteta->at(s);
                  Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                              (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
                  for(int l=0;l<nRefBins;l++)
                    {
                      Int_t ibindr = xjjc::findibin(&drBins, deltaR[l]);
                      if(ibindr<0) continue;

                      Int_t result_initcutval = initcutval_bindep(collisionsyst, ibinselpt, ibindr);
                      if(result_initcutval) return;
                      djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
                      djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);
                      Int_t djtDsel = djt.isDselected(jd, djt.aDopt[irecogen]);
                      if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                      if(!djtDsel) continue;
                      if((*djt.Dgen)[jd]==23333)
                        {
                          ahHistoRMassSignal[l][ibinpt][ibindr]->Fill((*djt.Dmass)[jd], 1. / nsjet);
                          ahNumREfficiency[l][ibinpt]->Fill(deltaR[l], evtweight*weightDgen / nsjet);
                          if(deltaR[l] < 0.3 && l)
                            {
                              ahHistoRMassSignalRef[ibinpt]->Fill((*djt.Dmass)[jd], 1. / nsjet);
                              ahNumREfficiencyRef[ibinpt]->Fill(deltaR[l], evtweight*weightDgen / nsjet);                              
                            }
                        }
                      if((*djt.Dgen)[jd]==23344) 
                        {
                          ahHistoRMassSwapped[l][ibinpt][ibindr]->Fill((*djt.Dmass)[jd], 1. / nsjet);
                          if(deltaR[l] < 0.3 && l)
                            ahHistoRMassSwappedRef[ibinpt]->Fill((*djt.Dmass)[jd], 1. / nsjet);
                        }
                    }
                }
            }

          // gen
          for(int jd=0;jd<djt.Gsize;jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (*djt.Gpt)[jd]);
              if(ibinpt<0) continue;

              if((*djt.GcollisionId)[jd] != 0) continue;

              Float_t Gpt = (*djt.Gpt)[jd];
              Float_t weightG = djtweight::getDptweight(Gpt, ispp);

              int nsjet = vjetpt->size();
              if(nsjet!=vjeteta->size() || nsjet!=vjetphi->size() || nsjet!=(issmear?NSMEAR:1)) { std::cout<<"error: wrong number of jet in vector."<<std::endl; return; }
              for(int s=0;s<nsjet;s++)
                {
                  if(vjetpt->at(s) < jetptmin || vjetpt->at(s) > jetptmax) continue;
                  if(!(TMath::Abs(vjeteta->at(s)) > jetetamin && TMath::Abs(vjeteta->at(s)) < jetetamax)) continue;

                  Float_t deltaphi = TMath::ACos(TMath::Cos((*djt.Gphi)[jd] - vjetphi->at(s)));
                  Float_t deltaeta = (*djt.Geta)[jd] - vjeteta->at(s);
                  Float_t deltaetaref = (*djt.Geta)[jd] + vjeteta->at(s);
                  Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                              (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
                  for(int l=0;l<nRefBins;l++)
                    {
                      Int_t djtDsel = djt.isDselected(jd, "gen");
                      if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                      if(!djtDsel) continue;

                      ahDenREfficiency[l][ibinpt]->Fill(deltaR[l], evtweight*weightG / nsjet);
                      if(deltaR[l] < 0.3 && l)
                        ahDenREfficiencyRef[ibinpt]->Fill(deltaR[l], evtweight*weightG / nsjet);
                      if(djtDsel && 
                         TMath::Abs((*djt.Gtk1eta)[jd]) < 2.0 && TMath::Abs((*djt.Gtk2eta)[jd]) < 2.0 && (*djt.Gtk1pt)[jd] > 2.0 && (*djt.Gtk2pt)[jd] > 2.0)
                        {
                          ahAccREfficiency[l][ibinpt]->Fill(deltaR[l], evtweight*weightG / nsjet);
                          if(deltaR[l] < 0.3 && l)
                            ahAccREfficiencyRef[ibinpt]->Fill(deltaR[l], evtweight*weightG / nsjet);
                        }
                    }
                }
            }
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   djtana_savetpl("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(30)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<std::endl;
  std::cout<<std::endl;

  for(int i=0;i<nPtBins;i++)
    {
      for(int l=0;l<nRefBins;l++)
        {
          ahREfficiency[l][i]->Divide(ahNumREfficiency[l][i], ahDenREfficiency[l][i]);
          ahREff[l][i]->Divide(ahNumREfficiency[l][i], ahAccREfficiency[l][i]);
          ahRAcceptance[l][i]->Divide(ahAccREfficiency[l][i], ahDenREfficiency[l][i]);
        }
      ahREfficiencyRef[i]->Divide(ahNumREfficiencyRef[i], ahDenREfficiencyRef[i]);
      ahREffRef[i]->Divide(ahNumREfficiencyRef[i], ahAccREfficiencyRef[i]);
      ahRAcceptanceRef[i]->Divide(ahAccREfficiencyRef[i], ahDenREfficiencyRef[i]);
    }

  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savetpl")) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==14)
    {
      djtana_savetpl(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]),
                     atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]),
                     atoi(argv[10]), atoi(argv[11]), atoi(argv[12]), 
                     atoi(argv[13]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_savetpl()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t irecogen, Int_t gensmearpt, Int_t gensmearphi)
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
  if(irecogen==1 || irecogen==3)
    {
      std::cout<<"\"irecogen\" indicates genD, skip djtana_savetpl()."<<std::endl;
      return 2;
    }
  if(gensmearpt != gensmearphi)
    {
      std::cout<<"error: smear gen pt and angle together"<<std::endl;
      return 2;
    }
  return 0;
}
