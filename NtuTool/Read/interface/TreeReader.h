#ifndef TreeReader_h
#define TreeReader_h

#include "NtuTool/Common/interface/TreeWrapper.h"

#include <string>

class TObject;

class TreeReader: public virtual TreeWrapper {

 public:

  TreeReader();
  virtual ~TreeReader();

  static TreeReader* getInstance();

  virtual void initRead( const std::string& file );
  virtual int  loop( int evtmax = 999999999, int ifirst = 0 );
  virtual void plot( int argc, char* argv[], char flag );
  virtual void save( const std::string& name );
  void autoSave();

  virtual void plot();
  virtual void save();

  int events();

 protected:

  virtual void process( int ientry );

  class AutoSavedObject {
   public:
    typedef std::vector<const TObject*> obj_list;
    typedef obj_list::const_iterator    obj_iter;
    obj_iter begin();
    obj_iter end();
    AutoSavedObject& operator=( const TObject* obj );
   private:
    obj_list objectList;
  };
  AutoSavedObject autoSavedObject;

 private:

  static TreeReader* readerInstance;
  int analyzedEvents;
  bool histoPlotted;

  TreeReader( const TreeReader& t );
  TreeReader& operator=( const TreeReader& t );

};


#endif
