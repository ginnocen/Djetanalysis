#include "TMath.h"

TString functionalFormTurnOn= "([3]*TMath::Erf(x*[1]+[2])*0.5*(1-[0])+0.5*(1+[0]))";
TString functionalFormTurnOnShifted= "([3]*TMath::Erf((x+%f)*[1]+[2])*0.5*(1-[0])+0.5*(1+[0]))";

TString functionalFormTurnOnTest= "(%f*TMath::Erf(x*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";
TString functionalFormTurnOnTestShifted= "(%f*TMath::Erf((x+40)*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";

TString functionalFormTurnOnFinal= "(%f*TMath::Erf(jetpt_akpu3pf[0]*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";
TString functionalFormTurnOnFinalShifted= "(%f*TMath::Erf((jetpt_akpu3pf[0]+40)*%f+%f)*0.5*(1-%f)+0.5*(1+%f))";

const int samples_=2;
const int ntriggers_=4;

 
double a0L1[samples_][ntriggers_]={{0,-0.00363706,-0.0150987,0},{0,-0.0121254,-0.0482678,-0.0644453}};
double a1L1[samples_][ntriggers_]={{0,0.0798612,0.0849793,0},{0,0.0828111,0.0717909,0.0609877}};
double a2L1[samples_][ntriggers_]={{0,-2.60536,-3.26176,0},{0,-3.4634,-4.24326,-4.43416}};
double a3L1[samples_][ntriggers_]={{0,0.995534,0.970328,0},{0,0.979284,0.907791,0.878779}};
double a0HLT[samples_][ntriggers_]={{0,-0.0138927,-0.0215687,0},{0,0.0272289,-0.0202727,-0.0234813}};
double a1HLT[samples_][ntriggers_]={{0,0.113385,0.101078,0},{0,0.111628,0.0593221,0.0528735}};
double a2HLT[samples_][ntriggers_]={{0,-6.44713,-7.81463,0},{0,-5.48997,-4.33808,-4.98271}};
double a3HLT[samples_][ntriggers_]={{0,0.972536,0.956368,0},{0,0.999846,0.942634,0.942673}};

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
    expmyHLTtest[1][1]=Form(functionalFormTurnOnTestShifted.Data(),a3HLT[1][3],a1HLT[1][3],a2HLT[1][3],a0HLT[1][3],a0HLT[1][3]);
    expmyHLTfinal[1][1]=Form(functionalFormTurnOnFinalShifted.Data(),a3HLT[1][3],a1HLT[1][3],a2HLT[1][3],a0HLT[1][3],a0HLT[1][3]);
    
	for (int index=0;index<samples_;index++){
		for (int indextriggers=0;indextriggers<ntriggers_;indextriggers++){
		expmyweightL1final[index][indextriggers]=Form("1./%s*(jeteta_akpu3pf[0]<1.6&&jetpt_akpu3pf[0]>%f)",expmyL1final[index][indextriggers].Data(),mythresholds[index][indextriggers]);        
		expmyweightHLTfinal[index][indextriggers]=Form("1./%s*(jeteta_akpu3pf[0]<1.6&&jetpt_akpu3pf[0]>%f)",expmyHLTfinal[index][indextriggers].Data(),mythresholds[index][indextriggers]);        
        }
    }   
}

double efficiencyweight(int indexsample, int indextrigger, double jetptmin, double ptleadingjet){
  std::cout<<"I AM USING EFF WEIGTHS"<<std::endl;
  double totaleff=1;
  double weight=0;
  double l1eff=0;
  double hlteff=0;
    
  l1eff=a3L1[indexsample][indextrigger]*TMath::Erf(ptleadingjet*a1L1[indexsample][indextrigger]+a2L1[indexsample][indextrigger])*0.5*(1-a0L1[indexsample][indextrigger])+0.5*(1+a0L1[indexsample][indextrigger]);
  hlteff=a3HLT[indexsample][indextrigger]*TMath::Erf(ptleadingjet*a1HLT[indexsample][indextrigger]+a2HLT[indexsample][indextrigger])*0.5*(1-a0HLT[indexsample][indextrigger])+0.5*(1+a0HLT[indexsample][indextrigger]);
 
  if (indexsample==1 && indextrigger==1){
      hlteff=a3HLT[indexsample][3]*TMath::Erf((ptleadingjet+40)*a1HLT[indexsample][3]+a2HLT[indexsample][3])*0.5*(1-a0HLT[indexsample][3])+0.5*(1+a0HLT[indexsample][3]);    
    }
  totaleff=totaleff*l1eff*hlteff;
  weight=1./totaleff;
  return weight;
  
}
