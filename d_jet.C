#include "d_jet.h"

#include "TFile.h"
#include "TH1.h"

int djet::d_jet(std::string output) {
    if (fChain == 0)
        return 1;

    TFile* foutput = new TFile(output.c_str(), "recreate");
    for (int i=0;i<nRedges;i++){
      fhHistoMass[i]->Write();
      fhHistoGenSignal[i]->Write();  
      fhHistoGenSwapped[i]->Write();  
    }
    for (int i=0;i<nZedges;i++){
      fhHistoZMass[i]->Write();
      fhHistoZGenSignal[i]->Write();
      fhHistoZGenSwapped[i]->Write();
    }
    hNjets->Write();
    fhDenEfficiency->Write();
    fhNumEfficiency->Write();
    fhEfficiency->Write();
    fhZDenEfficiency->Write();
    fhZNumEfficiency->Write();
    fhZEfficiency->Write();
    foutput->Close();
    delete foutput;
   return 0;
}

int djet::loop(int isData) {
  bool debugmode=false;
  int64_t nentries = fChain->GetEntriesFast();
  int NjetsforNorm=0;
  for (int64_t jentry = 0; jentry < nentries; jentry++) {
    if (jentry % 1000 == 0) printf("%li/%li\n", jentry, nentries);
    if (LoadTree(jentry) < 0) break;
    fChain->GetEntry(jentry);
    if(debugmode) cout<<"********************* event number="<<evt<<" *********************"<<endl;
      if (!(Dsize > 0 && njet_akpu3pf)) continue;
        for(int indexjets=0;indexjets<njet_akpu3pf;indexjets++){
          if((*jetptCorr_akpu3pf)[indexjets] > fJetpt_cut && fabs((*jeteta_akpu3pf)[indexjets]) < fJeteta_cut){
            NjetsforNorm++;
            for (int indexDm = 0; indexDm < Dsize; indexDm++) {
              bool isrecoD=selectDrecoCand((*Dpt)[indexDm],(*Dy)[indexDm],(*DsvpvDistance)[indexDm],(*DsvpvDisErr)[indexDm],(*Dalpha)[indexDm],(*Dchi2cl)[indexDm]);
              bool isrecoDtrack=selectDrecoTrack((*Dtrk1Eta)[indexDm],(*Dtrk2Eta)[indexDm],(*Dtrk1Pt)[indexDm],(*Dtrk2Pt)[indexDm],(*Dtrk1PtErr)[indexDm],(*Dtrk2PtErr)[indexDm],(*Dtrk1highPurity)[indexDm],(*Dtrk2highPurity)[indexDm]);
              if (isrecoD&&isrecoDtrack){
                double deltaphi = acos(cos((*Dphi)[indexDm] - (*jetphi_akpu3pf)[indexjets]));
                double deltaeta = (*Deta)[indexDm] - (*jeteta_akpu3pf)[indexjets];
                double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                double zvariable=(*Dpt)[indexDm]/(*jetptCorr_akpu3pf)[indexjets];

                if(isData==0 && ((*Dgen)[indexDm])==23333) fhNumEfficiency->Fill(DeltaR);
                fillHistoR(isData,DeltaR,(*Dmass)[indexDm],(*Dgen)[indexDm]);
                fillHistoZ(isData,zvariable,(*Dmass)[indexDm],(*Dgen)[indexDm]);
             
             }//end of isselected              
           }//loop over D mesons
           
           if(isData==0){
             for (int indexDgenm = 0; indexDgenm < Gsize; indexDgenm++) {
               bool isGen=selectDgen((*Gpt)[indexDgenm],(*Gy)[indexDgenm],(*GisSignal)[indexDgenm]);
               if(isGen){
                 double deltagenphi = acos(cos((*Gphi)[indexDgenm] - (*jetphi_akpu3pf)[indexjets]));
                 double deltageneta = (*Geta)[indexDgenm] - (*jeteta_akpu3pf)[indexjets];
                 double DeltagenR = sqrt(pow(deltagenphi, 2) + pow(deltageneta, 2));
                 double zgenvariable=(*Gpt)[indexDgenm]/(*jetptCorr_akpu3pf)[indexjets];
                 fhDenEfficiency->Fill(DeltagenR);
                 fhZDenEfficiency->Fill(zgenvariable);
               }//end selected  
             }//loop over gen candidate
           }//end of isData
         }// selection on jet pt
       }//end of loop over jets
     }//end of loop over events
   
    fhDenEfficiency->Sumw2();
    fhNumEfficiency->Sumw2();
    fhZDenEfficiency->Sumw2();
    fhZNumEfficiency->Sumw2();
    fhEfficiency=(TH1F*)fhNumEfficiency->Clone("fhEfficiency");
    fhZEfficiency=(TH1F*)fhZNumEfficiency->Clone("fhZEfficiency");
    fhEfficiency->Sumw2();
    fhZEfficiency->Sumw2();

    fhEfficiency->Divide(fhEfficiency,fhDenEfficiency, 1.0, 1.0, "B");
    fhZEfficiency->Divide(fhZEfficiency,fhZDenEfficiency, 1.0, 1.0, "B");
    
    hNjets->SetBinContent(1,NjetsforNorm);
    cout<<"calling fit"<<endl;
    return 1;
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: ./d_jet [input] [output]\n");
        return 1;
    }

    djet* t = new djet(argv[1]);

    if (argc == 3)
        return t->d_jet(argv[2]);
    else
        return 1;
}
