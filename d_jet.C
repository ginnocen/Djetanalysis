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
            for (int indexDm = 0; indexDm < Dsize; indexDm++) {
              if((*Dpt)[indexDm] >fDptlow_cut && (*Dpt)[indexDm] <fDpthigh_cut){
                if ( fabs((*Dy)[indexDm]) < fDy_cut  && ((*DsvpvDistance)[indexDm] / (*DsvpvDisErr)[indexDm]) > fDdecaylength_cut && (*Dalpha)[indexDm] < fDalpha_cut && (*Dchi2cl)[indexDm] > fDchi2cl_cut ) {
                  if(fabs((*Dtrk1Eta)[indexDm]) < fDtrketa_cut && fabs((*Dtrk2Eta)[indexDm]) < fDtrketa_cut && (*Dtrk1Pt)[indexDm] > fDtrkptmin_cut && (*Dtrk2Pt)[indexDm] > fDtrkptmin_cut){
                    if(((*Dtrk1PtErr)[indexDm] / (*Dtrk1Pt)[indexDm]) < fDtrkpterr_cut && ((*Dtrk2PtErr)[indexDm] / (*Dtrk2Pt)[indexDm]) < fDtrkpterr_cut && (*Dtrk1highPurity)[indexDm]==1 && (*Dtrk2highPurity)[indexDm]==1){
                      double deltaphi = acos(cos((*Dphi)[indexDm] - (*jetphi_akpu3pf)[indexjets]));
                      double deltaeta = (*Deta)[indexDm] - (*jeteta_akpu3pf)[indexjets];
                      double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                    
                      for (int indexR=0; indexR<nRedges; indexR++){ 
                        if(DeltaR>Redges[indexR]&&DeltaR<Redges[indexR+1]){
                          if(debugmode){
                            cout<<"leading jet pt"<<(*jetpt_akpu3pf)[0]<<",eta="<<(*jeteta_akpu3pf)[indexjets]<<",phi="<<(*jetphi_akpu3pf)[indexjets]<<endl;
                            cout<<"Radius between "<<Redges[indexR]<<"and "<<Redges[indexR+1]<<endl;
                            cout<<"Dmeson index="<<indexDm<<",Dmeson pt="<<(*Dpt)[indexDm]<<"Dmeson eta="<<(*Deta)[indexDm]<<", phi="<<(*Dphi)[indexDm]<<"radius="<<DeltaR<<endl;
                            cout<<"Delta eta="<<deltaeta<<", deltaphi="<<deltaphi<<endl;
                          }
                          fhHistoMass[indexR]->Fill((*Dmass)[indexDm]);
                          if(!isData){
                            if(((*Dgen)[indexDm])==23333) fhHistoGenSignal[indexR]->Fill((*Dmass)[indexDm]);
                            else if (((*Dgen)[indexDm])==23344) fhHistoGenSwapped[indexR]->Fill((*Dmass)[indexDm]);
                          }
                        }//selection on R
                      }//end of loop over R
 
                      double zvariable=(*Dpt)[indexDm]/(*jetpt_akpu3pf)[indexjets];

                      for (int indexZ=0; indexZ<nZedges; indexZ++){
                        if(zvariable>Zedges[indexZ]&&zvariable<Zedges[indexZ+1]){
                          fhHistoZMass[indexZ]->Fill((*Dmass)[indexDm]);
                          if(!isData){
                            if(((*Dgen)[indexDm])==23333) fhHistoZGenSignal[indexZ]->Fill((*Dmass)[indexDm]);
                            else if (((*Dgen)[indexDm])==23344) fhHistoZGenSwapped[indexZ]->Fill((*Dmass)[indexDm]);
                          }
                        }//selection on z
                      }//end of loop over z
                    }//track selection2           
                  }//trackselection
                }//D meson selection 
              }//pt cut on D mesons
            }//loop over D mesons
          } // selection on jet pt
        } //end of loop over jets
      }//end of loop over events
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
