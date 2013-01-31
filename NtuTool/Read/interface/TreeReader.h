#ifndef TreeReader_h
#define TreeReader_h

#include "NtuTool/Common/interface/TreeWrapper.h"

#include <string>

class TChain;

class TreeReader: public virtual TreeWrapper {

 public:

  TreeReader();
  virtual ~TreeReader();

  static TreeReader* getInstance();

  virtual TChain* initRead( const std::string& file );
  virtual int  loop( int evtmax = 0, int evskip = 0, int accmax = 0, 
                     bool anaexe = true );

 protected:

  std::string currentFile;

  virtual void getEntry( int ientry );
  virtual void process( int ientry );

 private:

  static TreeReader* readerInstance;

  TreeReader( const TreeReader& t );
  TreeReader& operator=( const TreeReader& t );

};


#endif
