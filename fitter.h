#ifndef FITTER_H
#define FITTER_H

#include <iostream>
#include "TF1.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TLegend.h"


using namespace std;

class Dfitter{

  public:
 
  TF1*fFuncTotal;
  TF1*fFuncBackground;
  TF1*fFuncMass;
  TF1*fFuncMassSwap;

  Double_t setparam0;
  Double_t setparam1;
  Double_t setparam2;
  Double_t setparam10;
  Double_t setparam8;
  Double_t setparam9;
  Double_t fixparam1;
  Double_t minhisto;
  Double_t maxhisto;
  Double_t nbinsmasshisto;
  Double_t binwidthmass;
  
  double signal;
  Dfitter(TH1F* hMass, TH1F*hMC, TH1F*hMCswapped);
  ~Dfitter();
  TH1F*fhMass;
  TH1F*fhMC;
  TH1F*fhMCswapped;
  
  double GetSignal();
  double GetSignalError();

};

#endif
