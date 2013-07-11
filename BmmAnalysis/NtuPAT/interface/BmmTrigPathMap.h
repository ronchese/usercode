#ifndef BmmTrigPathMap_H
#define BmmTrigPathMap_H

#include "TObject.h"

#include <map>
#include <string>

class BmmTrigPathMap: public TObject {

  ClassDef(BmmTrigPathMap,1)

 public:

  BmmTrigPathMap();
  BmmTrigPathMap( const std::map<int,std::string>& pathMapIS,
                  const std::map<std::string,int>& pathMapSI );
  ~BmmTrigPathMap();

  const std::map<int,std::string>* mapIS();
  const std::map<std::string,int>* mapSI();

  std::string get( int         path ) const;
  int         get( std::string path ) const;
  void print() const;

 private:

  std::map<int,std::string> trigPathMapIS;
  std::map<std::string,int> trigPathMapSI;

};

#endif

