#include "../includes/xjjrootuti.h"
#include "utilitiescorrectedspectrum.h"
#include <TH2F.h>
#include <TH1F.h>
#include <TLegend.h>

void mcleadingptratio()
{
	TFile* fin=new TFile("foutputjetspectrumCorrected.root");
	fin->cd();
    initialise();
	xjjroot::setgstyle();