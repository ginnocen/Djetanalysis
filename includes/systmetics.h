#ifndef SYSTMETICS_
#define SYSTMETICS_

#include <vector>
#include <TMath.h>

namespace djtsyst
{
  // jet energy scale
  std::vector<std::vector<Float_t>> syst60999_SCALE_pp = {{6.8, 15.2, 7.7, 10.3},
                                                          {1.6, 7.2, 9.6, 17.5}};
  std::vector<std::vector<Float_t>> syst60999_SCALE_PbPb = {{24.3, 31.5, 8.1, 35.8},
                                                            {1.8, 5.0, 11.5, 41.8}};
  std::vector<std::vector<Float_t>> syst6080_SCALE_pp = {{3.4, 5.8, 13.3, 26.5}};
  std::vector<std::vector<Float_t>> syst80100_SCALE_pp = {{0.8, 3.0, 3.5, 8.2}};
  std::vector<std::vector<Float_t>> syst100999_SCALE_pp = {{0.6, 3.2, 2.8, 3.5}};
  std::vector<std::vector<Float_t>> syst6080_SCALE_PbPb = {{8.6, 7.0, 17.7, 17.4}};
  std::vector<std::vector<Float_t>> syst80100_SCALE_PbPb = {{6.7, 2.2, 21.5, 26.6}};
  std::vector<std::vector<Float_t>> syst100999_SCALE_PbPb = {{0.9, 6.6, 11.2, 24.6}};

  // jet resolution
  std::vector<std::vector<Float_t>> syst60999_RESO_pp = {{3.0, 0.3, 1.2, 1.3},
                                                         {0.4, 1.2, 2.5, 0.8}};
  std::vector<std::vector<Float_t>> syst60999_RESO_PbPb = {{5.6, 1.3, 2.9, 3.7},
                                                           {0.6, 0.7, 4.9, 1.8}};
  std::vector<std::vector<Float_t>> syst6080_RESO_pp = {{0.3, 0.5, 0.5, 0.2}};
  std::vector<std::vector<Float_t>> syst80100_RESO_pp = {{0.1, 0.3, 0.6, 0.6}};
  std::vector<std::vector<Float_t>> syst100999_RESO_pp = {{0.2, 0.1, 0.5, 0.7}};
  std::vector<std::vector<Float_t>> syst6080_RESO_PbPb = {{0.0, 0.2, 0.4, 0.5}};
  std::vector<std::vector<Float_t>> syst80100_RESO_PbPb = {{0.3, 0.3, 1.1, 1.0}};
  std::vector<std::vector<Float_t>> syst100999_RESO_PbPb = {{0.3, 0.3, 1.0, 0.6}};

  // pdf variation
  std::vector<std::vector<Float_t>> syst60999_PDF_pp = {{4.5, 4.8, 3.1, 2.6},
                                                        {3.8, 3.7, 3.8, 5.4}};
  std::vector<std::vector<Float_t>> syst60999_PDF_PbPb = {{4.9, 5.2, 4.8, 7.7},
                                                          {5.9, 5.0, 8.2, 1.4}};
  std::vector<std::vector<Float_t>> syst6080_PDF_pp = {{3.8, 3.7, 3.2, 2.8}};
  std::vector<std::vector<Float_t>> syst80100_PDF_pp = {{3.9, 3.1, 3.4, 3.0}};
  std::vector<std::vector<Float_t>> syst100999_PDF_pp = {{4.3, 4.1, 3.3, 2.5}};
  std::vector<std::vector<Float_t>> syst6080_PDF_PbPb = {{6.1, 4.8, 6.3, 8.2}};
  std::vector<std::vector<Float_t>> syst80100_PDF_PbPb = {{4.9, 4.6, 6.7, 3.9}};
  std::vector<std::vector<Float_t>> syst100999_PDF_PbPb = {{6.4, 6.8, 7.0, 9.5}};
  std::vector<std::vector<Float_t>> syst60999_PDF_ratio = {{2.0, 3.0, 1.9, 8.2},
                                                           {2.5, 2.3, 6.5, 7.2}};
  std::vector<std::vector<Float_t>> syst6080_PDF_ratio = {{2.4, 1.9, 4.8, 5.5}};
  std::vector<std::vector<Float_t>> syst80100_PDF_ratio = {{1.5, 1.6, 3.6, 1.1}};
  std::vector<std::vector<Float_t>> syst100999_PDF_ratio = {{3.3, 3.3, 3.8, 7.3}};

  // non-closure
  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_pp = {{6.5, 0.5, 2.6, 3.3},
                                                               {2.2, 6.9, 14.7, 14.9}};
  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_PbPb = {{3.4, 1.3, 0.6, 0.7},
                                                                 {3.9, 8.4, 14.4, 15.6}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_pp = {{5.4, 5.6, 12.1, 12.7}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_pp = {{5.7, 6.5, 10.3, 10.5}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_pp = {{5.6, 6.4, 8.1, 7.4}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_PbPb = {{7.8, 6.5, 12.7, 14.2}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_PbPb = {{9.6, 8.7, 14.9, 12.0}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_PbPb = {{11.5, 12.2, 14.1, 10.3}};

  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_ratio = {{2.7, 1.8, 2.1, 4.3},
                                                                  {1.7, 1.7, 0.5, 0.9}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_ratio = {{2.2, 1.0, 0.9, 2.1}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_ratio = {{3.4, 2.6, 5.8, 1.9}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_ratio = {{5.4, 6.7, 7.1, 3.4}};

  // cut variation
  std::vector<Float_t> syst_CUT_pp = {3.6, 0.5};
  std::vector<Float_t> syst_CUT_PbPb = {3.5, 2.7};

  //
  std::vector<std::vector<Float_t>>* syst_SCALE_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_SCALE_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_RESO_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_RESO_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_PDF_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_PDF_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_PDF_ratio = 0;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_ratio = 0;  

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
        syst_NONCLOSURE_ratio = &syst60999_NONCLOSURE_ratio;
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
        syst_NONCLOSURE_ratio = &syst6080_NONCLOSURE_ratio;
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
        syst_NONCLOSURE_ratio = &syst80100_NONCLOSURE_ratio;
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
        syst_NONCLOSURE_ratio = &syst100999_NONCLOSURE_ratio;
        return 0;
      }
    std::cout<<"error: invalid jetptmin or jetptmax"<<std::endl;
    return 1;
  }

  Float_t getsyst(int ibinpt, int ibindr, Option_t* option)
  {
    TString opt  = option;
    Float_t syst = 0;

    if(!syst_SCALE_pp || !syst_SCALE_PbPb || !syst_RESO_pp || !syst_RESO_PbPb || !syst_PDF_pp || !syst_PDF_PbPb || !syst_NONCLOSURE_pp || !syst_NONCLOSURE_PbPb) 
      { std::cout<<"error: init syst first."<<std::endl; return -1; }

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
          syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt] + 
          syst_SCALE_PbPb->at(ibinpt).at(ibindr) * syst_SCALE_PbPb->at(ibinpt).at(ibindr) + 
          syst_RESO_PbPb->at(ibinpt).at(ibindr) * syst_RESO_PbPb->at(ibinpt).at(ibindr) + 

          syst_NONCLOSURE_ratio->at(ibinpt).at(ibindr) * syst_NONCLOSURE_ratio->at(ibinpt).at(ibindr) + 
          syst_PDF_ratio->at(ibinpt).at(ibindr) * syst_PDF_ratio->at(ibinpt).at(ibindr);        
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
