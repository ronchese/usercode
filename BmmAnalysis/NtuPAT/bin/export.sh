#!/bin/sh

cd `dirname $0`/../../..
export BMM_PATH=BmmAnalysis/NtuPAT
export BMM_PACK=`pwd`/bmmAnalysis.tgz
rm -f ${BMM_PACK}
tar -czf ${BMM_PACK} \
${BMM_PATH}/interface/BmmNtupleData.h     \
${BMM_PATH}/interface/BmmNtupleBranch.h   \
${BMM_PATH}/interface/BmmNtupleBranch.icc \
${BMM_PATH}/interface/BmmNtuple.h         \
${BMM_PATH}/interface/BmmEventSelect.h    \
${BMM_PATH}/src/BmmNtupleData.cc          \
${BMM_PATH}/src/BmmNtuple.cc              \
${BMM_PATH}/src/BmmEventSelect.cc         \
${BMM_PATH}/src/BmmAnalyzerFW.cc          \
${BMM_PATH}/bin/BmmAnalyzer.h             \
${BMM_PATH}/bin/BmmAnalyzer.cc            \
${BMM_PATH}/bin/BmmAnalyzerInstance.cc    \
${BMM_PATH}/bin/compile.csh               \
${BMM_PATH}/bin/TreeLightReader.h         \
${BMM_PATH}/bin/BmmLightNtuple.h          \
${BMM_PATH}/bin/BmmLightNtuple.cc         \
${BMM_PATH}/bin/BmmMacro.C                \
${BMM_PATH}/bin/setupMacroAnalysis.csh    \
${BMM_PATH}/bin/export.sh
echo ${BMM_PACK}
