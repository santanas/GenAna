// -*- C++ -*-
//
// Package:    MyGeneration/GenAna
// Class:      GenAna
// 
/**\class GenAna GenAna.cc MyGeneration/GenAna/plugins/GenAna.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Francesco Santanastasio
//         Created:  Tue, 31 Oct 2017 17:49:46 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/METReco/interface/GenMET.h"

//
// class declaration
//

#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "TFile.h"
#include "TH1D.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TTree.h"


// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

using namespace std;
using namespace edm;
using namespace reco;

class GenAna : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit GenAna(const edm::ParameterSet&);
      ~GenAna();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------

  edm::Service<TFileService> fs_;
  
  edm::EDGetTokenT<reco::GenParticleCollection> genPartInputToken_;

  TH1F *h1_R;
  TH1F *h1_Res1_mass,*h1_Res1_pt,*h1_Res1_eta,*h1_Res1_phi;
  TH1F *h1_Res2_mass,*h1_Res2_pt,*h1_Res2_eta,*h1_Res2_phi;
  TH1F *h1_P1_mass,*h1_P1_pt,*h1_P1_eta,*h1_P1_phi;
  TH1F *h1_P2_mass,*h1_P2_pt,*h1_P2_eta,*h1_P2_phi;
  TH1F *h1_P3_mass,*h1_P3_pt,*h1_P3_eta,*h1_P3_phi;

  TH1F *h1_Res1_Res2P3_massDiff;
  TH1F *h1_Res2_P1P2_massDiff;

  TH1F *h1_P1P2_Angle;
  TH1F *h1_P1P2_DeltaR;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GenAna::GenAna(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  usesResource("TFileService");
  genPartInputToken_ = (consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticlesInputTag")));
}


GenAna::~GenAna()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif

   edm::Handle<reco::GenParticleCollection> genParticles;
   if (!iEvent.isRealData())
     iEvent.getByToken(genPartInputToken_, genParticles);


   TLorentzVector Res1, Res2, P1, P2, P3;
   //Res 1 --> Res2 + P3 --> (P1+P2) + P3 
   //Res1 = KK gluon
   //Res2 = Radion
   //P1,P2,P3 = gluons

   if( genParticles.isValid() ) {

     bool P1found = false;      

     for( reco::GenParticleCollection::const_iterator it = genParticles->begin(); it != genParticles->end(); ++it ) {

       //Res1
       if (it->pdgId()==9000021 && it->status()==62 && it->mother()->pdgId()==9000021 && it->numberOfDaughters()==2)
	 {
	   //cout << "pdgid, mass, ndaughter = " << it->pdgId() << ", " << it->mass() << ", " << it->numberOfDaughters() << endl;	 
	   Res1.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());	 
	 }

       //Res2
       if (it->pdgId()==9000025 && it->status()==52 && it->mother()->pdgId()==9000025 && it->numberOfDaughters()==2 )
	 {
	   Res2.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());	 
	 }

       //P3
       if (it->pdgId()==21 && it->status()==23 && it->mother()->pdgId()==9000021)
	 {
	   P3.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());	 
	 }

       //P1 and P2 

       if (it->pdgId()==21 && it->status()==23 && it->mother()->pdgId()==9000025)
	 {
	   if(P1found)
	     {
	       P2.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());	 
	     }
	   else
	     {
	       P1.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());	 
	       P1found = true;
	     }	   
	 }
     }

     float R = Res2.M() / Res1.M();

     h1_R->Fill(R);
     h1_Res1_mass->Fill(Res1.M());
     h1_Res1_pt->Fill(Res1.Pt());
     h1_Res1_eta->Fill(Res1.Eta());
     h1_Res1_phi->Fill(Res1.Phi());

     h1_Res2_mass->Fill(Res2.M());
     h1_Res2_pt->Fill(Res2.Pt());
     h1_Res2_eta->Fill(Res2.Eta());
     h1_Res2_phi->Fill(Res2.Phi());

     h1_P1_mass->Fill(P1.M());
     h1_P1_pt->Fill(P1.Pt());
     h1_P1_eta->Fill(P1.Eta());
     h1_P1_phi->Fill(P1.Phi());

     h1_P2_mass->Fill(P2.M());
     h1_P2_pt->Fill(P2.Pt());
     h1_P2_eta->Fill(P2.Eta());
     h1_P2_phi->Fill(P2.Phi());

     h1_P3_mass->Fill(P3.M());
     h1_P3_pt->Fill(P3.Pt());
     h1_P3_eta->Fill(P3.Eta());
     h1_P3_phi->Fill(P3.Phi());

     h1_Res1_Res2P3_massDiff->Fill(Res1.M()-(Res2+P3).M());
     h1_Res2_P1P2_massDiff->Fill(Res2.M()-(P1+P2).M());

     h1_P1P2_Angle->Fill(P1.Angle(P2.BoostVector()));
     h1_P1P2_DeltaR->Fill(P1.DeltaR(P2));

   }

}


// ------------ method called once each job just before starting event loop  ------------
void 
GenAna::beginJob()
{  

  h1_R = fs_->make<TH1F>("h1_R","h1_R",100,0,1);

  h1_Res1_mass = fs_->make<TH1F>("h1_Res1_mass","h1_Res1_mass",1000,0,10000);
  h1_Res1_pt = fs_->make<TH1F>("h1_Res1_pt","h1_Res1_pt",1000,0,10000);
  h1_Res1_eta = fs_->make<TH1F>("h1_Res1_eta","h1_Res1_eta",100,-6,6);
  h1_Res1_phi = fs_->make<TH1F>("h1_Res1_phi","h1_Res1_phi",100,-3.15,3.15);

  h1_Res2_mass = fs_->make<TH1F>("h1_Res2_mass","h1_Res2_mass",1000,0,10000);
  h1_Res2_pt = fs_->make<TH1F>("h1_Res2_pt","h1_Res2_pt",1000,0,10000);
  h1_Res2_eta = fs_->make<TH1F>("h1_Res2_eta","h1_Res2_eta",100,-6,6);
  h1_Res2_phi = fs_->make<TH1F>("h1_Res2_phi","h1_Res2_phi",100,-3.15,3.15);

  h1_P1_mass = fs_->make<TH1F>("h1_P1_mass","h1_P1_mass",1000,0,10000);
  h1_P1_pt = fs_->make<TH1F>("h1_P1_pt","h1_P1_pt",1000,0,10000);
  h1_P1_eta = fs_->make<TH1F>("h1_P1_eta","h1_P1_eta",100,-6,6);
  h1_P1_phi = fs_->make<TH1F>("h1_P1_phi","h1_P1_phi",100,-3.15,3.15);

  h1_P2_mass = fs_->make<TH1F>("h1_P2_mass","h1_P2_mass",1000,0,10000);
  h1_P2_pt = fs_->make<TH1F>("h1_P2_pt","h1_P2_pt",1000,0,10000);
  h1_P2_eta = fs_->make<TH1F>("h1_P2_eta","h1_P2_eta",100,-6,6);
  h1_P2_phi = fs_->make<TH1F>("h1_P2_phi","h1_P2_phi",100,-3.15,3.15);

  h1_P3_mass = fs_->make<TH1F>("h1_P3_mass","h1_P3_mass",1000,0,10000);
  h1_P3_pt = fs_->make<TH1F>("h1_P3_pt","h1_P3_pt",1000,0,10000);
  h1_P3_eta = fs_->make<TH1F>("h1_P3_eta","h1_P3_eta",100,-6,6);
  h1_P3_phi = fs_->make<TH1F>("h1_P3_phi","h1_P3_phi",100,-3.15,3.15);

  h1_Res1_Res2P3_massDiff = fs_->make<TH1F>("h1_Res1_Res2P3_massDiff","h1_Res1_Res2P3_massDiff",1000,-100,100);
  h1_Res2_P1P2_massDiff = fs_->make<TH1F>("h1_Res2_P1P2_massDiff","h1_Res2_P1P2_massDiff",1000,-100,100);

  h1_P1P2_Angle = fs_->make<TH1F>("h1_P1P2_Angle","h1_P1P2_Angle",1000,0,6.30);
  h1_P1P2_DeltaR = fs_->make<TH1F>("h1_P1P2_DeltaR","h1_P1P2_DeltaR",1000,0,6.30);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenAna::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenAna);
