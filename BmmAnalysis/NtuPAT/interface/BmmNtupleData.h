#ifndef BmmNtupleData_H
#define BmmNtupleData_H

#include <string>
#include <vector>

class BmmNtupleData {

 public:

  BmmNtupleData();
  virtual ~BmmNtupleData();

 protected:

  // Declaration of leaf types

  // header
  unsigned int runNumber;
  unsigned int lumiSection;
  unsigned int eventNumber;

  // HLT

  // mEt
  bool use_mEt;
  double mEt;
  double mEx;
  double mEy;

  // muons
  bool use_muons;
  int nMuons;
  std::vector<double>* muoPt;
  std::vector<double>* muoEta;
  std::vector<double>* muoPhi;
  std::vector<double>* muoPx;
  std::vector<double>* muoPy;
  std::vector<double>* muoPz;
  std::vector<double>* muoE;
  std::vector<int   >* muoCharge;
  std::vector<double>* muoChaIso;
  std::vector<double>* muoNeuIso;
  std::vector<double>* muoPhoIso;
  std::vector<double>* muoSumCHpt;
  std::vector<double>* muoSumCPpt;
  std::vector<double>* muoSumNHet;
  std::vector<double>* muoSumPHet;
  std::vector<double>* muoSumPUpt;
  std::vector<double>* muoNumMatches;
  std::vector<double>* muoDb;
  std::vector<double>* muoNumValidHits;
  std::vector<double>* muoNormChi2;
  std::vector<double>* muoNumMuHits;
  std::vector<double>* muoNumPixHits;
  std::vector<double>* muoNumTkHits;

  // jets
  bool use_jets;
  int nJets;
  std::vector<double>* jetPt;
  std::vector<double>* jetEta;
  std::vector<double>* jetPhi;
  std::vector<double>* jetPx;
  std::vector<double>* jetPy;
  std::vector<double>* jetPz;
  std::vector<double>* jetE;
  std::vector<double>* jetCSV;
  std::vector<double>* jetTCHE;
  std::vector<bool  >* jetPF;
  std::vector<int   >* jetNDau;
  std::vector<double>* jetNHF;
  std::vector<double>* jetNEF;
  std::vector<double>* jetCHF;
  std::vector<double>* jetCEF;
  std::vector<double>* jetNCH;

  // gen particles
  bool use_gen;
  int nGenP;
  std::vector<int   >* genId;
  std::vector<int   >* genStatus;
  std::vector<int   >* genMother;
  std::vector<double>* genPt;
  std::vector<double>* genEta;
  std::vector<double>* genPhi;
  std::vector<double>* genPx;
  std::vector<double>* genPy;
  std::vector<double>* genPz;
  std::vector<double>* genE;
  std::vector<int   >* genCharge;
  std::vector<double>* genMass;

 private:

  BmmNtupleData( const BmmNtupleData& td );
  BmmNtupleData& operator=( const BmmNtupleData& td );

};

#endif

