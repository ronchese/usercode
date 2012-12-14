#ifndef HTTAnalyzer_H
#define HTTAnalyzer_H

#define FULL 2
#define BARE 3

#include "TH1.h"

#  if UTIL_USE == FULL

// use the full utility to control ntuple files, event loop and 
// user parameters from command line
// "HTTNtuple"  contains the tree definition
// "TreeWrapper" is provided by the utility
// "TreeReader" is provided by the utility
#include "HTTAnalysis/NtuPAT/interface/HTTNtuple.h"
#include "NtuTool/Common/interface/TreeWrapper.h"
class HTTAnalyzer: public HTTNtuple,
                   public virtual TreeWrapper {

#elif UTIL_USE == BARE

// get the bare ntuple definition, with no usage of other utilities
// in addition to HTT specific ones
// "HTTLightNtuple" simply forward calls directly to ROOT with no 
// additional operation
#include "HTTLightNtuple.h"
class HTTAnalyzer: public HTTLightNtuple {

#else
#error use -D UTIL_USE=FULL or -D UTIL_USE=BARE
#endif

 public:

  HTTAnalyzer();
  virtual ~HTTAnalyzer();

  // function called before starting the analysis
  virtual void beginJob();

  // functions to book the histograms
  void book();

  // functions called for each event
  virtual bool analyze( int entry, int event_file );
  virtual bool analyze( int entry, int event_file, int event_tot );

  // function called at the end of the analysis
  virtual void endJob();

  // functions called at the end of the event loop
  virtual void plot();   // plot the histograms on the screen
  virtual void save();   // save the histograms on a ROOT file

  bool verbose;

  double eqlumi;

 private:

  // cuts to select good jets
  int    jetNDaumin;
  int    jetNDaumax;
  double jetNHFmin;
  double jetNHFmax;
  double jetNEFmin;
  double jetNEFmax;
  double jetCHFmin;
  double jetCHFmax;
  double jetCEFmin;
  double jetCEFmax;
  double jetNCHmin;
  double jetNCHmax;
  double jetEtaCut;

  // event counters
  double Nevents;
  double Nevents_2j;
  double Nevents_2j_2mu;
  double Nevents_2j_2e;
  double Nevents_2j_2l;
  double Nevents_2j_2l_1b;
  double Nevents_2j_2l_2b;
  double Nevents_2j_2l_met;

  double Nevents_simHLT_2j_2mu;
  double Nevents_simHLT_2j_2e;
  double Nevents_simHLT_2j_2l;
  double Nevents_simHLT_2j_2l_1b;
  double Nevents_simHLT_2j_2l_2b;
  double Nevents_simHLT_2j_2l_met;

  // selection cuts
  double JetEtCut;
  double JetEtaCut;
  double JetCSVLoose;
  double JetCSVMedium;
  double JetCSVTight;

  double Lep1PtCut;
  double Lep2PtCut;

  double MEtCut;

  // results
  double MEt;
  double Mjj;
  double Mmm;
  double Mee;
  double mh;

  double mZqq;
  double mZll;
  double mH;

  // histos
  TH1D* hptmuZmax;
  TH1D* hptmuZmin;
  TH1D* hetamax;
  TH1D* hMZgen;
  TH1D* hMZgenAcc;

  TH1D* nevents;
  TH1D* hptmumax;
  TH1D* hptmu2nd;
  TH1D* hptmu;
  TH1D* hptmusame;
  TH1D* hptmuopp;
  TH1D* hptmuisosame;
  TH1D* hptmuisosame1b;
  TH1D* hptmuisosame2b;
  TH1D* hetamuisosame;
  TH1D* hetamuisosame1b;
  TH1D* hetamuisosame2b;
  TH1D* hptmuisoopp;
  TH1D* hptmuisoopp1b;
  TH1D* hptmuisoopp2b;
  TH1D* hptmuisosameCR;
  TH1D* hmuiso;
  TH1D* hmuiso2nd;
  TH1D* hmuisosame;
  TH1D* hmuisoopp;
  TH1D* hmuisosameCR;
  TH1D* hmuDRsame;
  TH1D* hmuDRopp;
  TH1D* hmuDRsameCR;
  TH1D* hNtop;
  TH1D* hNW;
  TH1D* hNZ;
  TH1D* hNtaus;
  TH1D* hNmutop;
  TH1D* hNmutau;
  TH1D* hMTW;
  TH1D* hMET;
  TH1D* hMTWbjets;
  TH1D* hMTW2bjets;
  TH1D* hNbjets;
  TH1D* hM2mu;
  TH1D* hM2mub;
  TH1D* hM2leptSS;
  TH1D* hM2leptSSSF;
  TH1D* hM2leptOS;
  TH1D* hM2leptb;
  TH1D* hM2tau;
  TH1D* hNtaurec;
  TH1D* hpttausame;
  TH1D* hpttauopp;

  TH1D* hM2e;
  TH1D* hM2eb;

  TH1D* hMjjZe;
  TH1D* hMbbZe;
  TH1D* hMjjZmu;
  TH1D* hMbbZmu;

  TH1D* hMHmmjj;
  TH1D* hMHmmbb;

  TH1D* hMWjj;
  TH1D* hMWjjtop;

  TH1D* hpt3CR;
  TH1D* hptmu3CR;
  TH1D* hpte3CR;
  TH1D* hpt3isoCR;
  TH1D* hptmu3isoCR;
  TH1D* hpte3isoCR;

  TH1D* hMZ2;
  TH1D* hM4lept;

  // map to associate subdirectories and numbers
  // "Obj"     ---> 0
  // "simHLT"  ---> 1
  std::map<std::string,int> dirMap;

  // bi-dimensional arrays of TH1D pointers:
  // h_jet_pt[iDir][iJet] is a TH1D*

  int nMaxJet;
  TH1D*** h_jet_pt;
  TH1D*** h_jet_eta;
  TH1D*** h_jet_CSV;

  int nMaxLep;
  TH1D*** h_muon_pt;
  TH1D*** h_muon_eta;
  TH1D*** h_ele_pt;
  TH1D*** h_ele_eta;

  // uni-dimensional arrays of TH1D pointers:
  // h_met[iDir] is a TH1D*

  TH1D** h_met;

  TH1D** h_Mjj;
  TH1D** h_Mmm;
  TH1D** h_Mee;
  TH1D** h_Mll;
  TH1D** h_Mh;

  TH1D** h_mZqq;
  TH1D** h_mZll;
  TH1D** h_mH;



  // dummy copy and assignment constructors
  HTTAnalyzer( const HTTAnalyzer& );
  HTTAnalyzer& operator=( const HTTAnalyzer& );

  TH1D* createHisto( const std::string& head,
                     const std::string& tail, int n,
                     int nBin, double xMin, double xMax );
  bool goodJet( int iJet );
  void fillHistos( const std::string& name,
                   int Ngoodjets , int JetIdx[],
                   int Ngoodmuons, int  MuIdx[],
                   int Ngoodeles , int EleIdx[] );

};


#endif

