#!/bin/csh

cd ${CMSSW_BASE}/src
setenv NTU_ROOT_DIR `find . | grep 'NtuTool$'`
cd ${NTU_ROOT_DIR}
cd ..

rm -f NtuTool.tgz
tar -czf NtuTool.tgz                                   \
         NtuTool/INSTRUCTIONS                          \
         NtuTool/VERSION                               \
         NtuTool/Common/interface NtuTool/Common/src   \
         NtuTool/Read/interface NtuTool/Read/src       \
         NtuTool/Read/test/treeAnalyze.cc              \
         NtuTool/uty/install.*h NtuTool/uty/envset*h   \
         NtuTool/uty/compile.*h                        \
         NtuTool/uty/go_compileNtuTool.*h NtuTool/uty/compileCMSSW.*h
