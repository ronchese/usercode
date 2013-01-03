#include "BmmAnalysis/NtuPAT/interface/BmmPATToNtuple.h"
#include "TFile.h"
#include "TROOT.h"

//#include "FWCore/Common/interface/TriggerNames.h"
//#include "DataFormats/Common/interface/TriggerResults.h"
//#include "DataFormats/HLTReco/interface/TriggerObject.h"
//#include "DataFormats/HLTReco/interface/TriggerEvent.h"
//#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

/*
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"

#include "DataFormats/PatCandidates/interface/Tau.h"
*/

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <map>


using edm::TriggerResults;
using pat::MET;
using pat::Muon;
//using pat::Electron; 
//using pat::Tau;
using pat::Jet;
using reco::GenParticle;

using namespace std;

BmmPATToNtuple::BmmPATToNtuple( const edm::ParameterSet& ps ) {
  ntuName = ps.getUntrackedParameter<std::string>( "ntuName" );
  labelHLT       = ps.getParameter<std::string>( "labelHLT"       );
  labelMets      = ps.getParameter<std::string>( "labelMets"      );
  labelMuons     = ps.getParameter<std::string>( "labelMuons"     );
//  labelElectrons = ps.getParameter<std::string>( "labelElectrons" );
//  labelTaus      = ps.getParameter<std::string>( "labelTaus"      );
  labelJets      = ps.getParameter<std::string>( "labelJets"      );
  labelGen       = ps.getParameter<std::string>( "labelGen"       );
  setUserParameter( "verbose",
                    ps.getUntrackedParameter<std::string>( "verbose" ) );
}


BmmPATToNtuple::~BmmPATToNtuple() {
}


void BmmPATToNtuple::beginJob() {
//  cout << "BmmPATToNtuple::beginJob()" << endl;
  TDirectory* current = gDirectory;
  gROOT->cd();
  BmmAnalyzer::beginJob();
  openNtuple( ntuName );
  gROOT->cd();
  book();
  current->cd();
  return;
}


void BmmPATToNtuple::openNtuple( const std::string& name ) {
  TDirectory* current = gDirectory;
  file = new TFile( name.c_str(), "CREATE" );
  initWrite( file );
  current->cd();
  return;
}


void BmmPATToNtuple::read( const edm::EventBase& ev ) {

  const char* verbFlag = getUserParameter( "verbose" ).c_str();
  bool verbose = ( ( *verbFlag == 't' ) || ( *verbFlag == 'T' ) );
  if ( verbose ) {
    cout << "event "
         << ev.id().run() << " / "
         << ev.id().event() << endl;
  }

  // function provided by the tool to automatically reset all variables
  autoReset();

  // store event id
  runNumber   = ev.id().run();
  lumiSection = ev.id().luminosityBlock();
  eventNumber = ev.id().event();

  // get handles

//  ev.getByLabel( labelHLT      , hlt       );
  ev.getByLabel( labelMets     , mets      );
  ev.getByLabel( labelMuons    , muons     );
//  ev.getByLabel( labelElectrons, electrons );
//  ev.getByLabel( labelTaus     , taus      );
  ev.getByLabel( labelJets     , jets      );
  ev.getByLabel( labelGen      , particles );

//  if ( hlt      .isValid() ) { fillTrigger     (); }
//  else                       { cout << "invalid hlt"       << endl;         }
  if ( use_mEt ) {
  if ( mets     .isValid() ) { fillMet         (); }
  else                       { cout << "invalid mets"      << endl; return; }
  }
  nMuons = 0;
  if ( use_muons ) {
  if ( muons    .isValid() ) { fillMuons       (); }
  else                       { cout << "invalid muons"     << endl; return; }
  }
/*
  if ( electrons.isValid() ) { fillElectrons   (); }
  else                       { cout << "invalid electrons" << endl; return; }
  if ( taus     .isValid() ) { fillTaus        (); }
  else                       { cout << "invalid taus"      << endl; return; }
*/
  if ( use_jets ) {
  if ( jets     .isValid() ) { fillJets        (); }
  else                       { cout << "invalid jets"      << endl; return; }
  }
  if ( use_gen ) {
  if ( particles.isValid() ) { fillGenParticles(); }
//  else                       { cout << "invalid particles" << endl;         }
  }
  // function provided by the tool to actually fill the tree
//  cout << "fill" << endl;
  fill();

  return;

}


void BmmPATToNtuple::closeNtuple() {
  close();
  file->Close();
  return;
}


void BmmPATToNtuple::endJob() {
  BmmAnalyzer::endJob();
  closeNtuple();
  return;
}


void BmmPATToNtuple::fillTrigger() {
  return;
}


void BmmPATToNtuple::fillMet() {

  // store mEt info

  mEt = mets->at( 0 ).pt();
  mEx = mets->at( 0 ).px();
  mEy = mets->at( 0 ).py();

  return;

}



void BmmPATToNtuple::fillMuons() {

  // store muons info

  int iObj;
  int nObj = muons->size();
  muoPt          ->resize( nObj );
  muoEta         ->resize( nObj );
  muoPhi         ->resize( nObj );
  muoPx          ->resize( nObj );
  muoPy          ->resize( nObj );
  muoPz          ->resize( nObj );
  muoE           ->resize( nObj );
  muoCharge      ->resize( nObj );
  muoChaIso      ->resize( nObj );
  muoNeuIso      ->resize( nObj );
  muoPhoIso      ->resize( nObj );
  muoSumCHpt     ->resize( nObj );
  muoSumCPpt     ->resize( nObj );
  muoSumNHet     ->resize( nObj );
  muoSumPHet     ->resize( nObj );
  muoSumPUpt     ->resize( nObj );
  muoNumMatches  ->resize( nObj );
  muoDb          ->resize( nObj, 0.0 );
  muoNumValidHits->resize( nObj, 0.0 );
  muoNormChi2    ->resize( nObj, 0.0 );
  muoNumMuHits   ->resize( nObj, 0.0 );
  muoNumPixHits  ->resize( nObj, 0.0 );
  muoNumTkHits   ->resize( nObj, 0.0 );

  std::vector<const Muon*> muonPtr;
  muonPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    muonPtr[iObj] = &( muons->at( iObj ) );
  }

  compareByPt<Muon> muoComp;
  sort( muonPtr.begin(), muonPtr.end(), muoComp );

  nMuons = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Muon& muon = *muonPtr[iObj];

    const reco::Candidate::LorentzVector p4 = muon.p4();
    muoPt          ->at( iObj ) = p4.pt    ();
    muoEta         ->at( iObj ) = p4.eta   ();
    muoPhi         ->at( iObj ) = p4.phi   ();
    muoPx          ->at( iObj ) = p4.px    ();
    muoPy          ->at( iObj ) = p4.py    ();
    muoPz          ->at( iObj ) = p4.pz    ();
    muoE           ->at( iObj ) = p4.energy();
    muoCharge      ->at( iObj ) = muon.charge();

    muoChaIso      ->at( iObj ) = muon.chargedHadronIso();
    muoNeuIso      ->at( iObj ) = muon.neutralHadronIso();
    muoPhoIso      ->at( iObj ) = muon.photonIso();
    const reco::MuonPFIsolation& pfIsolationR04 = muon.pfIsolationR04();
    muoSumCHpt     ->at( iObj ) = pfIsolationR04.sumChargedHadronPt;
    muoSumCPpt     ->at( iObj ) = pfIsolationR04.sumChargedParticlePt;
    muoSumNHet     ->at( iObj ) = pfIsolationR04.sumNeutralHadronEt;
    muoSumPHet     ->at( iObj ) = pfIsolationR04.sumPhotonEt;
    muoSumPUpt     ->at( iObj ) = pfIsolationR04.sumPUPt;

    if ( !( muon. isGlobalMuon() ) ) continue;
    if ( !( muon.isTrackerMuon() ) ) continue;
    const reco::TrackRef&  innerTrack = muon. innerTrack();
    const reco::TrackRef& globalTrack = muon.globalTrack();
    const reco::HitPattern& hitPattern = globalTrack->hitPattern();
    muoNumMatches  ->at( iObj ) = muon.numberOfMatchedStations();
    muoDb          ->at( iObj ) = muon.dB();
    muoNumValidHits->at( iObj ) =  innerTrack->numberOfValidHits();
    muoNormChi2    ->at( iObj ) = globalTrack->normalizedChi2();
    muoNumMuHits   ->at( iObj ) = hitPattern.numberOfValidMuonHits();
    muoNumPixHits  ->at( iObj ) = hitPattern.numberOfValidPixelHits();
    muoNumTkHits   ->at( iObj ) = hitPattern.numberOfValidTrackerHits();

  }

  return;

}


/*
void BmmPATToNtuple::fillElectrons() {

  // store electrons info

  int iObj;
  int nObj = electrons->size();
  elePt     ->resize( nObj );
  eleEta    ->resize( nObj );
  elePhi    ->resize( nObj );
  elePx     ->resize( nObj );
  elePy     ->resize( nObj );
  elePz     ->resize( nObj );
  eleE      ->resize( nObj );
  eleCharge ->resize( nObj );
  eleChaIso ->resize( nObj );
  eleNeuIso ->resize( nObj );
  elePhoIso ->resize( nObj );
  eleAbsEta ->resize( nObj );
  eleAEff   ->resize( nObj );
//  eleLPt    ->resize( nObj );
  eleID     ->resize( nObj );
  eleConsCha->resize( nObj );
  eleEBEEGap->resize( nObj );
  eleDb     ->resize( nObj );
  eleIso    ->resize( nObj );
  eleClass  ->resize( nObj );

  std::vector<const Electron*> electronPtr;
  electronPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    electronPtr[iObj] = &( electrons->at( iObj ) );
  }

  compareByPt<Electron> eleComp;
  sort( electronPtr.begin(), electronPtr.end(), eleComp );

  nElectrons = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Electron& electron = *electronPtr[iObj];

    const reco::Candidate::LorentzVector p4 = electron.p4();
    elePt     ->at( iObj ) = p4.pt    ();
    eleEta    ->at( iObj ) = p4.eta   ();
    elePhi    ->at( iObj ) = p4.phi   ();
    elePx     ->at( iObj ) = p4.px    ();
    elePy     ->at( iObj ) = p4.py    ();
    elePz     ->at( iObj ) = p4.pz    ();
    eleE      ->at( iObj ) = p4.energy();
    eleCharge ->at( iObj ) = electron.charge();

    eleChaIso ->at( iObj ) = electron.chargedHadronIso();
    eleNeuIso ->at( iObj ) = electron.neutralHadronIso();
    elePhoIso ->at( iObj ) = electron.photonIso();
    double absEta =
    eleAbsEta ->at( iObj ) = fabs( electron.superCluster()->eta() );
    eleAEff   ->at( iObj ) = 
      ElectronEffectiveArea::GetElectronEffectiveArea(
      ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, absEta,
      ElectronEffectiveArea::kEleEAData2011 );
//    eleLPt    ->at( iObj ) = electron.pt();

    eleID     ->at( iObj ) = electron.electronID( "eidMediumMC" );
    eleConsCha->at( iObj ) = electron.isGsfCtfScPixChargeConsistent();
    eleEBEEGap->at( iObj ) = electron.isEBEEGap();
    eleDb     ->at( iObj ) = electron.dB();

  }

  return;

}



void BmmPATToNtuple::fillTaus() {

  // store taus info

  int iObj;
  int nObj = taus->size();
  tauPt    ->resize( nObj );
  tauEta   ->resize( nObj );
  tauPhi   ->resize( nObj );
  tauPx    ->resize( nObj );
  tauPy    ->resize( nObj );
  tauPz    ->resize( nObj );
  tauE     ->resize( nObj );
  tauCharge->resize( nObj );

  std::vector<const Tau*> tauPtr;
  tauPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    tauPtr[iObj] = &( taus->at( iObj ) );
  }

  compareByPt<Tau> tauComp;
  sort( tauPtr.begin(), tauPtr.end(), tauComp );

  nTaus = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Tau& tau = *tauPtr[iObj];

    const reco::Candidate::LorentzVector p4 = tau.p4();
    tauPt    ->at( iObj ) = p4.pt    ();
    tauEta   ->at( iObj ) = p4.eta   ();
    tauPhi   ->at( iObj ) = p4.phi   ();
    tauPx    ->at( iObj ) = p4.px    ();
    tauPy    ->at( iObj ) = p4.py    ();
    tauPz    ->at( iObj ) = p4.pz    ();
    tauE     ->at( iObj ) = p4.energy();
    tauCharge->at( iObj ) = tau.charge();

  }

  return;

}
*/

void BmmPATToNtuple::fillJets() {

  // store jets info

  int iObj;
  int nObj = jets->size();
  jetPt  ->resize( nObj );
  jetEta ->resize( nObj );
  jetPhi ->resize( nObj );
  jetPx  ->resize( nObj );
  jetPy  ->resize( nObj );
  jetPz  ->resize( nObj );
  jetE   ->resize( nObj );
  jetCSV ->resize( nObj );
  jetTCHE->resize( nObj );
  jetPF  ->resize( nObj );
  jetNDau->resize( nObj );
  jetNHF ->resize( nObj );
  jetNEF ->resize( nObj );
  jetCHF ->resize( nObj );
  jetCEF ->resize( nObj );
  jetNCH ->resize( nObj );

  std::vector<const Jet*> jetPtr;
  jetPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; iObj++ ) {
    jetPtr[iObj] = &( jets->at( iObj ) );
  }

  compareByPt<Jet> jetComp;
  sort( jetPtr.begin(), jetPtr.end(), jetComp );

  labelCSV  = "combinedSecondaryVertexBJetTags";
  labelTCHE = "trackCountingHighEffBJetTags";
  nJets = nObj;
  for ( iObj = 0; iObj < nObj; iObj++ ) {

    const Jet& jet = *jetPtr[iObj];

    jetPt  ->at( iObj ) = jet.pt    ();
    jetEta ->at( iObj ) = jet.eta   ();
    jetPhi ->at( iObj ) = jet.phi   ();
    jetPx  ->at( iObj ) = jet.px    ();
    jetPy  ->at( iObj ) = jet.py    ();
    jetPz  ->at( iObj ) = jet.pz    ();
    jetE   ->at( iObj ) = jet.energy();
    jetCSV ->at( iObj ) = jet.bDiscriminator( labelCSV  );
    jetTCHE->at( iObj ) = jet.bDiscriminator( labelTCHE );
    jetPF  ->at( iObj ) = jet.isPFJet();
    jetNDau->at( iObj ) = jet.numberOfDaughters();
    jetNHF ->at( iObj ) = jet.neutralHadronEnergyFraction();
    jetNEF ->at( iObj ) = jet.neutralEmEnergyFraction();
    jetCHF ->at( iObj ) = jet.chargedHadronEnergyFraction();
    jetCEF ->at( iObj ) = jet.chargedEmEnergyFraction();
    jetNCH ->at( iObj ) = jet.chargedMultiplicity();

  }

  return;

}



void BmmPATToNtuple::fillGenParticles() {

  // store gen particles info

  int iObj;
  int nObj = particles->size();
  genId    ->resize( nObj );
  genStatus->resize( nObj );
  genMother->resize( nObj );
  genPt    ->resize( nObj );
  genEta   ->resize( nObj );
  genPhi   ->resize( nObj );
  genPx    ->resize( nObj );
  genPy    ->resize( nObj );
  genPz    ->resize( nObj );
  genE     ->resize( nObj );
  genCharge->resize( nObj );
  genMass  ->resize( nObj );

  map<const reco::Candidate*,int> genMap;
  nGenP = nObj;
  for ( iObj = 0; iObj < nObj; iObj++ ) {

    const GenParticle& gen = particles->at( iObj );
    genMap.insert( make_pair( &gen, iObj ) );

    genId    ->at( iObj ) = gen.pdgId();
    genStatus->at( iObj ) = gen.status();
    genMother->at( iObj ) = -1;//gen.mother();
    genPt    ->at( iObj ) = gen.pt    ();
    genEta   ->at( iObj ) = gen.eta   ();
    genPhi   ->at( iObj ) = gen.phi   ();
    genPx    ->at( iObj ) = gen.px    ();
    genPy    ->at( iObj ) = gen.py    ();
    genPz    ->at( iObj ) = gen.pz    ();
    genE     ->at( iObj ) = gen.energy();
    genCharge->at( iObj ) = gen.charge();
    genMass  ->at( iObj ) = gen.mass  ();

  }

  for ( iObj = 0; iObj < nObj; iObj++ ) {
    const GenParticle& gen = particles->at( iObj );
    map<const reco::Candidate*,int>::const_iterator iter = genMap.find(
                                                           gen.mother() );
    map<const reco::Candidate*,int>::const_iterator iend = genMap.end();
    if ( iter != iend ) genMother->at( iObj ) = iter->second;
//    cout << "gen particle: " << iObj << " "
//                             << &(particles->at( iObj )) << " "
//                             << &gen << " " << genMother->at( iObj ) << " "
//                             << gen.mother() << endl;
  }

  return;

}


