#ifndef TreeStandardAnalyzer_H
#define TreeStandardAnalyzer_H
/** \class TreeStandardAnalyzer
 *
 *  Description: 
 *    Class to steer the tree analysis:
 *          - open all files in sequence
 *          - loop over the tree for each file
 *
 *  $Date: 2011-03-02 13:35:36 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------


//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class TreeStandardAnalyzer {

 public:

  /** Constructor
   */
  TreeStandardAnalyzer();

  /** Destructor
   */
  virtual ~TreeStandardAnalyzer();

  static TreeStandardAnalyzer* getInstance();

  /** Operations
   */
  /// run the application
  virtual int run( int argc, char* argv[] );

 private:

  static TreeStandardAnalyzer* analyzerInstance;

  TreeStandardAnalyzer( const TreeStandardAnalyzer& t );
  TreeStandardAnalyzer& operator=( const TreeStandardAnalyzer& t );

};


#endif // TreeStandardAnalyzer_H

