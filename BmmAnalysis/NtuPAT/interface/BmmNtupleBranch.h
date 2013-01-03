#ifndef BmmNtupleBranch_H
#define BmmNtupleBranch_H

#include "BmmAnalysis/NtuPAT/interface/BmmNtupleData.h"
#include <string>
#include <vector>

class TBranch;

template <class T>
class BmmNtupleBranch: public virtual BmmNtupleData, public virtual T {

 public:

  BmmNtupleBranch();
  virtual ~BmmNtupleBranch();

  void initTree();

  void setBranches_mEt();
  void setBranches_muons();
  void setBranches_jets();
  void setBranches_gen();

 protected:

  // List of branches

  // header
  TBranch* b_runNumber;
  TBranch* b_lumiSection;
  TBranch* b_eventNumber;

  // mEt
  TBranch* b_mEt;
  TBranch* b_mEx;
  TBranch* b_mEy;

  // muons
  TBranch* b_nMuons;
  TBranch* b_muoPt;
  TBranch* b_muoEta;
  TBranch* b_muoPhi;
  TBranch* b_muoPx;
  TBranch* b_muoPy;
  TBranch* b_muoPz;
  TBranch* b_muoE;
  TBranch* b_muoCharge;
  TBranch* b_muoChaIso;
  TBranch* b_muoNeuIso;
  TBranch* b_muoPhoIso;
  TBranch* b_muoSumCHpt;
  TBranch* b_muoSumCPpt;
  TBranch* b_muoSumNHet;
  TBranch* b_muoSumPHet;
  TBranch* b_muoSumPUpt;
  TBranch* b_muoNumMatches;
  TBranch* b_muoDb;
  TBranch* b_muoNumValidHits;
  TBranch* b_muoNormChi2;
  TBranch* b_muoNumMuHits;
  TBranch* b_muoNumPixHits;
  TBranch* b_muoNumTkHits;

  // jets
  TBranch* b_nJets;
  TBranch* b_jetPt;
  TBranch* b_jetEta;
  TBranch* b_jetPhi;
  TBranch* b_jetPx;
  TBranch* b_jetPy;
  TBranch* b_jetPz;
  TBranch* b_jetE;
  TBranch* b_jetCSV;
  TBranch* b_jetTCHE;
  TBranch* b_jetPF;
  TBranch* b_jetNDau;
  TBranch* b_jetNHF;
  TBranch* b_jetNEF;
  TBranch* b_jetCHF;
  TBranch* b_jetCEF;
  TBranch* b_jetNCH;

  // gen particles
  TBranch* b_nGenP;
  TBranch* b_genId;
  TBranch* b_genStatus;
  TBranch* b_genMother;
  TBranch* b_genPt;
  TBranch* b_genEta;
  TBranch* b_genPhi;
  TBranch* b_genPx;
  TBranch* b_genPy;
  TBranch* b_genPz;
  TBranch* b_genE;
  TBranch* b_genCharge;
  TBranch* b_genMass;

 private:

  BmmNtupleBranch( const BmmNtupleBranch& td );
  BmmNtupleBranch& operator=( const BmmNtupleBranch& td );

};

#include "BmmNtupleBranch.icc"

#endif

