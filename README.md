# EGTagAndProbe
Set of tools to evaluate L1EG trigger performance on TnP

Taken from https://gitlab.cern.ch/ckoraka/EGTagAndProbe

# Install instructions
To run on 2018 data follow L1 Trigger Emulator Stage 2 Upgrade Instructions located here [1], and also given bellow
```
cmsrel CMSSW_11_0_2
cd CMSSW_11_0_2/src
cmsenv
git cms-init
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline l1t-integration-CMSSW_11_0_2
git cms-merge-topic -u cms-l1t-offline:l1t-integration-v104.5
git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TMuon
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TMuon.git L1Trigger/L1TMuon/data
git cms-addpkg L1Trigger/L1TCalorimeter
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TCalorimeter.git L1Trigger/L1TCalorimeter/data

scram b -j 8
```

Then clone the repository:
```
git clone https://github.com/mkovac/L1EgammaPerformance.git
scram b -j 4
```
Now you have set up the work directory. You should go to the L1EgammaPerformance/TagAndProbe/test directory and run scripts there. 


### Producing TagAndProbe ntuples with unpacked L1EG (no re-emulation)
- Set flag isMC and isMINIAOD in TnP_L1.py, depending on what kind of dataset you are running on.
- HLT path used specified in python/MCAnalysis_cff.py (MC) or python/tagAndProbe_cff.py (data)
- Launch TnP_L1.py

### Producing TagAndProbe ntuples with emulated L1EG
Here is a checklist of code you need to modify in order to run your desired process.
+ Update electron ID to be exactly the same ones used in the data.
+ Make sure you use L1TReEmulFromRawsimEcalTP(process) instead of L1TReEmulFromRaw(process). Corresponding lines in TnP_emulate_L1.py are:
```
from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAWsimEcalTP
process = L1TReEmulFromRAWsimEcalTP(process)
```
+ Use the correct Calo parameters according to your run number. See [L1 Known Issues](https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1KnownIssues#Calo). You can edit this in the line:```process.load("L1Trigger.L1TCalorimeter.caloParams_2018_v1_3_cfi")``` in the reEmulL1.py.
+ Be sure to use the correct sqlite file (with extension .db) in your TnP_emulate_L1.py


### Submit job on the Grid
Modify Crab3_TnP_\*.py: change requestName, inputDataSet, outLFNDirBase, outputDatasetTag, storageSite
```
cd CMSSW_9_4_0_pre3/src/EGTagAndProbe/EGTagAndProbe/test
source /cvmfs/cms.cern.ch/crab3/crab.sh
voms-proxy-init -voms cms
crab submit -c crab3_config.py
```

### Producing turn-on plots
Create configuration file based on test/fitter/run/stage2_turnOnEG_fitter_test.par
```
cd CMSSW_9_4_0_pre3/src/EGTagAndProbe/EGTagAndProbe/test/fitter
make clean; make
./fit.exe run/stage2_turnOnEG_fitter_test.par
```
Note that you need to modify the input file location in the .par file.

Create plotting script based on test/fitter/results/plot_EG_example.py
```
cd results
python plot_EG_example.py
```

[1] https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TStage2Instructions
