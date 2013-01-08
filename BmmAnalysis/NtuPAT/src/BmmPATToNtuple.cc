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

//#include "DataFormats/PatCandidates/interface/PFParticle.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"

#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <map>


using edm::TriggerResults;
using pat::MET;
using pat::Muon;
using pat::Electron; 
using pat::Tau;
using pat::Jet;
//using pat::PFParticle;
using reco::PFCandidate;
using reco::GenParticle;

using namespace std;

BmmPATToNtuple::BmmPATToNtuple( const edm::ParameterSet& ps ) {
  ntuName = ps.getUntrackedParameter<std::string>( "ntuName" );
  labelHLT          = ps.getParameter<std::string>( "labelHLT"          );
  labelMets         = ps.getParameter<std::string>( "labelMets"         );
  labelMuons        = ps.getParameter<std::string>( "labelMuons"        );
  labelElectrons    = ps.getParameter<std::string>( "labelElectrons"    );
  labelTaus         = ps.getParameter<std::string>( "labelTaus"         );
  labelPFCandidates = ps.getParameter<std::string>( "labelPFCandidates" );
  labelJets         = ps.getParameter<std::string>( "labelJets"         );
  labelGen          = ps.getParameter<std::string>( "labelGen"          );
  setUserParameter( "use_mEt"      , labelMets         == "" ? "f" : "t" );
  setUserParameter( "use_muons"    , labelMuons        == "" ? "f" : "t" );
  setUserParameter( "use_electrons", labelElectrons    == "" ? "f" : "t" );
  setUserParameter( "use_taus"     , labelTaus         == "" ? "f" : "t" );
  setUserParameter( "use_tracks"   , labelPFCandidates == "" ? "f" : "t" );
  setUserParameter( "use_jets"     , labelJets         == "" ? "f" : "t" );
  setUserParameter( "use_gen"      , labelGen          == "" ? "f" : "t" );

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

  if ( use_mEt       ) {
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
    fillTracks      ();
  }
  if ( use_jets      ) {
    ev.getByLabel( labelJets     , jets      );
    fillJets        ();
  }
  if ( use_gen       ) {
    ev.getByLabel( labelGen      , particles );
    fillGenParticles();
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

  mEt = -999.999;
  mEx = 0.0;
  mEy = 0.0;
  if ( !mets.isValid() ) return;

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
  if ( !vMuons ) return;

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

    muoNumMatches  ->at( iObj ) = muon.numberOfMatchedStations();
    muoDb          ->at( iObj ) = muon.dB();

    muoNumValidHits->at( iObj ) = 0;
    muoNormChi2    ->at( iObj ) = 0.0;
    muoNumMuHits   ->at( iObj ) = 0;
    muoNumPixHits  ->at( iObj ) = 0;
    muoNumTkHits   ->at( iObj ) = 0;

    if ( !( muon. isGlobalMuon() ) ) continue;
    if ( !( muon.isTrackerMuon() ) ) continue;
//    const reco::TrackRef&  innerTrack = muon. innerTrack();
    const reco::TrackRef& globalTrack = muon.globalTrack();
    const reco::HitPattern& hitPattern = globalTrack->hitPattern();
//    muoNumValidHits->at( iObj ) =  innerTrack->numberOfValidHits();
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
  if ( !vElectrons ) return;

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
  if ( !vTaus ) return;

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
  trkQuality ->resize( nObj );
  trkNormChi2->resize( nObj );
  trkDxy     ->resize( nObj );
  trkDz      ->resize( nObj );
  if ( !vTracks ) return;

  pfcMap.clear();
  nTracks = nObj;
  for ( iObj = 0; iObj < nObj; iObj++ ) {

    const PFCandidate& pfc = pfCandidates->at( iObj );
    pfcMap.insert( make_pair( &pfc, iObj ) );
    const reco::Candidate::LorentzVector p4 = pfc.p4();

    trkPt      ->at( iObj ) = p4.pt    ();
    trkEta     ->at( iObj ) = p4.eta   ();
    trkPhi     ->at( iObj ) = p4.phi   ();
    trkPx      ->at( iObj ) = p4.px    ();
    trkPy      ->at( iObj ) = p4.py    ();
    trkPz      ->at( iObj ) = p4.pz    ();
    trkE       ->at( iObj ) = p4.energy();
    trkCharge  ->at( iObj ) = pfc.charge();
    trkJet     ->at( iObj ) = -1;

    trkQuality ->at( iObj ) = -999;
    trkNormChi2->at( iObj ) = -999.999;
    trkDxy     ->at( iObj ) = -999.999;
    trkDz      ->at( iObj ) = -999.999;
/*
    const reco::TrackRef& trk = pfc.trackRef();
    if ( trk.isNull() ) continue;
//    trkMap.insert( make_pair( &(*trk), iObj ) );
    trkQuality ->at( iObj ) = trk->qualityMask();
    trkNormChi2->at( iObj ) = trk->normalizedChi2();
    trkDxy     ->at( iObj ) = trk->dxy();
    trkDz      ->at( iObj ) = trk->dz();
*/

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
  if ( !vJets ) return;

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

    const std::vector<reco::PFCandidatePtr>& jPFC = jet.getPFConstituents();
    int nPFC = jPFC.size();
    int iPFC;
//    std::map<const reco::PFCandidate*,int>::const_iterator iter =
//                                                           pfcMap.begin();
//    std::map<const reco::PFCandidate*,int>::const_iterator iend =
//                                                           pfcMap.end();
    for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
      const reco::PFCandidatePtr& pfp = jPFC.at( iPFC );
//      iter = pfcMap.find( &(*pfp) );
//      if ( iter != iend ) std::cout << "pfc found for jet " << iObj << " "
//                                    << iter->second << std::endl;
//      else                std::cout << "pfc missing for jet " << iObj
//                                    << std::endl;
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
    }

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
  if ( !vGen ) return;

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

