#include "djtana.h"
#include "TVector.h"

int MBsubtract_closure(std::string Djetfile, std::string mixfile, std::string genfile, std::string output)
{
    //grab Djet data
    int plotdphi = 1;
    int plotdr = 1;
    TFile* djf = TFile::Open(Djetfile.c_str(),"read");
    if(gethists(djf,"plothist")) return -1;
    TH1F* Djet_dr[nPtBins]; 
    TH1F* Djet_dphi[nPtBins];
    TVector nD_djt = *(TVector*)djf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        Djet_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("Djet_dr[%d]",i));
        Djet_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("Djet_dphi[%d]",i));
        //nD_djt[i] = hdr[i]->GetEntries();
    }
    //grab MB-mix data
    TFile* mixf = TFile::Open(mixfile.c_str(),"read");
    if(gethists(mixf,"plothist")) return -1;
    TH1F* mix_dr[nPtBins];
    TH1F* mix_dphi[nPtBins];
    TVector nD_mix = *(TVector*)mixf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        mix_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("mix_dr[%d]",i));
        mix_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("Djet_dphi[%d]",i));
        //nD_mix[i] = hdr[i]->GetEntries();
    }
    //grab gen data
    TFile* genf = TFile::Open(genfile.c_str(),"read");
    if(gethists(genf,"plothist")) return -1;
    TH1F* gen_dr[nPtBins];
    TH1F* gen_dphi[nPtBins];
    TVector nD_gen = *(TVector*)genf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        gen_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("gen_dr[%d]",i));
        gen_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("gen_dphi[%d]",i));
        //nD_gen[i] = hdr[i]->GetEntries();
    }

    //scale by number of D candidates and make MB-subtracted hists
    TH1F* MBsub_dr[nPtBins];
    TH1F* MBsub_dphi[nPtBins];
    TCanvas* cdr;
    TCanvas* cdphi;
    if(plotdr) cdr = new TCanvas("cdr","",600,600);
    if(plotdphi) cdphi = new TCanvas("cdphi","",600,600);
    //TCanvas* d = new TCanvas("d","",600,600);
    if(plotdr) cdr->SetLogy();
    TLegend* ldr[nPtBins];
    TLegend* ldphi[nPtBins];
    TFile* outfile = new TFile(output.c_str(),"recreate");
    //TH1F* ratio[nPtBins];
    for(int i=0;i<nPtBins;i++)
    {
        if(plotdr) cdr->Clear();
        if(plotdphi) cdphi->Clear();
        //d->Clear();

        Djet_dr[i]->Sumw2();
        Djet_dphi[i]->Sumw2();
        mix_dr[i]->Sumw2();
        mix_dphi[i]->Sumw2();
        gen_dr[i]->Sumw2();
        gen_dphi[i]->Sumw2();
        Djet_dr[i]->Scale(1./nD_djt[i]);
        Djet_dphi[i]->Scale(1./nD_djt[i]);
        mix_dr[i]->Scale(1./nD_mix[i]);
        mix_dphi[i]->Scale(1./nD_mix[i]);
        gen_dr[i]->Scale(1./nD_gen[i]);
        gen_dphi[i]->Scale(1./nD_gen[i]);
        MBsub_dr[i] = (TH1F*)Djet_dr[i]->Clone(Form("MBsub_dr[%d]",i));
        MBsub_dphi[i] = (TH1F*)Djet_dphi[i]->Clone(Form("MBsub_dphi[%d]",i));
        MBsub_dr[i]->Add(mix_dr[i],-1);  
        MBsub_dphi[i]->Add(mix_dphi[i],-1);

        TH2F* hemptydr = new TH2F("hemptydr",Form("pt[%d];#Delta R;",i),1,0.,0.5,1,pow(10.,-4),pow(10.,0));
        TH2F* hemptydphi = new TH2F("hemptydphi",Form("pt[%d];#Delta#phi",i),1,0,TMath::Pi(),1,mix_dphi[i]->GetMinimum(),Djet_dphi[i]->GetMaximum());

        if(plotdr)
        {
            std::cout << "dr" << std::endl;
            cdr->cd();
            xjjroot::sethempty(hemptydr,0,0.5);
            hemptydr->Draw();
            xjjroot::setthgrstyle(MBsub_dr[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsub_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(Djet_dr[i],kRed,21,1.2,kRed,1,1,-1,-1,-1);
            Djet_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(mix_dr[i],kBlue,22,1.2,kBlue,1,1,-1,-1,-1);
            mix_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(gen_dr[i],kGreen,20,1.2,kGreen,1,1,-1,-1,-1);
            gen_dr[i]->Draw("pe same");
            ldr[i] = new TLegend(0.75,0.6,0.9,0.7);
            ldr[i]->AddEntry(Djet_dr[i],"Raw","l");
            ldr[i]->AddEntry(mix_dr[i],"Bkgd","l");
            ldr[i]->AddEntry(gen_dr[i],"subid==0","l");
            ldr[i]->AddEntry(MBsub_dr[i],"MB-subtracted","l");
            ldr[i]->Draw();
            xjjroot::drawCMS("PbPb");
            cdr->SaveAs(Form("plots/MBsub_dr_pt_%d.png",i));
        }

        if(plotdphi)
        {
            std::cout << "dphi" << std::endl;
            cdphi->cd();
            xjjroot::sethempty(hemptydphi,0,0.5);
            hemptydphi->Draw();
            xjjroot::setthgrstyle(MBsub_dphi[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsub_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(Djet_dphi[i],kRed,21,1.2,kRed,1,1,-1,-1,-1);
            Djet_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(mix_dphi[i],kBlue,22,1.2,kBlue,1,1,-1,-1,-1);
            mix_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(gen_dphi[i],kGreen,20,1.2,kGreen,1,1,-1,-1,-1);
            gen_dphi[i]->Draw("pe same");
            ldphi[i] = new TLegend(0.75,0.6,0.9,0.7);
            ldphi[i]->AddEntry(Djet_dphi[i],"Raw","l");
            ldphi[i]->AddEntry(mix_dphi[i],"Bkgd","l");
            ldphi[i]->AddEntry(gen_dphi[i],"subid==0","l");
            ldphi[i]->AddEntry(MBsub_dphi[i],"MB-subtracted","l");
            ldphi[i]->Draw();
            xjjroot::drawCMS("PbPb");
            cdphi->SaveAs(Form("plots/MBsub_dphi_pt_%d.png",i));
        }
/*
        d->cd();
        TH2F* ratioempty = new TH2F("ratioempty",Form("pt[%d];#Delta R;",i),1,0.,TMath::Pi(),1,0.,5.);
        xjjroot::sethempty(ratioempty,0,0.5);
        ratioempty->Draw();
        ratio[i] = (TH1F*)Djet_dphi[i]->Clone(Form("ratio[%d]",i));
        ratio[i]->Sumw2();
        ratio[i]->Divide(MBsub_dphi[i]);
        ratio[i]->Draw("pe same");
        d->SaveAs(Form("plots/MBsubratio_pt_%d.png",i));
*/

        Djet_dr[i]->Write();
        mix_dr[i]->Write();
        MBsub_dr[i]->Write();
        gen_dr[i]->Write();
        Djet_dphi[i]->Write();
        mix_dphi[i]->Write();
        MBsub_dphi[i]->Write();
        gen_dphi[i]->Write();

        delete hemptydr;
        delete hemptydphi;
        //delete ratioempty;
        if(plotdr) delete ldr[i];
        if(plotdphi) delete ldphi[i];
    }
    djf->Close();
    mixf->Close();
    genf->Close();
    outfile->Close();
    delete cdr;
    delete cdphi;
    //delete d;
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
