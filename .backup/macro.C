#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TMath.h"
#include "math.h"

void macro(){


	TFile *inFile = TFile::Open("/export/d00/scratch/ginnocen/Djet/CMSSW_7_5_8/src/PbPb_dataForest0001_part1.root");
	TTree *fDkpi = (TTree*)inFile->Get("Dfinder/ntDkpi");
	//TTree *fEvtTree = (TTree*)inFile->Get("hiEvtAnalyzer/HiTree");
	//TTree *fSkimTree = (TTree*)inFile->Get("skimanalysis/HltTree");
	TTree *fJets = (TTree*)inFile->Get("akPu3CaloJetAnalyzer/t");
    
    fDkpi->AddFriend(fJets);
    fJets->AddFriend(fDkpi);

    int nref;
    int Dsize;
   
    float jteta[100000];
    float jtphi[100000];
    float jtpt[100000];

    bool Dtrk1highPurity[100000];
    bool Dtrk2highPurity[100000];
    float Dtrk1Pt[100000];
    float Dtrk2Pt[100000];
    float Dtrk1Eta[100000];
    float Dtrk2Eta[100000];
    float Dtrk1PtErr[100000];
    float Dtrk2PtErr[100000];

    float Dy[100000];
    float Dphi[100000];
    float Deta[100000];
    float Dmass[100000];
    float Dpt[100000];
    float DlxyBS[100000];
    float DlxyBSErr[100000];
    float Dalpha[100000];
    float Dchi2cl[100000];
    float DsvpvDistance[100000];
    float DsvpvDisErr[100000];
    
	fDkpi->SetBranchAddress("nref",&nref);
	fDkpi->SetBranchAddress("Dsize",&Dsize);
	fDkpi->SetBranchAddress("jteta",jteta);
	fDkpi->SetBranchAddress("jtpt",jtpt);
	fDkpi->SetBranchAddress("Dtrk1highPurity",Dtrk1highPurity);
	fDkpi->SetBranchAddress("Dtrk2highPurity",Dtrk2highPurity);
	fDkpi->SetBranchAddress("Dtrk1Pt",Dtrk1Pt);
	fDkpi->SetBranchAddress("Dtrk2Pt",Dtrk2Pt);
	fDkpi->SetBranchAddress("Dtrk1Eta",Dtrk1Eta);
	fDkpi->SetBranchAddress("Dtrk2Eta",Dtrk2Eta);
	fDkpi->SetBranchAddress("Dtrk1PtErr",Dtrk1PtErr);
	fDkpi->SetBranchAddress("Dtrk2PtErr",Dtrk2PtErr);
	fDkpi->SetBranchAddress("Dy",Dy);
	fDkpi->SetBranchAddress("Dphi",Dphi);
	fDkpi->SetBranchAddress("Deta",Deta);
	fDkpi->SetBranchAddress("Dmass",Dmass);
	fDkpi->SetBranchAddress("Dpt",Dpt);
	fDkpi->SetBranchAddress("DlxyBS",DlxyBS);
	fDkpi->SetBranchAddress("DlxyBSErr",DlxyBSErr);
	fDkpi->SetBranchAddress("Dalpha",Dalpha);
	fDkpi->SetBranchAddress("Dchi2cl",Dchi2cl);
	fDkpi->SetBranchAddress("DsvpvDistance",DsvpvDistance);
	fDkpi->SetBranchAddress("DsvpvDisErr",DsvpvDisErr);
	
	double DeltaR=0;
	
	TH1D* hInCone = new TH1D("hInCone","hInCone",50,1.7,2.1);
	TH1D* hOutCone = new TH1D("hOutCone","hOutCone",50,1.7,2.1);
	
    Long64_t entries = fDkpi->GetEntries();
	for(Long64_t j = 0; j < entries; ++j){   
	
		fDkpi->GetEntry(j);
		fJets->GetEntry(j);
		
		if(!(Dsize>0&&nref>0&&jtpt[0]>40)) continue;
		
	    for(int m = 0; m < Dsize; m++){
	      if((DsvpvDistance[m]/DsvpvDisErr[m])>3.06 &&Dpt[m]>10){
	        double deltaphi=acos(cos(Dphi[m]-jtphi[0]));
	        double deltaeta=Deta[m]-jteta[0];
	        DeltaR=sqrt(pow(deltaphi,2)+pow(deltaeta,2));
            if (DeltaR<0.5) hInCone->Fill(Dmass[m]);
            else hOutCone->Fill(Dmass[m]);
	    }
     } 
  }
  TCanvas*c=new TCanvas("c","c",1000,500);
  c->Divide(2,1);
  c->cd(1);
  hInCone->Draw();
  c->cd(2);
  hOutCone->Draw();
}