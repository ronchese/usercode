#define UTIL_USE FULL
#include "BmmAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"
#include "NtuTool/Read/bin/treeAnalyze.cc"

class BmmAnalyzerInstance: public BmmAnalyzer, public TreeReader {
};

static BmmAnalyzerInstance ai;

