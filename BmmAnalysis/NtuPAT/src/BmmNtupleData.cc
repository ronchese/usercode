#include <iostream>

#include "BmmAnalysis/NtuPAT/interface/BmmNtupleData.h"

BmmNtupleData::BmmNtupleData() {

  // hlt status
  use_hlts = false;
  hltPath         = new std::vector<std::string>;
  hltRun          = new std::vector<bool       >;
  hltAccept       = new std::vector<bool       >;

  // hlt objects
  use_hlto = false;
  hltObjType      = new std::vector<std::string>;
  hltPt           = new std::vector<double     >;
  hltEta          = new std::vector<double     >;
  hltPhi          = new std::vector<double     >;
  hltPx           = new std::vector<double     >;
  hltPy           = new std::vector<double     >;
  hltPz           = new std::vector<double     >;
  hltE            = new std::vector<double     >;

  // beam spot
  use_bspot = false;

  // met
  use_met = false;

  // muons
  use_muons = false;
  nMuons = 0;
  muoPt           = new std::vector<double>;
  muoEta          = new std::vector<double>;
  muoPhi          = new std::vector<double>;
  muoPx           = new std::vector<double>;
  muoPy           = new std::vector<double>;
  muoPz           = new std::vector<double>;
  muoE            = new std::vector<double>;
  muoCharge       = new std::vector<int   >;
  muoTrk          = new std::vector<int   >;
  muoTrg          = new std::vector<int   >;
  muoChaIso       = new std::vector<double>;
  muoNeuIso       = new std::vector<double>;
  muoPhoIso       = new std::vector<double>;
  muoSumCHpt      = new std::vector<double>;
  muoSumCPpt      = new std::vector<double>;
  muoSumNHet      = new std::vector<double>;
  muoSumPHet      = new std::vector<double>;
  muoSumPUpt      = new std::vector<double>;
  muoNumMatches   = new std::vector<double>;
  muoDb           = new std::vector<double>;
  muoNumValidHits = new std::vector<int   >;
  muoNormChi2     = new std::vector<double>;
  muoNumMuHits    = new std::vector<int   >;
  muoNumPixHits   = new std::vector<int   >;
  muoNumTkHits    = new std::vector<int   >;

  // electrons
  use_electrons = false;
  nElectrons = 0;
  elePt           = new std::vector<double>;
  eleEta          = new std::vector<double>;
  elePhi          = new std::vector<double>;
  elePx           = new std::vector<double>;
  elePy           = new std::vector<double>;
  elePz           = new std::vector<double>;
  eleE            = new std::vector<double>;
  eleCharge       = new std::vector<int   >;
  eleTrk          = new std::vector<int   >;
  eleTrg          = new std::vector<int   >;
  eleChaIso       = new std::vector<double>;
  eleNeuIso       = new std::vector<double>;
  elePhoIso       = new std::vector<double>;
  eleAbsEta       = new std::vector<double>;
  eleAEff         = new std::vector<double>;
  eleID           = new std::vector<int   >;
  eleConsCha      = new std::vector<bool  >;
  eleEBEEGap      = new std::vector<bool  >;
  eleDb           = new std::vector<double>;

  // taus
  use_taus = false;
  nTaus = 0;
  tauPt           = new std::vector<double>;
  tauEta          = new std::vector<double>;
  tauPhi          = new std::vector<double>;
  tauPx           = new std::vector<double>;
  tauPy           = new std::vector<double>;
  tauPz           = new std::vector<double>;
  tauE            = new std::vector<double>;
  tauCharge       = new std::vector<int   >;
  tauTrg          = new std::vector<int   >;

  // jets
  use_jets = false;
  nJets = 0;
  jetPt           = new std::vector<double>;
  jetEta          = new std::vector<double>;
  jetPhi          = new std::vector<double>;
  jetPx           = new std::vector<double>;
  jetPy           = new std::vector<double>;
  jetPz           = new std::vector<double>;
  jetE            = new std::vector<double>;
  jetCSV          = new std::vector<double>;
  jetTCHE         = new std::vector<double>;
  jetTrg          = new std::vector<int   >;
  jetPF           = new std::vector<bool  >;
  jetNDau         = new std::vector<int   >;
  jetNHF          = new std::vector<double>;
  jetNEF          = new std::vector<double>;
  jetCHF          = new std::vector<double>;
  jetCEF          = new std::vector<double>;
  jetNCH          = new std::vector<double>;

  // particle flow
  use_pflow = false;
  nPF = 0;
  pfcPt           = new std::vector<double>;
  pfcEta          = new std::vector<double>;
  pfcPhi          = new std::vector<double>;
  pfcPx           = new std::vector<double>;
  pfcPy           = new std::vector<double>;
  pfcPz           = new std::vector<double>;
  pfcE            = new std::vector<double>;
  pfcCharge       = new std::vector<int   >;
  pfcJet          = new std::vector<int   >;
  pfcTrk          = new std::vector<int   >;

  // tracks
  use_tracks = false;
  nTracks = 0;
  trkPt           = new std::vector<double>;
  trkEta          = new std::vector<double>;
  trkPhi          = new std::vector<double>;
  trkPx           = new std::vector<double>;
  trkPy           = new std::vector<double>;
  trkPz           = new std::vector<double>;
  trkCharge       = new std::vector<int   >;
  trkPFC          = new std::vector<int   >;
  trkJet          = new std::vector<int   >;
  trkPVtx         = new std::vector<int   >;
  trkSVtx         = new std::vector<int   >;
  trkQuality      = new std::vector<int   >;
  trkNormChi2     = new std::vector<double>;
  trkDxy          = new std::vector<double>;
  trkDz           = new std::vector<double>;

  // primary vertices
  use_pvts =  false;
  nPVertices = 0;
  pvtX            = new std::vector<double>;
  pvtY            = new std::vector<double>;
  pvtZ            = new std::vector<double>;
  pvtSxx          = new std::vector<double>;
  pvtSyy          = new std::vector<double>;
  pvtSzz          = new std::vector<double>;
  pvtSxy          = new std::vector<double>;
  pvtSxz          = new std::vector<double>;
  pvtSyz          = new std::vector<double>;
//  pvtCovariance   = new std::vector<
//                        std::vector<double>
//                                          >;
  pvtNTracks      = new std::vector<int   >;
  pvtNormChi2     = new std::vector<double>;
  pvtBadQuality   = new std::vector<int   >;

  // secondary vertices
  use_svts = false;
  nSVertices = 0;
  svtX          = new std::vector<double>;
  svtY          = new std::vector<double>;
  svtZ          = new std::vector<double>;
  svtSxx        = new std::vector<double>;
  svtSyy        = new std::vector<double>;
  svtSzz        = new std::vector<double>;
  svtSxy        = new std::vector<double>;
  svtSxz        = new std::vector<double>;
  svtSyz        = new std::vector<double>;
  svtDirX       = new std::vector<double>;
  svtDirY       = new std::vector<double>;
  svtDirZ       = new std::vector<double>;
  svtType       = new std::vector<std::string>;
  svtNTracks    = new std::vector<int   >;
  svtNormChi2   = new std::vector<double>;
  svtMass       = new std::vector<double>;
  svtDist2D     = new std::vector<double>;
  svtSign2D     = new std::vector<double>;
  svtDist3D     = new std::vector<double>;
  svtSign3D     = new std::vector<double>;
  svtJet        = new std::vector<int   >;
  svtBadQuality = new std::vector<int   >;

  // impact parameters
  use_ips = false;
  nTkIPs = 0;
  tipTrk          = new std::vector<int   >;
  tipSVtx         = new std::vector<int   >;
  tipDxy          = new std::vector<double>;
  tipDz           = new std::vector<double>;

  // momenta at vertices
  use_vtxp = false;
  nVtxPs = 0;
  tvpTrk          = new std::vector<int   >;
//  tvpPt           = new std::vector<double>;
//  tvpEta          = new std::vector<double>;
//  tvpPhi          = new std::vector<double>;
  tvpPx           = new std::vector<double>;
  tvpPy           = new std::vector<double>;
  tvpPz           = new std::vector<double>;

  // gen particles
  use_gen = false;
  nGenP = 0;
  genId           = new std::vector<int   >;
  genStatus       = new std::vector<int   >;
  genMother       = new std::vector<int   >;
  genPt           = new std::vector<double>;
  genEta          = new std::vector<double>;
  genPhi          = new std::vector<double>;
  genPx           = new std::vector<double>;
  genPy           = new std::vector<double>;
  genPz           = new std::vector<double>;
  genE            = new std::vector<double>;
  genCharge       = new std::vector<int   >;
  genMass         = new std::vector<double>;

}

BmmNtupleData::~BmmNtupleData() {
}


