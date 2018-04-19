#include <vector>

std::vector<std::vector<float>> parpp(7);
std::vector<std::vector<float>> parPbPb(7);
std::vector<std::vector<float>> parerrpp(7);
std::vector<std::vector<float>> parerrPbPb(7);
std::vector<TString> varfitpp(7);
std::vector<TString> varfitPbPb(7);

Color_t colorlist[] = {kViolet-7, kGreen-1, kAzure-3, kOrange+2, kMagenta-3, kCyan-1};

void initfitpar()
{
  // Y rapidity pp, Sigma
  parpp[2] = {0.931362, 0.0207396};
  parpp[3] = {0.921729, 0.0227696, 0.0188963};
  parpp[4] = {0.916146, -0.0470373, 0.0304723, 0.0531419};
  parpp[5] = {0.901303, -0.0390099, 0.0991494, 0.045281, -0.0301266};
  parpp[6] = {0.90077, -0.058854, 0.101739, 0.0818058, -0.0318587, -0.0112095};
  parerrpp[2] = {0.0128087, 0.0178277};
  parerrpp[3] = {0.0162886, 0.0179534, 0.0197395};
  parerrpp[4] = {0.0164234, 0.0318061, 0.0202139, 0.0199868};
  parerrpp[5] = {0.0192795, 0.0322715, 0.0509064, 0.0206898, 0.0204952};
  parerrpp[6] = {0.0193072, 0.0502484, 0.0511539, 0.0738489, 0.020769, 0.0217566};

  // Y rapidity PbPb, Sigma
  parPbPb[2] = {0.909772, 0.0339521};
  parPbPb[3] = {0.918217, 0.0357167, -0.0236473};
  parPbPb[4] = {0.918321, 0.0564954, -0.0241995, -0.0194949};
  parPbPb[5] = {0.924438, 0.0558162, -0.0575597, -0.0173007, 0.0152515};
  parPbPb[6] = {0.923134, 0.0871046, -0.051395, -0.0860303, 0.0148206, 0.0215421};
  parerrPbPb[2] = {0.0173298, 0.0288642};
  parerrPbPb[3] = {0.0212576, 0.0289786, 0.0344734};
  parerrPbPb[4] = {0.0212583, 0.0451676, 0.0344857, 0.0325055};
  parerrPbPb[5] = {0.0250083, 0.0451912, 0.0796867, 0.0328471, 0.0328428};
  parerrPbPb[6] = {0.0251188, 0.0723449, 0.0804603, 0.12837, 0.032852, 0.038896};
}
