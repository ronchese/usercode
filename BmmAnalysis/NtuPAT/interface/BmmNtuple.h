#ifndef BmmNtuple_H
#define BmmNtuple_H

#include "NtuTool/Common/interface/TreeWrapper.h"
#include "BmmAnalysis/NtuPAT/interface/BmmNtupleBranch.h"
#include "BmmAnalysis/NtuPAT/interface/BmmUtil.h"
#include <string>
#include <vector>

// The class with the tree definition must inherit from "TreeWrapper"

class BmmNtuple: public virtual BmmNtupleBranch<TreeWrapper>,
                 public BmmUtil,
                 public virtual TreeWrapper {

 public:

  BmmNtuple();
  virtual ~BmmNtuple();
  virtual void reset();

 private:

  BmmNtuple( const BmmNtuple& td );
  BmmNtuple& operator=( const BmmNtuple& td );

};

#endif

