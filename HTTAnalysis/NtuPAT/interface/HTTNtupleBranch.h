#ifndef HTTNtupleBranch_H
#define HTTNtupleBranch_H

#include "HTTAnalysis/NtuPAT/interface/HTTNtupleData.h"
#include <string>
#include <vector>

class TBranch;

template <class T>
class HTTNtupleBranch: public virtual HTTNtupleData, public virtual T {

 public:

  HTTNtupleBranch();
  virtual ~HTTNtupleBranch();

  void initTree();

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
  TBranch* b_muoIso;
  TBranch* b_muoClass;

  // electrons
  TBranch* b_nElectrons;
  TBranch* b_elePt;
  TBranch* b_eleEta;
  TBranch* b_elePhi;
  TBranch* b_elePx;
  TBranch* b_elePy;
  TBranch* b_elePz;
  TBranch* b_eleE;
  TBranch* b_eleCharge;
  TBranch* b_eleChaIso;
  TBranch* b_eleNeuIso;
  TBranch* b_elePhoIso;
  TBranch* b_eleAbsEta;
  TBranch* b_eleAEff;
//  TBranch* b_eleLPt;
  TBranch* b_eleID;
  TBranch* b_eleConsCha;
  TBranch* b_eleEBEEGap;
  TBranch* b_eleDb;
  TBranch* b_elIso;
  TBranch* b_elClass;

  // taus
  TBranch* b_nTaus;
  TBranch* b_tauPt;
  TBranch* b_tauEta;
  TBranch* b_tauPhi;
  TBranch* b_tauPx;
  TBranch* b_tauPy;
  TBranch* b_tauPz;
  TBranch* b_tauE;
  TBranch* b_tauCharge;

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

  HTTNtupleBranch( const HTTNtupleBranch& td );
  HTTNtupleBranch& operator=( const HTTNtupleBranch& td );

};

#include "HTTNtupleBranch.icc"

#endif

