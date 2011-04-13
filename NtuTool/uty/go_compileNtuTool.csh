#!/bin/csh
cd ${NTU_TOOL_DIR}
eval `scramv1 list CMSSW | awk '($1 == "CMSSW") {printf("uty/compileCMSSW.csh "$2" ")} ($1 == "-->") {print $2";"}'`
