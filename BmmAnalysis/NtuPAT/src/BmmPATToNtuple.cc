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
#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"

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
using reco::TrackBaseRef;
using reco::Vertex;
using reco::SecondaryVertexTagInfo;
using reco::GenParticle;

using namespace std;

BmmPATToNtuple::BmmPATToNtuple( const edm::ParameterSet& ps ) {

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

  setUserParameter( "labelPFCandidates"  , ps.getParameter<string>(
                    "labelPFCandidates"   ) );
  setUserParameter( "use_pflow"    , 
  getUserParameter( "labelPFCandidates" )  == "" ? "f" : "t" );

  setUserParameter( "labelGeneralTracks" , ps.getParameter<string>(
                    "labelGeneralTracks"  ) );
  setUserParameter( "use_tracks"   , 
  getUserParameter( "labelGeneralTracks" ) == "" ? "f" : "t" );

  setUserParameter( "labelJets"          , ps.getParameter<string>(
                    "labelJets"           ) );
  setUserParameter( "use_jets"     , 
  getUserParameter( "labelJets" )          == "" ? "f" : "t" );

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
  if ( use_pflow     ) fillPFCandidates();
  if ( use_tracks    ) fillTracks      ();
  if ( use_jets      ) fillJets        ();
  if ( use_pvts      ) fillPVertices   ();
  if ( use_svts      ) fillSVertices   ();
  if ( use_gen       ) fillGenParticles();

  if ( use_muons && use_tracks ) linkMuTracks();
  if ( use_pflow && use_jets   ) linkPFJets  ();
  if ( use_pflow && use_tracks ) linkPFTracks();

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
  int nObj = ( vMuons ? muons->size() : 0 );
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
  nMuons = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Muon& muon = *muonPtr[iObj];
    muoMap.insert( make_pair( &muon, iObj ) );

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
    const reco::TrackRef&  innerTrack = muon. innerTrack();
    const reco::TrackRef& globalTrack = muon.globalTrack();
    const reco::HitPattern& hitPattern = globalTrack->hitPattern();
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
  int nObj = ( vElectrons ? electrons->size() : 0 );
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

  nElectrons = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Electron& electron = *electronPtr[iObj];

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
    double absEta =
    eleAbsEta ->at( iObj ) = fabs( electron.superCluster()->eta() );
    eleAEff   ->at( iObj ) = 
      ElectronEffectiveArea::GetElectronEffectiveArea(
      ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, absEta,
      ElectronEffectiveArea::kEleEAData2011 );

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
  int nObj = ( vTaus ? taus->size() : 0 );
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

  nTaus = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Tau& tau = *tauPtr[iObj];

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


void BmmPATToNtuple::fillPFCandidates() {

  currentEvBase->getByLabel( getUserParameter( "labelPFCandidates" ),
                             pfCandidates );
  bool vPF = pfCandidates.isValid();

  // store tracks info

  int iObj;
  int nObj = ( vPF ? pfCandidates->size() : 0 );
  pfcPt      ->resize( nObj );
  pfcEta     ->resize( nObj );
  pfcPhi     ->resize( nObj );
  pfcPx      ->resize( nObj );
  pfcPy      ->resize( nObj );
  pfcPz      ->resize( nObj );
  pfcE       ->resize( nObj );
  pfcCharge  ->resize( nObj );
  pfcJet     ->resize( nObj );
  pfcTrk     ->resize( nObj );
  if ( !vPF ) {
    cout << "invalid particle flow" << endl;
    return;
  }

  pfcMap.clear();
  nPF = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const PFCandidate& pfc = pfCandidates->at( iObj );
    pfcMap.insert( make_pair( &pfc, iObj ) );
    const Candidate::LorentzVector p4 = pfc.p4();

    pfcPt      ->at( iObj ) = p4.pt    ();
    pfcEta     ->at( iObj ) = p4.eta   ();
    pfcPhi     ->at( iObj ) = p4.phi   ();
    pfcPx      ->at( iObj ) = p4.px    ();
    pfcPy      ->at( iObj ) = p4.py    ();
    pfcPz      ->at( iObj ) = p4.pz    ();
    pfcE       ->at( iObj ) = p4.energy();
    pfcCharge  ->at( iObj ) = pfc.charge();
    pfcJet     ->at( iObj ) = -1;
    pfcTrk     ->at( iObj ) = -1;

//    const reco::TrackRef& trk = pfc.trackRef();
//    pftMap.insert( make_pair( &(*trk), iObj ) );

  }

  return;

}

void BmmPATToNtuple::fillTracks() {

  currentEvBase->getByLabel( getUserParameter( "labelGeneralTracks" ),
                             generalTracks );
  bool vTracks = generalTracks.isValid();

  // store tracks info

  int iObj;
  int nObj = ( vTracks ? generalTracks->size() : 0 );
  trkPt      ->resize( nObj );
  trkEta     ->resize( nObj );
  trkPhi     ->resize( nObj );
  trkPx      ->resize( nObj );
  trkPy      ->resize( nObj );
  trkPz      ->resize( nObj );
  trkCharge  ->resize( nObj );
  trkPFC     ->resize( nObj );
  trkPVtx    ->resize( nObj );
  trkSVtx    ->resize( nObj );
  trkQuality ->resize( nObj );
  trkNormChi2->resize( nObj );
  trkDxy     ->resize( nObj );
  trkDz      ->resize( nObj );
  if ( !vTracks ) {
    cout << "invalid tracks" << endl;
    return;
  }

  trkMap.clear();
  nTracks = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Track& trk = generalTracks->at( iObj );
    trkMap.insert( make_pair( &trk, iObj ) );

    trkPt      ->at( iObj ) = trk.pt    ();
    trkEta     ->at( iObj ) = trk.eta   ();
    trkPhi     ->at( iObj ) = trk.phi   ();
    trkPx      ->at( iObj ) = trk.px    ();
    trkPy      ->at( iObj ) = trk.py    ();
    trkPz      ->at( iObj ) = trk.pz    ();
    trkCharge  ->at( iObj ) = trk.charge();
    trkPFC     ->at( iObj ) = -1;
    trkPVtx    ->at( iObj ) = -1;
    trkSVtx    ->at( iObj ) = -1;
    trkQuality ->at( iObj ) = trk.qualityMask();
    trkNormChi2->at( iObj ) = trk.normalizedChi2();
    trkDxy     ->at( iObj ) = trk.dxy();
    trkDz      ->at( iObj ) = trk.dz();

  }

  return;

}


void BmmPATToNtuple::fillJets() {

  currentEvBase->getByLabel( getUserParameter( "labelJets" ),
                             jets );
  bool vJets = jets.isValid();

  // store jets info

  int iObj;
  int nObj = ( vJets ? jets->size() : 0 );
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
  if ( !vJets ) {
    cout << "invalid jets" << endl;
    return;
  }

  vector<const Jet*> jetPtr;
  jetPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    jetPtr[iObj] = &( jets->at( iObj ) );
  }

  compareByPt<Jet> jetComp;
  sort( jetPtr.begin(), jetPtr.end(), jetComp );

  string labelCSV  = "combinedSecondaryVertexBJetTags";
  string labelTCHE = "trackCountingHighEffBJetTags";
  jetMap.clear();
  nJets = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Jet& jet = *jetPtr[iObj];
    jetMap.insert( make_pair( &jet, iObj ) );

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


void BmmPATToNtuple::fillPVertices() {

  currentEvBase->getByLabel( getUserParameter( "labelPVertices" ),
                             pVertices );
  bool vPvts = pVertices.isValid();

  // store primary vertices info

  int iObj;
  int nObj = ( vPvts ? pVertices->size() : 0 );
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

  nPVertices = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const Vertex& vtx = pVertices->at( iObj );
    pvtX         ->at( iObj ) = vtx.x();
    pvtY         ->at( iObj ) = vtx.y();
    pvtZ         ->at( iObj ) = vtx.z();
    pvtSxx       ->at( iObj ) = vtx.covariance( 0, 0 );
    pvtSyy       ->at( iObj ) = vtx.covariance( 1, 1 );
    pvtSzz       ->at( iObj ) = vtx.covariance( 2, 2 );
    pvtSxy       ->at( iObj ) = vtx.covariance( 0, 1 );
    pvtSxz       ->at( iObj ) = vtx.covariance( 0, 2 );
    pvtSyz       ->at( iObj ) = vtx.covariance( 1, 2 );
//    vector<double>& covariance =
//    pvtCovariance->at( iObj );
//    covariance.resize( 6 );
//    covariance[0] = vtx.covariance( 0, 0 );
//    covariance[1] = vtx.covariance( 1, 1 );
//    covariance[2] = vtx.covariance( 2, 2 );
//    covariance[3] = vtx.covariance( 0, 1 );
//    covariance[4] = vtx.covariance( 0, 2 );
//    covariance[5] = vtx.covariance( 1, 2 );
    pvtNormChi2  ->at( iObj ) = vtx.normalizedChi2();
    pvtBadQuality->at( iObj ) = 0;
    if ( vtx.isValid() ) pvtBadQuality->at( iObj ) = 0;
    else
    if ( vtx.isFake()  ) pvtBadQuality->at( iObj ) = 1;
    else                 pvtBadQuality->at( iObj ) = 2;
    try {
      Vertex::trackRef_iterator iter = vtx.tracks_begin();
      Vertex::trackRef_iterator iend = vtx.tracks_end();
      while ( iter != iend ) {
        const reco::TrackBaseRef& tkr = *iter++;
        map<const Track*,int>::const_iterator it_p = trkMap.find( &(*tkr) );
        map<const Track*,int>::const_iterator ie_p = trkMap.end();
        if ( it_p != ie_p ) trkPVtx->at( it_p->second ) = iObj;
      }
    }
    catch ( edm::Exception e ) {
    }
  }


  return;

}


void BmmPATToNtuple::fillSVertices() {

  nSVertices = 0;
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

  currentEvBase->getByLabel( getUserParameter( "labelSVertices" ),
                             sVertices );
  if ( !sVertices.isValid() ) {
    cout << "invalid sVertices" << endl;
    return;
  }

  int nObj = sVertices->size();
  if ( nObj != nJets ) cout << "JETS-VTX: " << nObj << " " << nJets << endl;
  int iObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
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
      svtNormChi2  ->push_back( vtx.normalizedChi2() );
      double vMass = 0;
      try                        { vMass = vtx.p4().M(); }
      catch ( edm::Exception e ) { vMass = 0.0; }
      svtMass      ->push_back( vMass );
      svtDist2D    ->push_back( d2d.value() );
      svtSign2D    ->push_back( d2d.significance() );
      svtDist3D    ->push_back( d3d.value() );
      svtSign3D    ->push_back( d3d.significance() );
      svtJet       ->push_back( iObj );
      svtNTracks   ->push_back( vtx.nTracks() );
      int badQ = 0;
      if ( vtx.isValid() ) badQ = 0;
      else
	if ( vtx.isFake()  ) badQ = 1;
	else                 badQ = 2;
      svtBadQuality->push_back( badQ );
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


void BmmPATToNtuple::linkMuTracks() {

  map<const Muon*,int>::const_iterator m_iter = muoMap.begin();
  map<const Muon*,int>::const_iterator m_iend = muoMap.end();
  while ( m_iter != m_iend ) {
    const pair<const Muon*,int>& entry = *m_iter++;
    const Muon* muon = entry.first;
    int iMuon        = entry.second;
    try {
      const PFCandidate& pfm = *muon->pfCandidateRef();
      if ( muon->pfCandidateRef().isNull() ) continue;
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

  return;

}


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


void BmmPATToNtuple::linkPFTracks() {

  map<const PFCandidate*,int>::const_iterator p_iter = pfcMap.begin();
  map<const PFCandidate*,int>::const_iterator p_iend = pfcMap.end();
  while ( p_iter != p_iend ) {
    const pair<const PFCandidate*,int>& entry = *p_iter++;
    const PFCandidate* pfc = entry.first;
    int iPFC               = entry.second;
    if ( !pfc->charge() ) continue;
    try {
      const reco::TrackRef& trk = pfc->trackRef();
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

