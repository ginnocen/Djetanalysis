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
    foutput->Close();
    delete foutput;
   return 0;
}

int djet::loop(int isData) {
  bool debugmode=false;
  int64_t nentries = fChain->GetEntriesFast();
  for (int64_t jentry = 0; jentry < nentries; jentry++) {
    if (jentry % 1000 == 0) printf("%li/%li\n", jentry, nentries);
    if (LoadTree(jentry) < 0) break;
      fChain->GetEntry(jentry);
      if(debugmode) cout<<"********************* event number="<<evt<<" *********************"<<endl;
      if (!(Dsize > 0 && njet_akpu3pf)) continue;
        for(int indexjets=0;indexjets<njet_akpu3pf;indexjets++){
         if(debugmode){ 
            cout<<"Dsize="<<Dsize<<endl;
            cout<<"indexjets="<<indexjets<<",pt="<<(*jetpt_akpu3pf)[indexjets]<<endl;
          }
          if((*jetpt_akpu3pf)[indexjets] > fJetpt_cut && fabs((*jeteta_akpu3pf)[indexjets]) < fJeteta_cut){
            for (int m = 0; m < Dsize; m++) {
              if((*Dpt)[m] >fDptlow_cut && (*Dpt)[m] <fDpthigh_cut){
                if ( fabs((*Dy)[m]) < fDy_cut  && ((*DsvpvDistance)[m] / (*DsvpvDisErr)[m]) > fDdecaylength_cut && (*Dalpha)[m] < fDalpha_cut && (*Dchi2cl)[m] > fDchi2cl_cut ) {
                  if(fabs((*Dtrk1Eta)[m]) < fDtrketa_cut && fabs((*Dtrk2Eta)[m]) < fDtrketa_cut && (*Dtrk1Pt)[m] > fDtrkptmin_cut && (*Dtrk2Pt)[m] > fDtrkptmin_cut){
                    if(((*Dtrk1PtErr)[m] / (*Dtrk1Pt)[m]) < fDtrkpterr_cut && ((*Dtrk2PtErr)[m] / (*Dtrk2Pt)[m]) < fDtrkpterr_cut && (*Dtrk1highPurity)[m]==1 && (*Dtrk2highPurity)[m]==1){
                      double deltaphi = acos(cos((*Dphi)[m] - (*jetphi_akpu3pf)[indexjets]));
                      double deltaeta = (*Deta)[m] - (*jeteta_akpu3pf)[indexjets];
                      double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                    
                      for (int n=0; n<nRedges; n++){ 
                        if(DeltaR>Redges[n]&&DeltaR<Redges[n+1]){
                          if(debugmode){
                            cout<<"leading jet pt"<<(*jetpt_akpu3pf)[0]<<",eta="<<(*jeteta_akpu3pf)[indexjets]<<",phi="<<(*jetphi_akpu3pf)[indexjets]<<endl;
                            cout<<"Radius between "<<Redges[n]<<"and "<<Redges[n+1]<<endl;
                            cout<<"Dmeson index="<<m<<",Dmeson pt="<<(*Dpt)[m]<<"Dmeson eta="<<(*Deta)[m]<<", phi="<<(*Dphi)[m]<<"radius="<<DeltaR<<endl;
                            cout<<"Delta eta="<<deltaeta<<", deltaphi="<<deltaphi<<endl;
                          }
                          fhHistoMass[n]->Fill((*Dmass)[m]);
                          if(!isData){
                            if(((*Dgen)[m])==23333) fhHistoGenSignal[n]->Fill((*Dmass)[m]);
                            else if (((*Dgen)[m])==23344) fhHistoGenSwapped[n]->Fill((*Dmass)[m]);
                          }
                        }
                      }
                      double zvariable=(*Dpt)[m]/(*jetpt_akpu3pf)[indexjets];

                      for (int nz=0; nz<nZedges; nz++){
                        if(zvariable>Zedges[nz]&&zvariable<Zedges[nz+1]){
                          fhHistoZMass[nz]->Fill((*Dmass)[m]);
                          if(!isData){
                            if(((*Dgen)[m])==23333) fhHistoZGenSignal[nz]->Fill((*Dmass)[m]);
                            else if (((*Dgen)[m])==23344) fhHistoZGenSwapped[nz]->Fill((*Dmass)[m]);
                          }
                        }
                      }//end of loop over z
                    }           
                  }
                }
              }
            }
          }
        }
      }
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
