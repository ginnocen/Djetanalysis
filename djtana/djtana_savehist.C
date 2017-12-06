#include "djtana.h"

void djtana_savehist(TString inputname, TString outputname, 
                     TString collisionsyst, Int_t isMC, Int_t irecogen,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax, 
                     TString hltsel="noHLT", Int_t jescale=0, Int_t gensmear=0, Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst, Int_t irecogen, Int_t isMC);
  if(arguerr(collisionsyst, irecogen, isMC)) return;

  if(createhists("savehist")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  setnCentBins(ispp);
 
  djet djt(inputname, ispp, isMC);
  djt.setjetcut(jetptmin, jetetamin, jetetamax);
  djt.setGcut(cutval_Dy);
  initcutval(collisionsyst);

  TRandom2* pRandom2 = new TRandom2();

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  int ncountjet = 0;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   djtana_savehist("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(20)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      djt.fHlt->GetEntry(i);
      //

      // to add event selection ...
      if(djt.ishltselected(hltsel) < 0) return;
      if(!djt.ishltselected(hltsel)) continue;

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) {std::cout<<"wrong ibincent"<<std::endl; return;}

      // loop jets
      for(int jj=0;jj<*(djt.anjet[irecogen]);jj++)
        {
          if(isMC && (**djt.asubid[irecogen])[jj]!=0) continue;

          Float_t jetpt = (**djt.ajetpt[irecogen])[jj];
          Float_t jetphi = (**djt.ajetphi[irecogen])[jj];
          Float_t jeteta = (**djt.ajeteta[irecogen])[jj];

          if(djt.ajetopt[irecogen]=="reco" && jescale)
            {
              std::vector<std::vector<Float_t>>* paramfScalePt = ispp?&paramfScalePt_pp:&paramfScalePt_PbPb;
              Float_t vScalePt = paramfScalePt->at(ibincent).at(0) + paramfScalePt->at(ibincent).at(1)/TMath::Sqrt((**djt.ajetpt[irecogen])[jj]) + paramfScalePt->at(ibincent).at(2)/(**djt.ajetpt[irecogen])[jj] + paramfScalePt->at(ibincent).at(3)/((**djt.ajetpt[irecogen])[jj]*(**djt.ajetpt[irecogen])[jj]);
              jetpt = (**djt.ajetpt[irecogen])[jj]/vScalePt;
            }

          if(djt.ajetopt[irecogen]=="gen" && gensmear)
            {
              std::vector<std::vector<Float_t>>* paramfResoPt = ispp?&paramfResoPtCorr_pp:&paramfResoPtCorr_PbPb;
              Float_t sigmaPt = paramfResoPt->at(ibincent).at(0)*paramfResoPt->at(ibincent).at(0) + paramfResoPt->at(ibincent).at(1)*paramfResoPt->at(ibincent).at(1)/jetpt + paramfResoPt->at(ibincent).at(2)*paramfResoPt->at(ibincent).at(2)/(jetpt*jetpt);
              jetpt = (**djt.ajetpt[irecogen])[jj] * pRandom2->Gaus(1, sigmaPt);

              std::vector<std::vector<Float_t>>* paramfResoPhi = ispp?&paramfResoPhi_pp:&paramfResoPhi_PbPb;
              Float_t sigmaPhi = paramfResoPhi->at(ibincent).at(0)*paramfResoPhi->at(ibincent).at(0) + paramfResoPhi->at(ibincent).at(1)*paramfResoPhi->at(ibincent).at(1)/jetpt + paramfResoPhi->at(ibincent).at(2)*paramfResoPhi->at(ibincent).at(2)/(jetpt*jetpt);
              jetphi = (**djt.ajetphi[irecogen])[jj] + pRandom2->Gaus(0, sigmaPhi);

              std::vector<std::vector<Float_t>>* paramfResoEta = ispp?&paramfResoEta_pp:&paramfResoEta_PbPb;
              Float_t sigmaEta = paramfResoEta->at(ibincent).at(0)*paramfResoEta->at(ibincent).at(0) + paramfResoEta->at(ibincent).at(1)*paramfResoEta->at(ibincent).at(1)/jetpt + paramfResoEta->at(ibincent).at(2)*paramfResoEta->at(ibincent).at(2)/(jetpt*jetpt);
              jeteta = (**djt.ajeteta[irecogen])[jj] + pRandom2->Gaus(0, sigmaEta);
            }

          if(!(jetpt > djt.cut_jetpt_min &&
               TMath::Abs(jeteta) > djt.cut_jeteta_min && TMath::Abs(jeteta) < djt.cut_jeteta_max)) continue;

          // int djtjetsel = djt.isjetselected(jj, djt.ajetopt[irecogen]);
          // if(djtjetsel < 0) return;
          // if(!djtjetsel) continue;
          ncountjet++;

          // loop D
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
                  Float_t Dmass = irecogen%2==0?(*djt.Dmass)[jd]:DZERO_MASS;
                  ahHistoRMass[l][ibinpt][ibindr]->Fill(Dmass);

                  if(deltaR[l]>0.3) continue; // ... to discuss
                  Int_t ibinz = xjjc::findibin(&zBins, zvariable);
                  if(ibinz<0) continue;
                  ahHistoZMass[l][ibinpt][ibinz]->Fill(Dmass);
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
  if(argc==13)
    {
      djtana_savehist(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), argv[9], atoi(argv[10]), atoi(argv[11]), atoi(argv[12]));
      return 0;
    }
  if(argc==12)
    {
      djtana_savehist(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), argv[9], atoi(argv[10]), atoi(argv[11]));
      return 0;
    }
  if(argc==10)
    {
      djtana_savehist(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), argv[9]);
      return 0;
    }
  else if(argc==1)
    {
      djtana_savehist("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root",
                      "test",
                      "pp", 1, 0,
                      40, 0.3, 1.6, 
                      "noHLT", 0, 0, 100000);
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_savehist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t irecogen, Int_t isMC)
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
  return 0;
}

