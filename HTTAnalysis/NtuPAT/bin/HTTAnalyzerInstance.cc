#include "HTTAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"

class HTTAnalyzerInstance: public HTTAnalyzer, public TreeReader {
};

static HTTAnalyzerInstance ai;

