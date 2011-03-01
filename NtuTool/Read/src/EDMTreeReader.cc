//using namespace std;
#include <iostream>

#include "NtuTool/Read/interface/EDMTreeReader.h"
#include "NtuTool/Read/interface/EDMTypeReaderManager.h"
#include "NtuTool/Common/interface/DataHandlerManager.h"
#include "NtuTool/Common/interface/DataHandler.h"
#include "NtuTool/Common/interface/DataConvert.h"

#include "TFile.h"
#include "TChain.h"


EDMTreeReader::EDMTreeReader() {
  handlerManager = new EDMTypeReaderManager;
}


EDMTreeReader::~EDMTreeReader() {
}


//void EDMTreeReader::initRead( TFile* file ) {
void EDMTreeReader::initRead( const std::string& file ) {

//  currentTree = dynamic_cast<TTree*>( file->Get( treeName.c_str() ) );
  TChain* c = new TChain( treeName.c_str() );
  c->Add( file.c_str() );
  currentTree = c;
  currentTree->SetMakeClass(1);

  branch_iterator iter = treeBegin();
  branch_iterator iend = treeEnd();
  while ( iter != iend ) {
    branch_desc* bDesc = *iter++;
    DataHandler* handler = handlerManager->setHandler( bDesc,
                                                       bDesc->branchData );
    bDesc->dataHandler = handler;
    void* dataPtr = 0;
    if ( bDesc->ppRef ) dataPtr = *reinterpret_cast<void**>( bDesc->dataPtr );
    else                dataPtr = handler->setAuxPtr(        bDesc->dataPtr );
    std::string branchName( handler->getBranchName( processName,
                                                    producerName ) );
    if ( bDesc->branchPtr == 0 ) bDesc->branchPtr = new TBranch*;
    currentTree->SetBranchAddress( branchName.c_str(), dataPtr,
                                                       bDesc->branchPtr );
/*
    if ( bDesc->branchPtr != 0 ) {
      std::cout << "address: " << dataPtr << std::endl;
      currentTree->SetBranchAddress( branchName.c_str(), dataPtr,
                                                         bDesc->branchPtr );
    }
    else {
      currentTree->SetBranchAddress( branchName.c_str(), dataPtr );
    }
    handler->setMemberPtr( currentTree, branchName, bDesc->dataPtr );
*/

//    if ( bDesc->branchPtr != 0 )
//      currentTree->SetBranchAddress( branchName.c_str(), dataPtr,
//                                                         bDesc->branchPtr );
//    else
//      currentTree->SetBranchAddress( branchName.c_str(), dataPtr );
//    handler->setMemberPtr( currentTree, branchName, bDesc->dataPtr );
  }

  return;

}


void EDMTreeReader::setProcessName( const std::string& name ) {
  processName = name;
  return;
}


void EDMTreeReader::setProducerName( const std::string& name ) {
  producerName = name;
  return;
}


void EDMTreeReader::process( int ientry ) {

  branch_iterator iter = treeBegin();
  branch_iterator iend = treeEnd();
  while ( iter != iend ) {
    const branch_desc* bDesc = *iter++;
    TBranch* branchPtr = *bDesc->branchPtr;
    branchPtr->GetEntry( ientry );
    DataHandler* handler = bDesc->dataHandler;
    handler->process( bDesc->dataPtr );
  }

  return;

}

