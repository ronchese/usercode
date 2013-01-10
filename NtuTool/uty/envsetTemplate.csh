setenv NTU_TOOL_DIR INSTALLDIR
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${NTU_TOOL_DIR}/lib
if ( `printenv | grep SCRAM_ARCH | awk -F= '{print $1}'` == "SCRAM_ARCH" ) then
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${NTU_TOOL_DIR}/lib/${SCRAM_ARCH}
endif
