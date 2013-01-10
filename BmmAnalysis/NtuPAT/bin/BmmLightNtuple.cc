#include <iostream>

#include "BmmLightNtuple.h"

BmmLightNtuple::BmmLightNtuple() {
  currentTree = 0;
  treeName = "Bmmtree";
}


BmmLightNtuple::~BmmLightNtuple() {
}


//void BmmLightNtuple::initTree() {
//  BmmNtupleBranch<TreeLightReader>::initTree();
//}


void BmmLightNtuple::openTree( TTree* tree ) {
  currentTree = tree;
  initTree();
  return;
}

/*
void BmmLightNtuple::reset() {

// ...reset all variables...
  return;

}
*/


