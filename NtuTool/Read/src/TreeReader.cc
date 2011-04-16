#include <iostream>

#include "NtuTool/Read/interface/TreeReader.h"
#include "NtuTool/Common/interface/DataHandler.h"
#include "NtuTool/Common/interface/TreeTypeManager.h"

#include "TApplication.h"
#include "TRint.h"
#include "TFile.h"
#include "TChain.h"


TreeReader* TreeReader::readerInstance = 0;


TreeReader::TreeReader(): analyzedEvents( 0 ) {
  handlerManager = new TreeTypeManager;
  if ( readerInstance == 0 ) readerInstance = this;
}


TreeReader::~TreeReader() {
  std::cout << std::endl << analyzedEvents << " events read" << std::endl;
}


TreeReader* TreeReader::getInstance() {
  return readerInstance;
}


void TreeReader::initRead( const std::string& file ) {

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

  return;

}


int TreeReader::loop( int evtmax, int ifirst ) {

  // get number of events
  int evtnum = static_cast<int>( currentTree->GetEntries() );

  // last required event
  if (   evtmax >  0       ) evtmax += ifirst;
  if ( ( evtmax == 0     ) ||
       ( evtmax > evtnum ) ) evtmax  = evtnum;

  int event_file = 0;
  // loop over all events
  int ientry;
  for ( ientry = ifirst; ientry < evtmax; ientry++ ) {
    reset();
    // read tree
    currentTree->GetEntry( ientry );
    // preliminary data process
    process( ientry );
    // perform user analysis
    analyze( ientry, ++event_file, ++analyzedEvents );
  }

  return evtnum;

}


void TreeReader::process( int ientry ) {
// default preliminary process - dummy
  return;
}


void TreeReader::plot( int argc, char* argv[], char flag ) {
  TApplication* app = 0;
  std::string name( treeName + "_app" );
  const char* cn = name.c_str();
  switch ( flag ) {
  case 'b':
    return;
  case 'i':
  case 'j':
    app = new TRint( cn, &argc, argv );
    break;
  default:
    app = new TApplication( cn, &argc, argv );
    break;
  }
  histoPlotted = true;
  if ( flag != 'i' ) plot();
  if ( histoPlotted || ( flag == 'j' ) ) app->Run( kTRUE );
  else std::cout << "no plot to draw" << std::endl;
  return;
}


void TreeReader::save( const std::string& name ) {
  TFile file( name.c_str(), "CREATE" );
  save();
  file.Close();
  return;
}


int TreeReader::events() {
  return analyzedEvents;
}


void TreeReader::autoSave() {
  AutoSavedObject::obj_iter iter = autoSavedObject.begin();
  AutoSavedObject::obj_iter iend = autoSavedObject.end();
  while ( iter != iend ) (*iter++)->Write();
  return;
}


void TreeReader::plot() {
// default analysis - dummy
  histoPlotted = false;
  return;
}


void TreeReader::save() {
// default analysis - dummy
  return;
}


TreeReader::AutoSavedObject&
TreeReader::AutoSavedObject::operator=( const TObject* obj ) {
  objectList.push_back( obj );
  return *this;
}


TreeReader::AutoSavedObject::obj_iter TreeReader::AutoSavedObject::begin() {
  return objectList.begin();
}


TreeReader::AutoSavedObject::obj_iter TreeReader::AutoSavedObject::end() {
  return objectList.end();
}

