#!/bin/csh

cd ${CMSSW_BASE}/src/NtuTool/Read/test

rm -rf tmp_export
mkdir tmp_export
cd ${CMSSW_BASE}/src/NtuTool/Read/test/tmp_export

cp ${CMSSW_BASE}/src/NtuTool/Common/test/stubs/SimpleNtuple.h      .
cp ${CMSSW_BASE}/src/NtuTool/Common/test/stubs/SimpleNtuple.cc     .
cp ${CMSSW_BASE}/src/NtuTool/Read/test/stubs/SimpleAnalyzer.h      .
cp ${CMSSW_BASE}/src/NtuTool/Read/test/stubs/SimpleAnalyzer.cc     .
cp ${CMSSW_BASE}/src/NtuTool/Read/test/stubs/EDMSimpleAnalyzer.h   .
cp ${CMSSW_BASE}/src/NtuTool/Read/test/stubs/EDMSimpleAnalyzer.cc  .
cp ${CMSSW_BASE}/src/NtuTool/Read/test/ntuList                     .
cp ${CMSSW_BASE}/src/NtuTool/Read/test/edmList                     .

sed -i s/"NtuTool\/Common\/test\/stubs\/"// SimpleNtuple.cc
sed -i s/"NtuTool\/Common\/test\/stubs\/"// SimpleAnalyzer.h
sed -i s/"NtuTool\/Common\/test\/stubs\/"// SimpleAnalyzer.cc
sed -i s/"NtuTool\/Common\/test\/stubs\/"// EDMSimpleAnalyzer.h
sed -i s/"NtuTool\/Common\/test\/stubs\/"// EDMSimpleAnalyzer.cc
sed -i s/"NtuTool\/Read\/test\/stubs\/"// SimpleAnalyzer.h
sed -i s/"NtuTool\/Read\/test\/stubs\/"// SimpleAnalyzer.cc
sed -i s/"NtuTool\/Read\/test\/stubs\/"// EDMSimpleAnalyzer.h
sed -i s/"NtuTool\/Read\/test\/stubs\/"// EDMSimpleAnalyzer.cc

tar -czf examples.tgz *

cd ${CMSSW_BASE}/src/NtuTool/Read/test
rm -rf tmp_export

