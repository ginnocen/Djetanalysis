#ifndef SYSTMETICS_
#define SYSTMETICS_

#include <vector>

namespace djtsyst
{
  std::vector<std::vector<Float_t>> syst_SCALE_pp = {{1.9, 1.0, 4.7, 3.5},
                                                     {0.3, 1.7, 6.9, 3.5}};
  std::vector<std::vector<Float_t>> syst_SCALE_PbPb = {{8.0, 4.8, 5.7, 1.7},
                                                       {0.3, 1.1, 1.3, 21.8}};

  std::vector<std::vector<Float_t>> syst_RESO_pp = {{1.6, 1.7, 1, 3.1},
                                                    {0.1, 0.5, 1, 1.1}};
  std::vector<std::vector<Float_t>> syst_RESO_PbPb = {{1.7, 5.6, 6.9, 1.5},
                                                      {0.8, 2.3, 0.2, 8.4}};

  std::vector<std::vector<Float_t>> syst_PDF_pp = {{9.3, 9.2, 6.3, 8.1},
                                                   {2.6, 7.7, 6.5, 8.6}};
  std::vector<std::vector<Float_t>> syst_PDF_PbPb = {{9.2, 15.1, 8.6, 8.0},
                                                     {3.3, 9.3, 20.9, 18.3}};
  std::vector<std::vector<Float_t>> syst_PDF_ratio = {{1.3, 6.5, 2.4, 2.0},
                                                      {0.9, 6.5, 15.3, 10.5}};

  std::vector<std::vector<Float_t>> syst_NONCLOSURE_pp = {{10.4, 6.5, 11.9, 14.6},
                                                          {0.6, 3.5, 18.0, 19.5}};
  std::vector<std::vector<Float_t>> syst_NONCLOSURE_PbPb = {{1.7, 0.4, 7.2, 4.4},
                                                            {5.0, 11.1, 2.4, 1.2}};

  std::vector<Float_t> syst_CUT_pp = {3.6, 0.5};
  std::vector<Float_t> syst_CUT_PbPb = {3.5, 2.7};

  //

  Float_t getsyst(int ibinpt, int ibindr, Option_t* option)
  {
    TString opt  = option;
    Float_t syst = 0;
    if(opt=="pp")
      {
        syst += syst_CUT_pp[ibinpt] * syst_CUT_pp[ibinpt] + 
          syst_SCALE_pp[ibinpt].at(ibindr) * syst_SCALE_pp[ibinpt].at(ibindr) + 
          syst_RESO_pp[ibinpt].at(ibindr) * syst_RESO_pp[ibinpt].at(ibindr) + 
          syst_PDF_pp[ibinpt].at(ibindr) * syst_PDF_pp[ibinpt].at(ibindr) + 
          syst_NONCLOSURE_pp[ibinpt].at(ibindr) * syst_NONCLOSURE_pp[ibinpt].at(ibindr);
      }
    else if(opt=="PbPb")
      {
        syst += syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt] + 
          syst_SCALE_PbPb[ibinpt].at(ibindr) * syst_SCALE_PbPb[ibinpt].at(ibindr) + 
          syst_RESO_PbPb[ibinpt].at(ibindr) * syst_RESO_PbPb[ibinpt].at(ibindr) + 
          syst_PDF_PbPb[ibinpt].at(ibindr) * syst_PDF_PbPb[ibinpt].at(ibindr) + 
          syst_NONCLOSURE_PbPb[ibinpt].at(ibindr) * syst_NONCLOSURE_PbPb[ibinpt].at(ibindr);
      }
    else if(opt=="ratio")
      {
        syst += syst_CUT_pp[ibinpt] * syst_CUT_pp[ibinpt] + 
          syst_SCALE_pp[ibinpt].at(ibindr) * syst_SCALE_pp[ibinpt].at(ibindr) + 
          syst_RESO_pp[ibinpt].at(ibindr) * syst_RESO_pp[ibinpt].at(ibindr) + 
          syst_NONCLOSURE_pp[ibinpt].at(ibindr) * syst_NONCLOSURE_pp[ibinpt].at(ibindr) +
          syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt] + 
          syst_SCALE_PbPb[ibinpt].at(ibindr) * syst_SCALE_PbPb[ibinpt].at(ibindr) + 
          syst_RESO_PbPb[ibinpt].at(ibindr) * syst_RESO_PbPb[ibinpt].at(ibindr) + 
          syst_NONCLOSURE_PbPb[ibinpt].at(ibindr) * syst_NONCLOSURE_PbPb[ibinpt].at(ibindr) +

          syst_PDF_ratio[ibinpt].at(ibindr) * syst_PDF_PbPb[ibinpt].at(ibindr);        
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
