#ifndef _PARAMCORR_H_
#define _PARAMCORR_H_

#include <vector>

// fScalePt
// [0]+[1]/TMath::Sqrt(x)+[2]/x
std::vector<std::vector<Float_t>> paramfScalePt_pp = {{1.00, -0.13, 2.08}};
std::vector<std::vector<Float_t>> paramfScalePt_PbPb = {{1.19, -3.96, 15.88},
                                                        {1.10, -2.17, 9.33}};

#endif
