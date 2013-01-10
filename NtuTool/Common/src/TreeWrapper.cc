#include <iostream>

#include "NtuTool/Common/interface/TreeWrapper.h"
#include "NtuTool/Common/interface/DataHandler.h"

#include "TFile.h"
#include "TTree.h"


TreeWrapper::TreeWrapper() {
}


TreeWrapper::~TreeWrapper() {
}


void TreeWrapper::setUserParameter( const std::string& key,
                                    const std::string& val ) {
  std::map<std::string,std::string>::iterator
                                     iter = userParameters.find( key );
  std::map<std::string,std::string>::iterator
                                     iend = userParameters.end();
  if ( iter != iend ) iter->second = val;
  else                userParameters.insert( make_pair( key, val ) );
  return;
}


std::string TreeWrapper::getUserParameter( const std::string& key ) {
  std::map<std::string,std::string>::iterator
                                     iter = userParameters.find( key );
  std::map<std::string,std::string>::iterator
                                     iend = userParameters.end();
  if ( iter != iend ) return iter->second;
  return "";
}


void TreeWrapper::beginJob() {
// default analysis - dummy
  return;
}


void TreeWrapper::book() {
// default analysis - dummy
  return;
}


void TreeWrapper::endJob() {
// default analysis - dummy
  return;
}


void TreeWrapper::plot() {
// default analysis - dummy
  return;
}


void TreeWrapper::save() {
// default analysis - dummy
  return;
}


void TreeWrapper::setBranch( const char* branchName, void* dataPtr,
                             const char* branchData ) {

  newBranch( branchName, dataPtr, branchData )->branchPtr  = 0;
  return;

}


void TreeWrapper::setBranch( const char* branchName, void* dataPtr,
                             const char* branchData,
                             TBranch** branchPtr ) {

  newBranch( branchName, dataPtr, branchData )->branchPtr  = branchPtr;
  return;

}


void TreeWrapper::setBranch( const char* branchName, void* dataPtr,
                             int bufferSize,
                             int splitLevel,
                             const char* branchData ) {

  branch_desc* bDesc =
    newBranch( branchName, dataPtr, branchData );
  bDesc->bufferSize = bufferSize;
  bDesc->splitLevel = splitLevel;
  bDesc->branchPtr  = 0;
  return;

}


void TreeWrapper::setBranch( const char* branchName, void* dataPtr,
                             int bufferSize,
                             int splitLevel,
                             const char* branchData,
                             TBranch** branchPtr ) {

  branch_desc* bDesc =
  newBranch( branchName, dataPtr, branchData );
  bDesc->bufferSize = bufferSize;
  bDesc->splitLevel = splitLevel;
  bDesc->branchPtr  = branchPtr;
  return;

}


void TreeWrapper::reset() {
// default analysis - dummy
  return;
}


bool TreeWrapper::analyze( int entry, int event_file, int event_tot ) {
// default analysis - dummy
  return true;
}


void TreeWrapper::autoReset() {
  branch_rev_iter iter = branchList.rbegin();
  branch_rev_iter iend = branchList.rend();
  while ( iter != iend ) {
    branch_desc* bDesc = *iter++;
    DataHandler* handler = bDesc->dataHandler;
    void* dataPtr = 0;
    if ( bDesc->ppRef ) dataPtr = *reinterpret_cast<void**>(
                                  bDesc->dataPtr );
    else                dataPtr = bDesc->dataPtr;
    if ( dataPtr == 0 ) continue;
    handler->reset( dataPtr );
  }
  return;
}


TreeWrapper::branch_iterator TreeWrapper::treeBegin() {
  return branchList.begin();
}


TreeWrapper::branch_iterator TreeWrapper::treeEnd() {
  return branchList.end();
}


TreeWrapper::branch_desc* TreeWrapper::newBranch( const char* branchName,
                                                  void* dataPtr,
                                                  const char* branchData ) {
  branch_desc* bDesc = new branch_desc;
  bDesc->branchName  = new std::string( branchName );
  bDesc->dataPtr     = dataPtr;
  bDesc->branchData  = new std::string( branchData );
  bDesc->branchPtr   = 0;
  bDesc->bufferSize  =
  bDesc->splitLevel  = -999;
  bDesc->ppRef       = false;
  bDesc->dataHandler = 0;
  branchList.push_back( bDesc );
  return bDesc;
}

