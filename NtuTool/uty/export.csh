#!/bin/csh

cd ${CMSSW_BASE}/src
tar -czf NtuTool.tgz                                   \
         NtuTool/Common/interface NtuTool/Common/src   \
         NtuTool/Read/interface NtuTool/Read/src       \
         NtuTool/Read/test/treeAnalyze.cc              \
         NtuTool/uty/install.*h NtuTool/uty/envset*h   \
         NtuTool/uty/compile.*h                        \
         NtuTool/uty/go_compileNtuTool.*h NtuTool/uty/compileCMSSW.*h
