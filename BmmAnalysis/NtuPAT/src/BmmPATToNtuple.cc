#include "BmmAnalysis/NtuPAT/interface/BmmPATToNtuple.h"
#include "TFile.h"
#include "TROOT.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
//#include "DataFormats/HLTReco/interface/TriggerObject.h"
//#include "DataFormats/HLTReco/interface/TriggerEvent.h"
//#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"

#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

//#include "DataFormats/PatCandidates/interface/PFParticle.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
//#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"

#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

//#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <map>


using edm::TriggerResults;
using pat::MET;
using pat::Muon;
using pat::Electron;
using pat::Tau;
using pat::Jet;
//using pat::PFParticle;
using reco::Candidate;
using reco::PFCandidate;
using reco::PFCandidatePtr;
using reco::Track;
using reco::TrackRef;
using reco::TrackBaseRef;
using reco::HitPattern;
using reco::Vertex;
using reco::SecondaryVertexTagInfo;
using reco::GenParticle;

using namespace std;

BmmPATToNtuple::BmmPATToNtuple( const edm::ParameterSet& ps ) {

  parameterSet = &ps;
  ntuName = ps.getUntrackedParameter<string>( "ntuName" );
  dumpNtuple = ( ntuName != "" );

  setUserParameter( "labelTrigResults"   , ps.getParameter<string>(
                    "labelTrigResults"    ) );
  setUserParameter( "use_hlts"     ,
  getUserParameter( "labelTrigResults" )   == "" ? "f" : "t" );

  setUserParameter( "labelTrigEvent"     , ps.getParameter<string>(
                    "labelTrigEvent"      ) );
  setUserParameter( "use_hlto"     , 
  getUserParameter( "labelTrigEvent" )     == "" ? "f" : "t" );

  setUserParameter( "labelBeamSpot"      , ps.getParameter<string>(
                    "labelBeamSpot"       ) );
  setUserParameter( "use_bspot"    , 
  getUserParameter( "labelBeamSpot" )      == "" ? "f" : "t" );

  setUserParameter( "labelMets"          , ps.getParameter<string>(
                    "labelMets"           ) );
  setUserParameter( "use_met"      , 
  getUserParameter( "labelMets" )          == "" ? "f" : "t" );

  setUserParameter( "labelMuons"         , ps.getParameter<string>(
                    "labelMuons"          ) );
  setUserParameter( "use_muons"    , 
  getUserParameter( "labelMuons" )         == "" ? "f" : "t" );

  setUserParameter( "labelElectrons"     , ps.getParameter<string>(
                    "labelElectrons"      ) );
  setUserParameter( "use_electrons", 
  getUserParameter( "labelElectrons" )     == "" ? "f" : "t" );

  setUserParameter( "labelTaus"          , ps.getParameter<string>(
                    "labelTaus"           ) );
  setUserParameter( "use_taus"     , 
  getUserParameter( "labelTaus" )          == "" ? "f" : "t" );

  setUserParameter( "labelJets"          , ps.getParameter<string>(
                    "labelJets"           ) );
  setUserParameter( "use_jets"     , 
  getUserParameter( "labelJets" )          == "" ? "f" : "t" );

  setUserParameter( "labelPFCandidates"  , ps.getParameter<string>(
                    "labelPFCandidates"   ) );
  setUserParameter( "use_pflow"    , 
  getUserParameter( "labelPFCandidates" )  == "" ? "f" : "t" );

  setUserParameter( "labelGeneralTracks" , ps.getParameter<string>(
                    "labelGeneralTracks"  ) );
  setUserParameter( "use_tracks"   , 
  getUserParameter( "labelGeneralTracks" ) == "" ? "f" : "t" );

  setUserParameter( "labelPVertices"     , ps.getParameter<string>(
                    "labelPVertices"      ) );
  setUserParameter( "use_pvts"     , 
  getUserParameter( "labelPVertices" )     == "" ? "f" : "t" );

  setUserParameter( "labelSVertices"     , ps.getParameter<string>(
                    "labelSVertices"      ) );
  setUserParameter( "use_svts"     , 
  getUserParameter( "labelSVertices" )     == "" ? "f" : "t" );

  setUserParameter( "labelGen"           , ps.getParameter<string>(
                    "labelGen"            ) );
  setUserParameter( "use_gen"      , 
  getUserParameter( "labelGen" )           == "" ? "f" : "t" );

  if ( ps.exists( "savedTriggerPaths"   ) )
                   savedTriggerPaths    = ps.getParameter< vector<string> >(
                  "savedTriggerPaths"   );
  if ( ps.exists( "savedTriggerObjects" ) )
                   savedTriggerObjects  = ps.getParameter< vector<string> >(
                  "savedTriggerObjects" );

  jetPtMin  = ps.getParameter<double>( "jetPtMin"  );
  jetEtaMax = ps.getParameter<double>( "jetEtaMax" );

  if ( ps.exists( "eventList" ) )
  setUserParameter( "eventList", ps.getParameter<string>( "eventList" ) );

  setUserParameter( "verbose",
                    ps.getUntrackedParameter<string>( "verbose" ) );

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


void BmmPATToNtuple::openNtuple( const string& name ) {
  TDirectory* current = gDirectory;
  file = ( dumpNtuple ? new TFile( name.c_str(), "CREATE" ) : 0 );
  initWrite( file );
  current->cd();
  return;
}


void BmmPATToNtuple::analyze( const edm::EventBase& ev,
                              int ientry, int event_file ) {

  if ( verbose ) {
    cout << " =========================== " << endl;
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

  if ( !find( runNumber, eventNumber ) ) return;
  read( ev );
  if ( BmmAnalyzer::analyze( ientry, event_file ) ) writeNtuple();

  return;

}

void BmmPATToNtuple::read( const edm::EventBase& ev ) {

  currentEvBase = &ev;

  // store event id
  runNumber   = ev.id().run();
  lumiSection = ev.id().luminosityBlock();
  eventNumber = ev.id().event();

  if ( use_hlts      ) fillHLTStatus   ();
  if ( use_hlto      ) fillHLTObjects  ();
  if ( use_bspot     ) fillBeamSpot    ();
  if ( use_met       ) fillMet         ();
  if ( use_muons     ) fillMuons       ();
  if ( use_electrons ) fillElectrons   ();
  if ( use_taus      ) fillTaus        ();
  if ( use_jets      ) fillJets        ();
  if ( use_pflow     ) fillPFCandidates();
  if ( use_tracks    ) fillTracks      ();
  if ( use_pvts      ) fillPVertices   ();
  if ( use_svts      ) fillSVertices   ();
  if ( use_gen       ) fillGenParticles();

  if ( use_muons && use_tracks ) linkMTracks();
//  if ( use_pflow && use_jets   ) linkPFJets ();
  if ( use_pflow && use_tracks ) linkPTracks();

  return;

}


void BmmPATToNtuple::writeNtuple() {

  if ( !dumpNtuple ) return;
  // function provided by the tool to actually fill the tree
//  cout << "fill" << endl;
  fill();

  return;

}


void BmmPATToNtuple::closeNtuple() {
  if ( !dumpNtuple ) return;
  close();
  file->Close();
  return;
}


void BmmPATToNtuple::endJob() {
  BmmAnalyzer::endJob();
  closeNtuple();
  return;
}


void BmmPATToNtuple::fillHLTStatus() {

  nHLTStatus = 0;
  hltPath  ->resize( 0 );
  hltRun   ->resize( 0 );
  hltAccept->resize( 0 );

  currentEvBase->getByLabel( getUserParameter( "labelTrigResults" ),
                             trigResults );
  if ( !trigResults.isValid() ) {
    cout << "invalid trigResults" << endl;
    triggerNames = 0;
    return;
  }
  else {
    triggerNames = &( currentEvBase->triggerNames( *trigResults ) );
  }

  int nObj = triggerNames->size();
  int iObj;
  int iTrg;
  int nTrg = savedTriggerPaths.size();
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const string& hltPathName = triggerNames->triggerName( iObj );
    int index = triggerNames->triggerIndex( hltPathName );
    for ( iTrg = 0; iTrg < nTrg; ++iTrg ) {
      const string& name = savedTriggerPaths[iTrg];
      if ( ( name != "*" ) &&
           ( hltPathName.find( name, 0 ) != string::npos ) ) continue;
      ++nHLTStatus;
      hltPath  ->push_back( name );
      hltRun   ->push_back( trigResults->wasrun( index ) );
      hltAccept->push_back( trigResults->accept( index ) );
    }
  }

  return;

}


void BmmPATToNtuple::fillHLTObjects() {

  nHLTObjects = 0;
  hltObjType->resize( 0 );
  hltPt     ->resize( 0 );
  hltEta    ->resize( 0 );
  hltPhi    ->resize( 0 );
  hltPx     ->resize( 0 );
  hltPy     ->resize( 0 );
  hltPz     ->resize( 0 );
  hltE      ->resize( 0 );
  currentEvBase->getByLabel( getUserParameter( "labelTrigEvent" ),
                             trigEvent );
  if ( !trigEvent.isValid() ) {
    cout << "invalid trigEvent" << endl;
    return;
  }

  int iTrg;
  int nTrg = savedTriggerObjects.size();
  int triggerObjectType;
  for ( iTrg = 0; iTrg < nTrg; ++iTrg ) {
    const string& name = savedTriggerObjects[iTrg];
    if      ( name == "muon" ) triggerObjectType = trigger::TriggerMuon;
    else if ( name == "jet"  ) triggerObjectType = trigger::TriggerJet;
    else continue;
    const pat::TriggerObjectRefVector
          trigRefs( trigEvent->objects( triggerObjectType ) );
    pat::TriggerObjectRefVector::const_iterator iter = trigRefs.begin();
    pat::TriggerObjectRefVector::const_iterator iend = trigRefs.end();
    while ( iter != iend ) {
      const pat::TriggerObject& obj = **iter++;
      hltObjType->push_back( name );
      const Candidate::LorentzVector p4 = obj.p4();
      hltPt          ->push_back( p4.pt    () );
      hltEta         ->push_back( p4.eta   () );
      hltPhi         ->push_back( p4.phi   () );
      hltPx          ->push_back( p4.px    () );
      hltPy          ->push_back( p4.py    () );
      hltPz          ->push_back( p4.pz    () );
      hltE           ->push_back( p4.energy() );
      ++nHLTObjects;
    }
  }

  return;

}


void BmmPATToNtuple::fillBeamSpot() {

  bwX         = -999.999;
  bwY         = -999.999;
  bwXError    = -999.999;
  bwYError    = -999.999;
  bsX         = -999.999;
  bsY         = -999.999;
  bsZ         = -999.999;
  bsXError    = -999.999;
  bsYError    = -999.999;
  bsZError    = -999.999;
  bsdXdZ      = -999.999;
  bsdYdZ      = -999.999;
  bsdXdZError = -999.999;
  bsdYdZError = -999.999;
  currentEvBase->getByLabel( getUserParameter( "labelBeamSpot" ),
                             beamSpot );
  if ( !beamSpot.isValid() ) {
    cout << "invalid beam spot" << endl;
    return;
  }

  bwX         = beamSpot->BeamWidthX();
  bwY         = beamSpot->BeamWidthY();
  bwXError    = beamSpot->BeamWidthXError();
  bwYError    = beamSpot->BeamWidthYError();
  bsX         = beamSpot->x0();
  bsY         = beamSpot->y0();
  bsZ         = beamSpot->z0();
  bsXError    = beamSpot->x0Error();
  bsYError    = beamSpot->y0Error();
  bsZError    = beamSpot->z0Error();
  bsdXdZ      = beamSpot->dxdz();
  bsdYdZ      = beamSpot->dydz();
  bsdXdZError = beamSpot->dxdzError();
  bsdYdZError = beamSpot->dydzError();

  return;

}


void BmmPATToNtuple::fillMet() {

  mEt = -999.999;
  mEx = -999.999;
  mEy = -999.999;
  currentEvBase->getByLabel( getUserParameter( "labelMets" ),
                             mets );
  if ( !mets.isValid() ) {
    cout << "invalid mets" << endl;
    return;
  }

  // store mEt info

  mEt = mets->at( 0 ).pt();
  mEx = mets->at( 0 ).px();
  mEy = mets->at( 0 ).py();

  return;

}


void BmmPATToNtuple::fillMuons() {

  currentEvBase->getByLabel( getUserParameter( "labelMuons" ),
                             muons );
  bool vMuons = muons.isValid();

  // store muons info

  int iObj;
  int nObj = nMuons = ( vMuons ? muons->size() : 0 );
  muoPt          ->resize( nObj );
  muoEta         ->resize( nObj );
  muoPhi         ->resize( nObj );
  muoPx          ->resize( nObj );
  muoPy          ->resize( nObj );
  muoPz          ->resize( nObj );
  muoE           ->resize( nObj );
  muoCharge      ->resize( nObj );
  muoTrk         ->resize( nObj );
  muoChaIso      ->resize( nObj );
  muoNeuIso      ->resize( nObj );
  muoPhoIso      ->resize( nObj );
  muoSumCHpt     ->resize( nObj );
  muoSumCPpt     ->resize( nObj );
  muoSumNHet     ->resize( nObj );
  muoSumPHet     ->resize( nObj );
  muoSumPUpt     ->resize( nObj );
  muoNumMatches  ->resize( nObj );
  muoDb          ->resize( nObj );
  muoNumValidHits->resize( nObj );
  muoNormChi2    ->resize( nObj );
  muoNumMuHits   ->resize( nObj );
  muoNumPixHits  ->resize( nObj );
  muoNumTkHits   ->resize( nObj );
  if ( !vMuons ) {
    cout << "invalid muons" << endl;
    return;
  }

  vector<const Muon*> muonPtr;
  muonPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    muonPtr[iObj] = &( muons->at( iObj ) );
  }

  compareByPt<Muon> muoComp;
  sort( muonPtr.begin(), muonPtr.end(), muoComp );

  muoMap.clear();
//  pcmMap.clear();
  tkmMap.clear();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Muon& muon = *muonPtr[iObj];
    muoMap.insert( make_pair( &muon, iObj ) );
    const reco::PFCandidateRef& pcr = muon.pfCandidateRef();
    if ( !pcr.isNull() ) {
//    pcmMap.insert( make_pair( &(*pcr), iObj ) );
      const TrackRef& tkr = pcr->trackRef();
      if ( !tkr.isNull() ) tkmMap.insert( make_pair( &(*tkr), iObj ) );
    }

    const Candidate::LorentzVector p4 = muon.p4();
    muoPt          ->at( iObj ) = p4.pt    ();
    muoEta         ->at( iObj ) = p4.eta   ();
    muoPhi         ->at( iObj ) = p4.phi   ();
    muoPx          ->at( iObj ) = p4.px    ();
    muoPy          ->at( iObj ) = p4.py    ();
    muoPz          ->at( iObj ) = p4.pz    ();
    muoE           ->at( iObj ) = p4.energy();
    muoCharge      ->at( iObj ) = muon.charge();
    muoTrk         ->at( iObj ) = -1;

    muoChaIso      ->at( iObj ) = muon.chargedHadronIso();
    muoNeuIso      ->at( iObj ) = muon.neutralHadronIso();
    muoPhoIso      ->at( iObj ) = muon.photonIso();
    const reco::MuonPFIsolation& pfIsolationR04 = muon.pfIsolationR04();
    muoSumCHpt     ->at( iObj ) = pfIsolationR04.sumChargedHadronPt;
    muoSumCPpt     ->at( iObj ) = pfIsolationR04.sumChargedParticlePt;
    muoSumNHet     ->at( iObj ) = pfIsolationR04.sumNeutralHadronEt;
    muoSumPHet     ->at( iObj ) = pfIsolationR04.sumPhotonEt;
    muoSumPUpt     ->at( iObj ) = pfIsolationR04.sumPUPt;

    muoNumMatches  ->at( iObj ) = muon.numberOfMatchedStations();
    muoDb          ->at( iObj ) = muon.dB();

    muoNumValidHits->at( iObj ) = 0;
    muoNormChi2    ->at( iObj ) = 0.0;
    muoNumMuHits   ->at( iObj ) = 0;
    muoNumPixHits  ->at( iObj ) = 0;
    muoNumTkHits   ->at( iObj ) = 0;

    if ( !( muon. isGlobalMuon() ) ) continue;
    if ( !( muon.isTrackerMuon() ) ) continue;
    const TrackRef&  innerTrack = muon. innerTrack();
    const TrackRef& globalTrack = muon.globalTrack();
    const HitPattern& hitPattern = globalTrack->hitPattern();
    try {
    muoNumValidHits->at( iObj ) =  innerTrack->numberOfValidHits();
    }
    catch ( edm::Exception e ) {
    muoNumValidHits->at( iObj ) = 0;
    }
    muoNormChi2    ->at( iObj ) = globalTrack->normalizedChi2();
    muoNumMuHits   ->at( iObj ) = hitPattern.numberOfValidMuonHits();
    muoNumPixHits  ->at( iObj ) = hitPattern.numberOfValidPixelHits();
    muoNumTkHits   ->at( iObj ) = hitPattern.numberOfValidTrackerHits();
  }

  return;

}


void BmmPATToNtuple::fillElectrons() {

  currentEvBase->getByLabel( getUserParameter( "labelElectrons" ),
                             electrons );
  bool vElectrons = electrons.isValid();

  // store electrons info

  int iObj;
  int nObj = nElectrons = ( vElectrons ? electrons->size() : 0 );
  elePt     ->resize( nObj );
  eleEta    ->resize( nObj );
  elePhi    ->resize( nObj );
  elePx     ->resize( nObj );
  elePy     ->resize( nObj );
  elePz     ->resize( nObj );
  eleE      ->resize( nObj );
  eleCharge ->resize( nObj );
  eleTrk    ->resize( nObj );
  eleChaIso ->resize( nObj );
  eleNeuIso ->resize( nObj );
  elePhoIso ->resize( nObj );
  eleAbsEta ->resize( nObj );
  eleAEff   ->resize( nObj );
  eleID     ->resize( nObj );
  eleConsCha->resize( nObj );
  eleEBEEGap->resize( nObj );
  eleDb     ->resize( nObj );
  if ( !vElectrons ) {
    cout << "invalid electrons" << endl;
    return;
  }

  vector<const Electron*> electronPtr;
  electronPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    electronPtr[iObj] = &( electrons->at( iObj ) );
  }

  compareByPt<Electron> eleComp;
  sort( electronPtr.begin(), electronPtr.end(), eleComp );

  eleMap.clear();
  tkeMap.clear();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Electron& electron = *electronPtr[iObj];
    eleMap.insert( make_pair( &electron, iObj ) );
    const reco::PFCandidateRef& pcr = electron.pfCandidateRef();
    if ( !pcr.isNull() ) {
      const TrackRef& tkr = pcr->trackRef();
      if ( !tkr.isNull() ) tkeMap.insert( make_pair( &(*tkr), iObj ) );
    }

    const Candidate::LorentzVector p4 = electron.p4();
    elePt     ->at( iObj ) = p4.pt    ();
    eleEta    ->at( iObj ) = p4.eta   ();
    elePhi    ->at( iObj ) = p4.phi   ();
    elePx     ->at( iObj ) = p4.px    ();
    elePy     ->at( iObj ) = p4.py    ();
    elePz     ->at( iObj ) = p4.pz    ();
    eleE      ->at( iObj ) = p4.energy();
    eleCharge ->at( iObj ) = electron.charge();
    eleTrk    ->at( iObj ) = -1;

    eleChaIso ->at( iObj ) = electron.chargedHadronIso();
    eleNeuIso ->at( iObj ) = electron.neutralHadronIso();
    elePhoIso ->at( iObj ) = electron.photonIso();
//    double absEta =
    eleAbsEta ->at( iObj ) = fabs( electron.superCluster()->eta() );
    eleAEff   ->at( iObj ) = -999.999;
//    eleAEff   ->at( iObj ) =
//      ElectronEffectiveArea::GetElectronEffectiveArea(
//      ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, absEta,
//      ElectronEffectiveArea::kEleEAData2011 );

    eleID     ->at( iObj ) = electron.electronID( "eidMediumMC" );
    eleConsCha->at( iObj ) = electron.isGsfCtfScPixChargeConsistent();
    eleEBEEGap->at( iObj ) = electron.isEBEEGap();
    eleDb     ->at( iObj ) = electron.dB();

  }

  return;

}



void BmmPATToNtuple::fillTaus() {

  currentEvBase->getByLabel( getUserParameter( "labelTaus" ),
                             taus );
  bool vTaus = taus.isValid();

  // store taus info

  int iObj;
  int nObj = nTaus = ( vTaus ? taus->size() : 0 );
  tauPt    ->resize( nObj );
  tauEta   ->resize( nObj );
  tauPhi   ->resize( nObj );
  tauPx    ->resize( nObj );
  tauPy    ->resize( nObj );
  tauPz    ->resize( nObj );
  tauE     ->resize( nObj );
  tauCharge->resize( nObj );
  if ( !vTaus ) {
    cout << "invalid taus" << endl;
    return;
  }

  vector<const Tau*> tauPtr;
  tauPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    tauPtr[iObj] = &( taus->at( iObj ) );
  }

  compareByPt<Tau> tauComp;
  sort( tauPtr.begin(), tauPtr.end(), tauComp );

  tauMap.clear();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Tau& tau = *tauPtr[iObj];
    tauMap.insert( make_pair( &tau, iObj ) );

    const Candidate::LorentzVector p4 = tau.p4();
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


void BmmPATToNtuple::fillJets() {

  currentEvBase->getByLabel( getUserParameter( "labelJets" ),
                             jets );
  bool vJets = jets.isValid();

  // store jets info

  int iObj;
  int nObj = 0;
//  int nObj = ( vJets ? jets->size() : 0 );
  jetPt  ->resize( 0 );
  jetEta ->resize( 0 );
  jetPhi ->resize( 0 );
  jetPx  ->resize( 0 );
  jetPy  ->resize( 0 );
  jetPz  ->resize( 0 );
  jetE   ->resize( 0 );
  jetCSV ->resize( 0 );
  jetTCHE->resize( 0 );
  jetPF  ->resize( 0 );
  jetNDau->resize( 0 );
  jetNHF ->resize( 0 );
  jetNEF ->resize( 0 );
  jetCHF ->resize( 0 );
  jetCEF ->resize( 0 );
  jetNCH ->resize( 0 );
  if ( !vJets ) {
    cout << "invalid jets" << endl;
    return;
  }
  else {
    nObj = jets->size();
  }

  vector<const Jet*> jetPtr;
  jetPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) jetPtr[iObj] = &( jets->at( iObj ) );

  compareByPt<Jet> jetComp;
  sort( jetPtr.begin(), jetPtr.end(), jetComp );

  string labelCSV  = "combinedSecondaryVertexBJetTags";
  string labelTCHE = "trackCountingHighEffBJetTags";
  jetMap.clear();
  pcjMap.clear();
  nJets = 0;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Jet& jet = *jetPtr[iObj];
    if ( fabs( jet.eta() ) > jetEtaMax ) continue;
    if (       jet.pt ()   < jetPtMin  ) continue;

    jetMap.insert( make_pair( &jet, nJets ) );
    const vector<PFCandidatePtr>& jPFC = jet.getPFConstituents();
    int nPFC = jPFC.size();
    int iPFC;
    for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
      const PFCandidatePtr& pfp = jPFC.at( iPFC );
      pcjMap.insert( make_pair( &(*pfp), nJets ) );
    }

    jetPt  ->push_back( jet.pt    () );
    jetEta ->push_back( jet.eta   () );
    jetPhi ->push_back( jet.phi   () );
    jetPx  ->push_back( jet.px    () );
    jetPy  ->push_back( jet.py    () );
    jetPz  ->push_back( jet.pz    () );
    jetE   ->push_back( jet.energy() );
    jetCSV ->push_back( jet.bDiscriminator( labelCSV  )   );
    jetTCHE->push_back( jet.bDiscriminator( labelTCHE )   );
    jetPF  ->push_back( jet.isPFJet()                     );
    jetNDau->push_back( jet.numberOfDaughters()           );
    jetNHF ->push_back( jet.neutralHadronEnergyFraction() );
    jetNEF ->push_back( jet.neutralEmEnergyFraction()     );
    jetCHF ->push_back( jet.chargedHadronEnergyFraction() );
    jetCEF ->push_back( jet.chargedEmEnergyFraction()     );
    jetNCH ->push_back( jet.chargedMultiplicity()         );

    ++nJets;

  }

  return;

}


void BmmPATToNtuple::fillPFCandidates() {

  currentEvBase->getByLabel( getUserParameter( "labelPFCandidates" ),
                             pfCandidates );
  bool vPF = pfCandidates.isValid();

  // store tracks info

  int iObj;
  int nObj = 0;
//  int nObj = ( vPF ? pfCandidates->size() : 0 );
  pfcPt      ->resize( 0 );
  pfcEta     ->resize( 0 );
  pfcPhi     ->resize( 0 );
  pfcPx      ->resize( 0 );
  pfcPy      ->resize( 0 );
  pfcPz      ->resize( 0 );
  pfcE       ->resize( 0 );
  pfcCharge  ->resize( 0 );
  pfcJet     ->resize( 0 );
  pfcTrk     ->resize( 0 );
  if ( !vPF ) {
    cout << "invalid particle flow" << endl;
    return;
  }
  else {
    nObj = pfCandidates->size();
  }

  pfcMap.clear();
  tkpMap.clear();
  nPF = 0;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const PFCandidate& pfc = pfCandidates->at( iObj );
    const TrackRef   & tkr = pfc.trackRef();
    const Track      * tkp = ( tkr.isNull() ? 0 : &(*tkr) );

//    map<const PFCandidate*,int>::const_iterator m_iter = pcmMap.find( &pfc );
//    map<const PFCandidate*,int>::const_iterator m_iend = pcmMap.end();
    map<const Track      *,int>::const_iterator m_iter = tkmMap.find( tkp );
    map<const Track      *,int>::const_iterator m_iend = tkmMap.end();
    map<const Track      *,int>::const_iterator e_iter = tkeMap.find( tkp );
    map<const Track      *,int>::const_iterator e_iend = tkeMap.end();
    map<const PFCandidate*,int>::const_iterator j_iter = pcjMap.find( &pfc );
    map<const PFCandidate*,int>::const_iterator j_iend = pcjMap.end();

    int muoIndex = -1;
    int eleIndex = -1;
    int jetIndex = -1;
    if ( m_iter != m_iend ) muoIndex = m_iter->second;
    if ( e_iter != e_iend ) eleIndex = e_iter->second;
    if ( j_iter != j_iend ) jetIndex = j_iter->second;
    if ( ( muoIndex < 0 ) &&
         ( eleIndex < 0 ) &&
         ( jetIndex < 0 ) ) continue;

    if ( tkp != 0 )
    tkpMap.insert( make_pair(  tkp, nPF ) );
    pfcMap.insert( make_pair( &pfc, nPF ) );
    const Candidate::LorentzVector p4 = pfc.p4();

    pfcPt      ->push_back( p4.pt    () );
    pfcEta     ->push_back( p4.eta   () );
    pfcPhi     ->push_back( p4.phi   () );
    pfcPx      ->push_back( p4.px    () );
    pfcPy      ->push_back( p4.py    () );
    pfcPz      ->push_back( p4.pz    () );
    pfcE       ->push_back( p4.energy() );
    pfcCharge  ->push_back( pfc.charge() );
//    pfcJet     ->push_back( -1 );
    pfcJet     ->push_back( jetIndex );
    pfcTrk     ->push_back( -1 );

//    const reco::TrackRef& trk = pfc.trackRef();
//    pftMap.insert( make_pair( &(*trk), iObj ) );

    ++nPF;

  }

  return;

}

void BmmPATToNtuple::fillTracks() {

  currentEvBase->getByLabel( getUserParameter( "labelGeneralTracks" ),
                             generalTracks );
  bool vTracks = generalTracks.isValid();

  // store tracks info

  int iObj;
  int nObj = 0;
//  int nObj = ( vTracks ? generalTracks->size() : 0 );
  trkPt      ->resize( 0 );
  trkEta     ->resize( 0 );
  trkPhi     ->resize( 0 );
  trkPx      ->resize( 0 );
  trkPy      ->resize( 0 );
  trkPz      ->resize( 0 );
  trkCharge  ->resize( 0 );
  trkPFC     ->resize( 0 );
  trkPVtx    ->resize( 0 );
  trkSVtx    ->resize( 0 );
  trkQuality ->resize( 0 );
  trkNormChi2->resize( 0 );
  trkDxy     ->resize( 0 );
  trkDz      ->resize( 0 );
  if ( !vTracks ) {
    cout << "invalid tracks" << endl;
    return;
  }
  else {
    nObj = generalTracks->size();
  }

  trkMap.clear();
  nTracks = 0;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Track& trk = generalTracks->at( iObj );
    const Track* tkp = &trk;

    map<const Track      *,int>::const_iterator m_iter = tkmMap.find( tkp );
    map<const Track      *,int>::const_iterator m_iend = tkmMap.end();
    map<const Track      *,int>::const_iterator e_iter = tkeMap.find( tkp );
    map<const Track      *,int>::const_iterator e_iend = tkeMap.end();
    map<const Track      *,int>::const_iterator p_iter = tkpMap.find( tkp );
    map<const Track      *,int>::const_iterator p_iend = tkpMap.end();
    int muoIndex = -1;
    int eleIndex = -1;
    int pfcIndex = -1;
    if ( m_iter != m_iend ) muoIndex = m_iter->second;
    if ( e_iter != e_iend ) eleIndex = e_iter->second;
    if ( p_iter != p_iend ) pfcIndex = p_iter->second;
    if ( ( pfcIndex < 0 ) &&
         ( muoIndex < 0 ) &&
         ( eleIndex < 0 ) ) continue;

    trkMap.insert( make_pair( tkp, nTracks ) );

    trkPt      ->push_back( trk.pt    () );
    trkEta     ->push_back( trk.eta   () );
    trkPhi     ->push_back( trk.phi   () );
    trkPx      ->push_back( trk.px    () );
    trkPy      ->push_back( trk.py    () );
    trkPz      ->push_back( trk.pz    () );
    trkCharge  ->push_back( trk.charge() );
    trkPFC     ->push_back( -1 );
    trkPVtx    ->push_back( -1 );
    trkSVtx    ->push_back( -1 );
    trkQuality ->push_back( trk.qualityMask() );
    trkNormChi2->push_back( trk.normalizedChi2() );
    trkDxy     ->push_back( trk.dxy() );
    trkDz      ->push_back( trk.dz () );

    ++nTracks;

  }

  return;

}


void BmmPATToNtuple::fillPVertices() {

  currentEvBase->getByLabel( getUserParameter( "labelPVertices" ),
                             pVertices );
  bool vPvts = pVertices.isValid();

  // store primary vertices info

  int iObj;
  int nObj = 0;
//  int nObj = ( vPvts ? pVertices->size() : 0 );
  pvtX         ->resize( nObj );
  pvtY         ->resize( nObj );
  pvtZ         ->resize( nObj );
  pvtSxx       ->resize( nObj );
  pvtSyy       ->resize( nObj );
  pvtSzz       ->resize( nObj );
  pvtSxy       ->resize( nObj );
  pvtSxz       ->resize( nObj );
  pvtSyz       ->resize( nObj );
//  pvtCovariance->resize( nObj );
  pvtNormChi2  ->resize( nObj );
  pvtBadQuality->resize( nObj );
  if ( !vPvts ) {
    cout << "invalid primary vertices" << endl;
    return;
  }
  else {
    nObj = pVertices->size();
  }

  map<const Track*,int>::const_iterator it_p = trkMap.begin();
  map<const Track*,int>::const_iterator ie_p = trkMap.end();
  nPVertices = 0;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Vertex& vtx = pVertices->at( iObj );
    const Vertex::Point& pos = vtx.position();

    bool found = false;
    try {
      Vertex::trackRef_iterator iter = vtx.tracks_begin();
      Vertex::trackRef_iterator iend = vtx.tracks_end();
      while ( iter != iend ) {
        const reco::TrackBaseRef& tkr = *iter++;
        it_p = trkMap.find( &(*tkr) );
        if ( it_p != ie_p ) {
          found = true;
          int trkIndex = it_p->second;
          int& trkLink = trkPVtx->at( trkIndex );
          if ( trkLink < 0 ) {
            trkLink = nPVertices;
            trkDxy->at( trkIndex ) = tkr->dxy( pos );
            trkDz ->at( trkIndex ) = tkr->dz ( pos );
          }
//          else cout << "multiple vertex " << iObj << " " << nPVertices << endl;
        }
//        else {
//          if ( tkr->pt() > 4.0 ) cout << "high pt " << tkr->pt() << endl;
//        }
      }
    }
    catch ( edm::Exception e ) {
    }

    if ( !found ) continue;

    pvtX         ->push_back( pos.X() );
    pvtY         ->push_back( pos.Y() );
    pvtZ         ->push_back( pos.Z() );
    pvtSxx       ->push_back( vtx.covariance( 0, 0 ) );
    pvtSyy       ->push_back( vtx.covariance( 1, 1 ) );
    pvtSzz       ->push_back( vtx.covariance( 2, 2 ) );
    pvtSxy       ->push_back( vtx.covariance( 0, 1 ) );
    pvtSxz       ->push_back( vtx.covariance( 0, 2 ) );
    pvtSyz       ->push_back( vtx.covariance( 1, 2 ) );
//    vector<double> covariance;
//    covariance.resize( 6 );
//    covariance[0] = vtx.covariance( 0, 0 );
//    covariance[1] = vtx.covariance( 1, 1 );
//    covariance[2] = vtx.covariance( 2, 2 );
//    covariance[3] = vtx.covariance( 0, 1 );
//    covariance[4] = vtx.covariance( 0, 2 );
//    covariance[5] = vtx.covariance( 1, 2 );
//    pvtCovariance->push_back( covariance );
    pvtNTracks   ->push_back( vtx.nTracks() );
    pvtNormChi2  ->push_back( vtx.normalizedChi2() );
    pvtBadQuality->push_back( vtx.isValid() ? 0 : ( vtx.isFake() ? 1 : 2 ) );

    ++nPVertices;

  }


  return;

}


void BmmPATToNtuple::fillSVertices() {

  currentEvBase->getByLabel( getUserParameter( "labelSVertices" ),
                             sVertices );
  bool vSvts = sVertices.isValid();

  // store secondary vertices info

  int iObj;
  int nObj = 0;
//  int nObj = ( vSvts ? sVertices->size() : 0 );
  svtX         ->resize( 0 );
  svtY         ->resize( 0 );
  svtZ         ->resize( 0 );
  svtSxx       ->resize( 0 );
  svtSyy       ->resize( 0 );
  svtSzz       ->resize( 0 );
  svtSxy       ->resize( 0 );
  svtSxz       ->resize( 0 );
  svtSyz       ->resize( 0 );
  svtDirX      ->resize( 0 );
  svtDirY      ->resize( 0 );
  svtDirZ      ->resize( 0 );
  svtNormChi2  ->resize( 0 );
  svtMass      ->resize( 0 );
  svtDist2D    ->resize( 0 );
  svtSign2D    ->resize( 0 );
  svtDist3D    ->resize( 0 );
  svtSign3D    ->resize( 0 );
  svtJet       ->resize( 0 );
  svtNTracks   ->resize( 0 );
  svtBadQuality->resize( 0 );

  if ( !vSvts ) {
    cout << "invalid sVertices" << endl;
    return;
  }
  else {
    nObj = sVertices->size();
  }


//  int ntj = jets->size();
//  if ( nObj != ntj ) cout << "JETS-VTX: " << nObj << " " << ntj << endl;

  map<const Jet*,int>::const_iterator j_iter = jetMap.begin();
  map<const Jet*,int>::const_iterator j_iend = jetMap.end();
  nSVertices = 0;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const Jet* jet = &( jets->at( iObj ) );
    j_iter = jetMap.find( jet );
    if ( j_iter == j_iend ) continue;
    const SecondaryVertexTagInfo& secVtxTagInfo = sVertices->at( iObj );
    int iVtx;
    int nVtx = secVtxTagInfo.nVertices();
//    if ( secVtxTagInfo.nVertices() <= 0 ) continue;
    for ( iVtx = 0; iVtx < nVtx; ++iVtx ) {
      const        Vertex& vtx = secVtxTagInfo.secondaryVertex( iVtx );
      const  GlobalVector& dir = secVtxTagInfo.flightDirection( iVtx );
      const Measurement1D& d2d = secVtxTagInfo.flightDistance( iVtx, true  );
      const Measurement1D& d3d = secVtxTagInfo.flightDistance( iVtx, false );
      svtX         ->push_back( vtx.x() );
      svtY         ->push_back( vtx.y() );
      svtZ         ->push_back( vtx.z() );
      svtSxx       ->push_back( vtx.covariance( 0, 0 ) );
      svtSyy       ->push_back( vtx.covariance( 1, 1 ) );
      svtSzz       ->push_back( vtx.covariance( 2, 2 ) );
      svtSxy       ->push_back( vtx.covariance( 0, 1 ) );
      svtSxz       ->push_back( vtx.covariance( 0, 2 ) );
      svtSyz       ->push_back( vtx.covariance( 1, 2 ) );
      svtDirX      ->push_back( dir.x() );
      svtDirY      ->push_back( dir.y() );
      svtDirZ      ->push_back( dir.z() );
      svtType      ->push_back( "tagInfo" );
      svtNTracks   ->push_back( vtx.nTracks() );
      svtNormChi2  ->push_back( vtx.normalizedChi2() );
      double vMass = 0;
      try                        { vMass = vtx.p4().M(); }
      catch ( edm::Exception e ) { vMass = 0.0; }
      svtMass      ->push_back( vMass );
      svtDist2D    ->push_back( d2d.value() );
      svtSign2D    ->push_back( d2d.significance() );
      svtDist3D    ->push_back( d3d.value() );
      svtSign3D    ->push_back( d3d.significance() );
      svtJet       ->push_back( j_iter->second );
      svtBadQuality->push_back( vtx.isValid() ? 0 : ( vtx.isFake() ? 1 : 2 ) );

      try {
        Vertex::trackRef_iterator iter = vtx.tracks_begin();
        Vertex::trackRef_iterator iend = vtx.tracks_end();
        while ( iter != iend ) {
          const reco::TrackBaseRef& tkr = *iter++;
          map<const Track*,int>::const_iterator it_p = trkMap.find( &(*tkr) );
          map<const Track*,int>::const_iterator ie_p = trkMap.end();
          if ( it_p != ie_p ) trkSVtx->at( it_p->second ) = nSVertices;
        }
      }
      catch ( edm::Exception e ) {
      }

      ++nSVertices;

    }
  }

  return;

}


void BmmPATToNtuple::fillGenParticles() {

  currentEvBase->getByLabel( getUserParameter( "labelGen" ),
                             particles );
  bool vGen = particles.isValid();

  // store gen particles info

  int iObj;
  int nObj = ( vGen ? particles->size() : 0 );
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
  if ( !vGen ) {
    cout << "invalid particles" << endl;
    return;
  }

  map<const Candidate*,int> genMap;
  nGenP = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

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

  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const GenParticle& gen = particles->at( iObj );
    map<const Candidate*,int>::const_iterator iter = genMap.find(
                                                            gen.mother() );
    map<const Candidate*,int>::const_iterator iend = genMap.end();
    if ( iter != iend ) genMother->at( iObj ) = iter->second;
//    cout << "gen particle: " << iObj << " "
//                             << &(particles->at( iObj )) << " "
//                             << &gen << " " << genMother->at( iObj ) << " "
//                             << gen.mother() << endl;
  }

  return;

}


void BmmPATToNtuple::linkMTracks() {

  map<const Muon*,int>::const_iterator m_iter = muoMap.begin();
  map<const Muon*,int>::const_iterator m_iend = muoMap.end();
  while ( m_iter != m_iend ) {
    const pair<const Muon*,int>& entry = *m_iter++;
    const Muon* muon = entry.first;
    int iMuon        = entry.second;
    try {
//      if ( muon->pfCandidateRef().isNull() ) cout << "muon->pfCandidateRef().isNull()" << endl;
      if ( muon->pfCandidateRef().isNull() ) continue;
      const PFCandidate& pfm = *muon->pfCandidateRef();
//      if ( pfm.trackRef().isNull() ) cout << "muon->pfCandidateRef().trackRef().isNull()" << endl;
      if ( pfm.trackRef().isNull() ) continue;
      const reco::TrackRef& trk = pfm.trackRef();
      map<const Track*,int>::const_iterator t_iter = trkMap.find( &(*trk) );
      map<const Track*,int>::const_iterator t_iend = trkMap.end();
      if ( t_iter != t_iend ) muoTrk->at( iMuon ) = t_iter->second;
//      if ( t_iter != t_iend ) cout << "muon trk: " << t_iter->second << endl;
//      else                    cout << "muon trk missing" << endl;
    }
    catch ( edm::Exception e ) {
      cout << "muon trk lost" << endl;
    }
/*
*/
  }

/*
*/
/*
  int nmu = muons->size();
  int imu;
  for ( imu = 0; imu < nmu; ++imu ) {
    cout << "link muon " << imu << endl;

    const Muon& muon = muons->at( imu );
    cout << "reloaded muons: " << imu << " " << &muon << endl;
    const Candidate::LorentzVector m4 = muon.p4();
    try {
    const PFCandidate& pfm = *muon.pfCandidateRef();
    map<const Track*,int>::const_iterator it_p = trkMap.find( &(*pfm.trackRef()) );
    map<const Track*,int>::const_iterator iend = trkMap.end();
    if ( it_p != iend ) {
      const Track& gtk = generalTracks->at( it_p->second );
      float dist = sqrt( pow( m4.px() - gtk.px(), 2 ) +
                         pow( m4.py() - gtk.py(), 2 ) +
                         pow( m4.pz() - gtk.pz(), 2 ) );
      cout << "trk match: " << it_p->second << " " << dist << endl;
    }
    }
    catch ( edm::Exception e ) {
      cout << "no trk match " << endl;
    }
  }
*/
/*
*/

  return;

}

/*
void BmmPATToNtuple::linkPFJets() {

  map<const Jet*,int>::const_iterator j_iter = jetMap.begin();
  map<const Jet*,int>::const_iterator j_iend = jetMap.end();
  while ( j_iter != j_iend ) {
    const pair<const Jet*,int>& entry = *j_iter++;
    const Jet* jet = entry.first;
    int iJet       = entry.second;
    map<const PFCandidate*,int>::const_iterator p_iter = pfcMap.begin();
    map<const PFCandidate*,int>::const_iterator p_iend = pfcMap.end();
    const vector<PFCandidatePtr>& jPFC = jet->getPFConstituents();
    int nPFC = jPFC.size();
    int iPFC;
    for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
      const PFCandidatePtr& pfp = jPFC.at( iPFC );
      p_iter = pfcMap.find( &(*pfp) );
      if ( p_iter != p_iend ) pfcJet->at( p_iter->second ) = iJet;
    }
  }
  return;

}
*/

void BmmPATToNtuple::linkPTracks() {

  map<const PFCandidate*,int>::const_iterator p_iter = pfcMap.begin();
  map<const PFCandidate*,int>::const_iterator p_iend = pfcMap.end();
  while ( p_iter != p_iend ) {
    const pair<const PFCandidate*,int>& entry = *p_iter++;
    const PFCandidate* pfc = entry.first;
    int iPFC               = entry.second;
    if ( !pfc->charge() ) continue;
    try {
      const TrackRef& trk = pfc->trackRef();
      map<const Track*,int>::const_iterator t_iter = trkMap.find( &(*trk) );
      map<const Track*,int>::const_iterator t_iend = trkMap.end();
      if ( t_iter == t_iend ) continue;
      int iTrk = t_iter->second;
      pfcTrk->at( iPFC ) = iTrk;
      trkPFC->at( iTrk ) = iPFC;
    }
    catch ( edm::Exception e ) {
    }
  }

  return;

}

