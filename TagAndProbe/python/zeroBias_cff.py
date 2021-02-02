import FWCore.ParameterSet.Config as cms

#print "Running on data or mc"

ZeroBias = cms.EDAnalyzer("ZeroBias",
    treeName = cms.string("ZeroBias"),
    L1Tau = cms.InputTag("caloStage2Digis", "Tau"),
    L1EmuTau = cms.InputTag("simCaloStage2Digis", "MP"),
)

NtupleZeroBiasSeq = cms.Sequence(
    ZeroBias
)
