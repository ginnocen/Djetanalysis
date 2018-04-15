#ifndef CORRFACTOR_
#define CORRFACTOR_

#include <vector>

// ! jet eta 0-1.6 (2018.4.14)

std::vector<std::vector<Float_t>> corrFactor60999_pp = {{1.12979, 1.01046, 0.948506, 0.93475},
                                                        {1.04303, 0.861068, 0.705473, 0.701208}};
std::vector<std::vector<Float_t>> corrFactor60999_PbPb = {{1.06886, 0.973969, 0.988284, 1.01432},
                                                          {1.07777, 0.832383, 0.712521, 0.688956}};
std::vector<std::vector<Float_t>> corrFactor6080_pp = {{1.10778, 0.887859, 0.758808, 0.746809}};
std::vector<std::vector<Float_t>> corrFactor80100_pp = {{1.11477, 0.870335, 0.794222, 0.790284}};
std::vector<std::vector<Float_t>> corrFactor100999_pp = {{1.11133, 0.872048, 0.837677, 0.852308}};
std::vector<std::vector<Float_t>> corrFactor6080_PbPb = {{1.15596, 0.869954, 0.745743, 0.715059}};
std::vector<std::vector<Float_t>> corrFactor80100_PbPb = {{1.19136, 0.825004, 0.701352, 0.760292}};
std::vector<std::vector<Float_t>> corrFactor100999_PbPb = {{1.2307, 0.755798, 0.718435, 0.793605}};


std::vector<std::vector<Float_t>> corrFactorSg60999_pp = {{1.0883, 1.01309, 0.965769, 0.964814},
                                                          {1.00857, 0.981331, 0.924256, 0.941387}};
std::vector<std::vector<Float_t>> corrFactorSg60999_PbPb = {{1.07275, 1.04543, 0.952244, 0.902155},
                                                            {0.887237, 1.59693, 1.04481, 0.906597}};
std::vector<std::vector<Float_t>> corrFactorSg6080_pp = {{1.00427, 1.00214, 0.984566, 0.997482}};
std::vector<std::vector<Float_t>> corrFactorSg80100_pp = {{1.00245, 1.00489, 0.9892, 0.969783}};
std::vector<std::vector<Float_t>> corrFactorSg100999_pp = {{1.00287, 1.0143, 0.982221, 0.994805}};
std::vector<std::vector<Float_t>> corrFactorSg6080_PbPb = {{0.86001, 1.41183, 1.06359, 1.0053}};
std::vector<std::vector<Float_t>> corrFactorSg80100_PbPb = {{0.904063, 1.3102, 1.0064, 0.972523}};
std::vector<std::vector<Float_t>> corrFactorSg100999_PbPb = {{0.925243, 1.20831, 1.0167, 0.98711}};

#endif
