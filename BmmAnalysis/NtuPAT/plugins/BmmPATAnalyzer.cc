#include "BmmAnalysis/NtuPAT/plugins/BmmPATAnalyzer.h"

// system include files
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "TFile.h"

BmmPATAnalyzer::BmmPATAnalyzer( const edm::ParameterSet& ps ):
  BmmPATToNtuple( ps ) {
}

BmmPATAnalyzer::~BmmPATAnalyzer() {
}

void BmmPATAnalyzer::beginJob() {
  BmmPATToNtuple::beginJob();
  analyzedFile = 0;
  return;
}

void BmmPATAnalyzer::endJob()  {
  BmmPATToNtuple::endJob();
  TreeWrapper::save( "hist.root" );
  return;
}

void BmmPATAnalyzer::fillDescriptions( edm::ConfigurationDescriptions&
                                            descriptions ) {
  // The following says we do not know what parameters are allowed 
  // so do no validation
  // Please change this to state exactly what you do use, even 
  // if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault( desc );
  return;
}


void BmmPATAnalyzer::analyze( const edm::Event& ev,
                              const edm::EventSetup& es ) {
  read( ev );
  int ientry = 0;
  if ( BmmPATToNtuple::analyze( ientry, analyzedFile++, analyzedEvts++ ) ) 
                                                        acceptedEvts++;
  return;
}

//define this as a plug-in
DEFINE_FWK_MODULE( BmmPATAnalyzer );
