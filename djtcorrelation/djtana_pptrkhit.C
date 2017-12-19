#include "djtana.h"
#include "TString.h"
#include "TRegexp.h"
#include "../includes/djet.h"

void djtana_pptrkhit()
{
    xjjroot::setgstyle();
    std::string gentype[5] = {"data_RecoD_RecoJet","MC_RecoD_RecoJet","MC_GenD_RecoJet","MC_RecoD_GenJet","MC_GenD_GenJet"};
    Color_t gencols[5] = {kBlack,kRed,kBlue,kGreen,kOrange};
    Style_t genstyl[5] = {21,22,23,21,22};
    Int_t ispp = 1;

    std::string filenames[2] = {"scratch/jwang/Djets/MC/DjetFiles_20171127_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root",
    "scratch/jwang/Djets/data/DjetFiles_20171120_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"};
    
    Int_t isMC[2] = {1,0};

    Int_t hits[5] = {1,2,3,4,5};

    for(int i=0;i<2;i++)
    {
        TH2F* hempty = new TH2F("hempty","D #phi for pp;#phi;",1,-TMath::Pi(),TMath::Pi(),1,0.,.03);
        djet* djt = new djet(Form("/mnt/T2_US_MIT/submit-hi2/%s",filenames[i].c_str()), ispp, isMC[i]);
        djt->setjetcut(40., 0., 2.);
        djt->setGcut(cutval_Dy);
        initcutval("pp");
        for(int j=0;j<4;j++)
        {
            std::cout << j << std::endl;
            TLegend *leg = new TLegend(0.3,0.4,0.5,0.6);
            if(isMC[i]==0 && j>0) continue;
            TCanvas* c = new TCanvas("c","",1000,1000);
            xjjroot::sethempty(hempty,0,0.5);
            hempty->Draw();
            xjjroot::drawCMS("pp");
            int64_t nentries = djt->fChain->GetEntriesFast();
            //int64_t nentries = 500000;
            TH1F* phis[5];
            for(int k=0;k<5;k++) phis[k] = new TH1F(Form("%d",k),"",50,-TMath::Pi(),TMath::Pi());
            for(int64_t m=0;m<nentries;m++)
            {
                if(m%10000==0) std::cout << m << std::endl;
                //
                djt->fChain->GetEntry(m);
                //djt->fChain->Draw(Form("Dphi[%d]>>phis",j),Form("Dtrk1PixelHit[%d]>%d",j,hits[k]),"norm");
                for(int jj=0;jj<*(djt->anjet[j]);jj++)
                {
                    int djtjetsel = djt->isjetselected(jj, djt->ajetopt[j]);
                    if(djtjetsel < 0)
                    {
                        std::cout << "bad djtsel" << std::endl;
                        return;
                    }
                    if(!djtjetsel) continue;
                    for(int jd=0;jd<*(djt->anD[j]);jd++)
                    {
                        Int_t ibinpt = xjjc::findibin(&ptBins, (**djt->aDpt[j])[jd]);
                        if(ibinpt<0) 
                        {
                            continue;
                        }
                        Int_t result_initcutval = initcutval_bindep_flat("pp",ibinpt);
                        if(result_initcutval)
                        {
                            //std::cout << "bad initcutval " << result_initcutval << "ibinpt: " << ibinpt << std::endl;
                            continue;
                        }
                        djt->settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
                        djt->setDcut(cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, cutval_Dy);                  
                        Int_t djtDsel = djt->isDselected(jd, djt->aDopt[j]);
                        if(djtDsel < 0) {std::cout<<"error: invalid option for isDselected()"<<std::endl; return;}
                        for(int k=0;k<5;k++) if(djtDsel && (*djt->Dtrk1PixelHit)[jd] >= k) phis[k]->Fill((**djt->aDphi[j])[jd]);
                    }
                }   
            }            
            for(int k=0;k<5;k++)
            {
                xjjroot::setthgrstyle(phis[k],gencols[k],genstyl[k],1.2,gencols[k],1,1,-1,-1,-1);
                phis[k]->Sumw2();
                phis[k]->Scale(1./phis[k]->GetEntries());
                phis[k]->Draw("pe same");            
                leg->AddEntry(phis[k],Form(">%d hits",hits[k]));
            }
            cout << "done" << endl;
            xjjroot::setleg(leg);
            leg->Draw();
            std::cout << "leg" << std::endl;
            std::cout << gentype[j+1] << std::endl;
            c->SaveAs(Form("plots/pptrkhit_%s.pdf",gentype[j+(isMC[i]==1)*1].c_str()));
            std::cout << "saved" << std::endl;
            delete leg;
            delete c;
            for(int k=0;k<5;k++) delete phis[k];
        }
        delete hempty;
        delete djt;
    }        
}
