#ifndef BmmAnalyzerUtil_H
#define BmmAnalyzerUtil_H

#define FULL 2
#define BARE 3

namespace edm {
  class ParameterSet;
  class Event;
  class EventBase;
  class EventSetup;
}

#include "BmmAnalysis/NtuPAT/interface/BmmEventSelect.h"

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

  static float energy( float px, float py, float pz, float mm );
  static float invMass( float px1, float py1, float pz1, float mm1,
                        float px2, float py2, float pz2, float mm2 );
  static float invMSph( float px1, float py1, float pz1, float mm1,
                        float px2, float py2, float pz2, float mm2 );
  static float dSqua2( float a1, float b1,
                       float a2, float b2 );
  static float dSqua3( float a1, float b1, float c1,
                       float a2, float b2, float c2 );
  static float delta2( float a1, float b1,
                       float a2, float b2 );
  static float delta3( float a1, float b1, float c1,
                       float a2, float b2, float c2 );

 protected:

  const edm::ParameterSet* parameterSet ;
  const edm::EventBase   * currentEvBase;
  const edm::Event       * currentEvent;
  const edm::EventSetup  * currentEvSetup;

  virtual void beginJob();

  virtual void getEntry( int ientry );
  virtual void getEntry( TBranch* branch, int ientry );

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

