TString functionalFormTurnOn= "[3]*TMath::Erf(x*[1]+[2])*0.5*(1-[0])+0.5*(1+[0])";
TString functionalFormTurnOnShifted= "[3]*TMath::Erf((x+%f)*[1]+[2])*0.5*(1-[0])+0.5*(1+[0])";

  double a0L1[samples][ntriggers]={{7.0734e-2, 7.0734e-2, 7.0734e-2, 7.0734e-2},{7.0734e-2, 7.0734e-2, 7.0734e-2, 7.0734e-2}};
  double a1L1[samples][ntriggers]={{6.76907e-2,6.76907e-2,6.76907e-2,6.76907e-2},{6.76907e-2,6.76907e-2,6.76907e-2,6.76907e-2}};
  double a2L1[samples][ntriggers]={{-2.31850,-2.31850,-2.31850,-2.31850},{-2.31850,-2.31850,-2.31850,-2.31850}};
  double a3L1[samples][ntriggers]={{1.,1.,1.,1.},{1.,1.,1.,1.}};

  double a0HLT[samples][ntriggers]={{7.0734e-2, 7.0734e-2, 7.0734e-2, 7.0734e-2},{7.0734e-2, 7.0734e-2, 7.0734e-2, 7.0734e-2}};
  double a1HLT[samples][ntriggers]={{6.76907e-2,6.76907e-2,6.76907e-2,6.76907e-2},{6.76907e-2,6.76907e-2,6.76907e-2,6.76907e-2}};
  double a2HLT[samples][ntriggers]={{-2.31850,-2.31850,-2.31850,-2.31850},{-2.31850,-2.31850,-2.31850,-2.31850}};
  double a3HLT[samples][ntriggers]={{1.,1.,1.,1.},{1.,1.,1.,1.}};
 