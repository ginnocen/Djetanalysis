#include "d_jet.h"

#include "TFile.h"
#include "TH1.h"

int djet::d_jet(std::string output) {
    if (fChain == 0)
        return 1;

    TFile* foutput = new TFile(output.c_str(), "recreate");
    for (int i=0;i<5;i++){
      fhHistoMass[i]->Write();
      fhHistoGenSignal[i]->Write();  
      fhHistoGenSwapped[i]->Write();  
    }
    foutput->Close();
    delete foutput;
   return 0;
}

int djet::loop(int isData,double jetpt_cut,double jeteta_cut, double Dptlow_cut, double Dpthigh_cut, double Dy_cut, double decaylength_cut, double Dalpha_cut, double trkptmin_cut, double trketa_cut, double trkpterr_cut, double chi2cl_cut) {
    
    int64_t nentries = fChain->GetEntriesFast();
    for (int64_t jentry = 0; jentry < nentries; jentry++) {
        if (jentry % 1000 == 0)
            printf("%li/%li\n", jentry, nentries);

        if (LoadTree(jentry) < 0) break;
        fChain->GetEntry(jentry);
        if (!(Dsize > 0 && njet_akpu3pf > 0 && (*jetpt_akpu3pf)[0] > jetpt_cut && fabs((*jeteta_akpu3pf)[0]) < jeteta_cut)) continue;
        for (int m = 0; m < Dsize; m++) { 
            if((*Dpt)[m] >Dptlow_cut && (*Dpt)[m] <Dpthigh_cut){
               if ( fabs((*Dy)[m]) < Dy_cut  && ((*DsvpvDistance)[m] / (*DsvpvDisErr)[m]) > decaylength_cut && (*Dalpha)[m] < Dalpha_cut && (*Dchi2cl)[m] > chi2cl_cut ) {
                  if(fabs((*Dtrk1Eta)[m]) < trketa_cut && fabs((*Dtrk2Eta)[m]) < trketa_cut && (*Dtrk1Pt)[m] > trkptmin_cut && (*Dtrk2Pt)[m] > trkptmin_cut){
                    if(((*Dtrk1PtErr)[m] / (*Dtrk1Pt)[m]) < trkpterr_cut && ((*Dtrk2PtErr)[m] / (*Dtrk2Pt)[m]) < trkpterr_cut){
                       double deltaphi = acos(cos((*Dphi)[m] - (*jetphi_akpu3pf)[0]));
                       double deltaeta = (*Deta)[m] - (*jeteta_akpu3pf)[0];
                       double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
               
                       for (int n=0; n<5; n++){ 
                         if(DeltaR>Redges[n]&&DeltaR<Redges[n+1]){
                           fhHistoMass[n]->Fill((*Dmass)[m]);
                           if(!isData){
                             if(((*Dgen)[m])==23333) fhHistoGenSignal[n]->Fill((*Dmass)[m]);
                             else if (((*Dgen)[m])==23344) fhHistoGenSwapped[n]->Fill((*Dmass)[m]);
                           }
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
