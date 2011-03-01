#ifndef TreeWrapper_h
#define TreeWrapper_h

#include <vector>
#include <map>
#include <string>
class DataHandler;
class DataHandlerManager;
class TFile;
class TTree;
class TBranch;

class TreeWrapper {

 public:

  TreeWrapper();
  virtual ~TreeWrapper();

  virtual void setUserParameter( const std::string& key,
                                 const std::string& val );
  virtual std::string getUserParameter( const std::string& key );

  virtual void book();
  virtual void beginJob();
  virtual void endJob();
  virtual void plot();
  virtual void save();

 protected:

  std::string treeName;

  // tree pointer
  TTree* currentTree;

  void setBranch( const char* branchName, void* dataPtr,
                  const char* branchData );
  void setBranch( const char* branchName, void* dataPtr,
                  const char* branchData,
                  TBranch** branchPtr );
  void setBranch( const char* branchName, void* dataPtr,
                  int bufferSize,
                  int splitLevel,
                  const char* branchData );
  void setBranch( const char* branchName, void* dataPtr,
                  int bufferSize,
                  int splitLevel,
                  const char* branchData,
                  TBranch** branchPtr );
  template<class T>
  void setBranch( const char* branchName, T* dataPtr,
                  int bufferSize = 32000,
                  int splitLevel = 99 );
  template<class T>
  void setBranch( const char* branchName, T* dataPtr,
                  int bufferSize,
                  int splitLevel,
                  TBranch** branchPtr );
  template<class T>
  void setBranch( const char* branchName, T** dataPtr,
                  int bufferSize = 32000,
                  int splitLevel = 99 );
  template<class T>
  void setBranch( const char* branchName, T** dataPtr,
                  int bufferSize,
                  int splitLevel,
                  TBranch** branchPtr );

  virtual void reset();
  virtual void analyze( int entry, int event_file, int event_tot );

  DataHandlerManager* handlerManager;
  void autoReset();

  struct branch_desc {
    std::string* branchName;
    void*        dataPtr;
    std::string* branchData;
    TBranch**    branchPtr;
    int          bufferSize;
    int          splitLevel;
    bool         ppRef;
    DataHandler* dataHandler;
  };
  typedef std::vector< branch_desc* > branch_list;
  typedef branch_list::const_iterator branch_iterator;
  typedef branch_list::const_reverse_iterator branch_rev_iter;

  branch_iterator treeBegin();
  branch_iterator treeEnd();

 private:

  TreeWrapper( const TreeWrapper& t );
  TreeWrapper& operator=( const TreeWrapper& t );

  std::map<std::string,std::string> userParameters;

  branch_list branchList;

  branch_desc* newBranch( const char* branchName, void* dataPtr,
                          const char* branchData );

};

#include "NtuTool/Common/interface/TreeWrapper.icc"

#endif
