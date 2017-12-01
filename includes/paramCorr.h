#ifndef _PARAMCORR_H_
#define _PARAMCORR_H_

#include <vector>

// fScalePt
// [0]+[1]/TMath::Sqrt(x)+[2]/x
std::vector<std::vector<Float_t>> paramfScalePt_pp = {{1.00, -0.13, 2.08}};
std::vector<std::vector<Float_t>> paramfScalePt_PbPb = {{1.19, -3.96, 15.88},
                                                        {1.10, -2.17, 9.33}};

// fResoPt
// [0]*[0]+[1]*[1]/x+[2]*[2]/(x*x)
std::vector<std::vector<Float_t>> paramfResoPt_pp = {{0.077, 0.743, 0}};
std::vector<std::vector<Float_t>> paramfResoPt_PbPb = {{0.056, 1.573, 0},
                                                       {0.072, 1.148, 0}};
std::vector<std::vector<Float_t>> paramfResoPtCorr_pp = {{0.087, 0.545, 0}};
std::vector<std::vector<Float_t>> paramfResoPtCorr_PbPb = {{0.055, 1.679, 0},
                                                           {0.074, 1.192, 0}};
std::vector<std::vector<Float_t>> paramfResoPhi_pp = {{0.002, 0.079, 0}};
std::vector<std::vector<Float_t>> paramfResoPhi_PbPb = {{0.015, 0.139, 0.927},
                                                        {0.015, 0.095, 0.583}};
std::vector<std::vector<Float_t>> paramfResoEta_pp = {{0.001, 0.060, 0}};
std::vector<std::vector<Float_t>> paramfResoEta_PbPb = {{0.017, 0.000, 1.155},
                                                        {0.015, 0.000, 0.662}};


#endif
