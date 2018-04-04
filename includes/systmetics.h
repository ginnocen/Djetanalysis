#ifndef SYSTMETICS_
#define SYSTMETICS_

#include <vector>
#include <TMath.h>

namespace djtsyst
{
  std::vector<std::vector<Float_t>> syst60999_SCALE_pp = {{11.5, 8.2, 9.5, 7.2},
                                                          {1.2, 5.0, 8.6, 22.6}};
  std::vector<std::vector<Float_t>> syst60999_SCALE_PbPb = {{35.8, 23.9, 10.5, 17.2},
                                                            {3.1, 8.6, 19.2, 34.6}};
  std::vector<std::vector<Float_t>> syst6080_SCALE_pp = {{4.1, 4.7, 14.8, 14.3}};
  std::vector<std::vector<Float_t>> syst80100_SCALE_pp = {{1.6, 2.4, 6.0, 13.3}};
  std::vector<std::vector<Float_t>> syst100999_SCALE_pp = {{1.8, 1.7, 4.3, 5.0}};
  std::vector<std::vector<Float_t>> syst6080_SCALE_PbPb = {{9.5, 8.6, 32.3, 22.2}};
  std::vector<std::vector<Float_t>> syst80100_SCALE_PbPb = {{5.6, 21.0, 8.2, 37.6}};
  std::vector<std::vector<Float_t>> syst100999_SCALE_PbPb = {{5.0, 14.1, 5.3, 30.4}};

  std::vector<std::vector<Float_t>> syst60999_RESO_pp = {{3.6, 0.3, 0.9, 1.2},
                                                         {0.5, 1.7, 3.0, 1.7}};
  std::vector<std::vector<Float_t>> syst60999_RESO_PbPb = {{10.9, 4.1, 4.4, 5.8},
                                                           {1.3, 2.1, 6.9, 3.2}};
  std::vector<std::vector<Float_t>> syst6080_RESO_pp = {{0.6, 0.9, 0.8, 0.3}};
  std::vector<std::vector<Float_t>> syst80100_RESO_pp = {{0.3, 0.0, 0.5, 1.0}};
  std::vector<std::vector<Float_t>> syst100999_RESO_pp = {{0.3, 0.1, 0.3, 0.8}};
  std::vector<std::vector<Float_t>> syst6080_RESO_PbPb = {{0.8, 0.2, 1.9, 1.3}};
  std::vector<std::vector<Float_t>> syst80100_RESO_PbPb = {{0.4, 0.2, 0.3, 2.6}};
  std::vector<std::vector<Float_t>> syst100999_RESO_PbPb = {{0.6, 0.0, 1.0, 0.9}};

  std::vector<std::vector<Float_t>> syst60999_PDF_pp = {{5.3, 1.6, 5.5, 15.7},
                                                        {3.5, 7.9, 6.8, 2.8}};
  std::vector<std::vector<Float_t>> syst60999_PDF_PbPb = {{5.9, 9.7, 1.9, 1.2},
                                                          {3.2, 3.9, 18.2, 18.4}};
  std::vector<std::vector<Float_t>> syst6080_PDF_pp = {{2.5, 4.4, 1.0, 4.4}};
  std::vector<std::vector<Float_t>> syst80100_PDF_pp = {{3.3, 5.1, 5.4, 2.1}};
  std::vector<std::vector<Float_t>> syst100999_PDF_pp = {{4.8, 9.5, 1.6, 14.1}};
  std::vector<std::vector<Float_t>> syst6080_PDF_PbPb = {{4.7, 11.4, 12.2, 3.5}};
  std::vector<std::vector<Float_t>> syst80100_PDF_PbPb = {{1.7, 4.0, 2.2, 0.7}};
  std::vector<std::vector<Float_t>> syst100999_PDF_PbPb = {{4.4, 3.0, 6.4, 2.3}};
  std::vector<std::vector<Float_t>> syst60999_PDF_ratio = {{10.6, 8.0, 6.4, 18.2},
                                                           {3.3, 4.7, 11.6, 17.0}};
  std::vector<std::vector<Float_t>> syst6080_PDF_ratio = {{5.1, 9.1, 11.1, 7.9}};
  std::vector<std::vector<Float_t>> syst80100_PDF_ratio = {{2.5, 2.9, 3.8, 1.6}};
  std::vector<std::vector<Float_t>> syst100999_PDF_ratio = {{2.6, 9.7, 4.9, 14.3}};

  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_pp = {{8.7, 0.7, 2.4, 3.8},
                                                               {2.6, 8.7, 15.3, 13.0}};
  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_PbPb = {{6.4, 3.0, 3.7, 2.7},
                                                                 {2.9, 6.0, 11.8, 14.4}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_pp = {{6.8, 6.9, 12.1, 13.0}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_pp = {{6.7, 6.0, 10.5, 12.1}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_pp = {{6.6, 6.2, 8.9, 7.0}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_PbPb = {{5.3, 5.3, 5.0, 7.5}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_PbPb = {{5.9, 1.4, 14.2, 0.4}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_PbPb = {{14.5, 14.7, 15.6, 12.9}};

  std::vector<Float_t> syst_CUT_pp = {3.6, 0.5};
  std::vector<Float_t> syst_CUT_PbPb = {3.5, 2.7};

  //
  std::vector<std::vector<Float_t>>* syst_SCALE_pp;  
  std::vector<std::vector<Float_t>>* syst_SCALE_PbPb;  
  std::vector<std::vector<Float_t>>* syst_RESO_pp;  
  std::vector<std::vector<Float_t>>* syst_RESO_PbPb;  
  std::vector<std::vector<Float_t>>* syst_PDF_pp;  
  std::vector<std::vector<Float_t>>* syst_PDF_PbPb;  
  std::vector<std::vector<Float_t>>* syst_PDF_ratio;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_pp;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_PbPb;  

  int initsyst(float jetptmin, float jetptmax)
  {
    if(jetptmin==60 && jetptmax==999)
      {
        syst_SCALE_pp = &syst60999_SCALE_pp;
        syst_SCALE_PbPb = &syst60999_SCALE_PbPb;
        syst_RESO_pp = &syst60999_RESO_pp;
        syst_RESO_PbPb = &syst60999_RESO_PbPb;
        syst_PDF_pp = &syst60999_PDF_pp;
        syst_PDF_PbPb = &syst60999_PDF_PbPb;
        syst_PDF_ratio = &syst60999_PDF_ratio;
        syst_NONCLOSURE_pp = &syst60999_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst60999_NONCLOSURE_PbPb;
        return 0;
      }
    if(jetptmin==60 && jetptmax==80)
      {
        syst_SCALE_pp = &syst6080_SCALE_pp;
        syst_SCALE_PbPb = &syst6080_SCALE_PbPb;
        syst_RESO_pp = &syst6080_RESO_pp;
        syst_RESO_PbPb = &syst6080_RESO_PbPb;
        syst_PDF_pp = &syst6080_PDF_pp;
        syst_PDF_PbPb = &syst6080_PDF_PbPb;
        syst_PDF_ratio = &syst6080_PDF_ratio;
        syst_NONCLOSURE_pp = &syst6080_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst6080_NONCLOSURE_PbPb;
        return 0;
      }
    if(jetptmin==80 && jetptmax==100)
      {
        syst_SCALE_pp = &syst80100_SCALE_pp;
        syst_SCALE_PbPb = &syst80100_SCALE_PbPb;
        syst_RESO_pp = &syst80100_RESO_pp;
        syst_RESO_PbPb = &syst80100_RESO_PbPb;
        syst_PDF_pp = &syst80100_PDF_pp;
        syst_PDF_PbPb = &syst80100_PDF_PbPb;
        syst_PDF_ratio = &syst80100_PDF_ratio;
        syst_NONCLOSURE_pp = &syst80100_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst80100_NONCLOSURE_PbPb;
        return 0;
      }
    if(jetptmin==100 && jetptmax==999)
      {
        syst_SCALE_pp = &syst100999_SCALE_pp;
        syst_SCALE_PbPb = &syst100999_SCALE_PbPb;
        syst_RESO_pp = &syst100999_RESO_pp;
        syst_RESO_PbPb = &syst100999_RESO_PbPb;
        syst_PDF_pp = &syst100999_PDF_pp;
        syst_PDF_PbPb = &syst100999_PDF_PbPb;
        syst_PDF_ratio = &syst100999_PDF_ratio;
        syst_NONCLOSURE_pp = &syst100999_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst100999_NONCLOSURE_PbPb;
        return 0;
      }
    std::cout<<"error: invalid jetptmin or jetptmax"<<std::endl;
    return 1;
  }

  Float_t getsyst(int ibinpt, int ibindr, Option_t* option)
  {
    TString opt  = option;
    Float_t syst = 0;

    if(opt=="pp")
      {
        syst += syst_CUT_pp[ibinpt] * syst_CUT_pp[ibinpt] + 
          syst_SCALE_pp->at(ibinpt).at(ibindr) * syst_SCALE_pp->at(ibinpt).at(ibindr) + 
          syst_RESO_pp->at(ibinpt).at(ibindr) * syst_RESO_pp->at(ibinpt).at(ibindr) + 
          syst_PDF_pp->at(ibinpt).at(ibindr) * syst_PDF_pp->at(ibinpt).at(ibindr) + 
          syst_NONCLOSURE_pp->at(ibinpt).at(ibindr) * syst_NONCLOSURE_pp->at(ibinpt).at(ibindr);
      }
    else if(opt=="PbPb")
      {
        syst += syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt] + 
          syst_SCALE_PbPb->at(ibinpt).at(ibindr) * syst_SCALE_PbPb->at(ibinpt).at(ibindr) + 
          syst_RESO_PbPb->at(ibinpt).at(ibindr) * syst_RESO_PbPb->at(ibinpt).at(ibindr) + 
          syst_PDF_PbPb->at(ibinpt).at(ibindr) * syst_PDF_PbPb->at(ibinpt).at(ibindr) + 
          syst_NONCLOSURE_PbPb->at(ibinpt).at(ibindr) * syst_NONCLOSURE_PbPb->at(ibinpt).at(ibindr);
      }
    else if(opt=="ratio")
      {
        syst += syst_CUT_pp[ibinpt] * syst_CUT_pp[ibinpt] + 
          syst_SCALE_pp->at(ibinpt).at(ibindr) * syst_SCALE_pp->at(ibinpt).at(ibindr) + 
          syst_RESO_pp->at(ibinpt).at(ibindr) * syst_RESO_pp->at(ibinpt).at(ibindr) + 
          syst_NONCLOSURE_pp->at(ibinpt).at(ibindr) * syst_NONCLOSURE_pp->at(ibinpt).at(ibindr) +
          syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt] + 
          syst_SCALE_PbPb->at(ibinpt).at(ibindr) * syst_SCALE_PbPb->at(ibinpt).at(ibindr) + 
          syst_RESO_PbPb->at(ibinpt).at(ibindr) * syst_RESO_PbPb->at(ibinpt).at(ibindr) + 
          syst_NONCLOSURE_PbPb->at(ibinpt).at(ibindr) * syst_NONCLOSURE_PbPb->at(ibinpt).at(ibindr) +

          syst_PDF_ratio->at(ibinpt).at(ibindr) * syst_PDF_PbPb->at(ibinpt).at(ibindr);        
      }
    else
      {
        std::cout<<"error: invalid option for getsyst()"<<std::endl;
        return -1;
      }

    return TMath::Sqrt(syst)/100.;
  }

}


#endif
