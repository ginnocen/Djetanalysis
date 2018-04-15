#include "../includes/xjjrootuti.h"
#include <TH2F.h>
#include <TH1F.h>
#include <TLegend.h>

void compareRatioDataMC(TString suffixsample="pp",int intsuffixpthat=0){

  const int nfiles=7;
  const int variables=2;
  
  TString cutval_Dchi2cl[nfiles]={"0p0","0p15","0p15","0p15","0p15","0p15","0p3",};
  TString cutval_Dsvpv[nfiles]={"4p5","2p0","4p5","4p5","4p5","6p0","4p5",};
  TString cutval_Dalpha[nfiles]={"0p12","0p12","0p02","0p12","0p3","0p12","0p12",};
  
  TString filename[nfiles];
  TFile* file[nfiles];
  TString namehistogram[variables]={"ahRatioSigmaYDataOverMC","ahRatioSigmaPtDataOverMC"};
  TH1F* hRatio[nfiles][variables];
  TH2F* hempties[variables];
    
   hempties[0]= new TH2F("hempties0", ";rapidity; #sigma DATA/MC", 10, -3, 3, 10, 0.,1.);
   hempties[1]= new TH2F("hempties1", ";p_{T}; #sigma DATA/MC", 10, 0, 100, 10, 0.,1.);
   
  TLegend* leg[variables];

   for (int i=0;i<nfiles;i++){
     filename[i]=Form("rootfiles/datamc_MC_Djet_%s_pthat%d_ptcutforYstudy4p0_ycutforPtstudy2p0_cutval_Dchi2cl%s_cutval_Dsvpv%s_cutval_Dalpha%s_gaussianindex2.root",suffixsample.Data(),intsuffixpthat,cutval_Dchi2cl[i].Data(),cutval_Dsvpv[i].Data(),cutval_Dalpha[i].Data());
     file[i]=new TFile(filename[i].Data(),"read");
     leg[i]=new TLegend(0.6,0.6,0.9,0.9);
     leg[i]->SetBorderSize(0);
     leg[i]->SetFillStyle(0);
     std::cout<<filename[i].Data()<<std::endl;
     for (int m=0;m<variables;m++){
       hRatio[i][m]=(TH1F*)file[i]->Get(namehistogram[m].Data());
     }
   } 

    TCanvas* c=new TCanvas("canvas","canvas",1000,500);
    c->Divide(2,1);
    for (int m=0;m<2;m++){
      c->cd(m+1);
      hempties[m]->Draw();
      for (int i=0;i<nfiles;i++){
    	hRatio[i][m]->Draw("same");	
    	}
    }
    //c->SaveAs(Form("canvas_cutvariationSigma%s.pdf",suffixsample.Data());

    TFile*test=new TFile("tottete.root","recreate");
    test->cd();
   for (int i=0;i<nfiles;i++){
     for (int m=0;m<variables;m++){
       hRatio[i][m]->SetName(Form("hRatioFile%d_variable%d",i,m));
       hRatio[i][m]->Write();
     }
   } 

}