# TEMPLATE used for automatic script submission of multiple datasets

from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TnP_emulate_L1_16_20'
config.General.workArea = 'Crab'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = 'test.py'
config.JobType.psetName = 'TnP_emulate_L1.py'
#config.JobType.allowUndistributedCMSSW = True
config.section_("Data")

config.Data.inputDataset = '/EGamma/Run2018C-PromptReco-v1/MINIAOD'
config.Data.secondaryInputDataset= '/EGamma/Run2018C-v1/RAW'

config.Data.inputDBS = 'global'
config.Data.runRange =  '319347'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 15000
config.Data.totalUnits = -999 # number of event
config.Data.outLFNDirBase = '/store/user/mkovac/Data/ECAL'
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = 'TnP_emulate_L1_16_20'
config.section_("Site")
config.Site.storageSite = 'T3_CH_CERNBOX'