
#ifndef BmmPATAnalyzer_h
#define BmmPATAnalyzer_h

#include "BmmAnalysis/NtuPAT/interface/BmmPATToNtuple.h"

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

class BmmPATAnalyzer: public edm::EDAnalyzer,
                      public BmmPATToNtuple {

 public:

  explicit BmmPATAnalyzer( const edm::ParameterSet& ps );
  ~BmmPATAnalyzer();

  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );
  virtual void beginJob();
  virtual void endJob();

 private:

  int analyzedFile;
  std::string histName;

  virtual void beginRun( const edm::Run& run , const edm::EventSetup& es );
  virtual void endRun(   const edm::Run& run , const edm::EventSetup& es );
  virtual void analyze(  const edm::Event& ev, const edm::EventSetup& es );

};

#endif
