#include "eff.h"

void eff_usehist(TString inputtplname, TString outputname, 
                 TString collisionsyst, Int_t irecogen,
                 Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax)
{
  int arguerr(TString collisionsyst, Int_t irecogen);
  if(arguerr(collisionsyst, irecogen)) return;

  xjjroot::setgstyle();

  Bool_t isrecoD = irecogen%2==0;
  Bool_t ispp = collisionsyst=="pp";
  djtcorr::setParameters(ispp);

  if(isrecoD)
    {
      TFile* inftpl = new TFile(Form("%s.root",inputtplname.Data()));
      if(!inftpl->IsOpen()) return;
      std::vector<TFile*> inf;
      inf.push_back(inftpl);
      if(gethists(inf, "tpl")) return;
    }

  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
    };
  TString texjetpt = jetptmax<999?
    Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):
    Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  std::vector<float> vdrBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  
  std::vector<TString>             tleg                   =  {"r"};
  std::vector<TString>             tname                  =  {"dr"};
  std::vector<std::vector<float>>  vxBins                 =  {vdrBins};
  std::vector<TH1F**>              hXEfficiency           =  {(TH1F**)ahREfficiency};
  std::vector<TH1F**>              hXEff                  =  {(TH1F**)ahREff};
  std::vector<TH1F**>              hXAcceptance           =  {(TH1F**)ahRAcceptance};
  std::vector<TH1F**>              hXEfficiencyRef        =  {(TH1F**)ahREfficiencyRef};

  int k = 0;
  if(isrecoD)
    {
      TString texpythia = ispp?"PYTHIA":"PYTHIA + HYDJET";
      vectex.push_back(texpythia);
      TCanvas* c = new TCanvas("c", "", 600, 600);
      TCanvas* c3 = new TCanvas("c3", "", 1800, 600);
      c3->Divide(3, 1);
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s",tleg[k].Data(),"#alpha x #epsilon_{reco} x #epsilon_{sel}"), 5, vxBins[k].front(), vxBins[k].back(), 10, 0, 1.);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.5);
      TH2F* hemptyAcc = new TH2F("hemptyAcc", Form(";%s;%s",tleg[k].Data(),"#alpha"), 5, vxBins[k].front(), vxBins[k].back(), 10, 0, 1.);
      hemptyAcc->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hemptyAcc, 0, 0.5);
      TH2F* hemptyEff = new TH2F("hemptyEff", Form(";%s;%s",tleg[k].Data(),"#epsilon_{reco} x #epsilon_{sel}"), 5, vxBins[k].front(), vxBins[k].back(), 10, 0, 1.);
      hemptyEff->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hemptyEff, 0, 0.5);
      c->cd();
      hempty->Draw();
      c3->cd(1);
      hempty->Draw();
      c3->cd(2);
      hemptyAcc->Draw();
      c3->cd(3);
      hemptyEff->Draw();
      // TLegend* leg = new TLegend(0.53, 0.88-nPtBins*nRefBins*0.06, 0.85, 0.88);
      TLegend* leg = new TLegend(0.53, 0.88-nPtBins*0.06, 0.85, 0.88);
      xjjroot::setleg(leg);
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              xjjroot::setthgrstyle((hXEfficiency.at(k))[l*nPtBins+i], amcolor[i], amstyle[l][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              xjjroot::setthgrstyle((hXEff.at(k))[l*nPtBins+i], amcolor[i], amstyle[l][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              xjjroot::setthgrstyle((hXAcceptance.at(k))[l*nPtBins+i], amcolor[i], amstyle[l][i], 1.2, amcolor[i], 1, 1, -1, -1, -1);
              TString tleg = l==1?"#eta reflection":(ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str()));
              if(l) continue;
              leg->AddEntry((hXEfficiency.at(k))[l*nPtBins+i], tleg.Data(), "p");
            }
        }
      c->cd();
      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              if(l) continue;
              (hXEfficiency.at(k))[l*nPtBins+i]->Draw("pe same");
            }
        }
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c->SaveAs(Form("ploteff/ceff_%s_%s.pdf",tname[k].Data(),outputname.Data()));

      for(int i=0;i<nPtBins;i++)
        {
          for(int l=0;l<nRefBins;l++)
            {
              if(l) continue;
              c3->cd(1);
              (hXEfficiency.at(k))[l*nPtBins+i]->Draw("pe same");
              c3->cd(2);
              (hXAcceptance.at(k))[l*nPtBins+i]->Draw("pe same");
              c3->cd(3);
              (hXEff.at(k))[l*nPtBins+i]->Draw("pe same");
            }
        }
      c3->cd(1);
      xjjroot::drawCMS(collisionsyst);
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c3->SaveAs(Form("ploteff/cacceff_%s_%s.pdf",tname[k].Data(),outputname.Data()));

      delete leg;
      delete hemptyEff;
      delete hemptyAcc;
      delete hempty;
      delete c3;
      delete c;
      vectex.pop_back();
    }
}

int main(int argc, char* argv[])
{
  if(argc==9)
    {
      eff_usehist(argv[1], argv[2], argv[3], atoi(argv[4]),
                  atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - eff_usehist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t irecogen)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  if(irecogen<0 && irecogen>3)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"irecogen\""<<std::endl;
      return 1;
    }
  return 0;
}

