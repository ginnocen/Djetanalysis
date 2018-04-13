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

void studySigma_savehist(TString inputname, TString outputname, TString collisionsyst, int maxevt=-1, int isMC=1,int ispthatweight=1, double ptcutforYstudy=2.0, double ycutforPtstudy=4.0,Float_t cutval_Dchi2cl = 0.15, Float_t cutval_Dsvpv = 4.5,Float_t cutval_Dalpha = 0.12)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  if(createhists("savehist")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  djtweight::init();
 
  std::cout<<"cut on pt="<<ptcutforYstudy<<std::endl;
  std::cout<<"cut on y="<<ycutforPtstudy<<std::endl;
 
  Float_t cutval_Dy = 2.0;
  Float_t cutval_trkPt = 2.0;
  Float_t cutval_trkEta = 2.0;
  Float_t cutval_trkPtErr = 0.3;

  djet djt(inputname, ispp, isMC);
  djt.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
  djt.setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);
  djt.setGcut(cutval_Dy);
  //initcutval(collisionsyst);

 if (ptcutforYstudy<4.) std::cout<<"there is a hard cut for pt<4 in the production!"<<std::endl;

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   studySigma_savehist("<<std::setw(20)<<Form("%s)",collisionsyst.Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
            //
      Float_t cweight = ispp?1.:djtweight::getcentweight(djt.hiBin);
      Float_t evtweight = cweight;
      Float_t ptweight=djt.pthatweight;
      
      if (ispthatweight==1&&isMC==1) evtweight=evtweight*ptweight;
      // loop D
      for(int jd=0;jd<djt.Dsize;jd++){
      Int_t djtDsel = djt.isDselected(jd, "r");
      if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
      if(!djtDsel) continue;

         Float_t Dmass =(*djt.Dmass)[jd];
         Float_t Dpt =(*djt.Dpt)[jd];
         Float_t Dy =(*djt.Dy)[jd];
         if(Dpt<4.) continue;

         for(int j=0;j<nptBins;j++) {
           if(std::fabs(Dy)>ycutforPtstudy) continue;
           if(Dpt>ptBins[j] && Dpt<ptBins[j+1]) {
             ahHistoMassPt[j]->Fill(Dmass);
             if (isMC==1){
               if((*djt.Dgen)[jd]==23333) ahHistoMassPtSignal[j]->Fill(Dmass,evtweight);
               if((*djt.Dgen)[jd]==23344) ahHistoMassPtSwapped[j]->Fill(Dmass,evtweight);
               }//if isMC
             }//if pt bin
         }//loop over pt bins
         for(int j=0;j<nyBins;j++) {
         if(Dpt<ptcutforYstudy) continue;
           if(Dy>yBins[j] && Dy<yBins[j+1]) {
             ahHistoMassY[j]->Fill(Dmass);
             if (isMC==1){
               if((*djt.Dgen)[jd]==23333) ahHistoMassYSignal[j]->Fill(Dmass,evtweight);
               if((*djt.Dgen)[jd]==23344) ahHistoMassYSwapped[j]->Fill(Dmass,evtweight);
               }//if isMC
             }//if y bin
         }//loop over y bins
         if(Dpt>ptcutforYstudy) {
           hDmesonY->Fill(Dy);
         }
       }//d size
    } //end of entries
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
  if(argc==12)
    {
      studySigma_savehist(argv[1], argv[2], argv[3], atoi(argv[4]),atoi(argv[5]),atoi(argv[6]),atof(argv[7]),atof(argv[8]),atof(argv[9]),atof(argv[10]),atof(argv[11]));
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

