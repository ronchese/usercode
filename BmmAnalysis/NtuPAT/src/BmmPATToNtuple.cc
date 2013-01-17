#include "BmmAnalysis/NtuPAT/interface/BmmPATToNtuple.h"
#include "TFile.h"
#include "TROOT.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
//#include "DataFormats/HLTReco/interface/TriggerObject.h"
//#include "DataFormats/HLTReco/interface/TriggerEvent.h"
//#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

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
  labelHLT          = ps.getParameter<string>( "labelHLT"          );
  labelMets         = ps.getParameter<string>( "labelMets"         );
  labelMuons        = ps.getParameter<string>( "labelMuons"        );
  labelElectrons    = ps.getParameter<string>( "labelElectrons"    );
  labelTaus         = ps.getParameter<string>( "labelTaus"         );
  labelPFCandidates = ps.getParameter<string>( "labelPFCandidates" );
  labelGeneralTracks = ps.getParameter<string>( "labelGeneralTracks" );
  labelJets         = ps.getParameter<string>( "labelJets"         );
  labelPVertices    = ps.getParameter<string>( "labelPVertices"    );
  labelSVertices    = ps.getParameter<string>( "labelSVertices"    );
  labelGen          = ps.getParameter<string>( "labelGen"          );
  savedTriggers     = ps.getParameter< vector<string> >( "savedTriggers" );
  setUserParameter( "use_hlt"      , labelHLT          == "" ? "f" : "t" );
  setUserParameter( "use_met"      , labelMets         == "" ? "f" : "t" );
  setUserParameter( "use_muons"    , labelMuons        == "" ? "f" : "t" );
  setUserParameter( "use_electrons", labelElectrons    == "" ? "f" : "t" );
  setUserParameter( "use_taus"     , labelTaus         == "" ? "f" : "t" );
  setUserParameter( "use_tracks"   , labelPFCandidates == "" ? "f" : "t" );
  setUserParameter( "use_tracks"   , labelGeneralTracks == "" ? "f" : "t" );
  setUserParameter( "use_jets"     , labelJets         == "" ? "f" : "t" );
  setUserParameter( "use_pvts"     , labelPVertices    == "" ? "f" : "t" );
  setUserParameter( "use_svts"     , labelSVertices    == "" ? "f" : "t" );
  setUserParameter( "use_gen"      , labelGen          == "" ? "f" : "t" );

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

  if ( use_hlt       ) {
    ev.getByLabel( labelHLT      , hlt       );
    if ( hlt.isValid() ) triggerNames = &( ev.triggerNames( *hlt ) );
    fillTrigger     ();
  }
  if ( use_met       ) {
    ev.getByLabel( labelMets     , mets      );
    fillMet         ();
  }
  if ( use_muons     ) {
    ev.getByLabel( labelMuons    , muons     );
    fillMuons       ();
  }
  if ( use_electrons ) {
    ev.getByLabel( labelElectrons, electrons );
    fillElectrons   ();
  }
  if ( use_taus      ) {
    ev.getByLabel( labelTaus     , taus      );
    fillTaus        ();
  }
  if ( use_tracks    ) {
    ev.getByLabel( labelPFCandidates, pfCandidates );
    ev.getByLabel( labelGeneralTracks, generalTracks );
    fillTracks      ();
  }
  if ( use_jets      ) {
    ev.getByLabel( labelJets     , jets      );
    fillJets        ();
  }
  if ( use_pvts ) {
    ev.getByLabel( labelPVertices, pVertices );
    fillPVertices   ();
  }
  if ( use_svts ) {
    ev.getByLabel( labelSVertices, sVertices );
    fillSVertices   ();
  }
  if ( use_gen       ) {
    ev.getByLabel( labelGen      , particles );
    fillGenParticles();
  }

  if ( use_muons     ) {
    ev.getByLabel( labelMuons    , muons     );
    fillMuons       ();
  }

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


void BmmPATToNtuple::fillTrigger() {

  nHLT = 0;
  hltPath  ->clear();
  hltAccept->clear();
  if ( !hlt.isValid() ) {
    cout << "invalid HLT" << endl;
    return;
  }

  int nObj = triggerNames->size();
  int iObj;
  int iTrg;
  int nTrg = savedTriggers.size();
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const string& hltPathName = triggerNames->triggerName( iObj );
    for ( iTrg = 0; iTrg < nTrg; ++iTrg ) {
      const string& name = savedTriggers[iTrg];
      if ( ( name != "*" ) &&
           ( hltPathName.find( name, 0 ) != string::npos ) ) continue;
      ++nHLT;
      hltPath  ->push_back( name );
      hltAccept->push_back( hlt->accept( iObj ) );
    }
  }

  return;

}


void BmmPATToNtuple::fillMet() {

  mEt = -999.999;
  mEx = 0.0;
  mEy = 0.0;
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

  nMuons = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Muon& muon = *muonPtr[iObj];

    const Candidate::LorentzVector p4 = muon.p4();
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


void BmmPATToNtuple::fillTracks() {

  bool vTracks = pfCandidates.isValid();

  // store tracks info

  int iObj;
  int nObj = ( vTracks ? pfCandidates->size() : 0 );
  trkPt      ->resize( nObj );
  trkEta     ->resize( nObj );
  trkPhi     ->resize( nObj );
  trkPx      ->resize( nObj );
  trkPy      ->resize( nObj );
  trkPz      ->resize( nObj );
  trkE       ->resize( nObj );
  trkCharge  ->resize( nObj );
  trkJet     ->resize( nObj );
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

  if ( generalTracks.isValid() ) {
  trkMap.clear();
  int igtk;
  int ngtk = generalTracks->size();
  for ( igtk = 0; igtk < ngtk; ++igtk ) {
    const Track& gtk = generalTracks->at( igtk );
    trkMap.insert( make_pair( &gtk, 0 ) );
  }
  }

  pfcMap.clear();
  nTracks = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const PFCandidate& pfc = pfCandidates->at( iObj );
    pfcMap.insert( make_pair( &pfc, iObj ) );
    const Candidate::LorentzVector p4 = pfc.p4();

    trkPt      ->at( iObj ) = p4.pt    ();
    trkEta     ->at( iObj ) = p4.eta   ();
    trkPhi     ->at( iObj ) = p4.phi   ();
    trkPx      ->at( iObj ) = p4.px    ();
    trkPy      ->at( iObj ) = p4.py    ();
    trkPz      ->at( iObj ) = p4.pz    ();
    trkE       ->at( iObj ) = p4.energy();
    trkCharge  ->at( iObj ) = pfc.charge();
    trkJet     ->at( iObj ) = -1;
    trkPVtx    ->at( iObj ) = -1;
    trkSVtx    ->at( iObj ) = -1;

    trkQuality ->at( iObj ) = -999;
    trkNormChi2->at( iObj ) = -999.999;
    trkDxy     ->at( iObj ) = -999.999;
    trkDz      ->at( iObj ) = -999.999;

    const reco::TrackRef& trk = pfc.trackRef();
    try {
//    if ( trk.isNull() ) {
//    cout << "null ref" << endl;
//    }
//    else {
//    if ( !trk.isNull() ) {
//
    trkMap.insert( make_pair( &(*trk), iObj ) );
    trkQuality ->at( iObj ) = trk->qualityMask();
    trkNormChi2->at( iObj ) = trk->normalizedChi2();
    trkDxy     ->at( iObj ) = trk->dxy();
    trkDz      ->at( iObj ) = trk->dz();
//    }
    }
    catch ( edm::Exception e ) {
    trkQuality ->at( iObj ) = 0;
    trkNormChi2->at( iObj ) = -999.99;
    trkDxy     ->at( iObj ) =  999.99;
    trkDz      ->at( iObj ) =  999.99;
    }
  }

  return;

}


void BmmPATToNtuple::fillJets() {

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

  labelCSV  = "combinedSecondaryVertexBJetTags";
  labelTCHE = "trackCountingHighEffBJetTags";
  nJets = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

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

    const vector<PFCandidatePtr>& jPFC = jet.getPFConstituents();
    int nPFC = jPFC.size();
    int iPFC;
    map<const PFCandidate*,int>::const_iterator iter = pfcMap.begin();
    map<const PFCandidate*,int>::const_iterator iend = pfcMap.end();
    for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
      const PFCandidatePtr& pfp = jPFC.at( iPFC );
//      const reco::TrackRef& trk = pfp->trackRef();
//      if ( trk.isNull() ) cout << "null ref" << endl;
      iter = pfcMap.find( &(*pfp) );
      if ( iter != iend ) trkJet->at( iter->second ) = iObj;
/*
      if ( iter != iend ) cout << "pfc found for jet " << iObj << " "
                               << iter->second << endl;
      else                cout << "pfc missing for jet " << iObj
                               << endl;
*/
/*
      float dmin = 1.0e+37;
      int itk;
      int jtk = -1;
      for ( itk = 0; itk < nTracks; ++itk ) {
        float dist = sqrt( pow( trkPx->at( itk ) - pfp->p4().px(), 2 ) +
                           pow( trkPy->at( itk ) - pfp->p4().py(), 2 ) +
                           pow( trkPz->at( itk ) - pfp->p4().pz(), 2 ) );
        if ( dist < dmin ) {
          dmin = dist;
          jtk = itk;
        }
      }
      if ( jtk >= 0 ) trkJet->at( jtk ) = iObj;
*/
    }

  }

  return;

}


void BmmPATToNtuple::fillPVertices() {

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
//  cout << "******************** " << nObj << endl;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
//    cout << "--- " << iObj << endl;
    const Vertex& vtx = pVertices->at( iObj );
    pvtX         ->at( iObj ) = vtx.x();
    pvtY         ->at( iObj ) = vtx.y();
    pvtZ         ->at( iObj ) = vtx.z();
//    continue;
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
//        else cout << "pvtx tracks not found" << endl;
      }
    }
    catch ( edm::Exception e ) {
    }
  }


  return;

}


void BmmPATToNtuple::fillSVertices() {

  int nObj = sVertices->size();
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

  nSVertices = 0;

//  int igtk;
//  int ngtk = generalTracks->size();

  if ( nObj != nJets ) cout << "JETS-VTX: " << nObj << " " << nJets << endl;
  int iObj;
//  cout << "---- " << nObj << endl;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const SecondaryVertexTagInfo& secVtxTagInfo = sVertices->at( iObj );
//    if ( secVtxTagInfo.nVertices() <= 0 ) cout << "no vtx" << endl;
    if ( secVtxTagInfo.nVertices() <= 0 ) continue;
    const        Vertex& vtx = secVtxTagInfo.secondaryVertex( 0 );
    const  GlobalVector& dir = secVtxTagInfo.flightDirection( 0 );
    const Measurement1D& d2d = secVtxTagInfo.flightDistance( 0, true  );
    const Measurement1D& d3d = secVtxTagInfo.flightDistance( 0, false );
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

  return;

}


void BmmPATToNtuple::fillGenParticles() {

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

