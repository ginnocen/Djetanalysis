#ifndef _MBSUBTRACT_CONFIG_H
#define _MBSUBTRACT_CONFIG_H

float cut_vz = 15;
int cut_pcollisionEventSelection = 1;

std::vector<std::string> jetCollections = {"akPu3PFJetAnalyzer", "akCs3PFJetAnalyzer", "akPu4PFJetAnalyzer", "akCs4PFJetAnalyzer"};
const int nMaxEvents_minBiasMixing = 25000;
const int nCentralityBins = 10;
const int nVertexBins = 5;
const int nEventPlaneBins = 2;
int nJetCollections = jetCollections.size();
const int nEventsToMix = 1;
float jetptmin=25;
const int maxjets=200;

#endif

