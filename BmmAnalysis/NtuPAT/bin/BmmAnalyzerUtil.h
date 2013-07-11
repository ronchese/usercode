#ifndef BmmAnalyzerUtil_H
#define BmmAnalyzerUtil_H

#define FULL 2
#define BARE 3

namespace edm {
  class ParameterSet;
  class Run;
  class Event;
  class EventBase;
  class EventSetup;
}

#include "BmmAnalysis/NtuPAT/interface/BmmEventSelect.h"
class BmmTrigPathMap;

#  if UTIL_USE == FULL

#include "BmmAnalysis/NtuPAT/interface/BmmNtuple.h"
class BmmAnalyzerUtil: public BmmNtuple,
                       public BmmEventSelect {

#elif UTIL_USE == BARE

// get the bare ntuple definition, with no usage of other utilities
// in addition to Bmm specific ones
// "TreeLightReader" simply forward calls directly to ROOT with no 
// additional operation
#include "BmmLightNtuple.h"
class BmmAnalyzerUtil: public BmmLightNtuple,
                       public BmmEventSelect {

#else
#error use -D UTIL_USE=FULL or -D UTIL_USE=BARE
#endif

 public:

  BmmAnalyzerUtil();
  virtual ~BmmAnalyzerUtil();

 protected:

  const edm::ParameterSet* parameterSet ;
  const edm::Run         * currentRun;
  const edm::Event       * currentEvent;
  const edm::EventBase   * currentEvBase;
  const edm::EventSetup  * currentEvSetup;

  const BmmTrigPathMap* trigMap;

  // function called before starting the analysis
  virtual void beginJob();

  virtual void getEntry( int ientry );
  virtual void getEntry( TBranch* branch, int ientry );

  int findSVtx( int trkIndex, int prevSVtx = -1 );
  bool goodJet( unsigned int iJet );

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

  // dummy copy and assignment constructors
  BmmAnalyzerUtil( const BmmAnalyzerUtil& );
  BmmAnalyzerUtil& operator=( const BmmAnalyzerUtil& );

};


#endif

