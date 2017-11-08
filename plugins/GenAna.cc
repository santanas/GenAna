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
  edm::EDGetTokenT<reco::GenJetCollection> genJetsAK4InputToken_;
  edm::EDGetTokenT<reco::GenJetCollection> genJetsAK8InputToken_;

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

  TH1F *h1_Mjj;
  TH1F *h1_Mjj_sel;
  TH1F *h1_DeltaEtajj;

  TH1F *h1_AK8jet1_pt;
  TH1F *h1_AK8jet1_eta;
  TH1F *h1_AK8jet1_phi;
  TH1F *h1_AK8jet1_mass;

  TH1F *h1_AK8jet2_pt;
  TH1F *h1_AK8jet2_eta;
  TH1F *h1_AK8jet2_phi;
  TH1F *h1_AK8jet2_mass;

  TH1F *h1_AK8jet3_pt;
  TH1F *h1_AK8jet3_eta;
  TH1F *h1_AK8jet3_phi;
  TH1F *h1_AK8jet3_mass;

  TH1F *h1_AK8jet4_pt;
  TH1F *h1_AK8jet4_eta;
  TH1F *h1_AK8jet4_phi;
  TH1F *h1_AK8jet4_mass;

  TH1F *h1_Mjjj;
  TH1F *h1_Mjjj_match;
  TH1F *h1_Mjjj_sel;
  TH1F *h1_DeltaEtajj12;
  TH1F *h1_DeltaEtajj13;
  TH1F *h1_DeltaEtajj23;
  TH1F *h1_pt3_over_Mjjj;

  TH1F *h1_DeltaRMin_AK8Jet1Parton;
  TH1F *h1_DeltaRMin_AK8Jet2Parton;
  TH1F *h1_DeltaRMin_AK8Jet3Parton;

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
  genPartInputToken_ = (consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticlesInputTag")));

  genJetsAK4InputToken_ = (consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("genJetsAK4InputTag")));
  genJetsAK8InputToken_ = (consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("genJetsAK8InputTag")));
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

   edm::Handle<reco::GenJetCollection> genJetsAK4;
   if (!iEvent.isRealData())
     iEvent.getByToken(genJetsAK4InputToken_,genJetsAK4);

   edm::Handle<reco::GenJetCollection> genJetsAK8;
   if (!iEvent.isRealData())
     iEvent.getByToken(genJetsAK8InputToken_,genJetsAK8);


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

     if(Res1.M()>0)
       {
	 float R = Res2.M() / Res1.M();
	 h1_R->Fill(R);
       }

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

     //AK8 gen jets - dijet sel
     if( genJetsAK8.isValid() && genJetsAK8->size()>=2 ) {
      
       TLorentzVector AK8Jet1, AK8Jet2, AK8Jet3, AK8Jet4, Dijet, Trijet;

       AK8Jet1.SetPtEtaPhiM(genJetsAK8->at(0).pt(),genJetsAK8->at(0).eta(),genJetsAK8->at(0).phi(),genJetsAK8->at(0).mass());	 
       AK8Jet2.SetPtEtaPhiM(genJetsAK8->at(1).pt(),genJetsAK8->at(1).eta(),genJetsAK8->at(1).phi(),genJetsAK8->at(1).mass());	 
       Dijet = AK8Jet1 + AK8Jet2;

       float DeltaEtaJJ = fabs(AK8Jet1.Eta()-AK8Jet2.Eta());

       h1_AK8jet1_pt->Fill(AK8Jet1.Pt());
       h1_AK8jet1_eta->Fill(AK8Jet1.Eta());
       h1_AK8jet1_phi->Fill(AK8Jet1.Phi());
       h1_AK8jet1_mass->Fill(AK8Jet1.M());

       h1_AK8jet2_pt->Fill(AK8Jet2.Pt());
       h1_AK8jet2_eta->Fill(AK8Jet2.Eta());
       h1_AK8jet2_phi->Fill(AK8Jet2.Phi());
       h1_AK8jet2_mass->Fill(AK8Jet2.M());

       h1_Mjj->Fill(Dijet.M());
       h1_DeltaEtajj->Fill(DeltaEtaJJ);

       //dijet selection
       if( AK8Jet1.Pt() > 50 && fabs(AK8Jet1.Eta()) < 2.5 && 
	   AK8Jet2.Pt() > 50 && fabs(AK8Jet2.Eta()) < 2.5 && 
	   DeltaEtaJJ < 1.3)
	 {
	   h1_Mjj_sel->Fill(Dijet.M());
	 }
     
       //3rd jet
       if( genJetsAK8->size()>=3 ) {
	 	 
	 AK8Jet3.SetPtEtaPhiM(genJetsAK8->at(2).pt(),genJetsAK8->at(2).eta(),genJetsAK8->at(2).phi(),genJetsAK8->at(2).mass());	 
	 Trijet = AK8Jet1 + AK8Jet2 + AK8Jet3;
	 
	 float DeltaEtaJJ12 = fabs(AK8Jet1.Eta()-AK8Jet2.Eta());
	 float DeltaEtaJJ13 = fabs(AK8Jet1.Eta()-AK8Jet3.Eta());
	 float DeltaEtaJJ23 = fabs(AK8Jet2.Eta()-AK8Jet3.Eta());
	 
	 float pT3_over_mjjj = AK8Jet3.Pt() / Trijet.M();
	 
	 h1_AK8jet3_pt->Fill(AK8Jet3.Pt());
	 h1_AK8jet3_eta->Fill(AK8Jet3.Eta());
	 h1_AK8jet3_phi->Fill(AK8Jet3.Phi());
	 h1_AK8jet3_mass->Fill(AK8Jet3.M());
	 
	 h1_Mjjj->Fill(Trijet.M());
	 
	 h1_DeltaEtajj12->Fill(DeltaEtaJJ12);
	 h1_DeltaEtajj13->Fill(DeltaEtaJJ13);
	 h1_DeltaEtajj23->Fill(DeltaEtaJJ23);
	 
	 h1_pt3_over_Mjjj->Fill(pT3_over_mjjj);
	 
	 //trijet selection
	 if( AK8Jet1.Pt() > 50 && fabs(AK8Jet1.Eta()) < 2.5 && 
	     AK8Jet2.Pt() > 50 && fabs(AK8Jet2.Eta()) < 2.5 && 
	     AK8Jet3.Pt() > 50 && fabs(AK8Jet3.Eta()) < 2.5 && 
	     DeltaEtaJJ12 < 1.2 &&
	     DeltaEtaJJ13 < 1.9 &&
	     pT3_over_mjjj > 0.2
	     )
	   {
	     h1_Mjjj_sel->Fill(Trijet.M());
	   }
	 	 
	 //gen matching
	 bool jet1Match = false; 
	 bool jet2Match = false; 
	 bool jet3Match = false;
	 
	 h1_DeltaRMin_AK8Jet1Parton->Fill( std::min(std::min(P1.DeltaR(AK8Jet1), P2.DeltaR(AK8Jet1)), P3.DeltaR(AK8Jet1)) );
	 h1_DeltaRMin_AK8Jet2Parton->Fill( std::min(std::min(P1.DeltaR(AK8Jet2), P2.DeltaR(AK8Jet2)), P3.DeltaR(AK8Jet2)) );
	 h1_DeltaRMin_AK8Jet3Parton->Fill( std::min(std::min(P1.DeltaR(AK8Jet3), P2.DeltaR(AK8Jet3)), P3.DeltaR(AK8Jet3)) );
	 
	 if( P1.DeltaR(AK8Jet1) < 0.2 || P2.DeltaR(AK8Jet1) <0.2 || P3.DeltaR(AK8Jet1) <0.2 )
	   jet1Match = true;
	 
	 if( P1.DeltaR(AK8Jet2) < 0.2 || P2.DeltaR(AK8Jet2) <0.2 || P3.DeltaR(AK8Jet2) <0.2 )
	   jet2Match = true;
	 
	 if( P1.DeltaR(AK8Jet3) < 0.2 || P2.DeltaR(AK8Jet3) <0.2 || P3.DeltaR(AK8Jet3) <0.2 )
	   jet3Match = true;
	 
	 if (jet1Match && jet2Match && jet3Match)
	   h1_Mjjj_match->Fill(Trijet.M());	 

	 //4th jet
	 if(genJetsAK8->size()>=4)
	   {
	     AK8Jet4.SetPtEtaPhiM(genJetsAK8->at(3).pt(),genJetsAK8->at(3).eta(),genJetsAK8->at(3).phi(),genJetsAK8->at(3).mass());	 
	     
	     h1_AK8jet4_pt->Fill(AK8Jet4.Pt());
	     h1_AK8jet4_eta->Fill(AK8Jet4.Eta());
	     h1_AK8jet4_phi->Fill(AK8Jet4.Phi());
	     h1_AK8jet4_mass->Fill(AK8Jet4.M());
	   }

       }//gen jet ak8 3rd jet
  
     }//gen jet ak8 valid
     
   }//gen particles valid

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

  h1_Mjj = fs_->make<TH1F>("h1_Mjj","h1_Mjj",1000,0,10000);
  h1_Mjj_sel = fs_->make<TH1F>("h1_Mjj_sel","h1_Mjj_sel",1000,0,10000);
  h1_DeltaEtajj = fs_->make<TH1F>("h1_DeltaEtajj","h1_DeltaEtajj",100,0,6);

  h1_AK8jet1_mass = fs_->make<TH1F>("h1_AK8jet1_mass","h1_AK8jet1_mass",1000,0,10000);
  h1_AK8jet1_pt = fs_->make<TH1F>("h1_AK8jet1_pt","h1_AK8jet1_pt",1000,0,10000);
  h1_AK8jet1_eta = fs_->make<TH1F>("h1_AK8jet1_eta","h1_AK8jet1_eta",100,-6,6);
  h1_AK8jet1_phi = fs_->make<TH1F>("h1_AK8jet1_phi","h1_AK8jet1_phi",100,-3.15,3.15);

  h1_AK8jet2_mass = fs_->make<TH1F>("h1_AK8jet2_mass","h1_AK8jet2_mass",1000,0,10000);
  h1_AK8jet2_pt = fs_->make<TH1F>("h1_AK8jet2_pt","h1_AK8jet2_pt",1000,0,10000);
  h1_AK8jet2_eta = fs_->make<TH1F>("h1_AK8jet2_eta","h1_AK8jet2_eta",100,-6,6);
  h1_AK8jet2_phi = fs_->make<TH1F>("h1_AK8jet2_phi","h1_AK8jet2_phi",100,-3.15,3.15);

  h1_AK8jet3_mass = fs_->make<TH1F>("h1_AK8jet3_mass","h1_AK8jet3_mass",1000,0,10000);
  h1_AK8jet3_pt = fs_->make<TH1F>("h1_AK8jet3_pt","h1_AK8jet3_pt",1000,0,10000);
  h1_AK8jet3_eta = fs_->make<TH1F>("h1_AK8jet3_eta","h1_AK8jet3_eta",100,-6,6);
  h1_AK8jet3_phi = fs_->make<TH1F>("h1_AK8jet3_phi","h1_AK8jet3_phi",100,-3.15,3.15);

  h1_AK8jet4_mass = fs_->make<TH1F>("h1_AK8jet4_mass","h1_AK8jet4_mass",1000,0,10000);
  h1_AK8jet4_pt = fs_->make<TH1F>("h1_AK8jet4_pt","h1_AK8jet4_pt",1000,0,10000);
  h1_AK8jet4_eta = fs_->make<TH1F>("h1_AK8jet4_eta","h1_AK8jet4_eta",100,-6,6);
  h1_AK8jet4_phi = fs_->make<TH1F>("h1_AK8jet4_phi","h1_AK8jet4_phi",100,-3.15,3.15);

  h1_Mjjj = fs_->make<TH1F>("h1_Mjjj","h1_Mjjj",1000,0,10000);
  h1_Mjjj_match = fs_->make<TH1F>("h1_Mjjj_match","h1_Mjjj_match",1000,0,10000);
  h1_Mjjj_sel = fs_->make<TH1F>("h1_Mjjj_sel","h1_Mjjj_sel",1000,0,10000);
  h1_DeltaEtajj12 = fs_->make<TH1F>("h1_DeltaEtajj12","h1_DeltaEtajj12",100,0,6);
  h1_DeltaEtajj13 = fs_->make<TH1F>("h1_DeltaEtajj13","h1_DeltaEtajj13",100,0,6);
  h1_DeltaEtajj23 = fs_->make<TH1F>("h1_DeltaEtajj23","h1_DeltaEtajj23",100,0,6);
  h1_pt3_over_Mjjj = fs_->make<TH1F>("h1_pt3_over_Mjjj","h1_pt3_over_Mjjj",100,0,1);

  h1_DeltaRMin_AK8Jet1Parton = fs_->make<TH1F>("h1_DeltaRMin_AK8Jet1Parton","h1_DeltaRMin_AK8Jet1Parton",100,0,6);
  h1_DeltaRMin_AK8Jet2Parton = fs_->make<TH1F>("h1_DeltaRMin_AK8Jet2Parton","h1_DeltaRMin_AK8Jet2Parton",100,0,6);
  h1_DeltaRMin_AK8Jet3Parton = fs_->make<TH1F>("h1_DeltaRMin_AK8Jet3Parton","h1_DeltaRMin_AK8Jet3Parton",100,0,6);
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
