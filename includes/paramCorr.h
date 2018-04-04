#ifndef _PARAMCORR_H_
#define _PARAMCORR_H_

#include <vector>

#ifndef _JTPTBINS
#define _JTPTBINS
Float_t jtptBins[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 1000};
const int nJtptBins = sizeof(jtptBins)/sizeof(jtptBins[0])-1;
#endif
#ifndef _RESOJTPTBINS
#define _RESOJTPTBINS
Float_t resojtptBins[] = {10, 20, 30, 40, 50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 250, 300};
const int nResoJtptBins = sizeof(resojtptBins)/sizeof(resojtptBins[0])-1;
#endif
#ifndef _RESOJTDRBINS
#define _RESOJTDRBINS
Float_t resojtdrBins[] = {0, 0.01, 0.03, 0.05, 0.07, 0.1, 0.15, 0.20, 0.25, 0.30, 0.40, 0.50, 0.60, 0.70};
const int nResoJtdrBins = sizeof(resojtdrBins)/sizeof(resojtdrBins[0])-1;
#endif

Float_t centBins[] = {0, 30, 100};
const int NCentBins = sizeof(centBins)/sizeof(centBins[0])-1;
int nCentBins = 0;

Float_t param0fResoPt_pp_param = 0.0757855;
Float_t param0fResoPt_pp_err = 0.000351793;

Float_t param0fResoPtCorr_pp_param = 0.0776852;
Float_t param0fResoPtCorr_pp_err = 0.000245307;
Float_t param0fResoPtFfJecCorr_pp_param = 0.0720245;
Float_t param0fResoPtFfJecCorr_pp_err = 0.000453406;

Float_t param1fResoPt_peri_param = 1.24604;
Float_t param1fResoPt_peri_err = 0.00527129;

Float_t param1fResoPtCorr_peri_param = 1.1766;
Float_t param1fResoPtCorr_peri_err = 0.00583449;
Float_t param1fResoPtFfJecCorr_peri_param = 1.06791;
Float_t param1fResoPtFfJecCorr_peri_err = 0.0139354;


// fScalePt
// [0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)
// fReso
// sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))

// pp
std::vector<std::vector<Float_t>> paramfScaleRecoPt_pp = {{1.00213, 0.371503, 1.69773, 0}};

std::vector<std::vector<Float_t>> paramfScalePt_pp = {{1.00015, -0.21315, 1.82462, 0}};
std::vector<std::vector<Float_t>> paramfResoPt_pp = {{0.0766372, 0.825332, 0}};
std::vector<std::vector<Float_t>> paramfResoPtCorr_pp = {{0.0775148, 0.824444, 0}};
std::vector<std::vector<Float_t>> paramfResoPhi_pp = {{0.00357677, 0.0517923, 0}};
std::vector<std::vector<Float_t>> paramfResoEta_pp = {{-0.0026966, -0.03799, -4.0313e-05}};
std::vector<std::vector<Float_t>> paramfScalePtFfCorr_pp = {{0.969778, 0.221112, -5.5763, 85.0571}};
std::vector<std::vector<Float_t>> paramfResoPtFfJecCorr_pp = {{0.0718088, 0.871882, 0}};

std::vector<std::vector<Float_t>> paramfScalePtQ_pp = {{1.01219, -0.131363, 2.16967, 0}};
std::vector<std::vector<Float_t>> paramfScalePtG_pp = {{0.974809, 0.025065, 0.783917, 0}};

// PbPb
std::vector<std::vector<Float_t>> paramfScaleRecoPt_PbPb = {{0.98, 1.51804, -8.57594, 483.001},
                                                            {0.98, 1.48117, -9.94075, 333.871}};

std::vector<std::vector<Float_t>> paramfScalePt_PbPb = {{0.986528, 0.393473, -10.2676, 275.712},
                                                        {0.967475, 0.794111, -10.6019, 208.91}};
std::vector<std::vector<Float_t>> paramfResoPt_PbPb = {{0.0761373, 1.25131, 6.3818},
                                                       {0.0754337, 1.34341, 0}};
std::vector<std::vector<Float_t>> paramfResoPtCorr_PbPb = {{0.0774399, 1.49503, 7.84127},
                                                           {0.0774399, 1.21844, 5.41395}};
std::vector<std::vector<Float_t>> paramfResoPhi_PbPb = {{0.0165147, 0.0822335, 1.3887},
                                                        {0.0161443, 0.0267169, 1.02173}};
std::vector<std::vector<Float_t>> paramfResoEta_PbPb = {{0.0166437, 3.81913e-06, 1.33787},
                                                        {0.0158205, -1.00767e-06, 0.860816}};
std::vector<std::vector<Float_t>> paramfScalePtFfCorr_PbPb = {{0.88159, 3.10849, -36.6637, 490.326},
                                                              {0.918543, 1.76715, -20.8582, 233.459}};
std::vector<std::vector<Float_t>> paramfResoPtFfJecCorr_PbPb = {{0.0724779, 1.08185, 12.4263},
                                                                {0.0724779, 0.992695, 8.18682}};

std::vector<std::vector<Float_t>> paramfScalePtQ_PbPb = {{0.95, 1.85957, -15.355, 308.413},
                                                         {0.95, 1.72989, -13.3642, 221.901}};
std::vector<std::vector<Float_t>> paramfScalePtG_PbPb = {{0.95, 0.786854, -14.4104, 354.875},
                                                         {0.95, 0.662886, -9.84546, 200.487}};

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


// 10-300 GeV

std::vector<std::vector<Float_t>> paramRealfP0_pp = {{98.6751, 108.998, 90.5642, 86.6141, 111.011, 152.648, 162.521, 199.715, 215.724, 239.721, 240.621, 236.863, 253.421, 270.582, 264.629, 265.322, 275.36, 296.57, 281.735, 275.677, 285.389, 282.213, 286.643, 287.513, 298.756, 251.985, 254.503, 286.414, 275.203, 275.349}};
std::vector<std::vector<Float_t>> paramRealfP1_pp = {{-0.0115014, -0.0105634, -0.0129491, -0.013636, -0.0104285, -0.00740854, -0.00693307, -0.00556621, -0.00513244, -0.00459263, -0.00457967, -0.00465694, -0.00433162, -0.00404367, -0.0041433, -0.00413517, -0.00397553, -0.00367438, -0.00388082, -0.00397447, -0.00382195, -0.00387364, -0.003808, -0.00380021, -0.00364362, -0.00436654, -0.00432931, -0.00380513, -0.00397303, -0.00397281}};

std::vector<std::vector<Float_t>> paramRealfP0_PbPb = {{961.768, 3054.19, 1371.36, 57.3097, 139.657, 141.49, 203.308, 141.8, 116.774, 122.752, 173.82, 142.837, 172.441, 144.505, 155.111, 159.242, 154.541, 183.67, 163.262, 177.857, 167.652, 175.284, 177.907, 182.322, 194.148, 185.304, 194.612, 282.808, 228.298, 186.223},
                                                       {306.944, 40.8062, 30.8533, 40.3039, 54.6585, 58.1898, 72.7721, 73.0693, 86.2406, 93.1925, 101.005, 105.218, 113.257, 126.224, 132.741, 139.204, 154.253, 141.102, 155.727, 153.869, 161.691, 158.711, 165.887, 161.211, 165.776, 155.12, 196.993, 196.329, 175.513, 194.314}};
std::vector<std::vector<Float_t>> paramRealfP1_PbPb = {{-0.00135301, -0.000426067, -0.00095073, -0.0233099, -0.00865589, -0.00835643, -0.00565049, -0.00816568, -0.0100883, -0.00951828, -0.00652992, -0.00802009, -0.00656803, -0.00791513, -0.00736137, -0.00716083, -0.00737767, -0.00610633, -0.00696469, -0.00633351, -0.0067206, -0.00641927, -0.00629879, -0.00615917, -0.00571709, -0.00603286, -0.00571225, -0.0038419, -0.004803, -0.00598722},
                                                       {-0.00424261, -0.0327413, -0.0460583, -0.0325904, -0.0226429, -0.0210882, -0.0164534, -0.0165006, -0.0137523, -0.0126774, -0.0116085, -0.0111734, -0.0102658, -0.00913629, -0.00866415, -0.00821791, -0.0073241, -0.00809069, -0.00725392, -0.0073519, -0.00699388, -0.00711468, -0.00678149, -0.00700057, -0.00677408, -0.00729401, -0.00561325, -0.00563126, -0.00637371, -0.00569402}};

#endif
