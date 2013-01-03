#ifndef BmmPATToNtuple_h
#define BmmPATToNtuple_h

#include "BmmAnalysis/NtuPAT/interface/BmmNtuple.h"
#include "BmmAnalysis/NtuPAT/interface/BmmAnalyzerFW.h"
#include "NtuTool/Common/interface/TreeWriter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>
class TFile;

namespace edm {
  class TriggerResults;
}

namespace pat {
  class MET;
  class Muon;
//  class Electron;
//  class Tau;
  class Jet;
}

namespace reco {
  class GenParticle;
}


class BmmPATToNtuple: public BmmAnalyzer,
                      public TreeWriter {

 public:

  BmmPATToNtuple( const edm::ParameterSet& ps );
  virtual ~BmmPATToNtuple();

  virtual void beginJob();
  virtual void openNtuple( const std::string& ntuName );
  virtual void read( const edm::EventBase& ev );
  virtual void closeNtuple();
  virtual void endJob();

 private:

  std::string ntuName;
  TFile* file;

  template<class PATObject> class compareByPt {
   public:
    bool operator()( const PATObject* l, const PATObject* r ) {
      return l->pt() > r->pt();
    }
  };

  std::string labelHLT;
  std::string labelMets;
  std::string labelMuons;
//  std::string labelElectrons;
//  std::string labelTaus;
  std::string labelJets;
  std::string labelGen;

  std::string labelCSV;
  std::string labelTCHE;

  edm::Handle< edm::TriggerResults          > hlt;
  edm::Handle< std::vector<pat::MET         > > mets;
  edm::Handle< std::vector<pat::Muon        > > muons;
//  edm::Handle< std::vector<pat::Electron    > > electrons;
//  edm::Handle< std::vector<pat::Tau         > > taus;
  edm::Handle< std::vector<pat::Jet         > > jets;
  edm::Handle< std::vector<reco::GenParticle> > particles;

  void fillTrigger     ();
  void fillMet         ();
  void fillMuons       ();
//  void fillElectrons   ();
//  void fillTaus        ();
  void fillJets        ();
  void fillGenParticles();

};

#endif
