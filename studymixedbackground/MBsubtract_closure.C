#include "djtana.h"
#include "TVector.h"

int MBsubtract_closure(std::string Djetfile, std::string mixjetfile, std::string mixDfile, std::string mixbothfile, std::string genfile, std::string output, Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
    //grab Djet data
    xjjroot::setgstyle();
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
    TFile* mixjetf = TFile::Open(mixjetfile.c_str(),"read");
    if(gethists(mixjetf,"plothist")) return -1;
    TH1F* mixjet_dr[nPtBins];
    TH1F* mixjet_dphi[nPtBins];
    TVector nD_mixjet = *(TVector*)mixjetf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        mixjet_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("mixjet_dr[%d]",i));
        mixjet_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("mixjet_dphi[%d]",i));
        //nD_mix[i] = hdr[i]->GetEntries();
    }
    TFile* mixDf = TFile::Open(mixDfile.c_str(),"read");
    if(gethists(mixDf,"plothist")) return -1;
    TH1F* mixD_dr[nPtBins];
    TH1F* mixD_dphi[nPtBins];
    TVector nD_mixD = *(TVector*)mixDf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        mixD_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("mixD_dr[%d]",i));
        mixD_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("mixD_dphi[%d]",i));
        //nD_mix[i] = hdr[i]->GetEntries();
    }
    TFile* mixbothf = TFile::Open(mixbothfile.c_str(),"read");
    if(gethists(mixbothf,"plothist")) return -1;
    TH1F* mixboth_dr[nPtBins];
    TH1F* mixboth_dphi[nPtBins];
    TVector nD_mixboth = *(TVector*)mixbothf->Get("nD");
    for(int i=0;i<nPtBins;i++)
    {
        mixboth_dr[i] = (TH1F*)ahNumREfficiency[0][i]->Clone(Form("mixboth_dr[%d]",i));
        mixboth_dphi[i] = (TH1F*)hDdelPhi[i]->Clone(Form("mixboth_dphi[%d]",i));
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
    TH1F* MBsubratio_dr[nPtBins];
    TH1F* MBsubratio_dphi[nPtBins];
    TH1F* mixjet_clean_dr[nPtBins];
    TH1F* mixD_clean_dr[nPtBins];
    TH1F* mixjet_clean_dphi[nPtBins];
    TH1F* mixD_clean_dphi[nPtBins];
    TH1F* mixjet_clean_dr_ratio[nPtBins];
    TH1F* mixD_clean_dr_ratio[nPtBins];
    TH1F* mixjet_clean_dphi_ratio[nPtBins];
    TH1F* mixD_clean_dphi_ratio[nPtBins];
    TH1F* mixboth_dr_ratio[nPtBins];
    TH1F* mixboth_dphi_ratio[nPtBins];
    TCanvas* cdr;
    TCanvas* bdr;
    TCanvas* cdphi;
    TCanvas* bdphi;

    if(plotdr) {cdr = new TCanvas("cdr","",600,600); bdr = new TCanvas("bdr","",600,600);}
    if(plotdphi) {cdphi = new TCanvas("cdphi","",600,600); bdphi = new TCanvas("bdphi","",600,600);}
    //TCanvas* d = new TCanvas("d","",600,600);
    if(plotdr) cdr->SetLogy();
    TLegend* ldr[nPtBins];
    TLegend* lbdr[nPtBins];
    TLegend* ldphi[nPtBins];
    TLegend* lbdphi[nPtBins];
    TFile* outfile = new TFile(output.c_str(),"recreate");
    std::vector<TString>             ptbinlabel    =  {"4 < p_{T}^{D} < 20 GeV/c","p_{T}^{D} > 20 GeV/c"};
    std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
    //TH1F* ratio[nPtBins];
    for(int i=0;i<nPtBins;i++)
    {
        if(plotdr) {cdr->Clear(); bdr->Clear();}
        if(plotdphi) {cdphi->Clear(); bdphi->Clear();}
        //d->Clear();

        Djet_dr[i]->Sumw2();
        Djet_dphi[i]->Sumw2();
        mixjet_dr[i]->Sumw2();
        mixjet_dphi[i]->Sumw2();
        mixD_dr[i]->Sumw2();
        mixD_dphi[i]->Sumw2();
        mixboth_dr[i]->Sumw2();
        mixboth_dphi[i]->Sumw2();
        gen_dr[i]->Sumw2();
        gen_dphi[i]->Sumw2();

        Djet_dr[i]->Scale(1./nD_djt[i]);
        Djet_dphi[i]->Scale(1./nD_djt[i]);
        mixjet_dr[i]->Scale(1./nD_mixjet[i]);
        mixjet_dphi[i]->Scale(1./nD_mixjet[i]);
        mixD_dr[i]->Scale(1./nD_mixD[i]);
        mixD_dphi[i]->Scale(1./nD_mixD[i]);
        mixboth_dr[i]->Scale(1./nD_mixboth[i]);
        mixboth_dphi[i]->Scale(1./nD_mixboth[i]);
        gen_dr[i]->Scale(1./nD_gen[i]);
        gen_dphi[i]->Scale(1./nD_gen[i]);

        MBsub_dr[i] = (TH1F*)Djet_dr[i]->Clone(Form("MBsub_dr[%d]",i));
        MBsub_dphi[i] = (TH1F*)Djet_dphi[i]->Clone(Form("MBsub_dphi[%d]",i));
        MBsub_dr[i]->Add(mixjet_dr[i],-1);
        MBsub_dr[i]->Add(mixD_dr[i],-1);
        MBsub_dr[i]->Add(mixboth_dr[i],1);  
        MBsub_dphi[i]->Add(mixjet_dphi[i],-1);
        MBsub_dphi[i]->Add(mixD_dphi[i],-1);
        MBsub_dphi[i]->Add(mixboth_dphi[i],1);

        mixjet_clean_dr[i] = (TH1F*)mixjet_dr[i]->Clone(Form("mixjet_clean_dr[%d]",i));
        mixjet_clean_dphi[i] = (TH1F*)mixjet_dphi[i]->Clone(Form("mixjet_clean_dphi[%d]",i));
        mixjet_clean_dr[i]->Add(mixboth_dr[i],-1);
        mixjet_clean_dphi[i]->Add(mixboth_dphi[i],-1);

        mixjet_clean_dr_ratio[i] = (TH1F*)mixjet_clean_dr[i]->Clone(Form("mixjet_clean_dr_ratio[%d]",i));
        mixjet_clean_dphi_ratio[i] = (TH1F*)mixjet_clean_dphi[i]->Clone(Form("mixjet_clean_dphi_ratio[%d]",i));
        mixjet_clean_dr_ratio[i]->Sumw2();
        mixjet_clean_dphi_ratio[i]->Sumw2();
        mixjet_clean_dr_ratio[i]->Divide(MBsub_dr[i]);
        mixjet_clean_dphi_ratio[i]->Divide(MBsub_dphi[i]);

        mixD_clean_dr[i] = (TH1F*)mixD_dr[i]->Clone(Form("mixD_clean_dr[%d]",i));
        mixD_clean_dphi[i] = (TH1F*)mixD_dphi[i]->Clone(Form("mixD_clean_dphi[%d]",i));
        mixD_clean_dr[i]->Add(mixboth_dr[i],-1);
        mixD_clean_dphi[i]->Add(mixboth_dphi[i],-1);

        mixD_clean_dr_ratio[i] = (TH1F*)mixD_clean_dr[i]->Clone(Form("mixD_clean_dr_ratio[%d]",i));
        mixD_clean_dphi_ratio[i] = (TH1F*)mixD_clean_dphi[i]->Clone(Form("mixD_clean_dphi_ratio[%d]",i));
        mixD_clean_dr_ratio[i]->Sumw2();
        mixD_clean_dphi_ratio[i]->Sumw2();
        mixD_clean_dr_ratio[i]->Divide(MBsub_dr[i]);
        mixD_clean_dphi_ratio[i]->Divide(MBsub_dphi[i]);

        mixboth_dr_ratio[i] = (TH1F*)mixboth_dr[i]->Clone(Form("mixboth_dr_ratio[%d]",i));
        mixboth_dphi_ratio[i] = (TH1F*)mixboth_dphi[i]->Clone(Form("mixboth_dphi_ratio[%d]",i));
        mixboth_dr_ratio[i]->Sumw2();
        mixboth_dphi_ratio[i]->Sumw2();
        mixboth_dr_ratio[i]->Divide(MBsub_dr[i]);
        mixboth_dphi_ratio[i]->Divide(MBsub_dphi[i]);

        MBsubratio_dr[i] = (TH1F*)MBsub_dr[i]->Clone(Form("MBsubratio_dr[%d]",i));
        MBsubratio_dr[i]->Sumw2();
        MBsubratio_dr[i]->Divide(gen_dr[i]);
        MBsubratio_dphi[i] = (TH1F*) MBsub_dphi[i]->Clone(Form("MBsubratio_dphi[%d]",i));
        //MBsubratio_dphi[i]->Sumw2();
        MBsubratio_dphi[i]->Divide(gen_dphi[i]);

        TH2F* hemptydr = new TH2F("hemptydr",";;#frac{1}{N_{evt}} #frac{dN_{evt}}{d#DeltaR}",1,0.,0.5,1,pow(10.,-5),pow(10.,(i==0?1:2)));
        TH2F* hemptydphi = new TH2F("hemptydphi",";;#frac{1}{N_{evt}} #frac{dN_{evt}}{d#Delta#phi}",1,0.,TMath::Pi(),1,pow(10,-5),pow(10,2));
        TH2F* hemptydr_ratio = new TH2F("hemptydr_ratio",";#DeltaR;Ratio",1,0.,0.5,1,0.5,1.5);
        TH2F* hemptydphi_ratio = new TH2F("hemptydphi_ratio",";#Delta#phi;Ratio",1,0,TMath::Pi(),1,0.,2);
        TH2F* bhemptydr_ratio = new TH2F("hemptydr_ratio",";#DeltaR;Ratio",1,0.,0.5,1,pow(10,-5),pow(10,1));
        TH2F* bhemptydphi_ratio = new TH2F("hemptydphi_ratio",";#Delta#phi;Ratio",1,0,TMath::Pi(),1,pow(10,-5),pow(10,1));

        if(plotdr)
        {
            std::cout << "dr" << std::endl;
            cdr->cd();
            TPad* histpad = new TPad("histpad","histpad",0.0,0.3,1.0,1.0);
            TPad* ratiopad = new TPad("ratiopad","ratiopad",0.0,0.0,1.0,0.3);
            histpad->Draw();
            ratiopad->Draw();

            histpad->cd();
            histpad->SetLogy();
            histpad->SetRightMargin(0.05);
            histpad->SetLeftMargin(0.13);
            histpad->SetBottomMargin(0);

            xjjroot::sethempty(hemptydr,0,-0.15);
            hemptydr->Draw();
            xjjroot::setthgrstyle(MBsub_dr[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsub_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(Djet_dr[i],kRed,21,1.2,kRed,1,1,-1,-1,-1);
            Djet_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixjet_dr[i],kBlue,22,1.2,kBlue,1,1,-1,-1,-1);
            mixjet_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixD_dr[i],kTeal,22,1.2,kTeal,1,1,-1,-1,-1);
            mixD_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixboth_dr[i],kOrange,22,1.2,kOrange,1,1,-1,-1,-1);
            mixboth_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(gen_dr[i],kGreen,20,1.2,kGreen,1,1,-1,-1,-1);
            gen_dr[i]->Draw("pe same");

            ldr[i] = new TLegend(0.3,0.6,0.95,0.9);
            ldr[i]->AddEntry(Djet_dr[i],"HYDJET+PYTHIA D, HYDJET+PYTHIA Jet","lp");
            ldr[i]->AddEntry(mixjet_dr[i],"HYDJET+PYTHIA D, HYDJET Jet","lp");
            ldr[i]->AddEntry(mixD_dr[i],"HYDJET D, HYDJET+PYTHIA Jet","lp");
            ldr[i]->AddEntry(mixboth_dr[i],"HYDJET D, HYDJET Jet","lp");
            ldr[i]->AddEntry(MBsub_dr[i],"Signal D, Signal Jet (MC-subtracted)","lp");
            ldr[i]->AddEntry(gen_dr[i],"Signal D, Signal Jet (MC-gen)","lp");
            
            xjjroot::setleg(ldr[i]);
            ldr[i]->Draw();

            xjjroot::drawtex(0.15,0.85,vectex[0].Data());
            xjjroot::drawtex(0.15,0.79,ptbinlabel[i].Data());
            xjjroot::drawtex(0.15,0.73,vectex[1].Data());
            xjjroot::drawtex(0.15,0.67,vectex[2].Data());
            TLatex* texCms = new TLatex(0.13,0.93, "#scale[1.25]{CMS} Performance");
            texCms->SetNDC();
            texCms->SetTextAlign(12);
            texCms->SetTextSize(0.04);
            texCms->SetTextFont(42);
            texCms->Draw();
            TLatex* texCol = new TLatex(0.95,0.93,"PbPb #sqrt{s_{NN}} = 5.02 TeV");
            texCol->SetNDC();
            texCol->SetTextAlign(32);
            texCol->SetTextSize(0.04);
            texCol->SetTextFont(42);
            texCol->Draw();
            histpad->Update();

            std::cout << "ratio" << std::endl;
            ratiopad->cd();
            ratiopad->SetRightMargin(0.05);
            ratiopad->SetLeftMargin(0.13);
            ratiopad->SetTopMargin(0);
            ratiopad->SetBottomMargin(.3);

            hemptydr_ratio->SetNdivisions(505,"Y");
            xjjroot::sethempty(hemptydr_ratio,-0.35,-0.9);
            hemptydr_ratio->GetYaxis()->SetLabelSize(1/0.4*hemptydr_ratio->GetYaxis()->GetLabelSize());
            hemptydr_ratio->GetYaxis()->SetTitleSize(1/0.4*hemptydr_ratio->GetYaxis()->GetTitleSize());
            hemptydr_ratio->GetXaxis()->SetLabelSize(1/0.4*hemptydr_ratio->GetXaxis()->GetLabelSize());
            hemptydr_ratio->GetXaxis()->SetTitleSize(1/0.4*hemptydr_ratio->GetXaxis()->GetTitleSize());
            hemptydr_ratio->Draw();

            xjjroot::setthgrstyle(MBsubratio_dr[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsubratio_dr[i]->Draw("pe same");
            xjjroot::drawline(0.,1.,0.5,1.,kBlack,1,2);
            ratiopad->Update();
            cdr->SaveAs(Form("plots/MBsub_dr_pt_%d.pdf",i));

            bdr->cd();
            bdr->Clear();

            TPad* bhistpad = new TPad("histpad","histpad",0.0,0.3,1.0,1.0);
            TPad* bratiopad = new TPad("ratiopad","ratiopad",0.0,0.0,1.0,0.3);
            bhistpad->Draw();
            bratiopad->Draw();

            bhistpad->cd();
            bhistpad->SetLogy();
            bhistpad->SetRightMargin(0.05);
            bhistpad->SetLeftMargin(0.13);
            bhistpad->SetBottomMargin(0);

            xjjroot::sethempty(hemptydr,0,-0.15);
            hemptydr->Draw();
            xjjroot::setthgrstyle(MBsub_dr[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsub_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixjet_clean_dr[i],kBlue,20,1.2,kBlue,1,1,-1,-1,-1);
            mixjet_clean_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixD_clean_dr[i],kTeal,20,1.2,kTeal,1,1,-1,-1,-1);
            mixD_clean_dr[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixboth_dr[i],kOrange,20,1.2,kOrange,1,1,-1,-1,-1);
            mixboth_dr[i]->Draw("pe same");

            lbdr[i] = new TLegend(0.45,0.6,0.95,0.9);
            lbdr[i]->AddEntry(MBsub_dr[i],"Signal D, Signal Jet","lp");
            lbdr[i]->AddEntry(mixjet_clean_dr[i],"Signal D, UE Jet","lp");
            lbdr[i]->AddEntry(mixD_clean_dr[i],"UE D, Signal Jet","lp");
            lbdr[i]->AddEntry(mixboth_dr[i],"UE D, UE Jet","lp");
            xjjroot::setleg(lbdr[i]);
            lbdr[i]->Draw();

            xjjroot::drawtex(0.25,0.85,vectex[0].Data());
            xjjroot::drawtex(0.25,0.79,ptbinlabel[i].Data());
            xjjroot::drawtex(0.25,0.73,vectex[1].Data());
            xjjroot::drawtex(0.25,0.67,vectex[2].Data());
            texCms->Draw();
            texCol->Draw();
            bhistpad->Update();

            bratiopad->cd();
            bratiopad->SetLogy();
            bratiopad->SetRightMargin(0.05);
            bratiopad->SetLeftMargin(0.13);
            bratiopad->SetTopMargin(0);
            bratiopad->SetBottomMargin(.3);

            bhemptydr_ratio->SetNdivisions(505,"Y");
            xjjroot::sethempty(bhemptydr_ratio,-0.35,-0.9);
            bhemptydr_ratio->GetYaxis()->SetLabelSize(1/0.4*bhemptydr_ratio->GetYaxis()->GetLabelSize());
            bhemptydr_ratio->GetYaxis()->SetTitleSize(1/0.4*bhemptydr_ratio->GetYaxis()->GetTitleSize());
            bhemptydr_ratio->GetXaxis()->SetLabelSize(1/0.4*bhemptydr_ratio->GetXaxis()->GetLabelSize());
            bhemptydr_ratio->GetXaxis()->SetTitleSize(1/0.4*bhemptydr_ratio->GetXaxis()->GetTitleSize());
            bhemptydr_ratio->Draw();

            xjjroot::setthgrstyle(mixjet_clean_dr_ratio[i],kBlue,20,1.2,kBlue,1,1,-1,-1,-1);
            mixjet_clean_dr_ratio[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixD_clean_dr_ratio[i],kTeal,20,1.2,kTeal,1,1,-1,-1,-1);
            mixD_clean_dr_ratio[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixboth_dr_ratio[i],kOrange,20,1.2,kOrange,1,1,-1,-1,-1);
            mixboth_dr_ratio[i]->Draw("pe same");
            xjjroot::drawline(0.,1.,0.5,1.,kBlack,1,2);
            bratiopad->Update();
            bdr->SaveAs(Form("plots/bkgd_ratio_dr_pt_%d.pdf",i));

            //delete histpad;
            //delete ratiopad;
        }

        if(plotdphi)
        {
            std::cout << "dphi" << std::endl;
            cdphi->cd();
            TPad* histpad = new TPad("histpad","histpad",0.0,0.3,1.0,1.0);
            TPad* ratiopad = new TPad("ratiopad","ratiopad",0.0,0.0,1.0,0.3);
            histpad->Draw();
            ratiopad->Draw();
            histpad->cd();
            histpad->SetLogy();
            histpad->SetRightMargin(0.05);
            histpad->SetLeftMargin(0.13);
            histpad->SetBottomMargin(0);
            xjjroot::sethempty(hemptydphi,0,-0.15);
            hemptydphi->Draw();
            xjjroot::setthgrstyle(MBsub_dphi[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsub_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(Djet_dphi[i],kRed,21,1.2,kRed,1,1,-1,-1,-1);
            Djet_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixjet_dphi[i],kBlue,22,1.2,kBlue,1,1,-1,-1,-1);
            mixjet_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixD_dphi[i],kTeal,22,1.2,kTeal,1,1,-1,-1,-1);
            mixD_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixboth_dphi[i],kOrange,22,1.2,kOrange,1,1,-1,-1,-1);
            mixboth_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(gen_dphi[i],kGreen,20,1.2,kGreen,1,1,-1,-1,-1);
            gen_dphi[i]->Draw("pe same");
            ldphi[i] = new TLegend(0.3,0.6,0.95,0.9);
            ldphi[i]->AddEntry(Djet_dphi[i],"HYDJET+PYTHIA D, HYDJET+PYTHIA Jet","lp");
            ldphi[i]->AddEntry(mixjet_dphi[i],"HYDJET+PYTHIA D, HYDJET Jet","lp");
            ldphi[i]->AddEntry(mixD_dphi[i],"HYDJET D, HYDJET+PYTHIA Jet","lp");
            ldphi[i]->AddEntry(mixboth_dphi[i],"HYDJET D, HYDJET Jet","lp");
            ldphi[i]->AddEntry(MBsub_dphi[i],"Signal D, Signal Jet (MC-subtracted)","lp");
            ldphi[i]->AddEntry(gen_dphi[i],"Signal D, Signal Jet (MC-gen)","lp");
            xjjroot::setleg(ldphi[i]);
            ldphi[i]->Draw();
            xjjroot::drawtex(0.15,0.85,vectex[0].Data());
            xjjroot::drawtex(0.15,0.79,ptbinlabel[i].Data());
            xjjroot::drawtex(0.15,0.73,vectex[1].Data());
            xjjroot::drawtex(0.15,0.67,vectex[2].Data());
            TLatex* texCms = new TLatex(0.13,0.93, "#scale[1.25]{CMS} Performance");
            texCms->SetNDC();
            texCms->SetTextAlign(12);
            texCms->SetTextSize(0.04);
            texCms->SetTextFont(42);
            texCms->Draw();
            TLatex* texCol = new TLatex(0.95,0.93,"PbPb #sqrt{s_{NN}} = 5.02 TeV");
            texCol->SetNDC();
            texCol->SetTextAlign(32);
            texCol->SetTextSize(0.04);
            texCol->SetTextFont(42);
            texCol->Draw();
            histpad->Update();
            ratiopad->cd();
            ratiopad->SetRightMargin(0.05);
            ratiopad->SetLeftMargin(0.13);
            ratiopad->SetTopMargin(0);
            ratiopad->SetBottomMargin(.3);
            hemptydphi_ratio->SetNdivisions(505,"Y");
            xjjroot::sethempty(hemptydphi_ratio,-0.35,-0.9);
            hemptydphi_ratio->GetYaxis()->SetLabelSize(1/0.4*hemptydphi_ratio->GetYaxis()->GetLabelSize());
            hemptydphi_ratio->GetYaxis()->SetTitleSize(1/0.4*hemptydphi_ratio->GetYaxis()->GetTitleSize());
            hemptydphi_ratio->GetXaxis()->SetLabelSize(1/0.4*hemptydphi_ratio->GetXaxis()->GetLabelSize());
            hemptydphi_ratio->GetXaxis()->SetTitleSize(1/0.4*hemptydphi_ratio->GetXaxis()->GetTitleSize());
            hemptydphi_ratio->Draw();
            xjjroot::setthgrstyle(MBsubratio_dphi[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsubratio_dphi[i]->Draw("pe same");
            xjjroot::drawline(0.,1.,TMath::Pi(),1.,kBlack,1,2);
            ratiopad->Update();
            cdphi->SaveAs(Form("plots/MBsub_dphi_pt_%d.pdf",i));

            bdphi->cd();
            bdphi->Clear();

            TPad* bhistpad = new TPad("histpad","histpad",0.0,0.3,1.0,1.0);
            TPad* bratiopad = new TPad("ratiopad","ratiopad",0.0,0.0,1.0,0.3);
            bhistpad->Draw();
            bratiopad->Draw();

            bhistpad->cd();
            bhistpad->SetLogy();
            bhistpad->SetRightMargin(0.05);
            bhistpad->SetLeftMargin(0.13);
            bhistpad->SetBottomMargin(0);

            xjjroot::sethempty(hemptydphi,0,-0.15);
            hemptydphi->Draw();
            xjjroot::setthgrstyle(MBsub_dphi[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            MBsub_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixjet_clean_dphi[i],kBlue,20,1.2,kBlue,1,1,-1,-1,-1);
            mixjet_clean_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixD_clean_dphi[i],kTeal,20,1.2,kTeal,1,1,-1,-1,-1);
            mixD_clean_dphi[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixboth_dphi[i],kOrange,20,1.2,kOrange,1,1,-1,-1,-1);
            mixboth_dphi[i]->Draw("pe same");

            lbdphi[i] = new TLegend(0.45,0.6,0.95,0.9);
            lbdphi[i]->AddEntry(MBsub_dphi[i],"Signal D, Signal Jet","lp");
            lbdphi[i]->AddEntry(mixjet_clean_dphi[i],"Signal D, UE Jet","lp");
            lbdphi[i]->AddEntry(mixD_clean_dphi[i],"UE D, Signal Jet","lp");
            lbdphi[i]->AddEntry(mixboth_dphi[i],"UE D, UE Jet","lp");
            xjjroot::setleg(lbdphi[i]);
            lbdphi[i]->Draw();

            xjjroot::drawtex(0.25,0.85,vectex[0].Data());
            xjjroot::drawtex(0.25,0.79,ptbinlabel[i].Data());
            xjjroot::drawtex(0.25,0.73,vectex[1].Data());
            xjjroot::drawtex(0.25,0.67,vectex[2].Data());
            texCms->Draw();
            texCol->Draw();
            bhistpad->Update();

            bratiopad->cd();
            bratiopad->SetRightMargin(0.05);
            bratiopad->SetLeftMargin(0.13);
            bratiopad->SetTopMargin(0);
            bratiopad->SetBottomMargin(.3);
            bratiopad->SetLogy();

            bhemptydphi_ratio->SetNdivisions(505,"Y");
            xjjroot::sethempty(bhemptydphi_ratio,-0.35,-0.9);
            bhemptydphi_ratio->GetYaxis()->SetLabelSize(1/0.4*bhemptydphi_ratio->GetYaxis()->GetLabelSize());
            bhemptydphi_ratio->GetYaxis()->SetTitleSize(1/0.4*bhemptydphi_ratio->GetYaxis()->GetTitleSize());
            bhemptydphi_ratio->GetXaxis()->SetLabelSize(1/0.4*bhemptydphi_ratio->GetXaxis()->GetLabelSize());
            bhemptydphi_ratio->GetXaxis()->SetTitleSize(1/0.4*bhemptydphi_ratio->GetXaxis()->GetTitleSize());
            bhemptydphi_ratio->Draw();

            xjjroot::setthgrstyle(mixjet_clean_dphi_ratio[i],kBlue,20,1.2,kBlue,1,1,-1,-1,-1);
            mixjet_clean_dphi_ratio[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixD_clean_dphi_ratio[i],kTeal,20,1.2,kTeal,1,1,-1,-1,-1);
            mixD_clean_dphi_ratio[i]->Draw("pe same");
            xjjroot::setthgrstyle(mixboth_dphi_ratio[i],kOrange,20,1.2,kOrange,1,1,-1,-1,-1);
            mixboth_dphi_ratio[i]->Draw("pe same");
            xjjroot::drawline(0.,1.,TMath::Pi(),1.,kBlack,1,2);
            bratiopad->Update();
            bdphi->SaveAs(Form("plots/bkgd_ratio_dphi_pt_%d.pdf",i));
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
        mixjet_dr[i]->Write();
        mixD_dr[i]->Write();
        mixboth_dr[i]->Write();
        MBsub_dr[i]->Write();
        gen_dr[i]->Write();
        Djet_dphi[i]->Write();
        mixjet_dphi[i]->Write();
        mixD_dphi[i]->Write();
        mixboth_dphi[i]->Write();
        MBsub_dphi[i]->Write();
        gen_dphi[i]->Write();

        delete hemptydr;
        delete hemptydphi;
        delete hemptydr_ratio;
        delete hemptydphi_ratio;
        if(plotdr) {delete ldr[i]; delete lbdr[i];}
        if(plotdphi) {delete ldphi[i]; delete lbdphi[i];}
    }
    djf->Close();
    mixjetf->Close();
    mixDf->Close();
    mixbothf->Close();
    genf->Close();
    outfile->Close();
    delete cdr;
    delete cdphi;
    delete bdr;
    delete bdphi;
    //delete d;
    delete outfile;
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc==10)
        MBsubtract_closure(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],atof(argv[7]),atof(argv[8]),atof(argv[9]));
    else
        printf("Usage: ./MBsubtract.C [Djetfile] [MBmixfile] [output]\n");
}
