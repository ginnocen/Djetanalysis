from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'PbPb_5TeV_MCHydjet_Dfinder_MC_pthat30_31March_split'
config.General.workArea = config.General.requestName

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_PbPb_MB_75X.py'
config.JobType.maxMemoryMB = 4000
#config.JobType.inputFiles = ['btagnew_data75X.db']

config.section_("Data")
#config.Data.inputDataset = '/GenericTTbar/HC-CMSSW_7_0_4_START70_V7-v1/GEN-SIM-RECO'
#config.Data.lumiMask = 'Cert_262081-262328_5TeV_PromptReco_Collisions15_25ns_JSON.txt'
#config.Data.lumiMask = "Cert_262548-263757_PromptReco_HICollisions15_JSON_v2_part1.txt"
#config.Data.userInputFiles = open('HighPtJet80_ppRECO.txt').readlines()
config.Data.inputDataset = '/Pythia8_prompt_D0pt0p0_Pthat30_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1/AODSIM'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 200
config.Data.totalUnits = -1
config.Data.splitting = 'EventAwareLumiBased'
#config.Data.outLFNDirBase = '/store/group/phys_heavyions/ginnocen/Djetstudy'
config.Data.publication = False
config.section_("Site")
config.Site.storageSite = 'T2_US_MIT'
#config.Site.ignoreGlobalBlacklist = True
#config.Site.whitelist = 'T2_US_MIT'

