#ifndef CORRFACTOR_
#define CORRFACTOR_

#include <vector>

// ! jet eta 0-1.6, Dpt weight (2018.4.25)

std::vector<std::vector<Float_t>> corrFactor60999_pp = {{1.13193, 1.00881, 0.939681, 0.929455},
                                                        {1.04338, 0.859659, 0.701563, 0.697884}};
std::vector<std::vector<Float_t>> corrFactor60999_PbPb = {{1.06594, 0.969972, 0.990157, 1.00108},
                                                          {1.06102, 0.822581, 0.714466, 0.689699}};
std::vector<std::vector<Float_t>> corrFactor6080_pp = {{1.09409, 0.881977, 0.74707, 0.73354}};
std::vector<std::vector<Float_t>> corrFactor80100_pp = {{1.10486, 0.859414, 0.78515, 0.788794}};
std::vector<std::vector<Float_t>> corrFactor100999_pp = {{1.10374, 0.867128, 0.825832, 0.847114}};
std::vector<std::vector<Float_t>> corrFactor6080_PbPb = {{1.09312, 0.865577, 0.741024, 0.699058}};
std::vector<std::vector<Float_t>> corrFactor80100_PbPb = {{1.10628, 0.804735, 0.666163, 0.712058}};
std::vector<std::vector<Float_t>> corrFactor100999_PbPb = {{1.14406, 0.679655, 0.637097, 0.706196}};

// std::vector<std::vector<Float_t>> corrFactor60999_pp = {{1.12979, 1.01046, 0.948506, 0.93475},
//                                                         {1.04303, 0.861068, 0.705473, 0.701208}};
// std::vector<std::vector<Float_t>> corrFactor60999_PbPb = {{1.06886, 0.973969, 0.988284, 1.01432},
//                                                           {1.07777, 0.832383, 0.712521, 0.688956}};
// std::vector<std::vector<Float_t>> corrFactor6080_pp = {{1.10778, 0.887859, 0.758808, 0.746809}};
// std::vector<std::vector<Float_t>> corrFactor80100_pp = {{1.11477, 0.870335, 0.794222, 0.790284}};
// std::vector<std::vector<Float_t>> corrFactor100999_pp = {{1.11133, 0.872048, 0.837677, 0.852308}};
// std::vector<std::vector<Float_t>> corrFactor6080_PbPb = {{1.15596, 0.869954, 0.745743, 0.715059}};
// std::vector<std::vector<Float_t>> corrFactor80100_PbPb = {{1.19136, 0.825004, 0.701352, 0.760292}};
// std::vector<std::vector<Float_t>> corrFactor100999_PbPb = {{1.2307, 0.755798, 0.718435, 0.793605}};

std::vector<std::vector<Float_t>> corrFactorSg60999_pp = {{1.08766, 1.00952, 0.962299, 0.957533},
                                                          {1.00854, 0.980418, 0.926552, 0.944118}};
std::vector<std::vector<Float_t>> corrFactorSg60999_PbPb = {{1.07627, 1.05095, 0.944057, 0.900284},
                                                            {0.8831, 1.91064, 1.15496, 0.977316}};
std::vector<std::vector<Float_t>> corrFactorSg6080_pp = {{1.00492, 1.00089, 0.979408, 0.995188}};
std::vector<std::vector<Float_t>> corrFactorSg80100_pp = {{1.0017, 1.00679, 0.987734, 0.967546}};
std::vector<std::vector<Float_t>> corrFactorSg100999_pp = {{1.00052, 1.01378, 0.986423, 0.987912}};
std::vector<std::vector<Float_t>> corrFactorSg6080_PbPb = {{0.846146, 1.77416, 1.18841, 1.10423}};
std::vector<std::vector<Float_t>> corrFactorSg80100_PbPb = {{0.89093, 1.62917, 1.08892, 1.03921}};
std::vector<std::vector<Float_t>> corrFactorSg100999_PbPb = {{0.923006, 1.38538, 1.06056, 1.02257}};

// std::vector<std::vector<Float_t>> corrFactorSg60999_pp = {{1.0883, 1.01309, 0.965769, 0.964814},
//                                                           {1.00857, 0.981331, 0.924256, 0.941387}};
// std::vector<std::vector<Float_t>> corrFactorSg60999_PbPb = {{1.07275, 1.04543, 0.952244, 0.902155},
//                                                             {0.887237, 1.59693, 1.04481, 0.906597}};
// std::vector<std::vector<Float_t>> corrFactorSg6080_pp = {{1.00427, 1.00214, 0.984566, 0.997482}};
// std::vector<std::vector<Float_t>> corrFactorSg80100_pp = {{1.00245, 1.00489, 0.9892, 0.969783}};
// std::vector<std::vector<Float_t>> corrFactorSg100999_pp = {{1.00287, 1.0143, 0.982221, 0.994805}};
// std::vector<std::vector<Float_t>> corrFactorSg6080_PbPb = {{0.86001, 1.41183, 1.06359, 1.0053}};
// std::vector<std::vector<Float_t>> corrFactorSg80100_PbPb = {{0.904063, 1.3102, 1.0064, 0.972523}};
// std::vector<std::vector<Float_t>> corrFactorSg100999_PbPb = {{0.925243, 1.20831, 1.0167, 0.98711}};


// ! jet eta 0.3-1.6
// std::vector<std::vector<Float_t>> corrFactor60999_pp = {{1.15332, 1.00313, 0.944529, 0.913613},
//                                                         {1.04719, 0.844928, 0.691269, 0.684452}};
// std::vector<std::vector<Float_t>> corrFactor60999_PbPb = {{1.07022, 0.968591, 0.990932, 0.99121},
//                                                           {1.07866, 0.829344, 0.704708, 0.68494}};
// std::vector<std::vector<Float_t>> corrFactor6080_pp = {{1.11595, 0.867601, 0.755132, 0.718664}};
// std::vector<std::vector<Float_t>> corrFactor80100_pp = {{1.1204, 0.872541, 0.779175, 0.784418}};
// std::vector<std::vector<Float_t>> corrFactor100999_pp = {{1.12354, 0.868897, 0.816446, 0.845841}};
// std::vector<std::vector<Float_t>> corrFactor6080_PbPb = {{1.16282, 0.863605, 0.735227, 0.695213}};
// std::vector<std::vector<Float_t>> corrFactor80100_PbPb = {{1.19543, 0.81764, 0.700679, 0.736634}};
// std::vector<std::vector<Float_t>> corrFactor100999_PbPb = {{1.24026, 0.739893, 0.709131, 0.777169}};

// std::vector<std::vector<Float_t>> corrFactorSg60999_pp = {{0.999236, 1.00046, 1.00623, 1.00701},
//                                                           {0.99985, 1.00174, 0.998102, 0.997398}};
// std::vector<std::vector<Float_t>> corrFactorSg60999_PbPb = {{1.00607, 0.998326, 1.00262, 1.01198},
//                                                             {1.00612, 0.833406, 0.902184, 0.929127}};
// std::vector<std::vector<Float_t>> corrFactorSg6080_pp = {{0.999536, 1.00187, 1.00677, 1.00156}};
// std::vector<std::vector<Float_t>> corrFactorSg80100_pp = {{1.00122, 1.00022, 0.997523, 1.00284}};
// std::vector<std::vector<Float_t>> corrFactorSg100999_pp = {{0.99682, 1.00257, 1.0074, 1.00776}};
// std::vector<std::vector<Float_t>> corrFactorSg6080_PbPb = {{1.01578, 0.795385, 0.894044, 0.918252}};
// std::vector<std::vector<Float_t>> corrFactorSg80100_PbPb = {{1.01884, 0.804365, 0.918885, 0.92174}};
// std::vector<std::vector<Float_t>> corrFactorSg100999_PbPb = {{1.00174, 0.877935, 0.951161, 0.966611}};

#endif
