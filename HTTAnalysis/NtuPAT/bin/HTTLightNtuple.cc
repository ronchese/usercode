#include <iostream>

#include "HTTLightNtuple.h"

HTTLightNtuple::HTTLightNtuple() {
  treeName = "hTTtree";
}


HTTLightNtuple::~HTTLightNtuple() {
}

void HTTLightNtuple::initTree( TTree* tree ) {
  currentTree = tree;
  HTTNtupleBranch<TreeLightReader>::initTree();
  return;
}

/*
void HTTLightNtuple::reset() {

// ...reset all variables...
  return;

}
*/


