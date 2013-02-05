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
  static float invMass( float px1, float  py1, float  pz1, float mm1,
                        float px2, float  py2, float  pz2, float mm2 );
  static float invMass( float px1, float  py1, float  pz1, float mm1,
                        float px2, float  py2, float  pz2, float mm2,
                        float px3, float  py3, float  pz3, float mm3 );
  static float invMass( float px1, float  py1, float  pz1, float mm1,
                        float px2, float  py2, float  pz2, float mm2,
                        float px3, float  py3, float  pz3, float mm3,
                        float px4, float  py4, float  pz4, float mm4 );
  static float invMSph( float pt1, float eta1, float phi1, float mm1,
                        float pt2, float eta2, float phi2, float mm2 );
  static float invMSph( float pt1, float eta1, float phi1, float mm1,
                        float pt2, float eta2, float phi2, float mm2,
                        float pt3, float eta3, float phi3, float mm3 );
  static float invMSph( float pt1, float eta1, float phi1, float mm1,
                        float pt2, float eta2, float phi2, float mm2,
                        float pt3, float eta3, float phi3, float mm3,
                        float pt4, float eta4, float phi4, float mm4 );
  static float dSqua( float a1, float b1,
                      float a2, float b2 );
  static float dSqua( float a1, float b1, float c1,
                      float a2, float b2, float c2 );
  static float delta( float a1, float b1,
                      float a2, float b2 );
  static float delta( float a1, float b1, float c1,
                      float a2, float b2, float c2 );

  static void convCartSphe( number  x, number  y, number  z,
                            number& t, number& e, number& p );
  static void convSpheCart( number  t, number  e, number  p,
                            number& x, number& y, number& z );
  static void convCartSphe( const std::vector<number>* x,
                            const std::vector<number>* y,
                            const std::vector<number>* z,
                                  std::vector<number>* t,
                                  std::vector<number>* e,
                                  std::vector<number>* p, int i = -1 );
  static void convSpheCart( const std::vector<number>* t,
                            const std::vector<number>* e,
                            const std::vector<number>* p,
                                  std::vector<number>* x,
                                  std::vector<number>* y,
                                  std::vector<number>* z, int i = -1 );

 protected:

  const edm::ParameterSet* parameterSet ;
  const edm::EventBase   * currentEvBase;
  const edm::Event       * currentEvent;
  const edm::EventSetup  * currentEvSetup;

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

