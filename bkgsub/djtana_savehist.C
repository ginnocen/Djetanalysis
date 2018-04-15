#include "djtana.h"

void djtana_savehist(TString inputname, TString outputname, TString collisionsyst,
                     Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax, 
                     Int_t maxevt=-1)
{
  if(createhists("savehist")) return;
  
  Int_t ispp = collisionsyst=="pp";
  djtcorr::setParameters(ispp);
  djtweight::init();
  Int_t isMC = 1;
 
  djet djt(inputname, ispp, isMC);
  initcutval(collisionsyst);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(20)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //

      if(djt.pthat < 30) continue;

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) {std::cout<<"wrong ibincent"<<std::endl; return;}

      Float_t cweight = 1.;
      // Float_t cweight = ispp?1.:centweight[djt.hiBin];
      // Float_t evtweight = 1;
      Float_t evtweight = isMC?(djt.pthatweight*cweight):1.;

      // loop jets
      for(int jj=0;jj<djt.njet_akpu3pf;jj++)
        {
          Float_t jetpt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetphi = (*djt.jetphi_akpu3pf)[jj];
          Float_t jeteta = (*djt.jeteta_akpu3pf)[jj];

          if(djtcorr::ptCorr(1, jetpt, 0., ibincent)) return;;

          /*********************************/
          if(jetpt < jetptmin || jetpt > jetptmax) continue;
          if(!(TMath::Abs(jeteta) > jetetamin && TMath::Abs(jeteta) < jetetamax)) continue;
          /*********************************/
          
          // loop D
          for(int jd=0;jd<djt.Gsize;jd++)
            {
              if(!( ((*djt.GisSignal)[jd]==1 || (*djt.GisSignal)[jd]==2) && TMath::Abs((*djt.Gy)[jd]) < 2. )) continue;
              Int_t ibinpt = xjjc::findibin(&ptBins, (*djt.Gpt)[jd]);
              if(ibinpt<0) continue;

              Float_t deltaR[nRefBins];
              deltaR[0] = djtuti::calr((*djt.Gphi)[jd], (*djt.Geta)[jd], jetphi, jeteta, 0);
              deltaR[1] = djtuti::calr((*djt.Gphi)[jd], (*djt.Geta)[jd], jetphi, jeteta, 1);
              ahSignalRPH[0][ibinpt]->Fill(deltaR[0], evtweight);
              ahSignalRPH[1][ibinpt]->Fill(deltaR[1], evtweight);
              if((*djt.subid_akpu3pf)[jj]==0 && (*djt.GcollisionId)[jd]==0) 
                {
                  ahSignalRP[0][ibinpt]->Fill(deltaR[0], evtweight);
                  ahSignalRP[1][ibinpt]->Fill(deltaR[1], evtweight);
                }
              if(deltaR[1] < 0.3) hDensity->Fill(ibinpt, evtweight);
            }
          if(ispp) continue;
          // loop UE D
          for(int jd=0;jd<djt.Gsize_mix;jd++)
            {
              if(!( ((*djt.GisSignal_mix)[jd]==1 || (*djt.GisSignal_mix)[jd]==2) && TMath::Abs((*djt.Gy_mix)[jd]) < 2. )) continue;
              Int_t ibinpt = xjjc::findibin(&ptBins, (*djt.Gpt_mix)[jd]);
              if(ibinpt<0) continue;

              Float_t deltaR = djtuti::calr((*djt.Gphi_mix)[jd], (*djt.Geta_mix)[jd], jetphi, jeteta, 0);
              ahSignalRMe[1][ibinpt]->Fill(deltaR, evtweight);
            }
        }
      if(ispp) continue;
      // loop MB jets
      for(int jj=0;jj<djt.njet_akpu3pf_mix;jj++)
        {
          Float_t jetpt = (*djt.jetpt_akpu3pf_mix)[jj];
          Float_t jetphi = (*djt.jetphi_akpu3pf_mix)[jj];
          Float_t jeteta = (*djt.jeteta_akpu3pf_mix)[jj];

          if(djtcorr::ptCorr(1, jetpt, 0., ibincent)) return;;

          /*********************************/
          if(jetpt < jetptmin || jetpt > jetptmax) continue;
          if(!(TMath::Abs(jeteta) > jetetamin && TMath::Abs(jeteta) < jetetamax)) continue;
          /*********************************/

          // loop D
          for(int jd=0;jd<djt.Gsize;jd++)
            {
              if(!( ((*djt.GisSignal)[jd]==1 || (*djt.GisSignal)[jd]==2) && TMath::Abs((*djt.Gy)[jd]) < 2. )) continue;
              Int_t ibinpt = xjjc::findibin(&ptBins, (*djt.Gpt)[jd]);
              if(ibinpt<0) continue;

              Float_t deltaR = djtuti::calr((*djt.Gphi)[jd], (*djt.Geta)[jd], jetphi, jeteta, 0);
              ahSignalRMe[0][ibinpt]->Fill(deltaR, evtweight);
            }
          // loop UE D
          for(int jd=0;jd<djt.Gsize_mix;jd++)
            {
              if(!( ((*djt.GisSignal_mix)[jd]==1 || (*djt.GisSignal_mix)[jd]==2) && TMath::Abs((*djt.Gy_mix)[jd]) < 2. )) continue;
              Int_t ibinpt = xjjc::findibin(&ptBins, (*djt.Gpt_mix)[jd]);
              if(ibinpt<0) continue;

              Float_t deltaR = djtuti::calr((*djt.Gphi_mix)[jd], (*djt.Geta_mix)[jd], jetphi, jeteta, 0);
              ahSignalRMe[2][ibinpt]->Fill(deltaR, evtweight);
            }
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<std::setw(30)<<"\033[0m event(s)."<<std::endl;
  std::cout<<std::endl;

  hDensity->Scale(1. / (3.14159265*0.3*0.3));
  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++)
        {
          Float_t area = 3.14159265 * (drBins[j+1]*drBins[j+1] - drBins[j]*drBins[j]);
          ahSignalRPH[1][i]->SetBinContent(j+1, hDensity->GetBinContent(i+1)*area);
          ahSignalRPH[1][i]->SetBinError(j+1, hDensity->GetBinError(i+1)*area);
        }
    }

  for(int i=0;i<nPtBins;i++)
    {
      ahSignalRPHsub[i]->Add(ahSignalRPH[0][i], ahSignalRPH[1][i], 1, -1);
      ahSignalRPsub[i]->Add(ahSignalRP[0][i], ahSignalRP[1][i], 1, -1);
      ahSignalRMesub[i]->Add(ahSignalRPH[0][i], ahSignalRMe[0][i], 1, -1);
      ahSignalRMesub[i]->Add(ahSignalRMe[1][i], -1);
      ahSignalRMesub[i]->Add(ahSignalRMe[2][i]);
    }
  
  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savehist")) return;
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==9)
    {
      djtana_savehist(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atoi(argv[8]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_savehist()"<<std::endl;
      return 1;
    }
}

int arguerr()
{
  return 0;
}

