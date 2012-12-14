#ifndef HTTPATAnalyzer_h
#define HTTPATAnalyzer_h

#include "HTTAnalysis/NtuPAT/interface/HTTPATToNtuple.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>
#include <iostream>
#include <fstream>

//
// class declaration
//

class HTTPATAnalyzer: public edm::EDAnalyzer,
                      public HTTPATToNtuple {

 public:

  explicit HTTPATAnalyzer( const edm::ParameterSet& ps );
  ~HTTPATAnalyzer();

  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );
  void beginJob();
  void endJob();

 private:

  int analyzedFile;

  virtual void analyze( const edm::Event& ev, const edm::EventSetup& es );

};

#endif
