void shiftptturnon(){

  TString namefiles=" ../TurnOnCurves.root";
  TFile *finput=new TFile(namefiles,"read"); 
  TF1*fit=(TF1*)finput->Get("fitErfL1_PbPbHLT80");
  TH1F*hempty=new TH1F("hempty","hempty",300,0,300);
  
  TString functionalFormTurnOnShifted= "0.5*TMath::Erf((x+%f)*[0]+[1]+TMath::Exp((-(x+%f)^2+[1])/[3])*[2])+0.5";
  TF1 *fitshifted= new TF1("fitshifted",Form(functionalFormTurnOnShifted.Data(),20.,20.),0,150);
  fitshifted->SetParameters(fit->GetParameter(0),fit->GetParameter(1),fit->GetParameter(2),fit->GetParameter(3));
  hempty->Draw();
  fit->SetLineColor(1);
  fit->Draw("same");
  fitshifted->Draw("same");

}

