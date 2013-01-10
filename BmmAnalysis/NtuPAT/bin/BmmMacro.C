// macro to read the ntuples and run the analysis interactively inside ROOT
// WARNING: some symbolic links are required, to set them issue the 
// command "setupMacroAnalysis.csh" before starting ROOT
// To compile and run issue the following commands inside ROOT:
// root [0] .L BmmMacro.C++
// root [1] BmmMacro("dataset", eqlumi);
// the ntuples listed in "ntu_dataset.list" will be read,
// an integrated lumi will be used


#define UTIL_USE BARE
#include "BmmAnalysis/NtuPAT/src/BmmNtupleData.cc"
#include "BmmLightNtuple.cc"
#include "BmmAnalyzer.cc"
#include "TFile.h"
#include "TChain.h"
#include <fstream>

//void BmmMacro( const std::string& dataset, double eqlumi ) {
void BmmMacro( const std::string& dataset ) {

  BmmAnalyzer* ntu = new BmmAnalyzer;
  ntu->setUserParameter( "verbose", "t" );
  ntu->beginJob();
  ntu->book();
//  ntu->eqlumi = eqlumi;

  vector<string> fileName;
  std::stringstream sstr;
  std::string ntuListName = "ntu_";
  ntuListName += dataset;
  ntuListName += ".list";
  std::ifstream ntuListFile( ntuListName.c_str() );
  char* ntuLine = new char[1000];
  char* linePtr;
  while ( ntuListFile.getline( ntuLine, 1000 ) ) {
    linePtr = ntuLine;
    while ( *linePtr == ' ' ) ++linePtr;
    if ( *linePtr == 'b' ) break;
    if ( *linePtr == 'B' ) break;
    if ( *linePtr == 'Y' ) *linePtr = 'y';
    if ( *linePtr != 'y' ) continue;
    ++linePtr;
    while ( *linePtr == ' ' ) ++linePtr;
    fileName.push_back( linePtr );
  }

  // set nMax <= 0 to analyze all events
  int nMax = 1000;
//  cout << ntu->eqlumi << endl;

  bool endAna = false;
  int nFiles = fileName.size();
  int idFile = 0;
  for ( idFile = 0; idFile < nFiles; ++idFile ) {
    TChain* c = new TChain( ntu->treeName.c_str() );
    c->Add( fileName[idFile].c_str() );
    TTree* tree = c;
    ntu->openTree( tree );
    int nEvt = tree->GetEntries();
    cout << idFile << " " << fileName[idFile] << " " << ntu->treeName << " "
         << nEvt << endl;
    int iEvt;
    for ( iEvt = 0; iEvt < nEvt; ++iEvt ) {
      if ( ( endAna = ( ( nMax > 0 ) &&
                        ( ntu->analyzedEvents() >= nMax ) ) ) ) break;
      tree->GetEntry( iEvt );
      ntu->analyze( iEvt, iEvt );
    }
    delete c;
    if ( endAna ) break;
  }

  ntu->endJob();
  ntu->plot();
  TFile* histFile = new TFile( "hist.root", "CREATE" );
  ntu->save();
  histFile->Close();
  delete histFile;

  return;

}

