#include "jetffscale.h"

void jetffscale_plothist(TString inputhistname, TString inputscale, TString outputname,
                         TString collisionsyst, Int_t plotCorr=1)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);

  xjjroot::setgstyle();

  if(createhists("plothist")) return;
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;
  TFile* infscale = new TFile(Form("%s.root",inputscale.Data()));
  if(!infscale->IsOpen()) return;
  if(gethists(infscale, "plothistscale")) return;

  TH2F* hemptyScaleNpfPt = new TH2F("hemptyScaleNpfPt", Form(";%s;#mu(p_{T}^{reco} / p_{T}^{gen})", ispp?"nPF":"nCS"), 10, minJtnpfBins, maxJtnpfBins, 10, ispp?0.9:0.8, ispp?1.1:1.2);
  xjjroot::sethempty(hemptyScaleNpfPt, 0, 0.4);
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      // TCanvas* c15 = new TCanvas("c15", "", 1000, 600);
      // c15->Divide(5, 3);
      TCanvas* c15 = new TCanvas("c15", "", 1600, 1000);
      c15->Divide(8, 5);
      std::vector<TF1*>* afScaleNpfPt = new std::vector<TF1*>(nJtptBins);
      std::vector<TLegend*>* alegScaleNpfPt = new std::vector<TLegend*>(nJtptBins);
      for(int i=0;i<nJtptBins;i++)
        {
          TString texpt = Form("%s < p_{T}^{reco jet} < %s", xjjc::number_remove_zero(jtptBins[i]).c_str(), xjjc::number_remove_zero(jtptBins[i+1]).c_str());
          c15->cd(i+1);
          hemptyScaleNpfPt->Draw();
          // alegScaleNpfPt->at(i) = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
          // xjjroot::setleg(legScaleNpfPt->at(i));
          xjjroot::setthgrstyle(hScaleNpfPt[k][i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(hScaleNpfPtCorr[k][i], kRed+2, 24, 1.2, kRed+2, 1, 1, -1, -1, -1);
          xjjroot::setthgrstyle(hvScalePt[k][i], kOrange-9, -1, -1, -1, -1, -1, -1, -1, -1);
          if(plotCorr)
            hvScalePt[k][i]->Draw("same");
          xjjroot::drawline(minJtnpfBins, 1.0, maxJtnpfBins, 1.0, kGray+3, 2, 3);

          hScaleNpfPt[k][i]->Draw("same pe");
          afScaleNpfPt->at(i) = new TF1(Form("fScaleNpfPt%d",i), "[1]*(x-[0])", minJtnpfBins, maxJtnpfBins);
          afScaleNpfPt->at(i)->SetParameter(0, 20);
          afScaleNpfPt->at(i)->SetParameter(1, -0.12);
          afScaleNpfPt->at(i)->SetLineWidth(3);
          afScaleNpfPt->at(i)->SetLineColor(kAzure-6);
          afScaleNpfPt->at(i)->SetLineStyle(1);
          hScaleNpfPt[k][i]->Fit(Form("fScaleNpfPt%d",i), "L q", "", minJtnpfBins, ispp?maxJtnpfBins:30/*maxJtnpfBins*/);
          hScaleNpfPt[k][i]->Fit(Form("fScaleNpfPt%d",i), "m q", "", minJtnpfBins, ispp?maxJtnpfBins:30/*maxJtnpfBins*/);
          hScaleNpfPt[k][i]->Fit(Form("fScaleNpfPt%d",i), "m q", "", minJtnpfBins, ispp?maxJtnpfBins:30/*maxJtnpfBins*/);
          // xjjroot::drawtex(0.22, 0.2, Form("%.2f%s%.2f/#sqrt{x}%s%.2f/x%s%.2f/(x*x)",afScaleNpfPt->at(i)->GetParameter(0),afScaleNpfPt->at(i)->GetParameter(1)>=0?"+":"-",TMath::Abs(afScaleNpfPt->at(i)->GetParameter(1)),afScaleNpfPt->at(i)->GetParameter(2)>=0?"+":"-",TMath::Abs(afScaleNpfPt->at(i)->GetParameter(2)),afScaleNpfPt->at(i)->GetParameter(3)>=0?"+":"-",TMath::Abs(afScaleNpfPt->at(i)->GetParameter(3))));
          hScaleP0NpfPt[k]->SetBinContent(i+1, afScaleNpfPt->at(i)->GetParameter(0));
          hScaleP0NpfPt[k]->SetBinError(i+1, afScaleNpfPt->at(i)->GetParError(0));
          hScaleP1NpfPt[k]->SetBinContent(i+1, afScaleNpfPt->at(i)->GetParameter(1));
          hScaleP1NpfPt[k]->SetBinError(i+1, afScaleNpfPt->at(i)->GetParError(1));
          if(plotCorr)
            hScaleNpfPtCorr[k][i]->Draw("same pe");              
          xjjroot::drawCMS(collisionsyst); 
          // legScaleNpfPt->at(i)->Draw();
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6");
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texpt.Data());
          if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
        }
      c15->SaveAs(Form("plotresos/cScaleNpfPt%s_%s_%d.pdf",(plotCorr?"Corr":""),outputname.Data(),k));
      delete afScaleNpfPt;
      delete alegScaleNpfPt;
      delete c15;
    }
  TFile* outf = new TFile(Form("rootfiles/scalepar_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("plothist")) return;
  outf->Write();
  outf->Close();
}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      jetffscale_plothist(argv[1], argv[2], argv[3], argv[4]);
      return 0;
    }
  return 1;
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
