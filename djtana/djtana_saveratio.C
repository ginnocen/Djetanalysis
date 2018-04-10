#include "djtana.h"

void djtana_saveratio(std::vector<TString> inputhistname, TString outputname)
{
  int arguerr(std::vector<TString> inputhistname);
  if(arguerr(inputhistname)) return;

  if(createhists("saveratio")) return;

  for(int m=0;m<2;m++)
    {
      TFile* infhist = new TFile(Form("%s.root",inputhistname[m].Data()));
      if(!infhist->IsOpen()) return;
      if(gethists(infhist, (m==0?"saveratiopp":"saveratiopbpb"))) return;
    }

  for(int i=0;i<nPtBins;i++)
    {
      ahSignalRsubRatio[i]->Divide(ahSignalRsubP[1][i], ahSignalRsubP[0][i]);
      ahSignalRsubRatioMe[i]->Divide(ahSignalRsubMeP[1][i], ahSignalRsubMeP[0][i]);
    }
  
  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("saveratio")) return;
  outf->Write();
  outf->Close();  

}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      std::vector<TString> inputname = {argv[1], argv[2]};
      djtana_saveratio(inputname, argv[3]);
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_saveratio()"<<std::endl;
      return 1;
    }
}

int arguerr(std::vector<TString> inputhistname)
{
  if(inputhistname.size()!=2)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"inputhistname\""<<std::endl;
      return 1;
    }
  return 0;
}

