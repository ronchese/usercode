#ifndef BmmEnumString_H
#define BmmEnumString_H

#include <map>
#include <string>

class BmmEnumString {

 public:

  BmmEnumString();
  virtual ~BmmEnumString();

  enum trigObject { hltJet = 1,
                    hltMuon,
                    hltElectron,
                    hltTau };
  enum trigPath   { HLT_Mu40_eta2p1_v = 1,
                    HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v,
                    HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v,
                    HLT_DoubleMu4_Jpsi_Displaced_v };
  enum vertexType { svtTagInfo = 1,
                    svtFitPair };

  static int                findTrigObject( const std::string& trigObject );
  static const std::string& findTrigObject( int                trigObject );
  static int                findTrigPath  ( const std::string& trigPath   );
  static const std::string& findTrigPath  ( int                trigPath   );
  static int                findVertexType( const std::string& vtxType    );
  static const std::string& findVertexType( int                vtxType    );

 private:

  static std::string defaultString;
  static std::map<int,std::string> trigObjectMapIS;
  static std::map<std::string,int> trigObjectMapSI;
  static std::map<int,std::string> trigPathMapIS;
  static std::map<std::string,int> trigPathMapSI;
  static std::map<int,std::string> vertexTypeMapIS;
  static std::map<std::string,int> vertexTypeMapSI;

  static void revertMap( const std::map<std::string,int>& mapSI,
                               std::map<int,std::string>& mapIS );

};


#endif

