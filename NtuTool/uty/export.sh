#!/bin/sh

cd ${CMSSW_BASE}/src
tar -czf NtuTool.tgz                                   \
         NtuTool/Common/interface NtuTool/Common/src   \
         NtuTool/Read/interface NtuTool/Read/src       \
         NtuTool/Read/test/treeAnalyze.cc              \
         NtuTool/uty/install.sh NtuTool/uty/envset*h   \
         NtuTool/uty/compile.sh                        \
         NtuTool/uty/go_compileNtuTool.*h NtuTool/uty/compileCMSSW.*h
