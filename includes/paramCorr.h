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
std::vector<std::vector<Float_t>> paramfScalePt_pp = {{0.99, -0.09, 1.26, 0}};
std::vector<std::vector<Float_t>> paramfScalePt_PbPb = {{0.98, 0.86, -15.22, 372.09},
                                                        {0.98, 0.79, -10.42, 237.93}};

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


// fP0: [0]-exp([1]+[2]*x)
// fP1: [0]+[3]*x-exp([1]+[2]*x)
// pp
std::vector<std::vector<Float_t>> paramfP0_pp = {{284.292, 6.24451, -0.0208096, 3.25401e-12}};
std::vector<std::vector<Float_t>> paramfP1_pp = {{-0.00401379, -2.76225, -0.0423297, 4.14402e-07}};
// PbPb
std::vector<std::vector<Float_t>> paramfP0_PbPb = {{74.7742, 7.06194, -0.0753196, 0.40824},
                                                   {257.139, 5.60937, -0.00512358, 8.76003e-11}};
std::vector<std::vector<Float_t>> paramfP1_PbPb = {{-0.0104941, -2.69602, -0.0404066, 1.63857e-05},
                                                   {-0.0107106, -2.07119, -0.0361938, 1.7809e-05}};

#endif
