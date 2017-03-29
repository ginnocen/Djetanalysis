#include "d_jet.h"

#include "TFile.h"
#include "TH1.h"

int djet::d_jet(std::string output) {
    if (fChain == 0)
        return 1;

    TFile* foutput = new TFile(output.c_str(), "recreate");

    TH1D* hInCone = new TH1D("hInCone", "hInCone", 50, 1.7, 2.1);
    TH1D* hOutCone = new TH1D("hOutCone", "hOutCone", 50, 1.7, 2.1);

    int64_t nentries = fChain->GetEntriesFast();
    for (int64_t jentry = 0; jentry < nentries; jentry++) {
        if (jentry % 1000 == 0)
            printf("%li/%li\n", jentry, nentries);

        if (LoadTree(jentry) < 0) break;
        fChain->GetEntry(jentry);

        if (!(Dsize > 0 && njet_akpu3pf > 0 && (*jetpt_akpu3pf)[0] > 60)) continue;

        for (int m = 0; m < Dsize; m++) {
            if (((*DsvpvDistance)[m] / (*DsvpvDisErr)[m]) > 4.06 && (*Dpt)[m] > 20) {
                double deltaphi = acos(cos((*Dphi)[m] - (*jetphi_akpu3pf)[0]));
                double deltaeta = (*Deta)[m] - (*jeteta_akpu3pf)[0];
                double DeltaR = sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
                if (DeltaR < 0.5) hInCone->Fill((*Dmass)[m]);
                else hOutCone->Fill((*Dmass)[m]);
            }
        }
    }

    foutput->Write("", TObject::kOverwrite);
    foutput->Close();

    return 0;
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
