import FWCore.ParameterSet.VarParsing as VarParsing
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms

process = cms.Process("TagAndProbe")

isMC = False
isMINIAOD = True

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")


options = VarParsing.VarParsing ('analysis')

options.register ('skipEvents',
                  -1, # Default value
                  VarParsing.VarParsing.multiplicity.singleton, # Singleton or list
                  VarParsing.VarParsing.varType.int,            # string, int, or float
                  "Number of events to skip")
                  
options.register ('JSONfile',
                  "", # Default value
                  VarParsing.VarParsing.multiplicity.singleton, # Singleton or list
                  VarParsing.VarParsing.varType.string,         # string, int, or float
                  "JSON file (empty for no JSON)")
                  
options.outputFile = 'TnP_L1.root'
options.inputFiles = []
options.maxEvents  = 1000
options.parseArguments()


###############
# Electron ID #
###############

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
from RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi import *
from RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi import *

#process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
#process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi")


dataFormat = DataFormat.AOD
if isMINIAOD:
    dataFormat = DataFormat.MiniAOD
    
switchOnVIDElectronIdProducer(process, dataFormat)



if isMINIAOD:
    process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('slimmedElectrons')

from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry
process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)

# Define which IDs we want to produce
my_id_modules =[
'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V1_cff'
] 


#Add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


egmGsfElectronIDTask = cms.Task(
    electronMVAValueMapProducer,
    egmGsfElectronIDs
)

egmGsfElectronIDSequence = cms.Sequence(egmGsfElectronIDTask)

if not isMC:
    from Configuration.AlCa.autoCond import autoCond
    process.GlobalTag.globaltag = '101X_dataRun2_Prompt_v11'
    process.load('EGTagAndProbe.EGTagAndProbe.tagAndProbe_cff')
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring('/store/data/Run2018C/EGamma/MINIAOD/PromptReco-v1/000/319/349/00000/F086E433-3385-E811-B7F8-FA163E89BD00.root'),
    )
else:
    process.GlobalTag.globaltag = '106X_mcRun2_asymptotic_preVFP_v6'
    process.load('EGTagAndProbe.EGTagAndProbe.MCanalysis_cff')
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/CCB6A88B-A1DE-4044-910A-B548D565AFC4.root',
        '/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/8943C7FE-7326-D64E-9D54-B4FB6EE9229D.root',
        '/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/362B166F-348C-1948-B1BB-F26AEABED9FB.root' 
        )
    )
    
    
    #In case no HLT object in MC sample considered or you're fed up with trying to find the right HLT collections
    process.Ntuplizer.useHLTMatch = cms.bool(False)

if isMINIAOD:
    process.Ntuplizer.electrons = cms.InputTag("slimmedElectrons")
    process.Ntuplizer.genParticles = cms.InputTag("prunedGenParticles")
    process.Ntuplizer.Vertices = cms.InputTag("offlineSlimmedPrimaryVertices")

if options.JSONfile:
    print "Using JSON: " , options.JSONfile
    process.source.lumisToProcess = LumiList.LumiList(filename = options.JSONfile).getVLuminosityBlockRange()

if options.inputFiles:
    process.source.fileNames = cms.untracked.vstring(options.inputFiles)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

if options.maxEvents >= -1:
    process.maxEvents.input = cms.untracked.int32(options.maxEvents)
if options.skipEvents >= 0:
    process.source.skipEvents = cms.untracked.uint32(options.skipEvents)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.p = cms.Path(
    process.egmGsfElectronIDSequence +
    process.NtupleSeq
)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string(options.outputFile))
