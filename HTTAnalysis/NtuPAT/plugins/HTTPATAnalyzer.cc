#include "HTTAnalysis/NtuPAT/plugins/HTTPATAnalyzer.h"

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

HTTPATAnalyzer::HTTPATAnalyzer( const edm::ParameterSet& ps ):
  HTTPATToNtuple( ps ) {
}

HTTPATAnalyzer::~HTTPATAnalyzer() {
}

void HTTPATAnalyzer::beginJob() {
  HTTPATToNtuple::beginJob();
  analyzedFile = 0;
  return;
}

void HTTPATAnalyzer::endJob()  {
  HTTPATToNtuple::endJob();
  TreeWrapper::save( "hist.root" );
  return;
}

void HTTPATAnalyzer::fillDescriptions( edm::ConfigurationDescriptions&
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


void HTTPATAnalyzer::analyze( const edm::Event& ev,
                              const edm::EventSetup& es ) {
  read( ev );
  int ientry = 0;
  if ( HTTPATToNtuple::analyze( ientry, analyzedFile++, analyzedEvts++ ) ) 
                                                        acceptedEvts++;
  return;

}

//define this as a plug-in
DEFINE_FWK_MODULE( HTTPATAnalyzer );
