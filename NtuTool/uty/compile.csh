#!/bin/csh

cd $NTU_TOOL_DIR

c++ -I.. `root-config --cflags` -fPIC \
    --shared -o $NTU_TOOL_DIR/lib/libNtupleTool.so \
    Common/src/*.cc  Read/src/*.cc
