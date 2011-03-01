#!/bin/sh
cd ${NTU_TOOL_DIR}
eval `scramv1 list CMSSW | awk '($1 == "CMSSW") {printf("uty/compileCMSSW.sh "$2" ")} ($1 == "-->") {print $2";"}'`
