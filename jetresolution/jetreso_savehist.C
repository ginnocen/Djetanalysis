#include "jetresolution.h"

void jetreso_savehist(TString inputname, TString outputname, TString collisionsyst,
                      // Float_t jetetamin, Float_t jetetamax,
                      Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  if(createhists("savehist")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;

  djet djt(inputname, ispp);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   jetreso_savehist("<<std::setw(20)<<Form("%s)",collisionsyst.Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //

      // loop jets
      for(int jj=0;jj<djt.njet_akpu3pf;jj++)
        {
          if(TMath::Abs((*djt.gjeteta_akpu3pf)[jj])>1.6) continue;

          Int_t ibinpt = xjjc::findibin(&jtptBins, (*djt.gjetpt_akpu3pf)[jj]);
          if(ibinpt<0) continue;

          ahHistoResoPt[ibinpt]->Fill((*djt.jetpt_akpu3pf)[jj]/(*djt.gjetpt_akpu3pf)[jj], djt.pthatweight);
          ahHistoResoPhi[ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], djt.pthatweight);
          ahHistoResoEta[ibinpt]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], djt.pthatweight);

        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   jetreso_savehist("<<std::setw(30)<<Form("%s)",collisionsyst.Data())<<std::endl;
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
      jetreso_savehist(argv[1], argv[2], argv[3], atoi(argv[4]));
      return 0;
    }
  if(argc==4)
    {
      jetreso_savehist(argv[1], argv[2], argv[3]);
      return 0;
    }
  return 1;
}

int arguerr(TString collisionsyst)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  return 0;
}
