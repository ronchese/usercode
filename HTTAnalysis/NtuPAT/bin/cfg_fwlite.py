import FWCore.ParameterSet.Config as cms

process = cms.PSet()
#process = cms.Process("Htt")

filename = open('pat_files.list', 'r')
filelist = cms.vstring( filename.readlines() )

process.fwliteInput = cms.PSet(
    fileNames   = filelist,               ## mandatory
    maxEvents   = cms.int32(1000),        ## optional, use maxEvents<=0
                                          ##           to read all events
    outputEvery = cms.uint32(10),         ## optional (usage not clear...)
)
    
process.fwliteOutput = cms.PSet(
    fileName = cms.string('hist.root'),   ## mandatory
)

process.hTTAnalyzer = cms.PSet(
    ## mandatory
    ntuName = cms.untracked.string('ntu.root'),
    labelHLT       = cms.string('HLT'),
    labelMets      = cms.string('patMETsAK5PFNoPUTypeII'),
# 8TeV
#    labelMets      = cms.string('patMETsAK5PFNoPU'),
    labelMuons     = cms.string('userDataSelectedPFMuonsAK5PFNoPU'),
    labelElectrons = cms.string('userDataSelectedPFElectronsAK5PFNoPU'),
    labelTaus      = cms.string('selectedPatTausAK5PFNoPU'),
    labelJets      = cms.string('cleanPatJetsIsoPFLeptAK5PFNoPU'),
# 8TeV ?
#    labelJets      = cms.string('customPFJetsAK5PFNoPU'),
    labelGen       = cms.string('genParticles')
)


