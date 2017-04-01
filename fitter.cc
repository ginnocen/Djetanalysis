#include "fitter.h"

Dfitter::Dfitter(TH1F* hMass, TH1F*hMC, TH1F*hMCswapped){
  fhMass=(TH1F*)hMass->Clone();
  fhMC=(TH1F*)hMC->Clone();
  fhMCswapped=(TH1F*)hMCswapped->Clone();

  setparam0=100.;
  setparam1=1.865;
  setparam2=0.03;
  setparam0=100.;
  setparam8=0.1;
  setparam9=0.1;
  fixparam1=1.865;
  minhisto=1.7;
  maxhisto=2.0;
  nbinsmasshisto=60;
  binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;
}

void Dfitter::fit(){

  fFuncTotal = new TF1("fFuncTotal","[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);
  fFuncBackground = new TF1("fFuncBackground","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  fFuncMass = new TF1("fmass","[0]*([3]*([4]*Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  fFuncMassSwap = new TF1("fFuncMassSwap","[0]*(1-[2])*Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
    
  fFuncTotal->SetParLimits(4,-1000,1000);
  fFuncTotal->SetParLimits(10,0.001,0.05);
  fFuncTotal->SetParLimits(2,0.01,0.5);
  fFuncTotal->SetParLimits(8,0.02,0.2);
  fFuncTotal->SetParLimits(7,0,1);
  fFuncTotal->SetParLimits(9,0,1);
  
  fFuncTotal->SetParameter(0,setparam0);
  fFuncTotal->SetParameter(1,setparam1);
  fFuncTotal->SetParameter(2,setparam2);
  fFuncTotal->SetParameter(10,setparam10);
  fFuncTotal->SetParameter(9,setparam9);

  fFuncTotal->FixParameter(8,setparam8);
  fFuncTotal->FixParameter(7,1);
  fFuncTotal->FixParameter(1,fixparam1);
  fFuncTotal->FixParameter(3,0);
  fFuncTotal->FixParameter(4,0);
  fFuncTotal->FixParameter(5,0);
  fFuncTotal->FixParameter(6,0);
  fFuncTotal->FixParameter(11,0);
  fhMass->GetEntries();
  
  fhMC->Fit("fFuncTotal","q","",minhisto,maxhisto);
  fhMC->Fit("fFuncTotal","q","",minhisto,maxhisto);
  fFuncTotal->ReleaseParameter(1);
  fhMC->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMC->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMC->Fit("fFuncTotal","L m","",minhisto,maxhisto);
  
  fFuncTotal->FixParameter(1,fFuncTotal->GetParameter(1));
  fFuncTotal->FixParameter(2,fFuncTotal->GetParameter(2));
  fFuncTotal->FixParameter(10,fFuncTotal->GetParameter(10));
  fFuncTotal->FixParameter(9,fFuncTotal->GetParameter(9));
  fFuncTotal->FixParameter(7,0);
  fFuncTotal->ReleaseParameter(8);
  fFuncTotal->SetParameter(8,setparam8);
  
  fhMCswapped->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMCswapped->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMCswapped->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMCswapped->Fit("fFuncTotal","L m","",minhisto,maxhisto);
  
  fFuncTotal->FixParameter(7,fhMC->Integral(0,1000)/(fhMCswapped->Integral(0,1000)+fhMC->Integral(0,1000)));
  fFuncTotal->FixParameter(8,fFuncTotal->GetParameter(8));
  fFuncTotal->ReleaseParameter(3);
  fFuncTotal->ReleaseParameter(4);
  fFuncTotal->ReleaseParameter(5);
  fFuncTotal->ReleaseParameter(6);

  fFuncTotal->SetLineColor(kRed);
  
  fhMass->Fit("fFuncTotal","q","",minhisto,maxhisto);
  fhMass->Fit("fFuncTotal","q","",minhisto,maxhisto);
  fFuncTotal->ReleaseParameter(1);
  fFuncTotal->SetParLimits(1,1.86,1.87);
  fFuncTotal->ReleaseParameter(11);
  fFuncTotal->SetParLimits(11,-1.,1.);
  fhMass->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMass->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMass->Fit("fFuncTotal","L q","",minhisto,maxhisto);
  fhMass->Fit("fFuncTotal","L m","",minhisto,maxhisto);
  
  TF1* fFuncBackground = new TF1("fFuncBackground","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  fFuncBackground->SetParameter(0,fFuncTotal->GetParameter(3));
  fFuncBackground->SetParameter(1,fFuncTotal->GetParameter(4));
  fFuncBackground->SetParameter(2,fFuncTotal->GetParameter(5));
  fFuncBackground->SetParameter(3,fFuncTotal->GetParameter(6));
  fFuncBackground->SetLineColor(4);
  fFuncBackground->SetRange(minhisto,maxhisto);
  fFuncBackground->SetLineStyle(2);
  
  TF1* fFuncMass = new TF1("fmass","[0]*([3]*([4]*Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  fFuncMass->SetParameters(fFuncTotal->GetParameter(0),fFuncTotal->GetParameter(1),fFuncTotal->GetParameter(2),fFuncTotal->GetParameter(7),fFuncTotal->GetParameter(9),fFuncTotal->GetParameter(10),fFuncTotal->GetParameter(11));
  fFuncMass->SetParError(0,fFuncTotal->GetParError(0));
  fFuncMass->SetParError(1,fFuncTotal->GetParError(1));
  fFuncMass->SetParError(2,fFuncTotal->GetParError(2));
  fFuncMass->SetParError(3,fFuncTotal->GetParError(7));
  fFuncMass->SetParError(4,fFuncTotal->GetParError(9));
  fFuncMass->SetParError(5,fFuncTotal->GetParError(10));
  fFuncMass->SetFillColor(kOrange-3);
  fFuncMass->SetFillStyle(3002);
  fFuncMass->SetLineColor(kOrange-3);
  fFuncMass->SetLineWidth(3);
  fFuncMass->SetLineStyle(2);
  
  TF1* fFuncMassSwap = new TF1("fmassSwap","[0]*(1-[2])*Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
  fFuncMassSwap->SetParameters(fFuncTotal->GetParameter(0),fFuncTotal->GetParameter(1),fFuncTotal->GetParameter(7),fFuncTotal->GetParameter(8),fFuncTotal->GetParameter(11));
  fFuncMassSwap->SetParError(0,fFuncTotal->GetParError(0));
  fFuncMassSwap->SetParError(1,fFuncTotal->GetParError(1));
  fFuncMassSwap->SetParError(2,fFuncTotal->GetParError(7));
  fFuncMassSwap->SetParError(3,fFuncTotal->GetParError(8));
  fFuncMassSwap->SetFillColor(kGreen+4);
  fFuncMassSwap->SetFillStyle(3005);
  fFuncMassSwap->SetLineColor(kGreen+4);
  fFuncMassSwap->SetLineWidth(3);
  fFuncMassSwap->SetLineStyle(1);
  
  fhMass->GetXaxis()->SetRangeUser(1.7,2.0);
  fhMass->SetXTitle("m_{#piK} (GeV/c^{2})");
  fhMass->SetYTitle("Entries / (5 MeV/c^{2})");
  fhMass->GetXaxis()->CenterTitle();
  fhMass->GetYaxis()->CenterTitle();
  fhMass->SetAxisRange(0,fhMass->GetMaximum()*1.4*1.2,"Y");
  fhMass->GetXaxis()->SetTitleOffset(1.3);
  fhMass->GetYaxis()->SetTitleOffset(1.8);
  fhMass->GetXaxis()->SetLabelOffset(0.007);
  fhMass->GetYaxis()->SetLabelOffset(0.007);
  fhMass->GetXaxis()->SetTitleSize(0.045);
  fhMass->GetYaxis()->SetTitleSize(0.045);
  fhMass->GetXaxis()->SetTitleFont(42);
  fhMass->GetYaxis()->SetTitleFont(42);
  fhMass->GetXaxis()->SetLabelFont(42);
  fhMass->GetYaxis()->SetLabelFont(42);
  fhMass->GetXaxis()->SetLabelSize(0.04);
  fhMass->GetYaxis()->SetLabelSize(0.04);
  fhMass->SetMarkerSize(0.8);
  fhMass->SetMarkerStyle(20);
  fhMass->SetStats(0);
  /*
  fhMass->Draw("e");
  fFuncBackground->Draw("same");   
  fFuncMass->SetRange(minhisto,maxhisto);	
  fFuncMass->Draw("same");
  fFuncMassSwap->SetRange(minhisto,maxhisto);
  fFuncMassSwap->Draw("same");
  fFuncTotal->Draw("same");
  */
 }



