#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include "BmmAnalysis/NtuPAT/interface/BmmEventSelect.h"

#include <iostream>
#include <fstream>
#include <sstream>

BmmEventSelect::ev_compare BmmEventSelect::ev_compare::instance;

BmmEventSelect::BmmEventSelect() {
}


BmmEventSelect::~BmmEventSelect() {
}


void BmmEventSelect::read( const std::string& name ) {
  if ( name == "" ) return;
  std::ifstream file( name.c_str() );
  std::stringstream sstr;
  char* line = new char[1000];
  std::vector<ev_id> evList;
  evList.reserve( 100000 );
  while ( file.getline( line, 1000 ) ) {
    char* lptr = line;
    while ( *lptr == ' ' ) ++lptr;
    if ( ( *lptr < '0' ) ||
         ( *lptr > '9' ) ) continue;
    sstr.clear();
    sstr.str( lptr );
    ev_id evId;
    sstr >> evId.run >> evId.event;
    evList.push_back( evId );
  }
  sort( evList.begin(), evList.end(), ev_compare::instance );
  eventSet.insert( evList.begin(), evList.end() );
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



