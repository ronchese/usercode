#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "BmmAnalysis/NtuPAT/interface/BmmEventSelect.h"

#include <iostream>
#include <fstream>
#include <sstream>

BmmEventSelect::BmmEventSelect() {
}


BmmEventSelect::~BmmEventSelect() {
}


void BmmEventSelect::read( const std::string& name ) {
  if ( name == "" ) return;
  std::ifstream file( name.c_str() );
  std::stringstream sstr;
  char* line = new char[1000];
  while ( file.getline( line, 1000 ) ) {
    std::cout << line << std::endl;
    char* lptr = line;
    while ( *lptr == ' ' ) ++lptr;
    if ( ( *lptr < '0' ) ||
         ( *lptr > '9' ) ) continue;
    sstr.clear();
    sstr.str( lptr );
    ev_id evId;
    std::cout << lptr << std::endl;
    sstr >> evId.run >> evId.event;
    std::cout << "insert " << evId.run << " " << evId.event << std::endl;
    eventSet.insert( evId );
  }
  std::cout << eventSet.size() << std::endl;
  delete[] line;
  return;
}


bool BmmEventSelect::find( unsigned int run, unsigned int event ) {
  if ( eventSet.size() == 0 ) return true;
  ev_id evId;
  evId.run   = run;
  evId.event = event;
  if ( eventSet.find( evId ) != eventSet.end() ) return true;
  return false;
}



