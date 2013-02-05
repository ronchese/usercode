#ifndef BmmEventSelect_H
#define BmmEventSelect_H

#include <set>
#include <string>

class BmmEventSelect {

 public:

  BmmEventSelect();
  virtual ~BmmEventSelect();

  virtual void read( const std::string& name );
  virtual bool find( unsigned int run, unsigned int event );

 private:

  // dummy copy and assignment constructors
  BmmEventSelect( const BmmEventSelect& );
  BmmEventSelect& operator=( const BmmEventSelect& );

  struct ev_id {
    unsigned int run;
    unsigned int event;
  };
  class ev_compare {
   public:
    bool operator()( const ev_id& l, const ev_id& r ) const {
      if ( l.run   < r.run   ) return true;
      if ( l.run   > r.run   ) return false;
      if ( l.event < r.event ) return true;
      return false;
    }
    static ev_compare instance;
  };
  std::set<ev_id, ev_compare> eventSet;

};


#endif

