#include "BmmAnalysis/NtuPAT/interface/BmmTrigPathMap.h"
#include <iostream>

ClassImp(BmmTrigPathMap)

BmmTrigPathMap::BmmTrigPathMap() {
}


BmmTrigPathMap::BmmTrigPathMap( const std::map<int,std::string>& pathMapIS,
                                const std::map<std::string,int>& pathMapSI ):
 trigPathMapIS( pathMapIS ),
 trigPathMapSI( pathMapSI ) {
}


BmmTrigPathMap::~BmmTrigPathMap() {
}


const std::map<int,std::string>* BmmTrigPathMap::mapIS() {
  return &trigPathMapIS;
}


const std::map<std::string,int>* BmmTrigPathMap::mapSI() {
  return &trigPathMapSI;
}


std::string BmmTrigPathMap::get( int         path ) const {
  std::map<int,std::string>::const_iterator
    iter = trigPathMapIS.find( path );
  std::map<int,std::string>::const_iterator
    iend = trigPathMapIS.end();
  if ( iter != iend ) return iter->second;
  return "";
}


int         BmmTrigPathMap::get( std::string path  ) const {
  std::map<std::string,int>::const_iterator
    iter = trigPathMapSI.find( path );
  std::map<std::string,int>::const_iterator
    iend = trigPathMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


void BmmTrigPathMap::print() const {
  std::map<int,std::string>::const_iterator iter = trigPathMapIS.begin();
  std::map<int,std::string>::const_iterator iend = trigPathMapIS.end();
  while ( iter != iend ) {
    const std::pair<int,std::string>& entry = *iter++;
    std::cout << entry.first << " " << entry.second << std::endl;
  }
}

