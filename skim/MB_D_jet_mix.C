#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "D_jet_tree.h"

int MB_D_jet_mix(std::string Djetfile, std::string MBfile, std::string output)
{
    //mixing parameters
    std::vector<std::string> jetCollections = {"akPu3PFJetAnalyzer", "akPu4PFJetAnalyzer"};
    const int nJetCollections = jetCollections.size();
    const int nCentralityBins = 5;
    const int nVertexBins = 3;
    const int nEventPlaneBins = 3;
    const int nEventsToMix = 40;

    //input tree variables
    int hiBin;
    float vz;
    float hiEvtPlanes[29];
    int njet_akpu3pf;
    std::vector<float> *jetptCorr_akpu3pf=0;
    std::vector<float> *jetpt_akpu3pf=0;
    std::vector<float> *jeteta_akpu3pf=0;
    std::vector<float> *jetphi_akpu3pf=0;
    //std::vector<int> *jetnpfpart_akpu3pf;
    //std::vector<float> *gjetpt_akpu3pf;
    //std::vector<float> *gjeteta_akpu3pf;
    //std::vector<float> *gjetphi_akpu3pf;
    //std::vector<int> *gjetflavor_akpu3pf;
    std::vector<float> *chargedSum_akpu3pf=0;
    //std::vector<int> *subid_akpu3pf;

    /*
    //int ngen_akpu3pf;
    std::vector<float> *genpt_akpu3pf;
    std::vector<float> *geneta_akpu3pf;
    std::vector<float> *genphi_akpu3pf;
    std::vector<int> *gensubid_akpu3pf;
    */
    int njet_akpu4pf;
    std::vector<float> *jetptCorr_akpu4pf=0;
    std::vector<float> *jetpt_akpu4pf=0;
    std::vector<float> *jeteta_akpu4pf=0;
    std::vector<float> *jetphi_akpu4pf=0;
    //std::vector<float> *gjetpt_akpu4pf;
    //std::vector<float> *gjeteta_akpu4pf;
    //std::vector<float> *gjetphi_akpu4pf;
    //std::vector<int> *gjetflavor_akpu4pf;
    std::vector<float> *chargedSum_akpu4pf=0;
    //std::vector<int> *subid_akpu4pf;

    /*
    //int ngen_akpu4pf;
    std::vector<float> *genpt_akpu4pf;
    std::vector<float> *geneta_akpu4pf;
    std::vector<float> *genphi_akpu4pf;
    std::vector<int> *gensubid_akpu4pf;
    */

    //MB tree variables
    int MBnref;
    int maxjets = 200;
    Float_t MBjetptCorr[maxjets];
    Float_t MBjetpt[maxjets];
    Float_t MBjeteta[maxjets];
    Float_t MBjetphi[maxjets];
    Float_t MBchargedSum[maxjets];

    //output tree variables
    int outhiBin;
    float outvz;
    float outhiEvtPlanes[29];
    int outnjet_akpu3pf;
    std::vector<float> *outjetptCorr_akpu3pf=0;
    std::vector<float> *outjetpt_akpu3pf=0;
    std::vector<float> *outjeteta_akpu3pf=0;
    std::vector<float> *outjetphi_akpu3pf=0;
    
    //std::vector<int> *outjetnpfpart_akpu3pf;
    //std::vector<float> *outgjetpt_akpu3pf;
    //std::vector<float> *outgjeteta_akpu3pf;
    //std::vector<float> *outgjetphi_akpu3pf;
    //std::vector<int> *outgjetflavor_akpu3pf;
    std::vector<float> *outchargedSum_akpu3pf=0;
    //std::vector<int> *outsubid_akpu3pf;
    

    /*
    //int outngen_akpu3pf;
    std::vector<float> *outgenpt_akpu3pf;
    std::vector<float> *outgeneta_akpu3pf;
    std::vector<float> *outgenphi_akpu3pf;
    std::vector<int> *outgensubid_akpu3pf;
    */

    int outnjet_akpu4pf;
    std::vector<float> *outjetptCorr_akpu4pf=0;
    std::vector<float> *outjetpt_akpu4pf=0;
    std::vector<float> *outjeteta_akpu4pf=0;
    std::vector<float> *outjetphi_akpu4pf=0;
    std::vector<float> *outgjetpt_akpu4pf=0;
    std::vector<float> *outgjeteta_akpu4pf=0;
    std::vector<float> *outgjetphi_akpu4pf=0;
    std::vector<int> *outgjetflavor_akpu4pf=0;
    std::vector<float> *outchargedSum_akpu4pf=0;
    std::vector<int> *outsubid_akpu4pf=0;

    /*
    //int outngen_akpu4pf;
    std::vector<float> *outgenpt_akpu4pf;
    std::vector<float> *outgeneta_akpu4pf;
    std::vector<float> *outgenphi_akpu4pf;
    std::vector<int> *outgensubid_akpu4pf;
    */
    
    //extract djet and MB-jet trees from input files
    TFile* Dfile = TFile::Open(Djetfile.c_str(),"read");
    if(Dfile->IsZombie())
    {
        std::cout << "Bad Djet input!" << std::endl;
        return -1;
    }    
    TFile* minbiasfile = TFile::Open(MBfile.c_str(),"read");
    if(minbiasfile->IsZombie())
    {
        std::cout << "Bad MB input!" << std::endl;
        return -1;
    }
    TFile* outfile = new TFile(output.c_str(),"recreate");
    TTree* djt_tree = (TTree*)Dfile->Get("djt");
    if(djt_tree==0)
    {
        std::cout << "Could not get djt tree. Check DJet input file." << std::endl;
        return -2;
    }
    TTree* MBjets[nJetCollections][nCentralityBins][nVertexBins][nEventPlaneBins];
    for(int i=0;i<nJetCollections;i++)
    {
        for(int j=0;j<nCentralityBins;j++)
        {
            for(int k=0;k<nVertexBins;k++)
            {
                for(int l=0;l<nEventPlaneBins;l++)
                {
                    MBjets[i][j][k][l] = (TTree*)minbiasfile->Get(Form("%s_centBin%d_vzBin%d_evPlaneBin%d",jetCollections[i].c_str(),j,k,l));
                    if(!MBjets[i][j][k][l])
                    {
                        std::cout << Form("Could not get MB jet %s_centBin%d_vzBin%d_evPlaneBin%d. Check MB input file.",jetCollections[i].c_str(),j,k,l) << std::endl;
                        return -2;
                    }
                    //set MB jet branch addresses
                    MBjets[i][j][k][l]->SetBranchAddress("nref",&MBnref);
                    MBjets[i][j][k][l]->SetBranchAddress("jtpt",&MBjetptCorr);
                    MBjets[i][j][k][l]->SetBranchAddress("rawpt",&MBjetpt);
                    MBjets[i][j][k][l]->SetBranchAddress("jteta",&MBjeteta);
                    MBjets[i][j][k][l]->SetBranchAddress("jtphi",&MBjetphi);
                    MBjets[i][j][k][l]->SetBranchAddress("chargedSum",&MBchargedSum);
                }
            }
        }
    }


    
    //initialize output tree
    TTree* djtMB_out = new TTree("djtMB","MB-mixed Djet events");
    DJetTree djt(djtMB_out);

    //initialize randomizer
    int seed = 12345;
    TRandom3 rand(seed);
    
    //set Djet branch addresses

    djt_tree->SetBranchAddress("hiBin",&hiBin);
    djt_tree->SetBranchAddress("vz",&vz);
    djt_tree->SetBranchAddress("hiEvtPlanes",hiEvtPlanes);

    djt_tree->SetBranchAddress("njet_akpu3pf",&njet_akpu3pf);
    djt_tree->SetBranchAddress("jetptCorr_akpu3pf",&jetptCorr_akpu3pf);
    djt_tree->SetBranchAddress("jetpt_akpu3pf",&jetpt_akpu3pf);
    djt_tree->SetBranchAddress("jeteta_akpu3pf",&jeteta_akpu3pf);
    djt_tree->SetBranchAddress("jetphi_akpu3pf",&jetphi_akpu3pf);
    djt_tree->SetBranchAddress("chargedSum_akpu3pf",&chargedSum_akpu3pf);

    //gen variables, not needed at present
    /*
    djt_tree->SetBranchAddress("gjetpt_akpu3pf",&gjetpt_akpu3pf);
    djt_tree->SetBranchAddress("gjeteta_akpu3pf",&gjeteta_akpu3pf);
    djt_tree->SetBranchAddress("gjetphi_akpu3pf",&gjetphi_akpu3pf);
    djt_tree->SetBranchAddress("gjetflavor_akpu3pf",&gjetflavor_akpu3pf);
    djt_tree->SetBranchAddress("subid_akpu3pf",&subid_akpu3pf);

    djt_tree->SetBranchAddress("ngen_akpu3pf",&ngen_akpu3pf);
    djt_tree->SetBranchAddress("genpt_akpu3pf",&genpt_akpu3pf);
    djt_tree->SetBranchAddress("geneta_akpu3pf",&geneta_akpu3pf);
    djt_tree->SetBranchAddress("genphi_akpu3pf",&genphi_akpu3pf);
    djt_tree->SetBranchAddress("gensubid_akpu3pf",&gensubid_akpu3pf);
    */

    djt_tree->SetBranchAddress("njet_akpu4pf",&njet_akpu4pf);
    djt_tree->SetBranchAddress("jetptCorr_akpu4pf",&jetptCorr_akpu4pf);
    djt_tree->SetBranchAddress("jetpt_akpu4pf",&jetpt_akpu4pf);
    djt_tree->SetBranchAddress("jeteta_akpu4pf",&jeteta_akpu4pf);
    djt_tree->SetBranchAddress("jetphi_akpu4pf",&jetphi_akpu4pf);
    djt_tree->SetBranchAddress("chargedSum_akpu4pf",&chargedSum_akpu4pf);

    //gen variables, not needed at present
    /*
    djt_tree->SetBranchAddress("gjetpt_akpu4pf",&gjetpt_akpu4pf);
    djt_tree->SetBranchAddress("gjeteta_akpu4pf",&gjeteta_akpu4pf);
    djt_tree->SetBranchAddress("gjetphi_akpu4pf",&gjetphi_akpu4pf);
    djt_tree->SetBranchAddress("gjetflavor_akpu4pf",&gjetflavor_akpu4pf);
    djt_tree->SetBranchAddress("subid_akpu4pf",&subid_akpu4pf);

    djt_tree->SetBranchAddress("ngen_akpu4pf",&ngen_akpu4pf);
    djt_tree->SetBranchAddress("genpt_akpu4pf",&genpt_akpu4pf);
    djt_tree->SetBranchAddress("geneta_akpu4pf",&geneta_akpu4pf);
    djt_tree->SetBranchAddress("genphi_akpu4pf",&genphi_akpu4pf);
    djt_tree->SetBranchAddress("gensubid_akpu4pf",&gensubid_akpu4pf);
    */

    //set output branch addresses

    djtMB_out->SetBranchAddress("hiBin",&outhiBin);
    djtMB_out->SetBranchAddress("vz",&outvz);
    djtMB_out->SetBranchAddress("hiEvtPlanes",outhiEvtPlanes);

    djtMB_out->SetBranchAddress("njet_akpu3pf",&outnjet_akpu3pf);
    djtMB_out->SetBranchAddress("jetptCorr_akpu3pf",&outjetptCorr_akpu3pf);
    djtMB_out->SetBranchAddress("jetpt_akpu3pf",&outjetpt_akpu3pf);
    djtMB_out->SetBranchAddress("jeteta_akpu3pf",&outjeteta_akpu3pf);
    djtMB_out->SetBranchAddress("jetphi_akpu3pf",&outjetphi_akpu3pf);
    djtMB_out->SetBranchAddress("chargedSum_akpu3pf",&outchargedSum_akpu3pf);
    //gen variables, not needed at present
    /*
    djtMB_out->SetBranchAddress("gjetpt_akpu3pf",&outgjetpt_akpu3pf);
    djtMB_out->SetBranchAddress("gjeteta_akpu3pf",&outgjeteta_akpu3pf);
    djtMB_out->SetBranchAddress("gjetphi_akpu3pf",&outgjetphi_akpu3pf);
    djtMB_out->SetBranchAddress("gjetflavor_akpu3pf",&outgjetflavor_akpu3pf);
    djtMB_out->SetBranchAddress("subid_akpu3pf",&outsubid_akpu3pf);

    djtMB_out->SetBranchAddress("ngen_akpu3pf",&outngen_akpu3pf);
    djtMB_out->SetBranchAddress("genpt_akpu3pf",&outgenpt_akpu3pf);
    djtMB_out->SetBranchAddress("geneta_akpu3pf",&outgeneta_akpu3pf);
    djtMB_out->SetBranchAddress("genphi_akpu3pf",&outgenphi_akpu3pf);
    djtMB_out->SetBranchAddress("gensubid_akpu3pf",&outgensubid_akpu3pf);
    */

    djtMB_out->SetBranchAddress("njet_akpu4pf",&outnjet_akpu4pf);
    djtMB_out->SetBranchAddress("jetptCorr_akpu4pf",&outjetptCorr_akpu4pf);
    djtMB_out->SetBranchAddress("jetpt_akpu4pf",&outjetpt_akpu4pf);
    djtMB_out->SetBranchAddress("jeteta_akpu4pf",&outjeteta_akpu4pf);
    djtMB_out->SetBranchAddress("jetphi_akpu4pf",&outjetphi_akpu4pf);
    djtMB_out->SetBranchAddress("gjetpt_akpu4pf",&outgjetpt_akpu4pf);
    djtMB_out->SetBranchAddress("gjeteta_akpu4pf",&outgjeteta_akpu4pf);
    djtMB_out->SetBranchAddress("gjetphi_akpu4pf",&outgjetphi_akpu4pf);
    djtMB_out->SetBranchAddress("gjetflavor_akpu4pf",&outgjetflavor_akpu4pf);
    djtMB_out->SetBranchAddress("chargedSum_akpu4pf",&outchargedSum_akpu4pf);
    djtMB_out->SetBranchAddress("subid_akpu4pf",&outsubid_akpu4pf);

    //djtMB_out->SetBranchAddress("ngen_akpu4pf",&outngen_akpu4pf);
    //djtMB_out->SetBranchAddress("genpt_akpu4pf",&outgenpt_akpu4pf);
    //djtMB_out->SetBranchAddress("geneta_akpu4pf",&outgeneta_akpu4pf);
    //djtMB_out->SetBranchAddress("genphi_akpu4pf",&outgenphi_akpu4pf);
    //djtMB_out->SetBranchAddress("gensubid_akpu4pf",&outgensubid_akpu4pf);  

    djt_tree->SetBranchStatus("*",1);
    djtMB_out->SetBranchStatus("*",1); 

    int nevents = djt_tree->GetEntries();

    //event loop
    for(int i=0;i<nevents;i++)
    {
        std::cout << i << std::endl;
        djt_tree->GetEntry(i);
        //determine appropriate MB jet tree
        int centbinwidth = 200/nCentralityBins;
        int centbin = hiBin/centbinwidth;
        int vzbinwidth = 30/nVertexBins;
        int vzbin = (vz+15)/vzbinwidth;
        float evplaneBinWidth = TMath::Pi()/nEventPlaneBins;
        int evplaneBin = (hiEvtPlanes[8]+(TMath::Pi()/2.)) / evplaneBinWidth;
        //MB mixing loop
        for(int j=0;j<nEventsToMix;j++)
        {
            std::cout << j << std::endl;
            djt_tree->SetBranchStatus("*",1);
            djtMB_out->SetBranchStatus("*",1);
            //copy over everything from djt_tree first
            djt_tree->CopyAddresses(djtMB_out);
            djtMB_out->Fill();
            //choose random MB event in correct bin (akpu3pf)
            djtMB_out->GetEntry(i*nEventsToMix+j);
            int nMB3events = MBjets[0][centbin][vzbin][evplaneBin]->GetEntries();
            MBjets[0][centbin][vzbin][evplaneBin]->GetEntry(rand.Integer(nMB3events));
            //replace jet variables with MB jet variables
            outnjet_akpu3pf      = MBnref;
            std::vector<float> MBjetptCorrvec;
            std::vector<float> MBjetptvec;
            std::vector<float> MBjetetavec;
            std::vector<float> MBjetphivec;
            std::vector<float> MBchargedSumvec;
            for(int k=0;k<MBnref;k++)
            {
                MBjetptCorrvec.push_back(MBjetptCorr[k]);
                MBjetptvec.push_back(MBjetpt[k]);
                MBjetetavec.push_back(MBjeteta[k]);
                MBjetphivec.push_back(MBjetphi[k]);
                MBchargedSumvec.push_back(MBchargedSum[k]);
            }
            std::vector<float>* MBjetptCorrptr = &MBjetptCorrvec;
            std::vector<float>* MBjetptptr = &MBjetptvec;
            std::vector<float>* MBjetetaptr = &MBjetetavec;
            std::vector<float>* MBjetphiptr = &MBjetphivec;
            std::vector<float>* MBchargedSumptr = &MBchargedSumvec;
            outjetptCorr_akpu3pf = MBjetptCorrptr;
            outjetpt_akpu3pf     = MBjetptptr;
            outjeteta_akpu3pf    = MBjetetaptr;
            outjetphi_akpu3pf    = MBjetphiptr;
            outchargedSum_akpu3pf= MBchargedSumptr;
            MBjetptCorrvec.clear();
            MBjetptvec.clear();
            MBjetetavec.clear();
            MBjetphivec.clear();
            MBchargedSumvec.clear();
            //choose random MB event in correct bin (akpu4pf)
            int nMB4events = MBjets[1][centbin][vzbin][evplaneBin]->GetEntries();
            MBjets[1][centbin][vzbin][evplaneBin]->GetEntry(rand.Integer(nMB4events));
            //replace jet variables with MB jet variables
            outnjet_akpu4pf      = MBnref;
            for(int k=0;k<MBnref;k++)
            {
                MBjetptCorrvec.push_back(MBjetptCorr[k]);
                MBjetptvec.push_back(MBjetpt[k]);
                MBjetetavec.push_back(MBjeteta[k]);
                MBjetphivec.push_back(MBjetphi[k]);
                MBchargedSumvec.push_back(MBchargedSum[k]);
            }
            outjetptCorr_akpu4pf = MBjetptCorrptr;
            outjetpt_akpu4pf     = MBjetptptr;
            outjeteta_akpu4pf    = MBjetetaptr;
            outjetphi_akpu4pf    = MBjetphiptr;
            outchargedSum_akpu4pf= MBchargedSumptr;
            MBjetptCorrvec.clear();
            MBjetptvec.clear();
            MBjetetavec.clear();
            MBjetphivec.clear();
            MBchargedSumvec.clear();
        }
        djt_tree->Show(i);
    }
    
    outfile->cd();
    djtMB_out->Write("",TObject::kOverwrite);
    outfile->Close();
    Dfile->Close();
    minbiasfile->Close();

    return 0;
}
int main(int argc, char* argv[])
{
    if(argc==4)
        return MB_D_jet_mix(argv[1],argv[2],argv[3]);
    else
        printf("Usage: ./MB_D_jet_mix.C [Djetfile] [MBfile] [output]\n");
    return 1;
}
