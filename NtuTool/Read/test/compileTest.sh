c++ `root-config --cflags --glibs` \
    -I ${CMSSW_BASE}/src -o treeAnalyze_Base treeAnalyze.cc \
    ${CMSSW_BASE}/src/NtuTool/Common/test/stubs/SimpleNtuple.cc \
    stubs/SimpleAnalyzer.cc \
    -L ${CMSSW_BASE}/lib/${SCRAM_ARCH} \
    -lNtuToolRead -lNtuToolCommon
c++ `root-config --cflags --glibs` \
    -I ${CMSSW_BASE}/src -o treeAnalyze_EDM treeAnalyze.cc \
    ${CMSSW_BASE}/src/NtuTool/Common/test/stubs/SimpleNtuple.cc \
    stubs/EDMSimpleAnalyzer.cc \
    -L ${CMSSW_BASE}/lib/${SCRAM_ARCH} \
    -lNtuToolRead -lNtuToolCommon
