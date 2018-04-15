#include "jetresolution.h"

void jetreso_savehist(TString inputname, TString outputname, TString collisionsyst,
                      Int_t seljetflavor=0,
                      Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);
  djtweight::init();
  djtcorr::setParameters(ispp);

  if(createhists("savehist")) return;
  // if(createhists("savehistetaphi")) return;
  djet djt(inputname, ispp, 1);

  TH1F* htest = new TH1F("htest", "", nResoJtdrBins, resojtdrBins);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   jetreso_savehist("<<std::setw(20)<<Form("%s)",collisionsyst.Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //

      if(djt.pthat < 15) continue; // to be discussed ...

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) { std::cout<<"wrong ibincent"<<std::endl; return; }

      // Float_t cweight = ispp?1.:djtweight::getcentweight(djt.hiBin);
      Float_t cweight = 1.;
      Float_t evtweight = djt.pthatweight*cweight;

      // loop jets
      for(int jj=0;jj<djt.njet_akpu3pf;jj++)
        {
          if((*djt.subid_akpu3pf)[jj]!=0) continue;

          if(seljetflavor==1 && ((*djt.gjetflavor_akpu3pf)[jj] <= -999 || (*djt.gjetflavor_akpu3pf)[jj] == 21)) continue;
          if(seljetflavor==2 && (*djt.gjetflavor_akpu3pf)[jj] != 21) continue;
          // if(TMath::Abs((*djt.gjetflavor_akpu3pf)[jj])!=4) continue;

          Int_t ibineta = xjjc::findibin(&jtetaBins, TMath::Abs((*djt.gjeteta_akpu3pf)[jj]));
          if(ibineta<0) continue; // |jet eta| < 1.6

          //
          Float_t jetrecopt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetrecopt_vScalePt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetrecopt_vRMatGScalePt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetrecopt_vFfScalePt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetrecopt_vFfJecScalePt = (*djt.jetpt_akpu3pf)[jj];
          Float_t gjetpt = (*djt.gjetpt_akpu3pf)[jj];
          Float_t gsmearjetpt = (*djt.gjetpt_akpu3pf)[jj];

          if( djtcorr::ptCorr(3, jetrecopt_vScalePt, 0., ibincent) ) return;
          if( djtcorr::ptCorr(1, jetrecopt_vRMatGScalePt, 0., ibincent) ) return;
          if( djtcorr::ptCorr(4, jetrecopt_vFfScalePt, (*djt.jetnpfpart_akpu3pf)[jj], ibincent) ) return;
          if( djtcorr::ptCorr(2, jetrecopt_vFfJecScalePt, (*djt.jetnpfpart_akpu3pf)[jj], ibincent) ) return;
          if( djtcorr::ptSmear(gsmearjetpt, ibincent) ) return;

          Int_t ibinpt = xjjc::findibin(&resojtptBins, (*djt.gjetpt_akpu3pf)[jj]);
          if(ibinpt>=0)
            {
              ahHistoResoPt[ibincent][0][ibinpt]->Fill(jetrecopt/gjetpt, evtweight);
              ahHistoResoPtCorr[ibincent][0][ibinpt]->Fill(jetrecopt_vScalePt/gjetpt, evtweight);
              ahHistoResoPtRMatGCorr[ibincent][0][ibinpt]->Fill(jetrecopt_vRMatGScalePt/gjetpt, evtweight);
              ahHistoResoPtFfCorr[ibincent][0][ibinpt]->Fill(jetrecopt_vFfScalePt/gjetpt, evtweight);
              ahHistoResoPtFfJecCorr[ibincent][0][ibinpt]->Fill(jetrecopt_vFfJecScalePt/gjetpt, evtweight);
              ahHistoResoPhi[ibincent][0][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
              ahHistoResoEta[ibincent][0][ibinpt]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
              // ahHistoResoEtaPhi[ibincent][0][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], (*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);

              ahHistoResoPt[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt/gjetpt, evtweight);
              ahHistoResoPtCorr[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt_vScalePt/gjetpt, evtweight);
              ahHistoResoPtRMatGCorr[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt_vRMatGScalePt/gjetpt, evtweight);
              ahHistoResoPtFfCorr[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt_vFfScalePt/gjetpt, evtweight);
              ahHistoResoPtFfJecCorr[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt_vFfJecScalePt/gjetpt, evtweight);
              ahHistoResoPhi[ibincent][ibineta+1][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
              ahHistoResoEta[ibincent][ibineta+1][ibinpt]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
              // ahHistoResoEtaPhi[ibincent][ibineta+1][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], (*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);              
            }

          hRecoVsGenPt->Fill(gjetpt, jetrecopt, evtweight);
          hRecoVsGenPtCorr->Fill(gjetpt, jetrecopt_vScalePt, evtweight);
          // hRecoVsGenPtRMatGStep1Corr->Fill(gjetpt, jetrecomatgenpt, evtweight);
          hRecoVsGenPtRMatGCorr->Fill(gjetpt, jetrecopt_vRMatGScalePt, evtweight);
          hRecoVsGenPtFfCorr->Fill(gjetpt, jetrecopt_vFfScalePt, evtweight);
          hRecoVsGenPtFfJecCorr->Fill(gjetpt, jetrecopt_vFfJecScalePt, evtweight);
          hGenSmearVsGenPt->Fill(gjetpt, gsmearjetpt, evtweight);
          hGenPtCorrNorm->Fill(gjetpt, evtweight);
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   jetreso_savehist("<<std::setw(30)<<Form("%s)",collisionsyst.Data())<<std::endl;
  std::cout<<std::endl;

  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  htest->Write();
  if(writehists("savehist")) return;
  outf->Write();
  outf->Close();
  // TFile* outfetaphi = new TFile(Form("%s_ResolutionEtaPhi.root",outputname.Data()), "recreate");
  // outfetaphi->cd();
  // if(writehists("savehistetaphi")) return;
  // outfetaphi->Write();
  // outfetaphi->Close();
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      jetreso_savehist(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));
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
