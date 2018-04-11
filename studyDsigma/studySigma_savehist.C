#include "studySigma.h"

void studySigma_savehist(TString inputname, TString outputname, TString collisionsyst, int maxevt=-1)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  if(createhists("savehist")) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  djtweight::init();
 
  djet djt(inputname, ispp, 1);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   studySigma_savehist("<<std::setw(20)<<Form("%s)",collisionsyst.Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //
      // Float_t cweight = ispp?1.:djtweight::getcentweight(djt.hiBin);
      Float_t cweight = 1.;
      Float_t evtweight = djt.pthatweight*cweight;
      // loop D
      for(int jd=0;jd<djt.Gsize;jd++)
        {
          // if((*djt.GcollisionId)[jd] != 0) continue;
          if(!( ((*djt.GisSignal)[jd]==1||(*djt.GisSignal)[jd]==2) && TMath::Abs((*djt.Gy)[jd]) < 1)) continue;
          
          Float_t Dptweight = djtweight::getDptweight((*djt.Gpt)[jd], ispp);
          hDpt_MC->Fill((*djt.Gpt)[jd], evtweight);
          hDpt_MC_weight->Fill((*djt.Gpt)[jd], evtweight * Dptweight);
          hDpt_MC_fine->Fill((*djt.Gpt)[jd], evtweight);
        }
    }
  hDpt_MC->Scale(1, "width");
  hDpt_MC_weight->Scale(1, "width");
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   studySigma_savehist("<<std::setw(30)<<Form("%s)",collisionsyst.Data())<<std::endl;
  std::cout<<std::endl;

  std::ifstream getdata(Form("datfiles/HIN16001_datatable_%s.txt",collisionsyst.Data()));
  if(!getdata.is_open()) { std::cout<<"error: getdata fails"<<std::endl; return; }
  for(int j=0;j<nPtBins;j++)
    {
      float tem, center, stat, syst;
      getdata>>tem>>tem>>tem>>center>>stat>>syst;
      hDpt_data->SetBinContent(j+1, center);
      hDpt_data->SetBinError(j+1, TMath::Sqrt(stat*stat+syst*syst));
    }

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

