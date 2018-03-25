#include "djtana.h"
#include "TVector.h"

int MBsubtract_closure(std::string Djetfile, std::string mixfile, std::string genfile, std::string output)
{
    //grab Djet data
    TFile* djf = TFile::Open(Djetfile.c_str(),"read");
    if(gethists(djf,"plothist")) return -1;
    TH1F* Djet_dr[nPtBins]; 
    TVector nD_djt = *(TVector*)djf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        Djet_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("Djet_dr[%d]",i));
        //nD_djt[i] = hdr[i]->GetEntries();
        std::cout << i << " " << nD_djt[i] << " " << hJetPhi->GetEntries() << " " << hDdelPhi[i]->GetEntries() << std::endl;
    }
    std::cout << "djt" << std::endl;
    //grab MB-mix data
    TFile* mixf = TFile::Open(mixfile.c_str(),"read");
    if(gethists(mixf,"plothist")) return -1;
    TH1F* mix_dr[nPtBins];
    TVector nD_mix = *(TVector*)mixf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        mix_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("mix_dr[%d]",i));
        //nD_mix[i] = hdr[i]->GetEntries();
        std::cout << i << " " << nD_mix[i] << " " << hJetPhi->GetEntries() << " " << hDdelPhi[i]->GetEntries() << std::endl;
    }
    //grab gen data
    TFile* genf = TFile::Open(genfile.c_str(),"read");
    if(gethists(genf,"plothist")) return -1;
    TH1F* gen_dr[nPtBins];
    TVector nD_gen = *(TVector*)genf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        gen_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("gen_dr[%d]",i));
        //nD_gen[i] = hdr[i]->GetEntries();
        std::cout << i << " " << nD_gen[i] << " " << hJetPhi->GetEntries() << " " << hDdelPhi[i]->GetEntries() << std::endl;
    }
/*
    TFile* bkgf = TFile::Open(bkgdfile.c_str(),"read");
    if(gethists(bkgf,"plothist")) return -1;
    TH1F* bkg_dr[nPtBins];
    TVector nD_bkg = *(TVector*)bkgf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        bkg_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("bkg_dr[%d]",i));
        //nD_gen[i] = hdr[i]->GetEntries();
        std::cout << i << " " << nD_gen[i] << " " << hJetPhi->GetEntries() << " " << hDdelPhi[i]->GetEntries() << std::endl;
    }
*/
    //scale by number of D candidates and make MB-subtracted hists
    TH1F* MBsub_dr[nPtBins];
    TCanvas* c = new TCanvas("c","",600,600);
    TCanvas* d = new TCanvas("d","",600,600);
    c->SetLogy();
    TLegend* l[nPtBins];
    TFile* outfile = new TFile(output.c_str(),"recreate");
    TH1F* ratio[nPtBins];
    TH1F* closure[nPtBins];
    for(int i=0;i<nPtBins;i++)
    {
        c->Clear();
        d->Clear();
        c->cd();
        Djet_dr[i]->Sumw2();
        mix_dr[i]->Sumw2();
        gen_dr[i]->Sumw2();
        Djet_dr[i]->Scale(1./nD_djt[i]);
        mix_dr[i]->Scale(1./nD_mix[i]);
        gen_dr[i]->Scale(1./nD_gen[i]);
        MBsub_dr[i] = (TH1F*)Djet_dr[i]->Clone(Form("MBsub_dr[%d]",i));
        closure[i] = (TH1F*)bkg_dr[i]->Clone(Form("closure[%d]",i));
        closure[i]->Add(gen_dr[i]);
        MBsub_dr[i]->Add(mix_dr[i],-1);  
        std::cout <<  MBsub_dr[i]->GetEntries() << std::endl;  
        TH2F* hempty = new TH2F("hempty",Form("pt[%d];#Delta R;",i),1,0.,0.5,1,pow(10.,-4),pow(10.,0));
        xjjroot::sethempty(hempty,0,0.5);
        hempty->Draw();
        xjjroot::setthgrstyle(MBsub_dr[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
        MBsub_dr[i]->Draw("pe same");
        xjjroot::setthgrstyle(Djet_dr[i],kRed,21,1.2,kRed,1,1,-1,-1,-1);
        Djet_dr[i]->Draw("pe same");
        xjjroot::setthgrstyle(mix_dr[i],kBlue,22,1.2,kBlue,1,1,-1,-1,-1);
        mix_dr[i]->Draw("pe same");
        xjjroot::setthgrstyle(gen_dr[i],kGreen,20,1.2,kGreen,1,1,-1,-1,-1);
        gen_dr[i]->Draw("pe same");
        //xjjroot::setthgrstyle(bkg_dr[i],kOrange,20,1.2,kOrange,1,1,-1,-1,-1);
        //bkg_dr[i]->Draw("pe same");
        //xjjroot::setthgrstyle(closure[i],kGray,20,1.2,kGray,1,1,-1,-1,-1);
        //closure[i]->Draw("pe same");
        l[i] = new TLegend(0.75,0.6,0.9,0.7);
        l[i]->AddEntry(Djet_dr[i],"Raw","l");
        l[i]->AddEntry(mix_dr[i],"Bkgd","l");
        l[i]->AddEntry(gen_dr[i],"subid==0","l");
        l[i]->AddEntry(MBsub_dr[i],"MB-subtracted","l");
        //l[i]->AddEntry(bkg_dr[i],"subid!=0","l");
        l[i]->Draw();
        xjjroot::drawCMS("PbPb");
        d->cd();
        TH2F* ratioempty = new TH2F("ratioempty",Form("pt[%d];#Delta R;",i),1,0.,TMath::Pi(),1,0.,5.);
        xjjroot::sethempty(ratioempty,0,0.5);
        ratioempty->Draw();
        ratio[i] = (TH1F*)Djet_dr[i]->Clone(Form("ratio[%d]",i));
        ratio[i]->Sumw2();
        ratio[i]->Divide(MBsub_dr[i]);
        ratio[i]->Draw("pe same");
        d->SaveAs(Form("plots/MBsubratio_pt_%d.png",i));
        Djet_dr[i]->Write();
        mix_dr[i]->Write();
        MBsub_dr[i]->Write();
        gen_dr[i]->Write();
        c->SaveAs(Form("plots/MBsub_pt_%d.png",i));
        delete hempty;
        delete l[i];
    }
    djf->Close();
    mixf->Close();
    genf->Close();
    outfile->Close();
    delete c;
    delete d;
    delete outfile;
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc==6)
        MBsubtract_closure(argv[1],argv[2],argv[3],argv[4],argv[5]);
    else
        printf("Usage: ./MBsubtract.C [Djetfile] [MBmixfile] [output]\n");
}
