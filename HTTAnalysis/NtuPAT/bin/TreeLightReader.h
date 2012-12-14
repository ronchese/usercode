#ifndef TreeLightReader_H
#define TreeLightReader_H

#include "TTree.h"

class TreeLightReader {

 public:

  TreeLightReader() { analyzedEvts = acceptedEvts = 0; };
  virtual ~TreeLightReader() {};
  TTree* currentTree;
  std::string currentFile;
  std::string treeName;

  int analyzedEvents() { return analyzedEvts; }
  int acceptedEvents() { return acceptedEvts; }

 protected:

  TObject* autoSavedObject;
  const char* dummyString;
  int dummySize;
  int dummyLevel;

  int analyzedEvts;
  int acceptedEvts;

  void setBranch( const char* branchName, void* dataPtr,
                  const char* branchData ) {
    currentTree->SetBranchAddress( branchName, dataPtr  );
    dummyString = branchData;
    return;
  }
  void setBranch( const char* branchName, void* dataPtr,
                  const char* branchData,
                  TBranch** branchPtr ) {
    currentTree->SetBranchAddress( branchName, dataPtr, branchPtr );
    dummyString = branchData;
    return;
  }

/*
*/
/*
  template<class T>
  void setBranch( const char* branchName, T* dataPtr,
                  int bufferSize = 32000,
                  int splitLevel = 99 ) {
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    currentTree->SetBranchAddress( branchName, dataPtr  );
    return;
  }
  template<class T>
  void setBranch( const char* branchName, T* dataPtr,
                  int bufferSize,
                  int splitLevel,
                  TBranch** branchPtr ) {
    currentTree->SetBranchAddress( branchName, dataPtr, branchPtr );
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    return;
  }
*/
/*
*/
  template<class T>
  void setBranch( const char* branchName, T** dataPtr,
                  int bufferSize = 32000,
                  int splitLevel = 99 ) {
    currentTree->SetBranchAddress( branchName, dataPtr  );
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    return;
  }
  template<class T>
  void setBranch( const char* branchName, T** dataPtr,
                  int bufferSize,
                  int splitLevel,
                  TBranch** branchPtr ) {
    currentTree->SetBranchAddress( branchName, dataPtr, branchPtr );
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    return;
  }

};

#endif

