#ifndef DJTCORR_H_
#define DJTCORR_H_

#include <vector>
#include <TRandom3.h>
#include "corrFactor.h"
#include "paramCorr.h"
#include "xjjcuti.h"

std::vector<std::vector<Float_t>>* paramfScalePt = 0;
std::vector<std::vector<Float_t>>* paramfResoPt = 0;
std::vector<std::vector<Float_t>>* paramfScaleRecoPt = 0;
std::vector<std::vector<Float_t>>* paramfScalePtFfCorr = 0;
std::vector<std::vector<Float_t>>* paramRealfP0 = 0;
std::vector<std::vector<Float_t>>* paramRealfP1 = 0;

std::vector<std::vector<Float_t>>* paramfResoPhi = 0;
std::vector<std::vector<Float_t>>* paramfResoEta = 0;
std::vector<std::vector<Float_t>>* paramfResoDeltaPhi = 0;
std::vector<std::vector<Float_t>>* paramfResoDeltaEta = 0;

std::vector<std::vector<Float_t>>* corrFactor6080 = 0;
std::vector<std::vector<Float_t>>* corrFactor80100 = 0;
std::vector<std::vector<Float_t>>* corrFactor100999 = 0;
std::vector<std::vector<Float_t>>* corrFactor60999 = 0;
std::vector<std::vector<Float_t>>* corrFactorSg6080 = 0;
std::vector<std::vector<Float_t>>* corrFactorSg80100 = 0;
std::vector<std::vector<Float_t>>* corrFactorSg100999 = 0;
std::vector<std::vector<Float_t>>* corrFactorSg60999 = 0;

TRandom3* pRandom3 = 0;

namespace djtcorr
{
  void setnCentBins(Int_t ispp) { nCentBins = ispp?1:NCentBins; }

  void setParameters(int ispp)
  {
    setnCentBins(ispp);
    pRandom3 = new TRandom3();

    paramfScalePt = ispp?&paramfScalePt_pp:&paramfScalePt_PbPb;
    paramfResoPt = ispp?&paramfResoPtCorr_pp:&paramfResoPtCorr_PbPb;
    paramfScaleRecoPt = ispp?&paramfScaleRecoPt_pp:&paramfScaleRecoPt_PbPb;
    paramfScalePtFfCorr = ispp?&paramfScalePtFfCorr_pp:&paramfScalePtFfCorr_PbPb;
    paramRealfP0 = ispp?&paramRealfP0_pp:&paramRealfP0_PbPb;
    paramRealfP1 = ispp?&paramRealfP1_pp:&paramRealfP1_PbPb;

    paramfResoPhi = ispp?&paramfResoPhi_pp:&paramfResoPhi_PbPb;
    paramfResoEta = ispp?&paramfResoEta_pp:&paramfResoEta_PbPb;

    corrFactor6080 = ispp?&corrFactor6080_pp:&corrFactor6080_PbPb;
    corrFactor80100 = ispp?&corrFactor80100_pp:&corrFactor80100_PbPb;
    corrFactor100999 = ispp?&corrFactor100999_pp:&corrFactor100999_PbPb;
    corrFactor60999 = ispp?&corrFactor60999_pp:&corrFactor60999_PbPb;

    corrFactorSg6080 = ispp?&corrFactorSg6080_pp:&corrFactorSg6080_PbPb;
    corrFactorSg80100 = ispp?&corrFactorSg80100_pp:&corrFactorSg80100_PbPb;
    corrFactorSg100999 = ispp?&corrFactorSg100999_pp:&corrFactorSg100999_PbPb;
    corrFactorSg60999 = ispp?&corrFactorSg60999_pp:&corrFactorSg60999_PbPb;
  }

  int ptCorr(int jescale, float &jetpt, float jetnpfpart, int ibincent)
  {
    if(!paramfScaleRecoPt || !paramfScalePt || !paramRealfP1 || !paramRealfP0 || !paramfScalePtFfCorr) { std::cout<<"error: set parameters first."<<std::endl; return 2; }
    if(jescale==1)
      {
        Float_t jetrecomatgenpt = jetpt / (paramfScaleRecoPt->at(ibincent).at(0) + paramfScaleRecoPt->at(ibincent).at(1)/TMath::Sqrt(jetpt) + paramfScaleRecoPt->at(ibincent).at(2)/jetpt + paramfScaleRecoPt->at(ibincent).at(3)/(jetpt*jetpt));
        Float_t vScalePt = paramfScalePt->at(ibincent).at(0) + paramfScalePt->at(ibincent).at(1)/TMath::Sqrt(jetrecomatgenpt) + paramfScalePt->at(ibincent).at(2)/jetrecomatgenpt + paramfScalePt->at(ibincent).at(3)/(jetrecomatgenpt*jetrecomatgenpt);
        jetpt = jetpt/vScalePt;
        return 0;
      }
    if(jescale==2)
      {
        Float_t vScaleFfPt = 1;
        Int_t ibinjtpt = xjjc::findibin(&jtptBins, jetpt);
        if(ibinjtpt >= 0)
          {
            vScaleFfPt = paramRealfP1->at(ibincent).at(ibinjtpt)*(jetnpfpart-paramRealfP0->at(ibincent).at(ibinjtpt));
          }
        jetpt = jetpt/vScaleFfPt;
        Float_t vScalePtFfCorr = paramfScalePtFfCorr->at(ibincent).at(0) + paramfScalePtFfCorr->at(ibincent).at(1)/TMath::Sqrt(jetpt) + paramfScalePtFfCorr->at(ibincent).at(2)/jetpt + paramfScalePtFfCorr->at(ibincent).at(3)/(jetpt*jetpt);
        jetpt = jetpt/vScalePtFfCorr;
        return 0;
      }
    if(jescale==3)
      {
        Float_t vScalePt = paramfScalePt->at(ibincent).at(0) + paramfScalePt->at(ibincent).at(1)/TMath::Sqrt(jetpt) + paramfScalePt->at(ibincent).at(2)/jetpt + paramfScalePt->at(ibincent).at(3)/(jetpt*jetpt);
        jetpt = jetpt/vScalePt;
        return 0;
      }
    if(jescale==4)
      {
        Float_t vScaleFfPt = 1;
        Int_t ibinjtpt = xjjc::findibin(&jtptBins, jetpt);
        if(ibinjtpt >= 0)
          {
            vScaleFfPt = paramRealfP1->at(ibincent).at(ibinjtpt)*(jetnpfpart-paramRealfP0->at(ibincent).at(ibinjtpt));
          }
        jetpt = jetpt/vScaleFfPt;
        return 0;
      }
    if(jescale==5)
      {
        Float_t jetrecomatgenpt = jetpt / (paramfScaleRecoPt->at(ibincent).at(0) + paramfScaleRecoPt->at(ibincent).at(1)/TMath::Sqrt(jetpt) + paramfScaleRecoPt->at(ibincent).at(2)/jetpt + paramfScaleRecoPt->at(ibincent).at(3)/(jetpt*jetpt));
        jetpt = jetrecomatgenpt;
        return 0;
      }
    std::cout<<"invalid jescale"<<std::endl; 
    return 1;
  }

  int ptSmear(float &jetpt, int ibincent)
  {
    if(!paramfResoPt) { std::cout<<"error: set parameters first."<<std::endl; return 2; }
    // if(jetpt > 10)
    if(jetpt > 0)
      {
        Float_t sigmaPt = TMath::Sqrt(paramfResoPt->at(ibincent).at(0)*paramfResoPt->at(ibincent).at(0) +
                                      paramfResoPt->at(ibincent).at(1)*paramfResoPt->at(ibincent).at(1)/jetpt +
                                      paramfResoPt->at(ibincent).at(2)*paramfResoPt->at(ibincent).at(2)/(jetpt*jetpt));
        jetpt = jetpt * pRandom3->Gaus(1, sigmaPt);
      }
    return 0;
  }

  int angleSmear(int gensmearphi, float &jeteta, float &jetphi, float jetpt, int ibincent)
  {
    if(!paramfResoPhi || !paramfResoEta || !paramfResoDeltaPhi || !paramfResoDeltaEta) { std::cout<<"error: set parameters first."<<std::endl; return 2; }
    if(gensmearphi==1)
      {
        Float_t sigmaPhi = TMath::Sqrt(paramfResoPhi->at(ibincent).at(0)*paramfResoPhi->at(ibincent).at(0) +
                                       paramfResoPhi->at(ibincent).at(1)*paramfResoPhi->at(ibincent).at(1)/jetpt +
                                       paramfResoPhi->at(ibincent).at(2)*paramfResoPhi->at(ibincent).at(2)/(jetpt*jetpt));
        jetphi = jetphi + pRandom3->Gaus(0, sigmaPhi);

        Float_t sigmaEta = TMath::Sqrt(paramfResoEta->at(ibincent).at(0)*paramfResoEta->at(ibincent).at(0) +
                                       paramfResoEta->at(ibincent).at(1)*paramfResoEta->at(ibincent).at(1)/jetpt +
                                       paramfResoEta->at(ibincent).at(2)*paramfResoEta->at(ibincent).at(2)/(jetpt*jetpt));
        jeteta = jeteta + pRandom3->Gaus(0, sigmaEta);
        return 0;
      }
    else if(gensmearphi==2)
      {
        Float_t sigmaPhi = TMath::Sqrt(paramfResoDeltaPhi->at(ibincent).at(0)*paramfResoDeltaPhi->at(ibincent).at(0) +
                                       paramfResoDeltaPhi->at(ibincent).at(1)*paramfResoDeltaPhi->at(ibincent).at(1)/jetpt +
                                       paramfResoDeltaPhi->at(ibincent).at(2)*paramfResoDeltaPhi->at(ibincent).at(2)/(jetpt*jetpt)
                                       - (paramfResoDeltaPhi->at(ibincent).at(3)*paramfResoDeltaPhi->at(ibincent).at(3) +
                                          paramfResoDeltaPhi->at(ibincent).at(4)*paramfResoDeltaPhi->at(ibincent).at(4)/jetpt +
                                          paramfResoDeltaPhi->at(ibincent).at(5)*paramfResoDeltaPhi->at(ibincent).at(5)/(jetpt*jetpt)));
        jetphi = jetphi + pRandom3->Gaus(0, sigmaPhi);

        Float_t sigmaEta = TMath::Sqrt(paramfResoDeltaEta->at(ibincent).at(0)*paramfResoDeltaEta->at(ibincent).at(0) +
                                       paramfResoDeltaEta->at(ibincent).at(1)*paramfResoDeltaEta->at(ibincent).at(1)/jetpt +
                                       paramfResoDeltaEta->at(ibincent).at(2)*paramfResoDeltaEta->at(ibincent).at(2)/(jetpt*jetpt)
                                       - (paramfResoDeltaEta->at(ibincent).at(3)*paramfResoDeltaEta->at(ibincent).at(3) +
                                          paramfResoDeltaEta->at(ibincent).at(4)*paramfResoDeltaEta->at(ibincent).at(4)/jetpt +
                                          paramfResoDeltaEta->at(ibincent).at(5)*paramfResoDeltaEta->at(ibincent).at(5)/(jetpt*jetpt)));
        jeteta = jeteta + pRandom3->Gaus(0, sigmaEta);
        return 0;
      }
    std::cout<<"invalid gensmearphi"<<std::endl; 
    return 1; 
  }

  int ptSmearPP(std::vector<float>* vjetpt, float jetpt, int ibincent, int NSMEAR)
  {
    Float_t sigmaPtPP = TMath::Sqrt((paramfResoPtCorr_PbPb.at(ibincent).at(0)*paramfResoPtCorr_PbPb.at(ibincent).at(0) +
                                     paramfResoPtCorr_PbPb.at(ibincent).at(1)*paramfResoPtCorr_PbPb.at(ibincent).at(1)/jetpt +
                                     paramfResoPtCorr_PbPb.at(ibincent).at(2)*paramfResoPtCorr_PbPb.at(ibincent).at(2)/(jetpt*jetpt)) -
                                    (paramfResoPtCorr_pp.at(ibincent).at(0)*paramfResoPtCorr_pp.at(ibincent).at(0) +
                                     paramfResoPtCorr_pp.at(ibincent).at(1)*paramfResoPtCorr_pp.at(ibincent).at(1)/jetpt +
                                     paramfResoPtCorr_pp.at(ibincent).at(2)*paramfResoPtCorr_pp.at(ibincent).at(2)/(jetpt*jetpt)));
    for(int s=0;s<NSMEAR;s++)
      {
        float sjetpt = jetpt;
        if(jetpt > 10)
          {
            sjetpt = jetpt * pRandom3->Gaus(1, sigmaPtPP);
          }
        vjetpt->push_back(sjetpt);
      }
    return 0;
  }

  int angleSmearPP(std::vector<float>* vjeteta, std::vector<float>* vjetphi, float jeteta, float jetphi, float jetpt, int ibincent, int NSMEAR)
  {
    Float_t sigmaPhiPP = TMath::Sqrt((paramfResoPhi_PbPb.at(ibincent).at(0)*paramfResoPhi_PbPb.at(ibincent).at(0) +
                                      paramfResoPhi_PbPb.at(ibincent).at(1)*paramfResoPhi_PbPb.at(ibincent).at(1)/jetpt +
                                      paramfResoPhi_PbPb.at(ibincent).at(2)*paramfResoPhi_PbPb.at(ibincent).at(2)/(jetpt*jetpt)) -
                                     (paramfResoPhi_pp.at(ibincent).at(0)*paramfResoPhi_pp.at(ibincent).at(0) +
                                      paramfResoPhi_pp.at(ibincent).at(1)*paramfResoPhi_pp.at(ibincent).at(1)/jetpt +
                                      paramfResoPhi_pp.at(ibincent).at(2)*paramfResoPhi_pp.at(ibincent).at(2)/(jetpt*jetpt)));
    Float_t sigmaEtaPP = TMath::Sqrt((paramfResoEta_PbPb.at(ibincent).at(0)*paramfResoEta_PbPb.at(ibincent).at(0) +
                                      paramfResoEta_PbPb.at(ibincent).at(1)*paramfResoEta_PbPb.at(ibincent).at(1)/jetpt +
                                      paramfResoEta_PbPb.at(ibincent).at(2)*paramfResoEta_PbPb.at(ibincent).at(2)/(jetpt*jetpt)) -
                                     (paramfResoEta_pp.at(ibincent).at(0)*paramfResoEta_pp.at(ibincent).at(0) +
                                      paramfResoEta_pp.at(ibincent).at(1)*paramfResoEta_pp.at(ibincent).at(1)/jetpt +
                                      paramfResoEta_pp.at(ibincent).at(2)*paramfResoEta_pp.at(ibincent).at(2)/(jetpt*jetpt)));
    for(int s=0;s<NSMEAR;s++)
      {
        float sjetphi = jetphi + pRandom3->Gaus(0, sigmaPhiPP);
        float sjeteta = jeteta + pRandom3->Gaus(0, sigmaEtaPP);
        vjetphi->push_back(sjetphi);
        vjeteta->push_back(sjeteta);
      }
    return 0;
  }

  int getcorrFactor(float &corrfactor, int ibinpt, int ibindr, float jetptmin, float jetptmax)
  {
    if(!corrFactor6080 || !corrFactor80100 || !corrFactor100999 || !corrFactor60999) { std::cout<<"error: set parameters first."<<std::endl; return 2; }
    if(jetptmin==60 && jetptmax==80) { corrfactor = corrFactor6080->at(ibinpt).at(ibindr); return 0; }
    else if(jetptmin==80 && jetptmax==100) { corrfactor = corrFactor80100->at(ibinpt).at(ibindr); return 0; }
    else if(jetptmin==100 && jetptmax==999) { corrfactor = corrFactor100999->at(ibinpt).at(ibindr); return 0; }
    else if(jetptmin==60 && jetptmax==999) { corrfactor = corrFactor60999->at(ibinpt).at(ibindr); return 0; }
    else { std::cout<<"error: invalid jetptmin or jetptmax."<<std::endl; return 1; }

    return 0;    
  }

  int getcorrFactorSg(float &corrfactorSg, int ibinpt, int ibindr, float jetptmin, float jetptmax)
  {
    // if(!corrFactorSg) { std::cout<<"error: set parameters first."<<std::endl; return 2; }
    if(!corrFactorSg6080 || !corrFactorSg80100 || !corrFactorSg100999 || !corrFactorSg60999) { std::cout<<"error: set parameters first."<<std::endl; return 2; }
    if(jetptmin==60 && jetptmax==80) { corrfactorSg = corrFactorSg6080->at(ibinpt).at(ibindr); return 0; }
    else if(jetptmin==80 && jetptmax==100) { corrfactorSg = corrFactorSg80100->at(ibinpt).at(ibindr); return 0; }
    else if(jetptmin==100 && jetptmax==999) { corrfactorSg = corrFactorSg100999->at(ibinpt).at(ibindr); return 0; }
    else if(jetptmin==60 && jetptmax==999) { corrfactorSg = corrFactorSg60999->at(ibinpt).at(ibindr); return 0; }
    else { std::cout<<"error: invalid jetptmin or jetptmax."<<std::endl; return 1; }
    // corrfactorSg = corrFactorSg->at(ibinpt).at(ibindr);
    // return 0;    
  }

}

#endif
