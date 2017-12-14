#include "djtana.h"
#include "TString.h"
#include "TRegexp.h"
#include "../includes/djet.h"

void djtana_datamc()
{
    xjjroot::setgstyle();
    cout << "start" << endl;
    std::string collsyst[2] = {"pp", "PbPb"};
    std::string gentype[5] = {"data_RecoD_RecoJet","MC_RecoD_RecoJet","MC_RecoD_GenJet","MC_GenD_RecoJet","MC_GenD_GenJet"};
    Color_t gencols[5] = {kBlack,kRed,kBlue,kGreen,kOrange};
    Style_t genstyl[5] = {20,21,22,23,24};
    TH1F* phis[5];
    TFile* f[5];
    for(int i=0;i<2;i++)
    {
        for(int k=0;k<2;k++)
        {
            cout << i << endl;
            TLegend *leg = new TLegend(0.3,0.4,0.5,0.6);
            for(int j=0;j<5;j++)
            {
                cout << j << endl;
                f[j] = new TFile(Form("rootfiles/masstpl_Djet_%s_%s_jetpt_40p0_jeteta_0p0_2p0_noHLT.root",collsyst[i].c_str(),gentype[j].c_str()));
                if(f[j]->IsZombie())
                {
                    cout << "bad file " << collsyst[i] << "_" << gentype[j] << endl;
                    return;
                }
                phis[j] = (TH1F*)f[j]->Get(Form("hDPhi_pt_%d",k));
                phis[j]->Sumw2();
                phis[j]->Scale(1./phis[j]->Integral("w"));
            }
            TCanvas *c = new TCanvas("c","",1000,1000);
            TH2F* hempty = new TH2F("hempty",Form("D #phi for %s, pt_%d;#phi;",collsyst[i].c_str(),k),1,-TMath::Pi(),TMath::Pi(),1,0.,.025);
            xjjroot::sethempty(hempty,0,0.5);
            hempty->Draw();
            xjjroot::drawCMS(collsyst[i]);
            for(int j=0;j<5;j++)
            {
                xjjroot::setthgrstyle(phis[j],gencols[j],genstyl[j],1.2,gencols[j],1,1,-1,-1,-1);
                if(j!=4)phis[j]->DrawClone("pe same");
                else phis[j]->DrawClone("p same");
                leg->AddEntry(phis[j],gentype[j].c_str());
            }
            xjjroot::setleg(leg);
            leg->Draw();
            c->SaveAs(Form("plots/%s_mcdata_pt_%d.png",collsyst[i].c_str(),k));
            delete c;
        }
    }        
}

