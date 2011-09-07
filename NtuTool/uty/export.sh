#!/bin/sh

cd ${CMSSW_BASE}/src
export NTU_ROOT_DIR=`find . | grep 'NtuTool$'`
cd ${NTU_ROOT_DIR}
cd ..

rm -f NtuTool.tgz
tar -czf NtuTool.tgz                                   \
         NtuTool/INSTRUCTIONS                          \
         NtuTool/Common/interface NtuTool/Common/src   \
         NtuTool/Read/interface NtuTool/Read/src       \
         NtuTool/Read/test/treeAnalyze.cc              \
         NtuTool/uty/install.*h NtuTool/uty/envset*h   \
         NtuTool/uty/compile.*h                        \
         NtuTool/uty/compile_CMSSW.*h                  \
         NtuTool/uty/go_compileNtuTool.*h
