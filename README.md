# EGTagAndProbe
Set of tools to evaluate L1EG trigger performance on T&amp;P

Based on TauTagAndProbe package developed by L. Cadamuro & O. Davignon
Forked from https://github.com/pkontaxa/EGTagAndProbe

### Install instructions
To run on 2018 data:(this version not tested on 2017 data yet)
Follow [L1 Trigger Emulator Stage 2 Upgrade Instructions](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TStage2Instructions)
Then clone the repository:
```
git clone https://github.com/siqiyyyy/EGTagAndProbe
scram b -j4
```
Now you have set up the work directory. You should go to the test/ directory and run scripts there. 


### Producing TagAndProbe ntuples with unpacked L1EG (no re-emulation)
Set flag isMC and isMINIAOD test.py, depending on what kind of dataset you are running on.
- HLT path used specified in python/MCAnalysis_cff.py (MC) or python/tagAndProbe_cff.py (data)
Launch test.py

### Producing TagAndProbe ntuples with emulated L1EG
reEmulL1.py is an example of cms pset file to run re-emulation on 2018 runC data.
Here is a checklist of code you need to modify in order to run your desired process.
+ Update electron ID to be exactly the same ones used in the data
+ Make sure you use L1TReEmulFromRawsimEcalTP(process) instead of L1TReEmulFromRaw(process). Corresponding lines in reEmulL1.py are:
```
from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAWsimEcalTP
process = L1TReEmulFromRAWsimEcalTP(process)
```
+ Use the correct Calo parameters according to your run number. See [L1 Known Issues](https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1KnownIssues#Calo). You can edit this in the line:```process.load("L1Trigger.L1TCalorimeter.caloParams_2018_v1_3_cfi")``` in the reEmulL1.py.
+ Be sure to use the correct sqlite file (with extension .db) in your reEmulL1.py


### Submit job on the Grid
Modify crab3_config.py: change requestName, inputDataSet, outLFNDirBase, outputDatasetTag, storageSite
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
