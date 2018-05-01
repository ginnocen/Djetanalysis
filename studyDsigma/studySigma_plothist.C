#include "../includes/xjjrootuti.h"
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <TFile.h>
#include <TGraphErrors.h>
#include "studySigma.h"


void studySigma_plothist(TString inputnameData="rootfiles/xsec_pp_Data", TString inputnameMC="rootfiles/xsec_pp_MC",TString output="rootfiles/output",  TString collisionsyst="pp",TString label="")
{
  xjjroot::setgstyle(1);
  
  int mycolors_sample[2]={1,2};
  
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  Int_t ispp = collisionsyst=="pp"?1:0;
  
  if(createhists("usehist")) return;
  
  TF1 *fFitY[nvariables][fitvariations];
  TF1 *fFitPt[nvariables][fitvariations];
  
  for (int i=0;i<nvariables;i++){
    for (int m=0;m<fitvariations;m++){
  
      fFitY[i][m]=new TF1(Form("fFitY%s%s",variablename[i].Data(),fittype[m].Data()),fittype[m],-2.,2.);
      fFitPt[i][m]=new TF1(Form("fFitPt%s%s",variablename[i].Data(),fittype[m].Data()),fittype[m],4.,100.);
      fFitY[i][m]->SetName(Form("fFitY%s%s",variablename[i].Data(),fittype[m].Data()));
      fFitPt[i][m]->SetName(Form("fFitPt%s%s",variablename[i].Data(),fittype[m].Data()));
      fFitY[i][m]->SetLineColor(fittypecolor[m]);
      fFitY[i][m]->SetLineWidth(2);
      fFitPt[i][m]->SetLineColor(fittypecolor[m]);
      fFitPt[i][m]->SetLineWidth(2);
    }
  }
  
  TFile* infData = new TFile(Form("%s.root",inputnameData.Data()));
  TFile* infMC = new TFile(Form("%s.root",inputnameMC.Data()));
  if(!infData->IsOpen()) return;
  if(!infMC->IsOpen()) return;
  if(gethistsDataMC(infData,infMC, "plothist")) return;
  
  TH1F*hDmesonYData=(TH1F*)infData->Get("hDmesonY");
  TH1F*hDmesonYMC=(TH1F*)infMC->Get("hDmesonY");

  TH2F* hemptyPt[4];
  hemptyPt[0]= new TH2F("hemptyPt0", ";D p_{T}; #mu (GeV)", 10, 0, 100, 10, 1.8,1.9);
  hemptyPt[1]= new TH2F("hemptyPt1", ";D p_{T}; #sigma (GeV)", 10, 0, 100, 10, 0.,0.1);
  hemptyPt[2]= new TH2F("hemptyPt2", ";D p_{T}; #mu(DATA)/#mu(MC)", 10, 0, 100, 10, 0.5,1.5);
  hemptyPt[3]= new TH2F("hemptyPt3", ";D p_{T}; #sigma(DATA)/#sigma(MC)", 10, 0, 100, 10, 0.5,1.5);
   
  TH2F* hemptyY[4];
  hemptyY[0]= new TH2F("hemptyY0", ";D rapidity; #mu (GeV)", 10, -3, 3, 10, 1.8,1.9);
  hemptyY[1]= new TH2F("hemptyY1", ";D rapidity; #sigma (GeV)", 10, -3, 3, 10, 0.,0.1);
  hemptyY[2]= new TH2F("hemptyY2", ";D rapidity; #mu(DATA)/#mu(MC)", 10, -3, 3, 10, 0.5,1.5);
  hemptyY[3]= new TH2F("hemptyY3", ";D rapidity; #sigma(DATA)/#sigma(MC)", 10, -3, 3, 10, 0.5,1.5);

  TH2F* hemptySpectra[4];
  hemptySpectra[0]= new TH2F("hemptySpectra0", ";D p_{T};signal", 10, 0, 100, 10, 0.,1);
  hemptySpectra[1]= new TH2F("hemptySpectra1", ";D rapidity;signal", 10, -3, 3, 10, 0.,1);
  hemptySpectra[2]= new TH2F("hemptySpectra2", ";D p_{T};signal Data/MC", 10, 0, 100, 10, 0., 2);
  hemptySpectra[3]= new TH2F("hemptySpectra3", ";D rapidity;signal Data/MC", 10, -3, 3, 10, 0., 2);

  TLatex *texData = new TLatex(0.68, 0.25, "Data");
  xjjroot::settex(texData, 0.08, 22);
  texData->SetTextColor(mycolors_sample[0]);
  // texData->SetTextAlign(22); 
  // texData->SetTextSize(0.08);
  TLatex *texMC = new TLatex(0.85, 0.25, "MC");
  xjjroot::settex(texMC, 0.08, 22);
  texMC->SetTextColor(mycolors_sample[1]);
  // texMC->SetTextAlign(22); texMC->SetTextSize(0.08);
   
  // TLatex *texDataY = new TLatex(-1.5,1.85,"Data");
  // texDataY->SetTextColor(mycolors_sample[0]);
  // texDataY->SetTextAlign(22); texDataY->SetTextSize(0.1);
  // TLatex *texMCY = new TLatex(0,1.85,"MC");
  // texMCY->SetTextColor(mycolors_sample[1]);
  // texMCY->SetTextAlign(22); texMCY->SetTextSize(0.1);

  TLegend* leg = new TLegend(0.53, 0.88, 0.85, 0.88);
  xjjroot::setleg(leg);

  TCanvas* cPt= new TCanvas("cPt", "", 1000, 1000);
  cPt->Divide(2,2);
  for (int i=0;i<2;i++){
    cPt->cd(i+1);
    hemptyPt[i]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hemptyPt[i], 0, 0.3);
    hemptyPt[i]->Draw();
    xjjroot::setthgrstyle(ahHistoPtsample[i][0], mycolors_sample[0], 21, 0.8, mycolors_sample[0], 1, 1, -1, -1, -1);
    xjjroot::setthgrstyle(ahHistoPtsample[i][1], mycolors_sample[1], 21, 0.8, mycolors_sample[1], 1, 1, -1, -1, -1);
    ahHistoPtsample[i][0]->Draw("same");
    ahHistoPtsample[i][1]->Draw("same");
    texData->Draw();
    texMC->Draw();
    xjjroot::drawCMS(collisionsyst.Data());
  }
  for (int i=0;i<2;i++){
    cPt->cd(i+3);
    hemptyPt[i]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hemptyPt[i+2], 0, 0.3);
    hemptyPt[i+2]->Draw();
    xjjroot::setthgrstyle(ahRatioPtDataOverMC[i], mycolors_sample[0], 21, 0.8, mycolors_sample[0], 1, 1, -1, -1, -1);
    ahRatioPtDataOverMC[i]->Draw("same");
    ahRatioPtDataOverMC[i]->Draw("same");
    
    for (int m=0;m<fitvariations;m++){
      ahRatioPtDataOverMC[i]->Fit(Form("fFitPt%s%s",variablename[i].Data(),fittype[m].Data()),"q");
      fFitPt[i][m]->Draw("same");
    }
    xjjroot::drawCMS(collisionsyst.Data());
  }

  cPt->SaveAs(Form("plotsSigma/canvasMeanSigmaPt%s.pdf",label.Data()));

  TCanvas* cY= new TCanvas("cY", "", 1000, 1000);
  cY->Divide(2,2);
  for (int i=0;i<2;i++){
    cY->cd(i+1);
    hemptyY[i]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hemptyY[i], 0, 0.3);
    hemptyY[i]->Draw();
    texData->Draw();
    texMC->Draw();
    xjjroot::setthgrstyle(ahHistoYsample[i][0], mycolors_sample[0], 21, 0.8, mycolors_sample[0], 1, 1, -1, -1, -1);
    xjjroot::setthgrstyle(ahHistoYsample[i][1], mycolors_sample[1], 21, 0.8, mycolors_sample[1], 1, 1, -1, -1, -1);
    ahHistoYsample[i][0]->Draw("same");
    ahHistoYsample[i][1]->Draw("same");
    xjjroot::drawCMS(collisionsyst.Data());
  }
  for (int i=0;i<2;i++){
    cY->cd(i+3);
    hemptyY[i]->GetXaxis()->SetNdivisions(505);
    xjjroot::sethempty(hemptyY[i+2], 0, 0.3);
    hemptyY[i+2]->Draw();
    xjjroot::setthgrstyle(ahRatioYDataOverMC[i], mycolors_sample[0], 21, 0.8, mycolors_sample[0], 1, 1, -1, -1, -1);
    ahRatioYDataOverMC[i]->Draw("same");
    ahRatioYDataOverMC[i]->Draw("same");
    for (int m=0;m<fitvariations;m++){
      ahRatioYDataOverMC[i]->Fit(Form("fFitY%s%s",variablename[i].Data(),fittype[m].Data()),"q");
      fFitY[i][m]->Draw("same");
    }
    xjjroot::drawCMS(collisionsyst.Data());
  }

  cY->SaveAs(Form("plotsSigma/canvasMeanSigmaY%s.pdf",label.Data()));

  TCanvas* cYmu= new TCanvas("cYmu", "", 500, 1000);
  cYmu->Divide(1,2);
  cYmu->cd(1);
  hemptyY[0]->Draw();
  texData->Draw();
  texMC->Draw();
  ahHistoYsample[0][0]->Draw("same");
  ahHistoYsample[0][1]->Draw("same");
  xjjroot::drawCMS(collisionsyst.Data());
  cYmu->cd(2);
  hemptyY[2]->Draw();
  ahRatioYDataOverMC[0]->Draw("same");
  ahRatioYDataOverMC[0]->Draw("same");
  for (int m=0;m<fitvariations;m++){
    fFitY[0][m]->Draw("same");
  }
  xjjroot::drawCMS(collisionsyst.Data());
  cYmu->SaveAs(Form("plotsSigma/canvasMeanY%s.pdf",label.Data()));

  TCanvas* cYsig= new TCanvas("cYsig", "", 500, 1000);
  cYsig->Divide(1,2);
  cYsig->cd(1);
  hemptyY[1]->Draw();
  texData->Draw();
  texMC->Draw();
  ahHistoYsample[1][0]->Draw("same");
  ahHistoYsample[1][1]->Draw("same");
  xjjroot::drawCMS(collisionsyst.Data());
  cYsig->cd(2);
  hemptyY[2]->Draw();
  ahRatioYDataOverMC[1]->Draw("same");
  ahRatioYDataOverMC[1]->Draw("same");
  for (int m=0;m<fitvariations;m++){
    fFitY[1][m]->Draw("same");
  }
  xjjroot::drawCMS(collisionsyst.Data());
  cYsig->SaveAs(Form("plotsSigma/canvasSigmaY%s.pdf",label.Data()));

  std::ofstream myfile;
  myfile.open(Form("%sparameters.h",collisionsyst.Data()));

  myfile<<"// Y rapidity "<<collisionsyst.Data()<<","<<variablename[1]<<std::endl;

  for (int m=0;m<fitvariations;m++){
    int nparam=fFitY[1][m]->GetNpar();
    myfile<<"par"<<collisionsyst.Data()<<"["<<nparam<<"]={";
    for (int jj=0;jj<nparam;jj++){
      myfile<<fFitY[1][m]->GetParameter(jj);;
      if(jj<nparam-1)  myfile<<",";
      else myfile<<"};"<<std::endl;
    }
  }
  for (int m=0;m<fitvariations;m++){
    int nparam=fFitY[1][m]->GetNpar();
    myfile<<"parerr"<<collisionsyst.Data()<<"["<<nparam<<"]={";
    for (int jj=0;jj<nparam;jj++){
      myfile<<fFitY[1][m]->GetParError(jj);;
      if(jj<nparam-1)  myfile<<",";
      else myfile<<"};"<<std::endl;
    }
  }
  myfile.close();

  TFile* outf = new TFile(Form("%s.root",output.Data()), "recreate");
  outf->cd();
  if(writehists("plothist")) return;
  for (int i=0;i<2;i++){
    for (int m=0;m<fitvariations;m++){
      fFitY[i][m]->Write();
      //fFitPt[i][m]->Write();
    }
  }
  outf->Write();
  outf->Close();


}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      studySigma_plothist(argv[1], argv[2], argv[3],argv[4],argv[5]);
      return 0;
    }
  std::cout<<"  Error: invalid arguments number - studySigma_plothist()"<<std::endl;
  return 1;
}

int arguerr(TString collisionsyst)
{
  if(collisionsyst!="pp" && collisionsyst!="PbPb")
    {
      std::cout<<"error: invalid collisionsyst"<<std::endl;
      return 1;
    }
  return 0;
}

