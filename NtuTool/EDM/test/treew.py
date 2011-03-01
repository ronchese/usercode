import FWCore.ParameterSet.Config as cms

process = cms.Process("PIPPO")

process.source = cms.Source("EmptyIOVSource",
    timetype   = cms.string('runnumber'),
    firstValue = cms.uint64(123456),
    lastValue  = cms.uint64(123465),
    interval   = cms.uint64(1)
)


process.testSimpleTree = cms.EDAnalyzer(
    "TestSimpleTree"
)


process.p = cms.Path(process.testSimpleTree)

