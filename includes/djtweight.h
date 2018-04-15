#include <TF1.h>

TString str_fcentweight = "TMath::Exp(1.73189e+00-1.95674e-02*x-3.23682e-04*x*x+3.25107e-06*x*x*x-1.21428e-08*x*x*x*x)";

TString str_weightGpt_pp = "2.279569-0.004518*x+30.063670/x-26.166070/(x*x)-11.656420/TMath::Sqrt(x)";
TString str_weightGpt_PbPb = "-14.375808+0.053090*x-196.670741/x+121.018606/(x*x)+121.064438/TMath::Sqrt(x)";

TString str_sigmaDmass_pp = "0.931362+0.0207396*x";
TString str_sigmaDmass_PbPb = "0.909772+0.0339522*x";
TString str_sigmaDmass_high_pp = "((1.021305-0.938347)/4.)*(x-2)+1.021305";
TString str_sigmaDmass_low_pp = "((0.924377-0.841419)/4.)*(x-2)+0.924377";
TString str_sigmaDmass_high_PbPb = "((1.052734-0.916926)/4.)*(x-2)+1.052734";
TString str_sigmaDmass_low_PbPb = "((0.902618-0.766810)/4.)*(x-2)+0.902618";

namespace djtweight
{
  TF1 *fcentweight=0;
  TF1 *fweightGpt_pp=0, *fweightGpt_PbPb=0;
  TF1 *fsigmaDmass_pp=0, *fsigmaDmass_PbPb=0;
  TF1 *fsigmaDmass_high_pp=0, *fsigmaDmass_high_PbPb=0;
  TF1 *fsigmaDmass_low_pp=0, *fsigmaDmass_low_PbPb=0;
  void init() 
  { 
    fcentweight = new TF1("fcentweight", str_fcentweight.Data(), 0, 200); 
    fweightGpt_pp = new TF1("fweightGpt_pp", str_weightGpt_pp.Data());
    fweightGpt_PbPb = new TF1("fweightGpt_PbPb", str_weightGpt_PbPb.Data());
    fsigmaDmass_pp = new TF1("fsigmaDmass_pp", str_sigmaDmass_pp.Data());
    fsigmaDmass_PbPb = new TF1("fsigmaDmass_PbPb", str_sigmaDmass_PbPb.Data());
    fsigmaDmass_high_pp = new TF1("fsigmaDmass_high_pp", str_sigmaDmass_high_pp.Data());
    fsigmaDmass_high_PbPb = new TF1("fsigmaDmass_high_PbPb", str_sigmaDmass_high_PbPb.Data());
    fsigmaDmass_low_pp = new TF1("fsigmaDmass_low_pp", str_sigmaDmass_low_pp.Data());
    fsigmaDmass_low_PbPb = new TF1("fsigmaDmass_low_PbPb", str_sigmaDmass_low_PbPb.Data());
  }
  float getcentweight(float hiBin) { return fcentweight->Eval(hiBin); }
  float getDptweight(float Dpt, int ispp)
  {
    if(ispp) return (1./fweightGpt_pp->Eval(Dpt));
    return (1./fweightGpt_PbPb->Eval(Dpt));
  }
  float getsigmascale(float Dy, int ispp, int option=0)
  {
    if(option==0)
      {
        if(ispp) return fsigmaDmass_pp->Eval(Dy);
        return fsigmaDmass_PbPb->Eval(Dy);
      }
    if(option==1)
      {
        if(ispp) return fsigmaDmass_low_pp->Eval(Dy);
        return fsigmaDmass_low_PbPb->Eval(Dy);        
      }
    if(option==2)
      {
        if(ispp) return fsigmaDmass_high_pp->Eval(Dy);
        return fsigmaDmass_high_PbPb->Eval(Dy);        
      }
    return -1;
  }

}
