import FWCore.ParameterSet.Config as cms

process = cms.Process("Bmm")

#process.load('Configuration.StandardSequences.Services_cff')
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = cms.string('MC_42_V15B::All')

process.load("FWCore.MessageService.MessageLogger_cfi")

# Quiet Mode or event dump
process.MessageLogger.cerr.threshold = 'ERROR'
#process.MessageLogger.cerr.FwkReport.reportEvery = 10000

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

filename = open('pat_files.list', 'r')
fileList = cms.untracked.vstring( filename.readlines() )
    
process.source = cms.Source ("PoolSource", fileNames=fileList)

process.bmmAnalyzer = cms.EDAnalyzer('BmmPATAnalyzer',

    ## optional
#    eventList = cms.string('evtlist'),
    verbose = cms.untracked.string('t'),

    ## mandatory
    ## ntuple file name: empty string to drop ntuple filling
    ntuName = cms.untracked.string('ntu.root'),
    ## histogram file name
    histName = cms.untracked.string('hist.root'),

    labelHLT          = cms.string('TriggerResults'),
    labelMets         = cms.string('patMETsPFlow'),
    labelMuons        = cms.string('selectedPatMuonsPFlow'),
#    labelElectrons    = cms.string('userDataSelectedPFElectronsAK5PFNoPU'),
#    labelTaus         = cms.string('selectedPatTausAK5PFNoPU'),
    labelElectrons    = cms.string(''),
    labelTaus         = cms.string(''),
#    labelPFCandidates = cms.string('particleFlow'),
    labelPFCandidates = cms.string('selectedPatJetsPFlow:pfCandidates:PAT'),
    labelGeneralTracks = cms.string('generalTracks'),
    labelJets         = cms.string('selectedPatJetsPFlow'),
    labelPVertices    = cms.string('offlinePrimaryVerticesWithBS'),
    labelSVertices    = cms.string('secondaryVertexTagInfosAODPFlow'),
    labelGen          = cms.string(''),

    ## trigger paths to save on ntuple: '*' to save all paths
    savedTriggers = cms.vstring(
        'HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v',
        'HLT_Mu12_eta2p1_DiCentral_20_v',
        'HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v',
        'HLT_Mu12_eta2p1_DiCentral_40_20_v',
        'HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v',
        'HLT_Mu12_DoubleCentralJet65_v',
        'HLT_Mu12_v'
    )

)


process.p = cms.Path(process.bmmAnalyzer)
