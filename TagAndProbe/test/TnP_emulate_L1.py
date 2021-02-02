import FWCore.ParameterSet.VarParsing as VarParsing
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras

process = cms.Process("TagAndProbe", eras.Run2_2018)

isMC = False
isMINIAOD = True

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')


options = VarParsing.VarParsing ('analysis')
options.register ('secondaryFilesList','',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string,  "List of secondary input files")

options.register ('skipEvents',
                  -1, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,            # string, int, or float
                  "Number of events to skip")
                  
options.register ('JSONfile',
                  "", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,         # string, int, or float
                  "JSON file (empty for no JSON)")
                  
options.outputFile = 'TnP_emulate_L1.root'
options.inputFiles = []
options.maxEvents  = -999

options.parseArguments()


###############
# Electron ID #
###############

# Load tools and function definitions
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

from RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi import *
from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry

process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")

dataFormat = DataFormat.AOD
if isMINIAOD:
    dataFormat = DataFormat.MiniAOD

switchOnVIDElectronIdProducer(process, dataFormat)

process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi")

# Overwrite a default parameter: for miniAOD, the collection name is a slimmed one
if isMINIAOD:
    process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('slimmedElectrons')

from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry
process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)

# Define which IDs we want to produce. Each of these two example IDs contains all four standard.
my_id_modules = [
	'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V1_cff'
] 


# Add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

from RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi import *

egmGsfElectronIDTask = cms.Task(
    #electronMVAVariableHelper,
    electronMVAValueMapProducer,
    egmGsfElectronIDs
)
egmGsfElectronIDSequence = cms.Sequence(egmGsfElectronIDTask)

if not isMC: # will use 80X
    from Configuration.AlCa.autoCond import autoCond
    process.GlobalTag.globaltag = '110X_dataRun2_v12'
    
    process.GlobalTag.toGet = cms.VPSet(
    	cms.PSet(
    		record = cms.string("EcalTPGSpikeRcd"),
 			tag = cms.string("EcalTPGSpike_16"),
 			connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
 			),
 		cms.PSet(
 			record = cms.string("EcalTPGFineGrainStripEERcd"),
 			tag = cms.string("EcalTPGFineGrainStrip_22"),
# 			tag = cms.string("EcalTPGFineGrainStrip_20"),
# 			tag = cms.string("EcalTPGFineGrainStrip_16"),
			connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
 			),
#    	cms.PSet(
#    		record = cms.string("EcalTPGLinearizationConstRcd"),
#        	tag = cms.string("EcalTPGLinearizationConst_IOV_319253_beginning_at_1"),
#           connect = cms.string('sqlite_file:EcalTPG_trans_319253_pedes_319111_moved_to_1.db')
#       		),
#      	cms.PSet(
#      		record = cms.string("EcalTPGPedestalsRcd"),
#            tag = cms.string("EcalTPGPedestals_319253_beginning_at_1"),
#	        connect =cms.string('sqlite_file:EcalTPG_trans_319253_pedes_319111_moved_to_1.db')
#	        )
	        )
       
    process.load('EGTagAndProbe.EGTagAndProbe.tagAndProbe_cff')
    
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring
        (
        	'/store/data/Run2018C/EGamma/MINIAOD/PromptReco-v1/000/319/349/00000/F086E433-3385-E811-B7F8-FA163E89BD00.root'
        ),
		secondaryFileNames = cms.untracked.vstring
		(
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/245CA228-1083-E811-BEE5-FA163E0F5CB9.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/40114D2F-1083-E811-B2FE-FA163E002F6D.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/465CC3A5-1383-E811-929E-FA163EA1695D.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/7291B6B7-1183-E811-B958-FA163ED411AD.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/7A31B34A-1683-E811-B28D-02163E01A179.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/4EC231C6-1183-E811-9B59-FA163EF57FC8.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/AA72A78D-1383-E811-A20A-FA163E157685.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/A0B073E4-1683-E811-978B-FA163EF9E3D8.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/C65B23C3-1683-E811-A826-FA163E3FF064.root',
			'/store/data/Run2018C/EGamma/RAW/v1/000/319/349/00000/20CBD470-1183-E811-ABC5-FA163E0D4D44.root'
		)
    	)
else:
    process.GlobalTag.globaltag = '106X_mcRun2_asymptotic_preVFP_v5'
    process.load('EGTagAndProbe.EGTagAndProbe.MCanalysis_cff')
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
#           	'/store/relval/CMSSW_10_6_8/RelValZEE_13/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v3_UL16_CP5_preVFP-v1/20000/FEF96392-3307-3B4F-9A4A-3571A8C54F26.root'
			'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/CCB6A88B-A1DE-4044-910A-B548D565AFC4.root'
#			'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/8943C7FE-7326-D64E-9D54-B4FB6EE9229D.root',
#			'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/362B166F-348C-1948-B1BB-F26AEABED9FB.root'
        ),
       secondaryFileNames = cms.untracked.vstring(
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/A255DD0A-714F-EA11-BCEB-0CC47A4D75EC.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/00FDEC5B-4C4F-EA11-8B31-0025905B85D6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/10EBA3B3-444F-EA11-9328-AC1F6BAC7D10.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/366241A5-454F-EA11-B7C6-0CC47A4D75F2.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/3EB877C6-494F-EA11-BF42-0CC47A4D7600.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/40E0EA66-484F-EA11-B6E5-0025905A612E.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/4436D4C2-494F-EA11-A1C9-0CC47A4C8F18.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/4A55CE2B-764F-EA11-A940-0CC47A4D76C6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/F041AF46-4C4F-EA11-A210-0CC47A7452DA.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/D0413658-514F-EA11-A0DA-0025905B85F6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/EADA2848-614F-EA11-AF89-0025905B8598.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/8CD19F06-664F-EA11-9280-0CC47A4D7628.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/8CD7B387-4D4F-EA11-839A-0025905B85D6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/BC9CA916-6A4F-EA11-BD3D-AC1F6BAC7C2A.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/EE735DDC-464F-EA11-A8CE-0CC47A7C3408.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/CEF45DE6-7B4F-EA11-B9EF-0CC47A7C354C.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/BC234A3D-494F-EA11-A2D2-0CC47A4C8E28.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/4ABB1E6C-484F-EA11-9F80-0025905A48FC.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/7CA13DCE-864F-EA11-A60C-AC1F6BAC7D14.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/50A5D0F3-644F-EA11-91DC-AC1F6BAC807A.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/5698404B-904F-EA11-89F5-0CC47A4D7646.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/7ADA49E9-414F-EA11-B0E3-AC1F6BAC7C78.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/7E787757-634F-EA11-91F1-0CC47A4D7690.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/8E11FA7C-624F-EA11-9696-0CC47A7C35D8.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/B4732519-6D4F-EA11-867E-0025905B85AE.root'
	)
    )
    process.Ntuplizer.useHLTMatch = cms.bool(False) #In case no HLT object in MC sample considered or you're fed up with trying to find the right HLT collections

if isMINIAOD:
    process.Ntuplizer.electrons = cms.InputTag("slimmedElectrons")
    process.Ntuplizer.genParticles = cms.InputTag("prunedGenParticles")
    process.Ntuplizer.Vertices = cms.InputTag("offlineSlimmedPrimaryVertices")

process.schedule = cms.Schedule()

## L1 emulation stuff

if not isMC:
    from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAWsimEcalTP 
    process = L1TReEmulFromRAWsimEcalTP(process)
else:
    from L1Trigger.Configuration.customiseReEmul import L1TReEmulMCFromRAW
    process = L1TReEmulMCFromRAW(process) 
    from L1Trigger.Configuration.customiseUtils import L1TTurnOffUnpackStage2GtGmtAndCalo 
    process = L1TTurnOffUnpackStage2GtGmtAndCalo(process)


#process.load("L1Trigger.L1TCalorimeter.caloStage2Params_2016_v2_2_cfi")
#process.load("L1Trigger.L1TCalorimeter.caloStage2Params_2016_v3_3_1_2018_EcalSF_cfi")
#process.load("L1Trigger.L1TCalorimeter.caloStage2Params_2016_v3_3_1_2018_EcalSF_EGcalib_cfi")
process.load("L1Trigger.L1TCalorimeter.caloParams_2018_v1_3_cfi")


#### handling of cms line options for tier3 submission
#### the following are dummy defaults, so that one can normally use the config changing file list by hand etc.

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

process.p = cms.Path (
    process.egmGsfElectronIDSequence +
    process.RawToDigi +
    process.L1TReEmul +
    process.NtupleSeq
)
process.schedule = cms.Schedule(process.p) # do my sequence pls

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string(options.outputFile))
