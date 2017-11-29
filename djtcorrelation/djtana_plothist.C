#include "djtana.h"

void djtana_plothist(TString inputhistname, TString outputname,
                     TString collisionsyst, Int_t isMC,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
                     Int_t plotref = 1)
{
  int arguerr(TString collisionsyst, Int_t isMC, Int_t plotref);
  if(arguerr(collisionsyst, isMC, plotref)) return;

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
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
  std::vector<TH1F**>              hSignalXnorm  =  {(TH1F**)ahSignalRnorm,  (TH1F**)ahSignalZnorm};
  std::vector<TH1F**>              hSignalXsub   =  {(TH1F**)ahSignalRsub,   (TH1F**)ahSignalZsub};
  std::vector<TH1F*>               hJetHists     =  {(TH1F*)hJetPhi,         (TH1F*)hJetEta};
  std::vector<Float_t>             jetmins       =  {0.,                     -2.};
  std::vector<Float_t>             jetmaxes      =  {2*TMath::Pi(),          2.};
  std::vector<Float_t>             jetymax       =  {350000.,                450000.};
  std::vector<TString>             jettitle      =  {"#phi",                 "#eta"};
  std::vector<TH1F**>              hDHists       =  {(TH1F**)hDPhi,          (TH1F**)hDEta,                   (TH1F**)hDdelPhi,   (TH1F**)hDdelEta};   
  std::vector<Float_t>             Dmins         =  {0.,                     -2.,                             -2*TMath::Pi(),     -4.};
  std::vector<Float_t>             Dmaxes        =  {2*TMath::Pi(),          2.,                              2*TMath::Pi(),      4.};   
  std::vector<Float_t>             Dymax         =  {8000.,                  18000.,                          180000.,            90000.};
  std::vector<TString>             Dtitle        =  {"#phi",                 "#eta",                          "#Delta#phi",       "#Delta#eta"};                         
  std::vector<TString>             xtitle        =  {"#DeltaR",              "z = p_{T}^{D} / p_{T}^{jet}"};
  std::vector<TString>             ytitle        =  {"#rho(#DeltaR)",        "#rho(z)"};
  std::vector<TString>             tname         =  {"dr",                   "z"};
  std::vector<std::vector<float>>  vxBins        =  {vdrBins,                vzBins};
  Float_t yaxismin = isMC?1.e-5:1.e-7, yaxismax = isMC?1.e+3:1.e+1;

  // plot
  for(int i=0;i<2;i++)
    {
      TCanvas* c = new TCanvas("c","",600,600);      
      TH2F* hempty = new TH2F("hempty",Form(";%s;",jettitle[i].Data()),1,jetmins[i],jetmaxes[i],1,0.,jetymax[i]);
      xjjroot::sethempty(hempty,0,0.5);
      hempty->Draw();
      xjjroot::setthgrstyle(hJetHists[i],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
      hJetHists[i]->Draw("pe same");
      xjjroot::drawCMS(collisionsyst);
      c->SaveAs("%s.pdf",hJetHists[i].Data());
      delete c;
      delete hempty;
    }
  for(int i=0;i<4;i++)
    {
      for(int j=0;j<nPtBins;j++)
        {
          TCanvas* c = new TCanvas("c","",600,600);      
          TH2F* hempty = new TH2F("hempty",Form("pt_{%d};%s;",j,Dtitle[i].Data()),1,Dmins[i],Dmaxes[i],1,0.,Dymax[i]);
          xjjroot::sethempty(hempty,0,0.5);
          hempty->Draw();
          xjjroot::setthgrstyle((hDHists.at(i))[j],kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
          (hDHists.at(i))[j]->Draw("pe same");
          xjjroot::drawCMS(collisionsyst);
          c->SaveAs("%s_pt_%d.pdf",(hDHists.at(i))[j].Data(),j);
          delete c;
          delete hempty;
        }
    }
  TCanvas* c = new TCanvas("c","",600,600);
  hCorr->Draw("surf1 fb");
  c->SaveAs("Correlation.pdf");
  delete c;      
  for(int k=0;k<2;k++)
    {
      //
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.5);
      hempty->Draw();
      TLegend* leg = new TLegend(0.53, 0.88-nPtBins*(1+plotref)*0.06, 0.85, 0.88);
      xjjroot::setleg(leg);
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              if(l && !plotref) continue;
              xjjroot::setthgrstyle((hSignalXnorm.at(k))[l*nPtBins+i], amcolor[i], amstyle[l][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              (hSignalXnorm.at(k))[l*nPtBins+i]->Draw("pe same");
              TString tleg = l==1?"#eta reflection":(ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()));
              leg->AddEntry((hSignalXnorm.at(k))[l*nPtBins+i], tleg.Data(), "p");
            }
        }
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      if(k) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "#DeltaR < 0.3");
      leg->Draw();
      c->SaveAs(Form("plotxsecs/cxsec_%s_%s.pdf",tname[k].Data(),outputname.Data()));

      //
      TCanvas* csub = new TCanvas("csub", "", 600, 600);
      csub->SetLogy();
      hempty->Draw();
      TLegend* legsub = new TLegend(0.53, 0.88-nPtBins*0.06, 0.85, 0.88);
      xjjroot::setleg(legsub);
      for(int i=0;i<nPtBins;i++)
        {
          xjjroot::setthgrstyle((hSignalXsub.at(k))[i], amcolor[i], amstyle[0][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
          (hSignalXsub.at(k))[i]->Draw("pe same");
          TString tleg = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
          legsub->AddEntry((hSignalXsub.at(k))[i], tleg.Data(), "p");
        }
      xjjroot::drawCMS(collisionsyst);
      texypos = 0.85;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      if(k) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "#DeltaR < 0.3");
      legsub->Draw();
      csub->SaveAs(Form("plotxsecs/cxsecsub_%s_%s.pdf",tname[k].Data(),outputname.Data()));

      delete legsub;
      delete csub;
      delete leg;
      delete hempty;
      delete c;
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

