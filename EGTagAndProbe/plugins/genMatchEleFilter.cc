#ifndef GENMATCHELEFILTER_H
#define GENMATCHELEFILTER_H

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <iostream>

using namespace edm;
using namespace std;
// using namespace reco;

 
class genMatchEleFilter : public edm::EDFilter {

    public:
        genMatchEleFilter(const edm::ParameterSet &);
        ~genMatchEleFilter();

    private:
        bool filter(edm::Event &, edm::EventSetup const&);
        EDGetTokenT<edm::View<reco::GsfElectron> >  _eleTag;
        EDGetTokenT<edm::View<reco::GenParticle> > _genParticlesTag;

        bool matchToTruth(const reco::GsfElectron ele, 
			  const edm::Handle<edm::View<reco::GenParticle>>  &genParticles);


};

genMatchEleFilter::genMatchEleFilter(const edm::ParameterSet & iConfig) :
  _eleTag   (consumes<edm::View<reco::GsfElectron> > (iConfig.getParameter<InputTag>("electrons"))),
  _genParticlesTag (consumes<edm::View<reco::GenParticle> > (iConfig.getParameter<edm::InputTag>("genParticles")))
{
    produces <reco::GsfElectronCollection>  ();
}

genMatchEleFilter::~genMatchEleFilter()
{}

bool genMatchEleFilter::filter(edm::Event & iEvent, edm::EventSetup const& iSetup)
{

  std::unique_ptr<reco::GsfElectronCollection>  resultEle  ( new reco::GsfElectronCollection()  );
  //auto_ptr<reco::GsfElectronCollection>  resultEle  ( new reco::GsfElectronCollection()  );

   
  edm::Handle<edm::View<reco::GsfElectron> > eleHandle;
  iEvent.getByToken (_eleTag, eleHandle);

  Handle<edm::View<reco::GenParticle> > genParticles;
  iEvent.getByToken(_genParticlesTag,genParticles);
  
  int goodEles = 0;
  
  for (uint iele = 0; iele < eleHandle->size(); ++iele)
    {
      const auto ele = eleHandle->ptrAt(iele) ;    
      reco::GsfElectron el(*ele);

      if (matchToTruth(el,genParticles))
	{
	  ++goodEles;
	  resultEle->push_back (el);
	}
    }
  
  
  if (goodEles == 0) return false;            
  
  iEvent.put(std::move(resultEle));
  return true;
}





bool genMatchEleFilter::matchToTruth(const reco::GsfElectron ele, 
				     const edm::Handle<edm::View<reco::GenParticle>> &prunedGenParticles){

  // 
  // Explicit loop and geometric matching method
  //

  // Find the closest status 1 gen electron to the reco electron
  double dR = 999;
  const reco::Candidate *closestElectron = 0;
  for(size_t i=0; i<prunedGenParticles->size();i++){
    const reco::Candidate *particle = &(*prunedGenParticles)[i];
    // Drop everything that is not electron or not status 1
    if( abs(particle->pdgId()) != 11 || particle->status() != 1 || particle->pt()<5)
      continue;
    //
    double dRtmp = deltaR( ele.p4(), particle->p4() );
    if( dRtmp < dR ){
      dR = dRtmp;
      closestElectron = particle;
    }
  }
  // See if the closest electron (if it exists) is close enough.
  // If not, no match found.
  if( !(closestElectron != 0 && dR < 0.1) ) {
    return false;
  }

  return true;

}




#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(genMatchEleFilter);

#endif
