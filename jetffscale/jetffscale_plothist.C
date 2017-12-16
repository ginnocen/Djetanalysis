#include "jetffscale.h"

void jetffscale_plothist(TString inputhistname, TString outputname,
                         TString collisionsyst, Int_t verboseonplot=0)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);

  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;

  TH2F* hemptyScaleNpfPt = new TH2F("hemptyScaleNpfPt", Form(";%s;#mu(p_{T}^{reco} / p_{T}^{gen})", ispp?"nPF":"nCS"), 10, minJtnpfBins, maxJtnpfBins, 10, ispp?0.9:0.8, ispp?1.1:1.2);
  xjjroot::sethempty(hemptyScaleNpfPt, 0, 0.4);
  for(int k=0;k<nCentBins;k++)
    {
      TString texcent = Form("Cent. %.0f - %.0f%s", centBins[k], centBins[k+1], "%");
      TCanvas* c15 = new TCanvas("c15", "", 1000, 600);
      c15->Divide(5, 3);
      std::vector<TF1*>* afScaleNpfPt = new std::vector<TF1*>(nJtptBins);
      std::vector<TLegend*>* alegScaleNpfPt = new std::vector<TLegend*>(nJtptBins);
      for(int i=0;i<nJtptBins;i++)
        {
          TString texpt = Form("%s < p_{T}^{reco jet} < %s", xjjc::number_remove_zero(jtptBins[i]).c_str(), xjjc::number_remove_zero(jtptBins[i+1]).c_str());
          c15->cd(i+1);
          hemptyScaleNpfPt->Draw();
          // alegScaleNpfPt->at(i) = new TLegend(0.53, 0.88-(nJtetaBins+1)*0.06, 0.85, 0.88);
          // xjjroot::setleg(legScaleNpfPt);
          xjjroot::setthgrstyle(hScaleNpfPt[k][i], kBlack, 24, 1.2, kBlack, 1, 1, -1, -1, -1);
          hScaleNpfPt[k][i]->Draw("same pe");
          // afScaleNpfPt->at(i) = new TF1("fScaleNpfPt", "[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", jtptBins[0], jtptBins[nJtptBins]);
          // afScaleNpfPt->at(i)->SetParLimits(0, 0.98, 1.02);
          // afScaleNpfPt->at(i)->SetParameter(0, 1);
          // afScaleNpfPt->at(i)->SetParameter(1, 0);
          // afScaleNpfPt->at(i)->SetParameter(2, 0.5);
          // if(ispp) afScaleNpfPt->at(i)->FixParameter(3, 0);
          // afScaleNpfPt->at(i)->SetLineWidth(3);
          // afScaleNpfPt->at(i)->SetLineColor(kGray+3);
          // afScaleNpfPt->at(i)->SetLineStyle(2);
          // hScaleNpfPt[k][i]->Fit("fScaleNpfPt", "L q", "", jtptBins[0], jtptBins[nJtptBins]);
          // hScaleNpfPt[k][i]->Fit("fScaleNpfPt", "m q", "", jtptBins[0], jtptBins[nJtptBins]);
          // xjjroot::drawtex(0.22, 0.2, Form("%.2f%s%.2f/#sqrt{x}%s%.2f/x%s%.2f/(x*x)",afScaleNpfPt->at(i)->GetParameter(0),afScaleNpfPt->at(i)->GetParameter(1)>=0?"+":"-",TMath::Abs(afScaleNpfPt->at(i)->GetParameter(1)),afScaleNpfPt->at(i)->GetParameter(2)>=0?"+":"-",TMath::Abs(afScaleNpfPt->at(i)->GetParameter(2)),afScaleNpfPt->at(i)->GetParameter(3)>=0?"+":"-",TMath::Abs(afScaleNpfPt->at(i)->GetParameter(3))));
          xjjroot::drawCMS(collisionsyst); 
          // legScaleNpfPt->Draw();
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6");
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texpt.Data());
          if(!ispp) xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), texcent);
        }
      c15->SaveAs(Form("plotresos/cScaleNpfPt_%s_%d.pdf",outputname.Data(),k));
      delete afScaleNpfPt;
      delete alegScaleNpfPt;
      delete c15;
    }

}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      jetffscale_plothist(argv[1], argv[2], argv[3]);
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
