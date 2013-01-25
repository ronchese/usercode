import FWCore.ParameterSet.Config as cms

process = cms.PSet()
#process = cms.Process("Bmm")

filename = open('pat_files.list', 'r')
filelist = cms.vstring( filename.readlines() )

process.fwliteInput = cms.PSet(
    fileNames   = filelist,               ## mandatory
    maxEvents   = cms.int32(500),        ## optional, use maxEvents<=0
                                          ##           to read all events
    outputEvery = cms.uint32(10),         ## optional (usage not clear...)
)
    
process.fwliteOutput = cms.PSet(
    fileName = cms.string('hist.root'),   ## mandatory
)

process.bmmAnalyzer = cms.PSet(

    ## optional
#    eventList = cms.string('evtlist'),
    verbose = cms.untracked.string('t'),

    ## mandatory
    ## ntuple file name: empty string to drop ntuple filling
    ntuName = cms.untracked.string('ntu.root'),
    ## histogram file name
    histName = cms.untracked.string('hist.root'),

    labelTrigResults  = cms.string('TriggerResults'),
    labelTrigEvent    = cms.string('patTriggerEvent'),
    labelBeamSpot     = cms.string('offlineBeamSpot'),
    labelMets         = cms.string('patMETsPFlow'),
    labelMuons        = cms.string('selectedPatMuonsPFlow'),
#    labelElectrons    = cms.string('userDataSelectedPFElectronsAK5PFNoPU'),
#    labelTaus         = cms.string('selectedPatTausAK5PFNoPU'),
    labelElectrons    = cms.string(''),
    labelTaus         = cms.string(''),
    labelJets         = cms.string('selectedPatJetsPFlow'),
#    labelPFCandidates = cms.string('particleFlow'),
    labelPFCandidates = cms.string('selectedPatJetsPFlow:pfCandidates:PAT'),
#    labelPFCandidates = cms.string(''),
    labelGeneralTracks = cms.string('generalTracks'),
    labelPVertices    = cms.string('offlinePrimaryVerticesWithBS'),
    labelSVertices    = cms.string('secondaryVertexTagInfosAODPFlow'),
    labelGen          = cms.string(''),

    jetPtMin  = cms.double( 10.0 ),
    jetEtaMax = cms.double(  2.5 ),

    ## trigger paths to save on ntuple: '*' to save all paths
    savedTriggerPaths = cms.vstring(
        'HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v',
        'HLT_Mu12_eta2p1_DiCentral_20_v',
        'HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v',
        'HLT_Mu12_eta2p1_DiCentral_40_20_v',
        'HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v',
        'HLT_Mu12_DoubleCentralJet65_v',
        'HLT_Mu12_v'
    ),

    ## trigger objects to save on ntuple:
    savedTriggerObjects = cms.vstring(
        'muon',
        'jet'
    )

)


