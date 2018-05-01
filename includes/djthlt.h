#ifndef DJTHLT_H_
#define DJTHLT_H_

TString str_jettrigger60_pp_L1 = "(0.995534*TMath::Erf(x*0.0798612-2.60536)*0.5*(1-0.00363702)+0.5*(1-0.00363702))";
TString str_jettrigger80_pp_L1 = "(0.970328*TMath::Erf(x*0.0849801-3.26178)*0.5*(1-0.0150987)+0.5*(1-0.0150987))";
TString str_jettrigger60_pp_HLT = "(0.972536*TMath::Erf(x*0.113385-6.44713)*0.5*(1-0.0138927)+0.5*(1-0.0138927))";
TString str_jettrigger80_pp_HLT = "(0.956368*TMath::Erf(x*0.101078-7.81464)*0.5*(1-0.0215687)+0.5*(1-0.0215687))";
TString str_jettrigger60_PbPb_L1 = "(0.979284*TMath::Erf(x*0.0828111-3.4634)*0.5*(1-0.0121254)+0.5*(1-0.0121254))";
TString str_jettrigger80_PbPb_L1 = "(0.907791*TMath::Erf(x*0.0717909-4.24326)*0.5*(1-0.0482678)+0.5*(1-0.0482678))";
TString str_jettrigger100_PbPb_L1 = "(0.878779*TMath::Erf(x*0.0609876-4.43417)*0.5*(1-0.0644453)+0.5*(1-0.0644453))";
TString str_jettrigger60_PbPb_HLT = "(0.942674*TMath::Erf((x+40.000000)*0.0528735-4.98271)*0.5*(1-0.0234821)+0.5*(1-0.0234821))";
TString str_jettrigger80_PbPb_HLT = "(0.942634*TMath::Erf(x*0.0593221-4.33808)*0.5*(1-0.0202727)+0.5*(1-0.0202727))";
TString str_jettrigger100_PbPb_HLT = "(0.942674*TMath::Erf(x*0.0528735-4.98271)*0.5*(1-0.0234821)+0.5*(1-0.0234821))";

TString str_Dtrigger_pp = "TMath::Erf(x*1.32864e-1-1.90241)*0.5*(1-6.35868e-2)+0.5*(1+6.35868e-2)";
TString str_Dtrigger_PbPb = "TMath::Erf(x*3.09974e-1+2.31049)*0.5*(1+4.5400e3)+0.5*(1-4.5400e3)";

namespace djthlt
{
  bool checkHlt(const djet &djt, float jetpt, int ispp, int fileno)
  {
    bool result = true;
    if(ispp)
      {
        if(jetpt >= 40 && jetpt < 60 && (!djt.HLT_AK4Jet40 || fileno==1)) result = false;
        if(jetpt >= 60 && jetpt < 80 && (!djt.HLT_AK4Jet60 || fileno==1)) result = false;
        if(jetpt >= 80 && jetpt < 100 && (!djt.HLT_AK4Jet80 || fileno==0)) result = false;
        if(jetpt >= 100 && (!djt.HLT_AK4Jet80 || fileno==0)) result = false;

        // if(!djt.HLT_DmesonDpt20) result = false;
      }
    else
      {        
        if(jetpt >= 40 && jetpt < 60 && !djt.HLT_AK4Jet40) result = false;
        if(jetpt >= 60 && jetpt < 80 && !djt.HLT_AK4Jet60) result = false;
        if(jetpt >= 80 && jetpt < 100 && !djt.HLT_AK4Jet80) result = false;
        if(jetpt >= 100 && !djt.HLT_AK4Jet100) result = false;

        // if(!djt.HLT_DmesonDpt20) result = false;
      }
    return result;
  }

  TF1 *fDtrigger_pp=0, *fDtrigger_PbPb=0;
  TF1 *fjettrigger60_pp_L1=0, *fjettrigger60_pp_HLT=0, *fjettrigger80_pp_L1=0, *fjettrigger80_pp_HLT=0, *fjettrigger100_pp_L1=0, *fjettrigger100_pp_HLT=0;
  TF1 *fjettrigger60_PbPb_L1=0, *fjettrigger60_PbPb_HLT=0, *fjettrigger80_PbPb_L1=0, *fjettrigger80_PbPb_HLT=0, *fjettrigger100_PbPb_L1=0, *fjettrigger100_PbPb_HLT=0;
  void init()
  {
    fDtrigger_pp = new TF1("fDtrigger_pp", str_Dtrigger_pp.Data());
    fDtrigger_PbPb = new TF1("fDtrigger_PbPb", str_Dtrigger_PbPb.Data());

    fjettrigger60_pp_L1 = new TF1("fjettrigger60_pp_L1", str_jettrigger60_pp_L1.Data());
    fjettrigger60_pp_HLT = new TF1("fjettrigger60_pp_HLT", str_jettrigger60_pp_HLT.Data());
    fjettrigger80_pp_L1 = new TF1("fjettrigger80_pp_L1", str_jettrigger80_pp_L1.Data());
    fjettrigger80_pp_HLT = new TF1("fjettrigger80_pp_HLT", str_jettrigger80_pp_HLT.Data());

    fjettrigger60_PbPb_L1 = new TF1("fjettrigger60_PbPb_L1", str_jettrigger60_PbPb_L1.Data());
    fjettrigger60_PbPb_HLT = new TF1("fjettrigger60_PbPb_HLT", str_jettrigger60_PbPb_HLT.Data());
    fjettrigger80_PbPb_L1 = new TF1("fjettrigger80_PbPb_L1", str_jettrigger80_PbPb_L1.Data());
    fjettrigger80_PbPb_HLT = new TF1("fjettrigger80_PbPb_HLT", str_jettrigger80_PbPb_HLT.Data());
    fjettrigger100_PbPb_L1 = new TF1("fjettrigger100_PbPb_L1", str_jettrigger100_PbPb_L1.Data());
    fjettrigger100_PbPb_HLT = new TF1("fjettrigger100_PbPb_HLT", str_jettrigger100_PbPb_HLT.Data());
  }
  float getDtriggerweight(float Dpt, int ispp)
  {
    // if(ispp) return (1./fDtrigger_pp->Eval(Dpt));
    if(ispp) return 1.;
    return (1./fDtrigger_PbPb->Eval(Dpt));
  }  
  float getjettriggerweight(float thre, float jetpt, int ispp)
  {
    float result = 1.;
    if(ispp)
      {
        // if(thre >= 40 && thre < 40) result = 1./(fjettrigger40_pp_L1->Eval(jetpt)*fjettrigger40_pp_HLT->Eval(jetpt));
        if(thre >= 60 && thre < 80) result = 1./(fjettrigger60_pp_L1->Eval(jetpt)*fjettrigger60_pp_HLT->Eval(jetpt));
        if(thre >= 80 && thre < 100) result = 1./(fjettrigger80_pp_L1->Eval(jetpt)*fjettrigger80_pp_HLT->Eval(jetpt));
        if(thre >= 100) result = 1./(fjettrigger80_pp_L1->Eval(jetpt)*fjettrigger80_pp_HLT->Eval(jetpt));
      }
    else
      {        
        // if(thre >= 40 && thre < 40) result = 1./(fjettrigger40_PbPb_L1->Eval(jetpt)*fjettrigger40_PbPb_HLT->Eval(jetpt));
        if(thre >= 60 && thre < 80) result = 1./(fjettrigger60_PbPb_L1->Eval(jetpt)*fjettrigger60_PbPb_HLT->Eval(jetpt));
        if(thre >= 80 && thre < 100) result = 1./(fjettrigger80_PbPb_L1->Eval(jetpt)*fjettrigger80_PbPb_HLT->Eval(jetpt));
        if(thre >= 100) result = 1./(fjettrigger100_PbPb_L1->Eval(jetpt)*fjettrigger100_PbPb_HLT->Eval(jetpt));
      }
    return result;
  }  
}

#endif
