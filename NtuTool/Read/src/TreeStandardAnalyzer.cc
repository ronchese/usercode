/*
 *  See header file for a description of this class.
 *
 *  $Date: 2011/09/07 12:54:34 $
 *  $Revision: 1.7 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "NtuTool/Read/interface/TreeStandardAnalyzer.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "NtuTool/Read/interface/TreeReader.h"

//---------------
// C++ Headers --
//---------------
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//-------------------
// Initializations --
//-------------------
TreeStandardAnalyzer* TreeStandardAnalyzer::analyzerInstance = 0;

//----------------
// Constructors --
//----------------
TreeStandardAnalyzer::TreeStandardAnalyzer() {
  if ( analyzerInstance == 0 ) analyzerInstance = this;
}

//--------------
// Destructor --
//--------------
TreeStandardAnalyzer::~TreeStandardAnalyzer() {
}


TreeStandardAnalyzer* TreeStandardAnalyzer::getInstance() {
  if ( analyzerInstance == 0 ) analyzerInstance = new TreeStandardAnalyzer;
  return analyzerInstance;
}


//--------------
// Operations --
//--------------
/// run the application
int TreeStandardAnalyzer::run( int argc, char* argv[] ) {

  TreeReader* tr = TreeReader::getInstance();

  std::string treeListName( "treeList" );
  std::string histFileName( "hist.root" );
  std::stringstream nmaxString;
  nmaxString.str( "0" );
  std::stringstream skipString;
  skipString.str( "0" );
  std::stringstream amaxString;
  amaxString.str( "0" );
  char type = 'b';
  bool listMissing = true;
  bool histMissing = true;
  std::string key = "";
  std::string val = "";
  char** argp = argv;
  char** argl = argp++ + argc;
  while ( argp < argl ) {
    std::string args( *argp++ );
    if ( args == "-n" ) {
      nmaxString.str( *argp++ );
      continue;
    }
    if ( args == "-s" ) {
      skipString.str( *argp++ );
      continue;
    }
    if ( args == "-a" ) {
      amaxString.str( *argp++ );
      continue;
    }
    if ( args == "-v" ) {
      key = *argp++;
      val = *argp++;
      tr->setUserParameter( key, val );
      continue;
    }
    if ( listMissing ) {
      treeListName = args;
      listMissing = false;
      continue;
    }
    if ( histMissing ) {
      histFileName = args;
      histMissing = false;
      continue;
    }
    type = *args.c_str();
  }

  std::ifstream treeListFile( treeListName.c_str() );
  int evtmax;
  nmaxString >> evtmax;
  int evskip;
  skipString >> evskip;
  int accmax;
  amaxString >> accmax;

  tr->beginJob();
  tr->book();

  loop( tr, treeListFile, evtmax, evskip, accmax );
  std::cout << std::endl << tr->analyzedEvents() << " events read, "
                         << tr->acceptedEvents() << " accepted" << std::endl;

  tr->endJob();

  argc = 1;
  tr->plot( argc, argv, type );
  tr->save( histFileName );

  return 0;

}


/// loop over files
int TreeStandardAnalyzer::loop( TreeReader* tr, std::ifstream& treeListFile,
                                int evtmax, int evskip, int accmax,
                                bool anaexe ) {

  bool nmaxTotal = ( evtmax > 0 );
  bool skipTotal = ( evskip > 0 );
  bool accByFile = ( accmax < 0 );
  if ( !nmaxTotal ) evtmax = -evtmax;
  if ( !skipTotal ) evskip = -evskip;
  if (  accByFile ) accmax = -accmax;

  char* treeLine = new char[1000];
  char* treeLptr;
  char* treeName;
  int evcount = 0;
  while ( treeListFile.getline( treeLine, 1000 ) ) {
    treeLptr = treeLine;
    while ( *treeLptr == ' ' ) treeLptr++;
    if ( *treeLptr == 'b' ) break;
    if ( *treeLptr == 'B' ) break;
    if ( *treeLptr == 'Y' ) *treeLptr = 'y';
    if ( *treeLptr != 'y' ) continue;
    treeLptr++;
    while ( *treeLptr == ' ' ) treeLptr++;
    treeName = treeLptr;
    while ( ( *treeLptr != ' ' ) &&
            ( *treeLptr != '\0' ) ) treeLptr++;
    *treeLptr = '\0';
    std::cout << "open file " << treeName << std::endl;
    tr->initRead( treeName );
    int tmpmax = ( accByFile ? accmax + tr->acceptedEvents() : accmax );
    int evfile = 
    tr->loop( evtmax, evskip, tmpmax, anaexe );
    int evfana = evfile - evskip;
    if ( evfana <= 0 ) evfana = 0;
    if ( evfana > evtmax ) evcount += evtmax;
    else                   evcount += evfana;
    if ( nmaxTotal ) {
      evtmax -= evfana;
      if ( evtmax <= 0 ) break;
    }
    if ( skipTotal ) evskip -= evfile;
    if ( evskip <= 0 ) evskip = 0;
  }

  delete[] treeLine;
  return evcount;

}



