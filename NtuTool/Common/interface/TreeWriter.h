#ifndef TreeWriter_h
#define TreeWriter_h

#include "NtuTool/Common/interface/TreeWrapper.h"

class TreeWriter: public virtual TreeWrapper {

 public:

  TreeWriter();
  virtual ~TreeWriter();

  virtual void initWrite();
  virtual void fill();
  virtual void close();

 protected:

 private:

  TreeWriter( const TreeWriter& t );
  TreeWriter& operator=( const TreeWriter& t );

};


#endif
