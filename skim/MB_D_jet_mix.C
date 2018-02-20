#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "D_jet_tree.h"
#include "MBsubtract_config.h"

int MB_D_jet_mix(std::string Djetfile, std::string MBfile, std::string output)
{
    //input tree variables
    int hiBin;
    float vz;
    float hiEvtPlanes[29];

    //MB tree variables
    int MBnref;
    Float_t MBjetptCorr[maxjets];
    Float_t MBjetpt[maxjets];
    Float_t MBjeteta[maxjets];
    Float_t MBjetphi[maxjets];
    Float_t MBchargedSum[maxjets];
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
    TTree* djt_tree = (TTree*)Dfile->Get("djt");
    if(djt_tree==0)
    {
        std::cout << "Could not get djt tree. Check DJet input file." << std::endl;
        return -2;
    }
    TTree* hlt_tree = (TTree*)Dfile->Get("hlt");
    if(!hlt_tree)
    {
        std::cout << "Could not get hlt tree. Check DJet input file." << std::endl;
        return -2;
    }
    TFile* minbiasfile = TFile::Open(MBfile.c_str(),"read");
    if(minbiasfile->IsZombie())
    {
        std::cout << "Bad MB input!" << std::endl;
        return -1;
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
                    MBjets[i][j][k][l]->SetBranchAddress("jtpt",MBjetptCorr);
                    MBjets[i][j][k][l]->SetBranchAddress("rawpt",MBjetpt);
                    MBjets[i][j][k][l]->SetBranchAddress("jteta",MBjeteta);
                    MBjets[i][j][k][l]->SetBranchAddress("jtphi",MBjetphi);
                    MBjets[i][j][k][l]->SetBranchAddress("chargedSum",MBchargedSum);
                }
            }
        }
    }


    TFile* outfile = new TFile(output.c_str(),"recreate");
    //initialize output tree
    TTree* djtMB_out = new TTree("djt","MB-mixed Djet events");
    DJetTree djt(djtMB_out);

    //initialize randomizer
    int seed = 12345;
    TRandom3 rand(seed);
    
    //set Djet branch addresses

    djt_tree->SetBranchStatus("*",1);
    djtMB_out->SetBranchStatus("*",1); 
    hlt_tree->SetBranchStatus("*",1);

    int nevents = djt_tree->GetEntries();
    //int nevents=1000;
    djtMB_out->CopyAddresses(djt_tree);

    djt_tree->SetBranchAddress("hiBin",&hiBin);
    djt_tree->SetBranchAddress("vz",&vz);
    djt_tree->SetBranchAddress("hiEvtPlanes",hiEvtPlanes);

    //event loop
    for(int i=0;i<nevents;i++)
    {
        std::cout << i << std::endl;
        djt_tree->GetEntry(i);
        //std::cout << "entry" << std::endl;
        //determine appropriate MB jet tree
        int centbinwidth = 200/nCentralityBins;
        //std::cout << "nCentralityBins " << nCentralityBins << std::endl;
        //std::cout << "hiBin " << hiBin << std::endl;
        //std::cout << "vz" << vz << std::endl;
        //std::cout << "evtPlanes" << hiEvtPlanes[8] << std::endl;
        int centbin = hiBin/centbinwidth;
        //std::cout << "centbin " << centbin << std::endl;
        int vzbinwidth = 30/nVertexBins;
        int vzbin = (vz+15)/vzbinwidth;
        //std::cout << "vzbin " << vzbin << std::endl;
        float evplaneBinWidth = TMath::Pi()/nEventPlaneBins;
        int evplaneBin = (hiEvtPlanes[8]+(TMath::Pi()/2.)) / evplaneBinWidth;
        //std::cout << "evplaneBin " << evplaneBin << std::endl;
        //std::cout << "bins" << std::endl;
        //MB mixing loop
        djt.hiBin = hiBin;
        djt.vz = vz;
        for(int m=0;m<29;m++) djt.hiEvtPlanes[m] = hiEvtPlanes[m];
        for(int j=0;j<nEventsToMix;j++)
        {
            //std::cout << j << std::endl;
            //choose random MB event in correct bin (akpu3pf)
            int nMB3events = MBjets[0][centbin][vzbin][evplaneBin]->GetEntriesFast();
            //std::cout << nMB3events << std::endl;
            //std::cout << "3entries" << std::endl;
            MBjets[0][centbin][vzbin][evplaneBin]->GetEntry(rand.Integer(nMB3events));
            //std::cout << "3randentry" << std::endl;
            //replace jet variables with MB jet variables
            djt.njet_akpu3pf = MBnref;
            djt.jetptCorr_akpu3pf.clear();
            djt.jetpt_akpu3pf.clear();
            djt.jeteta_akpu3pf.clear();
            djt.jetphi_akpu3pf.clear();
            djt.chargedSum_akpu3pf.clear();
            //std::cout << "3clear" << std::endl;
            for(int k=0;k<MBnref;k++)
            {
                djt.jetptCorr_akpu3pf.push_back(MBjetptCorr[k]);
                djt.jetpt_akpu3pf.push_back(MBjetpt[k]);
                djt.jeteta_akpu3pf.push_back(MBjeteta[k]);
                djt.jetphi_akpu3pf.push_back(MBjetphi[k]);
                djt.chargedSum_akpu3pf.push_back(MBchargedSum[k]);
                //std::cout << k << " " << MBjetpt[k] << std::endl;
                //std::cout << "3push" << k << std::endl;
            }
            //choose random MB event in correct bin (akpu4pf)
            int nMB4events = MBjets[2][centbin][vzbin][evplaneBin]->GetEntriesFast();
            //std::cout << "4entries" << std::endl;
            MBjets[2][centbin][vzbin][evplaneBin]->GetEntry(rand.Integer(nMB4events));
            //std::cout << "4randentry" << std::endl;
            //replace jet variables with MB jet variables
            djt.njet_akpu4pf = MBnref;
            djt.jetptCorr_akpu4pf.clear();
            djt.jetpt_akpu4pf.clear();
            djt.jeteta_akpu4pf.clear();
            djt.jetphi_akpu4pf.clear();
            djt.chargedSum_akpu4pf.clear();
            //std::cout << "4clear" << std::endl;
            for(int k=0;k<MBnref;k++)
            {
                djt.jetptCorr_akpu4pf.push_back(MBjetptCorr[k]);
                djt.jetpt_akpu4pf.push_back(MBjetpt[k]);
                djt.jeteta_akpu4pf.push_back(MBjeteta[k]);
                djt.jetphi_akpu4pf.push_back(MBjetphi[k]);
                djt.chargedSum_akpu4pf.push_back(MBchargedSum[k]);
                //std::cout << "4push" << k << std::endl;
            }
            djtMB_out->Fill();
        }
    }
    outfile->cd();
    djtMB_out->Write("",TObject::kOverwrite);
    hlt_tree->Write("",TObject::kOverwrite);
    outfile->Close();
    minbiasfile->Close();
    Dfile->Close();
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
