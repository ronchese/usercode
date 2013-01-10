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

  void setBranches_hlt();
  void setBranches_met();
  void setBranches_muons();
  void setBranches_electrons();
  void setBranches_taus();
  void setBranches_tracks();
  void setBranches_jets();
  void setBranches_gen();

 protected:

  // List of branches

  // header
  TBranch* b_runNumber;
  TBranch* b_lumiSection;
  TBranch* b_eventNumber;

  // hlt
  TBranch* b_nHLT;
  TBranch* b_hltPath;
  TBranch* b_hltAccept;

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
  TBranch* b_eleID;
  TBranch* b_eleConsCha;
  TBranch* b_eleEBEEGap;
  TBranch* b_eleDb;

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

  // tracks
  TBranch* b_nTracks;
  TBranch* b_trkPt;
  TBranch* b_trkEta;
  TBranch* b_trkPhi;
  TBranch* b_trkPx;
  TBranch* b_trkPy;
  TBranch* b_trkPz;
  TBranch* b_trkE;
  TBranch* b_trkCharge;
  TBranch* b_trkJet;
  TBranch* b_trkQuality;
  TBranch* b_trkNormChi2;
  TBranch* b_trkDxy;
  TBranch* b_trkDz;

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

