#ifndef TestBaseNtuple_h
#define TestBaseNtuple_h

#include "NtuTool/Common/test/stubs/SimpleNtuple.h"
#include "NtuTool/EDM/interface/EDMTreeWriter.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class TFile;

// to produce EDM ntuples the class must inherit from "EDMTreeWriter"
// "EDMTreeWriter" in turn inherits from EDProducer
// the ntuple definition is exactly in the same class "SimpleNtuple"

class TestSimpleEDMNtuple: public SimpleNtuple,
                           public EDMTreeWriter {

 public:

  explicit TestSimpleEDMNtuple( const edm::ParameterSet & );
  virtual ~TestSimpleEDMNtuple();

  virtual void beginJob();
  virtual void endJob();

  // the function
  //     void produce( edm::Event& ev, const edm::EventSetup& es );
  // is provided by the tool

 private:

  // the user code contained in the "analyze" function when 
  // writing standard trees in an EDAnalyzer is moved to 
  // a "fill" function called by the library
  virtual void fill( edm::Event &, const edm::EventSetup & );

  // function (by the user) to encapsulate operations to set variables
  void setData( unsigned int iRun );

};

#endif
