#ifndef EDMTypeWriterManager_H
#define EDMTypeWriterManager_H
/** \class EDMTypeWriterManager
 *
 *  Description: 
 *
 *
 *  $Date: 2010-11-08 13:01:04 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------
#include "NtuTool/Common/interface/DataHandlerManager.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------


//---------------
// C++ Headers --
//---------------
#include <map>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class EDMTypeWriterManager: public DataHandlerManager {

 public:

  /** Constructor
   */
  EDMTypeWriterManager();

  /** Destructor
   */
  virtual ~EDMTypeWriterManager();

  /** Operations
   */
  /// register new type
  static void registerHandler( const std::string& code,
                               DataHandler* handler );

 private:

/*
  typedef std::map<std::string,DataHandler*> handler_map;
  typedef handler_map::const_iterator handler_iterator;
  static handler_map* handlerMap;

  virtual DataHandler* typeSelector( const std::string& name,
                                     const std::string& code );
*/
  static DataHandlerMap* etwMap;
  virtual DataHandlerMap* handlerMap();

};


#endif // EDMTypeWriterManager_H






