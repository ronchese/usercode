#!/bin/csh

INSTALLDIR=`/bin/pwd`

rm -f uty/envset.sh
sed s#INSTALLDIR#${INSTALLDIR}# uty/envsetTemplate.sh  > uty/envset.sh
rm -f uty/envset.csh
sed s#INSTALLDIR#${INSTALLDIR}# uty/envsetTemplate.csh > uty/envset.csh

source uty/envset.csh

mv Read/test/treeAnalyze.cc Read/src
rmdir Read/test

rm -rf CVS
rm -rf */CVS
rm -rf */*/CVS
rm -rf */*/*/CVS

mkdir include
mkdir lib

cd include
eval `ls -1 ../*/interface/*h ../*/interface/*icc | awk '{print "ln -s "$0";"}'`
ln -s ${NTU_TOOL_DIR} ${NTU_TOOL_DIR}/include/NtuTool

