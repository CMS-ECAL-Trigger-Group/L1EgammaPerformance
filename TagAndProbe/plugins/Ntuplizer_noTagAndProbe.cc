#ifndef NTUPLIZER_NOTAGANDPROBE_H
#define NTUPLIZER_NOTAGANDPROBE_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <TNtuple.h>
#include <TString.h>
#include <bitset>


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "tParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"



//Set this variable to decide the number of triggers that you want to check simultaneously
#define NUMBER_OF_MAXIMUM_TRIGGERS 64


/*
██████  ███████  ██████ ██       █████  ██████   █████  ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ████   ██
██   ██ █████   ██      ██      ███████ ██████  ███████    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████  ██████ ███████ ██   ██ ██   ██ ██   ██    ██    ██  ██████  ██   ████
*/

class Ntuplizer_noTagAndProbe : public edm::EDAnalyzer {
    public:
        /// Constructor
        explicit Ntuplizer_noTagAndProbe(const edm::ParameterSet&);
        /// Destructor
        virtual ~Ntuplizer_noTagAndProbe();

    private:
        //----edm control---
        virtual void beginJob() ;
        virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob();
        virtual void endRun(edm::Run const&, edm::EventSetup const&);
        void Initialize();
        bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);

        TTree *_tree;
        TTree *_triggerNamesTreeTag;
        TTree *_triggerNamesTreeProbe;
        std::string _treeName;
        // -------------------------------------
        // variables to be filled in output tree
        ULong64_t       _indexevents;
        Int_t           _runNumber;
        Int_t           _lumi;
        unsigned long _eleProbeTriggerBits;
        unsigned long _eleTagTriggerBits;
        float _eleProbePt;
        float _eleProbeEta;
        float _eleProbePhi;
        float _eleProbeSclEt;
        int _eleProbeCharge;
        float _hltPt;
        float _hltEta;
        float _hltPhi;
        int _l1tQual;
        float _l1tPt;
        float _l1tEta;
        float _l1tPhi;
        int _l1tIso;
        int _l1tEmuQual;
        float _l1tEmuPt;
        float _l1tEmuEta;
        float _l1tEmuPhi;
        int _l1tEmuIso;
        int _l1tEmuNTT;
        int _l1tEmuTowerIEta;
        int _l1tEmuTowerIPhi;
        int _l1tEmuRawEt;
        int _l1tEmuIsoEt;
        Bool_t _isTagHLTmatched;
        Bool_t _isProbeHLTmatched;
        Bool_t _isMatched;
        Bool_t _isOS;
        int _foundTag;
        float _eleTagPt;
        float _eleTagEta;
        float _eleTagPhi;
        int _eleTagCharge;
        float _Mee;
        int _Nvtx;

        edm::EDGetTokenT<pat::ElectronRefVector>  _electronsTag;
        edm::EDGetTokenT<edm::ValueMap<bool> > _eleLooseIdMapTag;
        edm::EDGetTokenT<edm::ValueMap<bool> > _eleMediumIdMapTag;
        edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _triggerObjects;
        edm::EDGetTokenT<edm::TriggerResults> _triggerBits;
        edm::EDGetTokenT<l1t::EGammaBxCollection> _L1EGTag  ;
        edm::EDGetTokenT<l1t::EGammaBxCollection> _L1EmuEGTag  ;
        edm::EDGetTokenT<std::vector<reco::Vertex>> _VtxTag;

        //!Contains the parameters
        tVParameterSet _parametersTag;
        tVParameterSet _parametersProbe;

        edm::InputTag _processName;
        //! Maximum
        std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _eleProbeTriggerBitSet;
        std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _eleTagTriggerBitSet;


        HLTConfigProvider _hltConfig;


};

/*
██ ███    ███ ██████  ██      ███████ ███    ███ ███████ ███    ██ ████████  █████  ████████ ██  ██████  ███    ██
██ ████  ████ ██   ██ ██      ██      ████  ████ ██      ████   ██    ██    ██   ██    ██    ██ ██    ██ ████   ██
██ ██ ████ ██ ██████  ██      █████   ██ ████ ██ █████   ██ ██  ██    ██    ███████    ██    ██ ██    ██ ██ ██  ██
██ ██  ██  ██ ██      ██      ██      ██  ██  ██ ██      ██  ██ ██    ██    ██   ██    ██    ██ ██    ██ ██  ██ ██
██ ██      ██ ██      ███████ ███████ ██      ██ ███████ ██   ████    ██    ██   ██    ██    ██  ██████  ██   ████
*/

// ----Constructor and Destructor -----
Ntuplizer_noTagAndProbe::Ntuplizer_noTagAndProbe(const edm::ParameterSet& iConfig) :
_electronsTag       (consumes<pat::ElectronRefVector>                     (iConfig.getParameter<edm::InputTag>("electrons"))),
_eleLooseIdMapTag  (consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"))),
_eleMediumIdMapTag  (consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"))),
_triggerObjects (consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerSet"))),
_triggerBits    (consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("triggerResultsLabel"))),
_L1EGTag       (consumes<l1t::EGammaBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1EG"))),
_L1EmuEGTag    (consumes<l1t::EGammaBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1EmuEG"))),
_VtxTag         (consumes<std::vector<reco::Vertex>>              (iConfig.getParameter<edm::InputTag>("Vertexes")))
{
    this -> _treeName = iConfig.getParameter<std::string>("treeName");
    this -> _processName = iConfig.getParameter<edm::InputTag>("triggerResultsLabel");

    TString triggerNameTag;
    edm::Service<TFileService> fs;
    this -> _triggerNamesTreeTag = fs -> make<TTree>("triggerNamesTag", "triggerNamesTag");
    this -> _triggerNamesTreeTag -> Branch("triggerNamesTag",&triggerNameTag);

    //Building the trigger arrays
    const std::vector<edm::ParameterSet>& HLTListTag = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerListTag");
    for (const edm::ParameterSet& parameterSet : HLTListTag) {
        tParameterSet pSet;
        pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
        triggerNameTag = pSet.hltPath;
        pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
        pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
        pSet.leg1 = parameterSet.getParameter<int>("leg1");
        pSet.leg2 = parameterSet.getParameter<int>("leg2");
        this -> _parametersTag.push_back(pSet);

        this -> _triggerNamesTreeTag -> Fill();
    }


    TString triggerNameProbe;
    this -> _triggerNamesTreeProbe = fs -> make<TTree>("triggerNamesProbe", "triggerNamesProbe");
    this -> _triggerNamesTreeProbe -> Branch("triggerNamesProbe",&triggerNameProbe);

    //Building the trigger arrays
    const std::vector<edm::ParameterSet>& HLTListProbe = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerListProbe");
    for (const edm::ParameterSet& parameterSet : HLTListProbe) {
        tParameterSet pSet;
        pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
        triggerNameTag = pSet.hltPath;
        pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
        pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
        pSet.leg1 = parameterSet.getParameter<int>("leg1");
        pSet.leg2 = parameterSet.getParameter<int>("leg2");
        this -> _parametersProbe.push_back(pSet);

        this -> _triggerNamesTreeProbe -> Fill();
    }


    this -> Initialize();
    return;
}

Ntuplizer_noTagAndProbe::~Ntuplizer_noTagAndProbe()
{}

void Ntuplizer_noTagAndProbe::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{

    Bool_t changedConfig = false;

    if(!this -> _hltConfig.init(iRun, iSetup, this -> _processName.process(), changedConfig)){
        edm::LogError("HLTMatchingFilter") << "Initialization of HLTConfigProvider failed!!";
        return;
    }

    const edm::TriggerNames::Strings& triggerNames = this -> _hltConfig.triggerNames();
    //std::cout << " ===== LOOKING FOR THE PATH INDEXES =====" << std::endl;
    for (tParameterSet& parameter : this -> _parametersTag){
        const std::string& hltPath = parameter.hltPath;
        bool found = false;
        for(unsigned int j=0; j < triggerNames.size(); j++)
        {
            //std::cout << triggerNames[j] << std::endl;
            if (triggerNames[j].find(hltPath) != std::string::npos) {
                found = true;
                parameter.hltPathIndex = j;

                //std::cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << std::endl;
            }
        }
        if (!found) parameter.hltPathIndex = -1;
    }


    for (tParameterSet& parameter : this -> _parametersProbe){
        const std::string& hltPath = parameter.hltPath;
        bool found = false;
        for(unsigned int j=0; j < triggerNames.size(); j++)
        {
            //std::cout << triggerNames[j] << std::endl;
            if (triggerNames[j].find(hltPath) != std::string::npos) {
                found = true;
                parameter.hltPathIndex = j;

                //std::cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << std::endl;
            }
        }
        if (!found) parameter.hltPathIndex = -1;
    }


}

void Ntuplizer_noTagAndProbe::Initialize() {
    this -> _indexevents = 0;
    this -> _runNumber = 0;
    this -> _lumi = 0;
    this -> _eleProbePt = -1.;
    this -> _eleProbeEta = -1.;
    this -> _eleProbePhi = -1.;
    this -> _eleProbeSclEt = -1.;
    this -> _eleProbeCharge = 0;
    this -> _eleTagPt = -1.;
    this -> _eleTagEta = -1.;
    this -> _eleTagPhi = -1.;
    this -> _eleTagCharge = 0;
    this -> _Mee = 0;
    this -> _isTagHLTmatched = false;
    this -> _isProbeHLTmatched = false;
    this -> _hltPt = -1;
    this -> _hltEta = 666;
    this -> _hltPhi = 666;
    this -> _l1tPt = -1;
    this -> _l1tEta = 666;
    this -> _l1tPhi = 666;
    this -> _l1tQual = -1;
    this -> _l1tIso = -1;
    this -> _l1tEmuPt = -1;
    this -> _l1tEmuEta = 666;
    this -> _l1tEmuPhi = 666;
    this -> _l1tEmuQual = -1;
    this -> _l1tEmuIso = -1;
    this -> _l1tEmuNTT = -1;
    this -> _l1tEmuTowerIEta = -1;
    this -> _l1tEmuTowerIPhi = -1;
    this -> _l1tEmuRawEt = -1;
    this -> _l1tEmuIsoEt = -1;
    this -> _foundTag = 0;
}


void Ntuplizer_noTagAndProbe::beginJob()
{
    edm::Service<TFileService> fs;
    this -> _tree = fs -> make<TTree>(this -> _treeName.c_str(), this -> _treeName.c_str());

    //Branches
    this -> _tree -> Branch("EventNumber",&_indexevents,"EventNumber/l");
    this -> _tree -> Branch("RunNumber",&_runNumber,"RunNumber/I");
    this -> _tree -> Branch("lumi",&_lumi,"lumi/I");
    this -> _tree -> Branch("eleProbeTriggerBits", &_eleProbeTriggerBits, "eleProbeTriggerBits/l");
    this -> _tree -> Branch("eleTagTriggerBits", &_eleTagTriggerBits, "eleTagTriggerBits/l");
    this -> _tree -> Branch("eleProbePt",  &_eleProbePt,  "eleProbePt/F");
    this -> _tree -> Branch("eleProbeEta", &_eleProbeEta, "eleProbeEta/F");
    this -> _tree -> Branch("eleProbePhi", &_eleProbePhi, "eleProbePhi/F");
    this -> _tree -> Branch("eleProbeSclEt",  &_eleProbeSclEt,  "eleProbeSclEt/F");
    this -> _tree -> Branch("eleProbeCharge",  &_eleProbeCharge,  "eleProbeCharge/I");
    this -> _tree -> Branch("eleTagPt",  &_eleTagPt,  "eleTagPt/F");
    this -> _tree -> Branch("eleTagEta", &_eleTagEta, "eleTagEta/F");
    this -> _tree -> Branch("eleTagPhi", &_eleTagPhi, "eleTagPhi/F");
    this -> _tree -> Branch("eleTagCharge",  &_eleTagCharge,  "eleTagCharge/I");
    this -> _tree -> Branch("Mee",  &_Mee,  "Mee/F");
    this -> _tree -> Branch("hltPt",  &_hltPt,  "hltPt/F");
    this -> _tree -> Branch("hltEta", &_hltEta, "hltEta/F");
    this -> _tree -> Branch("hltPhi", &_hltPhi, "hltPhi/F");
    this -> _tree -> Branch("l1tPt",  &_l1tPt,  "l1tPt/F");
    this -> _tree -> Branch("l1tEta", &_l1tEta, "l1tEta/F");
    this -> _tree -> Branch("l1tPhi", &_l1tPhi, "l1tPhi/F");
    this -> _tree -> Branch("l1tQual", &_l1tQual, "l1tQual/I");
    this -> _tree -> Branch("l1tIso", &_l1tIso, "l1tIso/I");
    this -> _tree -> Branch("l1tEmuPt",  &_l1tEmuPt,  "l1tEmuPt/F");
    this -> _tree -> Branch("l1tEmuEta", &_l1tEmuEta, "l1tEmuEta/F");
    this -> _tree -> Branch("l1tEmuPhi", &_l1tEmuPhi, "l1tEmuPhi/F");
    this -> _tree -> Branch("l1tEmuQual", &_l1tEmuQual, "l1tEmuQual/I");
    this -> _tree -> Branch("l1tEmuIso", &_l1tEmuIso, "l1tEmuIso/I");
    this -> _tree -> Branch("l1tEmuNTT", &_l1tEmuNTT, "l1tEmuNTT/I");
    this -> _tree -> Branch("l1tEmuTowerIEta", &_l1tEmuTowerIEta, "l1tEmuTowerIEta/I");
    this -> _tree -> Branch("l1tEmuTowerIPhi", &_l1tEmuTowerIPhi, "l1tEmuTowerIPhi/I");
    this -> _tree -> Branch("l1tEmuRawEt", &_l1tEmuRawEt, "l1tEmuRawEt/I");
    this -> _tree -> Branch("l1tEmuIsoEt", &_l1tEmuIsoEt, "l1tEmuIsoEt/I");


    this -> _tree -> Branch("isTagHLTmatched", &_isTagHLTmatched, "isTagHLTmatched/O");
    this -> _tree -> Branch("isProbeHLTmatched", &_isProbeHLTmatched, "isProbeHLTmatched/O");
    this -> _tree -> Branch("isOS", &_isOS, "isOS/O");
    this -> _tree -> Branch("foundTag", &_foundTag, "foundTag/I");
    this -> _tree -> Branch("Nvtx", &_Nvtx, "Nvtx/I");

    return;
}


void Ntuplizer_noTagAndProbe::endJob()
{
    return;
}


void Ntuplizer_noTagAndProbe::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    return;
}


void Ntuplizer_noTagAndProbe::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
    this -> Initialize();

    _indexevents = iEvent.id().event();
    _runNumber = iEvent.id().run();
    _lumi = iEvent.luminosityBlock();

    // std::auto_ptr<pat::MuonRefVector> resultMuon(new pat::MuonRefVector);

    // search for the tag in the event
    edm::Handle<edm::View<pat::Electron> > electrons;
    edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
    edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<std::vector<reco::Vertex> >  vertices;

    iEvent.getByToken(this -> _electronsTag, electrons);
    iEvent.getByToken(this -> _eleLooseIdMapTag, loose_id_decisions);
    iEvent.getByToken(this -> _eleMediumIdMapTag, medium_id_decisions);
    iEvent.getByToken(this -> _triggerObjects, triggerObjects);
    iEvent.getByToken(this -> _triggerBits, triggerBits);
    iEvent.getByToken(this -> _VtxTag,vertices);


    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

    for( edm::View<pat::Electron>::const_iterator el = electrons->begin(); el != electrons->end(); el++){
      
      const unsigned int i = distance (electrons->begin(), el);
      const auto eleTag = electrons->ptrAt(i);

      for( edm::View<pat::Electron>::const_iterator el2 = electrons->begin(); el2 != electrons->end(); el2++){

	const unsigned int j = distance (electrons->begin(), el2);
	if(i==j) continue;

	const auto eleProbe = electrons->ptrAt(j);
	int isProbeLoose = (*loose_id_decisions)[eleProbe];
	float eleProbeEta = eleProbe->p4().Eta();
	if(!isProbeLoose || (abs(eleProbeEta)>1.4442 && abs(eleProbeEta)<1.566)) continue;

	bool isOS = (eleTag->charge() / eleProbe->charge() < 0) ? true : false;
	float Mee = (eleTag->p4() + eleProbe->p4()).M();


	this -> _isOS = isOS;
	this -> _Mee = Mee;

	//! TagAndProbe on HLT eles

	this -> _eleProbeTriggerBitSet.reset();
	this -> _eleTagTriggerBitSet.reset();


	for (pat::TriggerObjectStandAlone  obj : *triggerObjects)
	  {
	    if(!obj.hasTriggerObjectType(trigger::TriggerElectron)) continue;
      
	    const float dR_tag = deltaR (*eleTag, obj);
	    if ( dR_tag < 0.3)
	      {
		this -> _isTagHLTmatched = true;
            
		obj.unpackPathNames(names);
		const edm::TriggerNames::Strings& triggerNames = names.triggerNames();
		//Looking for the path
		unsigned int x = 0;
		bool foundTrigger = false;
		for (const tParameterSet& parameter : this -> _parametersTag)
		  {
		    if ((parameter.hltPathIndex >= 0)&&(obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
		      {
			foundTrigger = true;
			//Path found, now looking for the label 1, if present in the parameter set
			//std::cout << "==== FOUND PATH " << triggerNames[parameter.hltPathIndex] << " ====" << std::endl;
			//Retrieving filter list for the event
			const std::vector<std::string>& filters = (parameter.hltFilters1);
			if (this -> hasFilters(obj, filters))
			  {
			    //std::cout << "#### FOUND ELE WITH HLT PATH " << x << " ####" << std::endl;
			    this -> _hltPt = obj.pt();
			    this -> _hltEta = obj.eta();
			    this -> _hltPhi = obj.phi();			    this -> _eleTagTriggerBitSet[x] = true;			    
			    //std::cout << this -> _eleTagTriggerBitSet.to_string() << std::endl;
			  }
		      }
		    x++;
		  }
		if (foundTrigger){
		  this -> _foundTag++;
		  this -> _isTagHLTmatched = true;
		}
	      }


	    const float dR_probe = deltaR (*eleProbe, obj);
	    if ( dR_probe < 0.3)
	      {
		this -> _isProbeHLTmatched = true;
            
		obj.unpackPathNames(names);
		const edm::TriggerNames::Strings& triggerNames = names.triggerNames();
		//Looking for the path
		unsigned int x = 0;
		bool foundTrigger = false;
		for (const tParameterSet& parameter : this -> _parametersProbe)
		  {
		    if ((parameter.hltPathIndex >= 0)&&(obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
		      {
			foundTrigger = true;
			//Path found, now looking for the label 1, if present in the parameter set
			//std::cout << "==== FOUND PATH " << triggerNames[parameter.hltPathIndex] << " ====" << std::endl;
			//Retrieving filter list for the event
			const std::vector<std::string>& filters = (parameter.hltFilters1);
			if (this -> hasFilters(obj, filters))
			  {
			    //std::cout << "#### FOUND ELE WITH HLT PATH " << x << " ####" << std::endl;
			    this -> _hltPt = obj.pt();
			    this -> _hltEta = obj.eta();
			    this -> _hltPhi = obj.phi();
			    this -> _eleProbeTriggerBitSet[x] = true;
			    //std::cout << this -> _eleTagTriggerBitSet.to_string() << std::endl;
			  }
		      }
		    x++;
		  }
		if (foundTrigger) this -> _isProbeHLTmatched = true;
	      }



	  }

      

	//! TagAndProbe on L1T EG

	edm::Handle< BXVector<l1t::EGamma> >  L1EGHandle;
	iEvent.getByToken(_L1EGTag, L1EGHandle);

	float minDR = 0.3; //Uncomment for new match algo

	//cout<<"ill try this: "<<endl;

	for (l1t::EGammaBxCollection::const_iterator bx0EGIt = L1EGHandle->begin(0); bx0EGIt != L1EGHandle->end(0) ; bx0EGIt++)
	  {
	    const float dR = deltaR(*eleProbe, *bx0EGIt);
	    const l1t::EGamma& l1tEG = *bx0EGIt;

	    cout<<"FW EG, pT = "<<l1tEG.pt()<<", eta = "<<l1tEG.eta()<<", phi = "<<l1tEG.phi()<<endl;

	    if (dR < minDR) //Uncomment for new match algo
	      {
		minDR = dR; //Uncomment for new match algo
		this -> _l1tPt = l1tEG.pt();
		this -> _l1tEta = l1tEG.eta();
		this -> _l1tPhi = l1tEG.phi();
		this -> _l1tIso = l1tEG.hwIso();
		this -> _l1tQual = l1tEG.hwQual();
	      }
	  }

	edm::Handle< BXVector<l1t::EGamma> >  L1EmuEGHandle;
	try {iEvent.getByToken(_L1EmuEGTag, L1EmuEGHandle);} catch (...) {;}

	if (L1EmuEGHandle.isValid())
	  {
	    minDR = 0.3;
	
	    for (l1t::EGammaBxCollection::const_iterator bx0EmuEGIt = L1EmuEGHandle->begin(0); bx0EmuEGIt != L1EmuEGHandle->end(0) ; bx0EmuEGIt++)
	      {
		const float dR = deltaR(*eleProbe, *bx0EmuEGIt);
		const l1t::EGamma& l1tEmuEG = *bx0EmuEGIt;
		
		cout<<"Emul EG, pT = "<<l1tEmuEG.pt()<<", eta = "<<l1tEmuEG.eta()<<", phi = "<<l1tEmuEG.phi()<<endl;
		
		if (dR < minDR) //Uncomment for new match algo
		  {
		    minDR = dR; //Uncomment for new match algo
		    this -> _l1tEmuPt        = l1tEmuEG.pt();
		    this -> _l1tEmuEta       = l1tEmuEG.eta();
		    this -> _l1tEmuPhi       = l1tEmuEG.phi();
		    this -> _l1tEmuIso       = l1tEmuEG.hwIso();
		    this -> _l1tEmuNTT       = l1tEmuEG.nTT();
		    this -> _l1tEmuQual      = l1tEmuEG.hwQual();
		    this -> _l1tEmuTowerIEta = l1tEmuEG.towerIEta();
		    this -> _l1tEmuTowerIPhi = l1tEmuEG.towerIPhi();
		    this -> _l1tEmuRawEt     = l1tEmuEG.rawEt();
		    this -> _l1tEmuIsoEt     = l1tEmuEG.isoEt();
		    
		  }
	      }
	  }
	
	this -> _eleProbePt = eleProbe -> pt();
	this -> _eleProbeEta = eleProbe -> eta();
	this -> _eleProbePhi = eleProbe -> phi();
	this -> _eleProbeSclEt = (eleProbe->superCluster()->energy()) / cosh(eleProbe->superCluster()->eta()) ;
	this -> _eleProbeCharge = eleProbe -> charge();


	this -> _eleTagPt = eleTag -> pt();
	this -> _eleTagEta = eleTag -> eta();
	this -> _eleTagPhi = eleTag -> phi();
	this -> _eleTagCharge = eleTag -> charge();

	this -> _Nvtx = vertices->size();

 
	this -> _eleProbeTriggerBits = this -> _eleProbeTriggerBitSet.to_ulong();
	this -> _eleTagTriggerBits = this -> _eleTagTriggerBitSet.to_ulong();
	//std::cout << "++++++++++ FILL ++++++++++" << std::endl;
	this -> _tree -> Fill();

      }

    }


}

bool Ntuplizer_noTagAndProbe::hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor) {

    const std::vector<std::string>& eventLabels = obj.filterLabels();
    for (const std::string& filter : filtersToLookFor)
    {
        //Looking for matching filters
        bool found = false;
        for (const std::string& label : eventLabels)
        {
            //if (label == std::string("hltOverlapFilterIsoMu17MediumIsoPFTau40Reg"))
            if (label == filter)
            {

                //std::cout << "#### FOUND FILTER " << label << " == " << filter << " ####" << std::endl;
                found = true;
            }
        }
        if(!found) return false;
    }

    return true;
}


#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(Ntuplizer_noTagAndProbe);

#endif //NTUPLIZER_NOTAGANDPROBE_H
