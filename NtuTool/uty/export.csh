#!/bin/csh

setenv NTU_ROOT_DIR `find ${CMSSW_BASE}/src | grep 'NtuTool$'`
cd ${NTU_ROOT_DIR}

rm -f export.tgz
tar -czf export.tgz                \
         INSTRUCTIONS              \
         VERSION                   \
         Common/interface          \
         Common/src                \
         Read/interface            \
         Read/src                  \
         Read/test/treeAnalyze.cc  \
         uty/install.*h            \
         uty/envset*h              \
         uty/compile.*h            \
         uty/go_compileNtuTool.*h  \
         uty/compile_CMSSW.*h

setenv NTU_TOOL_TMP NtuTool_`head -1 ${NTU_ROOT_DIR}/VERSION | sed s/"\."/_/g`
mkdir ${NTU_TOOL_TMP}

mv export.tgz ${NTU_TOOL_TMP}
cd ${NTU_TOOL_TMP}
tar -xzf export.tgz
rm -f export.tgz

cd ${NTU_ROOT_DIR}
rm -f ${NTU_TOOL_TMP}.tgz
tar -czf ${NTU_TOOL_TMP}.tgz ${NTU_TOOL_TMP}
rm -rf ${NTU_TOOL_TMP}
mv ${NTU_TOOL_TMP}.tgz ..

find ${CMSSW_BASE}/src | grep NtuTool | grep tgz

