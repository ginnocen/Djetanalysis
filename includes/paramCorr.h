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


// fP0
// [0]-exp([1]+[2]*x)
std::vector<std::vector<Float_t>> paramfP0_pp = {{316.858, 5.75719, -0.0164776}};
std::vector<std::vector<Float_t>> paramfP0_PbPb = {{227.034, 5.271, -0.00581757},
                                                   {244.217, 5.53904, -0.00594099}};
// std::vector<std::vector<Float_t>> paramfP0_pp = {{308.863, 3.86902, 0.0451719, -0.000624834}};
// std::vector<std::vector<Float_t>> paramfP0_PbPb = {{187.046, 4.81753, -0.000517769, -7.17011e-05},
//                                                    {194.423, 5.23655, -0.00425428, 5.02585e-05}};

// fP1
// [0]-exp([1]+[2]*x+[3]*x*x)
std::vector<std::vector<Float_t>> paramfP1_pp = {{-0.00336493, -7.13976, 0.0566976, -0.000624834}};
std::vector<std::vector<Float_t>> paramfP1_PbPb = {{-0.00599937, -4.59462, -0.00440119, -7.17011e-05},
                                                   {-0.00525996, -2.73032, -0.0304137, 5.02585e-05}};

#endif
