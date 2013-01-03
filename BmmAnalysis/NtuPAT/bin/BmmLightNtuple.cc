#include <iostream>

#include "BmmLightNtuple.h"

BmmLightNtuple::BmmLightNtuple() {
  treeName = "Bmmtree";
}


BmmLightNtuple::~BmmLightNtuple() {
}

void BmmLightNtuple::initTree( TTree* tree ) {
  currentTree = tree;
  BmmNtupleBranch<TreeLightReader>::initTree();
  return;
}

/*
void BmmLightNtuple::reset() {

// ...reset all variables...
  return;

}
*/


