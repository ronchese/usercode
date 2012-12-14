#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "HTTAnalyzer.h"

#include "TDirectory.h"
#include "TCanvas.h"
#include "Math/LorentzVector.h"

using namespace std;

HTTAnalyzer::HTTAnalyzer() {
  std::cout << "new HTTAnalyzer" << std::endl;
#  if UTIL_USE == FULL
  // use the full utility to set user parameters from command line:
  // user parameters are set as names associated to a string, 
  // default values can be set in the analyzer class contructor
  setUserParameter( "verbose", "f" );
#endif
}


HTTAnalyzer::~HTTAnalyzer() {
}


void HTTAnalyzer::beginJob() {
#  if UTIL_USE == FULL
  // use the full utility to set user parameters from command line:
  // user parameters are retrieved as strings by using their names;
  // numeric parameters ( int, float or whatever ) can be directly set
  // by passing the corresponding variable,
  // e.g. getUserParameter( "name", x )

  const char* verbFlag = getUserParameter( "verbose" ).c_str();
  verbose = ( ( *verbFlag == 't' ) || ( *verbFlag == 'T' ) );

  getUserParameter( "eqlumi", eqlumi );

#elif UTIL_USE == BARE
  // when not using the full ntuple handling utility user parameters
  // are to be hardcoded or set anyhow else
//  verbose = true;
  verbose = false;
#endif

  jetNDaumin = 1;
  jetNDaumax = 999999999;
  jetNHFmin = -999999999.999;
  jetNHFmax =  0.99;
  jetNEFmin = -999999999.999;
  jetNEFmax =  0.99;
  jetCHFmin =  0.0;
  jetCHFmax =  999999999.999;
  jetCEFmin = -999999999.999;
  jetCEFmax =  0.99;
  jetNCHmin =  0;
  jetNCHmax =  999999999;
  jetEtaCut = 2.4;

  Nevents           = 0;
  Nevents_2j        = 0;
  Nevents_2j_2mu    = 0;
  Nevents_2j_2e     = 0;
  Nevents_2j_2l     = 0;
  Nevents_2j_2l_1b  = 0;
  Nevents_2j_2l_2b  = 0;
  Nevents_2j_2l_met = 0;

  Nevents_simHLT_2j_2mu    = 0;
  Nevents_simHLT_2j_2e     = 0;
  Nevents_simHLT_2j_2l     = 0;
  Nevents_simHLT_2j_2l_1b  = 0;
  Nevents_simHLT_2j_2l_2b  = 0;
  Nevents_simHLT_2j_2l_met = 0;

  JetEtCut     = 20.;
  JetEtaCut    = 2.5;
  JetCSVLoose  = 0.244;
  JetCSVMedium = 0.679;
  JetCSVTight  = 0.898;

  Lep1PtCut = 17.0;
  Lep2PtCut =  8.0;

  MEtCut    = 30.0;

  return;
}


void HTTAnalyzer::book() {

  // putting "autoSavedObject" in front of the histo creation 
  // it's automatically marked for saving on file; the option 
  // is uneffective when not using the full utility


  autoSavedObject =
  hptmuZmax       = new TH1D( "hptmuZmax"    , "ptmuZmax"  ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmuZmin       = new TH1D( "hptmuZmin"    , "ptmuZmin"  ,  50, 0.0, 100.0 );
  autoSavedObject =
  hetamax         = new TH1D( "hetamax"      , "etamax"    ,  50, 0.0,   5.0 );
  autoSavedObject =
  hMZgen          = new TH1D( "hMZgen"       , "MZ gen"    ,  50, 0.0, 200.0 );
  autoSavedObject =
  hMZgenAcc       = new TH1D( "hMZgenAcc"    , "MZ gen acc",  50, 0.0, 200.0 );
  autoSavedObject =

  autoSavedObject =
  nevents         = new TH1D( "nevents"     , "nevents"    ,   1, 1.0,   2.0 );
  autoSavedObject =
  hptmumax        = new TH1D( "hptmumax"    , "ptmumax"    ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu2nd        = new TH1D( "hptmu2nd"    , "ptmu 2nd"   ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu           = new TH1D( "hptmu"       , "ptmu"       ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmusame       = new TH1D( "hptmusame"   , "ptmusame"   ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmuopp        = new TH1D( "hptmuopp"    , "ptmuopp"    ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmuisosame    = new TH1D( "hptmuisosame", "ptmuisosame",  50, 0.0 ,100.0 );
  autoSavedObject =
  hptmuisosame1b  = new TH1D( "hptmuisosame1b" ,
                              "ptmuisosame, 1b", 50, 0.0, 100.0 );
  autoSavedObject =
  hptmuisosame2b  = new TH1D( "hptmuisosame2b" ,
                              "ptmuisosame, 2b", 50, 0.0 ,100.0 );
  autoSavedObject =
  hetamuisosame   = new TH1D( "hetamuisosame"  ,
                              "etamuisosame"   , 30, 0.0 ,  3.0 );
  autoSavedObject =
  hetamuisosame1b = new TH1D( "hetamuisosame1b",
                              "etamuisosame"   , 30, 0.0,   3.0 );
  autoSavedObject =
  hetamuisosame2b = new TH1D( "hetamuisosame2b",
                              "etamuisosame"   , 30, 0.0,   3.0 );
  autoSavedObject =
  hptmuisoopp     = new TH1D( "hptmuisoopp"    ,
                              "ptmuisoopp"     , 50, 0.0, 100.0 );
  autoSavedObject =
  hptmuisoopp1b   = new TH1D( "hptmuisoopp1b"  ,
                              "ptmuisoopp, 1b" , 50, 0.0 ,100.0 );
  autoSavedObject =
  hptmuisoopp2b   = new TH1D( "hptmuisoopp2b"  ,
                              "ptmuisoopp, 2b" , 50, 0.0 ,100.0 );
  autoSavedObject =
  hptmuisosameCR  = new TH1D( "hptmuisosameCR" ,
                              "ptmuisosame CR" , 50, 0.0 ,100.0 );
  autoSavedObject =
  hmuiso          = new TH1D( "hmuiso"      , "muiso"       , 100, 0.0,  5.0 );
  autoSavedObject =
  hmuiso2nd       = new TH1D( "hmuiso2nd"   , "muiso 2nd"   , 100, 0.0,  5.0 );
  autoSavedObject =
  hmuisosame      = new TH1D( "hmuisosame"  , "muisosame"   , 100, 0.0,  5.0 );
  autoSavedObject =
  hmuisoopp       = new TH1D( "hmuisoopp"   , "muisoopp"    , 100, 0.0,  5.0 );
  autoSavedObject =
  hmuisosameCR    = new TH1D( "hmuisosameCR",
                              "muisosame CR"                , 100, 0.0,  5.0 );
  autoSavedObject =
  hmuDRsame       = new TH1D( "hmuDRsame"   , "muDRsame"    ,  60, 0.0,  6.0 );
  autoSavedObject =
  hmuDRopp        = new TH1D( "hmuDRopp"    , "muDRopp"     ,  60, 0.0,  6.0 );
  autoSavedObject =
  hmuDRsameCR     = new TH1D( "hmuDRsameCR" , "muDRsameCR"  ,  60, 0.0,  6.0 );
  autoSavedObject =
  hNtop           = new TH1D( "hNtop"       , "ntop"        , 10, 0.0,  10.0 );
  autoSavedObject =
  hNW             = new TH1D( "hNW"         , "nW"          , 10, 0.0,  10.0 );
  autoSavedObject =
  hNZ             = new TH1D( "hNZ"         , "nZ"          , 10, 0.0,  10.0 );
  autoSavedObject =
  hNtaus          = new TH1D( "hNtaus"      , "ntaus"       , 10, 0.0,  10.0 );
  autoSavedObject =
  hNmutop         = new TH1D( "hNmutop"     , "nmutop"      , 10, 0.0,  10.0 );
  autoSavedObject =
  hNmutau         = new TH1D( "hNmutau"     , "nmutau"      , 10, 0.0,  10.0 );
  autoSavedObject =
  hMTW            = new TH1D( "hMTW"        , "MTW"         , 80, 0.0, 400.0 );
  autoSavedObject =
  hMET            = new TH1D( "hMET"        , "MET"         , 80, 0.0, 400.0 );
  autoSavedObject =
  hMTWbjets       = new TH1D( "hMTWbjets"   , "MTWbjets"    , 80, 0.0, 400.0 );
  autoSavedObject =
  hMTW2bjets      = new TH1D( "hMTW2bjets"  , "MTWbjets"    , 80, 0.0, 400.0 );
  autoSavedObject =
  hNbjets         = new TH1D( "hNbjets"     , "Nbjets"      , 10, 0.0,  10.0 );
  autoSavedObject =
  hM2mu           = new TH1D( "hM2mu"       , "M2mu"        , 50, 0.0, 200.0 );
  autoSavedObject =
  hM2mub          = new TH1D( "hM2mub"      , "M2mu b"      , 50, 0.0, 200.0 );
  autoSavedObject =
  hM2leptSS       = new TH1D( "hM2leptSS"   , "M2lept SS"   , 50, 0.0, 200.0 );
  autoSavedObject =
  hM2leptSSSF     = new TH1D( "hM2leptSSSF" , "M2lept SS SF", 50, 0.0, 200.0 );
  autoSavedObject =
  hM2leptOS       = new TH1D( "hM2leptOS"   , "M2lept OS"    ,50, 0.0, 200.0 );
  autoSavedObject =
  hM2leptb        = new TH1D( "hM2leptb"    , "M2lept b"     ,50, 0.0, 200.0 );
  autoSavedObject =
  hM2tau          = new TH1D( "hM2tau"      , "M2tau"        ,40, 0.0, 400.0 );
  autoSavedObject =
  hNtaurec        = new TH1D( "hNtaurec"    , "ntaurec"      ,10, 0.0,  10.0 );
  autoSavedObject =
  hpttausame      = new TH1D( "hpttausame"  , "pttausame"    ,50, 0.0, 100.0 );
  autoSavedObject =
  hpttauopp       = new TH1D( "hpttauopp"   , "pttauopp"     ,50, 0.0, 100.0 );

  autoSavedObject =
  hM2e            = new TH1D( "hM2e" , "M2e"   , 50, 0.0, 200.0 );
  autoSavedObject =
  hM2eb           = new TH1D( "hM2eb", "M2e b" , 50, 0.0, 200.0 );

  autoSavedObject =
  hMjjZe          = new TH1D( "hMjjZe" , "MjjZe" , 60, 0.0, 480.0 );
  autoSavedObject =
  hMbbZe          = new TH1D( "hMbbZe" , "MbbZe" , 60, 0.0, 480.0 );
  autoSavedObject =
  hMjjZmu         = new TH1D( "hMjjZmu", "MjjZmu", 60, 0.0, 480.0 );
  autoSavedObject =
  hMbbZmu         = new TH1D( "hMbbZmu", "MbbZmu", 60, 0.0, 480.0 );

  autoSavedObject =
  hMHmmjj         = new TH1D( "hMHmmjj", "MH mmjj", 60, 0.0, 480.0 );
  autoSavedObject =
  hMHmmbb         = new TH1D( "hMHmmbb", "MH mmbb", 60, 0.0, 480.0 );

  autoSavedObject =
  hMWjj           = new TH1D( "hMWjj"   , "MWjj"   , 60, 0.0, 480.0 );
  autoSavedObject =
  hMWjjtop        = new TH1D( "hMWjjtop", "MWjjtop", 60, 0.0, 480.0 );

  autoSavedObject =
  hpt3CR          = new TH1D( "hpt3CR"     , "pt3 , Z"    , 50, 0.0, 100.0 );
  autoSavedObject =
  hptmu3CR        = new TH1D( "hptmu3CR"   , "ptmu3, Z"   , 50, 0.0, 100.0 );
  autoSavedObject =
  hpte3CR         = new TH1D( "hpte3CR"    , "pte3, Z"    , 50, 0.0, 100.0 );
  autoSavedObject =
  hpt3isoCR       = new TH1D( "hpt3isoCR"  , "pt3iso , Z" , 50, 0.0, 100.0 );
  autoSavedObject =
  hptmu3isoCR     = new TH1D( "hptmu3isoCR", "ptmu3iso, Z", 50, 0.0, 100.0 );
  autoSavedObject =
  hpte3isoCR      = new TH1D( "hpte3isoCR" , "pte3iso, Z" , 50, 0.0, 100.0 );

  autoSavedObject =
  hMZ2            = new TH1D( "hMZ2"   , "MZ2"   ,  50, 0.0, 200.0 );
  autoSavedObject =
  hM4lept         = new TH1D( "hM4lept", "M4lept", 100, 0.0, 400.0 );

  // associate subdirectories and numbers
  // "Obj"     ---> 0
  // "simHLT"  ---> 1
  int nDir = 0;
  dirMap.insert( make_pair( "Obj"   , nDir++ ) );
  dirMap.insert( make_pair( "simHLT", nDir++ ) );

  // create bi-dimensional arrays
  // h_jet_pt             is a   bi-dimensional array of TH1D*
  // h_jet_pt[iDir]       is an uni-dimensional array of TH1D*
  // h_jet_pt[iDir][iJet] is a TH1D*

  h_jet_pt   = new TH1D**[nDir];
  h_jet_eta  = new TH1D**[nDir];
  h_jet_CSV  = new TH1D**[nDir];
  h_muon_pt  = new TH1D**[nDir];
  h_muon_eta = new TH1D**[nDir];
  h_ele_pt   = new TH1D**[nDir];
  h_ele_eta  = new TH1D**[nDir];


  // create uni-dimensional arrays
  // h_met       is an array of TH1D*
  // h_met[iDir] is a TH1D*

  h_met = new TH1D*[nDir];

  h_Mjj = new TH1D*[nDir];
  h_Mmm = new TH1D*[nDir];
  h_Mee = new TH1D*[nDir];
  h_Mll = new TH1D*[nDir];
  h_Mh  = new TH1D*[nDir];

  h_mZqq = new TH1D*[nDir];
  h_mZll = new TH1D*[nDir];
  h_mH   = new TH1D*[nDir];

  TDirectory* subDir;
  std::map<std::string,int>::const_iterator iter = dirMap.begin();
  std::map<std::string,int>::const_iterator iend = dirMap.end();
  while ( iter != iend ) {

    const std::string& name = iter->first;
    int iDir                = iter->second;
    ++iter;

    // when using the full "NtuTool" utility, the command
    // autoSavedObject = gDirectory->mkdir( "xyz" );
    // automatically sets "xyz" as current directory and
    // replicates the "xyz" subdirectory in the output file
    // when not using the "NtuTool" utility,
    // autoSavedObject is uneffective, and the subdirectory has to 
    // be set as the working one by hand

    autoSavedObject =
    subDir = // needed when not using the full utility
    gDirectory->mkdir( name.c_str() );
    subDir->cd();

    (nMaxJet = 5)++; // up to 5 jets, count starting from 1
    TH1D** hh_jet_pt  = h_jet_pt [iDir] = new TH1D*[nMaxJet];
    TH1D** hh_jet_eta = h_jet_eta[iDir] = new TH1D*[nMaxJet];
    TH1D** hh_jet_CSV = h_jet_CSV[iDir] = new TH1D*[nMaxJet];
    int iJ;
    for ( iJ = 1; iJ < nMaxJet; ++iJ ) {
      autoSavedObject =
      hh_jet_pt [iJ] = createHisto( "jet",  "pt", iJ, 200, -0.5, 199.5 );
      autoSavedObject =
      hh_jet_eta[iJ] = createHisto( "jet", "eta", iJ,  50, -2.5,   2.5 );
      autoSavedObject =
      hh_jet_CSV[iJ] = createHisto( "jet", "CSV", iJ, 202, -0.05,  1.05);
    }

    (nMaxLep = 3)++; // up to 3 leptons, count starting from 1
    TH1D** hh_muon_pt  = h_muon_pt [iDir] = new TH1D*[nMaxLep];
    TH1D** hh_muon_eta = h_muon_eta[iDir] = new TH1D*[nMaxLep];
    TH1D** hh_ele_pt   = h_ele_pt  [iDir] = new TH1D*[nMaxLep];
    TH1D** hh_ele_eta  = h_ele_eta [iDir] = new TH1D*[nMaxLep];
    int iL;
    for ( iL = 1; iL < nMaxLep; ++iL ) {
      autoSavedObject =
      hh_muon_pt [iL] = createHisto( "muon",  "pt", iL, 200, -0.5, 199.5 );
      autoSavedObject =
      hh_muon_eta[iL] = createHisto( "muon", "eta", iL,  50, -2.5,   2.5 );
      autoSavedObject =
       hh_ele_pt [iL] = createHisto(  "ele",  "pt", iL, 200, -0.5, 199.5 );
      autoSavedObject =
       hh_ele_eta[iL] = createHisto(  "ele", "eta", iL,  50, -2.5,   2.5 );
    }

    autoSavedObject =
    h_met[iDir] = new TH1D( "met", "met", 200, -0.5, 199.5 );

    autoSavedObject =
    h_Mjj[iDir] = new TH1D( "Mjj", "Mjj", 100, 0.0, 200.0 );
    autoSavedObject =
    h_Mmm[iDir] = new TH1D( "Mmm", "Mmm", 200, 0.0, 200.0 );
    autoSavedObject =
    h_Mee[iDir] = new TH1D( "Mee", "Mee", 200, 0.0, 200.0 );
    autoSavedObject =
    h_Mll[iDir] = new TH1D( "Mll", "Mll", 200, 0.0, 200.0 );
    autoSavedObject =
    h_Mh [iDir] = new TH1D( "Mh",  "Mh" , 200, 0.0, 200.0 );

    autoSavedObject =
    h_mZqq[iDir] = new TH1D( "mZqq", "mZqq", 200, 0.0, 200.0 );
    autoSavedObject =
    h_mZll[iDir] = new TH1D( "mZll", "mZll", 200, 0.0, 200.0 );
    autoSavedObject =
    h_mH  [iDir] = new TH1D( "mH"  , "mH"  , 200, 0.0, 200.0 );

    // see the comment above about setting current directories

    autoSavedObject =
    subDir = // needed when not using the full utility
    gDirectory->GetDirectory( ".." );
    subDir->cd();

  }

  return;

}


bool HTTAnalyzer::analyze( int entry, int event_file ) {
  bool acceptEv = analyze( entry, event_file, analyzedEvts++ );
  if ( acceptEv ) acceptedEvts++;
  return acceptEv;
}


bool HTTAnalyzer::analyze( int entry, int event_file, int event_tot ) {

  if ( verbose ) {
    cout << " +++++++++++++++++++++++++++ " << endl;
    cout << "entry: "
         << entry << " " << event_file << " " << event_tot << endl;
    cout << "run: " <<   runNumber << " , "
         << "evt: " << eventNumber << endl;
  }
  else {
//    if ( !( event_file % 10000 ) || !( event_tot % 10000 ) )
    if ( !( event_file % 10000 ) )
      cout << event_file << " " << event_tot << endl;
  }

  bool debugFlag = verbose;

  // flag to be set "true" or "false" for events accepted or rejected
  bool flag;

  flag = true;

  bool good_event = true;
  nevents->Fill(1.);

  // loop on gen particles: count top/Z/W and taus from Higgs #####################
  mZqq = -1., mZll = -1., mH   = -1.;
  int Ntop = 0, NW = 0, NZ = 0, Ntaus = 0, Nmutop = 0, Nmutau = 0 , NmuZ = 0;
  float ptmuZ1 = 0., ptmuZ2 = 0., aeta1 = 0., aeta2 = 0.;
  float MugenPt[10],MugenPx[10],MugenPy[10],MugenPz[10],MugenEta[10],MugenPhi[10],MugenCharge[10];	

//  int nGenP = genId->size();
  int iGenP;
  for ( iGenP = 0; iGenP < nGenP; ++iGenP ) {
    int pID = genId->at( iGenP );
    int pStatus = genStatus->at( iGenP );
    int mID = genMother->at( iGenP ) >= 0 ?
              genId->at( genMother->at( iGenP ) ) : 0;
    if(fabs(pID)==6 and pStatus == 3) Ntop++;
    if(fabs(pID)==24 and pStatus == 3) NW++;
    if(fabs(pID)==23 and pStatus == 3) NZ++;
    if(fabs(pID)==15 and pStatus == 3) {  // taus
      //   if(mID == 25 ) Ntaus++;
      if( genPt->at( iGenP ) > 10. ) Ntaus++;    }
    if(fabs(pID)==13 and pStatus == 3) { 
      if( fabs(mID) == 23 ) {       // muons from Z	       
        MugenPt[NmuZ] = genPt->at( iGenP );
        MugenPx[NmuZ] = genPx->at( iGenP );
        MugenPy[NmuZ] = genPy->at( iGenP );
        MugenPz[NmuZ] = genPz->at( iGenP );
        MugenEta[NmuZ] = genEta->at( iGenP );
        MugenPhi[NmuZ] = genPhi->at( iGenP );
        MugenCharge[NmuZ] = genCharge->at( iGenP );
        NmuZ++;
        if(NmuZ == 1) {
          ptmuZ1 = genPt->at( iGenP );
          aeta1 = fabs(genEta->at( iGenP ) );}
        if(NmuZ == 2) {
          ptmuZ2 = genPt->at( iGenP );
          aeta2 = fabs(genEta->at( iGenP ) );}
      }
      if( fabs(mID) == 24 ) Nmutop++;
      if( fabs(mID) == 15 ) Nmutau++;
    }
    if (fabs(pID) == 25 and pStatus == 3)
      mH = genMass->at( iGenP );
    if( fabs(mID) == 23 and pStatus == 3) {
      if (fabs(pID)<=6) {
        mZqq = genMass->at( genMother->at( iGenP ) );
      } else if (fabs(pID) == 11 or fabs(pID) == 13) {
        mZll = genMass->at( genMother->at( iGenP ) );
      }
    }  
  }

  float ptmuZmax = ptmuZ1;
  float ptmuZmin = ptmuZ2;
  if(ptmuZmax < ptmuZmin ) {
    ptmuZmax = ptmuZ2;
    ptmuZmin = ptmuZ1; }
  if(ptmuZmax > 0. ) {      	
    hptmuZmax->Fill(ptmuZmax);
    hptmuZmin->Fill(ptmuZmin); }
  float aetamax = aeta1;
  float aetamin = aeta2;
  if(aetamax < aetamin ) {
    aetamax = aeta2;
    aetamin = aeta1; }
  if(ptmuZmin > 12.) hetamax->Fill(aetamax);

  hNtop->Fill(Ntop);
  if(Ntop == 0 ) hNW->Fill(NW);
  hNZ->Fill(NZ);

  hNtaus->Fill(Ntaus); // generated taus
  hNmutop->Fill(Nmutop);
  hNmutau->Fill(Nmutau);

  if ( verbose ) {
    cout << " --------------------------- " << endl;
  }

//      keep only ttH events inn ttH/WH/ZH production #######
//        if(Ntop == 0 ) return false;

//    select SL top decays
//        if(Nmutop == 0 ) return false;

  int Ngoodjets;
  int Ngoodmuons;
  int Ngoodeles;
  int Ngoodtaus;

  double JetPt[100];
  double JetEta[100];
  double JetCSV[100];
  double MuPt[10];
  double MuEta[10];

  // Loop on jets #######################################
  // ------------
  Ngoodjets=0;
  int JetIdx[100];
  double JetTCHE[100], JetPhi[100], JetPx[100], JetPy[100], JetPz[100];
  for (int i=0; i<100; i++) {
    JetIdx[i] = -1;
    JetPt[i] = -1.;
    JetEta[i] = -9.;
    JetPhi[i] = -9.;
    JetCSV[i] = -9.;
    JetTCHE[i] = -9.; }
//  int index = 0;

//  int nJets = jetPt->size();
  int iJet;
  for ( iJet = 0; iJet < nJets; ++iJet ) {
    if ( !goodJet( iJet ) ) continue;
    if (jetPt->at( iJet )>JetEtCut && fabs(jetEta->at( iJet ))<JetEtaCut) {
      if (Ngoodjets<100) {
	JetIdx[Ngoodjets]=iJet;
	JetPt[Ngoodjets]=jetPt->at( iJet );
	JetEta[Ngoodjets]=jetEta->at( iJet );
	JetPhi[Ngoodjets]=jetPhi->at( iJet );
	JetPx[Ngoodjets] = jetPx->at( iJet );
	JetPy[Ngoodjets] = jetPy->at( iJet );
	JetPz[Ngoodjets] = jetPz->at( iJet );	      
	JetCSV[Ngoodjets]=jetCSV->at( iJet );
	if (JetCSV[Ngoodjets]<0.) JetCSV[Ngoodjets]=0.;
	JetTCHE[Ngoodjets]=jetTCHE->at( iJet );
      }
      Ngoodjets++;
    }
  }
  if (debugFlag)	std::cout << "Ngoodjets: " << Ngoodjets << std::endl;
  int Nbjets_loose=0;
  int Nbjets_medium=0;
  int Nbjets_tight=0;
  for (int i=0; i<Ngoodjets; i++ ) {
    if (JetCSV[i] >= JetCSVLoose) Nbjets_loose++;
    if (JetCSV[i] >= JetCSVMedium) Nbjets_medium++;
    if (JetCSV[i] >= JetCSVTight) Nbjets_tight++;   }
  if (debugFlag) {
    std::cout << "Nbjets_loose: " << Nbjets_loose << std::endl;
    std::cout << "Nbjets_medium: " << Nbjets_medium << std::endl;
    std::cout << "Nbjets_tight: " << Nbjets_tight << std::endl;
  }
//  if(idbg1 == 1 ) std::cout << "Nbjets_medium: " << Nbjets_medium << std::endl;

  // Muons ################################
  // --------------------------------------
  int MuIdx[10];
  double MuCharge[10], MuIso[10], MuPx[10], MuPy[10], MuPz[10], MuPhi[10];
  double LeptCharge[20], LeptIso[20], LeptPx[20], LeptPy[20], LeptPz[20], LeptPhi[20], LeptFlag[20];
  double LeptPt[20], LeptEta[20];
  Ngoodmuons=0;
//  index = 0;
  float ptmumax = 0.;
  int   imutrigg = 0;

//  int nMuons = muoPt->size();
  int iMuon;
  for ( iMuon = 0; iMuon < nMuons; ++iMuon ) {
    if (Ngoodmuons<10) {
      MuIdx[Ngoodmuons] = iMuon;
      MuPt[Ngoodmuons] = muoPt->at( iMuon );
      MuPx[Ngoodmuons] = muoPx->at( iMuon );
      MuPy[Ngoodmuons] = muoPy->at( iMuon );
      MuPz[Ngoodmuons] = muoPz->at( iMuon );
      MuEta[Ngoodmuons] = muoEta->at( iMuon );
      MuPhi[Ngoodmuons] = muoPhi->at( iMuon );
      MuCharge[Ngoodmuons] = muoCharge->at( iMuon );
      float muisoch  = muoChaIso->at( iMuon );
      float muisoneu = muoNeuIso->at( iMuon );
      float muisogam = muoPhoIso->at( iMuon );
      float muiso = (muisoch + muisoneu + muisogam)/ MuPt[Ngoodmuons] ; 
      //    float muiso = muisoch ; 
      MuIso[Ngoodmuons] = muiso;
      LeptPt[Ngoodmuons] = muoPt->at( iMuon );
      LeptPx[Ngoodmuons] = muoPx->at( iMuon );
      LeptPy[Ngoodmuons] = muoPy->at( iMuon );
      LeptPz[Ngoodmuons] = muoPz->at( iMuon );
      LeptEta[Ngoodmuons] = muoEta->at( iMuon );
      LeptPhi[Ngoodmuons] = muoPhi->at( iMuon );
      LeptCharge[Ngoodmuons] = muoCharge->at( iMuon );	
      LeptIso[Ngoodmuons] = muiso;
      LeptFlag[Ngoodmuons] = 1. ;    
//      hptmu->Fill(muoPt->at( iMuon ));
//	hmuiso->Fill(muiso);
      if( MuPt[Ngoodmuons] > ptmumax ) {
        imutrigg = Ngoodmuons;
        ptmumax = MuPt[Ngoodmuons] ;
      }
      Ngoodmuons++;
    }
  } // next muon
  int Nlept = Ngoodmuons;
  //      if(idbg1 == 1 ) std::cout << "Nmuons: " << Ngoodmuons << std::endl;

// look to 2nd pT muon	
  float ptmu2nd = 0.;
  int imu2nd = -1;
  for ( int jmu=0; jmu < Ngoodmuons; jmu++) {
    if(jmu == imutrigg)     continue;
    if(MuPt[jmu]> ptmu2nd ) {
      ptmu2nd = MuPt[jmu];
      imu2nd = jmu;  } 
  } // next mu

  // Electrons
  // ---------
  int EleIdx[10];
  double ElePt[10];
  double EleEta[10], ElePhi[10], ElePx[10], ElePy[10], ElePz[10];
  double EleCharge[10], EleIso[10];
  Ngoodeles=0;
//  index = 0;

//  int nElectrons = elePt->size();
  int iEle;
  for ( iEle = 0; iEle < nElectrons; ++iEle ) {
    if (Ngoodeles<10) {
      EleIdx[Ngoodeles] = iEle;
      ElePt[Ngoodeles] = elePt->at( iEle );
      EleEta[Ngoodeles] = eleEta->at( iEle );
      ElePhi[Ngoodeles] = elePhi->at( iEle );
      ElePx[Ngoodeles] = elePx->at( iEle );
      ElePy[Ngoodeles] = elePy->at( iEle );
      ElePz[Ngoodeles] = elePz->at( iEle );
      EleCharge[Ngoodeles] = eleCharge->at( iEle );
      float eisoch  = eleChaIso->at( iEle );
      float eisoneu = eleNeuIso->at( iEle );
      float eisogam = elePhoIso->at( iEle );
      float eiso = (eisoch + eisoneu + eisogam)/ ElePt[Ngoodeles] ; 
      EleIso[Ngoodeles] = eiso;
      LeptPt[Nlept]  = elePt->at( iEle );
      LeptEta[Nlept] = eleEta->at( iEle );
      LeptPhi[Nlept] = elePhi->at( iEle );
      LeptPx[Nlept]  = elePx->at( iEle );
      LeptPy[Nlept]  = elePy->at( iEle );
      LeptPz[Nlept]  = elePz->at( iEle );
      LeptCharge[Nlept] = eleCharge->at( iEle );
      LeptIso[Nlept]    = eiso;
      LeptFlag[Nlept]   = 2.;
      Ngoodeles++;
      Nlept++;
    }
  }
  if (debugFlag)	std::cout << "Ngoodeles: " << Ngoodeles << std::endl;
  //  if(idbg1 == 1 ) std::cout << "Ngoodeles: " << Ngoodeles << std::endl;

  // Loop on taus
  // ------------
  int indextau = 0;
  Ngoodtaus = 0;
  double TauPt[50],TauEta[50],TauPhi[50], TauCharge[50], TauPx[50], TauPy[50], TauPz[50];


//  int nTaus = tauPt->size();
  int iTau;
  for ( iTau = 0; iTau < nTaus; ++iTau ) {
//	  if ( !goodTau( iTau ) ) continue;
    if (tauPt->at( iTau )> 10. && fabs(tauEta->at( iTau ))< 2.5 ) {
      if (Ngoodtaus<50) {
        //      JetIdx[Ngoodjets]=index;
        // check it is not an electron/muon
          int iok = 1;
          for ( int jmu=0; jmu < Ngoodmuons; jmu++) {
            float deta = tauEta->at( iTau ) - MuEta[jmu];
            float dphi = tauPhi->at( iTau ) - MuPhi[jmu];
            float DR =  sqrt(deta*deta + dphi*dphi);
            if(DR < 0.05 ) iok = 0;
          } // next muon
          for ( int jel=0; jel < Ngoodeles; jel++) {
            float deta = tauEta->at( iTau ) - EleEta[jel];
            float dphi = tauPhi->at( iTau ) - ElePhi[jel];
            float DR =  sqrt(deta*deta + dphi*dphi);
            if(DR < 0.05 ) iok = 0;
          } // next electron
          if(iok == 1 ) {
            indextau++;
            TauPt[Ngoodtaus]=tauPt->at( iTau );
            TauEta[Ngoodtaus]=tauEta->at( iTau );
            TauPhi[Ngoodtaus]=tauPhi->at( iTau );
            TauCharge[Ngoodtaus]=tauCharge->at( iTau );
            TauPx[Ngoodtaus] = tauPx->at( iTau );
            TauPy[Ngoodtaus] = tauPy->at( iTau );
            TauPz[Ngoodtaus] = tauPz->at( iTau );
            Ngoodtaus++;
          } // iok = 1
      } // Ntau < 50
    } // endif pT > 10, eta < 2.4
  } // next tau cand
  //      if(idbg1 == 1) std::cout << "Ntaus: " << Ngoodtaus << std::endl;


// analyse ALL leptons
  float ptlmax = 0., ptl2nd = 0.;
  int iltrigg = -1, il2nd = -1;
  for ( int jl=0; jl < Nlept; jl++) {
    if(LeptPt[jl] > ptlmax ) {
      ptlmax = LeptPt[jl];
      iltrigg = jl;	  } 
  } // next lepton      
  for ( int jl=0; jl < Nlept; jl++) {
    if(jl == iltrigg)     continue;
    if(LeptPt[jl] > ptl2nd ) {
      ptl2nd = LeptPt[jl];
      il2nd = jl;	  } 
  } // next lepton


 // ###############################################
 // start ttH analysis selection ##################
 // ###############################################

/* 
 // muon selection
 if(ptmumax > 0. && MuIso[imutrigg] < 0.15 ) hptmumax->Fill(ptmumax);
 if(ptmu2nd > 0. && MuIso[imutrigg] < 0.15 ) hptmu2nd->Fill(ptmu2nd);	
 if(ptmumax < 17.) return false;
 if(ptmu2nd < 8.)  return false;
*/

  int iemu = 0;
  if( LeptFlag[iltrigg]== 1 &&  LeptFlag[il2nd]== 2 ) iemu = 1; // mimic MuEG trigger in MC
  if( LeptFlag[iltrigg]== 2 &&  LeptFlag[il2nd]== 1 ) iemu = 1;
//  if(iemu == 0 ) return false;

  int i2mu = 0;
  if( LeptFlag[iltrigg]== 1 &&  LeptFlag[il2nd]== 1 ) i2mu = 1; // mimic DiMu trigger in MC
//  if(i2mu == 0 ) return false;

  int i2e  = 0;
  if( LeptFlag[iltrigg]== 2 &&  LeptFlag[il2nd]== 2 ) i2e = 1; // mimic DiMu trigger in MC
//  if(i2e == 0 ) return false;

//  cout << iltrigg << " " << iemu << " " << i2mu << " " << i2e << endl;

  int ioktrigg;
//  ioktrigg = iemu+i2mu+i2e;
  ioktrigg = i2mu;
//  if(ioktrigg == 0 ) return false;

 // lepton selection
 //   if(ptlmax > 0. && LeptIso[iltrigg] < 0.15 ) hptmumax->Fill(ptlmax);
 //       if(ptl2nd > 0. && LeptIso[iltrigg] < 0.15 ) hptmu2nd->Fill(ptl2nd);	
//  if(ptlmax < 17.) return false;
//  if(ptl2nd < 8.)  return false;

  hmuiso->Fill(LeptIso[iltrigg] );
//  if(LeptIso[iltrigg] > 0.15 ) return false;

  hmuiso2nd->Fill(LeptIso[il2nd] );	

  // invariant mass mu-mu --------------------------
  int itagZmu = 0, iZmu1 = -1, iZmu2 = -1;
  float pZ[5];
  pZ[0] = 0., pZ[1] = 0., pZ[2] = 0., pZ[3] = 0., pZ[4] = 0. ;
  if(Ngoodmuons > 1 ) {
    for ( int jmu=0; jmu < Ngoodmuons-1; jmu++) {
      float Emu = sqrt ( MuPx[jmu]*MuPx[jmu] + MuPy[jmu]*MuPy[jmu] + MuPz[jmu]*MuPz[jmu] );
      for ( int jmu2=jmu+1; jmu2 < Ngoodmuons; jmu2++) {
        if(MuCharge[jmu] == MuCharge[jmu2] ) continue;
        if(MuIso[jmu]  >  0.2 )              continue;
        if(MuIso[jmu2] >  0.2 )              continue;
        int iokpt = 0 ;
        if(MuPt[jmu] > 17. && MuPt[jmu2] >  8.) iokpt = 1;
        if(MuPt[jmu] >  8. && MuPt[jmu2] > 17.) iokpt = 1;
        if(iokpt == 0 )                      continue;
        float Emu2 = sqrt ( MuPx[jmu2]*MuPx[jmu2] + MuPy[jmu2]*MuPy[jmu2] + MuPz[jmu2]*MuPz[jmu2] );
        float minv = sqrt(2.*(Emu*Emu2 - MuPx[jmu]*MuPx[jmu2] - MuPy[jmu]*MuPy[jmu2] - MuPz[jmu]*MuPz[jmu2] ) ); 
        hM2mu->Fill(minv);
        pZ[1] = MuPx[jmu] + MuPx[jmu2];
        pZ[2] = MuPy[jmu] + MuPy[jmu2];
        pZ[3] = MuPz[jmu] + MuPz[jmu2];
        float pZ2 = pZ[1]*pZ[1] + pZ[2]*pZ[2]  + pZ[3]*pZ[3] ;
        pZ[0] = sqrt(minv*minv + pZ2 );
        pZ[4] = minv;
	//  itagZmu = 1;
        if(fabs(minv-91.) < 10. ) {
	  itagZmu = 1;
	  iZmu1 = jmu;
	  iZmu2 = jmu2; }
        if(Nbjets_medium > 0 )  hM2mub->Fill(minv);
      } // next mu2
    } // next muon
  } // endif Nmu > 1	   
  //  if(idbg1 == 1 ) std::cout << "tagZmu: " << itagZmu << std::endl;
	
 // invariant mass e-e ----------------------------------
  int itagZe = 0, iZe1 = -1, iZe2 = -1;
  if(Ngoodeles > 1 ) {
    for ( int je=0; je < Ngoodeles-1; je++) {
      float Ee = sqrt ( ElePx[je]*ElePx[je] + ElePy[je]*ElePy[je] + ElePz[je]*ElePz[je] );
      for ( int je2=je+1; je2 < Ngoodeles; je2++) {
        if(EleCharge[je] == EleCharge[je2] ) continue;
        if(EleIso[je]  >  0.2 )              continue;
        if(EleIso[je2] >  0.2 )              continue;
        int iokpt = 0 ;
        if(ElePt[je] > 17. && ElePt[je2] >  8.) iokpt = 1;
        if(ElePt[je] >  8. && ElePt[je2] > 17.) iokpt = 1;
        if(iokpt == 0 )                      continue;
        float Ee2 = sqrt ( ElePx[je2]*ElePx[je2] + ElePy[je2]*ElePy[je2] + ElePz[je2]*ElePz[je2] );
        float minv = sqrt(2.*(Ee*Ee2 - ElePx[je]*ElePx[je2] - ElePy[je]*ElePy[je2] - ElePz[je]*ElePz[je2] ) ); 
        hM2e->Fill(minv);
        if(fabs(minv-91.) < 10. ) {
          itagZe = 1;
          iZe1 = je;
          iZe2 = je2; }
        if(Nbjets_medium > 0 )  hM2eb->Fill(minv);
      } // next ele2
    } // next ele
  } // endif Nele > 1
 //       if(idbg1 == 1 ) std::cout << "tagZe: " << itagZe << std::endl;
       
// invariant mass lept-lept ----------------------------------
  int itagZ = 0, iZlep1 = -1, iZlep2 = -1;
  float MZ1 = 0., PxZ1 = 0., PyZ1 = 0, PzZ1 = 0., EZ1 = 0. ;
  if(Nlept > 1 ) {
    for ( int je=0; je < Nlept-1; je++) {
      float Ee = sqrt ( LeptPx[je]*LeptPx[je] + LeptPy[je]*LeptPy[je] + LeptPz[je]*LeptPz[je] );
      for ( int je2=je+1; je2 < Nlept; je2++) {
        //  if(LeptCharge[je] == LeptCharge[je2] ) continue;
        if(LeptIso[je]  >  0.2 )              continue;
        if(LeptIso[je2] >  0.2 )              continue;
        int iokpt = 0 ;
        if(LeptPt[je] > 17. && LeptPt[je2] >  8.) iokpt = 1;
        if(LeptPt[je] >  8. && LeptPt[je2] > 17.) iokpt = 1;
        if(iokpt == 0 )                      continue;
        float Ee2 = sqrt ( LeptPx[je2]*LeptPx[je2] + LeptPy[je2]*LeptPy[je2] + LeptPz[je2]*LeptPz[je2] );
        float minv = sqrt(2.*(Ee*Ee2 - LeptPx[je]*LeptPx[je2] - LeptPy[je]*LeptPy[je2] - LeptPz[je]*LeptPz[je2] ) ); 
        if(LeptCharge[je] == LeptCharge[je2] ) hM2leptSS->Fill(minv);
        if(LeptCharge[je] != LeptCharge[je2] ) hM2leptOS->Fill(minv);
        if(LeptFlag[je] != LeptFlag[je2] )   continue;  // only same flavour leptons
        hM2leptSSSF->Fill(minv);
        if(fabs(minv-91.) < 15. ) {
          PxZ1 = LeptPx[je] + LeptPx[je2];
          PyZ1 = LeptPy[je] + LeptPy[je2];
          PzZ1 = LeptPz[je] + LeptPz[je2];
          EZ1 = sqrt( minv*minv + PxZ1*PxZ1 + PyZ1*PyZ1 + PzZ1*PzZ1 ); 
          MZ1 = minv;
          itagZ  = 1;
          iZlep1 = je;
          iZlep2 = je2; }
        if(Nbjets_medium > 0 )  hM2leptb->Fill(minv);
      } // next lept2
    } // next lept1
  } // endif Nlept > 1       
  //       if(idbg1 == 1 ) std::cout << "tagZ: " << itagZ << std::endl;

// invariant mass jet-jet -------------------------
  if(Ngoodjets > 1 ) {
    float pZjj[5];
    for ( int jj=0; jj < Ngoodjets-1; jj++) {
      float Ej = sqrt ( JetPx[jj]*JetPx[jj] + JetPy[jj]*JetPy[jj] + JetPz[jj]*ElePz[jj] );
      for ( int jj2=jj+1; jj2 < Ngoodjets; jj2++) {	      
        if(JetPt[jj] < 20. || JetPt[jj2] < 20.) continue;
        float Ej2 = sqrt ( JetPx[jj2]*JetPx[jj2] + JetPy[jj2]*JetPy[jj2] + JetPz[jj2]*JetPz[jj2] );
        float minv = sqrt(2.*(Ej*Ej2 - JetPx[jj]*JetPx[jj2] - JetPy[jj]*JetPy[jj2] - JetPz[jj]*JetPz[jj2] ) ); 
        pZjj[1] = JetPx[jj] + JetPx[jj2];
        pZjj[2] = JetPy[jj] + JetPy[jj2];
        pZjj[3] = JetPz[jj] + JetPz[jj2];
        float pZ2 = pZjj[1]*pZjj[1] + pZjj[2]*pZjj[2] + pZjj[3]*pZjj[3]; 
        pZjj[0] = sqrt(minv*minv + pZ2 );
        float m2mujj = 0.;
        if(itagZe  > 0 )  hMjjZe->Fill(minv);
        if(itagZmu > 0 ) {
          hMjjZmu->Fill(minv);
          m2mujj = sqrt( minv*minv + pZ[4]*pZ[4] + 2.*( pZjj[0]*pZ[0] - 
                   - pZjj[1]*pZ[1] - pZjj[2]*pZ[2] - pZjj[3]*pZ[3] ) ) ;
          hMHmmjj->Fill(m2mujj);		
        }	  
        if(JetCSV[jj] < 0.8 || JetCSV[jj2] < 0.8 ) continue;
        if(itagZe  > 0 )  hMbbZe->Fill(minv);
        if(itagZmu > 0 )  {
          hMbbZmu->Fill(minv);
          hMHmmbb->Fill(m2mujj);
        }	 	       
      } // next jet2	     
    } // next jet
  } // endif Njets > 1 
  //       if(idbg1 == 1 ) std::cout << "Wjj ana done" <<  std::endl;

  //   if(Nbjets_medium < 1 )    continue;
  //    if(Nbjets_medium < 2 )    continue;
  MEt = mEt;
  hMET->Fill(MEt);

  //	if(MEt < 30. )            continue;
  double MEtx = mEx;
  double MEty = mEy;
  double MTW = sqrt(2.*(MEt*LeptPt[imutrigg] - MEtx*LeptPx[imutrigg] - MEty*LeptPy[imutrigg]) ); 	
  hptmu->Fill(ptlmax);

//   top control plots --------
  if(MEt > 30. ) {	
    hMTW->Fill(MTW);
    if(MTW>40.) hNbjets->Fill(Nbjets_medium); 
    if(Nbjets_medium > 0)  hMTWbjets->Fill(MTW);
    if(Nbjets_medium > 1)  hMTW2bjets->Fill(MTW);   // pure top sample 
    if(Nbjets_medium > 1)  {   // tt selection	    
      // look for W->jj  -------------------------
      float pZjj[5];
      for ( int jj=0; jj < Ngoodjets-1; jj++) {
        if(JetCSV[jj] > 0.4 )     continue;   // btag veto
        float Ej = sqrt ( JetPx[jj]*JetPx[jj] + JetPy[jj]*JetPy[jj] + JetPz[jj]*ElePz[jj] );
        for ( int jj2=jj+1; jj2 < Ngoodjets; jj2++) {
          if( JetCSV[jj2] > 0.4 ) continue;     // btag veto
          if(JetPt[jj] < 25. || JetPt[jj2] < 25.) continue;
          float Ej2 = sqrt ( JetPx[jj2]*JetPx[jj2] + JetPy[jj2]*JetPy[jj2] + JetPz[jj2]*JetPz[jj2] );
          float minv = sqrt(2.*(Ej*Ej2 - JetPx[jj]*JetPx[jj2] - JetPy[jj]*JetPy[jj2] - JetPz[jj]*JetPz[jj2] ) ); 
          pZjj[1] = JetPx[jj] + JetPx[jj2];
          pZjj[2] = JetPy[jj] + JetPy[jj2];
          pZjj[3] = JetPz[jj] + JetPz[jj2];
          float pZ2 = pZjj[1]*pZjj[1] + pZjj[2]*pZjj[2] + pZjj[3]*pZjj[3]; 
          pZjj[0] = sqrt(minv*minv + pZ2 );
          hMWjjtop->Fill(minv);	 	       
        } // next jet2	     
      } // next jet1
    } // endif 2 btags   
  } // endif MET > 30	


  hNtaurec->Fill(Ngoodtaus); // rec taus

/*
  // invariant mass tau-mu
  for ( int jmu=0; jmu < Ngoodmuons; jmu++) {
    if(jmu == imutrigg) continue;
    float Emu = sqrt ( MuPx[jmu]*MuPx[jmu] + MuPy[jmu]*MuPy[jmu] + MuPz[jmu]*MuPz[jmu] );
    for ( int jtau=0; jtau < Ngoodtaus; jtau++) {
      if(MuCharge[jmu] == TauCharge[jtau] ) continue;
      float Etau = sqrt ( TauPx[jtau]*TauPx[jtau] + TauPy[jtau]*TauPy[jtau] + TauPz[jtau]*TauPz[jtau] );
      float minv = sqrt(2.*(Emu*Etau - MuPx[jmu]*TauPx[jtau] - MuPy[jmu]*TauPy[jtau] - MuPz[jmu]*TauPz[jtau] ) ); 
      hM2tau->Fill(minv);
    } // next tau
  } // next muon
*/

  // final analysis:   all leptons ############################################
  int idbg = 0;
  int issflag = 0; // isolated same sign lepton flag
  for ( int jmu=0; jmu < Nlept; jmu++ ) {
//         3 lepton analysis : Z + lept
    if ( itagZ == 1  ) {	   
      if( jmu != iZlep1 && jmu != iZlep2 ) {   // 3rd lepton
	       hpt3CR->Fill(LeptPt[jmu]);
               if( LeptFlag[jmu] == 1 ) hptmu3CR->Fill(LeptPt[jmu]);
	       if( LeptFlag[jmu] == 2 ) hpte3CR->Fill(LeptPt[jmu]);
	       if( LeptIso[jmu] < 0.15  )         {   // 3rd iso lepton
	     //    idbg = 1;
  	         hpt3isoCR->Fill(LeptPt[jmu]);
                 if( LeptFlag[jmu] == 1 ) hptmu3isoCR->Fill(LeptPt[jmu]);
	         if( LeptFlag[jmu] == 2 ) hpte3isoCR->Fill(LeptPt[jmu]); }
      } // endif 3rd lepton
    } 	// endif tag Z
//    if(jmu == iltrigg) cout << "jmu == iltrigg" << endl;
    if(jmu == iltrigg)         continue;  // same-sign lepton analysis....
    float DRmin = 99999.;
    for ( int j=0; j < Ngoodjets; j++ ) {
      float deta = LeptEta[jmu] - JetEta[j];
      float dphi = fabs(LeptPhi[jmu] - JetPhi[j]);
      if(dphi > 3.14 )  dphi = 6.28 - dphi; 
      float DR = sqrt(deta*deta + dphi*dphi); 
      if(DR< DRmin) DRmin = DR;
    } // next jet
//    cout << LeptCharge[jmu] << " " << LeptCharge[iltrigg] << " " << MEt << endl;
    if( LeptCharge[jmu] == LeptCharge[iltrigg] &&  MEt > 30.) {  // same sign leptons --------------
//      cout << "same sign leptons " << LeptPt[jmu] << " " << LeptIso[jmu] << endl;
      hptmusame->Fill(LeptPt[jmu]);
      if( LeptPt[jmu]  > 10.  ) hmuisosame->Fill(LeptIso[jmu]);
      if( LeptPt[jmu]  > 10.  ) hmuDRsame->Fill(DRmin);
      if( LeptIso[jmu] < 0.1  ) {	      
        hptmuisosame->Fill(LeptPt[jmu]); // *** signal plot ****
        if(Nbjets_medium > 0) hptmuisosame1b->Fill(LeptPt[jmu]);  // signal, ttH specific
        if(Nbjets_medium > 1) hptmuisosame2b->Fill(LeptPt[jmu]);  // signal, ttH specific	       
//        cout << "LeptPt " << LeptPt[jmu] << endl;
        if( LeptPt[jmu]  > 16. ) {
          issflag = 1 ;
          idbg = 1; 
//          float aeta1 = fabs(LeptEta[iltrigg]);
//          float aeta2 = fabs(LeptEta[jmu]);
//          float aetamax = aeta1;
          aeta1 = fabs(LeptEta[iltrigg]);
          aeta2 = fabs(LeptEta[jmu]);
          aetamax = aeta1;
          if( aeta2 > aeta1 ) aetamax = aeta2;
          hetamuisosame->Fill(aetamax);
          if(Nbjets_medium > 0) hetamuisosame1b->Fill(aetamax);  
          // signal, ttH specific
	         if(Nbjets_medium > 1) hetamuisosame2b->Fill(aetamax);  
          // signal, ttH specific	       
        }	 
        // invariant mass tau-mu	   
        float Emu = sqrt ( MuPx[jmu]*MuPx[jmu] + MuPy[jmu]*MuPy[jmu] + MuPz[jmu]*MuPz[jmu] );
        for ( int jtau=0; jtau < Ngoodtaus; jtau++) {
          if(LeptCharge[jmu] == TauCharge[jtau] ) continue;
          float Etau = sqrt ( TauPx[jtau]*TauPx[jtau] + TauPy[jtau]*TauPy[jtau] + TauPz[jtau]*TauPz[jtau] );
          float minv = sqrt(2.*(Emu*Etau - LeptPx[jmu]*TauPx[jtau] - LeptPy[jmu]*TauPy[jtau] - LeptPz[jmu]*TauPz[jtau] ) ); 
          hM2tau->Fill(minv);
        } // next tau
      }  // endif muiso    
    }  // endif same sign muon & MET > 30. ---------------------------------------------------
    if( LeptCharge[jmu] != LeptCharge[iltrigg]  && MEt > 30. ) {  // opp sign leptons -------------
      hptmuopp->Fill(LeptPt[jmu]);
      if( LeptPt[jmu]  > 10.  ) hmuisoopp->Fill(LeptIso[jmu]);
      if( LeptPt[jmu]  > 10.  ) hmuDRopp->Fill(DRmin);
      if( LeptIso[jmu] < 0.1  ) {
	hptmuisoopp->Fill(LeptPt[jmu]); // 
	if(Nbjets_medium > 0) hptmuisoopp1b->Fill(LeptPt[jmu]);  // signal, ttH specific
	if(Nbjets_medium > 1) hptmuisoopp2b->Fill(LeptPt[jmu]);  // signal, ttH specific
      }	 
    } 	// endif opp signe muon & MET > 30   -------------------------------------------------
    if( LeptCharge[jmu] == LeptCharge[iltrigg] && itagZmu == 1 && MEt < 30. )  { // same sign  CR ------------
      if( LeptPt[jmu]  > 10.  ) hmuisosameCR->Fill(LeptIso[jmu]);
      if( LeptPt[jmu]  > 10.  ) hmuDRsameCR->Fill(DRmin);
      if( LeptIso[jmu] < 0.1  ) hptmuisosameCR->Fill(LeptPt[jmu]);
    }	 // endif same sign in Z CR -------------------------------------------------------------	 	      	   
  } // next lepton 

  // loop again on taus
  for ( int jtau=0; jtau < Ngoodtaus; jtau++ ) {
    if( TauCharge[jtau] == MuCharge[imutrigg] ) {  // same sign taus
      hpttausame->Fill(TauPt[jtau]);
    }  // endif same sign tau
    if( TauCharge[jtau] != MuCharge[imutrigg] ) {  // opp sign taus
      hpttauopp->Fill(TauPt[jtau]);
    } 	   
  } // next tau 

//    W-> jj analysis ---------------------------------------------
  if( issflag == 1 && Ngoodjets > 1 )  {   // isolated same sign leptons	    
    float pZjj[5];
    for ( int jj=0; jj < Ngoodjets-1; jj++) {
      if(JetCSV[jj] > 0.4 )     continue;   // btag veto
      float Ej = sqrt ( JetPx[jj]*JetPx[jj] + JetPy[jj]*JetPy[jj] + JetPz[jj]*ElePz[jj] );
      for ( int jj2=jj+1; jj2 < Ngoodjets; jj2++) {	 
        if( JetCSV[jj2] > 0.4 ) continue;     // btag veto
        if(JetPt[jj] < 25. || JetPt[jj2] < 25.) continue;
        float Ej2 = sqrt ( JetPx[jj2]*JetPx[jj2] + JetPy[jj2]*JetPy[jj2] + JetPz[jj2]*JetPz[jj2] );
        float minv = 2.*(Ej*Ej2 - JetPx[jj]*JetPx[jj2] - JetPy[jj]*JetPy[jj2] - JetPz[jj]*JetPz[jj2] ) ; 
        if(minv < 0.)                           continue;
        minv = sqrt(minv ); 
        pZjj[1] = JetPx[jj] + JetPx[jj2];
        pZjj[2] = JetPy[jj] + JetPy[jj2];
        pZjj[3] = JetPz[jj] + JetPz[jj2];
        float pZ2 = pZjj[1]*pZjj[1] + pZjj[2]*pZjj[2] + pZjj[3]*pZjj[3]; 
        pZjj[0] = sqrt(minv*minv + pZ2 );
        hMWjj->Fill(minv);	 	       
        if(idbg == 1 ) std::cout << " j1, j2 " << jj << ", " << jj2 << " Mjj " << minv << std::endl;
      } // next jet2	     
    } // next jet1
  } // endif isolated same sign leptons 

// ZZ analysis =======================
  if(  itagZ == 1 )  {
    float MZ2 = 0., PxZ2 = 0., PyZ2 = 0, PzZ2 = 0., EZ2= 0.;
    if(Nlept > 3 ) {
      for ( int je=0; je < Nlept-1; je++) {
        if(je == iZlep1 || je == iZlep2 )      continue; 
        float Ee = sqrt ( LeptPx[je]*LeptPx[je] + LeptPy[je]*LeptPy[je] + LeptPz[je]*LeptPz[je] );
        for ( int je2=je+1; je2 < Nlept; je2++) {
          if(je2 == iZlep1 || je2 == iZlep2 )    continue; 
          if(LeptCharge[je] == LeptCharge[je2] ) continue;   // opp  charge
          if(LeptFlag[je]   != LeptFlag[je2] )   continue;   // same flavour
          if(LeptIso[je]  >  0.2 )               continue;
          if(LeptIso[je2] >  0.2 )               continue;
          int iokpt = 0 ;
          if(LeptPt[je] > 10. && LeptPt[je2] >  7.) iokpt = 1;
          if(LeptPt[je] >  7. && LeptPt[je2] > 10.) iokpt = 1;
          if(iokpt == 0 )                        continue;
          float Ee2 = sqrt ( LeptPx[je2]*LeptPx[je2] + LeptPy[je2]*LeptPy[je2] + LeptPz[je2]*LeptPz[je2] );
          float minv = sqrt(2.*(Ee*Ee2 - LeptPx[je]*LeptPx[je2] - LeptPy[je]*LeptPy[je2] - LeptPz[je]*LeptPz[je2] ) ); 
          hMZ2->Fill(minv);
          PxZ2 = LeptPx[je] + LeptPx[je2];
          PyZ2 = LeptPy[je] + LeptPy[je2];
          PzZ2 = LeptPz[je] + LeptPz[je2];
          EZ2 = sqrt( minv*minv + PxZ2*PxZ2 + PyZ2*PyZ2 + PzZ2*PzZ2 ); 
          MZ2 = minv;
          float minv4 = sqrt(MZ1*MZ1 + MZ2*MZ2 + 2.*(EZ1*EZ2 - PxZ1*PxZ2 - PyZ1*PyZ2 - PzZ1*PzZ2  ) ); 
          hM4lept->Fill(minv4);
        } // next ele2
      } // next ele
    } // endif Nlept > 3    
  } // endif Z tagged
   
// #######################################
// debug / printout event ################
// #######################################
  if(idbg == 0 ) return false;
//  cout << "event accepted" << endl;
    
//  gen particles
  for ( iGenP = 0; iGenP < nGenP; ++iGenP ) {
    int pID = genId->at( iGenP );
    int pStatus = genStatus->at( iGenP );
    int mID = genMother->at( iGenP ) >= 0 ?
              genId->at( genMother->at( iGenP ) ) : 0;
    int iprt = 0;
    if( pStatus != 3 )               continue;
    //    if(fabs(pID)==5 )  iprt = 1; // b 
    //    if(fabs(pID)==6 )  iprt = 1; // top 
    if(fabs(pID) < 7 ) iprt = 1; // all quarks 
    if(fabs(pID)==24 ) iprt = 1; // W
    if(fabs(pID)==23 ) iprt = 1; // Z
    if(fabs(pID)==25 ) iprt = 1; // Higgs
    if(fabs(pID)==15 ) iprt = 1;  // taus
    if(fabs(pID)==13 ) iprt = 1;  // muons
    if(fabs(pID)==11 ) iprt = 1;  // electrons
    if(iprt == 0 )                   continue;
    std::cout << " partID " << pID  << " Moth " << mID
              << " Pt " << genPt->at( iGenP )
              << " Eta " << genEta->at( iGenP )
              << " Phi " << genPhi->at( iGenP ) << std::endl ;    		
  }  // next gen particle ----------------

  // leptons ------
  for ( int je=0; je < Nlept; je++) {
    std::cout << " Lept: " << LeptFlag[je]
              << " Pt " << LeptCharge[je]*LeptPt[je]
              << " Eta " << LeptEta[je]
              << " Phi " << LeptPhi[je] << " Iso " << LeptIso[je] << std::endl;
  }
  // jets -----------  
  for ( int je=0; je < Ngoodjets; je++) {
    std::cout << " Jet : " << je
              << " Pt " << JetPt[je]
              << " Eta " << JetEta[je]
              << " Phi " << JetPhi[je]
              <<  " CSV " << JetCSV[je] << std::endl;
  }
  std::cout << "-------------------------------------------------  "
            << std::endl;
	
  if (debugFlag)
    std::cout << "Ngoodmuons: " << Ngoodmuons << std::endl;

// Apply selection ##########################
  if (Ngoodjets<2) return false;
// ##########################################
  Nevents_2j++;


	
// Apply selection #####################################
  if (Ngoodmuons<2 and Ngoodeles<2) return true;
// #################################################

  Nevents_2j_2l++;
  if (Nbjets_medium>=1) Nevents_2j_2l_1b++;
  if (Nbjets_medium>=2) Nevents_2j_2l_2b++;

  if (Ngoodmuons>=2) {
    Nevents_2j_2mu++;
    if (MuPt[0]<Lep1PtCut and MuPt[1]<Lep2PtCut) good_event = false;
  }
  if (debugFlag)
    std::cout << "DONE w/ muons" << std::endl;
  
  if (Ngoodeles>=2) {
    Nevents_2j_2e++;
    if (ElePt[0]<Lep1PtCut and ElePt[1]<Lep2PtCut) good_event = false;
  }
  
  if (debugFlag)
    std::cout << "DONE w/ electrons" << std::endl;

  // Impose requirement on Missing Et
  // --------------------------------
  MEt = mEt;
  //	std::cout << " MET " << MEt << " METx " <<  mEx << " METy " <<  mEy <<   std::endl;
  if (MEt<MEtCut) Nevents_2j_2l_met++; 	
  if (debugFlag)
    std::cout << "DONE w/ MET" << std::endl;


  // ================================================================================	
  // hypothesis of Z->qq
  int iJet0 = JetIdx[0];
  int iJet1 = JetIdx[1];
  ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
    p4j0( jetPx->at( iJet0 ),
          jetPy->at( iJet0 ),
          jetPz->at( iJet0 ),
          jetE ->at( iJet0 ) );
  ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
    p4j1( jetPx->at( iJet1 ),
          jetPy->at( iJet1 ),
          jetPz->at( iJet1 ),
          jetE ->at( iJet1 ) );
  Mjj = ( p4j0 + p4j1 ).M();
  if (debugFlag)
    std::cout << "DONE w/ zjj" << std::endl;

  int iMuo0 = MuIdx[0];
  int iMuo1 = MuIdx[1];
  if (Ngoodmuons>=2) {
    ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
      p4m0( muoPx->at( iMuo0 ),
            muoPy->at( iMuo0 ),
            muoPz->at( iMuo0 ),
            muoE ->at( iMuo0 ) );
    ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
      p4m1( muoPx->at( iMuo1 ),
            muoPy->at( iMuo1 ),
            muoPz->at( iMuo1 ),
            muoE ->at( iMuo1 ) );
    Mmm = ( p4m0 + p4m1 ).M();
    mh = ( p4j0 + p4j1 + p4m0 + p4m1 ).M();
  }
  if (debugFlag)
    std::cout << "DONE w/ zmm" << std::endl;

  int iEle0 = EleIdx[0];
  int iEle1 = EleIdx[1];
  if (Ngoodeles>=2) {     
    ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
      p4e0( elePx->at( iEle0 ),
            elePy->at( iEle0 ),
            elePz->at( iEle0 ),
            eleE ->at( iEle0 ) );
    ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
      p4e1( elePx->at( iEle1 ),
            elePy->at( iEle1 ),
            elePz->at( iEle1 ),
            eleE ->at( iEle1 ) );
    Mee = ( p4e0 + p4e1 ).M();
    mh = ( p4j0 + p4j1 + p4e0 + p4e1 ).M();
  }
  if (debugFlag)
    std::cout << "DONE w/ zee" << std::endl;


  // Fill histos of pt of leading jets
  // ---------------------------------




  return flag;

}


void HTTAnalyzer::endJob() {


  // Print result
  // ------------
  cout << eqlumi << endl;
  cout << "\n\nTotal number of events processed " << analyzedEvts << endl;
  cout << "This corresponds to a luminosity of " << analyzedEvts * 1.0/eqlumi << " fb-1" << endl;
  cout << endl;
  cout << "Statistics:" << endl;
  cout << "-----------" << endl;
  cout << "Number of events = " << Nevents << endl;
  cout << "Number of events with 2 jets = " << Nevents_2j << endl;
  cout << "Number of events with 2 jets and 2 muons = " << Nevents_2j_2mu << endl;
  cout << "Number of events with 2 jets and 2 electrons = " << Nevents_2j_2e << endl;
  cout << "Number of events with 2 jets and 2 leptons = " << Nevents_2j_2l << endl;
  cout << "And >=1 CSV>0.679 btag = " << Nevents_2j_2l_1b << endl;
  cout << "And >=2 CSV>0.679 btag = " << Nevents_2j_2l_2b << endl;
  cout << "And MEt<30 GeV = " << Nevents_2j_2l_met << endl;
  cout << "-----------" << endl;
  cout << "simulated HLT tresholds" << std::endl;
  cout << "Number of events with 2 jets and 2 muons = " << Nevents_simHLT_2j_2mu << endl;
  cout << "Number of events with 2 jets and 2 electrons = " << Nevents_simHLT_2j_2e << endl;
  cout << "Number of events with 2 jets and 2 leptons = " << Nevents_simHLT_2j_2l << endl;
  cout << "And >=1 CSV>0.679 btag = " << Nevents_simHLT_2j_2l_1b << endl;
  cout << "And >=2 CSV>0.679 btag = " << Nevents_simHLT_2j_2l_2b << endl;
  cout << "And MEt<30 GeV = " << Nevents_simHLT_2j_2l_met << endl;
  cout << endl;


}


void HTTAnalyzer::save() {
#  if UTIL_USE == FULL
  // explicit saving not necessary for "autoSavedObjects"
  autoSave();
#elif UTIL_USE == BARE
  // explicit save histos when not using the full utility

  hptmuZmax      ->Write();
  hptmuZmin      ->Write();
  hetamax        ->Write();
  hMZgen         ->Write();
  hMZgenAcc      ->Write();

  nevents        ->Write();
  hptmumax       ->Write();
  hptmu2nd       ->Write();
  hptmu          ->Write();
  hptmusame      ->Write();
  hptmuopp       ->Write();
  hptmuisosame   ->Write();
  hptmuisosame1b ->Write();
  hptmuisosame2b ->Write();
  hetamuisosame  ->Write();
  hetamuisosame1b->Write();
  hetamuisosame2b->Write();
  hptmuisoopp    ->Write();
  hptmuisoopp1b  ->Write();
  hptmuisoopp2b  ->Write();
  hptmuisosameCR ->Write();
  hmuiso         ->Write();
  hmuiso2nd      ->Write();
  hmuisosame     ->Write();
  hmuisoopp      ->Write();
  hmuisosameCR   ->Write();
  hmuDRsame      ->Write();
  hmuDRopp       ->Write();
  hmuDRsameCR    ->Write();
  hNtop          ->Write();
  hNW            ->Write();
  hNZ            ->Write();
  hNtaus         ->Write();
  hNmutop        ->Write();
  hNmutau        ->Write();
  hMTW           ->Write();
  hMET           ->Write();
  hMTWbjets      ->Write();
  hMTW2bjets     ->Write();
  hNbjets        ->Write();
  hM2mu          ->Write();
  hM2mub         ->Write();
  hM2leptSS      ->Write();
  hM2leptSSSF    ->Write();
  hM2leptOS      ->Write();
  hM2leptb       ->Write();
  hM2tau         ->Write();
  hNtaurec       ->Write();
  hpttausame     ->Write();
  hpttauopp      ->Write();

  hM2e           ->Write();
  hM2eb          ->Write();

  hMjjZe         ->Write();
  hMbbZe         ->Write();
  hMjjZmu        ->Write();
  hMbbZmu        ->Write();

  hMHmmjj        ->Write();
  hMHmmbb        ->Write();

  hMWjj          ->Write();
  hMWjjtop       ->Write();

  hpt3CR         ->Write();
  hptmu3CR       ->Write();
  hpte3CR        ->Write();
  hpt3isoCR      ->Write();
  hptmu3isoCR    ->Write();
  hpte3isoCR     ->Write();

  hMZ2           ->Write();
  hM4lept        ->Write();

  int nDir = dirMap.size();
  int iDir;
  for ( iDir = 0; iDir < nDir; ++iDir ) {
    int iJet;
    for ( iJet = 1; iJet < nMaxJet; ++iJet ) {
      h_jet_pt [iDir][iJet]->Write();
      h_jet_eta[iDir][iJet]->Write();
      h_jet_CSV[iDir][iJet]->Write();
    }
    int iLep;
    for ( iLep = 1; iLep < nMaxLep; ++iLep ) {
      h_muon_pt [iDir][iLep]->Write();
      h_muon_eta[iDir][iLep]->Write();
      h_ele_pt  [iDir][iLep]->Write();
      h_ele_eta [iDir][iLep]->Write();
    }
    h_met [iDir]->Write();
    h_Mjj [iDir]->Write();
    h_Mmm [iDir]->Write();
    h_Mee [iDir]->Write();
    h_Mll [iDir]->Write();
    h_Mh  [iDir]->Write();
    h_mZqq[iDir]->Write();
    h_mZll[iDir]->Write();
    h_mH  [iDir]->Write();
  }

#endif

  return;
}


void HTTAnalyzer::plot() {
/*
  TCanvas* can = new TCanvas( "muoPt", "muoPt", 800, 600 );
  can->cd();
//  can->Divide( 1, 2 );
//  can->cd( 1 );
  h_muoPt->Draw();
*/
  return;
}


bool HTTAnalyzer::goodJet( int iJet ) {
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


TH1D* HTTAnalyzer::createHisto( const std::string& head,
                                const std::string& tail, int n,
                                int nBin, double xMin, double xMax ) {
  stringstream sstr;
  string nstr;
  const char* cstr;
  sstr.str( "" );
  sstr << head << n << tail;
  nstr = sstr.str();
  cstr = nstr.c_str();
  return new TH1D( cstr, cstr, nBin, xMin, xMax );
}


void HTTAnalyzer::fillHistos( const std::string& name,
                              int Ngoodjets , int JetIdx[],
                              int Ngoodmuons, int  MuIdx[],
                              int Ngoodeles , int EleIdx[] ) {

  std::map<std::string,int>::const_iterator iter = dirMap.find( name );
  std::map<std::string,int>::const_iterator iend = dirMap.end();
  if ( iter == iend ) return;
  int iDir = iter->second;

  for (int ijet=0; ijet<2; ijet++) {
    int idJet = JetIdx[ijet];
    int jjet = ijet + 1;
    h_jet_pt [iDir][jjet]->Fill( jetPt ->at( idJet ) );
    h_jet_eta[iDir][jjet]->Fill( jetEta->at( idJet ) );
    h_jet_CSV[iDir][jjet]->Fill( jetCSV->at( idJet ) );
  }
  if (Ngoodjets>2) h_jet_pt[iDir][3]->Fill( jetPt->at( JetIdx[2] ) );
  if (Ngoodjets>3) h_jet_pt[iDir][4]->Fill( jetPt->at( JetIdx[3] ) );

  if (Ngoodmuons>=2) {
    for (int imuon=0; imuon<2; imuon++) {
      int idMuon = MuIdx[imuon];
      int jmuon = imuon + 1;
      h_muon_pt [iDir][jmuon]->Fill( muoPt ->at( idMuon ) );
      h_muon_eta[iDir][jmuon]->Fill( muoEta->at( idMuon ) );
      h_Mmm[iDir]->Fill( Mmm );
      h_Mll[iDir]->Fill( Mmm );
      h_Mh [iDir]->Fill( mh );
    }
  }
  if (Ngoodeles>=2) {
    for (int iele=0; iele<2; iele++) {
      int idEle = EleIdx[iele];
      int jele = iele + 1;
      h_ele_pt [iDir][jele]->Fill( elePt ->at( idEle ) );
      h_ele_eta[iDir][jele]->Fill( eleEta->at( idEle ) );
      h_Mee[iDir]->Fill( Mee );
      h_Mll[iDir]->Fill( Mee );
      h_Mh [iDir]->Fill( mh );
    }
  }

  if ( mH   > 0 ) h_Mh  [iDir]->Fill( mh );
  if ( mZqq > 0 ) h_mZqq[iDir]->Fill( mZqq );
  if ( mZll > 0 ) h_mZll[iDir]->Fill( mZll );

  return;

}

