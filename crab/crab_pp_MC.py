#

from CRABClient.UserUtilities import config
config = config()
config.General.transferOutputs = True
config.General.requestName = 'DfinderMC_pp_20170404_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar'
config.General.workArea = 'crab_projects'
config.JobType.psetName = 'runForestAOD_pp_MC_75X.py'
config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['rssLimit']
config.JobType.pyCfgParams = ['noprint']
config.JobType.outputFiles = ['HiForestAOD.root']
config.Data.inputDataset = '/Pythia8_prompt_D0pt0p0_Pthat30_pp502_TuneCUETP8M1/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1/AODSIM'
config.Data.inputDBS = 'global'
config.Data.totalUnits = -1
config.Data.unitsPerJob = 2000
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'EventAwareLumiBased'
config.Site.storageSite = 'T2_US_MIT'
#config.Site.whitelist = ['T2_US_MIT']
#config.Site.ignoreGlobalBlacklist = True
