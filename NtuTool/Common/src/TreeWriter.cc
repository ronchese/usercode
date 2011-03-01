//using namespace std;
//#include <iostream>

#include "NtuTool/Common/interface/TreeWriter.h"
#include "NtuTool/Common/interface/DataHandler.h"
#include "NtuTool/Common/interface/TreeTypeManager.h"

#include "TTree.h"


TreeWriter::TreeWriter() {
  handlerManager = new TreeTypeManager;
}


TreeWriter::~TreeWriter() {
}


void TreeWriter::initWrite() {

  const char* name = treeName.c_str();
  currentTree = new TTree( name, name );
                           

  branch_iterator iter = treeBegin();
  branch_iterator iend = treeEnd();
  while ( iter != iend ) {
    branch_desc* bDesc = *iter++;
    DataHandler* handler = handlerManager->setHandler( bDesc,
                                                       bDesc->branchData );
    bDesc->dataHandler = handler;
    TBranch* b = 0;
    void** dataPtr = 0;
    if ( bDesc->splitLevel < 0 ) handler->setAuxPtr( bDesc->dataPtr,
                                                     handlerManager );
    if ( bDesc->ppRef ) dataPtr =  reinterpret_cast<void**>( bDesc->dataPtr );
    else                dataPtr = &bDesc->dataPtr;
    if ( bDesc->splitLevel < 0 )
         b = currentTree->Branch( bDesc->branchName->c_str(),
                                  bDesc->dataPtr,
                                  bDesc->branchData->c_str() );
    else b = handler->branch( currentTree, bDesc->branchName, dataPtr,
                              bDesc->bufferSize, bDesc->splitLevel );
    if ( bDesc->branchPtr != 0 ) *bDesc->branchPtr = b;

  }

  return;

}


void TreeWriter::fill() {
  currentTree->Fill();
  return;
}


void TreeWriter::close() {
  currentTree->Write();
  return;
}


