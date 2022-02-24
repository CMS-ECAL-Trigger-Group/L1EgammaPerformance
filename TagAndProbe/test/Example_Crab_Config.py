# TEMPLATE used for automatic script submission of multiple datasets

# from WMCore.Configuration import Configuration
# config = Configuration()

from CRABClient.UserUtilities import config
config = config()

# config.section_("General")
config.General.requestName = 'TnP_emulate_L1_16_16'
config.General.workArea = 'Crab'
config.General.transferOutputs = True
config.General.transferLogs = False 

# config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'TnP_emulate_L1.py'

# config.section_("Data")
config.Data.inputDataset = '/EGamma/Run2018C-UL2018_MiniAODv2-v1/MINIAOD'
config.Data.secondaryInputDataset= '/EGamma/Run2018C-v1/RAW'

config.Data.inputDBS = 'global'
config.Data.runRange =  '320065'
# config.Data.runRange =  '320416'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 10000
config.Data.totalUnits = 10000 # number of event
config.Data.outLFNDirBase = '/store/group/dpg_ecal/alca_ecalcalib/Trigger/DoubleWeights/L1_Rates_and_TurnOns/' 
config.Data.publication = False 
config.Data.outputDatasetTag = 'TnP_Test'
# config.section_("Site")
#config.Site.whitelist = ['T2_CH_CERN'] ##-- Eventually had to change from 'T2_FR_GRIF_LLR' whitelist to this 
#config.Site.whitelist = ['T2_FR_GRIF_LLR']
config.Site.storageSite = 'T2_CH_CERN'