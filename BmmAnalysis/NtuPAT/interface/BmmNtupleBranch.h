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

 protected:

  // List of branches

  // header
  TBranch* b_runNumber;
  TBranch* b_lumiSection;
  TBranch* b_eventNumber;

  // hlt status
  void setBranches_hlts();
  TBranch* b_nHLTStatus;
  TBranch* b_hltPath;
  TBranch* b_hltRun;
  TBranch* b_hltAccept;

  // hlt objects
  void setBranches_hlto();
  TBranch* b_nHLTObjects;
  TBranch* b_hltObjType;
  TBranch* b_hltPt;
  TBranch* b_hltEta;
  TBranch* b_hltPhi;
  TBranch* b_hltPx;
  TBranch* b_hltPy;
  TBranch* b_hltPz;
  TBranch* b_hltE;

  // beam spot
  void setBranches_bspot();
  TBranch* b_bwX;         // beam width
  TBranch* b_bwY;
  TBranch* b_bwXError;
  TBranch* b_bwYError;
  TBranch* b_bsX;         // beam spot
  TBranch* b_bsY;
  TBranch* b_bsZ;
  TBranch* b_bsXError;
  TBranch* b_bsYError;
  TBranch* b_bsZError;
  TBranch* b_bsdXdZ;      // beam slope
  TBranch* b_bsdYdZ;
  TBranch* b_bsdXdZError;
  TBranch* b_bsdYdZError;

  // met
  void setBranches_met();
  TBranch* b_mEt;
  TBranch* b_mEx;
  TBranch* b_mEy;

  // muons
  void setBranches_muons();
  TBranch* b_nMuons;
  TBranch* b_muoPt;
  TBranch* b_muoEta;
  TBranch* b_muoPhi;
  TBranch* b_muoPx;
  TBranch* b_muoPy;
  TBranch* b_muoPz;
  TBranch* b_muoE;
  TBranch* b_muoCharge;
  TBranch* b_muoTrk;
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
  void setBranches_electrons();
  TBranch* b_nElectrons;
  TBranch* b_elePt;
  TBranch* b_eleEta;
  TBranch* b_elePhi;
  TBranch* b_elePx;
  TBranch* b_elePy;
  TBranch* b_elePz;
  TBranch* b_eleE;
  TBranch* b_eleCharge;
  TBranch* b_eleTrk;
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
  void setBranches_taus();
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
  void setBranches_jets();
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

  // particle flow
  void setBranches_pflow();
  TBranch* b_nPF;
  TBranch* b_pfcPt;
  TBranch* b_pfcEta;
  TBranch* b_pfcPhi;
  TBranch* b_pfcPx;
  TBranch* b_pfcPy;
  TBranch* b_pfcPz;
  TBranch* b_pfcE;
  TBranch* b_pfcCharge;
  TBranch* b_pfcJet;
  TBranch* b_pfcTrk;

  // tracks
  void setBranches_tracks();
  TBranch* b_nTracks;
  TBranch* b_trkPt;
  TBranch* b_trkEta;
  TBranch* b_trkPhi;
  TBranch* b_trkPx;
  TBranch* b_trkPy;
  TBranch* b_trkPz;
  TBranch* b_trkCharge;
  TBranch* b_trkPFC;
  TBranch* b_trkPVtx;
  TBranch* b_trkSVtx;
  TBranch* b_trkQuality;
  TBranch* b_trkNormChi2;
  TBranch* b_trkDxy;
  TBranch* b_trkDz;

  // primary vertices
  void setBranches_pVertices();
  TBranch* b_nPVertices;
  TBranch* b_pvtX;
  TBranch* b_pvtY;
  TBranch* b_pvtZ;
  TBranch* b_pvtSxx;
  TBranch* b_pvtSyy;
  TBranch* b_pvtSzz;
  TBranch* b_pvtSxy;
  TBranch* b_pvtSxz;
  TBranch* b_pvtSyz;
//  TBranch* b_pvtCovariance;
  TBranch* b_pvtNormChi2;
  TBranch* b_pvtBadQuality;

  // secondary vertices
  void setBranches_sVertices();
  TBranch* b_nSVertices;
  TBranch* b_svtX;
  TBranch* b_svtY;
  TBranch* b_svtZ;
  TBranch* b_svtSxx;
  TBranch* b_svtSyy;
  TBranch* b_svtSzz;
  TBranch* b_svtSxy;
  TBranch* b_svtSxz;
  TBranch* b_svtSyz;
  TBranch* b_svtDirX;
  TBranch* b_svtDirY;
  TBranch* b_svtDirZ;
  TBranch* b_svtNormChi2;
  TBranch* b_svtMass;
  TBranch* b_svtDist2D;
  TBranch* b_svtSign2D;
  TBranch* b_svtDist3D;
  TBranch* b_svtSign3D;
  TBranch* b_svtJet;
  TBranch* b_svtNTracks;
  TBranch* b_svtBadQuality;

  // gen particles
  void setBranches_gen();
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

