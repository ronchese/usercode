#!/bin/csh

setenv VERSION $1
setenv INSTDIR $2

setenv SUFFIX `echo ${VERSION} | awk -F_ '{printf($2); for (i=3; i<=NF; i++)printf("_"$i)}'`

unsetenv ROOTSYS

cd ${INSTDIR}
eval `scramv1 runtime -csh`

if ( ! -s "${ROOTSYS}" ) then
echo "${VERSION}: "
echo "${ROOTSYS} not found"
exit
endif

cd ${NTU_TOOL_DIR}

echo "build lib for "${SCRAM_ARCH}" "${VERSION}

setenv LIBDIR ${NTU_TOOL_DIR}/lib/${SCRAM_ARCH}
if ( ! -d ${LIBDIR} ) then
mkdir ${LIBDIR}
endif

c++ -I.. `root-config --cflags` -fPIC \
    --shared -o ${LIBDIR}/libNtupleTool_cms_${SUFFIX}.so \
    Common/src/*.cc  Read/src/*.cc


