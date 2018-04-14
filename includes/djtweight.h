#include <TF1.h>

TString str_fcentweight = "TMath::Exp(1.73189e+00-1.95674e-02*x-3.23682e-04*x*x+3.25107e-06*x*x*x-1.21428e-08*x*x*x*x)";
TString str_weightGpt_pp = "2.279569-0.004518*x+30.063670/x-26.166070/(x*x)-11.656420/TMath::Sqrt(x)";
TString str_weightGpt_PbPb = "-14.375808+0.053090*x-196.670741/x+121.018606/(x*x)+121.064438/TMath::Sqrt(x)";

namespace djtweight
{
  TF1 *fcentweight, *fweightGpt_pp, *fweightGpt_PbPb;
  void init() 
  { 
    fcentweight = new TF1("fcentweight", str_fcentweight.Data(), 0, 200); 
    fweightGpt_pp = new TF1("fweightGpt_pp", str_weightGpt_pp.Data());
    fweightGpt_PbPb = new TF1("fweightGpt_PbPb", str_weightGpt_PbPb.Data());
  }
  float getcentweight(float hiBin) { return fcentweight->Eval(hiBin); }
  float getDptweight(float Dpt, int ispp)
  {
    if(ispp) return (1./fweightGpt_pp->Eval(Dpt));
    return (1./fweightGpt_PbPb->Eval(Dpt));
  }

}
