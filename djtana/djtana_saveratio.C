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
      for(int l=0;l<nRefBins;l++)
        {
          TH1F* hSignalXnormP[2][2] = {{ahSignalRnormP[0][l][i]}, 
                                       {ahSignalRnormP[1][l][i]}};
          TH1F* hSignalXnormRatio[2] = {ahSignalRnormRatio[l][i]};
          for(int k=0;k<1;k++)
            {
              hSignalXnormRatio[k]->Divide(hSignalXnormP[1][k], hSignalXnormP[0][k]);
            }
        }
      TH1F* hSignalXsubP[2][2] = {{ahSignalRsubP[0][i]}, 
                                  {ahSignalRsubP[1][i]}};
      TH1F* hSignalXsubRatio[2] = {ahSignalRsubRatio[i]};
      for(int k=0;k<1;k++)
        {
          hSignalXsubRatio[k]->Divide(hSignalXsubP[1][k], hSignalXsubP[0][k]);
        }
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

