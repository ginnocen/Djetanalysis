#include "eff.h"

int plotindex[] = {0, 1, 2};
const int nplotindex = sizeof(plotindex)/sizeof(plotindex[0]);
void eff_plothist(std::vector<TString> inputname, std::vector<TString> name,
                  TString outputname, TString collisionsyst, 
                  Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                  Int_t plotref=0)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;

  xjjroot::setgstyle(1);
  Bool_t ispp = collisionsyst=="pp";

  int nhist = inputname.size();
  std::vector<TFile*> infhist(nhist);
  for(int i=0;i<nhist;i++)
    { infhist[i] = new TFile(Form("%s.root",inputname[i].Data())); }
  if(gethists(infhist, "plothist")) return;

  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
    };
  TString texjetpt = jetptmax<999?
    Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):
    Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);
  TString texpythia = ispp?"PYTHIA":"PYTHIA + HYDJET";
  vectex.push_back(texpythia);

  for(int i=0;i<nPtBins;i++)
    {
      TString texdpt = ptBins[i+1]==999?
        Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):
        Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      vectex.push_back(texdpt);
      TCanvas* c = new TCanvas("c", "", 600, 600);
      TCanvas* c3 = new TCanvas("c3", "", 1800, 600);
      c3->Divide(3, 1);
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#alpha x #epsilon_{reco} x #epsilon_{sel}"), 5, drBins[0], drBins[nDrBins], 10, 0, 1.);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.5);
      TH2F* hemptyAcc = new TH2F("hemptyAcc", Form(";%s;%s","r","#alpha"), 5, drBins[0], drBins[nDrBins], 10, 0, 1.);
      hemptyAcc->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hemptyAcc, 0, 0.5);
      TH2F* hemptyEff = new TH2F("hemptyEff", Form(";%s;%s","r","#epsilon_{reco} x #epsilon_{sel}"), 5, drBins[0], drBins[nDrBins], 10, 0, 1.);
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
      TLegend* leg = new TLegend(0.53, 0.88-nplotindex*0.05, 0.85, 0.88);
      xjjroot::setleg(leg);
      for(int l=0;l<nhist;l++)
        {
          xjjroot::setthgrstyle(vhREfficiency[i][l], colorlist[l], 21, 1.2, colorlist[l], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(vhREff[i][l], colorlist[l], 21, 1.2, colorlist[l], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(vhRAcceptance[i][l], colorlist[l], 21, 1.2, colorlist[l], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(vhREfficiencyRef[i][l], colorlist[l], 24, 1.2, colorlist[l], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(vhREffRef[i][l], colorlist[l], 24, 1.2, colorlist[l], 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(vhRAcceptanceRef[i][l], colorlist[l], 24, 1.2, colorlist[l], 1, 1, -1, -1, -1);
        }
      for(int l=0;l<nplotindex;l++)
        leg->AddEntry(vhREfficiency[i][plotindex[l]], name[plotindex[l]].Data(), "p");

      c->cd();
      for(int l=0;l<nplotindex;l++)
        {
          vhREfficiency[i][plotindex[l]]->Draw("ple same");
          if(plotref) vhREfficiencyRef[i][plotindex[l]]->Draw("ple same");
        }
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c->SaveAs(Form("ploteffall/ceff_%s_%s_%d.pdf","r",outputname.Data(),i));

      for(int l=0;l<nplotindex;l++)
        {
          c3->cd(1);
          vhREfficiency[i][plotindex[l]]->Draw("ple same");
          if(plotref) vhREfficiencyRef[i][plotindex[l]]->Draw("ple same");
          c3->cd(2);
          vhRAcceptance[i][plotindex[l]]->Draw("ple same");
          if(plotref) vhRAcceptanceRef[i][plotindex[l]]->Draw("ple same"); 
          c3->cd(3);
          vhREff[i][plotindex[l]]->Draw("ple same");
          if(plotref) vhREff[i][plotindex[l]]->Draw("ple same");
        }
      c3->cd(1);
      xjjroot::drawCMS(collisionsyst);
      texxpos = 0.22; texypos = 0.85; texdypos = 0.06; texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c3->SaveAs(Form("ploteffall/cacceff_%s_%s_%d.pdf","dr",outputname.Data(),i));

      vectex.pop_back();

      delete leg;
      delete hemptyEff;
      delete hemptyAcc;
      delete hempty;
      delete c3;
      delete c;
    }
}

int main(int argc, char* argv[])
{
  if((argc-7)%2==0)
    {
      std::vector<TString> vinput;
      std::vector<TString> vname;
      for(int c=1;c<argc-6;c+=2)
        {
          vinput.push_back(argv[c]);
          vname.push_back(argv[c+1]);
        }
      eff_plothist(vinput, vname, argv[argc-6], argv[argc-5], atof(argv[argc-4]), atof(argv[argc-3]), atof(argv[argc-2]), atof(argv[argc-1]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - eff_plothist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  return 0;
}

