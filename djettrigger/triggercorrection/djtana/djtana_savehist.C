#include "djtana.h"

void djtana_savehist(TString inputname, TString outputname, 
                     TString collisionsyst, Int_t isMC, Int_t irecogen,
                     Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax, 
                     Int_t jescale=0, Int_t gensmearpt=0, Int_t gensmearphi=0, 
                     Int_t signalMC=1, Int_t corrSmearsmearPP=0, Int_t corrFac=0,
                     Int_t maxevt=-1)
{
  if(corrSmearsmearPP==2) { std::cout<<"don't use this macro to smearpp"<<std::endl; }

  int arguerr(TString collisionsyst, Int_t irecogen, Int_t isMC, Int_t corrSmearsmearPP);
  if(arguerr(collisionsyst, irecogen, isMC, corrSmearsmearPP)) return;

  if(createhists("savehist")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  setnCentBins(ispp);
  djtcorr::setParameters(ispp);
 
  djet djt(inputname, ispp, isMC);
  djt.setGcut(cutval_Dy);
  initcutval(collisionsyst);

  Int_t fileno = -1;
  djt.fHlt->SetBranchStatus("fileno", 1);
  djt.fHlt->SetBranchAddress("fileno", &fileno);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  int ncountjet = 0;

  int NSMEAR=15;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   djtana_savehist("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(20)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      djt.fHlt->GetEntry(i);
      //

      if(isMC && djt.pthat < 15) continue;
      // float leadingjetpt = 0;
      // for(int jj=0;jj<*(djt.anjet[irecogen]);jj++)
      //   {
      //     if((**djt.ajetpt[irecogen])[jj]>leadingjetpt)
      //       leadingjetpt = (**djt.ajetpt[irecogen])[jj];
      //   }
      if(!isMC && !djthlt::checkHlt(djt, jetptmin, ispp, fileno)) continue;

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) {std::cout<<"error: wrong ibincent"<<std::endl; return;}
      Float_t cweight = ispp?1.:centweight[djt.hiBin];
      Float_t evtweight = isMC?(djt.pthatweight*cweight):1.;

      // loop jets
      for(int jj=0;jj<*(djt.anjet[irecogen]);jj++)
        {
          if(isMC && signalMC && (**djt.asubid[irecogen])[jj]!=0) continue;
          
          Float_t jetpt = (**djt.ajetpt[irecogen])[jj];
          Float_t jetphi = (**djt.ajetphi[irecogen])[jj];
          Float_t jeteta = (**djt.ajeteta[irecogen])[jj];
          Float_t jetnpdfpart = 0;
          if(jescale==2) jetnpdfpart = (*djt.jetnpfpart_akpu3pf)[jj];

          // JEC
          if(djt.ajetopt[irecogen]=="reco" && jescale)
            if(djtcorr::ptCorr(jescale, jetpt, jetnpdfpart, ibincent)) return;
          // smear pt
          int flagsmear = 0;
          std::vector<float>* vjetpt = new std::vector<float>();
          if(djt.ajetopt[irecogen]=="gen" && gensmearpt)
            {
              flagsmear++;
              for(int n=0;n<NSMEAR;n++)
                {
                  float sjetpt = jetpt;
                  if(djtcorr::ptSmear(sjetpt, ibincent)) return;
                  vjetpt->push_back(sjetpt);
                }              
            }
          else
            vjetpt->push_back(jetpt);

          // smear angle
          std::vector<float>* vjetphi = new std::vector<float>();
          std::vector<float>* vjeteta = new std::vector<float>();
          if(djt.ajetopt[irecogen]=="gen" && gensmearphi)
            {
              flagsmear++;
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

          // loop D
          for(int jd=0;jd<*(djt.anD[irecogen]);jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[irecogen])[jd]);
              if(ibinpt<0) continue;              
              Int_t ibinselpt = xjjc::findibin(&ptselBins, (**djt.aDpt[irecogen])[jd]);

              int nsjet = vjetpt->size();
              if(nsjet!=vjeteta->size() || nsjet!=vjetphi->size() || nsjet!=(flagsmear?NSMEAR:1)) { std::cout<<"error: wrong number of jet in vector."<<std::endl; return; }
              for(int s=0;s<nsjet;s++)
                {
                  if(vjetpt->at(s) < jetptmin || vjetpt->at(s) > jetptmax) continue;
                  if(!(TMath::Abs(vjeteta->at(s)) > jetetamin && TMath::Abs(vjeteta->at(s)) < jetetamax)) continue;

                  Float_t deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[irecogen])[jd] - vjetphi->at(s)));
                  Float_t deltaeta = (**djt.aDeta[irecogen])[jd] - vjeteta->at(s);
                  Float_t deltaetaref = (**djt.aDeta[irecogen])[jd] + vjeteta->at(s);
                  Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                                              (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
                  Float_t corrfactor = 1, corrfactorSg = 1;
                  for(int l=0;l<nRefBins;l++)
                    {
                      Int_t ibindr = xjjc::findibin(&drBins, deltaR[l]);
                      if(ibindr<0) continue;
                      if(djt.ajetopt[irecogen]=="reco" && corrFac) 
                        if(djtcorr::getcorrFactor(corrfactor, ibinpt, ibindr, jetptmin, jetptmax)) return;
                      if(corrSmearsmearPP==1) 
                        if(djtcorr::getcorrFactorSg(corrfactorSg, ibinpt, ibindr, jetptmin, jetptmax)) return;

                      Int_t result_initcutval = initcutval_bindep(collisionsyst, ibinselpt, ibindr);
                      if(result_initcutval) return;
                      djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
                      djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);
                      Int_t djtDsel = djt.isDselected(jd, djt.aDopt[irecogen]);
                      if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                      if(!djtDsel) continue;
                      Float_t Dmass = irecogen%2==0?(*djt.Dmass)[jd]:DZERO_MASS;
                      ahHistoRMass[l][ibinpt][ibindr]->Fill(Dmass, evtweight / (nsjet * corrfactor * corrfactorSg));
                      if(deltaR[l] < 0.3 && l)
                        ahHistoRMassRef[ibinpt]->Fill(Dmass, evtweight / (nsjet * corrfactor * corrfactorSg));
                    }
                }
            }
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   djtana_savehist("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(30)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<std::endl;
  std::cout<<std::endl;

  hNjets->SetBinContent(1, ncountjet);

  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savehist")) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==17)
    {
      djtana_savehist(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), 
                      atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]),
                      atoi(argv[10]), atoi(argv[11]), atoi(argv[12]),
                      atoi(argv[13]), atoi(argv[14]), atoi(argv[15]),
                      atoi(argv[16]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_savehist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t irecogen, Int_t isMC, Int_t corrSmearsmearPP)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  if(isMC!=0 && isMC!=1)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"isMC\""<<std::endl;
      return 1;
    }
  if(irecogen<0 && irecogen>3)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"irecogen\""<<std::endl;
      return 1;
    }
  if(collisionsyst!="pp" && corrSmearsmearPP==2)
    {
      std::cout<<"error: set smearPP=0 for PbPb"<<std::endl;
      return 1;
    }
  return 0;
}

