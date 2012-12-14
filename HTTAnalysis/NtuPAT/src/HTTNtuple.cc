#include <iostream>

#include "HTTAnalysis/NtuPAT/interface/HTTNtuple.h"

HTTNtuple::HTTNtuple() {
  // "treeName" must be assigned the name chosen by the user for the tree
  // the TTree object is created by the utility
  treeName = "hTTtree";
  initTree();
}


HTTNtuple::~HTTNtuple() {
}


void HTTNtuple::reset() {
  // calling "autoReset" all variables and vectors are automatically reset
  autoReset();
  return;
}


