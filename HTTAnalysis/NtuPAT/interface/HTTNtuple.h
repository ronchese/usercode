#ifndef HTTNtuple_H
#define HTTNtuple_H

#include "NtuTool/Common/interface/TreeWrapper.h"
#include "HTTAnalysis/NtuPAT/interface/HTTNtupleBranch.h"
#include <string>
#include <vector>

// The class with the tree definition must inherit from "TreeWrapper"

class HTTNtuple: public virtual HTTNtupleBranch<TreeWrapper>,
                 public virtual TreeWrapper {

 public:

  HTTNtuple();
  virtual ~HTTNtuple();
  virtual void reset();

 private:

  HTTNtuple( const HTTNtuple& td );
  HTTNtuple& operator=( const HTTNtuple& td );

};

#endif

