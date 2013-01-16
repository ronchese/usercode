#ifndef BmmAnalyzer_H
#define BmmAnalyzer_H

#define FULL 2
#define BARE 3

namespace edm {
  class Event;
  class EventBase;
  class EventSetup;
}

#include "TH1.h"
#include "BmmAnalysis/NtuPAT/interface/BmmEventSelect.h"

#  if UTIL_USE == FULL

// use the full utility to control ntuple files, event loop and 
// user parameters from command line
// "BmmNtuple"  contains the tree definition
// "TreeWrapper" is provided by the utility
#include "BmmAnalysis/NtuPAT/interface/BmmNtuple.h"
#include "NtuTool/Common/interface/TreeWrapper.h"
class BmmAnalyzer: public BmmNtuple,
                   public BmmEventSelect,
                   public virtual TreeWrapper {

#elif UTIL_USE == BARE

// get the bare ntuple definition, with no usage of other utilities
// in addition to Bmm specific ones
// "BmmLightNtuple" simply forward calls directly to ROOT with no 
// additional operation
#include "BmmLightNtuple.h"
class BmmAnalyzer: public BmmLightNtuple,
                   public BmmEventSelect {

#else
#error use -D UTIL_USE=FULL or -D UTIL_USE=BARE
#endif

 public:

  BmmAnalyzer();
  virtual ~BmmAnalyzer();

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

 protected:

  const edm::EventBase * currentEvBase;
  const edm::Event     * currentEvent;
  const edm::EventSetup* currentEvSetup;

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

  TH1D* hptmumax;
  TH1D* hptmu2nd;
  TH1D* hptmu;

  // dummy copy and assignment constructors
  BmmAnalyzer( const BmmAnalyzer& );
  BmmAnalyzer& operator=( const BmmAnalyzer& );

  bool goodJet( int iJet );

};


#endif

