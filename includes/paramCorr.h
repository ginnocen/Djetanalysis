#ifndef _PARAMCORR_H_
#define _PARAMCORR_H_

#include <vector>

Float_t param0fResoPt_pp_param = 0.068;
Float_t param0fResoPt_pp_err = 0.001;

Float_t param0fResoPtCorr_pp_param = 0.071;
Float_t param0fResoPtCorr_pp_err = 0.001;

Float_t param1fResoPt_peri_param = 1.233;
Float_t param1fResoPt_peri_err = 0.004;

Float_t param1fResoPtCorr_peri_param = 1.265;
Float_t param1fResoPtCorr_peri_err = 0.004;

// fScalePt
// [0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)
std::vector<std::vector<Float_t>> paramfScalePt_pp = {{0.99, -0.09, 1.28, 0}};
std::vector<std::vector<Float_t>> paramfScalePt_PbPb = {{0.98, 0.93, -16.39, 408.64},
                                                        {0.98, 0.85, -12.09, 291.60}};

// fResoPt
// [0]*[0]+[1]*[1]/x+[2]*[2]/(x*x)
std::vector<std::vector<Float_t>> paramfResoPt_pp = {{0.068, 0.904, 0}};
std::vector<std::vector<Float_t>> paramfResoPt_PbPb = {{0.069, 1.237, 8.558},
                                                       {0.067, 1.233, 0}};
std::vector<std::vector<Float_t>> paramfResoPtCorr_pp = {{0.071, 0.908, 0}};
std::vector<std::vector<Float_t>> paramfResoPtCorr_PbPb = {{0.072, 1.269, 9.833},
                                                           {0.070, 1.265, 0}};
std::vector<std::vector<Float_t>> paramfResoPhi_pp = {{0.000, 0.098, 0}};
std::vector<std::vector<Float_t>> paramfResoPhi_PbPb = {{0.016, 0.073, 1.302},
                                                        {0.016, 0.043, 0.874}};
std::vector<std::vector<Float_t>> paramfResoEta_pp = {{0.001, 0.073, 0}};
std::vector<std::vector<Float_t>> paramfResoEta_PbPb = {{0.016, 0.000, 1.215},
                                                        {0.015, 0.000, 0.715}};




#endif
