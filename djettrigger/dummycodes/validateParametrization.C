#include "../triggertables.h"
#include "../utilitiesturnonstudy.h"

void validateParametrization(){
  initialiseWeights();


TFile*fcross=new TFile("fcross.root","recreate");  
TF1 *myfL1[samples_][ntriggers_];
  TF1 *myfHLT[samples_][ntriggers_];
	for (int index=0;index<samples_;index++){
		for (int indextriggers=0;indextriggers<ntriggers_;indextriggers++){
		//cout<<expmyL1test[index][indextriggers].Data()<<endl;
		//cout<<expmyHLTtest[index][indextriggers].Data()<<endl;
		//cout<<expmyL1final[index][indextriggers].Data()<<endl;
		//cout<<expmyHLTfinal[index][indextriggers].Data()<<endl;
		cout<<expmyweightL1final[index][indextriggers].Data()<<endl;
		cout<<expmyweightHLTfinal[index][indextriggers].Data()<<endl;
		  myfL1[index][indextriggers]= new TF1("myfL1",expmyL1test[index][indextriggers].Data(),0,1000);
		  myfHLT[index][indextriggers]= new TF1("myfHLT",expmyHLTtest[index][indextriggers].Data(),0,1000);
          myfL1[index][indextriggers]->Write(Form("myfL1_%s",nametriggerselectiontagtriggers[index][indextriggers].Data()));		    		
          myfHLT[index][indextriggers]->Write(Form("myfHLT_%s",nametriggerselectiontagtriggers[index][indextriggers].Data()));		    		
        }
    }
}