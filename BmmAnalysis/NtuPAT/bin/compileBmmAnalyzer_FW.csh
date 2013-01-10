
#### script to compile an executable to read the ntuples
#### WARNING: the code performing the actual analysis is 
#### compiled by issuing a "scram b" in ${CMSSW_BASE}/src

#### to run: 
#### rm -f hist.root ; treeAnalyze ntu_dataset.list hist.root -v eqlumi=...
#### WARNING: the output file (hist.root) MUST be removed before running
#### see NtuTool/INSTRUCTIONS for running options

rm -f treeAnalyze
c++ `root-config --cflags --glibs` -D UTIL_USE=FULL \
    -I ${CMSSW_BASE}/src -o treeAnalyze \
    ${CMSSW_BASE}/src/NtuTool/Read/bin/treeAnalyze.cc \
    ${CMSSW_BASE}/src/BmmAnalysis/NtuPAT/bin/BmmAnalyzerInstance.cc \
    -L ${CMSSW_BASE}/lib/${SCRAM_ARCH} \
    -lBmmAnalysisNtuPAT -lNtuToolRead -lNtuToolCommon

