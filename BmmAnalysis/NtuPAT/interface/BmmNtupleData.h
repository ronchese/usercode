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

  // hlt
  bool use_hlt;
  int nHLT;
  std::vector<std::string>* hltPath;
  std::vector<bool       >* hltAccept;

  // met
  bool use_met;
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
  std::vector<double>* muoChaIso;     //.chargedHadronIso()
  std::vector<double>* muoNeuIso;     //.neutralHadronIso()
  std::vector<double>* muoPhoIso;     //.photonIso()
  std::vector<double>* muoSumCHpt;    //.pfIsolationR04().sumChargedHadronPt
  std::vector<double>* muoSumCPpt;    //.pfIsolationR04().sumChargedParticlePt
  std::vector<double>* muoSumNHet;    //.pfIsolationR04().sumNeutralHadronEt
  std::vector<double>* muoSumPHet;    //.pfIsolationR04().sumPhotonEt
  std::vector<double>* muoSumPUpt;    //.pfIsolationR04().sumPUPt
  std::vector<double>* muoNumMatches; //.numberOfMatchedStations()
  std::vector<double>* muoDb;         //.dB()
  std::vector<int   >* muoNumValidHits; //. innerTrack()->numberOfValidHits() EMPTY
  std::vector<double>* muoNormChi2;     //.globalTrack()->normalizedChi2()
  std::vector<int   >* muoNumMuHits;    //.globalTrack()->hitPattern().numberOfValidMuonHits()
  std::vector<int   >* muoNumPixHits;   //.globalTrack()->hitPattern().numberOfValidPixelHits()
  std::vector<int   >* muoNumTkHits;    //.globalTrack()->hitPattern().numberOfValidTrackerHits()

  // electrons
  bool use_electrons;
  int nElectrons;
  std::vector<double>* elePt;
  std::vector<double>* eleEta;
  std::vector<double>* elePhi;
  std::vector<double>* elePx;
  std::vector<double>* elePy;
  std::vector<double>* elePz;
  std::vector<double>* eleE;
  std::vector<int   >* eleCharge;
  std::vector<double>* eleChaIso; //.chargedHadronIso()
  std::vector<double>* eleNeuIso; //.neutralHadronIso()
  std::vector<double>* elePhoIso; //.photonIso()
  std::vector<double>* eleAbsEta; //fabs(.superCluster()->eta())
  std::vector<double>* eleAEff;
    //ElectronEffectiveArea::GetElectronEffectiveArea(
    //ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, absEta,
    //ElectronEffectiveArea::kEleEAData2011 )
  std::vector<int   >* eleID;      //.electronID( "eidMediumMC" );
  std::vector<bool  >* eleConsCha; //.isGsfCtfScPixChargeConsistent();
  std::vector<bool  >* eleEBEEGap; //.isEBEEGap();
  std::vector<double>* eleDb;      //.dB();

  // taus
  bool use_taus;
  int nTaus;
  std::vector<double>* tauPt;
  std::vector<double>* tauEta;
  std::vector<double>* tauPhi;
  std::vector<double>* tauPx;
  std::vector<double>* tauPy;
  std::vector<double>* tauPz;
  std::vector<double>* tauE;
  std::vector<int   >* tauCharge;

  // tracks
  bool use_tracks;
  int nTracks;
  std::vector<double>* trkPt;
  std::vector<double>* trkEta;
  std::vector<double>* trkPhi;
  std::vector<double>* trkPx;
  std::vector<double>* trkPy;
  std::vector<double>* trkPz;
  std::vector<double>* trkE;
  std::vector<int   >* trkCharge;
  std::vector<int   >* trkJet;      // jet index
  std::vector<int   >* trkQuality;  //.trackRef()->qualityMask()     EMPTY
  std::vector<double>* trkNormChi2; //.trackRef()->normalizedChi2()  EMPTY
  std::vector<double>* trkDxy;      //.trackRef()->dxy()             EMPTY
  std::vector<double>* trkDz;       //.trackRef()->dz()              EMPTY

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
  std::vector<double>* jetCSV;  //.bDiscriminator( "combinedSecondaryVertexBJetTags" )
  std::vector<double>* jetTCHE; //.bDiscriminator( "trackCountingHighEffBJetTags" )
  std::vector<bool  >* jetPF;   //.isPFJet()
  std::vector<int   >* jetNDau; //.numberOfDaughters()
  std::vector<double>* jetNHF;  //.neutralHadronEnergyFraction()
  std::vector<double>* jetNEF;  //.neutralEmEnergyFraction()
  std::vector<double>* jetCHF;  //.chargedHadronEnergyFraction()
  std::vector<double>* jetCEF;  //.chargedEmEnergyFraction()
  std::vector<double>* jetNCH;  //.chargedMultiplicity()

  // jets
  bool use_vertices;
  int nVertices;

  // gen particles
  bool use_gen;
  int nGenP;
  std::vector<int   >* genId;
  std::vector<int   >* genStatus;
  std::vector<int   >* genMother; // mother index
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

