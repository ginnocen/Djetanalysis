#include "jetresolution.h"

void jetreso_savehist(TString inputname, TString outputname, TString collisionsyst,
                      Int_t ifCorr=0, Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);

  if(createhists("savehist")) return;
  if(createhists("savehistetaphi")) return;
  djet djt(inputname, ispp, 1);

  std::vector<std::vector<Float_t>>* paramfScalePt = ispp?&paramfScalePt_pp:&paramfScalePt_PbPb;
  std::vector<std::vector<Float_t>>* paramfScaleRecoPt = ispp?&paramfScaleRecoPt_pp:&paramfScaleRecoPt_PbPb;
  std::vector<std::vector<Float_t>>* paramfScalePtFfCorr = ispp?&paramfScalePtFfCorr_pp:&paramfScalePtFfCorr_PbPb;
  std::vector<std::vector<Float_t>>* paramfP0 = ispp?&paramfP0_pp:&paramfP0_PbPb;
  std::vector<std::vector<Float_t>>* paramfP1 = ispp?&paramfP1_pp:&paramfP1_PbPb;
  std::vector<std::vector<Float_t>>* paramRealfP0 = ispp?&paramRealfP0_pp:&paramRealfP0_PbPb;
  std::vector<std::vector<Float_t>>* paramRealfP1 = ispp?&paramRealfP1_pp:&paramRealfP1_PbPb;

  std::vector<std::vector<Float_t>>* paramfResoPt = ispp?&paramfResoPtCorr_pp:&paramfResoPtCorr_PbPb;

  TRandom3* pRandom3 = new TRandom3();

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
      if(ibincent<0) {std::cout<<"wrong ibincent"<<std::endl; return;}

      Float_t leadGpt = -1;
      Float_t leadGphi = -20;
      Float_t leadGeta = -20;
      // Float_t leaddeltaR = -1;
      for(int jd=0;jd<djt.Gsize;jd++)
        {
          if(!((*djt.GisSignal)[jd]==1||(*djt.GisSignal)[jd]==2) || TMath::Abs((*djt.Gy)[jd])>2) continue;
          if((*djt.Gpt)[jd] > leadGpt)
            {
              leadGpt = (*djt.Gpt)[jd];
              leadGphi = (*djt.Gphi)[jd];
              leadGeta = (*djt.Geta)[jd];
              // leaddeltaR = deltaR;
            }
        }

      Float_t leadDpt = -1;
      Float_t leadDphi = -20;
      Float_t leadDeta = -20;
      // Float_t leaddeltaR = -1;
      for(int jd=0;jd<djt.Dsize;jd++)
        {
          if((*djt.Dgen)[jd]!=23333 || TMath::Abs((*djt.Dy)[jd])>2) continue;
          if((*djt.Dpt)[jd] > leadDpt)
            {
              leadDpt = (*djt.Dpt)[jd];
              leadDphi = (*djt.Dphi)[jd];
              leadDeta = (*djt.Deta)[jd];
              // leaddeltaR = deltaR;
            }
        }

      // loop jets
      for(int jj=0;jj<djt.njet_akpu3pf;jj++)
        {
          if((*djt.subid_akpu3pf)[jj]!=0) continue;
          // if(TMath::Abs((*djt.gjetflavor_akpu3pf)[jj])!=4) continue;

          Int_t ibineta = xjjc::findibin(&jtetaBins, TMath::Abs((*djt.gjeteta_akpu3pf)[jj]));
          if(ibineta<0) continue; // |jet eta| < 1.6

          // Float_t cweight = 1.;
          Float_t cweight = ispp?1.:centweight[djt.hiBin];
          // Float_t evtweight = 1;
          Float_t evtweight = djt.pthatweight*cweight;

          //
          Float_t jetrecopt = (*djt.jetpt_akpu3pf)[jj];
          Float_t gjetpt = (*djt.gjetpt_akpu3pf)[jj];
          Float_t gsmearjetpt = (*djt.gjetpt_akpu3pf)[jj];

          Float_t sigmaPt = TMath::Sqrt(paramfResoPt->at(ibincent).at(0)*paramfResoPt->at(ibincent).at(0) + paramfResoPt->at(ibincent).at(1)*paramfResoPt->at(ibincent).at(1)/gjetpt + paramfResoPt->at(ibincent).at(2)*paramfResoPt->at(ibincent).at(2)/(gjetpt*gjetpt));
          gsmearjetpt = gjetpt * pRandom3->Gaus(1, sigmaPt);

          Float_t vScalePt = ifCorr?(paramfScalePt->at(ibincent).at(0)+paramfScalePt->at(ibincent).at(1)/TMath::Sqrt(jetrecopt)+paramfScalePt->at(ibincent).at(2)/jetrecopt+paramfScalePt->at(ibincent).at(3)/(jetrecopt*jetrecopt)):1.;

          Float_t jetrecomatgenpt = jetrecopt / (paramfScaleRecoPt->at(ibincent).at(0) + paramfScaleRecoPt->at(ibincent).at(1)/TMath::Sqrt(jetrecopt) + paramfScaleRecoPt->at(ibincent).at(2)/jetrecopt + paramfScaleRecoPt->at(ibincent).at(3)/(jetrecopt*jetrecopt));
          Float_t vRMatGScalePt = ifCorr?(paramfScalePt->at(ibincent).at(0)+paramfScalePt->at(ibincent).at(1)/TMath::Sqrt(jetrecomatgenpt)+paramfScalePt->at(ibincent).at(2)/jetrecomatgenpt+paramfScalePt->at(ibincent).at(3)/(jetrecomatgenpt*jetrecomatgenpt)):1.;

          Float_t vFfScalePt = 1;
          Int_t ibinrecopt = xjjc::findibin(&jtptBins, (*djt.jetpt_akpu3pf)[jj]);
          if(ibinrecopt >=0)
            {
              Float_t pfP0 = paramRealfP0->at(ibincent).at(ibinrecopt);
              Float_t pfP1 = paramRealfP1->at(ibincent).at(ibinrecopt);
              vFfScalePt = ifCorr?(pfP1*((*djt.jetnpfpart_akpu3pf)[jj]-pfP0)):1;
            }

          Float_t vFfJecScalePt = 1;
          vFfJecScalePt = ifCorr?(paramfScalePtFfCorr->at(ibincent).at(0)+paramfScalePtFfCorr->at(ibincent).at(1)/TMath::Sqrt(jetrecopt/vFfScalePt)+paramfScalePtFfCorr->at(ibincent).at(2)/(jetrecopt/vFfScalePt)+paramfScalePtFfCorr->at(ibincent).at(3)/((jetrecopt/vFfScalePt)*(jetrecopt/vFfScalePt))):1.;

          Int_t ibinpt = xjjc::findibin(&resojtptBins, (*djt.gjetpt_akpu3pf)[jj]);
          if(ibinpt>=0)
            {
              ahHistoResoPt[ibincent][0][ibinpt]->Fill((*djt.jetpt_akpu3pf)[jj]/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtCorr[ibincent][0][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/vScalePt)/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtRMatGCorr[ibincent][0][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/vRMatGScalePt)/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtFfCorr[ibincent][0][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/vFfScalePt)/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtFfJecCorr[ibincent][0][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/(vFfScalePt*vFfJecScalePt))/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPhi[ibincent][0][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
              ahHistoResoEta[ibincent][0][ibinpt]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
              ahHistoResoEtaPhi[ibincent][0][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], (*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);

              ahHistoResoPt[ibincent][ibineta+1][ibinpt]->Fill((*djt.jetpt_akpu3pf)[jj]/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtCorr[ibincent][ibineta+1][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/vScalePt)/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtRMatGCorr[ibincent][ibineta+1][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/vRMatGScalePt)/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtFfCorr[ibincent][ibineta+1][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/vFfScalePt)/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPtFfJecCorr[ibincent][ibineta+1][ibinpt]->Fill(((*djt.jetpt_akpu3pf)[jj]/(vFfScalePt*vFfJecScalePt))/(*djt.gjetpt_akpu3pf)[jj], evtweight);
              ahHistoResoPhi[ibincent][ibineta+1][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
              ahHistoResoEta[ibincent][ibineta+1][ibinpt]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
              ahHistoResoEtaPhi[ibincent][ibineta+1][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], (*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
              
            }

          Int_t ibindeltajtpt = xjjc::findibin(&resodeltajtptBins, (*djt.gjetpt_akpu3pf)[jj]);
          if(ibindeltajtpt>=0)
            {
              ahHistoResoRecoDeltaPhi[ibincent][0][ibindeltajtpt]->Fill(leadDphi - (*djt.jetphi_akpu3pf)[jj], evtweight);              
              ahHistoResoRecoDeltaEta[ibincent][0][ibindeltajtpt]->Fill(leadDeta - (*djt.jeteta_akpu3pf)[jj], evtweight);              
              ahHistoResoGenDeltaPhi[ibincent][0][ibindeltajtpt]->Fill(leadGphi - (*djt.gjetphi_akpu3pf)[jj], evtweight);
              ahHistoResoGenDeltaEta[ibincent][0][ibindeltajtpt]->Fill(leadGeta - (*djt.gjeteta_akpu3pf)[jj], evtweight);              

              ahHistoResoRecoDeltaPhi[ibincent][ibineta+1][ibindeltajtpt]->Fill(leadDphi - (*djt.jetphi_akpu3pf)[jj], evtweight);              
              ahHistoResoRecoDeltaEta[ibincent][ibineta+1][ibindeltajtpt]->Fill(leadDeta - (*djt.jeteta_akpu3pf)[jj], evtweight);              
              ahHistoResoGenDeltaPhi[ibincent][ibineta+1][ibindeltajtpt]->Fill(leadGphi - (*djt.gjetphi_akpu3pf)[jj], evtweight);
              ahHistoResoGenDeltaEta[ibincent][ibineta+1][ibindeltajtpt]->Fill(leadGeta - (*djt.gjeteta_akpu3pf)[jj], evtweight);
            }

          hRecoVsGenPt->Fill((*djt.gjetpt_akpu3pf)[jj], (*djt.jetpt_akpu3pf)[jj], evtweight);
          hRecoVsGenPtCorr->Fill((*djt.gjetpt_akpu3pf)[jj], (*djt.jetpt_akpu3pf)[jj]/vScalePt, evtweight);
          hRecoVsGenPtRMatGStep1Corr->Fill((*djt.gjetpt_akpu3pf)[jj], jetrecomatgenpt, evtweight);
          hRecoVsGenPtRMatGCorr->Fill((*djt.gjetpt_akpu3pf)[jj], (*djt.jetpt_akpu3pf)[jj]/vRMatGScalePt, evtweight);
          hRecoVsGenPtFfCorr->Fill((*djt.gjetpt_akpu3pf)[jj], (*djt.jetpt_akpu3pf)[jj]/vFfScalePt, evtweight);
          hRecoVsGenPtFfJecCorr->Fill((*djt.gjetpt_akpu3pf)[jj], (*djt.jetpt_akpu3pf)[jj]/(vFfScalePt*vFfJecScalePt), evtweight);
          hGenSmearVsGenPt->Fill((*djt.gjetpt_akpu3pf)[jj], gsmearjetpt, evtweight);
          hGenPtCorrNorm->Fill((*djt.gjetpt_akpu3pf)[jj], evtweight);

          if((*djt.gjetpt_akpu3pf)[jj] > 40)
            {
              if(leadDpt > 0)
                {
                  Float_t leaddeltaphi = TMath::ACos(TMath::Cos(leadDphi - (*djt.gjetphi_akpu3pf)[jj]));
                  Float_t leaddeltaeta = TMath::Abs(leadDeta - (*djt.gjeteta_akpu3pf)[jj]);
                  Float_t leaddeltaR = TMath::Sqrt(pow(leaddeltaphi, 2) + pow(leaddeltaeta, 2));
                  Int_t ibindr = xjjc::findibin(&resojtdrBins, leaddeltaR);
                  if(ibindr>=0)
                    {
                      ahHistoResoDrPhi[ibincent][0][ibindr]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
                      ahHistoResoDrEta[ibincent][0][ibindr]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
                      ahHistoResoDrEtaPhi[ibincent][0][ibindr]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], (*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);                  

                      ahHistoResoDrPhi[ibincent][ibineta+1][ibindr]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
                      ahHistoResoDrEta[ibincent][ibineta+1][ibindr]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
                      ahHistoResoDrEtaPhi[ibincent][ibineta+1][ibindr]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], (*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);                  
                    }
                }
            }
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
  TFile* outfetaphi = new TFile(Form("%s_ResolutionEtaPhi.root",outputname.Data()), "recreate");
  outfetaphi->cd();
  if(writehists("savehistetaphi")) return;
  outfetaphi->Write();
  outfetaphi->Close();
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      jetreso_savehist(argv[1], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));
      return 0;
    }
  if(argc==5)
    {
      jetreso_savehist(argv[1], argv[2], argv[3], atoi(argv[4]));
      return 0;
    }
  if(argc==4)
    {
      jetreso_savehist(argv[1], argv[2], argv[3]);
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
