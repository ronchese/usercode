#!/bin/csh

setenv VERSION $1
setenv INSTDIR $2

setenv SUFFIX `echo ${VERSION} | awk -F_ '{printf($2); for (i=3; i<=NF; i++)printf("_"$i)}'`

cd ${INSTDIR}
eval `scramv1 runtime -csh`

if ( ! -s "${ROOTSYS}" ) then
echo "${VERSION}: "
echo "${ROOTSYS} not found"
exit
endif

cd ${NTU_TOOL_DIR}

echo "build lib for "${VERSION}
c++ -I.. `root-config --cflags` -fPIC \
    --shared -o ${NTU_TOOL_DIR}/lib/libNtupleTool_cms_${SUFFIX}.so \
    Common/src/*.cc  Read/src/*.cc


