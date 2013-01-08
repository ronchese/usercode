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
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

filename = open('pat_files.list', 'r')
fileList = cms.untracked.vstring( filename.readlines() )
    
process.source = cms.Source ("PoolSource", fileNames=fileList)

process.bmmAnalyzer = cms.EDAnalyzer('BmmPATAnalyzer',
    ## mandatory
    ntuName = cms.untracked.string('ntu.root'),
    histName = cms.untracked.string('hist.root'),

    labelHLT       = cms.string('HLT'),
    labelMets      = cms.string('patMETsAK5PFNoPUTypeII'),
# 8TeV
#    labelMets      = cms.string('patMETsAK5PFNoPU'),
    labelMuons     = cms.string('userDataSelectedPFMuonsAK5PFNoPU'),
#    labelElectrons = cms.string('userDataSelectedPFElectronsAK5PFNoPU'),
#    labelTaus      = cms.string('selectedPatTausAK5PFNoPU'),
    labelJets      = cms.string('cleanPatJetsIsoPFLeptAK5PFNoPU'),
# 8TeV ?
#    labelJets      = cms.string('customPFJetsAK5PFNoPU'),
    labelGen       = cms.string('genParticles'),
    ## optional
    verbose = cms.untracked.string('f')
)


process.p = cms.Path(process.bmmAnalyzer)
