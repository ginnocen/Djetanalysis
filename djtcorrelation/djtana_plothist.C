#include "djtana.h"
#include "TString.h"
#include "TRegexp.h"
#include "../includes/djet.h"

void djtana_plothist(TString inputhistname, TString outputname,
                     TString collisionsyst, Int_t isMC,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
                     Int_t plotref = 1)
{
  int arguerr(TString collisionsyst, Int_t isMC, Int_t plotref);
  if(arguerr(collisionsyst, isMC, plotref)) return;
  xjjroot::setgstyle();
  

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(infhist->IsZombie()) return;

  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;

  // preparation
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  std::vector<float> vdrBins, vzBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  for(int j=0;j<sizeof(zBins)/sizeof(zBins[0]);j++) vzBins.push_back(zBins[j]);
  Float_t jet_ymax = 20000;
  Float_t D_ymax = 20000;
  std::vector<TH1F*>               hJetHists     =  {(TH1F*)hJetPhi,         (TH1F*)hJetEta};
  std::vector<Float_t>             jetmins       =  {0.,                     -2.};
  std::vector<Float_t>             jetmaxes      =  {(Float_t)TMath::Pi(),   2.};
  std::vector<TString>             jettitle      =  {"#phi",                 "#eta"};
  std::vector<TH1F**>              hDHists       =  {(TH1F**)hDPhi,          (TH1F**)hDEta,                   (TH1F**)hDdelPhi,         (TH1F**)hDdelEta};   
  std::vector<Float_t>             Dmins         =  {-(Float_t)TMath::Pi(),  -2.,                             0.,                       -4.};
  std::vector<Float_t>             Dmaxes        =  {(Float_t)TMath::Pi(),   2.,                              (Float_t)TMath::Pi(),     4.};   
  std::vector<TString>             Dtitle        =  {"#phi",                 "#eta",                          "#Delta#phi",             "#Delta#eta"};                         
  std::vector<TString>             xtitle        =  {"#DeltaR",              "z = p_{T}^{D} / p_{T}^{jet}"};
  std::vector<TString>             ytitle        =  {"#rho(#DeltaR)",        "#rho(z)"};
  std::vector<TString>             tname         =  {"dr",                   "z"};
  std::vector<std::vector<float>>  vxBins        =  {vdrBins,                vzBins};
  std::vector<TH2F**>              h2DHists      =  {hCorr,                  hDphivsDtrk1hit,                 hDphivsDtrk2hit,          hDphivsDtrk1algo,         hDphivsDtrk2algo}; 

  // plot

  for(int i=0;i<2;i++)
    {
      TCanvas* c = new TCanvas("c","",600,600);      
      TH2F* hempty = new TH2F("hempty",Form(";%s;",jettitle[i].Data()),1,jetmins[i],jetmaxes[i],1,0.,hJetHists[i]->GetMaximum());
      xjjroot::sethempty(hempty,0,0.5);
      hempty->Draw();
      xjjroot::setthgrstyle(hJetHists[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
      hJetHists[i]->Draw("pe same");
      xjjroot::drawCMS(collisionsyst);
      TRegexp re("_pt_.");
      TString name = hJetHists[i]->GetName();
      name(re) = "";
      TString fullname = hJetHists[i]->GetName();
      fullname += "_";
      // Saves twice for easy comparison; this one compares the same histogram in different datasets
      c->SaveAs(Form("plots/%s/%s.png",name.Data(),fullname.Append(outputname).Data()));
      // And this one compares different histograms in the same dataset
      c->SaveAs(Form("plots/%s/%s.png",outputname.Data(),fullname.Data()));
      delete c;
      delete hempty;
    }
  for(int i=0;i<4;i++)
    {
      for(int j=0;j<nPtBins;j++)
        {
          TCanvas* c = new TCanvas("c","",600,600);      
          TH2F* hempty = new TH2F("hempty",Form("pt_{%d};%s;",j,Dtitle[i].Data()),1,Dmins[i],Dmaxes[i],1,0.,(hDHists.at(i))[j]->GetMaximum());
          xjjroot::sethempty(hempty,0,0.5);
          hempty->Draw();
          xjjroot::setthgrstyle((hDHists.at(i))[j],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
          (hDHists.at(i))[j]->Draw("pe same");
          xjjroot::drawCMS(collisionsyst);
          TRegexp re("_pt_.");
          TString name = (hDHists.at(i))[j]->GetName();
          name(re) = "";
          TString fullname = (hDHists.at(i))[j]->GetName();
          fullname += "_";
          c->SaveAs(Form("plots/%s/%s.png",name.Data(),fullname.Append(outputname).Data()));
          c->SaveAs(Form("plots/%s/%s.png",outputname.Data(),fullname.Data()));
          delete c;
          delete hempty;
        }
    }
    for(int i=0;i<5;i++)
    { 
        for(int j=0;j<nPtBins;j++)
        {
            TCanvas* c = new TCanvas("c","",600,600);
            c->SetRightMargin(0.13);
            (h2DHists.at(i))[j]->GetYaxis()->SetRangeUser(0.,20.);
            (h2DHists.at(i))[j]->Draw("colz same");
            TRegexp re("_pt_.");
            TString name = (h2DHists.at(i))[j]->GetName();
            name(re) = "";
            TString fullname = (h2DHists.at(i))[j]->GetName();
            fullname += "_";
            c->SaveAs(Form("plots/%s/%s.png",name.Data(),fullname.Append(outputname).Data()));
          c->SaveAs(Form("plots/%s/%s.png",outputname.Data(),fullname.Data()));
            delete c;
        } 
    }
}

int main(int argc, char* argv[])
{
  if(argc==8)
    {
      djtana_plothist(argv[1], argv[2], argv[3], atoi(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_plothist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t isMC, Int_t plotref)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    } 
  if(isMC!=0 && isMC!=1)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"isMC\""<<std::endl;
      return 1;
    }
  if(plotref!=0 && plotref!=1)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"plotref\""<<std::endl;
      return 1;
    }
  return 0;
}

