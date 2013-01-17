#include <iostream>

#include "NtuTool/Read/interface/TreeReader.h"
#include "NtuTool/Common/interface/DataHandler.h"
#include "NtuTool/Common/interface/TreeTypeManager.h"

#include "TFile.h"
#include "TChain.h"


TreeReader* TreeReader::readerInstance = 0;


TreeReader::TreeReader():
 analyzedEvts( 0 ),
 acceptedEvts( 0 ) {
  handlerManager = new TreeTypeManager;
  if ( readerInstance == 0 ) readerInstance = this;
}


TreeReader::~TreeReader() {
}


TreeReader* TreeReader::getInstance() {
  return readerInstance;
}


TChain* TreeReader::initRead( const std::string& file ) {

  currentFile = file;

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
    if ( ( bDesc->ppRef ) ||
         ( bDesc->splitLevel < 0 ) ) dataPtr =  bDesc->dataPtr;
    else                             dataPtr = &bDesc->dataPtr;
    if ( bDesc->splitLevel < 0 ) handler->setAuxPtr( bDesc->dataPtr,
                                                     handlerManager );
    currentTree->SetBranchAddress( bDesc->branchName->c_str(), dataPtr,
                                   bDesc->branchPtr );
  }

  return c;

}


int TreeReader::loop( int evtmax, int evskip, int accmax, bool anaexe ) {

  // get number of events
  int evtnum = static_cast<int>( currentTree->GetEntries() );

  // last required event
  if (   evtmax >  0       ) evtmax += evskip;
  if ( ( evtmax == 0     ) ||
       ( evtmax > evtnum ) ) evtmax  = evtnum;

  if ( !anaexe ) return evtnum;
  if (   accmax == 0       ) accmax  = evtnum + acceptedEvts;

  beginFile();
  int analyzedFile = 0;
  // loop over all events
  int ientry;
  for ( ientry = evskip; ientry < evtmax; ientry++ ) {
    if ( acceptedEvts >= accmax ) break;
    reset();
    // read tree
    currentTree->GetEntry( ientry );
    // preliminary data process
    process( ientry );
    // perform user analysis
    if ( analyze( ientry, analyzedFile++, analyzedEvts++ ) )
                                          acceptedEvts++;
  }
  endFile();

  return evtnum;

}


void TreeReader::process( int ientry ) {
// default preliminary process - dummy
  return;
}


int TreeReader::analyzedEvents() {
  return analyzedEvts;
}


int TreeReader::acceptedEvents() {
  return acceptedEvts;
}

