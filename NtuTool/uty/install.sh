#!/bin/sh

INSTALLDIR=`/bin/pwd`

rm -f envset.tmp
sed s#INSTALLDIR#${INSTALLDIR}# uty/envset.sh  > envset.tmp
rm -f uty/envset.sh
mv envset.tmp uty/envset.sh
sed s#INSTALLDIR#${INSTALLDIR}# uty/envset.csh > envset.tmp
rm -f uty/envset.csh
mv envset.tmp uty/envset.csh

source uty/envset.sh

mv Read/test/treeAnalyze.cc Read/src
rmdir Read/test

rm -rf CVS
rm -rf */CVS
rm -rf */*/CVS
rm -rf */*/*/CVS

mkdir include
mkdir lib

cp */interface/* include
ln -s ${NTU_TOOL_DIR} ${NTU_TOOL_DIR}/include/NtuTool

