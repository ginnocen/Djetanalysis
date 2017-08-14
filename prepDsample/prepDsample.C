#include <iostream>
#include <iomanip>
#include <TMath.h>
#include "includes/d_jet.h"
#include "includes/d_jet.C"
#include "includes/prepD.h"

Bool_t istest = false;
void prepDsample(string inputname="", string outputname="", Int_t isMC=1, Float_t jetptcut=80, Float_t jetetamincut=0.0, Float_t jetetamaxcut=2.0, Int_t maxevt=-1)
{
  if(istest)
    {
      inputname = "/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root";
      outputname = "test.root";
      isMC = 1;
      jetptcut = 40;
      jetetamincut = 0.3;
      jetetamaxcut = 1.6;
      maxevt = 100000;
    }

  std::cout<<std::endl;
  djet djt(inputname);

  TFile* outf = new TFile(outputname.c_str(), "recreate");
  TTree* outtree_recojet = new TTree("recojet","");
  prepD pd_recojet(outtree_recojet, /*int isgenjet=*/0);
  TTree* outtree_genjet = new TTree("genjet","");
  prepD pd_genjet(outtree_genjet, /*int isgenjet=*/1);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&istest&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/rnentries)<<"%\033[0m"<<"\r"<<std::flush;
      pd_recojet.clear_vectors();
      pd_genjet.clear_vectors();
      //
      djt.fChain->GetEntry(i);
      //
      //if(!(djt.Dsize>0 && djt.njet_akpu3pf)) continue;

      const int ncases = 4;
      /* -------------------------------------- rD,rJet --------------- gD,rJet --------------- rD,gJet ------------ gD,gJet --------- */
      int                  dsize[ncases]    =  {0,                      0,                      0,                   0};
      int                  djtnD[ncases]    =  {djt.Dsize,              djt.Gsize,              djt.Dsize,           djt.Gsize};
      int                  djtnjet[ncases]  =  {djt.njet_akpu3pf,       djt.njet_akpu3pf,       djt.ngen_akpu3pf,    djt.ngen_akpu3pf};
      std::vector<float>*  aDpt[ncases]     =  {djt.Dpt,                djt.Gpt,                djt.Dpt,             djt.Gpt};
      std::vector<float>*  aDeta[ncases]    =  {djt.Deta,               djt.Geta,               djt.Deta,            djt.Geta};
      std::vector<float>*  aDphi[ncases]    =  {djt.Dphi,               djt.Gphi,               djt.Dphi,            djt.Gphi};
      std::vector<float>*  ajetpt[ncases]   =  {djt.jetptCorr_akpu3pf,  djt.jetptCorr_akpu3pf,  djt.genpt_akpu3pf,   djt.genpt_akpu3pf};
      std::vector<float>*  ajeteta[ncases]  =  {djt.jeteta_akpu3pf,     djt.jeteta_akpu3pf,     djt.geneta_akpu3pf,  djt.geneta_akpu3pf};
      std::vector<float>*  ajetphi[ncases]  =  {djt.jetphi_akpu3pf,     djt.jetphi_akpu3pf,     djt.genphi_akpu3pf,  djt.genphi_akpu3pf};
      prepD*               apd[ncases]      =  {&pd_recojet,            &pd_recojet,            &pd_genjet,          &pd_genjet};
      TTree*               atree[ncases]    =  {outtree_recojet,        outtree_recojet,        outtree_genjet,      outtree_genjet};
      
      // if(!isMC) continue;
      for(int k=0;k<ncases;k++)
        {
          for(int jj=0;jj<djtnjet[k];jj++)
            {
              if((*(ajetpt[k]))[jj] > jetptcut && fabs((*(ajeteta[k]))[jj]) > jetetamincut && fabs((*(ajeteta[k]))[jj]) < jetetamaxcut)
                {
                  for(int jd=0;jd<djtnD[k];jd++)
                    {
                      Float_t deltaphi = TMath::ACos(TMath::Cos((*(aDphi[k]))[jd] - (*(ajetphi[k]))[jj]));
                      Float_t deltaeta = (*(aDeta[k]))[jd] - (*(ajeteta[k]))[jj];
                      Float_t deltaR = TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                      Float_t deltaetaref = (*(aDeta[k]))[jd] + (*(ajeteta[k]))[jj];
                      Float_t deltaRref = TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2));
                      Float_t zvariable = (*(aDpt[k]))[jd]/(*(ajetpt[k]))[jj];
                      if(k%2==0) apd[k]->copy_index(djt, jd, jj, deltaR, deltaRref, zvariable);
                      else apd[k]->copy_gen_index(djt, jd, jj, deltaR, deltaRref, zvariable);
                      dsize[k]++;
                    }
                }
            }
          if(k%2!=0) 
            {
              apd[k]->copy_variables(djt, dsize[k-1], dsize[k]);
              atree[k]->Fill();
            }
        }
    }

  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<std::endl;

  outf->cd();
  outtree_recojet->Write();
  outtree_genjet->Write();
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==8)
    {
      prepDsample(argv[1], argv[2], atoi(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atoi(argv[7]));
      return 0;
    }
  else if(argc==1)
    {
      prepDsample();
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - prepDsample()"<<std::endl;
      return 1;
    }
}
