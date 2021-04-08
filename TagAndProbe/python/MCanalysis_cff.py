#=====================================================
# User imports
#=====================================================
import FWCore.ParameterSet.Config as cms
import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt

HLTLISTTAG = cms.VPSet(
    cms.PSet (
        HLT = cms.string("*"),
        #HLT = cms.string("HLT_Ele27_WPTight_Gsf_v"),
        #path1 = cms.vstring ("hltEle32WPTightGsfTrackIsoFilter"),
        path1 = cms.vstring ("hltEle27WPTightGsfTrackIsoFilter"),
        path2 = cms.vstring (""),
        leg1 = cms.int32(11),
        leg2 = cms.int32(999)
        ),
)

HLTLISTPROBE = cms.VPSet(
    cms.PSet (
        HLT = cms.string("*"),
        path1 = cms.vstring ("hltEle27WPTightGsfTrackIsoFilter"),
        #HLT = cms.string("HLT_Ele32_WPTight_Gsf_v"),
        #path1 = cms.vstring ("hltEle32WPTightGsfTrackIsoFilter"),
        path2 = cms.vstring (""),
        leg1 = cms.int32(11),
        leg2 = cms.int32(999)
        ),
)

# filter HLT paths for T&P
hltFilter = hlt.hltHighLevel.clone(
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    #HLTPaths = ['HLT_Ele27_WPTight_Gsf_v*'],
    HLTPaths = ['*'],
    andOr = cms.bool(True), # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
    throw = cms.bool(True) #if True: throws exception if a trigger path is invalid
)


patTriggerUnpacker = cms.EDProducer("PATTriggerObjectStandAloneUnpacker",
                                    patTriggerObjectsStandAlone = cms.InputTag("slimmedPatTrigger"),
                                    triggerResults = cms.InputTag('TriggerResults', '', "HLT"),
                                    unpackFilterLabels = cms.bool(True)
                                    )


Ntuplizer = cms.EDAnalyzer("Ntuplizer",
                           treeName = cms.string("TagAndProbe"),
                           electrons = cms.InputTag("gedGsfElectrons"),
                           genParticles = cms.InputTag("genParticles"),                       
                           eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-iso-V1-wp90"),
                           eleTightIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-iso-V1-wp80"),
                           eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-iso-V1-wpLoose"),
                           triggerSet = cms.InputTag("patTriggerUnpacker"),
                           triggerResultsLabel = cms.InputTag("TriggerResults", "", "HLT"),
                           L1EG = cms.InputTag("caloStage2Digis", "EGamma", "RECO"),
                           L1EmuEG = cms.InputTag("simCaloStage2Digis"),
                           Vertices = cms.InputTag("offlinePrimaryVertices"),
                           triggerListTag = HLTLISTTAG,
                           triggerListProbe = HLTLISTPROBE,
                           useGenMatch = cms.bool(True),
                           useHLTMatch = cms.bool(True)
                           )

#============================================
# Module Execution
#============================================
NtupleSeq = cms.Sequence(
    hltFilter +
    patTriggerUnpacker +
    Ntuplizer
)


