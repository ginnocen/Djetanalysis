#ifndef _JET_TREE_H
#define _JET_TREE_H

#include "TTree.h"

class jetTree {
public:
  jetTree() {
    nref = -99;
    rawpt = 0;
    jtpt = 0;
    jteta = 0;
    jtphi = 0;
    refpt = 0;
    refeta = 0;
    refphi = 0;
    refparton_flavor = 0;
    subid = 0;
    chargedMax = 0;
    chargedSum = 0;
    chargedN = 0;
    photonMax = 0;
    photonSum = 0;
    photonN = 0;
    neutralMax = 0;
    neutralSum = 0;
    neutralN = 0;
    eMax = 0;
    eSum = 0;
    eN = 0;
    muMax = 0;
    muSum = 0;
    muN = 0;

    ngen = -99;
    genpt = 0;
    geneta = 0;
    genphi = 0;
    gensubid = 0;
  }
  ~jetTree() {
    clear_memory();
  };

  jetTree(TTree* t) : jetTree() {
    this->read_tree(t);
  }

  void init_memory();
  void clear_memory();
  void read_tree(TTree* t);

  int nref;
  float* rawpt;
  float* jtpt;
  float* jteta;
  float* jtphi;
  float* refpt;
  float* refeta;
  float* refphi;
  int* refparton_flavor;
  int* subid;

  float* chargedMax;
  float* chargedSum;
  int* chargedN;
  float* photonMax;
  float* photonSum;
  int* photonN;
  float* neutralMax;
  float* neutralSum;
  int* neutralN;
  float* eMax;
  float* eSum;
  int* eN;
  float* muMax;
  float* muSum;
  int* muN;

  int ngen;
  float* genpt;
  float* geneta;
  float* genphi;
  int* gensubid;
};

void jetTree::init_memory() {
  rawpt = (float*) malloc(sizeof(float) * 300);
  jtpt = (float*) malloc(sizeof(float) * 300);
  jteta = (float*) malloc(sizeof(float) * 300);
  jtphi = (float*) malloc(sizeof(float) * 300);
  refpt = (float*) malloc(sizeof(float) * 300);
  refeta = (float*) malloc(sizeof(float) * 300);
  refphi = (float*) malloc(sizeof(float) * 300);
  refparton_flavor = (int*) malloc(sizeof(int) * 300);
  subid = (int*) malloc(sizeof(int) * 300);
  chargedMax = (float*) malloc(sizeof(float) * 300);
  chargedSum = (float*) malloc(sizeof(float) * 300);
  chargedN = (int*) malloc(sizeof(int) * 300);
  photonMax = (float*) malloc(sizeof(float) * 300);
  photonSum = (float*) malloc(sizeof(float) * 300);
  photonN = (int*) malloc(sizeof(int) * 300);
  neutralMax = (float*) malloc(sizeof(float) * 300);
  neutralSum = (float*) malloc(sizeof(float) * 300);
  neutralN = (int*) malloc(sizeof(int) * 300);
  eMax = (float*) malloc(sizeof(float) * 300);
  eSum = (float*) malloc(sizeof(float) * 300);
  eN = (int*) malloc(sizeof(int) * 300);
  muMax = (float*) malloc(sizeof(float) * 300);
  muSum = (float*) malloc(sizeof(float) * 300);
  muN = (int*) malloc(sizeof(int) * 300);

  genpt = (float*) malloc(sizeof(float) * 5000);
  geneta = (float*) malloc(sizeof(float) * 5000);
  genphi = (float*) malloc(sizeof(float) * 5000);
  gensubid = (int*) malloc(sizeof(int) * 5000);
}

void jetTree::clear_memory() {
  free(rawpt);
  free(jtpt);
  free(jteta);
  free(jtphi);
  free(refpt);
  free(refeta);
  free(refphi);
  free(refparton_flavor);
  free(subid);
  free(chargedMax);
  free(chargedSum);
  free(chargedN);
  free(photonMax);
  free(photonSum);
  free(photonN);
  free(neutralMax);
  free(neutralSum);
  free(neutralN);
  free(eMax);
  free(eSum);
  free(eN);
  free(muMax);
  free(muSum);
  free(muN);

  free(genpt);
  free(geneta);
  free(genphi);
  free(gensubid);
}

void jetTree::read_tree(TTree* t) {
  init_memory();

  t->SetBranchStatus("nref", 1);
  t->SetBranchStatus("rawpt", 1);
  t->SetBranchStatus("jtpt", 1);
  t->SetBranchStatus("jteta", 1);
  t->SetBranchStatus("jtphi", 1);
  t->SetBranchStatus("refpt", 1);
  t->SetBranchStatus("refeta", 1);
  t->SetBranchStatus("refphi", 1);
  t->SetBranchStatus("refparton_flavor", 1);
  t->SetBranchStatus("subid", 1);
  t->SetBranchStatus("chargedMax", 1);
  t->SetBranchStatus("chargedSum", 1);
  t->SetBranchStatus("chargedN", 1);
  t->SetBranchStatus("photonMax", 1);
  t->SetBranchStatus("photonSum", 1);
  t->SetBranchStatus("photonN", 1);
  t->SetBranchStatus("neutralMax", 1);
  t->SetBranchStatus("neutralSum", 1);
  t->SetBranchStatus("neutralN", 1);
  t->SetBranchStatus("eMax", 1);
  t->SetBranchStatus("eSum", 1);
  t->SetBranchStatus("eN", 1);
  t->SetBranchStatus("muMax", 1);
  t->SetBranchStatus("muSum", 1);
  t->SetBranchStatus("muN", 1);

  t->SetBranchStatus("ngen", 1);
  t->SetBranchStatus("genpt", 1);
  t->SetBranchStatus("geneta", 1);
  t->SetBranchStatus("genphi", 1);
  t->SetBranchStatus("gensubid", 1);

  t->SetBranchAddress("nref", &nref);
  t->SetBranchAddress("rawpt", rawpt);
  t->SetBranchAddress("jtpt", jtpt);
  t->SetBranchAddress("jteta", jteta);
  t->SetBranchAddress("jtphi", jtphi);
  t->SetBranchAddress("refpt", refpt);
  t->SetBranchAddress("refeta", refeta);
  t->SetBranchAddress("refphi", refphi);
  t->SetBranchAddress("refparton_flavor", refparton_flavor);
  t->SetBranchAddress("subid", subid);
  t->SetBranchAddress("chargedMax", chargedMax);
  t->SetBranchAddress("chargedSum", chargedSum);
  t->SetBranchAddress("chargedN", chargedN);
  t->SetBranchAddress("photonMax", photonMax);
  t->SetBranchAddress("photonSum", photonSum);
  t->SetBranchAddress("photonN", photonN);
  t->SetBranchAddress("neutralMax", neutralMax);
  t->SetBranchAddress("neutralSum", neutralSum);
  t->SetBranchAddress("neutralN", neutralN);
  t->SetBranchAddress("eMax", eMax);
  t->SetBranchAddress("eSum", eSum);
  t->SetBranchAddress("eN", eN);
  t->SetBranchAddress("muMax", muMax);
  t->SetBranchAddress("muSum", muSum);
  t->SetBranchAddress("muN", muN);

  t->SetBranchAddress("ngen", &ngen);
  t->SetBranchAddress("genpt", genpt);
  t->SetBranchAddress("geneta", geneta);
  t->SetBranchAddress("genphi", genphi);
  t->SetBranchAddress("gensubid", gensubid);
}

#endif
