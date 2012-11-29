#include <iostream>
#include <math.h>

#include "NtuTool/Read/test/stubs/SimpleAnalyzer.h"
#include "NtuTool/Common/interface/Math.h"
#include "TDirectory.h"
#include "TROOT.h"


static SimpleAnalyzer ta;


SimpleAnalyzer::SimpleAnalyzer() {
  std::cout << "new SimpleAnalyzer" << std::endl;
}


SimpleAnalyzer::~SimpleAnalyzer() {
}


void SimpleAnalyzer::beginJob() {
  std::cout << "SimpleAnalyzer::beginJob" << std::endl;
  return;
}


void SimpleAnalyzer::book() {

  // putting "autoSavedObject" in front of the histo creation 
  // it's automatically marked for saving on file
  // doing the same with directories they are replicated in the file

  autoSavedObject =
  hist = new TH1F( "hist", "hist", 10, -2.5, 2.5 );

  autoSavedObject =
  gDirectory->mkdir( "subd" );
  autoSavedObject =
  hisd = new TH1F( "hisd", "hisd", 25, -12.5, 12.5 );

  autoSavedObject =
  gDirectory->GetDirectory( ".." );
  autoSavedObject =
  hisc = new TH1F( "hisc", "hisc", 25, -5.0, 5.0 );

  return;

}


void SimpleAnalyzer::beginFile() {
  std::cout << "open file " << currentFile << std::endl;
  return;
}


void SimpleAnalyzer::reset() {
  autoReset();
  return;
}


bool SimpleAnalyzer::analyze( int entry, int event_file, int event_tot ) {

  std::cout << " +++++++++++++++++++++++++++ " << std::endl;
  std::cout << currentFile << std::endl;

  std::cout << "run: "
            <<  i_run << std::endl;

  int isize = i_vec.size();
  std::cout << "vec size " << isize << std::endl;
  int ipos = 0;
  std::vector<int>::const_iterator i_iter = i_vec.begin();
  std::vector<int>::const_iterator i_iend = i_vec.end();
  while ( i_iter != i_iend ) std::cout << ipos++ << " -> "
                                       << *i_iter++ << std::endl;

  int fsize = f_vpt->size();
  std::cout << "vpt size " << fsize << std::endl;
  int fpos = 0;
  std::vector<float>::const_iterator f_iter = f_vpt->begin();
  std::vector<float>::const_iterator f_iend = f_vpt->end();
  while ( f_iter != f_iend ) std::cout << fpos++ << " -> "
                                       << *f_iter++ << std::endl;

  std::cout << "array length " << n_arr << std::endl;
  int j = 0;
  while ( j < n_arr ) std::cout << i_arr[j++] << " ";
  std::cout << std::endl;

  hist->Fill( ( ( i_run % 10 ) / 2.0 ) - 2.5 );
  hisd->Fill( ( ( i_run % 10 ) / 2.0 ) - 5.5 );
  hisc->Fill( ( ( i_run % 10 ) / 2.0 ) - 3.5 );

  std::cout << " --------------------------- " << std::endl;

  return !( i_run % 3 );

}


void SimpleAnalyzer::endFile() {
  std::cout << "close file " << currentFile << std::endl;
  return;
}


void SimpleAnalyzer::endJob() {
  std::cout << "SimpleAnalyzer::endJob" << std::endl;
  return;
}


void SimpleAnalyzer::plot() {
  gROOT->cd();
  hist->Draw();
  return;
}


// "save" function not needed for auto-saved histos,
// see book() function
//void SimpleAnalyzer::save() {
//  std::cout << "save histos" << std::endl;
//  hist->Write();
//  return;
//}

