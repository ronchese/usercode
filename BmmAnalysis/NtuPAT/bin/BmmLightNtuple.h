#ifndef BmmLightNtuple_H
#define BmmLightNtuple_H

#include "BmmAnalysis/NtuPAT/interface/BmmNtupleBranch.h"
#include "TreeLightReader.h"
#include <string>
#include <vector>

// The class with the tree definition must inherit from "TreeLightReader"

class BmmLightNtuple: public virtual BmmNtupleBranch<TreeLightReader>,
                      public virtual TreeLightReader {

 public:

  BmmLightNtuple();
  virtual ~BmmLightNtuple();

//  void initTree();
  void openTree( TTree* tree );
//  virtual void reset();

 private:

  BmmLightNtuple( const BmmLightNtuple& td );
  BmmLightNtuple& operator=( const BmmLightNtuple& td );

};

#endif

