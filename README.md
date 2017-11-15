# GenAna

This code runs on GEN files (for example those produced by https://github.com/santanas/GenerateMC).
It creates histograms in a root file. The a script is run over the histograms to create final plots (i.e. in ".png" format).

1) Create CMSSW area and set environment variables
```
scram p CMSSW_9_2_7
cd CMSSW_9_2_7/src
cmsenv
```

2) Pull the code from repository

```
git clone git@github.com:santanas/GenAna.git santanas/GenAna
cd santanas/GenAna
```

3) Edit and compile code
* Analyzer = plugins/GenAna.c
```
scram b
```

4) Create list of input GEN files

Example of list (lists/list_Res1ToRes2GluTo3Glu.txt) is:
```
root://eoscms///eos/cms/store/cmst3/user/santanas/MCsamples/Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN.root
root://eoscms///eos/cms/store/cmst3/user/santanas/MCsamples/Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN.root
root://eoscms///eos/cms/store/cmst3/user/santanas/MCsamples/Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN.root
root://eoscms///eos/cms/store/cmst3/user/santanas/MCsamples/Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN.root
root://eoscms///eos/cms/store/cmst3/user/santanas/MCsamples/Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN.root
```

5) Run code over GEN samples
```
python makeANAfromGEN.py -c python/GenAna_cfg.py -i lists/list_Res1ToRes2GluTo3Glu.txt -t /tmp/santanas/ --outputDir `pwd`/Output_Res1ToRes2GluTo3Glu_V2
```
Note: both "eos" and "afs" input and output directories are supported

In this example, the output files with histograms are stored in the "Output_Res1ToRes2GluTo3Glu_V2" afs folder:
```
/afs/cern.ch/work/s/santanas/Releases/GenerateMC/CMSSW_9_2_7/src/santanas/GenAna/Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root
/afs/cern.ch/work/s/santanas/Releases/GenerateMC/CMSSW_9_2_7/src/santanas/GenAna/Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root
/afs/cern.ch/work/s/santanas/Releases/GenerateMC/CMSSW_9_2_7/src/santanas/GenAna/Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root
/afs/cern.ch/work/s/santanas/Releases/GenerateMC/CMSSW_9_2_7/src/santanas/GenAna/Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root
/afs/cern.ch/work/s/santanas/Releases/GenerateMC/CMSSW_9_2_7/src/santanas/GenAna/Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root
```

6) Make final plots

* Edit ROOT macro "makePlots.C" with the input files and add any histogram you want to draw in the final plots. The macro can also calculate selection efficiencies. All is very analysis dependent. This is just an example.

* Run the macro
```
root -l -b makePlots.C
```

In this example, the final plots are stored in https://santanas.web.cern.ch/santanas/TrijetResoannces13TeV/GenStudies_ggg_madgraph and they can be seen from a web browser.








