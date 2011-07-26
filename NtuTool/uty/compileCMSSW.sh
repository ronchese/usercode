#!/bin/sh

export VERSION=$1
export INSTDIR=$2

export SUFFIX=`echo ${VERSION} | awk -F_ '{printf($2); for (i=3; i<=NF; i++)printf("_"$i)}'`

unset ROOTSYS

cd ${INSTDIR}
eval `scramv1 runtime -sh`

if [ ! -s "${ROOTSYS}" ]; then
echo "${VERSION}: "
echo "${ROOTSYS} not found"
exit
fi

cd ${NTU_TOOL_DIR}

echo "build lib for "${SCRAM_ARCH}" "${VERSION}

export LIBDIR=${NTU_TOOL_DIR}/lib/${SCRAM_ARCH}
if [ ! -d ${LIBDIR} ]; then
mkdir ${LIBDIR}
fi

c++ -I.. `root-config --cflags` -fPIC \
    --shared -o ${LIBDIR}/libNtupleTool_cms_${SUFFIX}.so \
    Common/src/*.cc  Read/src/*.cc


