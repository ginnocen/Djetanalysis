#include "jetresolution.h"

void jetreso_plotpar()
{
  xjjroot::setgstyle();
  
  const int NP = 4;
  std::vector<TString> name = {"ScalePt", "ResoPtCorr", "ResoPhi", "ResoEta"};
  std::vector<std::vector<std::vector<Float_t>>*> paramf_pp = {&paramfScaleRecoPt_pp, &paramfResoPtCorr_pp, &paramfResoPhi_pp, &paramfResoEta_pp};
  std::vector<std::vector<std::vector<Float_t>>*> paramf_PbPb = {&paramfScaleRecoPt_PbPb, &paramfResoPtCorr_PbPb, &paramfResoPhi_PbPb, &paramfResoEta_PbPb};
  std::vector<TString> fun = {"[0]+[1]/TMath::Sqrt(x)+[2]/x+[3]/(x*x)", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))", "TMath::Sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/(x*x))"};
  std::vector<TString> var = {"p_{T}", "p_{T}", "#phi", "#eta"};
  std::vector<TString> obs = {"#mu", "#sigma", "#sigma", "#sigma"};
  std::vector<TString> sign = {"/", "/", "-", "-"};
  std::vector<Float_t> ymin = {1.0, 0, 0, 0};
  std::vector<Float_t> ymax = {1.4, 0.4, 0.05, 0.05};

  const int NI = 2;
  Int_t ispp[NI] = {0, 1};
  std::vector<std::vector<Color_t>> colorf = {{kAzure+3, kRed+3}, {kBlack}}; // 
  std::vector<std::vector<TString>> legf = {{"PbPb, 0-30%", "PbPb, 30-100%"}, {"pp"}}; // 

  for(int p=0;p<NP;p++)
    {
      TCanvas* c = new TCanvas("c", "", 600, 600);
      TH2F* hempty = new TH2F("hempty", Form(";reco jet p_{T} (GeV/c);%s(%s^{reco} %s %s^{gen})",obs[p].Data(),var[p].Data(),sign[p].Data(),var[p].Data()), 10, resojtptBins[0], resojtptBins[nResoJtptBins], 10, ymin[p], ymax[p]);
      xjjroot::sethempty(hempty, 0, 0.4);
      hempty->Draw();
      TLegend* leg = new TLegend(0.60, 0.88-3*0.06, 0.90, 0.88);
      xjjroot::setleg(leg);
      for(int i=0;i<NI;i++)
        {
          setnCentBins(ispp[i]);
          std::vector<std::vector<Float_t>>* paramf = ispp[i]?paramf_pp[p]:paramf_PbPb[p];
          for(int k=0;k<nCentBins;k++)
            {
              TF1* fReso = new TF1("fReso", fun[p].Data(), resojtptBins[0], resojtptBins[nResoJtptBins]);
              for(int m=0;m<paramf->at(k).size();m++)
                fReso->SetParameter(m, paramf->at(k).at(m));
              fReso->SetLineWidth(3);
              fReso->SetLineColor(colorf.at(i).at(k));
              fReso->SetLineStyle(1);
              fReso->Draw("same");
              leg->AddEntry(xjjroot::copyobject(fReso, Form("fReso_%d",i*10+k)), legf.at(i).at(k), "l");
            }
        }
      xjjroot::drawCMS("");
      leg->Draw();
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06; texypos += texdypos;
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), "|#eta^{reco jet}| < 1.6");
      c->SaveAs(Form("plotresos/cReso_%s.pdf",name[p].Data()));

      delete leg;
      delete hempty;
      delete c;
    }
}

  int main(int argc, char* argv[])
  {
    jetreso_plotpar();
    return 0;
  }

