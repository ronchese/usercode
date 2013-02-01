#ifndef BmmAnalyzer_H
#define BmmAnalyzer_H

#include "TH1.h"
#include "BmmAnalyzerUtil.h"

class BmmAnalyzer: public BmmAnalyzerUtil {

 public:

  BmmAnalyzer();
  virtual ~BmmAnalyzer();

  // function called before starting the analysis
  virtual void beginJob();

  // functions to book the histograms
  void book();

  // functions called for each event
  virtual bool analyze( int entry, int event_file );
  virtual bool analyze( int entry, int event_file, int event_tot );

  // function called at the end of the analysis
  virtual void endJob();

  // functions called at the end of the event loop
  virtual void plot();   // plot the histograms on the screen
  virtual void save();   // save the histograms on a ROOT file

  bool verbose;

  double eqlumi;

 protected:

 private:

  TH1D* hptmumax;
  TH1D* hptmu2nd;
  TH1D* hptmu;

  // dummy copy and assignment constructors
  BmmAnalyzer( const BmmAnalyzer& );
  BmmAnalyzer& operator=( const BmmAnalyzer& );

};


#endif

