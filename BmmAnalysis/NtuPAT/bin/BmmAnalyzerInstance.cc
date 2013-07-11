#define UTIL_USE FULL
#include "BmmAnalyzer.h"
#include "BmmAnalysis/NtuPAT/interface/BmmTrigPathMap.h"
#include "NtuTool/Read/interface/TreeReader.h"
#include "NtuTool/Read/bin/treeAnalyze.cc"
#include "TFile.h"
#include <iostream>

class BmmAnalyzerInstance: public BmmAnalyzer, public TreeReader {
  virtual void getEntry( int ientry );
  // function to do file-specific initialization
  virtual void beginFile();
  // function to do file-specific final operations
  virtual void endFile();
};

void BmmAnalyzerInstance::getEntry( int ientry ) {
  BmmAnalyzer::getEntry( ientry );
}

void BmmAnalyzerInstance::beginFile() {
  trigMap = dynamic_cast<BmmTrigPathMap*>( currentFile->Get( "trigMap" ) );
  return;
}

void BmmAnalyzerInstance::endFile() {
  std::cout << "drop map" << std::endl;
  delete trigMap;
  trigMap = 0;
}

static BmmAnalyzerInstance ai;

