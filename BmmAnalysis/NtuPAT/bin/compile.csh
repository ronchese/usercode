#!/bin/csh

cd `dirname $0`/..
setenv BMM_PACK_DIR `/bin/pwd`
cd ../..
setenv BMM_ROOT_DIR `/bin/pwd`

setenv BMM_EXE_FILE ${BMM_PACK_DIR}/bin/treeAnalyze
rm -f ${BMM_EXE_FILE}

c++ `root-config --cflags --glibs` \
-I ${BMM_ROOT_DIR} -I ${NTU_TOOL_DIR}/include \
-o ${BMM_PACK_DIR}/bin/treeAnalyze \
${BMM_PACK_DIR}/bin/BmmAnalyzerInstance.cc \
${BMM_PACK_DIR}/src/BmmAnalyzerFW.cc \
${BMM_PACK_DIR}/src/BmmNtuple.cc \
${BMM_PACK_DIR}/src/BmmNtupleData.cc \
${BMM_PACK_DIR}/src/BmmEventSelect.cc \
-L${NTU_TOOL_DIR}/lib -lNtupleTool

echo ${BMM_EXE_FILE}
