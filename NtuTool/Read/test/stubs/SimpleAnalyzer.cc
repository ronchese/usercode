#include <iostream>
#include <math.h>

#include "NtuTool/Read/test/stubs/SimpleAnalyzer.h"
#include "NtuTool/Common/interface/Math.h"


static SimpleAnalyzer ta;


SimpleAnalyzer::SimpleAnalyzer() {
  std::cout << "new SimpleAnalyzer" << std::endl;
}


SimpleAnalyzer::~SimpleAnalyzer() {
}


void SimpleAnalyzer::setUserParameter( const std::string& key,
                                       const std::string& val ) {
  std::cout << "user parameter : " << key << " " << val << std::endl;
  return;
}


void SimpleAnalyzer::book() {

  hist = new TH1F( "hist", "hist", 10, -2.5, 2.5 );

  return;

}


void SimpleAnalyzer::reset() {
  autoReset();
  return;
}


bool SimpleAnalyzer::analyze( int entry, int event_file, int event_tot ) {

  std::cout << " +++++++++++++++++++++++++++ " << std::endl;

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

  std::cout << " --------------------------- " << std::endl;

  return !( i_run % 3 );

}


void SimpleAnalyzer::save() {
  hist->Write();
  return;
}


void SimpleAnalyzer::plot() {
  hist->Draw();
  return;
}


