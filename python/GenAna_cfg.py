import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://eoscms///eos/cms/store/cmst3/user/santanas/MCsamples/TrijetRes_g_ggg_BP2_testV2/TrijetRes_g_ggg_BP2_testV2_MGKK2000R0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN.root'
    )
)


process.TFileService=cms.Service("TFileService",
                                 fileName=cms.string("GenAna.root"),
                                 closeFileFast = cms.untracked.bool(True)
                                 )

process.demo = cms.EDAnalyzer('GenAna',
                              genParticlesInputTag = cms.InputTag('genParticles')
)


process.p = cms.Path(process.demo)