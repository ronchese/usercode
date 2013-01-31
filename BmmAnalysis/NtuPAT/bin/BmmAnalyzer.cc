#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "BmmAnalyzer.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
#include "Math/LorentzVector.h"

using namespace std;

BmmAnalyzer::BmmAnalyzer() {

  parameterSet = 0;
  currentEvBase  = 0;
  currentEvent   = 0;
  currentEvSetup = 0;

  std::cout << "new BmmAnalyzer" << std::endl;

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

  setUserParameter( "verbose", "f" );

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


BmmAnalyzer::~BmmAnalyzer() {
}



void BmmAnalyzer::beginJob() {

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
  initTree();

  getUserParameter( "verbose", verbose );

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

  read( getUserParameter( "eventList" ) );

  return;

}


void BmmAnalyzer::book() {

  // putting "autoSavedObject" in front of the histo creation 
  // it's automatically marked for saving on file; the option 
  // is uneffective when not using the full utility

  autoSavedObject =
  hptmumax        = new TH1D( "hptmumax"    , "ptmumax"    ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu2nd        = new TH1D( "hptmu2nd"    , "ptmu 2nd"   ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu           = new TH1D( "hptmu"       , "ptmu"       ,  50, 0.0, 100.0 );

  return;

}


bool BmmAnalyzer::analyze( int entry, int event_file ) {
  bool acceptEv = analyze( entry, event_file, analyzedEvts++ );
  if ( acceptEv ) acceptedEvts++;
  return acceptEv;
}


bool BmmAnalyzer::analyze( int entry, int event_file, int event_tot ) {

  if ( verbose ) {
    cout << " +++++++++++++++++++++++++++ " << endl;
    cout << "entry: "
         << entry << " " << event_file << " " << event_tot << endl;
    cout << "run: " <<   runNumber << " , "
         << "evt: " << eventNumber << endl;
  }
  else {
//    if ( !( event_file % 10000 ) || !( event_tot % 10000 ) )
    if ( !( event_file % 10000 ) && event_file )
      cout << event_file << " " << event_tot << endl;
  }

  // flag to be set "true" or "false" for events accepted or rejected
  bool flag;

  flag = true;

//  getEntry( b_nMuons, entry );
//  getEntry( b_muoPt , entry );

  int iMuon;
  float ptmu;
  float ptmumax = -1.0;
  float ptmu2nd = -1.0;
  for ( iMuon = 0; iMuon < nMuons; ++iMuon ) {
    ptmu = muoPt->at( iMuon );
    hptmu->Fill( ptmu );
    if( ptmu > ptmu2nd ) {
      if( ptmu > ptmumax ) {
        ptmu2nd = ptmumax;
        ptmumax = ptmu;
      }
      else {
        ptmu2nd = ptmu;
      }
    }
  }
  hptmumax->Fill( ptmumax );
  hptmu2nd->Fill( ptmu2nd );	

  return flag;

}


void BmmAnalyzer::endJob() {
  return;
}


void BmmAnalyzer::save() {
#  if UTIL_USE == FULL
  // explicit saving not necessary for "autoSavedObjects"
  autoSave();
#elif UTIL_USE == BARE
  // explicit save histos when not using the full utility
  hptmumax->Write();
  hptmu2nd->Write();
  hptmu   ->Write();
#endif

  return;
}


void BmmAnalyzer::plot() {
/*
  TCanvas* can = new TCanvas( "muoPt", "muoPt", 800, 600 );
  can->cd();
  can->Divide( 1, 2 );
  can->cd( 1 );
  hptmumax->Draw();
  hptmu2nd->Draw();
*/
  return;
}


void BmmAnalyzer::getEntry( int ientry ) {
//  cout << "BmmAnalyzer::getEntry" << endl;
  b_runNumber  ->GetEntry( ientry );
  b_lumiSection->GetEntry( ientry );
  b_eventNumber->GetEntry( ientry );
  if ( !find( runNumber, eventNumber ) ) return;
  currentTree->GetEntry( ientry );
  return;
}


void BmmAnalyzer::getEntry( TBranch* branch, int ientry ) {
  if ( currentEvBase != 0 ) return;
  if ( currentEvent  != 0 ) return;
  branch->GetEntry( ientry );
  return;
}


bool BmmAnalyzer::goodJet( int iJet ) {
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


