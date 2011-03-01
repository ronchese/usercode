#ifndef SimpleAnalyzer_H
#define SimpleAnalyzer_H

#include "NtuTool/Common/test/stubs/SimpleNtuple.h"
//#include "NtuTool/Common/test/stubs/SimpleNtuple.cc"
#include "NtuTool/Read/interface/TreeReader.h"

#include "TH1.h"

// The class used to read the tree must inherit from
// "SimpleTree" containing the tree definition
// "TreeReader" provided by the tool

class SimpleAnalyzer: private SimpleNtuple,
                      private TreeReader {

 public:

  SimpleAnalyzer();
  virtual ~SimpleAnalyzer();

  // functions called at the begin of the event loop
  virtual void setUserParameter( const std::string& key,
                                 const std::string& val );

  // functions called for each event
  virtual void reset();
  virtual void analyze( int entry, int event_file, int event_tot );

  // functions called at the end of the event loop
  virtual void plot();   // plot the histograms on the screen
  virtual void save();   // save the histograms on a ROOT file

 private:

  TH1F* hist;

  // functions to book the histograms
  void book();

  // dummy copy and assignment constructors
  SimpleAnalyzer( const SimpleAnalyzer& );
  SimpleAnalyzer& operator=( const SimpleAnalyzer& );

};


#endif

