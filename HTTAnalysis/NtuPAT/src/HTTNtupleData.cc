#include <iostream>

#include "HTTAnalysis/NtuPAT/interface/HTTNtupleData.h"

HTTNtupleData::HTTNtupleData() {

  // muons
  muoPt           = new std::vector<double>;
  muoEta          = new std::vector<double>;
  muoPhi          = new std::vector<double>;
  muoPx           = new std::vector<double>;
  muoPy           = new std::vector<double>;
  muoPz           = new std::vector<double>;
  muoE            = new std::vector<double>;
  muoCharge       = new std::vector<int   >;
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
  muoNumValidHits = new std::vector<double>;
  muoNormChi2     = new std::vector<double>;
  muoNumMuHits    = new std::vector<double>;
  muoNumPixHits   = new std::vector<double>;
  muoNumTkHits    = new std::vector<double>;
  muoIso          = new std::vector<double>;
  muoClass        = new std::vector<int   >;

  // electrons
  elePt           = new std::vector<double>;
  eleEta          = new std::vector<double>;
  elePhi          = new std::vector<double>;
  elePx           = new std::vector<double>;
  elePy           = new std::vector<double>;
  elePz           = new std::vector<double>;
  eleE            = new std::vector<double>;
  eleCharge       = new std::vector<int   >;
  eleChaIso       = new std::vector<double>;
  eleNeuIso       = new std::vector<double>;
  elePhoIso       = new std::vector<double>;
  eleAbsEta       = new std::vector<double>;
  eleAEff         = new std::vector<double>;
//  eleLPt          = new std::vector<double>;
  eleID           = new std::vector<int   >;
  eleConsCha      = new std::vector<bool  >;
  eleEBEEGap      = new std::vector<bool  >;
  eleDb           = new std::vector<double>;
  eleIso          = new std::vector<double>;
  eleClass        = new std::vector<int   >;

  // taus
  tauPt           = new std::vector<double>;
  tauEta          = new std::vector<double>;
  tauPhi          = new std::vector<double>;
  tauPx           = new std::vector<double>;
  tauPy           = new std::vector<double>;
  tauPz           = new std::vector<double>;
  tauE            = new std::vector<double>;
  tauCharge       = new std::vector<int   >;

  // jets
  jetPt           = new std::vector<double>;
  jetEta          = new std::vector<double>;
  jetPhi          = new std::vector<double>;
  jetPx           = new std::vector<double>;
  jetPy           = new std::vector<double>;
  jetPz           = new std::vector<double>;
  jetE            = new std::vector<double>;
  jetCSV          = new std::vector<double>;
  jetTCHE         = new std::vector<double>;
  jetPF           = new std::vector<bool  >;
  jetNDau         = new std::vector<int   >;
  jetNHF          = new std::vector<double>;
  jetNEF          = new std::vector<double>;
  jetCHF          = new std::vector<double>;
  jetCEF          = new std::vector<double>;
  jetNCH          = new std::vector<double>;

  // gen particles
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

HTTNtupleData::~HTTNtupleData() {
}


