#ifndef DataHandlerManager_h
#define DataHandlerManager_h

#include <map>
#include <string>

class DataHandler;
//class DataHandlerFactory;
class DataHandlerMap;

class DataHandlerManager {

 public:

  DataHandlerManager();
  virtual ~DataHandlerManager();

  DataHandler* setHandler( const void* descPtr,
                           const std::string* branchData );
  DataHandler* getHandler( const void* descPtr );
  DataHandler* getHandler( const std::string& dataName );

  /// get concrete object
  DataHandler* getInstance( const std::string* branchData );

  /// register new type
//  void registerHandler( const std::string& code,
//                        DataHandler* handler );

 private:

  DataHandlerManager( const DataHandlerManager& t );
  DataHandlerManager& operator=( const DataHandlerManager& t );

//  DataHandlerFactory* handlerFactory;

  typedef std::map< const void*, DataHandler* > data_map;
  typedef data_map::const_iterator data_iterator;

  data_map dataMap;

  virtual DataHandlerMap* handlerMap() = 0;
//  DataHandler* typeSelector( const std::string& name,
//                             const std::string& code );

};


#endif
