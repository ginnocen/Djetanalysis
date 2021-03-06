#include <TF1.h>
#include <TCanvas.h>
#include <TH2F.h>
#include "../../includes/xjjrootuti.h"
#include "fitpar.h"

void scale()
{
  xjjroot::setgstyle(1);
  initfitpar();

  const int NCOR = 2;
  TString collsyst[NCOR] = {"pp", "PbPb"};
  Float_t a0[NCOR] = {0.931362, 0.909772};
  Float_t a0err[NCOR] = {0.0128087, 0.0173298};
  Float_t a1[NCOR] = {0.0207396, 0.0339522};
  Float_t a1err[NCOR] = {0.0178277, 0.0288642};
  std::vector<TString> varfit[NCOR] = {varfitpp, varfitPbPb};
  std::vector<std::vector<float>> par[NCOR] = {parpp, parPbPb};
  
  for(int s=0;s<NCOR;s++)
    {
      for(int i=0;i<7;i++)
        {
          if(par[s].at(i).empty()) continue;
          for(int j=0;j<par[s].at(i).size();j++)
            {
              varfit[s].at(i) =  varfit[s].at(i)+(par[s].at(i).at(j)>0?"+":"-");
              varfit[s].at(i) = varfit[s].at(i)+Form("%f",fabs(par[s].at(i).at(j)));
              for(int k=0;k<j;k++)
                {
                  varfit[s].at(i) = varfit[s].at(i)+"*x";
                }
            }
          std::cout<<"\033[1;36mTString str_sigmaDmass_pol"<<i<<"_"<<collsyst[s]<<" = \""<<varfit[s].at(i)<<"\";\033[0m"<<std::endl;
        }
    }
  
  TCanvas* c = new TCanvas("c", "", 1200, 600);
  c->Divide(2, 1);
  TH2F* hempty = new TH2F("hempty", ";Dy;#sigma(data) / #sigma(MC)", 10, -2, 2, 10, 0.7, 1.3);
  xjjroot::sethempty(hempty);
  for(int i=0;i<NCOR;i++)
    {
      c->cd(i+1);
      TF1* f = new TF1("f", Form("%f+%f*x",a0[i],a1[i]), -2, 2);
      f->SetLineColor(kRed+3);
      f->SetLineWidth(3);
      TF1* af[4];
      Float_t a0var[4] = {a0[i]+a0err[i], a0[i]+a0err[i], a0[i]-a0err[i], a0[i]-a0err[i]};
      Float_t a1var[4] = {a1[i]+a1err[i], a1[i]-a1err[i], a1[i]+a1err[i], a1[i]-a1err[i]};
      for(int j=0;j<4;j++)
        {
          af[j] = new TF1(Form("af%d",j), Form("%f+%f*x",a0var[j],a1var[j]), -2, 2);
          af[j]->SetLineStyle(2);
          af[j]->SetLineColor(kRed-10);
          af[j]->SetLineWidth(3);
        }
      Float_t nhigh = af[1]->Eval(-2);
      Float_t phigh = af[0]->Eval(2);
      Float_t nlow = af[2]->Eval(-2);
      Float_t plow = af[3]->Eval(2);
      TF1* fhigh = new TF1("fhigh", Form("((%f-%f)/4.)*(x-2)+%f",phigh,nhigh,phigh), -2, 2);
      fhigh->SetLineStyle(10);
      fhigh->SetLineColor(kRed-7);
      fhigh->SetLineWidth(3);
      TF1* flow = new TF1("flow", Form("((%f-%f)/4.)*(x-2)+%f",plow,nlow,plow), -2, 2);
      flow->SetLineStyle(10);
      flow->SetLineColor(kRed-7);
      flow->SetLineWidth(3);

      TF1* afpol[7];
      for(int j=0;j<7;j++)
        {
          if(par[i].at(j).empty()) continue;
          afpol[j] = new TF1(Form("afpol%d",j), varfit[i].at(j), -2, 2);
          afpol[j]->SetLineStyle(10);
          afpol[j]->SetLineColor(colorlist[j-2]);
          afpol[j]->SetLineWidth(3);          
        }

      TLegend* leg = new TLegend(0.20, 0.86-0.05*3, 0.80, 0.86);
      leg->SetNColumns(2);
      xjjroot::setleg(leg);
      hempty->Draw();
      f->Draw("same");
      leg->AddEntry(f, "nominal (pol1)", "l");
      for(int j=0;j<4;j++) { af[j]->Draw("same"); }
      fhigh->Draw("same");
      flow->Draw("same"); 
      leg->AddEntry(fhigh, "vary par err", "l");
      for(int j=0;j<7;j++) 
        { 
          if(par[i].at(j).empty() || par[i].at(j).size()==2) continue;
          leg->AddEntry(afpol[j], Form("pol%d",par[i].at(j).size()-1), "l");
          afpol[j]->Draw("same"); 
        }
      leg->Draw();
      xjjroot::drawCMS(collsyst[i]);
      std::cout<<"\033[1;36mTString str_sigmaDmass_high_"<<collsyst[i]<<" = \""<<Form("((%f-%f)/4.)*(x-2)+%f",phigh,nhigh,phigh)<<"\";\033[0m"<<std::endl;
      std::cout<<"\033[1;36mTString str_sigmaDmass_low_"<<collsyst[i]<<" = \""<<Form("((%f-%f)/4.)*(x-2)+%f",plow,nlow,plow)<<"\";\033[0m"<<std::endl;
    }
  c->SaveAs("plotscale/cscale.pdf");  
}

int main()
{
  scale();
  return 0;
}
