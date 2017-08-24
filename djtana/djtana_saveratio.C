#include "djtana.h"

void djtana_saveratio(TString inputhistnamePP, TString inputhistnamePbPb, TString outputname,
                      Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  int arguerr();
  if(arguerr()) return;

  if(createhists("saveratio")) return;

  TFile* infhistPP = new TFile(Form("%s.root",inputhistnamePP.Data()));
  if(!infhistPP->IsOpen()) return;
  if(gethists(infhistPP, "saveratioPP")) return;
  TFile* infhistPbPb = new TFile(Form("%s.root",inputhistnamePbPb.Data()));
  if(!infhistPbPb->IsOpen()) return;
  if(gethists(infhistPbPb, "saveratioPbPb")) return;

  for(int l=0;l<nRefBins;l++)
    {
      for(int i=0;i<nPtBins;i++)
        {
          TH1F*  hSignalXnormPP[2]     =  {ahSignalRnormPP[l][i],     ahSignalZnormPP[l][i]};
          TH1F*  hSignalXnormPbPb[2]   =  {ahSignalRnormPbPb[l][i],   ahSignalZnormPbPb[l][i]};
          TH1F*  hSignalXnormRatio[2]  =  {ahSignalRnormRatio[l][i],  ahSignalZnormRatio[l][i]};
          for(int k=0;k<2;k++)
            {
              TH1F* hRatio = (TH1F*)hSignalXnormPbPb[k]->Clone("hRatio");
              hRatio->Divide(hSignalXnormPP[k]);
              for(int j=0;j<hSignalXnormRatio[k]->GetNbinsX();j++)
                {
                  hSignalXnormRatio[k]->SetBinContent(j+1, hRatio->GetBinContent(j+1));
                  hSignalXnormRatio[k]->SetBinError(j+1, hRatio->GetBinError(j+1));
                }
              delete hRatio;
            }
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
  if(argc==7)
    {
      djtana_saveratio(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_saveratio()"<<std::endl;
      return 1;
    }
}

int arguerr()
{
  return 0;
}

