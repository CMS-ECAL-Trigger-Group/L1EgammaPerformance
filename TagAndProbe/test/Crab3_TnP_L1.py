# TEMPLATE used for automatic script submission of multiple datasets

from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TnP_L1'
config.General.workArea = 'Crab'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = 'test.py'
config.JobType.psetName = 'TnP_L1.py'
#config.JobType.allowUndistributedCMSSW = True
config.section_("Data")

config.Data.inputDataset = '/EGamma/Run2018C-PromptReco-v1/MINIAOD'
config.Data.secondaryInputDataset= '/EGamma/Run2018C-v1/RAW'

config.Data.inputDBS = 'global'
config.Data.runRange =  '319347'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 10000 # number of events per jobs
config.Data.totalUnits = -1 # number of event
config.Data.outLFNDirBase = '/store/user/mkovac/Data/ECAL'
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = 'TnP_L1'
config.section_("Site")
config.Site.storageSite = 'T2_CH_CERNBOX'