#include "d_jet.h"

#include "TFile.h"
#include "TH1.h"

int djet::d_jet(std::string output) {
    if (fChain == 0)
        return 1;

    TFile* foutput = new TFile(output.c_str(), "recreate");
    for (int indexgen=0;indexgen<indexGenRecoMass;indexgen++){
      for (int i=0;i<nRedges;i++){
        fhHistoMass[indexgen][i]->Write();
        fhHistoGenSignal[indexgen][i]->Write();  
        fhHistoGenSwapped[indexgen][i]->Write();  
      }
      for (int i=0;i<nZedges;i++){
        fhHistoZMass[indexgen][i]->Write();
        fhHistoZGenSignal[indexgen][i]->Write();
        fhHistoZGenSwapped[indexgen][i]->Write();
      }
    }
    hNjets->Write();
    for (int indexeff=0;indexeff<indexGenRecoEff;indexeff++){
      fhDenEfficiency[indexeff]->Write();
      fhNumEfficiency[indexeff]->Write();
      fhEfficiency[indexeff]->Write();
      fhZDenEfficiency[indexeff]->Write();
      fhZNumEfficiency[indexeff]->Write();
      fhZEfficiency[indexeff]->Write();
    }
    foutput->Close();
    delete foutput;
   return 0;
}

int djet::loop(int isData) {
  bool debugmode=false;
  int64_t nentries = fChain->GetEntriesFast();
  int NjetsforNorm=0;
  int NjetsforNormGenJet=0;
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

              if(isData==0 && ((*Dgen)[indexDm])==23333) fhNumEfficiency[0]->Fill(DeltaR);
              if(isData==0 && ((*Dgen)[indexDm])==23333) fhZNumEfficiency[0]->Fill(zvariable);

              fillHistoR(isData,0,DeltaR,(*Dmass)[indexDm],(*Dgen)[indexDm]);
              fillHistoZ(isData,0,zvariable,(*Dmass)[indexDm],(*Dgen)[indexDm]);   
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
                 fhDenEfficiency[0]->Fill(DeltagenR);
                 fhZDenEfficiency[0]->Fill(zgenvariable);
               }//end selected  
             }//loop over gen candidate
           }//end of isData
         }// selection on jet pt
       }//end of loop over jets
    if(isData==0){
      if (!(Dsize > 0 && ngen_akpu3pf)) continue;
        for(int indexjets=0;indexjets<ngen_akpu3pf;indexjets++){
          if((*genpt_akpu3pf)[indexjets] > fJetpt_cut && fabs((*geneta_akpu3pf)[indexjets]) < fJeteta_cut){
            NjetsforNormGenJet++;
            for (int indexDm = 0; indexDm < Dsize; indexDm++) {
              bool isrecoD=selectDrecoCand((*Dpt)[indexDm],(*Dy)[indexDm],(*DsvpvDistance)[indexDm],(*DsvpvDisErr)[indexDm],(*Dalpha)[indexDm],(*Dchi2cl)[indexDm]);
              bool isrecoDtrack=selectDrecoTrack((*Dtrk1Eta)[indexDm],(*Dtrk2Eta)[indexDm],(*Dtrk1Pt)[indexDm],(*Dtrk2Pt)[indexDm],(*Dtrk1PtErr)[indexDm],(*Dtrk2PtErr)[indexDm],(*Dtrk1highPurity)[indexDm],(*Dtrk2highPurity)[indexDm]);
              if (isrecoD&&isrecoDtrack){
                double deltaphi = acos(cos((*Dphi)[indexDm] - (*genphi_akpu3pf)[indexjets]));
                double deltaeta = (*Deta)[indexDm] - (*geneta_akpu3pf)[indexjets];
                double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                double zvariable=(*Dpt)[indexDm]/(*genpt_akpu3pf)[indexjets];

                if(isData==0 && ((*Dgen)[indexDm])==23333) fhNumEfficiency[1]->Fill(DeltaR);
                if(isData==0 && ((*Dgen)[indexDm])==23333) fhZNumEfficiency[1]->Fill(zvariable);
                fillHistoR(isData,1,DeltaR,(*Dmass)[indexDm],(*Dgen)[indexDm]);
                fillHistoZ(isData,1,zvariable,(*Dmass)[indexDm],(*Dgen)[indexDm]);
              }//end of isselected              
            }//loop over D meson

            for (int indexDgenm = 0; indexDgenm < Gsize; indexDgenm++) {
             bool isGen=selectDgen((*Gpt)[indexDgenm],(*Gy)[indexDgenm],(*GisSignal)[indexDgenm]);
               if(isGen){
                 double deltagenphi = acos(cos((*Gphi)[indexDgenm] - (*genphi_akpu3pf)[indexjets]));
                 double deltageneta = (*Geta)[indexDgenm] - (*geneta_akpu3pf)[indexjets];
                 double DeltagenR = sqrt(pow(deltagenphi, 2) + pow(deltageneta, 2));
                 double zgenvariable=(*Gpt)[indexDgenm]/(*jetptCorr_akpu3pf)[indexjets];
                 fhDenEfficiency[1]->Fill(DeltagenR);
                 fhZDenEfficiency[1]->Fill(zgenvariable);
               }//end selected  
             }//loop over gen candidate
         }// selection on jet pt
       }//end of loop over jets
    }//end of is data
    }//end of loop over events
   
    for (int indexeff=0;indexeff<indexGenRecoEff;indexeff++){
      fhDenEfficiency[indexeff]->Sumw2();
      fhNumEfficiency[indexeff]->Sumw2();
      fhZDenEfficiency[indexeff]->Sumw2();
      fhZNumEfficiency[indexeff]->Sumw2();
      fhEfficiency[indexeff]=(TH1F*)fhNumEfficiency[indexeff]->Clone(Form("fhEfficiency_%d",indexeff));
      fhZEfficiency[indexeff]=(TH1F*)fhZNumEfficiency[indexeff]->Clone(Form("fhZEfficiency_%d",indexeff));
      fhEfficiency[indexeff]->Sumw2();
      fhZEfficiency[indexeff]->Sumw2();      
      fhEfficiency[indexeff]->Divide(fhEfficiency[indexeff],fhDenEfficiency[indexeff], 1.0, 1.0, "B");
      fhZEfficiency[indexeff]->Divide(fhZEfficiency[indexeff],fhZDenEfficiency[indexeff], 1.0, 1.0, "B");
    }
    //NjetsforNormGenJet
    hNjets->SetBinContent(1,NjetsforNorm);
    hNjets->SetBinContent(2,NjetsforNormGenJet);
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
