using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//#include "TChain.h"
//#include "TTree.h"
#include "NtuTool/Read/interface/TreeReader.h"

int main( int argc, char* argv[] ) {

  TreeReader* tr = TreeReader::getInstance();

  string treeListName( "treeList" );
  string histFileName( "hist.root" );
  stringstream nmaxString;
  nmaxString.str( "0" );
  stringstream skipString;
  skipString.str( "0" );
  char type = 'b';
  bool listMissing = true;
  bool histMissing = true;
  string key = "";
  string val = "";
  char** argp = argv;
  char** argl = argp++ + argc;
  while ( argp < argl ) {
    string args( *argp++ );
    if ( args == "-n" ) {
      nmaxString.str( *argp++ );
      continue;
    }
    if ( args == "-s" ) {
      skipString.str( *argp++ );
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

  ifstream treeListFile( treeListName.c_str() );
  int evtmax;
  nmaxString >> evtmax;
  int evskip;
  skipString >> evskip;

  bool nmaxTotal = ( evtmax > 0 );
  bool skipTotal = ( evskip > 0 );
  if ( !nmaxTotal ) evtmax = -evtmax;
  if ( !skipTotal ) evskip = -evskip;

  tr->beginJob();
  tr->book();

  char* treeLine = new char[1000];
  char* treeLptr;
  char* treeName;
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
    cout << "open file " << treeName << endl;
//    TFile* file = new TFile( treeName );
//    tr->initRead( file );
    tr->initRead( treeName );
    int evfile = 
    tr->loop( evtmax, evskip );
    int evfana = evfile - evskip;
    if ( evfana <= 0 ) evfana = 0;
    if ( nmaxTotal ) evtmax -= evfana;
    if ( evtmax <= 0 ) break;
    if ( skipTotal ) evskip -= evfile;
    if ( evskip <= 0 ) evskip = 0;
  }

  tr->endJob();

  argc = 1;
  tr->plot( argc, argv, type );
  tr->save( histFileName );

  return 0;

}



