#ifndef CORRFACTOR_
#define CORRFACTOR_

#include <vector>

// std::vector<std::vector<Float_t>>corrFactor6080_pp = {{1.13526, 0.861353, 0.758731, 0.739018}};
// std::vector<std::vector<Float_t>>corrFactor80100_pp = {{1.13437, 0.8797, 0.789466, 0.758}};
// std::vector<std::vector<Float_t>>corrFactor100999_pp = {{1.13211, 0.876474, 0.82262, 0.859951}};
// std::vector<std::vector<Float_t>>corrFactor60999_pp = {{1.17343, 1.01488, 0.951858, 0.923028},
//                                                        {1.05196, 0.825363, 0.694105, 0.739121}};

std::vector<std::vector<Float_t>> corrFactor60999_pp = {{1.15611, 0.998289, 0.936268, 0.908008},
                                                        {1.0469, 0.846123, 0.689234, 0.682908}};
std::vector<std::vector<Float_t>> corrFactor6080_pp = {{1.10122, 0.862233, 0.743225, 0.70638}};
std::vector<std::vector<Float_t>> corrFactor80100_pp = {{1.10981, 0.860823, 0.769777, 0.781874}};
std::vector<std::vector<Float_t>> corrFactor100999_pp = {{1.10917, 0.867163, 0.812123, 0.842303}};


// std::vector<std::vector<Float_t>>corrFactor6080_PbPb = {{1.10552, 0.893129, 0.900363, 0.849218}};
// std::vector<std::vector<Float_t>>corrFactor80100_PbPb = {{1.11873, 0.971808, 0.715702, 0.992708}};
// std::vector<std::vector<Float_t>>corrFactor100999_PbPb = {{1.29016, 0.706269, 0.68846, 0.741864}};
// std::vector<std::vector<Float_t>>corrFactor60999_PbPb = {{0.872042, 0.940332, 1.07469, 1.05322},
//                                                          {1.05789, 0.880384, 0.764462, 1.2871}};

std::vector<std::vector<Float_t>> corrFactor60999_PbPb = {{1.07866, 0.968363, 0.986225, 0.987687},
                                                          {1.06159, 0.821185, 0.704662, 0.685829}};
std::vector<std::vector<Float_t>> corrFactor6080_PbPb = {{1.09632, 0.862595, 0.730438, 0.687216}};
std::vector<std::vector<Float_t>> corrFactor80100_PbPb = {{1.1085, 0.801546, 0.659002, 0.679108}};
std::vector<std::vector<Float_t>> corrFactor100999_PbPb = {{1.14916, 0.667841, 0.616855, 0.691623}};

// std::vector<std::vector<Float_t>>corrFactorSg6080_pp = {{1.0114, 1.01135, 0.965177, 0.956598}};
// std::vector<std::vector<Float_t>>corrFactorSg80100_pp = {{0.999431, 1.019, 0.983467, 1.00556}};
// std::vector<std::vector<Float_t>>corrFactorSg100999_pp = {{0.998578, 1.0133, 0.995262, 0.991134}};
// std::vector<std::vector<Float_t>>corrFactorSg60999_pp = {{1.11551, 1.03504, 0.960894, 0.951966},
//                                                          {1.00967, 0.982058, 0.914683, 0.921759}};

std::vector<std::vector<Float_t>> corrFactorSg6080_pp = {{1.00967, 0.993928, 0.968999, 0.984983}};
std::vector<std::vector<Float_t>> corrFactorSg80100_pp = {{0.998328, 1.0153, 0.990716, 0.974518}};
std::vector<std::vector<Float_t>> corrFactorSg100999_pp = {{1.00199, 1.01006, 0.985599, 0.979668}};
std::vector<std::vector<Float_t>> corrFactorSg60999_pp = {{1.0938, 1.01596, 0.957365, 0.955137},
                                                          {1.01017, 0.971012, 0.929652, 0.939074}};

// std::vector<std::vector<Float_t>>corrFactorSg6080_PbPb = {{0.837279, 1.54263, 1.03652, 0.994842}};
// std::vector<std::vector<Float_t>>corrFactorSg80100_PbPb = {{0.894661, 1.33485, 1.0368, 0.927311}};
// std::vector<std::vector<Float_t>>corrFactorSg100999_PbPb = {{0.915823, 1.24216, 1.0335, 0.958818}};
// std::vector<std::vector<Float_t>>corrFactorSg60999_PbPb = {{1.15877, 1.08516, 0.938007, 0.888238},
//                                                            {0.86295, 1.78793, 1.03848, 0.842844}};

std::vector<std::vector<Float_t>> corrFactorSg6080_PbPb = {{0.844738, 1.77868, 1.19594, 1.09728}};
std::vector<std::vector<Float_t>> corrFactorSg80100_PbPb = {{0.893523, 1.60068, 1.09043, 1.06662}};
std::vector<std::vector<Float_t>> corrFactorSg100999_PbPb = {{0.923333, 1.38376, 1.06558, 1.01112}};
std::vector<std::vector<Float_t>> corrFactorSg60999_PbPb = {{1.06463, 1.04917, 0.948894, 0.896172},
                                                            {0.883788, 1.90865, 1.15165, 0.978647}};

#endif
