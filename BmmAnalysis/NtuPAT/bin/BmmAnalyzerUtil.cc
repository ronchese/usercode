#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "BmmAnalyzerUtil.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
#include "Math/LorentzVector.h"

using namespace std;

BmmAnalyzerUtil::BmmAnalyzerUtil() {

  parameterSet = 0;
  currentEvBase  = 0;
  currentEvent   = 0;
  currentEvSetup = 0;

  // user parameters are set as names associated to a string, 
  // default values can be set in the analyzer class contructor

  setUserParameter( "use_hlts"     , "true"  );
  setUserParameter( "use_hlto"     , "true"  );
  setUserParameter( "use_bspot"    , "true"  );
  setUserParameter( "use_met"      , "true"  );
  setUserParameter( "use_muons"    , "true"  );
  setUserParameter( "use_electrons", "false" );
  setUserParameter( "use_taus"     , "false" );
  setUserParameter( "use_jets"     , "true"  );
  setUserParameter( "use_pflow"    , "true"  );
  setUserParameter( "use_tracks"   , "true"  );
  setUserParameter( "use_pvts"     , "true"  );
  setUserParameter( "use_svts"     , "true"  );
  setUserParameter( "use_tkips"    , "true"  );
  setUserParameter( "use_vtxps"    , "true"  );
  setUserParameter( "use_gen"      , "false" );

  setUserParameter( "use_hlto_sphe"     , "true"  );
  setUserParameter( "use_hlto_cart"     , "false" );
  setUserParameter( "use_muons_sphe"    , "true"  );
  setUserParameter( "use_muons_cart"    , "false" );
  setUserParameter( "use_electrons_sphe", "true"  );
  setUserParameter( "use_electrons_cart", "false" );
  setUserParameter( "use_taus_sphe"     , "true"  );
  setUserParameter( "use_taus_cart"     , "false" );
  setUserParameter( "use_jets_sphe"     , "true"  );
  setUserParameter( "use_jets_cart"     , "false" );
  setUserParameter( "use_pflow_sphe"    , "true"  );
  setUserParameter( "use_pflow_cart"    , "false" );
  setUserParameter( "use_tracks_sphe"   , "true"  );
  setUserParameter( "use_tracks_cart"   , "false" );
  setUserParameter( "use_vtxps_sphe"    , "true"  );
  setUserParameter( "use_vtxps_cart"    , "false" );
  setUserParameter( "use_gen_sphe"      , "true"  );
  setUserParameter( "use_gen_cart"      , "false" );

  setUserParameter( "jetNDaumin",  "1" );
  setUserParameter( "jetNDaumax",  "999999999" );
  setUserParameter( "jetNHFmin" , "-999999999.999" );
  setUserParameter( "jetNHFmax" ,  "0.99" );
  setUserParameter( "jetNEFmin" , "-999999999.999" );
  setUserParameter( "jetNEFmax" ,  "0.99" );
  setUserParameter( "jetCHFmin" ,  "0.0" );
  setUserParameter( "jetCHFmax" ,  "999999999.999" );
  setUserParameter( "jetCEFmin" , "-999999999.999" );
  setUserParameter( "jetCEFmax" ,  "0.99" );
  setUserParameter( "jetNCHmin" ,  "0" );
  setUserParameter( "jetNCHmax" ,  "999999999" );
  setUserParameter( "jetEtaCut" , "2.4" );

}


BmmAnalyzerUtil::~BmmAnalyzerUtil() {
}



void BmmAnalyzerUtil::beginJob() {

  // user parameters are retrieved as strings by using their names;
  // numeric parameters ( int, float or whatever ) can be directly set
  // by passing the corresponding variable,
  // e.g. getUserParameter( "name", x )

  getUserParameter( "use_hlts"     , use_hlts      );
  getUserParameter( "use_hlto"     , use_hlto      );
  getUserParameter( "use_bspot"    , use_bspot     );
  getUserParameter( "use_met"      , use_met       );
  getUserParameter( "use_muons"    , use_muons     );
  getUserParameter( "use_electrons", use_electrons );
  getUserParameter( "use_taus"     , use_taus      );
  getUserParameter( "use_jets"     , use_jets      );
  getUserParameter( "use_pflow"    , use_pflow     );
  getUserParameter( "use_tracks"   , use_tracks    );
  getUserParameter( "use_pvts"     , use_pvts      );
  getUserParameter( "use_svts"     , use_svts      );
  getUserParameter( "use_tkips"    , use_tkips     );
  getUserParameter( "use_vtxps"    , use_vtxps     );
  getUserParameter( "use_gen"      , use_gen       );
  if ( !use_jets ) use_svts = false;
  if ( !use_svts ) { use_tkips = false;
                     use_tkips = false; }
  getUserParameter( "use_hlto_sphe"     , use_hlto_sphe      );
  getUserParameter( "use_hlto_cart"     , use_hlto_cart      );
  getUserParameter( "use_muons_sphe"    , use_muons_sphe     );
  getUserParameter( "use_muons_cart"    , use_muons_cart     );
  getUserParameter( "use_electrons_sphe", use_electrons_sphe );
  getUserParameter( "use_electrons_cart", use_electrons_cart );
  getUserParameter( "use_taus_sphe"     , use_taus_sphe      );
  getUserParameter( "use_taus_cart"     , use_taus_cart      );
  getUserParameter( "use_jets_sphe"     , use_jets_sphe      );
  getUserParameter( "use_jets_cart"     , use_jets_cart      );
  getUserParameter( "use_pflow_sphe"    , use_pflow_sphe     );
  getUserParameter( "use_pflow_cart"    , use_pflow_cart     );
  getUserParameter( "use_tracks_sphe"   , use_tracks_sphe    );
  getUserParameter( "use_tracks_cart"   , use_tracks_cart    );
  getUserParameter( "use_vtxps_sphe"    , use_vtxps_sphe     );
  getUserParameter( "use_vtxps_cart"    , use_vtxps_cart     );
  getUserParameter( "use_gen_sphe"      , use_gen_sphe       );
  getUserParameter( "use_gen_cart"      , use_gen_cart       );

  initTree();
  read( getUserParameter( "eventList" ) );

  getUserParameter( "jetNDaumin", jetNDaumin );
  getUserParameter( "jetNDaumax", jetNDaumax );
  getUserParameter( "jetNHFmin" , jetNHFmin );
  getUserParameter( "jetNHFmax" , jetNHFmax );
  getUserParameter( "jetNEFmin" , jetNEFmin );
  getUserParameter( "jetNEFmax" , jetNEFmax );
  getUserParameter( "jetCHFmin" , jetCHFmin );
  getUserParameter( "jetCHFmax" , jetCHFmax );
  getUserParameter( "jetCEFmin" , jetCEFmin );
  getUserParameter( "jetCEFmax" , jetCEFmax );
  getUserParameter( "jetNCHmin" , jetNCHmin );
  getUserParameter( "jetNCHmax" , jetNCHmax );
  getUserParameter( "jetEtaCut" , jetEtaCut );

  return;

}


void BmmAnalyzerUtil::getEntry( int ientry ) {
//  cout << "BmmAnalyzer::getEntry" << endl;
  b_runNumber  ->GetEntry( ientry );
  b_lumiSection->GetEntry( ientry );
  b_eventNumber->GetEntry( ientry );
  if ( !find( runNumber, eventNumber ) ) return;
  currentTree->GetEntry( ientry );
  return;
}


void BmmAnalyzerUtil::getEntry( TBranch* branch, int ientry ) {
  if ( currentEvBase != 0 ) return;
  if ( currentEvent  != 0 ) return;
  branch->GetEntry( ientry );
  return;
}


bool BmmAnalyzerUtil::goodJet( unsigned int iJet ) {
  if ( iJet >= jetPF->size() ) return false;
  if ( jetPF->at( iJet ) ) {
    if ( jetNDau->at( iJet ) <= jetNDaumin ) return false;
    if ( jetNEF ->at( iJet ) >  jetNEFmax  ) return false;
    if ( jetNHF ->at( iJet ) >  jetNHFmax  ) return false;
    if ( fabs( jetEta->at( iJet ) ) <= jetEtaCut ) {
      if ( jetNCH->at( iJet ) <= jetNCHmin ) return false;
      if ( jetCEF->at( iJet ) >  jetCEFmax ) return false;
      if ( jetCHF->at( iJet ) <= jetCHFmin ) return false;
    }
  }
  return true;
}


int BmmAnalyzerUtil::findSVtx( int trkIndex, int prevSVtx ) {
  int svtIndex;
  int tipIndex;
  int tvpIndex;
  for ( tvpIndex = 0; tvpIndex < nVtxPs; ++tvpIndex ) {
    tipIndex = tvpTrk->at( tvpIndex );
    if ( tipIndex < 0 ) continue;
    if ( ( ( svtIndex = tipSVtx->at( tipIndex ) ) > prevSVtx ) &&
         (              tipTrk ->at( tipIndex )  == trkIndex ) )
       return svtIndex;
  }
  return -1;
}


float BmmAnalyzerUtil::energy( float px, float py, float pz, float mm ) {
  return sqrt( ( px * px ) + ( py * py ) + ( pz * pz ) + ( mm * mm ) );
}


float BmmAnalyzerUtil::invMass( float px1, float py1,
                                float pz1, float mm1,
                                float px2, float py2,
                                float pz2, float mm2 ) {
  float pxt = px1 + px2;
  float pyt = py1 + py2;
  float pzt = pz1 + pz2;
  float eet = energy( px1, py1, pz1, mm1 ) +
              energy( px2, py2, pz2, mm2 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


float BmmAnalyzerUtil::invMass( float px1, float py1,
                                float pz1, float mm1,
                                float px2, float py2,
                                float pz2, float mm2,
                                float px3, float py3,
                                float pz3, float mm3 ) {
  float pxt = px1 + px2 + px3;
  float pyt = py1 + py2 + py3;
  float pzt = pz1 + pz2 + pz3;
  float eet = energy( px1, py1, pz1, mm1 ) +
              energy( px2, py2, pz2, mm2 ) +
              energy( px3, py3, pz3, mm3 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


float BmmAnalyzerUtil::invMass( float px1, float py1,
                                float pz1, float mm1,
                                float px2, float py2,
                                float pz2, float mm2,
                                float px3, float py3,
                                float pz3, float mm3,
                                float px4, float py4,
                                float pz4, float mm4 ) {
  float pxt = px1 + px2 + px3 + px4;
  float pyt = py1 + py2 + py3 + py4;
  float pzt = pz1 + pz2 + pz3 + pz4;
  float eet = energy( px1, py1, pz1, mm1 ) +
              energy( px2, py2, pz2, mm2 ) +
              energy( px3, py3, pz3, mm3 ) +
              energy( px4, py4, pz4, mm4 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


float BmmAnalyzerUtil::invMSph( float  pt1, float eta1,
                                float phi1, float  mm1,
                                float  pt2, float eta2,
                                float phi2, float  mm2 ) {
  return 0;
}


float BmmAnalyzerUtil::invMSph( float  pt1, float eta1,
                                float phi1, float  mm1,
                                float  pt2, float eta2,
                                float phi2, float  mm2,
                                float  pt3, float eta3,
                                float phi3, float  mm3 ) {
  return 0;
}


float BmmAnalyzerUtil::invMSph( float  pt1, float eta1,
                                float phi1, float  mm1,
                                float  pt2, float eta2,
                                float phi2, float  mm2,
                                float  pt3, float eta3,
                                float phi3, float  mm3,
                                float  pt4, float eta4,
                                float phi4, float  mm4 ) {
  return 0;
}


float BmmAnalyzerUtil::dSqua( float a1, float b1,
                              float a2, float b2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  return ( ( aD * aD ) + ( bD * bD ) );
}


float BmmAnalyzerUtil::dSqua( float a1, float b1, float c1,
                              float a2, float b2, float c2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  float cD = c1 - c2;
  return ( ( aD * aD ) + ( bD * bD ) + ( cD * cD ) );
}


float BmmAnalyzerUtil::delta( float a1, float b1,
                              float a2, float b2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  return sqrt( ( aD * aD ) + ( bD * bD ) );
}


float BmmAnalyzerUtil::delta( float a1, float b1, float c1,
                              float a2, float b2, float c2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  float cD = c1 - c2;
  return sqrt( ( aD * aD ) + ( bD * bD ) + ( cD * cD ) );
}


void BmmAnalyzerUtil::convCartSphe( number  x, number  y, number  z,
                                    number& t, number& e, number& p ) {
  t = sqrt( ( x * x ) + ( y * y ) );
  float
  r = sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
  e = -log( ( r + z ) / ( r - z ) ) / 2.0;
  p = atan2( y, x );
  return;
}


void BmmAnalyzerUtil::convSpheCart( number  t, number  e, number  p,
                                    number& x, number& y, number& z ) {
  x = t * cos( p );
  y = t * sin( p );
  z = t / tan( 2 * atan( exp( -e ) ) );
  return;
}


void BmmAnalyzerUtil::convCartSphe( const std::vector<number>* x,
                                    const std::vector<number>* y,
                                    const std::vector<number>* z,
                                          std::vector<number>* t,
                                          std::vector<number>* e,
                                          std::vector<number>* p,
                                          int i ) {
  if ( i < 0 ) {
    int j;
    int n = x->size();
    t->resize( n );
    e->resize( n );
    p->resize( n );
    for ( j = 0; j < n; ++j )
    convCartSphe( x->at( j ), y->at( j ), z->at( j ),
                  t->at( j ), e->at( j ), p->at( j ) );
  }
  else {
    convCartSphe( x->at( i ), y->at( i ), z->at( i ),
                  t->at( i ), e->at( i ), p->at( i ) );
  }
  return;
}


void BmmAnalyzerUtil::convSpheCart( const std::vector<number>* t,
                                    const std::vector<number>* e,
                                    const std::vector<number>* p,
                                          std::vector<number>* x,
                                          std::vector<number>* y,
                                          std::vector<number>* z,
                                          int i ) {
  if ( i < 0 ) {
    int j;
    int n = t->size();
    x->resize( n );
    y->resize( n );
    z->resize( n );
    for ( j = 0; j < n; ++j )
    convSpheCart( t->at( j ), e->at( j ), p->at( j ),
                  x->at( j ), y->at( j ), z->at( j ) );
  }
  else {
    convSpheCart( t->at( i ), e->at( i ), p->at( i ),
                  x->at( i ), y->at( i ), z->at( i ) );
  }
  return;
}
