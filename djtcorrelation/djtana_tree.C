#include "djtana.h"

void djtana_tree(TString inputname, TString outputname, 
                    TString collisionsyst, Int_t isMC, Int_t irecogen,
                    Float_t jetptmin, Float_t jetetamin, Float_t jetetamax, 
                    Int_t maxevt=-1)
{

  Int_t ispp = collisionsyst=="pp"?1:0;

  djet* djt = new djet(inputname, ispp, isMC);
  djt->setjetcut(jetptmin, jetetamin, jetetamax);
  djt->setGcut(cutval_Dy);
  initcutval(collisionsyst);

  TCanvas* f = new TCanvas("f","",800,800);
  djt->fChain->Draw("Dtrk1PixelHit:Dphi","Dphi<=3.14 && Dphi>=-3.14","COLZ");
  f->SaveAs(Form("plots/npixel1_%s.png",outputname.Data()));
  djt->fChain->Draw("Dtrk2PixelHit:Dphi","Dphi<=3.14 && Dphi>=-3.14","COLZ");
  f->SaveAs(Form("plots/npixel2_%s.png",outputname.Data()));
  delete f;
  delete djt;

}

int main(int argc, char* argv[])
{
  if(argc==10)
    {
      djtana_tree(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atoi(argv[9]));
      return 0;
    }
  if(argc==9)
    {
      djtana_tree(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_tree() " << argc <<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t irecogen)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  if(irecogen<0 || irecogen>3)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"irecogen\""<<std::endl;
      return 1;
    }
/*
  if(irecogen==1 || irecogen==3)
    {
      std::cout<<"\"irecogen\" indicates genD, skip djtana_tree()."<<std::endl;
      return 2;
    }
*/
  return 0;
}
