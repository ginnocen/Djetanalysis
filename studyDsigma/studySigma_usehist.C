#include "studySigma.h"

void studySigma_usehist(TString inputhistname, TString inputtplname, TString outputname, TString collisionsyst,int indexgaussian=2)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  
  if (!(indexgaussian==2 || indexgaussian ==5)) std::cout<<"wrong index of gaussian"<<std::endl;
  xjjroot::setgstyle();

  if(createhists("usehist")) return;
  Bool_t ispp = collisionsyst=="pp";
  Bool_t isMC = inputhistname.Contains("MC");
  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "hist")) return;

  TFile* inftpl = new TFile(Form("%s.root",inputtplname.Data()));
  if(!inftpl->IsOpen()) return;
  if(gethists(inftpl, "tpl")) return;

  xjjroot::dfitter* dft = new xjjroot::dfitter("S");

  TCanvas* cy = new TCanvas("cy", "cy", 600*nyBins, 600);
  cy->Divide(nyBins, 1);
  
  std::vector<TString> vectexy ={"p_{T}>10 GeV"};
  
  for(int i=0;i<nyBins;i++){
    cy->cd(i+1);
    dft->fit(ahHistoMassY[i], ahHistoMassYSignal[i], ahHistoMassYSwapped[i], collisionsyst, vectexy);
    if(dft->drawfit(collisionsyst, vectexy)) return;

    TF1* fmass=(TF1*)dft->GetFun_mass();
    
    double variable[nvariables];
    double errvariable[nvariables];

    variable[0]=fmass->GetParameter(1);
    variable[1]=fmass->GetParameter(indexgaussian)*(1+fmass->GetParameter(6));
    variable[2]=dft->GetY();

    errvariable[0]=fmass->GetParError(1);
    errvariable[1]=fmass->GetParameter(indexgaussian)*fmass->GetParError(6);
    errvariable[2]=dft->GetYE();

    for (int j=0;j<nvariables;j++){
      ahHistoY[j]->SetBinContent(i+1,variable[j]);
      ahHistoY[j]->SetBinError(i+1,errvariable[j]);
    }
  }
  cy->SaveAs(Form("plotfits/cmassY_%s.pdf",outputname.Data()));

  TCanvas* cpt = new TCanvas("cpt", "cpt", 600*nptBins, 600);
  cpt->Divide(nptBins, 1);
  
  std::vector<TString> vectexpt ={"|y^{D}| < 2"};

  for(int i=0;i<nptBins;i++){
    cy->cd(i+1);
    dft->fit(ahHistoMassPt[i], ahHistoMassPtSignal[i], ahHistoMassPtSwapped[i], collisionsyst, vectexpt);
    if(dft->drawfit(collisionsyst, vectexy)) return;

    TF1* fmass=(TF1*)dft->GetFun_mass();
    
    double variable[nvariables];
    double errvariable[nvariables];

    variable[0]=fmass->GetParameter(1);
    variable[1]=fmass->GetParameter(indexgaussian)*(1+fmass->GetParameter(6));
    variable[2]=dft->GetY();

    errvariable[0]=fmass->GetParError(1);
    errvariable[1]=fmass->GetParameter(indexgaussian)*fmass->GetParError(6);
    errvariable[2]=dft->GetYE();
    
    for (int j=0;j<nvariables;j++){
      ahHistoPt[j]->SetBinContent(i+1,variable[j]);
      ahHistoPt[j]->SetBinError(i+1,errvariable[j]);
    }
  }
  cy->SaveAs(Form("plotfits/cmassPt_%s.pdf",outputname.Data()));


  TFile* outf = new TFile(Form("rootfiles/xsec_%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("usehist")) return;
  outf->Write();
  outf->Close();
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      studySigma_usehist(argv[1], argv[2], argv[3], argv[4],atoi(argv[5]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_usehist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst)
{
  if(collisionsyst!="pp" && collisionsyst!="PbPb")
    {
      std::cout<<"error: invalid collisionsyst"<<std::endl;
      return 1;
    }
  return 0;
}

