#include "../includes/djet.h"
#include "../includes/xjjcuti.h"
#include "../includes/xjjrootuti.h"
#include "../includes/dfitter.h"
#include "../includes/djtcorr.h"
#include "../includes/djthlt.h"
#include "../includes/djtuti.h"
#include "../includes/systmetics.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include "studySigma.h"

void studySigma_savehist(TString inputname, TString outputname, TString collisionsyst, int maxevt=-1)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  if(createhists("savehist")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  djtweight::init();
 
 
  Float_t cutval_Dy = 2.0;
  Float_t cutval_trkPt = 2.0;
  Float_t cutval_trkEta = 2.0;
  Float_t cutval_trkPtErr = 0.3;
  Float_t cutval_Dchi2cl = 0.05;
  Float_t cutval_Dsvpv = 4.0; //! bin-dep
  Float_t cutval_Dalpha = 0.12; //! bin-dep

  djet djt(inputname, ispp, 0);
  //djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
  //djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);
  //djt.setGcut(cutval_Dy);
  //initcutval(collisionsyst);


  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   studySigma_savehist("<<std::setw(20)<<Form("%s)",collisionsyst.Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      std::cout<<djt.Dsize<<std::endl;
      //
      // Float_t cweight = ispp?1.:djtweight::getcentweight(djt.hiBin);
      //Float_t cweight = 1.;
      //Float_t evtweight = djt.pthatweight*cweight;
      // loop D
      for(int jd=0;jd<djt.Dsize;jd++)
        {

         for(int j=0;j<nptBins;j++) {
           Float_t Dmass =(*djt.Dmass)[jd];
           Float_t Dpt =(*djt.Dpt)[jd];
           Float_t Dy =(*djt.Dy)[jd];

           if(Dpt>ptBins[j] && Dpt<ptBins[j+1]) ahHistoMassPt[j]->Fill(Dmass);
           if(Dy>yBins[j] && Dy<yBins[j+1]) ahHistoMassY[j]->Fill(Dmass);
         }

          /*
          Float_t Dptwieight = djtweight::getDptweight((*djt.Gpt)[jd], ispp);
          hDpt_MC->Fill((*djt.Gpt)[jd], evtweight);
          hDpt_MC_weight->Fill((*djt.Gpt)[jd], evtweight * Dptweight);
          hDpt_MC_fine->Fill((*djt.Gpt)[jd], evtweight);
          */
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   studySigma_savehist("<<std::setw(30)<<Form("%s)",collisionsyst.Data())<<std::endl;
  std::cout<<std::endl;
 

  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savehist")) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      studySigma_savehist(argv[1], argv[2], argv[3], atoi(argv[4]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - studySigma_savehist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst)
{
  if(collisionsyst!="pp" && collisionsyst!="PbPb")
    {
      std::cout<<"error: invalid collisionsyst"<<std::endl;
      return 1;
    }
  return 0;
}

