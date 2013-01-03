#include "BmmAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"

class BmmAnalyzerInstance: public BmmAnalyzer, public TreeReader {
};

static BmmAnalyzerInstance ai;

