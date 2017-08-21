#include "d_jet.h"

#include "TFile.h"
#include "TH1.h"

int djet::d_jet(std::string output) {
    if (fChain == 0)
        return 1;

    TFile* foutput = new TFile(output.c_str(), "recreate");
    for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
      for (int indexgen=0;indexgen<indexGenRecoMass;indexgen++){
        for (int i=0;i<nRedges;i++){
          fhHistoMass[indexgen][i][indexBkg]->Write();
          fhHistoGenSignal[indexgen][i][indexBkg]->Write();  
          fhHistoGenSwapped[indexgen][i][indexBkg]->Write();  
        }
        for (int i=0;i<nZedges;i++){
          fhHistoZMass[indexgen][i][indexBkg]->Write();
          fhHistoZGenSignal[indexgen][i][indexBkg]->Write();
          fhHistoZGenSwapped[indexgen][i][indexBkg]->Write();
        }
      }
      if(fisData==0){ 
        for (int indexeff=0;indexeff<indexGenRecoEff;indexeff++){
          fhDenEfficiency[indexeff][indexBkg]->Write();
          fhNumEfficiency[indexeff][indexBkg]->Write();
          fhEfficiency[indexeff][indexBkg]->Write();
          fhZDenEfficiency[indexeff][indexBkg]->Write();
          fhZNumEfficiency[indexeff][indexBkg]->Write();
          fhZEfficiency[indexeff][indexBkg]->Write();
        }
      }
    }
    hNjets->Write();
    foutput->Close();
    delete foutput;
   return 0;
}

int djet::loop(int isData) {
  fisData=isData;
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
        if((*jetptCorr_akpu3pf)[indexjets] > fJetpt_cut && fabs((*jeteta_akpu3pf)[indexjets]) > fJetetamin_cut && fabs((*jeteta_akpu3pf)[indexjets]) < fJetetamax_cut){
          NjetsforNorm++;
          for (int indexDm = 0; indexDm < Dsize; indexDm++) {
            bool isrecoD=selectDrecoCand((*Dpt)[indexDm],(*Dy)[indexDm],(*DsvpvDistance)[indexDm],(*DsvpvDisErr)[indexDm],(*Dalpha)[indexDm],(*Dchi2cl)[indexDm]);
            bool isrecoDtrack=selectDrecoTrack((*Dtrk1Eta)[indexDm],(*Dtrk2Eta)[indexDm],(*Dtrk1Pt)[indexDm],(*Dtrk2Pt)[indexDm],(*Dtrk1PtErr)[indexDm],(*Dtrk2PtErr)[indexDm],(*Dtrk1highPurity)[indexDm],(*Dtrk2highPurity)[indexDm]);
            if (isrecoD&&isrecoDtrack){             
              double deltaphi = acos(cos((*Dphi)[indexDm] - (*jetphi_akpu3pf)[indexjets]));
              double deltaeta = (*Deta)[indexDm] - (*jeteta_akpu3pf)[indexjets];
              double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
              double deltaetaRefl = (*Deta)[indexDm] + (*jeteta_akpu3pf)[indexjets];
              double DeltaRRefl = sqrt(pow(deltaphi, 2) + pow(deltaetaRefl, 2));
              double zvariable=(*Dpt)[indexDm]/(*jetptCorr_akpu3pf)[indexjets];
              
              fillHistoR(isData,0,0,DeltaR,(*Dmass)[indexDm],(*Dgen)[indexDm]);
              fillHistoR(isData,0,1,DeltaRRefl,(*Dmass)[indexDm],(*Dgen)[indexDm]);
               
              if(DeltaR<0.3) fillHistoZ(isData,0,0,zvariable,(*Dmass)[indexDm],(*Dgen)[indexDm]);
              if(DeltaRRefl<0.3) fillHistoZ(isData,0,1,zvariable,(*Dmass)[indexDm],(*Dgen)[indexDm]);

              if(isData==0 && ((*Dgen)[indexDm])==23333){ 
                fhNumEfficiency[0][0]->Fill(DeltaR);
                fhNumEfficiency[0][1]->Fill(DeltaRRefl);

                if(DeltaR<0.3) fhZNumEfficiency[0][0]->Fill(zvariable);
                if(DeltaRRefl<0.3) fhZNumEfficiency[0][1]->Fill(zvariable); 
              }
            }//end of isselected              
          }//loop over D mesons
           
          if(isData==0){
            for (int indexDgenm = 0; indexDgenm < Gsize; indexDgenm++) {
             bool isGen=selectDgen((*Gpt)[indexDgenm],(*Gy)[indexDgenm],(*GisSignal)[indexDgenm]);
               if(isGen){
                 double deltagenphi = acos(cos((*Gphi)[indexDgenm] - (*jetphi_akpu3pf)[indexjets]));
                 double deltageneta = (*Geta)[indexDgenm] - (*jeteta_akpu3pf)[indexjets];
                 double DeltagenR = sqrt(pow(deltagenphi, 2) + pow(deltageneta, 2));
                 double deltagenetaRefl = (*Geta)[indexDgenm] + (*jeteta_akpu3pf)[indexjets];
                 double DeltagenRRefl = sqrt(pow(deltagenphi, 2) + pow(deltagenetaRefl, 2));
                 double zgenvariable=(*Gpt)[indexDgenm]/(*jetptCorr_akpu3pf)[indexjets];
                 
                 fhDenEfficiency[0][0]->Fill(DeltagenR);
                 fhDenEfficiency[0][1]->Fill(DeltagenRRefl);
                 if(DeltagenR<0.3) fhZDenEfficiency[0][0]->Fill(zgenvariable);
                 if(DeltagenRRefl<0.3) fhZDenEfficiency[0][1]->Fill(zgenvariable);
               }//end selected  
             }//loop over gen candidate
           }//end of isData
         }// selection on jet pt
       }//end of loop over jets

    if(isData==0){
      if (!(Dsize > 0 && ngen_akpu3pf)) continue;
        for(int indexjets=0;indexjets<ngen_akpu3pf;indexjets++){
          if((*genpt_akpu3pf)[indexjets] > fJetpt_cut && fabs((*geneta_akpu3pf)[indexjets]) > fJetetamin_cut && fabs((*geneta_akpu3pf)[indexjets]) < fJetetamax_cut){
            NjetsforNormGenJet++;
            for (int indexDm = 0; indexDm < Dsize; indexDm++) {
              bool isrecoD=selectDrecoCand((*Dpt)[indexDm],(*Dy)[indexDm],(*DsvpvDistance)[indexDm],(*DsvpvDisErr)[indexDm],(*Dalpha)[indexDm],(*Dchi2cl)[indexDm]);
              bool isrecoDtrack=selectDrecoTrack((*Dtrk1Eta)[indexDm],(*Dtrk2Eta)[indexDm],(*Dtrk1Pt)[indexDm],(*Dtrk2Pt)[indexDm],(*Dtrk1PtErr)[indexDm],(*Dtrk2PtErr)[indexDm],(*Dtrk1highPurity)[indexDm],(*Dtrk2highPurity)[indexDm]);
              if (isrecoD&&isrecoDtrack){
                double deltaphi = acos(cos((*Dphi)[indexDm] - (*genphi_akpu3pf)[indexjets]));
                double deltaeta = (*Deta)[indexDm] - (*geneta_akpu3pf)[indexjets];
                double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                double deltaetaRefl = (*Deta)[indexDm] + (*geneta_akpu3pf)[indexjets];
                double DeltaRRefl = sqrt(pow(deltaphi, 2) + pow(deltaetaRefl, 2));
                double zvariable=(*Dpt)[indexDm]/(*genpt_akpu3pf)[indexjets];

                fillHistoR(isData,1,0,DeltaR,(*Dmass)[indexDm],(*Dgen)[indexDm]);
                fillHistoR(isData,1,1,DeltaRRefl,(*Dmass)[indexDm],(*Dgen)[indexDm]);

                if(DeltaR<0.3) fillHistoZ(isData,1,0,zvariable,(*Dmass)[indexDm],(*Dgen)[indexDm]);
                if(DeltaRRefl<0.3) fillHistoZ(isData,1,1,zvariable,(*Dmass)[indexDm],(*Dgen)[indexDm]);

                if(isData==0 && ((*Dgen)[indexDm])==23333){
                  fhNumEfficiency[1][0]->Fill(DeltaR);
                  fhNumEfficiency[1][1]->Fill(DeltaRRefl);

                  if(DeltaR<0.3) fhZNumEfficiency[1][0]->Fill(zvariable);
                  if(DeltaRRefl<0.3) fhZNumEfficiency[1][1]->Fill(zvariable);
                }
              }//end of isselected              
            }//loop over D meson

            for (int indexDgenm = 0; indexDgenm < Gsize; indexDgenm++) {
             bool isGen=selectDgen((*Gpt)[indexDgenm],(*Gy)[indexDgenm],(*GisSignal)[indexDgenm]);
               if(isGen){
                 double deltagenphi = acos(cos((*Gphi)[indexDgenm] - (*genphi_akpu3pf)[indexjets]));
                 double deltageneta = (*Geta)[indexDgenm] - (*geneta_akpu3pf)[indexjets];
                 double DeltagenR = sqrt(pow(deltagenphi, 2) + pow(deltageneta, 2));
                 double deltagenetaRefl = (*Geta)[indexDgenm] + (*geneta_akpu3pf)[indexjets];
                 double DeltagenRRefl = sqrt(pow(deltagenphi, 2) + pow(deltagenetaRefl, 2));
                 double zgenvariable=(*Gpt)[indexDgenm]/(*genpt_akpu3pf)[indexjets];
      
                 fhDenEfficiency[1][0]->Fill(DeltagenR);
                 fhDenEfficiency[1][1]->Fill(DeltagenRRefl);
                 if(DeltagenR<0.3) fhZDenEfficiency[1][0]->Fill(zgenvariable);
                 if(DeltagenRRefl<0.3) fhZDenEfficiency[1][1]->Fill(zgenvariable);
                 /*
                 if(DeltagenRRefl<0.01){
                   cout<<"evt number="<<evt<<endl;
                   cout<<"EvtNo"<<EvtNo<<endl;
                   cout<<"jet pt="<<(*genpt_akpu3pf)[indexjets]<<endl;
                   cout<<"jet eta="<<(*geneta_akpu3pf)[indexjets]<<endl;
                   cout<<"jet phi="<<(*genphi_akpu3pf)[indexjets]<<endl;
                   //cout<" D pt="<<(*Gpt)[indexDgenm]<<endl;
                   cout<<"D pt="<<(*Gpt)[indexDgenm]<<endl;
                   cout<<"D eta="<<(*Geta)[indexDgenm]<<endl;
                   cout<<"D phi="<<(*Gphi)[indexDgenm]<<endl;
                 }
                 */
               }//end selected  
             }//loop over gen candidate
         }// selection on jet pt
       }//end of loop over jets
    }//end of is data
    }//end of loop over events

    if(isData==0){  
      for (int indexBkg=0;indexBkg<indexBkgReflection;indexBkg++){
        for (int indexeff=0;indexeff<indexGenRecoEff;indexeff++){
          fhDenEfficiency[indexeff][indexBkg]->Sumw2();
          fhNumEfficiency[indexeff][indexBkg]->Sumw2();
          fhZDenEfficiency[indexeff][indexBkg]->Sumw2();
          fhZNumEfficiency[indexeff][indexBkg]->Sumw2();
          fhEfficiency[indexeff][indexBkg]=(TH1F*)fhNumEfficiency[indexeff][indexBkg]->Clone(Form("fhEfficiency_%d_indexBkg%d",indexeff,indexBkg));
          fhZEfficiency[indexeff][indexBkg]=(TH1F*)fhZNumEfficiency[indexeff][indexBkg]->Clone(Form("fhZEfficiency_%d_indexBkg%d",indexeff,indexBkg));
          fhEfficiency[indexeff][indexBkg]->Sumw2();
          fhZEfficiency[indexeff][indexBkg]->Sumw2();      
          fhEfficiency[indexeff][indexBkg]->Divide(fhEfficiency[indexeff][indexBkg],fhDenEfficiency[indexeff][indexBkg], 1.0, 1.0, "B");
          fhZEfficiency[indexeff][indexBkg]->Divide(fhZEfficiency[indexeff][indexBkg],fhZDenEfficiency[indexeff][indexBkg], 1.0, 1.0, "B");
        }
      }
    }
    //NjetsforNormGenJet
    hNjets->SetBinContent(1,NjetsforNorm);
    hNjets->SetBinContent(2,NjetsforNormGenJet);
    cout<<"calling fit"<<endl;
    return 1;
}


/*
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
*/
