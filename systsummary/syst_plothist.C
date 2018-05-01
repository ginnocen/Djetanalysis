#include "systsummary.h"

void syst_plothist(TString outputname, TString collisionsyst,
                   Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax)
{
  xjjroot::setgstyle(1);
  Bool_t ispp = collisionsyst=="pp";

  if(createhist("plotsyst")) return;

  djtsyst::initsyst(jetptmin, jetptmax);
  setsyst(ispp);

  std::vector<TString> vectex = {"|y^{D}| < 2", 
                                 Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str())};
  TString texjetpt = jetptmax<999?Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++)
        {
          hsystSCALE[i]->SetBinContent(j+1, syst_SCALE->at(i).at(j)/100.);
          hsystRESO[i]->SetBinContent(j+1, syst_RESO->at(i).at(j)/100.);
          hsystTRIGGER[i]->SetBinContent(j+1, syst_TRIGGER->at(i).at(j)/100.);
          hsystPDF[i]->SetBinContent(j+1, syst_PDF->at(i).at(j)/100.);
          hsystNONCLOSURE[i]->SetBinContent(j+1, syst_NONCLOSURE->at(i).at(j)/100.);
          hsystCUT[i]->SetBinContent(j+1, syst_CUT->at(i)/100.);
          // std::cout<<djtsyst::getsyst(i, j, collisionsyst)<<std::endl;
          hsystTOTAL[i]->SetBinContent(j+1, djtsyst::getsyst(i, j, collisionsyst));
        }
      xjjroot::setthgrstyle(hsystSCALE[i], colorlist[0], 21, 1, colorlist[0], 1, 3);
      xjjroot::setthgrstyle(hsystRESO[i], colorlist[1], 21, 1, colorlist[1], 1, 3);
      xjjroot::setthgrstyle(hsystTRIGGER[i], colorlist[5], 21, 1, colorlist[5], 1, 3);
      xjjroot::setthgrstyle(hsystPDF[i], colorlist[2], 21, 1, colorlist[2], 1, 3);
      xjjroot::setthgrstyle(hsystNONCLOSURE[i], colorlist[3], 21, 1, colorlist[3], 1, 3);
      xjjroot::setthgrstyle(hsystCUT[i], colorlist[4], 21, 1, colorlist[4], 1, 3);
      xjjroot::setthgrstyle(hsystTOTAL[i], kBlack, 21, 1, kBlack, 2, 3);
    }

  for(int i=0;i<nPtBins;i++)
    {
      TString texpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      vectex.push_back(texpt);
      TCanvas* c = new TCanvas("c", "", 600, 600);
      TH2F* hempty = new TH2F("hempty", ";r;Systematics", 10, drBins[0], drBins[nDrBins], 10, 0, 0.7);
      xjjroot::sethempty(hempty, 0, 0);
      hempty->GetXaxis()->SetNdivisions(505);
      hempty->Draw();
      TLegend* leg = new TLegend(0.62, 0.88-6*0.05, 0.90, 0.88);
      xjjroot::setleg(leg);
      hsystSCALE[i]->Draw("same");
      hsystRESO[i]->Draw("same");
      hsystTRIGGER[i]->Draw("same");
      hsystPDF[i]->Draw("same");
      hsystNONCLOSURE[i]->Draw("same");
      hsystCUT[i]->Draw("same");
      hsystTOTAL[i]->Draw("same");
      leg->AddEntry(hsystSCALE[i], "JES", "l");
      leg->AddEntry(hsystRESO[i], "JER", "l");
      leg->AddEntry(hsystTRIGGER[i], "Trigger eff", "l");
      leg->AddEntry(hsystPDF[i], "Yield extraction", "l");
      leg->AddEntry(hsystCUT[i], "D efficiency", "l");
      leg->AddEntry(hsystNONCLOSURE[i], "Non-closure", "l");
      leg->AddEntry(hsystTOTAL[i], "Total", "l");
      leg->Draw();
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      c->SaveAs(Form("plotsyst/csyst_%s_pt_%d.pdf", outputname.Data(), i));
      delete leg;
      delete hempty;
      delete c;
      vectex.pop_back();
    }
  
  std::cout<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(24)<<"\033[1;36mSignal extraction";
  for(int i=0;i<nPtBins;i++)
    for(int j=0;j<nDrBins;j++) { std::cout<<"& "<<Form("%.1f",syst_PDF->at(i).at(j))<<"$\\%$ "; }
  std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(24)<<"Selection efficiency";
  for(int i=0;i<nPtBins;i++)
    { std::cout<<"& \\multicolumn{4}{c|}{"<<Form("%.1f",syst_CUT->at(i))<<"$\\%$} "; }
  std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(24)<<"Jet energy scale";
  for(int i=0;i<nPtBins;i++)
    for(int j=0;j<nDrBins;j++) { std::cout<<"& "<<Form("%.1f",syst_SCALE->at(i).at(j))<<"$\\%$ "; }
  std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(24)<<"Jet energy resolution";
  for(int i=0;i<nPtBins;i++)
    for(int j=0;j<nDrBins;j++) { std::cout<<"& "<<Form("%.1f",syst_RESO->at(i).at(j))<<"$\\%$ "; }
  std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(24)<<"Trigger efficiency";
  for(int i=0;i<nPtBins;i++)
    for(int j=0;j<nDrBins;j++) { std::cout<<"& "<<Form("%.1f",syst_TRIGGER->at(i).at(j))<<"$\\%$ "; }
  std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(24)<<"Non-closure";
  for(int i=0;i<nPtBins;i++)
    for(int j=0;j<nDrBins;j++) { std::cout<<"& "<<Form("%.1f",syst_NONCLOSURE->at(i).at(j))<<"$\\%$ "; }
  std::cout<<"\\\\"<<std::endl<<"\\hline\033[0m"<<std::endl;

}

int main(int argc, char* argv[])
{
  if(argc==7)
    {
      syst_plothist(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]));
      return 0;
    }
  std::cout<<"error: invalid parameter number - syst_plothist"<<std::endl;
  return 1;
}
