#ifndef HTTLightNtuple_H
#define HTTLightNtuple_H

#include "HTTAnalysis/NtuPAT/interface/HTTNtupleBranch.h"
#include "TreeLightReader.h"
#include <string>
#include <vector>

// The class with the tree definition must inherit from "TreeLightReader"

class HTTLightNtuple: public virtual HTTNtupleBranch<TreeLightReader>,
                      public virtual TreeLightReader {

 public:

  HTTLightNtuple();
  virtual ~HTTLightNtuple();

  void initTree( TTree* tree );
//  virtual void reset();

 private:

  HTTLightNtuple( const HTTLightNtuple& td );
  HTTLightNtuple& operator=( const HTTLightNtuple& td );

};

#endif

