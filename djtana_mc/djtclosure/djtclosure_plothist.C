#include "djtclosure.h"

Float_t ypaddiv = 2./3, yPullpaddiv = 1-ypaddiv;
void djtclosure_plothist(std::vector<TString> inputhistname, TString outputname,
                         TString collisionsyst,
                         Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax)
{
  void setup_hemptypull(TH2F* hemptyPull);  
  int arguerr(std::vector<TString>inputhistname, TString collisionsyst);
  if(arguerr(inputhistname, collisionsyst)) return;

  Bool_t ispp = collisionsyst=="pp";

  if(createhists("plothist")) return;

  std::vector<TFile*> infhist(nCases, 0);
  for(int m=0;m<nCases;m++)
    {
      infhist[m] = new TFile(Form("%s.root",inputhistname[m].Data()));
      if(!infhist[m]->IsOpen()) return;
    }
  if(gethists(infhist, "plothist")) return;

  // preparation
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999? Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()): Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);
  TString texpythia = ispp?"PYTHIA":"PYTHIA + HYDJET";
  vectex.push_back(texpythia);

  std::vector<float> vdrBins;
  for(int j=0;j<sizeof(drBins)/sizeof(drBins[0]);j++) vdrBins.push_back(drBins[j]);
  std::vector<TString>            xtitle           = {"r"};
  std::vector<TString>            ytitle           = {"#frac{1}{N_{jD}} #frac{dN_{jD}}{dr}"};
  std::vector<TString>            tname            = {"dr"};
  std::vector<std::vector<float>> vxBins           = {vdrBins};
  // std::vector<TH1F**>             hSignalXnorm     = {(TH1F**)ahSignalRnorm};
  // std::vector<TH1F**>             hSignalXnormPull = {(TH1F**)ahSignalRnormPull};
  std::vector<TH1F**>             hSignalXsub      = {(TH1F**)ahSignalRsub};
  std::vector<TH1F**>             hSignalXsubPull  = {(TH1F**)ahSignalRsubPull};
  std::vector<float>              yPullaxismin     = {0.2};
  std::vector<float>              yPullaxismax     = {2.2};

  int k = 0;

  // calculate pull
  for(int i=0;i<nPtBins;i++)
    {
      for(int m=0;m<nCases;m++)
        {
          (hSignalXsubPull.at(k))[m*nPtBins+i]->Divide((hSignalXsub.at(k))[m*nPtBins+i], 
                                                       (hSignalXsub.at(k))[(nCases-1)*nPtBins+i]); // hSignalXsub[nCases-1][i] is truth
        }
    }

  // plot
  for(int i=0;i<nPtBins;i++)
    {
      Float_t yaxismax = ahSignalRsub[0][i]->GetBinContent(1) * 1.e+3;
      Float_t yaxismin = ahSignalRsub[0][i]->GetBinContent(nDrBins) * 1.e-2;
      TCanvas* c[3];
      for(int j=0;j<3;j++) { c[j] = new TCanvas(Form("c%d",j), "", 600, 800); }
      TPad* pXsec[3];
      for(int j=0;j<3;j++)
        {
          pXsec[j] = new TPad(Form("pXsec%d"), "", 0, 1-ypaddiv, 1, 1);
          pXsec[j]->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
        }
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s",xtitle[k].Data(),ytitle[k].Data()), 5, vxBins[k].front(), vxBins[k].back(), 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      TLegend* leg = new TLegend(0.58, 0.88-nCases*0.06, 0.90, 0.88);
      xjjroot::setleg(leg);
      for(int m=nCases-1;m>=0;m--)
        {
          xjjroot::setthgrstyle((hSignalXsub.at(k))[m*nPtBins+i], amcolor[m], amstyle[m], 1.2, amcolor[m], 1, 1, -1, -1, -1);
          leg->AddEntry((hSignalXsub.at(k))[m*nPtBins+i], legCases[m].Data(), "p");
        }
      for(int j=0;j<3;j++)
        {
          c[j]->cd();
          pXsec[j]->Draw();
          pXsec[j]->cd();
          pXsec[j]->SetLogy();
          hempty->Draw();
          for(int m=nCases-1;m>=0;m--)
            { (hSignalXsub.at(k))[m*nPtBins+i]->Draw("pe same"); }
          xjjroot::drawCMS(collisionsyst);
          Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
          texypos += texdypos;
          for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
            xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
          TString tpt = ptBins[i+1]>=999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
          xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), tpt.Data());
          leg->Draw();
        }

      TPad* pPull[3];
      for(int j=0;j<3;j++) 
        {
          pPull[j]= new TPad(Form("pPull%d"), "", 0, 0, 1, yPullpaddiv);
          pPull[j]->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0.07*1/yPullpaddiv, 0);
        }
      TH2F* hemptyPull = new TH2F("hemptyPull", Form(";%s;%s",xtitle[k].Data(),"X / GenD,sGenJ"), 5, vxBins[k].front(), vxBins[k].back(), 10, yPullaxismin[k], yPullaxismax[k]);
      setup_hemptypull(hemptyPull);
      for(int m=nCases-1;m>=0;m--)
        { xjjroot::setthgrstyle((hSignalXsubPull.at(k))[m*nPtBins+i], amcolor[m], amstyle[m], 1.2, amcolor[m], 1, 1, -1, -1, -1); }
      c[0]->cd();
      pPull[0]->Draw();
      pPull[0]->cd();
      hemptyPull->Draw();
      xjjroot::drawbox(vxBins[k].front(), 0.90, vxBins[k].back(), 1.10, kGray, 0.4);
      xjjroot::drawline(vxBins[k].front(), 1.00, vxBins[k].back(), 1.00, kGray+2, 2, 4);
      for(int m=nCases-1;m>=0;m--)
        { (hSignalXsubPull.at(k))[m*nPtBins+i]->Draw("pe same"); }
      c[0]->SaveAs(Form("plotclosure/cclosuresub_xsec_%s_%s_pt_%s_%s.pdf",outputname.Data(),tname[k].Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));
      c[1]->cd();
      pPull[1]->Draw();
      pPull[1]->cd();
      hemptyPull->Draw();
      xjjroot::drawbox(vxBins[k].front(), 0.90, vxBins[k].back(), 1.10, kGray, 0.4);
      xjjroot::drawline(vxBins[k].front(), 1.00, vxBins[k].back(), 1.00, kGray+2, 2, 4);
      (hSignalXsubPull.at(k))[1*nPtBins+i]->Draw("pe same");
      TLegend* legJetclosure = new TLegend(0.40, 0.90-0.07, 0.80, 0.90);
      xjjroot::setleg(legJetclosure, 0.07);
      legJetclosure->AddEntry((hSignalXsubPull.at(k))[1*nPtBins+i], "GenD, RecoJet / GenD, sGenJet");
      legJetclosure->Draw();
      c[1]->SaveAs(Form("plotclosureAN/cclosuresub_xsec_Jetclosure_%s_%s_pt_%s_%s.pdf",outputname.Data(),tname[k].Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));
      c[2]->cd();
      pPull[2]->Draw();
      pPull[2]->cd();
      hemptyPull->Draw();
      xjjroot::drawbox(vxBins[k].front(), 0.90, vxBins[k].back(), 1.10, kGray, 0.4);
      xjjroot::drawline(vxBins[k].front(), 1.00, vxBins[k].back(), 1.00, kGray+2, 2, 4);
      (hSignalXsubPull.at(k))[2*nPtBins+i]->Draw("pe same");
      TLegend* legDclosure = new TLegend(0.40, 0.90-0.07, 0.80, 0.90);
      xjjroot::setleg(legDclosure, 0.07);
      legDclosure->AddEntry((hSignalXsubPull.at(k))[2*nPtBins+i], "RecoD, sGenJet / GenD, sGenJet");
      legDclosure->Draw();
      c[2]->SaveAs(Form("plotclosureAN/cclosuresub_xsec_Dclosure_%s_%s_pt_%s_%s.pdf",outputname.Data(),tname[k].Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str()));

      delete legDclosure;
      delete legJetclosure;
      delete leg;
      delete hemptyPull;
      delete hempty;
      for(int j=0;j<3;j++) { delete pPull[j]; delete pXsec[j]; delete c[j]; }
    }
}

int main(int argc, char* argv[])
{
  if(argc==(nCases+7))
    {
      std::vector<TString> inputhistname;
      for(int m=0;m<nCases;m++) inputhistname.push_back(argv[m+1]);
      djtclosure_plothist(inputhistname, argv[nCases+1], argv[nCases+2], atof(argv[nCases+3]), atof(argv[nCases+4]), atof(argv[nCases+5]), atof(argv[nCases+6]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtclosure_plothist()"<<std::endl;
      return 1;
    }
}

int arguerr(std::vector<TString>inputhistname, TString collisionsyst)
{
  if(inputhistname.size()!=nCases)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"inputhistname\""<<std::endl;
      return 1;
    } 
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    } 
  return 0;
}

void setup_hemptypull(TH2F* hemptyPull)
{
  hemptyPull->GetXaxis()->SetNdivisions(505);
  hemptyPull->GetYaxis()->SetNdivisions(504);
  xjjroot::sethempty(hemptyPull, -0.5, -0);
  hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv) *(1+1.8));
  hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv) *(1+12));
  hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv));
}
