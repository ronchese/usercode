#ifndef BmmPATToNtuple_h
#define BmmPATToNtuple_h

#include "BmmAnalysis/NtuPAT/interface/BmmNtuple.h"
#include "BmmAnalysis/NtuPAT/interface/BmmAnalyzerFW.h"
#include "NtuTool/Common/interface/TreeWriter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>
#include <vector>
class TFile;

namespace edm {
  class TriggerResults;
  class TriggerNames;
}

namespace pat {
  class TriggerEvent;
  class MET;
  class Muon;
  class Electron;
  class Tau;
//  class PFParticle;
  class Jet;
}

namespace reco {
  class BeamSpot;
  class PFCandidate;
  class Track;
  class Vertex;
  class SecondaryVertexTagInfo;
  class GenParticle;
}


class BmmPATToNtuple: public BmmAnalyzer,
                      public TreeWriter {

 public:

  BmmPATToNtuple( const edm::ParameterSet& ps );
  virtual ~BmmPATToNtuple();

  virtual void beginJob();
  virtual void openNtuple( const std::string& ntuName );
  virtual void analyze( const edm::EventBase& ev,
                        int ientry, int event_file );
  virtual void read( const edm::EventBase& ev );
  virtual void writeNtuple();
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

  edm::Handle< edm::TriggerResults                       > trigResults;
  edm::Handle< pat::TriggerEvent                         > trigEvent;
  edm::Handle< reco::BeamSpot                            > beamSpot;
  edm::Handle< std::vector<pat::MET                    > > mets;
  edm::Handle< std::vector<pat::Muon                   > > muons;
  edm::Handle< std::vector<pat::Electron               > > electrons;
  edm::Handle< std::vector<pat::Tau                    > > taus;
  edm::Handle< std::vector<pat::Jet                    > > jets;
//  edm::Handle< std::vector<pat::PFParticle             > > pfParticles;
  edm::Handle< std::vector<reco::PFCandidate           > > pfCandidates;
  edm::Handle< std::vector<reco::Track                 > > generalTracks;
  edm::Handle< std::vector<reco::Vertex                > > pVertices;
  edm::Handle< std::vector<reco::SecondaryVertexTagInfo> > sVertices;
  edm::Handle< std::vector<reco::GenParticle           > > particles;

  const edm::TriggerNames* triggerNames;
  std::vector<std::string> savedTriggerPaths;
  std::vector<std::string> savedTriggerObjects;

  std::map<const pat::Muon        *,int> muoMap;
  std::map<const pat::Electron    *,int> eleMap;
  std::map<const pat::Tau         *,int> tauMap;
  std::map<const pat::Jet         *,int> jetMap;
  std::map<const reco::PFCandidate*,int> pfcMap;
//  std::map<const reco::Track      *,int> pftMap;
  std::map<const reco::Track      *,int> trkMap;

  bool dumpNtuple;
  void fillHLTStatus   ();
  void fillHLTObjects  ();
  void fillBeamSpot    ();
  void fillMet         ();
  void fillMuons       ();
  void fillElectrons   ();
  void fillTaus        ();
  void fillJets        ();
  void fillPFCandidates();
  void fillTracks      ();
  void fillPVertices   ();
  void fillSVertices   ();
  void fillGenParticles();

  void linkMuTracks();
  void linkPFJets  ();
  void linkPFTracks();

};

#endif
