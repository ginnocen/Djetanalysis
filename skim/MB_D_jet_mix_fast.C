#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "D_jet_tree.h"
#include "MBsubtract_config.h"

std::vector <std::vector <std::vector <std::vector <Int_t> > > > get_sorted_events(std::string MBfile, int isMC, int isPP)
{
    std::cout<<"Cut Configuration :"<<std::endl;
    std::cout<<"cut_vz = "<< cut_vz <<std::endl;
    std::cout<<"cut_pcollisionEventSelection = "<< cut_pcollisionEventSelection <<std::endl;

    std::cout<<"nJetCollections = "<< nJetCollections <<std::endl;
    for (int i=0; i<nJetCollections; ++i) {
        std::cout << Form("jetCollections[%d] = %s", i, jetCollections.at(i).c_str()) << std::endl;
    }
    std::cout<<"nMaxEvents_minBiasMixing = "<< nMaxEvents_minBiasMixing <<std::endl;
    std::cout<<"nCentralityBins          = "<< nCentralityBins <<std::endl;
    std::cout<<"nVertexBins              = "<< nVertexBins <<std::endl;
    std::cout<<"nEventPlaneBins          = "<< nEventPlaneBins <<std::endl;

    std::cout<<"#####"<< std::endl;
    std::cout<<MBfile << std::endl;
    std::cout<<"##### END #####"<< std::endl;

    TFile* f = TFile::Open(MBfile.c_str(),"read");
    TTree* t = (TTree*)f->Get("hiEvtAnalyzer/HiTree");
    TTree* hlt = (TTree*)f->Get("skimanalysis/HltTree");
    
    if(!t)
    {
        std::cout << "Unable to get event tree. Check MB file." << std::endl;
        return {{{{}}}};
    }
    //initialize sorting vector
    std::vector <std::vector <std::vector <std::vector <Int_t> > > > 
        list(nCentralityBins, 
            std::vector <std::vector <std::vector <Int_t> > >(nVertexBins,
                std::vector <std::vector <Int_t> >(nEventPlaneBins,
                    std::vector <Int_t>() ) ) );
    int hiBin;
    float vz;
    float hiEvtPlanes[29];

    int pcollisionEventSelection;
    int HBHENoiseFilterResultRun2Loose;
    int pPAprimaryVertexFilter;
    int pBeamScrapingFilter;

    t->SetBranchAddress("hiBin",&hiBin);
    t->SetBranchAddress("vz",&vz);
    t->SetBranchAddress("hiEvtPlanes",hiEvtPlanes);

    hlt->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection);
    hlt->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose);
    hlt->SetBranchAddress("pPAprimaryVertexFilter", &pPAprimaryVertexFilter);
    hlt->SetBranchAddress("pBeamScrapingFilter", &pBeamScrapingFilter);

    Int_t nentries = t->GetEntries();
    Int_t vzrejected = 0;
    Int_t hltrejected = 0;

    for(Int_t i=0;i<nentries;i++)
    {
        if(i % 10000 == 0) std::cout << i << " / " << nentries << std::endl;
        //determine correct bin
        t->GetEntry(i);
        if (fabs(vz) > cut_vz) {vzrejected++; continue;}
        if (!isPP) {  // HI event selection
            if ((pcollisionEventSelection < 1)) {hltrejected++; continue;}
            if (!isMC) {
                if (HBHENoiseFilterResultRun2Loose < 1) {hltrejected++; continue;}
            }
        } else {      // pp event selection
            if (pPAprimaryVertexFilter < 1 || pBeamScrapingFilter < 1) {hltrejected++; continue;}
        }
        int centbinwidth = 200/nCentralityBins;
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
        //assign index to correct bin
        if(centbin<0 || centbin>=nCentralityBins)
        {
            std::cout << i << ": bad centbin " << centbin << " for hiBin " << hiBin << std::endl;
            continue;
        }
        if(vzbin<0 || vzbin>=nVertexBins)
        {
            std::cout << i << ": bad vzbin " << vzbin << std::endl;
            continue;
        }
        if(evplaneBin<0 || evplaneBin>=nEventPlaneBins)
        {
            std::cout << i << ": bad evplanebin " << evplaneBin << std::endl;
            continue;
        }
        list[centbin][vzbin][evplaneBin].push_back(i);
    }
    std::cout << "Event list formed." << std::endl;
    int nlowbins = 0;
    std::vector<std::string> lowbinslist;
    for(int i=0;i<nCentralityBins;i++)
    {
        for(int j=0;j<nVertexBins;j++)
        {
            for(int k=0;k<nEventPlaneBins;k++)
            {
                if(list[i][j][k].size()<100)
                {
                    nlowbins++;
                    lowbinslist.push_back(Form("centbin: %d vzbin: %d evplanebin: %d numevents: %d",i,j,k,list[i][j][k].size()));
                }
            }
        }
    }
    if(nlowbins!=0)
    {
        std::cout << "CAUTION: Less than 100 entries in the following bins:" << std::endl;
        for(int i=0;i<(int)lowbinslist.size();i++) std::cout << lowbinslist[i] << std::endl;
    }
    f->Close();
    std::cout << "vzreject " << vzrejected << std::endl;
    std::cout << "hltreject " << hltrejected << std::endl;
    return list;
}

int MB_D_jet_mix(std::string Djetfile, std::string MBfile, std::vector <std::vector <std::vector <std::vector <Int_t> > > > list, std::string output)
{
    if(list[0][0][0].size()==0)
    {
        std::cout << "List creation failed." << std::endl;
        return -3;
    }

    //input tree variables
    int hiBin;
    float vz;
    float hiEvtPlanes[29];

    //MB tree variables
    int MBnref;
    //Float_t MBjetptCorr[maxjets];
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
    
    TTree* MBjets = (TTree*)minbiasfile->Get("akPu3PFJetAnalyzer/t");
    if(!MBjets)
    {
        std::cout << "Could not get MB tree. Check MB input file." << std::endl;
        return -2;
    }
    MBjets->SetBranchAddress("nref",&MBnref);
    MBjets->SetBranchAddress("jtpt",MBjetpt);
    //MBjets->SetBranchAddress("rawpt",MBjetpt);
    MBjets->SetBranchAddress("jteta",MBjeteta);
    MBjets->SetBranchAddress("jtphi",MBjetphi);
    MBjets->SetBranchAddress("chargedSum",MBchargedSum);

    TFile* outfile = new TFile(output.c_str(),"recreate");
    //initialize output tree
    TTree* djtMB_out = new TTree("djt","MB-mixed Djet events");
    TTree* hlt_out = new TTree("hlt","MB-mixed Djet events");
    DJetTree djt(djtMB_out);
    
    //set Djet branch addresses

    djt_tree->SetBranchStatus("*",1);
    djtMB_out->SetBranchStatus("*",1); 
    hlt_tree->SetBranchStatus("*",1);

    //int nevents = djt_tree->GetEntries();
    int nevents=5000;
    djtMB_out->CopyAddresses(djt_tree);
    hlt_out->CopyAddresses(hlt_tree);

    djt_tree->SetBranchAddress("hiBin",&hiBin);
    djt_tree->SetBranchAddress("vz",&vz);
    djt_tree->SetBranchAddress("hiEvtPlanes",hiEvtPlanes);

    int listposition[nCentralityBins][nVertexBins][nEventPlaneBins];
    for(int i=0;i<nCentralityBins;i++) for(int j=0;j<nVertexBins;j++) for(int k=0;k<nEventPlaneBins;k++) listposition[i][j][k]=0;

    Int_t mixptreject = 0;

    //event loop
    for(int i=0;i<nevents;i++)
    {
        if(i % 1000 == 0) std::cout << i << " / " << nevents << std::endl;
        djt_tree->GetEntry(i);
        //std::cout << "entry" << std::endl;
        //determine appropriate MB jet tree
        int centbinwidth = round(200/nCentralityBins);
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
            //int nMBevents = list[centbin][vzbin][evplaneBin].size();
            //std::cout << nMB3events << std::endl;
            //std::cout << "3entries" << std::endl;
            //int randindex = rand.Integer(nMBevents);
            //MBjets->GetEntry(randindex);
            int entry = listposition[centbin][vzbin][evplaneBin];
            MBjets->GetEntry(list[centbin][vzbin][evplaneBin][entry]);
            listposition[centbin][vzbin][evplaneBin]++;
            if(entry >= (int)list[centbin][vzbin][evplaneBin].size()) listposition[centbin][vzbin][evplaneBin] = 0;
            //std::cout << "3randentry" << std::endl;
            //replace jet variables with MB jet variables
            djt.njet_akpu3pf = MBnref;
            //std::cout << MBnref << std::endl;
            //djt.jetptCorr_akpu3pf.clear();
            djt.jetpt_akpu3pf.clear();
            djt.jeteta_akpu3pf.clear();
            djt.jetphi_akpu3pf.clear();
            djt.chargedSum_akpu3pf.clear();
            //std::cout << "3clear" << std::endl;
            int cutnref = 0;
            for(int k=0;k<MBnref;k++)
            {
                if (MBjetpt[k] > jetptmin && fabs(MBjeteta[k]) < 2.0)
                {
                    //djt.jetptCorr_akpu3pf.push_back(MBjetptCorr[k]);
                    djt.jetpt_akpu3pf.push_back(MBjetpt[k]);
                    djt.jeteta_akpu3pf.push_back(MBjeteta[k]);
                    djt.jetphi_akpu3pf.push_back(MBjetphi[k]);
                    djt.chargedSum_akpu3pf.push_back(MBchargedSum[k]);
                    //std::cout << k << " " << MBjetpt[k] << std::endl;
                    //std::cout << "3push" << k << std::endl;
                    cutnref++;
                }
                else
                {
                    mixptreject++;
                }
            }
            djt.njet_akpu3pf = cutnref; 
            djtMB_out->Fill();
            hlt_out->Fill();
        }
    }
    outfile->cd();
    djtMB_out->Write("",TObject::kOverwrite);
    hlt_out->Write("",TObject::kOverwrite);
    outfile->Close();
    minbiasfile->Close();
    Dfile->Close();
    std::cout << "mixptreject " << mixptreject << std::endl;
    return 0;
}

int MB_D_jet_mix_fast(std::string Djetfile, std::string MBfile, std::string output, int isMC, int isPP)
{
    MB_D_jet_mix(Djetfile,MBfile,get_sorted_events(MBfile,isMC,isPP),output);
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc==6)
        return MB_D_jet_mix_fast(argv[1],argv[2],argv[3],atoi(argv[4]),atoi(argv[5]));
    else
        printf("Usage: ./MB_D_jet_mix_fast.exe [Djetfile] [MBfile] [output]\n");
    return 1;
}
