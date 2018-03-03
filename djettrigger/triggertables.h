TString functionalFormTurnOn= "([3]*TMath::Erf(x*[1]+[2])*0.5*(1-[0])+0.5*(1+[0]))";
TString functionalFormTurnOnShifted= "([3]*TMath::Erf((x+%f)*[1]+[2])*0.5*(1-[0])+0.5*(1+[0]))";

TString functionalFormTurnOnTest= "(%f*TMath::Erf(x*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";
TString functionalFormTurnOnTestShifted= "(%f*TMath::Erf((x+20)*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";

TString functionalFormTurnOnFinal= "(%f*TMath::Erf(jetpt_akpu3pf[0]*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";
TString functionalFormTurnOnFinalShifted= "(%f*TMath::Erf((jetpt_akpu3pf[0]+20)*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";

const int samples_=2;
const int ntriggers_=4;

 
double a0L1[samples_][ntriggers_]={{0,-0.00363715,-0.0150987,0},{0,-0.0121254,-0.0482677,-0.0644453}};
double a1L1[samples_][ntriggers_]={{0,0.0798612,0.0849803,0},{0,0.0828111,0.071791,0.0609877}};
double a2L1[samples_][ntriggers_]={{0,-2.60536,-3.26179,0},{0,-3.4634,-4.24326,-4.43417}};
double a3L1[samples_][ntriggers_]={{0,0.995534,0.970328,0},{0,0.979284,0.907791,0.878779}};
double a0HLT[samples_][ntriggers_]={{0,-0.0138927,-0.0215686,0},{0,0.0191054,-0.0202712,0.00341066}};
double a1HLT[samples_][ntriggers_]={{0,0.113385,0.101078,0},{0,0.0529121,0.059322,0.0490259}};
double a2HLT[samples_][ntriggers_]={{0,-6.44714,-7.81461,0},{0,-2.81107,-4.33809,-4.66902}};
double a3HLT[samples_][ntriggers_]={{0,0.972536,0.956368,0},{0,0.999976,0.942631,0.999858}};

const int nparameterfit=4;
double parametersL1fit[samples_][ntriggers_][nparameterfit];
double parametersHLTfit[samples_][ntriggers_][nparameterfit];

TString expmyL1test[samples_][ntriggers_];
TString expmyHLTtest[samples_][ntriggers_];

TString expmyL1final[samples_][ntriggers_];
TString expmyHLTfinal[samples_][ntriggers_];

TString expmyweightL1final[samples_][ntriggers_];
TString expmyweightHLTfinal[samples_][ntriggers_];

 float mythresholds[samples_][ntriggers_]={{40,60,80,100},{40,60,80,100}};


void initialiseWeights(){

	for (int index=0;index<samples_;index++){
		for (int indextriggers=0;indextriggers<ntriggers_;indextriggers++){
		  expmyL1test[index][indextriggers]=Form(functionalFormTurnOnTest.Data(),a3L1[index][indextriggers],a1L1[index][indextriggers],a2L1[index][indextriggers],a0L1[index][indextriggers],a0L1[index][indextriggers]);
		  expmyHLTtest[index][indextriggers]=Form(functionalFormTurnOnTest.Data(),a3HLT[index][indextriggers],a1HLT[index][indextriggers],a2HLT[index][indextriggers],a0HLT[index][indextriggers],a0HLT[index][indextriggers]);
		  expmyL1final[index][indextriggers]=Form(functionalFormTurnOnFinal.Data(),a3L1[index][indextriggers],a1L1[index][indextriggers],a2L1[index][indextriggers],a0L1[index][indextriggers],a0L1[index][indextriggers]);
		  expmyHLTfinal[index][indextriggers]=Form(functionalFormTurnOnFinal.Data(),a3HLT[index][indextriggers],a1HLT[index][indextriggers],a2HLT[index][indextriggers],a0HLT[index][indextriggers],a0HLT[index][indextriggers]);
        }
    }   
    expmyHLTtest[1][1]=Form(functionalFormTurnOnTestShifted.Data(),a3HLT[1][2],a1HLT[1][2],a2HLT[1][2],a0HLT[1][2],a0HLT[1][2]);
    expmyHLTfinal[1][1]=Form(functionalFormTurnOnFinalShifted.Data(),a3HLT[1][2],a1HLT[1][2],a2HLT[1][2],a0HLT[1][2],a0HLT[1][2]);
    
	for (int index=0;index<samples_;index++){
		for (int indextriggers=0;indextriggers<ntriggers_;indextriggers++){
		expmyweightL1final[index][indextriggers]=Form("1./%s*(jeteta_akpu3pf[0]<1.6&&jetpt_akpu3pf[0]>%f)",expmyL1final[index][indextriggers].Data(),mythresholds[index][indextriggers]);        
		expmyweightHLTfinal[index][indextriggers]=Form("1./%s*(jeteta_akpu3pf[0]<1.6&&jetpt_akpu3pf[0]>%f)",expmyHLTfinal[index][indextriggers].Data(),mythresholds[index][indextriggers]);        
        }
    }   
}
