#!/bin/sh

export VERSION=$1
export INSTDIR=$2

export SUFFIX=`echo ${VERSION} | awk -F_ '{printf($2); for (i=3; i<=NF; i++)printf("_"$i)}'`

cd ${INSTDIR}
cmsenv

if [ ! -s "${ROOTSYS}" ]; then
echo "${VERSION}: "
echo "${ROOTSYS} not found"
exit
fi

cd ${NTU_TOOL_DIR}

echo "build lib for "${VERSION}
c++ -I.. `root-config --cflags` -fPIC \
    --shared -o ${NTU_TOOL_DIR}/lib/libNtupleTool_cms_${SUFFIX}.so \
    Common/src/*.cc  Read/src/*.cc


