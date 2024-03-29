#!/bin/sh

#export INSTALLDIR=`/bin/pwd | sed s/"\/"/"\\\/"/g`
#
#rm -f uty/envset.sh
#sed s/INSTALLDIR/${INSTALLDIR}/ uty/envsetTemplate.sh  > uty/envset.sh
#rm -f uty/envset.csh
#sed s/INSTALLDIR/${INSTALLDIR}/ uty/envsetTemplate.csh > uty/envset.csh

cd `dirname $0`/..
export INSTALLDIR=`/bin/pwd`

rm -f uty/envset.sh
sed s#INSTALLDIR#${INSTALLDIR}# uty/envsetTemplate.sh  > uty/envset.sh
rm -f uty/envset.csh
sed s#INSTALLDIR#${INSTALLDIR}# uty/envsetTemplate.csh > uty/envset.csh

. uty/envset.sh

cd ${NTU_TOOL_DIR}/Read/src
rm -f treeAnalyze.cc
ln -s ../bin/treeAnalyze.cc
#mv Read/test/treeAnalyze.cc Read/src
#rmdir Read/test

cd ${NTU_TOOL_DIR}
rm -rf CVS
rm -rf */CVS
rm -rf */*/CVS
rm -rf */*/*/CVS

rm -rf include lib
mkdir include
mkdir lib

cd include
eval `ls -1 ../*/interface/*h ../*/interface/*icc | awk '{print "ln -s "$0";"}'`
ln -s ${NTU_TOOL_DIR} ${NTU_TOOL_DIR}/include/NtuTool

