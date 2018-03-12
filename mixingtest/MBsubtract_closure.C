#include "djtana.h"

int MBsubtract_closure(std::string Djetfile, std::string mixfile, std::string genfile, std::string output)
{
    //grab Djet data
    TFile* djf = TFile::Open(Djetfile.c_str(),"read");
    if(gethists(djf,"plothist")) return -1;
    TH1F* Djet_dphi[nPtBins]; 
    int nD_djt[nPtBins];
    for(int i=0;i<nPtBins;i++)
    {
        Djet_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("Djet_dphi[%d]",i));
        nD_djt[i] = hDPhi[i]->GetEntries();
        std::cout << i << " " << nD_djt[i] << " " << hJetPhi->GetEntries() << " " << hDdelPhi[i]->GetEntries() << std::endl;
    }
    //grab MB-mix data
    TFile* mixf = TFile::Open(mixfile.c_str(),"read");
    if(gethists(mixf,"plothist")) return -1;
    TH1F* mix_dphi[nPtBins];
    int nD_mix[nPtBins];
    for(int i=0;i<nPtBins;i++)
    {
        mix_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("mix_dphi[%d]",i));
        nD_mix[i] = hDPhi[i]->GetEntries();
        std::cout << i << " " << nD_mix[i] << " " << hJetPhi->GetEntries() << " " << hDdelPhi[i]->GetEntries() << std::endl;
    }
    //grab gen data
    TFile* genf = TFile::Open(genfile.c_str(),"read");
    if(gethists(genf,"plothist")) return -1;
    TH1F* gen_dphi[nPtBins];
    int nD_gen[nPtBins];
    for(int i=0;i<nPtBins;i++)
    {
        gen_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("gen_dphi[%d]",i));
        nD_gen[i] = hDPhi[i]->GetEntries();
        std::cout << i << " " << nD_gen[i] << " " << hJetPhi->GetEntries() << " " << hDdelPhi[i]->GetEntries() << std::endl;
    }
    //scale by number of D candidates and make MB-subtracted hists
    TH1F* MBsub_dphi[nPtBins];
    TCanvas* c = new TCanvas("c","",600,600);
    TLegend* l[nPtBins];
    TFile* outfile = new TFile(output.c_str(),"recreate");
    for(int i=0;i<nPtBins;i++)
    {
        c->Clear();
        Djet_dphi[i]->Sumw2();
        mix_dphi[i]->Sumw2();
        gen_dphi[i]->Sumw2();
        Djet_dphi[i]->Scale(1./nD_djt[i]);
        mix_dphi[i]->Scale(1./nD_mix[i]);
        gen_dphi[i]->Scale(1./nD_gen[i]);
        MBsub_dphi[i] = (TH1F*)Djet_dphi[i]->Clone(Form("MBsub_dphi[%d]",i));
        MBsub_dphi[i]->Add(mix_dphi[i],-1);  
        std::cout <<  MBsub_dphi[i]->GetEntries() << std::endl;  
        TH2F* hempty = new TH2F("hempty",Form("pt[%d];#Delta#phi;",i),1,0.,TMath::Pi(),1,gen_dphi[i]->GetMinimum(),Djet_dphi[i]->GetMaximum());
        xjjroot::sethempty(hempty,0,0.5);
        hempty->Draw();
        xjjroot::setthgrstyle(MBsub_dphi[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
        MBsub_dphi[i]->Draw("pe same");
        xjjroot::setthgrstyle(Djet_dphi[i],kRed,21,1.2,kRed,1,1,-1,-1,-1);
        Djet_dphi[i]->Draw("pe same");
        xjjroot::setthgrstyle(mix_dphi[i],kBlue,22,1.2,kBlue,1,1,-1,-1,-1);
        mix_dphi[i]->Draw("pe same");
        xjjroot::setthgrstyle(gen_dphi[i],kGreen,20,1.2,kGreen,1,1,-1,-1,-1);
        gen_dphi[i]->Draw("pe same");
        l[i] = new TLegend(0.1,0.5,0.35,0.6);
        l[i]->AddEntry(Djet_dphi[i],"Raw","l");
        l[i]->AddEntry(mix_dphi[i],"Bkgd","l");
        l[i]->AddEntry(gen_dphi[i],"Gen","l");
        l[i]->AddEntry(MBsub_dphi[i],"MB-subtracted","l");
        l[i]->Draw();
        xjjroot::drawCMS("PbPb");
        Djet_dphi[i]->Write();
        mix_dphi[i]->Write();
        MBsub_dphi[i]->Write();
        gen_dphi[i]->Write();
        c->SaveAs(Form("plots/MBsub_pt_%d.png",i));
        delete hempty;
        delete l[i];
    }
    djf->Close();
    mixf->Close();
    genf->Close();
    outfile->Close();
    delete c;
    delete outfile;
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc==5)
        MBsubtract_closure(argv[1],argv[2],argv[3],argv[4]);
    else
        printf("Usage: ./MBsubtract.C [Djetfile] [MBmixfile] [output]\n");
}
