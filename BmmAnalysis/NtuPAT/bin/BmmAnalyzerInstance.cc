#define UTIL_USE FULL
#include "BmmAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"
#include "NtuTool/Read/bin/treeAnalyze.cc"

class BmmAnalyzerInstance: public BmmAnalyzer, public TreeReader {
  virtual void getEntry( int ientry );
};

void BmmAnalyzerInstance::getEntry( int ientry ) {
  BmmAnalyzer::getEntry( ientry );
}

static BmmAnalyzerInstance ai;

