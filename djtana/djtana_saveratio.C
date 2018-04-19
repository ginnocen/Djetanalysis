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

  if(inputhistname[0].Contains("0p0_1p6") && inputhistname[1].Contains("0p0_1p6"))
    {
      for(int i=0;i<nPtBins;i++)
        {
          std::cout<<"\033[0;36mHistogram bin content >>> "<<Form("D pt (%.0f, %.0f)\033[0m", ptBins[i], ptBins[i+1]);
          std::cout<<"\033[1;36m"<<std::endl;
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(20)<<"r"<<std::setw(10)<<"pp"<<std::setw(10)<<"PbPb"<<std::setw(10)<<"PbPb/pp"<<std::setw(10)<<"ratio"<<std::endl;
          for(int j=0;j<nDrBins;j++)
            {
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(20)<<Form("%.2f - %.2f",drBins[j],drBins[j+1]);
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<ahSignalRsubMeP[0][i]->GetBinContent(j+1);
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<ahSignalRsubMeP[1][i]->GetBinContent(j+1);
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<ahSignalRsubMeP[1][i]->GetBinContent(j+1)/ahSignalRsubMeP[0][i]->GetBinContent(j+1);
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<ahSignalRsubRatioMe[i]->GetBinContent(j+1);
              std::cout<<std::endl;
            }
          // std::cout<<std::setiosflags(std::ios::left)<<std::setw(20)<<"Norm"<<std::setw(10)<<normpp<<std::setw(10)<<normPbPb<<std::setw(10)<<normPbPb/normpp<<std::setw(10)<<normratio<<std::endl;
          std::cout<<"\033[0m"<<std::endl<<std::endl;
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

