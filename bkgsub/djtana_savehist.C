#include "djtana.h"

void djtana_savehist(TString inputname, TString outputname, TString collisionsyst,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax, 
                     Int_t signalMC,
                     Int_t maxevt=-1)
{
  if(createhists("savehist")) return;
  
  Int_t ispp = collisionsyst=="pp";
  setnCentBins(ispp);
  Int_t isMC = 1;
 
  djet djt(inputname, ispp, isMC);
  initcutval(collisionsyst);

  TRandom3* pRandom3 = new TRandom3();

  std::vector<std::vector<Float_t>>* paramfScalePt = ispp?&paramfScalePt_pp:&paramfScalePt_PbPb;
  std::vector<std::vector<Float_t>>* paramfScaleRecoPt = ispp?&paramfScaleRecoPt_pp:&paramfScaleRecoPt_PbPb;
  std::vector<std::vector<Float_t>>* paramfScalePtFfCorr = ispp?&paramfScalePtFfCorr_pp:&paramfScalePtFfCorr_PbPb;
  std::vector<std::vector<Float_t>>* paramRealfP0 = ispp?&paramRealfP0_pp:&paramRealfP0_PbPb;
  std::vector<std::vector<Float_t>>* paramRealfP1 = ispp?&paramRealfP1_pp:&paramRealfP1_PbPb;

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(20)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //

      if(djt.pthat < 15) continue;

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) {std::cout<<"wrong ibincent"<<std::endl; return;}

      // Float_t cweight = 1.;
      Float_t cweight = ispp?1.:centweight[djt.hiBin];
      // Float_t evtweight = 1;
      Float_t evtweight = isMC?(djt.pthatweight*cweight):1.;

      // loop jets
      for(int jj=0;jj<djt.njet_akpu3pf;jj++)
        {
          if(signalMC && (*djt.subid_akpu3pf)[jj]!=0) continue;

          /*********************************/

          Float_t jetpt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetphi = (*djt.jetphi_akpu3pf)[jj];
          Float_t jeteta = (*djt.jeteta_akpu3pf)[jj];

          // JEC
          Float_t jetrecomatgenpt = jetpt / (paramfScaleRecoPt->at(ibincent).at(0) + paramfScaleRecoPt->at(ibincent).at(1)/TMath::Sqrt(jetpt) + paramfScaleRecoPt->at(ibincent).at(2)/jetpt + paramfScaleRecoPt->at(ibincent).at(3)/(jetpt*jetpt));
          Float_t vScalePt = paramfScalePt->at(ibincent).at(0) + paramfScalePt->at(ibincent).at(1)/TMath::Sqrt(jetrecomatgenpt) + paramfScalePt->at(ibincent).at(2)/jetrecomatgenpt + paramfScalePt->at(ibincent).at(3)/(jetrecomatgenpt*jetrecomatgenpt);

          jetpt = jetpt/vScalePt;

          /*********************************/
          if(jetpt < jetptmin) continue;
          if(!(TMath::Abs(jeteta) > jetetamin && TMath::Abs(jeteta) < jetetamax)) continue;
          /*********************************/

          if((*djt.subid_akpu3pf)[jj]==0) hnjet->Fill(1, evtweight);

          // loop D
          for(int jd=0;jd<djt.Gsize;jd++)
            {
              if(!( ((*djt.GisSignal)[jd]==1 || (*djt.GisSignal)[jd]==2) && TMath::Abs((*djt.Gy)[jd]) < 2. )) continue;
              Int_t ibinpt = xjjc::findibin(&ptBins, (*djt.Gpt)[jd]);
              if(ibinpt<0) continue;

              if(signalMC && (*djt.GcollisionId)[jd]!=0) continue;

              // to add pt-dependent event selection ...

              Float_t deltaphi = TMath::ACos(TMath::Cos((*djt.Gphi)[jd] - jetphi));
              Float_t deltaeta = (*djt.Geta)[jd] - jeteta;
              Float_t deltaetaref = (*djt.Geta)[jd] + jeteta;
              Float_t deltaR[nRefBins] = {(float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2)), 
                                          (float)TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2))};
              ahSignalRPH[0][ibinpt]->Fill(deltaR[0], evtweight);
              ahSignalRPH[1][ibinpt]->Fill(deltaR[1], evtweight);
              if((*djt.subid_akpu3pf)[jj]==0 && (*djt.GcollisionId)[jd]==0) ahSignalRP[ibinpt]->Fill(deltaR[0], evtweight);
              // if((*djt.subid_akpu3pf)[jj]==0) ahSignalRP[ibinpt]->Fill(deltaR[0], evtweight);
              else ahSignalRPHbkg[ibinpt]->Fill(deltaR[0], evtweight);
            }
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<std::setw(30)<<"\033[0m event(s)."<<std::endl;
  std::cout<<std::endl;

  for(int i=0;i<nPtBins;i++)
    {
      ahSignalRPHsub[i]->Add(ahSignalRPH[0][i], ahSignalRPH[1][i], 1, -1);
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
      djtana_savehist(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]), atoi(argv[7]), atoi(argv[8]));
      return 0;
    }
  if(argc==8)
    {
      djtana_savehist(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]), atoi(argv[7]));
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

