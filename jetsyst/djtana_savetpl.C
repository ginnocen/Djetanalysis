#include "djtana.h"

void djtana_savetpl(TString inputname, TString outputname, 
                    TString collisionsyst, Int_t isMC, Int_t irecogen,
                    Float_t jetptmin, Float_t jetetamin, Float_t jetetamax, 
                    Int_t jescale=0, Int_t gensmearpt=0, Int_t gensmearphi=0, Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst, Int_t irecogen);
  if(arguerr(collisionsyst, irecogen)) return;

  if(createhists("savetpl")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  setnCentBins(ispp);

  djet djt(inputname, ispp, 1);
  djt.setjetcut(jetptmin, jetetamin, jetetamax);
  djt.setGcut(cutval_Dy);
  initcutval(collisionsyst);

  TRandom3* pRandom3 = new TRandom3();

  std::vector<std::vector<Float_t>>* paramfScalePt = ispp?&paramfScalePt_pp:&paramfScalePt_PbPb;
  std::vector<std::vector<Float_t>>* paramfResoPt = ispp?&paramfResoPtCorr_pp:&paramfResoPtCorr_PbPb;
  std::vector<std::vector<Float_t>>* paramfScaleRecoPt = ispp?&paramfScaleRecoPt_pp:&paramfScaleRecoPt_PbPb;
  std::vector<std::vector<Float_t>>* paramfScalePtFfCorr = ispp?&paramfScalePtFfCorr_pp:&paramfScalePtFfCorr_PbPb;
  std::vector<std::vector<Float_t>>* paramRealfP0 = ispp?&paramRealfP0_pp:&paramRealfP0_PbPb;
  std::vector<std::vector<Float_t>>* paramRealfP1 = ispp?&paramRealfP1_pp:&paramRealfP1_PbPb;

  std::vector<std::vector<Float_t>>* paramfResoPhi = ispp?&paramfResoPhi_pp:&paramfResoPhi_PbPb;
  std::vector<std::vector<Float_t>>* paramfResoEta = ispp?&paramfResoEta_pp:&paramfResoEta_PbPb;
  std::vector<std::vector<Float_t>>* paramfResoDeltaPhi = ispp?&paramfResoDeltaPhi_pp:&paramfResoDeltaPhi_PbPb;
  std::vector<std::vector<Float_t>>* paramfResoDeltaEta = ispp?&paramfResoDeltaEta_pp:&paramfResoDeltaEta_PbPb;

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  int ncountjet = 0;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   djtana_savetpl("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(20)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //

      if(djt.pthat < 15) continue;

      // to add event selection ...

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) { std::cout<<"wrong ibincent"<<std::endl; return; }

      // Float_t cweight = 1.;
      Float_t cweight = ispp?1.:centweight[djt.hiBin];
      // Float_t evtweight = 1;
      Float_t evtweight = isMC?(djt.pthatweight*cweight):1.;
      
      for(int jj=0;jj<*(djt.anjet[irecogen]);jj++)
        {
          if((**djt.asubid[irecogen])[jj]!=0) continue;

          /*********************************/

          Float_t jetpt = (**djt.ajetpt[irecogen])[jj];
          Float_t jetphi = (**djt.ajetphi[irecogen])[jj];
          Float_t jeteta = (**djt.ajeteta[irecogen])[jj];

          // JEC
          Float_t jetrecomatgenpt = jetpt / (paramfScaleRecoPt->at(ibincent).at(0) + paramfScaleRecoPt->at(ibincent).at(1)/TMath::Sqrt(jetpt) + paramfScaleRecoPt->at(ibincent).at(2)/jetpt + paramfScaleRecoPt->at(ibincent).at(3)/(jetpt*jetpt));
          Float_t vScalePt = paramfScalePt->at(ibincent).at(0) + paramfScalePt->at(ibincent).at(1)/TMath::Sqrt(jetrecomatgenpt) + paramfScalePt->at(ibincent).at(2)/jetrecomatgenpt + paramfScalePt->at(ibincent).at(3)/(jetrecomatgenpt*jetrecomatgenpt);
          jetpt = jetpt / vScalePt;

          if(djt.ajetopt[irecogen]=="reco" && jescale)
            {
              Float_t vScalePtSyst = 1;
              if(jescale==1)
                vScalePtSyst = 1 + uncert_scale;
              else if(jescale==2)
                vScalePtSyst = 1 - uncert_scale;
              else { std::cout<<"invalid jescale"<<std::endl; return; }
              jetpt = jetpt / vScalePtSyst;
            }

          // smear pt
          if(djt.ajetopt[irecogen]=="reco" && gensmearpt)
            {
              if(jetpt > 10)
                {
                  Float_t sigmaPt = TMath::Sqrt(paramfResoPt->at(ibincent).at(0)*paramfResoPt->at(ibincent).at(0) + 
                                                paramfResoPt->at(ibincent).at(1)*paramfResoPt->at(ibincent).at(1)/jetpt + 
                                                paramfResoPt->at(ibincent).at(2)*paramfResoPt->at(ibincent).at(2)/(jetpt*jetpt));
                  sigmaPt *= TMath::Sqrt((1+uncert_reso)*(1+uncert_reso) - 1);
                  jetpt = jetpt * pRandom3->Gaus(1, sigmaPt);
                }
            }

          /*********************************/
          if(jetpt < djt.cut_jetpt_min) continue;
          /*********************************/

          // smear angle
          if(djt.ajetopt[irecogen]=="gen" && gensmearphi)
            {
              if(gensmearphi==1)
                {
                  Float_t sigmaPhi = TMath::Sqrt(paramfResoPhi->at(ibincent).at(0)*paramfResoPhi->at(ibincent).at(0) +
                                                 paramfResoPhi->at(ibincent).at(1)*paramfResoPhi->at(ibincent).at(1)/jetpt +
                                                 paramfResoPhi->at(ibincent).at(2)*paramfResoPhi->at(ibincent).at(2)/(jetpt*jetpt));
                  jetphi = jetphi + pRandom3->Gaus(0, sigmaPhi);

                  Float_t sigmaEta = TMath::Sqrt(paramfResoEta->at(ibincent).at(0)*paramfResoEta->at(ibincent).at(0) +
                                                 paramfResoEta->at(ibincent).at(1)*paramfResoEta->at(ibincent).at(1)/jetpt +
                                                 paramfResoEta->at(ibincent).at(2)*paramfResoEta->at(ibincent).at(2)/(jetpt*jetpt));
                  jeteta = jeteta + pRandom3->Gaus(0, sigmaEta);
                }
              else if(gensmearphi==2)
                {
                  Float_t sigmaPhi = TMath::Sqrt(paramfResoDeltaPhi->at(ibincent).at(0)*paramfResoDeltaPhi->at(ibincent).at(0) +
                                                 paramfResoDeltaPhi->at(ibincent).at(1)*paramfResoDeltaPhi->at(ibincent).at(1)/jetpt +
                                                 paramfResoDeltaPhi->at(ibincent).at(2)*paramfResoDeltaPhi->at(ibincent).at(2)/(jetpt*jetpt)
                                                 - (paramfResoDeltaPhi->at(ibincent).at(3)*paramfResoDeltaPhi->at(ibincent).at(3) +
                                                    paramfResoDeltaPhi->at(ibincent).at(4)*paramfResoDeltaPhi->at(ibincent).at(4)/jetpt +
                                                    paramfResoDeltaPhi->at(ibincent).at(5)*paramfResoDeltaPhi->at(ibincent).at(5)/(jetpt*jetpt)));
                  jetphi = jetphi + pRandom3->Gaus(0, sigmaPhi);

                  Float_t sigmaEta = TMath::Sqrt(paramfResoDeltaEta->at(ibincent).at(0)*paramfResoDeltaEta->at(ibincent).at(0) +
                                                 paramfResoDeltaEta->at(ibincent).at(1)*paramfResoDeltaEta->at(ibincent).at(1)/jetpt +
                                                 paramfResoDeltaEta->at(ibincent).at(2)*paramfResoDeltaEta->at(ibincent).at(2)/(jetpt*jetpt)
                                                 - (paramfResoDeltaEta->at(ibincent).at(3)*paramfResoDeltaEta->at(ibincent).at(3) +
                                                    paramfResoDeltaEta->at(ibincent).at(4)*paramfResoDeltaEta->at(ibincent).at(4)/jetpt +
                                                    paramfResoDeltaEta->at(ibincent).at(5)*paramfResoDeltaEta->at(ibincent).at(5)/(jetpt*jetpt)));
                  jeteta = jeteta + pRandom3->Gaus(0, sigmaEta);
                }
              else { std::cout<<"invalid gensmearphi"<<std::endl; return; }
            }

          /*********************************/
          if(!(TMath::Abs(jeteta) > djt.cut_jeteta_min && TMath::Abs(jeteta) < djt.cut_jeteta_max)) continue;
          /*********************************/

          ncountjet += evtweight;

          // reco
          for(int jd=0;jd<*(djt.anD[irecogen]);jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[irecogen])[jd]);
              if(ibinpt<0) continue;              

              // to add pt-dependent event selection ...
              
              Float_t deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[irecogen])[jd] - jetphi));
              Float_t deltaeta = (**djt.aDeta[irecogen])[jd] - jeteta;
              Float_t deltaetaref = (**djt.aDeta[irecogen])[jd] + jeteta;
              Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                          (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
              Float_t zvariable = (**djt.aDpt[irecogen])[jd]/jetpt;
              
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
                      ahHistoRMassSignal[l][ibinpt][ibindr]->Fill((*djt.Dmass)[jd], evtweight);
                      ahNumREfficiency[l][ibinpt]->Fill(deltaR[l], evtweight);
                    }
                  if((*djt.Dgen)[jd]==23344) ahHistoRMassSwapped[l][ibinpt][ibindr]->Fill((*djt.Dmass)[jd], evtweight);

                  if(deltaR[l]>0.3) continue; // ... to discuss
                  Int_t ibinz = xjjc::findibin(&zBins, zvariable);
                  if(ibinz<0) continue;
                  if((*djt.Dgen)[jd]==23333) 
                    {
                      ahHistoZMassSignal[l][ibinpt][ibinz]->Fill((*djt.Dmass)[jd], evtweight);
                      ahNumZEfficiency[l][ibinpt]->Fill(zvariable, evtweight);
                    }
                  if((*djt.Dgen)[jd]==23344) ahHistoZMassSwapped[l][ibinpt][ibinz]->Fill((*djt.Dmass)[jd], evtweight);
                }
            }
          // gen
          for(int jd=0;jd<djt.Gsize;jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (*djt.Gpt)[jd]);
              if(ibinpt<0) continue;       
              
              // to add pt-dependent event selection ...
              
              Float_t deltaphi = TMath::ACos(TMath::Cos((*djt.Gphi)[jd] - jetphi));
              Float_t deltaeta = (*djt.Geta)[jd] - jeteta;
              Float_t deltaetaref = (*djt.Geta)[jd] + jeteta;
              Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                          (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
              Float_t zvariable = (*djt.Gpt)[jd]/jetpt;
              
              for(int l=0;l<nRefBins;l++)
                {
                  Int_t djtDsel = djt.isDselected(jd, "gen");
                  if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                  if(!djtDsel) continue;
                  ahDenREfficiency[l][ibinpt]->Fill(deltaR[l], evtweight);
                  
                  if(deltaR[l]>0.3) continue; // ... to discuss
                  ahDenZEfficiency[l][ibinpt]->Fill(zvariable, evtweight);
                }
            }
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   djtana_savetpl("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(30)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<std::endl;
  std::cout<<std::endl;

  hNjets->SetBinContent(1, ncountjet);
  for(int l=0;l<nRefBins;l++)
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

  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savetpl")) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==13)
    {
      djtana_savetpl(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atoi(argv[9]), atoi(argv[10]), atoi(argv[11]), atoi(argv[12]));
      return 0;
    }
  if(argc==12)
    {
      djtana_savetpl(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atoi(argv[9]), atoi(argv[10]), atoi(argv[11]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_savetpl()"<<std::endl;
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
  if(irecogen==1 || irecogen==3)
    {
      std::cout<<"\"irecogen\" indicates genD, skip djtana_savetpl()."<<std::endl;
      return 2;
    }
  return 0;
}
