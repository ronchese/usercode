#ifndef BmmPATToNtuple_h
#define BmmPATToNtuple_h

#include "BmmAnalysis/NtuPAT/interface/BmmNtuple.h"
#include "BmmAnalysis/NtuPAT/interface/BmmAnalyzerFW.h"
#include "BmmAnalysis/NtuPAT/interface/BmmEnumString.h"

#include "NtuTool/Common/interface/TreeWriter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"

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

  std::string labelTrigResults;
  std::string labelTrigEvent;
  std::string labelBeamSpot;
  std::string labelMets;
  std::string labelMuons;
  std::string labelElectrons;
  std::string labelTaus;
  std::string labelJets;
  std::string labelPFCandidates;
  std::string labelGeneralTracks;
  std::string labelPVertices;
  std::string labelSVertices;
  std::string labelGen;

  bool read_hlts;
  bool read_hlto;
  bool read_bspot;
  bool read_met;
  bool read_muons;
  bool read_electrons;
  bool read_taus;
  bool read_jets;
  bool read_pflow;
  bool read_tracks;
  bool read_pvts;
  bool read_svts;
  bool read_gen;

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

  float jetPtMin;
  float jetEtaMax;
  float trkDzMax;
  float trkPtMin;
  float trkEtaMax;

  float dRmatchHLT;
  float dPmatchHLT;

  std::map<const pat::Muon        *,int> muoMap;
  std::map<const pat::Electron    *,int> eleMap;
  std::map<const pat::Tau         *,int> tauMap;
  std::map<const pat::Jet         *,int> jetMap;
  std::map<const reco::PFCandidate*,int> pcjMap;
  std::map<const reco::PFCandidate*,int> pfcMap;
  std::map<const reco::Track      *,int> tkmMap;
  std::map<const reco::Track      *,int> tkeMap;
  std::map<const reco::Track      *,int> tkpMap;
  std::map<const reco::Track      *,int> ptjMap;
  std::map<const reco::Track      *,int> tkvMap;
  std::map<const reco::Track      *,int> trkMap;
  std::set<const reco::Track      *    > tkrSet;
  std::set<const reco::Track      *    > allPTk;
  std::vector<const reco::Vertex*> vtxList;

  bool dumpNtuple;
  void fillHLTStatus   ();
  void fillHLTObjects  ();
  void fillBeamSpot    ();
  void fillMet         ();
  void fillMuons       ();
  void fillElectrons   ();
  void fillTaus        ();
  void fillJets        ();
  void fillVtxTrkMap   ();
  void fillPFCandidates();
  void fillTracks      ();
  void fillPVertices   ();
  void fillSVertices   ();
  void fillGenParticles();

  int addSecondaryVertex( const reco::Vertex& vtx,
                          const  GlobalVector& dir,
                          const Measurement1D& d2d,
                          const Measurement1D& d3d,
                          const std::string& type, int jetId );
  int addTrackIP(   int trkIndex, const reco::Track & trk,
                    int vtxIndex, const reco::Vertex& vtx );
  int addTrackVtxP( int tipIndex, const reco::Track & trk,
                                  const reco::Vertex& vtx );

  void linkMTracks();
//  void linkPFJets ();
  void linkPTracks();

  int nearestHLT( BmmEnumString::trigObject type,
                  double pt, double eta, double phi );

};

#endif
