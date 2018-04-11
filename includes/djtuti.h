#ifndef DJTUTI_H_
#define DJTUTI_H_

namespace djtuti
{
  float calr(float Dphi, float Deta, float jetphi, float jeteta, int opt)
  {
    Float_t deltaphi = TMath::ACos(TMath::Cos(Dphi - jetphi));
    Float_t deltaeta = Deta - jeteta;
    Float_t deltaetaref = Deta + jeteta;
    Float_t deltaR[2] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)),
                         (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
    return deltaR[opt];
  }
}

#endif
