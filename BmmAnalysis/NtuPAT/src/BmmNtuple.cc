#include <iostream>

#include "BmmAnalysis/NtuPAT/interface/BmmNtuple.h"

BmmNtuple::BmmNtuple() {
  // "treeName" must be assigned the name chosen by the user for the tree
  // the TTree object is created by the utility
  treeName = "Bmmtree";
  use_mEt   = true;
  use_muons = true;
  use_jets  = true;
  use_gen   = true;
  initTree();
}


BmmNtuple::~BmmNtuple() {
}


void BmmNtuple::reset() {
  // calling "autoReset" all variables and vectors are automatically reset
  autoReset();
  return;
}


