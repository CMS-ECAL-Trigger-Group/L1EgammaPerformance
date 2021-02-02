#ifndef NTUPLIZER_H
#define NTUPLIZER_H

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
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "tParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"


//Set this variable to decide the number of triggers that you want to check simultaneously
#define NUMBER_OF_MAXIMUM_TRIGGERS 64


/*
   ??????????????????  ?????????????????????  ?????????????????? ??????       ???????????????  ??????????????????   ???????????????  ???????????????????????? ??????  ??????????????????  ?????????    ??????
   ??????   ?????? ??????      ??????      ??????      ??????   ?????? ??????   ?????? ??????   ??????    ??????    ?????? ??????    ?????? ????????????   ??????
   ??????   ?????? ???????????????   ??????      ??????      ????????????????????? ??????????????????  ?????????????????????    ??????    ?????? ??????    ?????? ?????? ??????  ??????
   ??????   ?????? ??????      ??????      ??????      ??????   ?????? ??????   ?????? ??????   ??????    ??????    ?????? ??????    ?????? ??????  ?????? ??????
   ??????????????????  ?????????????????????  ?????????????????? ????????????????????? ??????   ?????? ??????   ?????? ??????   ??????    ??????    ??????  ??????????????????  ??????   ????????????
   */

class Ntuplizer : public edm::EDAnalyzer {
	public:
		/// Constructor
		explicit Ntuplizer(const edm::ParameterSet&);
		/// Destructor
		virtual ~Ntuplizer();

	private:
		//----edm control---
		virtual void beginJob() ;
		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endJob();
		virtual void endRun(edm::Run const&, edm::EventSetup const&);
		void Initialize();
		bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);
		bool matchToTruth(const edm::Ptr<reco::GsfElectron> ele, 
				const edm::Handle<edm::View<reco::GenParticle>>  &genParticles);

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


		//////////////////// All Electrons ////////////////////////////////////
		std::vector<float> _allEl_Pt;
		std::vector<float> _allEl_Eta;
		std::vector<float> _allEl_Phi;
		std::vector<float> _allEl_SclEt;
		std::vector<float> _allEl_Charge;

                std::vector<float> _allL1tPt;
                std::vector<float> _allL1tEta;
                std::vector<float> _allL1tIso;
                std::vector<float> _allL1tPhi;
                std::vector<float> _allL1tQual;
 
                
		int _allEl_Size;

		/////////////////////////////////////////////////////////////////

 
                /////////////////////// Pantelis offline ID selections & DeltaR & SeedTowerEt & TowerHoE & iem & ihad //////////
                int _isProbeLoose;
                int _isProbeTight;
                int _isProbeMedium;

                float _Unpacked_dR;
                float _Emulated_dR;

                int _seedTowerEt;
                
                int _TowerHoE;     

                int _iem;
                int _ihad;

                int _shape;
                ////////////////////////////////////////////////////////////////

		float _eleProbePt;
		// std::vector<float> _eleProbePt; 
		float _eleProbeEta;
		// std::vector<float> _eleProbeEta;
		float _eleProbePhi;
		// std::vector<float> _eleProbePhi;
		float _eleProbeSclEt;
		//std::vector<float> _eleProbeSclEt;
		int _eleProbeCharge;
		//std::vector<float> _eleProbeCharge;
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
		Bool_t _isOS;
		int _foundTag;
		float _eleTagPt;
		float _eleTagEta;
		float _eleTagPhi;
		int _eleTagCharge;
		float _Mee;
		int _Nvtx;
                //float _dR_histo; //Charis test


		int _hasL1[100];
		int _hasL1_iso[100];

                ///////////////////////////////////////////////// Pantelis Emulator //////////////////////////////////////////////////
                int _hasL1Emu[100];
                int _hasL1Emu_iso[100];
                int _hasL1_looseiso[100];
                int _hasL1Emu_looseiso[100];
                int _hasL1_tightiso[100];
                int _hasL1Emu_tightiso[100];
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          
		edm::EDGetTokenT<edm::View<reco::GsfElectron> >  _electronsTag;
		edm::EDGetTokenT<edm::View<reco::GenParticle> > _genParticlesTag;
		edm::EDGetTokenT<edm::ValueMap<bool> > _eleLooseIdMapTag;
                //////////////////////////////////// Pantelis TightIDs //////////////////////////////////////////////////////////////
                edm::EDGetTokenT<edm::ValueMap<bool> > _eleTightIdMapTag;
                //edm::EDGetTokenT<edm::ValueMap<bool> > _eleMediumIdMapTag;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		edm::EDGetTokenT<edm::ValueMap<bool> > _eleMediumIdMapTag;
		edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _triggerObjects;
		edm::EDGetTokenT<edm::TriggerResults> _triggerBits;
		edm::EDGetTokenT<l1t::EGammaBxCollection> _L1EGTag  ;
		edm::EDGetTokenT<l1t::EGammaBxCollection> _L1EmuEGTag  ;
		edm::EDGetTokenT<std::vector<reco::Vertex>> _VtxTag;

		bool _useGenMatch;
		bool _useHLTMatch;

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
   ?????? ?????????    ????????? ??????????????????  ??????      ????????????????????? ?????????    ????????? ????????????????????? ?????????    ?????? ????????????????????????  ???????????????  ???????????????????????? ??????  ??????????????????  ?????????    ??????
   ?????? ????????????  ???????????? ??????   ?????? ??????      ??????      ????????????  ???????????? ??????      ????????????   ??????    ??????    ??????   ??????    ??????    ?????? ??????    ?????? ????????????   ??????
   ?????? ?????? ???????????? ?????? ??????????????????  ??????      ???????????????   ?????? ???????????? ?????? ???????????????   ?????? ??????  ??????    ??????    ?????????????????????    ??????    ?????? ??????    ?????? ?????? ??????  ??????
   ?????? ??????  ??????  ?????? ??????      ??????      ??????      ??????  ??????  ?????? ??????      ??????  ?????? ??????    ??????    ??????   ??????    ??????    ?????? ??????    ?????? ??????  ?????? ??????
   ?????? ??????      ?????? ??????      ????????????????????? ????????????????????? ??????      ?????? ????????????????????? ??????   ????????????    ??????    ??????   ??????    ??????    ??????  ??????????????????  ??????   ????????????
   */

// ----Constructor and Destructor -----
Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig) :
	_electronsTag       (consumes<edm::View<reco::GsfElectron> >                     (iConfig.getParameter<edm::InputTag>("electrons"))),
	_genParticlesTag (consumes<edm::View<reco::GenParticle> > (iConfig.getParameter<edm::InputTag>("genParticles"))),
	_eleLooseIdMapTag  (consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"))),
        /////////////////////////////// Pantelis TightIDs ////////////////////////////////////////////////////////////////////////////////
        _eleTightIdMapTag  (consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleTightIdMap"))),
        //_eleMediumIdMapTag  (consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"))),
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_eleMediumIdMapTag  (consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"))),
	_triggerObjects (consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerSet"))),
	_triggerBits    (consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("triggerResultsLabel"))),
	_L1EGTag       (consumes<l1t::EGammaBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1EG"))),
	_L1EmuEGTag    (consumes<l1t::EGammaBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1EmuEG"))),
	_VtxTag         (consumes<std::vector<reco::Vertex>>              (iConfig.getParameter<edm::InputTag>("Vertices")))
{
	this -> _treeName = iConfig.getParameter<std::string>("treeName");
	this -> _processName = iConfig.getParameter<edm::InputTag>("triggerResultsLabel");
	this -> _useGenMatch = iConfig.getParameter<bool>("useGenMatch");
	this -> _useHLTMatch = iConfig.getParameter<bool>("useHLTMatch");

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

Ntuplizer::~Ntuplizer()
{}

void Ntuplizer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
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

void Ntuplizer::Initialize() {
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
	this -> _l1tEmuTowerIEta = 666;
	this -> _l1tEmuTowerIPhi = 666;
	this -> _l1tEmuRawEt = -1;
	this -> _l1tEmuIsoEt = -1;
	this -> _foundTag = 0;	
        this -> _allL1tPt.clear();
        this -> _allL1tEta.clear();
        this -> _allL1tPhi.clear();
        this -> _allL1tIso.clear();         
        this -> _allL1tQual.clear();

	this -> _allEl_Size = -1;

        //////////////////////////////
        this -> _isProbeLoose = -1;
        this -> _isProbeTight = -1;
        this -> _isProbeMedium = -1;

        this -> _Unpacked_dR = -1;
        this -> _Emulated_dR = -1;

        this -> _seedTowerEt = -1;
      
        this ->_TowerHoE = -666;

        this -> _iem = -1;
        this -> _ihad = -1;

        this -> _shape = -2; 
        ////////////////////////////// 
        //this -> _dR_histo = 999.;

	//////////////////////////////////////////////

	for(unsigned int i=0;i<100;i++){
		this -> _hasL1[i] = -1;
		this -> _hasL1_iso[i] = -1;
	}

       ////////////////////// Pantelis Emulator /////////////////////////////
        for(unsigned int i=0;i<100;i++){
                this -> _hasL1Emu[i] = -1;
                this -> _hasL1Emu_iso[i] = -1;
                this -> _hasL1_looseiso[i] = -1;
                this -> _hasL1Emu_looseiso[i] = -1;
                this -> _hasL1_tightiso[i] = -1;
                this -> _hasL1Emu_tightiso[i] =-1;
                
        }
       /////////////////////////////////////////////////////////////////////

}


void Ntuplizer::beginJob()
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
        
        ////////////////////////////////// Pantelis offlineIDs Branches ///////////////////////////
        this -> _tree -> Branch("isProbeLoose", &_isProbeLoose, "isProbeLoose/I");
        this -> _tree -> Branch("isProbeTight", &_isProbeTight, "isProbeTight/I");
        this -> _tree -> Branch("isProbeMedium", &_isProbeMedium, "isProbeMedium/I");
        this -> _tree -> Branch("UnpackedDR", &_Unpacked_dR, "UnpackedDR/F");
        this -> _tree -> Branch("EmulatedDR", &_Emulated_dR, "EmulatedDR/F");
        this -> _tree -> Branch("seedTowerEt", &_seedTowerEt, "seedTowerEt/I");
        this -> _tree -> Branch("TowerHoE", &_TowerHoE,"TowerHoE/I");
        this -> _tree -> Branch("iem", &_iem,"iem/I");
        this -> _tree -> Branch("ihad", &_ihad,"ihad/I");
        this -> _tree -> Branch("shape", &_shape, "shape/I");
        ///////////////////////////////////////////////////////////////////////////////////////////  
         
	///////////////////////////////All Electrons////////////////////////////////////////////////
	this -> _tree -> Branch("allEl_Pt", &_allEl_Pt);//, "allElectonsPt/array");
	this -> _tree -> Branch("allEl_Eta", &_allEl_Eta);//, "allElectonsEta/array");
	this -> _tree -> Branch("allEl_Phi", &_allEl_Phi);//, "allElectonsPhi/array");
	this -> _tree -> Branch("allEl_SclEt", &_allEl_SclEt);//, "allElectonsSclEt/array");
	this -> _tree -> Branch("allEl_Charge", &_allEl_Charge);//, "allElectonsCharge/array");
	this -> _tree -> Branch("allEl_Size", &_allEl_Size, "allEl_Size/I");

        this -> _tree -> Branch("allL1tPt", &_allL1tPt);
        this -> _tree -> Branch("allL1tEta", &_allL1tEta);
        this -> _tree -> Branch("allL1tPhi", &_allL1tPhi);
        this -> _tree -> Branch("allL1tIso", &_allL1tIso);
        this -> _tree -> Branch("allL1tQual", &_allL1tQual);  
	///////////////////////////////////////////////////////////////////////////////////////

	this -> _tree -> Branch("isTagHLTmatched", &_isTagHLTmatched, "isTagHLTmatched/O");
	this -> _tree -> Branch("isProbeHLTmatched", &_isProbeHLTmatched, "isProbeHLTmatched/O");
	this -> _tree -> Branch("isOS", &_isOS, "isOS/O");
	this -> _tree -> Branch("foundTag", &_foundTag, "foundTag/I");
	this -> _tree -> Branch("Nvtx", &_Nvtx, "Nvtx/I");

        //this -> _tree -> Branch("dR_histo", &_dR_histo,"dR_histo/F"); //Charis test Dr



	for(unsigned int i=0;i<100;i++){  
		TString name = Form("hasL1_%i",i);
		this -> _tree -> Branch(name,  &_hasL1[i],  name+"/I");
		TString name_iso = Form("hasL1_iso_%i",i);
		this -> _tree -> Branch(name_iso,  &_hasL1_iso[i],  name_iso+"/I");
                TString name_looseiso = Form("hasL1_looseiso_%i",i);
                this -> _tree -> Branch(name_looseiso,  &_hasL1_looseiso[i],  name_looseiso+"/I");
                TString name_tightiso = Form("hasL1_tightiso_%i",i);
                this -> _tree -> Branch(name_tightiso,  &_hasL1_tightiso[i],  name_tightiso+"/I");


	}
        
        /////////////////////////////// Pantelis Emulator /////////////////////////
        for (unsigned int i=0;i<100;i++){
                TString name = Form("hasL1Emu_%i",i);
                this -> _tree -> Branch(name, &_hasL1Emu[i], name+"/I");
                TString name_iso = Form("hasL1Emu_iso%i",i);
                this -> _tree -> Branch(name_iso, &_hasL1Emu_iso[i], name_iso+"/I");
                TString name_looseiso = Form("hasL1Emu_looseiso%i",i);
                this -> _tree -> Branch(name_looseiso, &_hasL1Emu_looseiso[i], name_looseiso+"/I"); 
                TString name_tightiso = Form("hasL1Emu_tightiso%i",i);
                this -> _tree -> Branch(name_tightiso, &_hasL1Emu_tightiso[i], name_tightiso+"/I");
         }  
        
        //////////////////////////////////////////////////////////////////////////

	return;
}


void Ntuplizer::endJob()
{
	return;
}


void Ntuplizer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	return;
}


void Ntuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
	
        // search for the tag in the event
	edm::Handle<edm::View<reco::GsfElectron> > electrons;
	edm::Handle<edm::View<reco::GenParticle> > genParticles;
	edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
        ///////////////////////////// Pantelis TightIDs /////////////////////////////////////////////////////////////////////////////////
        edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
        //edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
	edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
	edm::Handle<edm::TriggerResults> triggerBits;
	edm::Handle<std::vector<reco::Vertex> >  vertices;

	iEvent.getByToken(this -> _electronsTag, electrons);
	iEvent.getByToken(this -> _eleLooseIdMapTag, loose_id_decisions);
        /////////////////////////////// Pantelis TightIDs ////////////////////////////////////////////////////////////////////////////////
        iEvent.getByToken(this -> _eleTightIdMapTag, tight_id_decisions); 
        iEvent.getByToken(this -> _eleMediumIdMapTag, medium_id_decisions);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	iEvent.getByToken(this -> _eleMediumIdMapTag, medium_id_decisions);
	if(this->_useHLTMatch)
		iEvent.getByToken(this -> _triggerObjects, triggerObjects);
	iEvent.getByToken(this -> _triggerBits, triggerBits);
	iEvent.getByToken(this -> _VtxTag,vertices);

	if(this->_useGenMatch)
		iEvent.getByToken(this -> _genParticlesTag, genParticles);


	const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

	////////////////// All Electrons /////////////////////////////////////////////////////////   

	this -> _allEl_Pt.clear();
	this -> _allEl_Eta.clear();
	this -> _allEl_Phi.clear();
	this -> _allEl_SclEt.clear();
	this -> _allEl_Charge.clear();

	this -> _allEl_Size=electrons->size();      


	for(unsigned int k=0; k<electrons->size(); ++k){
		const auto ele = electrons->ptrAt(k);
		this->_allEl_Pt.push_back(ele->pt());
		this->_allEl_Eta.push_back(ele->eta());
		this->_allEl_Phi.push_back(ele->phi());
		this->_allEl_SclEt.push_back((ele->superCluster()->energy()) / cosh(ele->superCluster()->eta()));
		this->_allEl_Charge.push_back(ele->charge());
	}
	//////////////////////////////////////////////////////////////////////////////////////
	for (unsigned int i = 0; i< electrons->size(); ++i){


		const auto eleTag = electrons->ptrAt(i);
		int isTagIDMedium = (*medium_id_decisions)[eleTag];
		if(!isTagIDMedium || eleTag->p4().Pt()<30) continue;


		for (unsigned int j = 0; j< electrons->size(); ++j){

			if(i==j) continue;	
                                               
                        this -> Initialize();
                        _indexevents = iEvent.id().event();
                        _runNumber = iEvent.id().run();
                        _lumi = iEvent.luminosityBlock();
  
            
			const auto eleProbe = electrons->ptrAt(j);
			//int isProbeLoose = (*loose_id_decisions)[eleProbe];
                        
                        //////////////////////// Pantelis ///////////////////
                        
                       //cout<<"eleProbe->SuperCluster()->eta(): "<<eleProbe->superCluster()->eta()<<endl;
                       // cout<<"eleProbe->SuperCluster()->phi(): "<<eleProbe->superCluster()->phi()<<endl; 
                         
                        int isProbeLoose2 = (*loose_id_decisions)[eleProbe];
                        int isProbeTight = (*tight_id_decisions)[eleProbe];
                        int isProbeMedium =(*medium_id_decisions)[eleProbe];
                        this -> _isProbeLoose = isProbeLoose2;
                        this -> _isProbeTight = isProbeTight;
                        this -> _isProbeMedium = isProbeMedium;
                        ////////////////////////////////////////////////////

                        //cout<< "isProbeLoose2: "<< isProbeLoose2<<endl;
                        //cout<< "isProbeMedium: "<< isProbeMedium<<endl;

			float eleProbeEta = eleProbe->p4().Eta();
	                if((abs(eleProbeEta)>1.4442 && abs(eleProbeEta)<1.566)) continue;

			bool isOS = (eleTag->charge() / eleProbe->charge() < 0) ? true : false;
			if(!isOS) continue;

			float Mee = (eleTag->p4() + eleProbe->p4()).M();
			if(!(Mee>60 && Mee<120)) continue;

			if(this->_useGenMatch){
				if(!matchToTruth(eleProbe,genParticles))
					continue;
			}


			this -> _isOS = isOS;
			this -> _Mee = Mee;

			//! TagAndProbe on HLT eles

			this -> _eleProbeTriggerBitSet.reset();
			this -> _eleTagTriggerBitSet.reset();

			if(_useHLTMatch){

				for (pat::TriggerObjectStandAlone  obj : *triggerObjects)
				{

					if(!obj.hasCollection("hltEgammaCandidates::HLT")) continue;

					const float dR_tag = deltaR (*eleTag, obj);
					if ( dR_tag < 0.3)
					{		  

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
							this -> _isTagHLTmatched = true;
							this -> _foundTag++;
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
								const std::vector<std::string>& filters = (parameter.hltFilters1);
								if (this -> hasFilters(obj, filters))
								{
									//std::cout << "#### FOUND ELE WITH HLT PATH " << x << " ####" << std::endl;
									this -> _hltPt = obj.pt();
									this -> _hltEta = obj.eta();
									this -> _hltPhi = obj.phi();
									this -> _eleProbeTriggerBitSet[x] = true;
								}
							}
							x++;
						}
						if (foundTrigger) this -> _isProbeHLTmatched = true;
					}

				}

				if(!(this -> _isTagHLTmatched)) continue;

			}      

			//! TagAndProbe on L1T EG

			edm::Handle< BXVector<l1t::EGamma> >  L1EGHandle;
			iEvent.getByToken(_L1EGTag, L1EGHandle);

			float minDR = 0.3; //Uncomment for new match algo  //Charis test
      
                        //float minDR = 999.; //Uncomment for new match algo

                        this -> _allL1tPt.clear();
                        this -> _allL1tEta.clear();
                        this -> _allL1tPhi.clear();
                        this -> _allL1tIso.clear();
                        this -> _allL1tQual.clear();

                        ///////////////////////////// All Electrons ////////////////////////////////////////////////////
			for (l1t::EGammaBxCollection::const_iterator bx0EGIt = L1EGHandle->begin(0); bx0EGIt != L1EGHandle->end(0) ; bx0EGIt++)
			{    
                             const l1t::EGamma& l1tEG= *bx0EGIt;                            

                             this -> _allL1tPt.push_back(l1tEG.pt());
                             this -> _allL1tEta.push_back(l1tEG.eta());
                             this -> _allL1tPhi.push_back(l1tEG.phi());
                             this -> _allL1tIso.push_back(l1tEG.hwIso());
                             this -> _allL1tQual.push_back(l1tEG.hwQual());

                        }
                        ////////////////////////////////////////////////////////////////////////////////////////////////


			for (l1t::EGammaBxCollection::const_iterator bx0EGIt = L1EGHandle->begin(0); bx0EGIt != L1EGHandle->end(0) ; bx0EGIt++)
			{
				const float dR = deltaR(*eleProbe, *bx0EGIt);
                                _Unpacked_dR = dR;
                             
				const l1t::EGamma& l1tEG = *bx0EGIt;

				//cout<<"FW EG, pT = "<<l1tEG.pt()<<", eta = "<<l1tEG.eta()<<", phi = "<<l1tEG.phi()<<endl;

				if (dR < minDR) //Uncomment for new match algo
				{

					minDR = dR; //Uncomment for new match algo
					this -> _l1tPt = l1tEG.pt();
					this -> _l1tEta = l1tEG.eta();
					this -> _l1tPhi = l1tEG.phi();
					this -> _l1tIso = l1tEG.hwIso();
					this -> _l1tQual = l1tEG.hwQual();
				}

                                //this -> _dR_histo = minDR; //Charis test 

			}

			for(unsigned int i=0;i<100;i++){
				this -> _hasL1[i] = (this -> _l1tPt)>=i;
				this -> _hasL1_iso[i] = ((this -> _l1tIso) && (this -> _l1tPt)>=i);
                                this -> _hasL1_looseiso[i] = (((this -> _l1tIso)==2 || (this -> _l1tIso)==3) && (this -> _l1tPt)>=i);
                                this -> _hasL1_tightiso[i] = (((this -> _l1tIso)==1 || (this -> _l1tIso)==3) && (this -> _l1tPt)>=i);

			}

			edm::Handle< BXVector<l1t::EGamma> >  L1EmuEGHandle;
			try {iEvent.getByToken(_L1EmuEGTag, L1EmuEGHandle);} catch (...) {;}

			if (L1EmuEGHandle.isValid())
			{
				minDR = 0.3;

				for (l1t::EGammaBxCollection::const_iterator bx0EmuEGIt = L1EmuEGHandle->begin(0); bx0EmuEGIt != L1EmuEGHandle->end(0) ; bx0EmuEGIt++)
				{
					const float dR = deltaR(*eleProbe, *bx0EmuEGIt);
                                        _Emulated_dR = dR;
					const l1t::EGamma& l1tEmuEG = *bx0EmuEGIt;
                  
                                          
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
                                                //this -> _seedTowerEt     = l1tEmuEG.seedTowerEt(); 
 						this -> _TowerHoE        = l1tEmuEG.towerHoE();  
						//this -> _iem             = l1tEmuEG.seedTowerEm();
                                                //this -> _ihad            = l1tEmuEG.seedTowerHad();
                                                this -> _shape           = l1tEmuEG.shape();
					}
				}
                      
                          ///////////////////////// Pantelis Emulator ////////////////////////////////////////
                          for(unsigned int i=0;i<100;i++){
                                  this -> _hasL1Emu[i] = (this -> _l1tEmuPt)>=i;
                                  this -> _hasL1Emu_iso[i] = ((this -> _l1tEmuIso) && ( this -> _l1tEmuPt)>=i);
                                  this -> _hasL1Emu_looseiso[i] = (((this -> _l1tEmuIso)==2 || (this -> _l1tEmuIso)==3) && (this -> _l1tEmuPt)>=i);
                                  this -> _hasL1Emu_tightiso[i] = (((this -> _l1tEmuIso)==1 || (this -> _l1tEmuIso)==3) && (this -> _l1tEmuPt)>=i);

                          } 
                          ////////////////////////////////////////////////////////////////////////////////////
                        
			}

			this -> _eleProbePt = eleProbe->pt();
			this -> _eleProbeEta = eleProbe->eta();
			this -> _eleProbePhi = eleProbe->phi();
			this -> _eleProbeSclEt = (eleProbe->superCluster()->energy()) / cosh(eleProbe->superCluster()->eta()) ;
			this -> _eleProbeCharge = eleProbe->charge();


			this -> _eleTagPt = eleTag->pt();
			this -> _eleTagEta = eleTag->eta();
			this -> _eleTagPhi = eleTag->phi();
			this -> _eleTagCharge = eleTag->charge();

			this -> _Nvtx = vertices->size();


			this -> _eleProbeTriggerBits = this -> _eleProbeTriggerBitSet.to_ulong();
			this -> _eleTagTriggerBits = this -> _eleTagTriggerBitSet.to_ulong();
			//std::cout << "++++++++++ FILL ++++++++++" << std::endl;
			this -> _tree -> Fill();

		}

	}



}


bool Ntuplizer::hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor) {

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


bool Ntuplizer::matchToTruth(const edm::Ptr<reco::GsfElectron> ele, 
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
		double dRtmp = deltaR( ele->p4(), particle->p4() );
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
DEFINE_FWK_MODULE(Ntuplizer);

#endif //NTUPLIZER_H
