#include "jetstudies.h"

void jetstudies_savehisto(TString inputname, TString outputname, 
                     TString collisionsyst, Int_t isMC, Int_t irecogen,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax, 
                     TString hltsel="noHLT", Int_t maxevt=1000000)
{

  int arguerr(TString collisionsyst, Int_t irecogen, Int_t isMC);
  if(arguerr(collisionsyst, irecogen, isMC)) return;
  if(createhists("savehist")) return;

  std::cout<<"look at here 2"<<std::endl;
  Int_t ispp = collisionsyst=="pp"?1:0;
 
  djet djt(inputname, ispp);
  djt.setjetcut(jetptmin, jetetamin, jetetamax);
  djt.setGcut(cutval_Dy);
  initcutval(collisionsyst);


  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  int ncountjet = 0;
  for(int i=0;i<rnentries;i++)
    { 
      if(i%10==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   jetstudies_savehisto("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(20)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      djt.fHlt->GetEntry(i);
      //        
      // to add event selection ...
      if(djt.ishltselected(hltsel) < 0) return;
      if(!djt.ishltselected(hltsel)) continue;

      // loop jets
      for(int jj=0;jj<*(djt.anjet[irecogen]);jj++)
        {           
          int djtjetsel = djt.isjetselected(jj, djt.ajetopt[irecogen]);
          if(djtjetsel < 0) return;
          if(!djtjetsel) continue;
          ncountjet++;
    
          hJetPtSpectrumInclusive->Fill((float)(**djt.ajetpt[irecogen])[jj]);
          
          // loop D
          for(int jd=0;jd<*(djt.anD[irecogen]);jd++)
            {
              Int_t ibinpt = xjjc::findibin(&ptBins, (**djt.aDpt[irecogen])[jd]);
              if(ibinpt<0) continue;              

              // to add pt-dependent event selection ...

              Float_t deltaphi = TMath::ACos(TMath::Cos((**djt.aDphi[irecogen])[jd] - (**djt.ajetphi[irecogen])[jj]));
              Float_t deltaeta = (**djt.aDeta[irecogen])[jd] - (**djt.ajeteta[irecogen])[jj];
              Float_t deltaetaref = (**djt.aDeta[irecogen])[jd] + (**djt.ajeteta[irecogen])[jj];
              Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)), 
                                          (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
              Float_t zvariable = (**djt.aDpt[irecogen])[jd]/(**djt.ajetpt[irecogen])[jj];
              
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
                  //ahHistoRMass[l][ibinpt][ibindr]->Fill(Dmass);

                  if(deltaR[l]>0.3) continue; // ... to discuss
                  hJetPtSpectrumDmeson[l][ibinpt]->Fill((float)(**djt.ajetpt[irecogen])[jj]);

                  Int_t ibinz = xjjc::findibin(&zBins, zvariable);
                  if(ibinz<0) continue;
                  //ahHistoZMass[l][ibinpt][ibinz]->Fill(Dmass);
                }
            }
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   jetstudies_savehisto("<<std::setw(5)<<Form("%s,",collisionsyst.Data())<<" "<<std::setw(5)<<Form("%s,",tMC[isMC].Data())<<" "<<std::setw(30)<<Form("%sD_%sjet)", djt.aDopt[irecogen].Data(), djt.ajetopt[irecogen].Data())<<std::endl;
  std::cout<<std::endl;
  
  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savehist")) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==11)
    {
      jetstudies_savehisto(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), argv[9], atoi(argv[10]));
      return 0;
    }
  if(argc==10)
    {
      jetstudies_savehisto(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), argv[9]);
      return 0;
    }
  else if(argc==1)
    { 
      std::cout<<"hello"<<std::endl;
      jetstudies_savehisto("/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root",
                      "test",
                      "pp", 1, 0,
                      40, 0.3, 1.6, 
                      "noHLT", 100000);
      std::cout<<"hello 2"<<std::endl;
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - jetstudies_savehisto()"<<std::endl;
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

