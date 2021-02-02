/**
 *  @file  TurnonFit.cpp
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date	05/10/2014
 *
 *  @internal
 *	 Created :  05/10/2014
 * Last update :  05/10/2014 21:03:01
 *		  by :  JB Sauvan
 *
 * =====================================================================================
 */


#include "TurnonFit.h"

#include <sstream>
#include <fstream>	  // std::filebuf

#include "TCanvas.h"
#include "TH1.h"
#include "TAxis.h"
#include "TROOT.h"

#include "RooCategory.h"
#include "RooEfficiency.h"
#include "RooDataSet.h"
#include "RooBinning.h"
#include "RooChi2Var.h"

using namespace std;
using namespace RooFit;


/*****************************************************************/
TurnonFit::TurnonFit(const std::string& name):m_name(name),
	m_xVar		("xVar","p_{T}",20.,0.,150.),
	m_max	 	("max","max",1.0,0.9,1.),
	m_alpha   	("alpha","#alpha",3.,0.01,50.),
	m_n	   	    ("n","n",10.,1.001,50.),
	m_mean		("mean","mean",	20.,0.,50.),
	m_sigma   	("sigma","#sigma",2.,0.01,10.)
/*****************************************************************/
{
	stringstream sxvar, smax, salpha, sn, smean, ssigma;
	sxvar  << "xVar_"  << m_name;
	smax   << "max_"   << m_name;
	salpha << "alpha_" << m_name;
	sn     << "n_"     << m_name;
	smean  << "mean_"  << m_name;
	ssigma << "sigma_" << m_name;
	m_xVar .SetName(sxvar.str().c_str());
	m_max  .SetName(smax.str().c_str());
	m_alpha.SetName(salpha.str().c_str());
	m_n    .SetName(sn.str().c_str());
	m_mean .SetName(smean.str().c_str());
	m_sigma.SetName(ssigma.str().c_str());
}


/*****************************************************************/
TurnonFit::~TurnonFit()
/*****************************************************************/
{
	//m_function->Delete();
	//m_fitResult->Delete();
	//m_plot->Delete();
}



/*****************************************************************/
void TurnonFit::setCrystalBall(double max, double max0, double max1,
		double alpha, double alpha0, double alpha1,
		double n, double n0, double n1,
		double mean, double mean0, double mean1, 
		double sigma, double sigma0, double sigma1)
/*****************************************************************/
{
	m_max.setVal(max);
	m_max.setRange(max0, max1);
	m_alpha.setVal(alpha);
	m_alpha.setRange(alpha0, alpha1);
	m_n.setVal(n);
	m_n.setRange(n0, n1);
	m_mean.setVal(mean);
	m_mean.setRange(mean0, mean1);
	m_sigma.setVal(sigma);
	m_sigma.setRange(sigma0, sigma1);

	stringstream cbName;
	cbName << "cb_" << m_name;
	m_function = new FuncCB(cbName.str().c_str(), cbName.str().c_str(), m_xVar, m_mean, m_sigma, m_alpha, m_n, m_max) ;
}



/*****************************************************************/
void TurnonFit::fit()
/*****************************************************************/
{

	RooTrace::active(1);

	printParameters();

	TFile* file = TFile::Open(m_fileName.c_str());
	TTree* tree = (TTree*)file->Get(m_treeName.c_str());
	// Define cut used for efficiency calculation
	RooCategory cut(m_cut.c_str(), m_cut.c_str()) ;
	cut.defineType("accept",1) ;
	cut.defineType("reject",0) ;
	RooEfficiency eff("eff","efficiency", *m_function, cut, "accept");

	// create dataset. In case of subset selection, add needed variables in the ArgSet
	RooDataSet* dataSet;
	RooArgSet argSet(m_xVar,  cut);
	vector<RooRealVar> selectionVars;
	vector<RooRealVar> weightVars;

	//m_selection = "tauPt>250";

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////

	RooRealVar rv1("l1tPt","l1tPt",0.);
	RooRealVar rv2("hasL1_tightiso_32","hasL1_tightiso_32",0.);
	RooRealVar rv3("isProbeLoose","isProbeLoose",0.);
	RooRealVar rv4("hasL1_tightiso_38","hasL1_tightiso_38",0.);
	RooRealVar rv5("eleTagEta","eleTagEta",0.);
	RooRealVar rv6("hasL1_30","hasL1_30",0.);
	RooRealVar rv7("eleTagPhi","eleTagPhi",0.);
	RooRealVar rv8("eleProbePhi","eleProbePhi",0.);
	RooRealVar rv9("hasL1_tightiso_30","hasL1_tightiso_30",0.);
	RooRealVar rv10("hasL1_tightiso_22","hasL1_tightiso_22",0.);
	RooRealVar rv11("l1tEta","l1tEta",0.);
	RooRealVar rv12("eleProbeEta","eleProbeEta",0.);
	RooRealVar rv13("hasL1_looseiso_22","hasL1_looseiso_22",0.);
	RooRealVar rv14("hasL1_32","hasL1_32",0.);
	//RooRealVar rv15("hasL1_tightiso_32","hasL1_tightiso_32",0.);
	RooRealVar rv16("hasL1_tightiso_34","hasL1_tightiso_34",0.);
	RooRealVar rv17("hasL1_tightiso_22","hasL1_tightiso_22",0.);
	RooRealVar rv18("hasL1_looseiso_24","hasL1_looseiso_24",0.);
	RooRealVar rv19("hasL1_looseiso_26","hasL1_looseiso_26",0.);
	RooRealVar rv20("hasL1_tightiso_28","hasL1_tightiso_28",0.);
	RooRealVar rv21("hasL1_0","hasL1_0",0.);
	RooRealVar rv22("RunNumber","RunNumber",0.);
	RooRealVar rv23("hasL1_34","hasL1_34",0.);
	RooRealVar rv24("hasL1_tightiso_26","hasL1_tightiso_26",0.);

	
//	argSet.add(rv1);
//	argSet.add(rv2);   
	argSet.add(rv3);
//	argSet.add(rv4);
	argSet.add(rv5);
//	argSet.add(rv6);
	argSet.add(rv7);
	argSet.add(rv8);
//	argSet.add(rv9);
//	argSet.add(rv10);
//	argSet.add(rv11);
//	argSet.add(rv12);
//  argSet.add(rv13);
//  argSet.add(rv14);
//	argSet.add(rv15);
//	argSet.add(rv16);
//	argSet.add(rv17);
//	argSet.add(rv18);
//	argSet.add(rv19);
//	argSet.add(rv20);
//	argSet.add(rv21);
//	argSet.add(rv22); 
//	argSet.add(rv23);
//	argSet.add(rv24);

	argSet.Print();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(m_selection=="")
	{
		if (m_weightVar==""){
			dataSet = new RooDataSet("data", "data", argSet, Import(*tree));
	  	}
		else
		{
	 		weightVars.push_back(RooRealVar(m_weightVar.c_str(), m_weightVar.c_str(), 0.));
	 		argSet.add(weightVars.back());
			dataSet = new RooDataSet("data", "data", argSet, Import(*tree), WeightVar(m_weightVar.c_str()));   
		}
	}
	else 
	{
		for(unsigned i=0;i<m_selectionVars.size();i++)
		{
			selectionVars.push_back( RooRealVar(m_selectionVars[i].c_str(), m_selectionVars[i].c_str(), 0.) );
			argSet.add(selectionVars.back());
		}
		if (m_weightVar=="") {
			dataSet = new RooDataSet("data", "data", argSet, Import(*tree), Cut(m_selection.c_str()));
		}
		else
		{
			weightVars.push_back(RooRealVar(m_weightVar.c_str(), m_weightVar.c_str(), 0.));
			argSet.add(weightVars.back());
			dataSet = new RooDataSet("data", "data", argSet, Import(*tree), Cut(m_selection.c_str()), WeightVar(m_weightVar.c_str()));			   
			//cout<<"flag2"<<endl;
		}
	}
	std::filebuf fb;
	fb.open ("test.txt",std::ios::out);
	std::ostream os(&fb);
	dataSet->printValue(os);

	// Create binned turn-on
	int nbins = m_binning.size()-1;	
	RooBinning binning = RooBinning(nbins, &m_binning[0], "binning");
	gROOT->cd(); // change current directory. Otherwise, m_plot is associated to "file", and file->Close() destroys m_plot
	m_plot = m_xVar.frame(Bins(18000),Title("")) ;
	stringstream plotName;
	plotName << "plot_" << m_name;
	m_plot->SetName(plotName.str().c_str());
	dataSet->plotOn(m_plot, DataError(RooAbsData::Poisson), Binning(binning), Efficiency(cut), MarkerColor(kBlack), LineColor(kBlack), MarkerStyle(20));

	// fit functional form to unbinned dataset
	//if(!m_noFit) m_fitResult = eff.fitTo(*dataSet,ConditionalObservables(m_xVar),Minos(kTRUE),Warnings(kFALSE),NumCPU(m_nCPU),Save(kTRUE),Verbose(kFALSE));
	
	if(!m_noFit)
	{
	    m_fitResult = eff.fitTo(*dataSet,ConditionalObservables(m_xVar),Minos(kFALSE),Warnings(kFALSE),NumCPU(m_nCPU),Save(kTRUE),SumW2Error(kTRUE),Range(m_fitrange[0],m_fitrange[1]));
		stringstream resultName;
		resultName << "fitResult_" << m_name;
		m_fitResult->SetName(resultName.str().c_str());
	}

	// m_function->plotOn(m_plot,VisualizeError(*m_fitResult,1),FillColor(kOrange),LineColor(kRed),LineWidth(2));
	m_function->plotOn(m_plot,LineColor(kRed),LineWidth(2));
	printParameters();

	m_plot->GetYaxis()->SetRangeUser(0,1.05);
	m_plot->GetXaxis()->SetRangeUser(m_xVar.getMin(),m_xVar.getMax());
	//cout<<"m_xVar.getMax() = "<<m_xVar.getMax()<<endl;

	m_histo = (RooHist*)m_plot->getObject(0);

	for (int ipt = 0; ipt < m_histo->GetN(); ++ipt)
	{
		double x,y;
		m_histo->GetPoint(ipt,x,y);
		cout<<"flag3"<<endl;
		cout<<"x = "<<x<<", y = "<<y<<", error = "<<m_histo->GetErrorYlow(ipt)<<endl;
		if (y > 1)
		{
			m_histo->SetPoint(ipt,x,1.);
			m_histo->SetPointEYhigh(ipt, 0.);
			cout << "** WARNING: turnOn " << m_name << " , efficiency exceeds 1 in bin " << ipt << " forcign value to 1" << endl;
		}   
	}

	m_fit  = (RooCurve*)m_plot->getObject(1);
	stringstream histoName, fitName;
	histoName << "histo_" << m_name;
	fitName << "fit_" << m_name;
	m_histo->SetName(histoName.str().c_str());
	m_fit->SetName(fitName.str().c_str());

	file->Close();
	dataSet->Delete();

	printParameters();
	RooTrace::dump();
	
}



/*****************************************************************/
void TurnonFit::save(TFile* outputFile)
/*****************************************************************/
{
	outputFile->cd();
	stringstream cName;
	cName << "canvas_" << m_name;
	TCanvas* canvas = new TCanvas(cName.str().c_str(), cName.str().c_str(), 800, 800);
	canvas->SetGrid();
	TH1F* dummy = new TH1F("test","test",300,0.,300.);
	dummy->GetXaxis()->SetRangeUser(0.,300.);
	dummy->GetXaxis()->SetTitle("p_{T}^{offl.} [GeV]");
	dummy->GetXaxis()->SetTitleOffset(1.3);
	dummy->GetYaxis()->SetTitle("L1 Efficiency");
	dummy->GetYaxis()->SetTitleOffset(1.3);
	dummy->SetTitle("");
	dummy->SetStats(0);
	dummy->Draw();
	m_plot->Draw("same");
	// m_plot->Draw();
	canvas->Write();
	m_histo->Write();
	m_fit->Write();
	m_function->Write();
	if(!m_noFit) m_fitResult->Write();
}


/*****************************************************************/
void TurnonFit::printParameters()
/*****************************************************************/
{
	cout<<"\n\n";
	cout<<"  Turnon "<<m_name<<" parameters:\n";
	cout<<"  File	 : "<<m_fileName<<"\n";
	cout<<"  Tree	 : "<<m_treeName<<"\n";
	cout<<"  XVar	 : "<<m_xVar.GetName()<<"\n";
	cout<<"  Cut	  : "<<m_cut<<"\n";
	cout<<"  Selection: "<<m_selection<<"\n";
	cout<<"  WeightVar: "<<m_weightVar<<"\n";
	cout<<"  CB	   :\n";
	cout<<"	Max  : "<<m_max.getVal()  <<" ["<<m_max.getMin()  <<", "<<m_max.getMax()<<"]\n";
	cout<<"	Alpha: "<<m_alpha.getVal()<<" ["<<m_alpha.getMin()<<", "<<m_alpha.getMax()<<"]\n";
	cout<<"	n	: "<<m_n.getVal()	<<" ["<<m_n.getMin()	<<", "<<m_n.getMax()<<"]\n";
	cout<<"	mean : "<<m_mean.getVal() <<" ["<<m_mean.getMin() <<", "<<m_mean.getMax()<<"]\n";
	cout<<"	sigma: "<<m_sigma.getVal()<<" ["<<m_sigma.getMin()<<", "<<m_sigma.getMax()<<"]\n";
	cout<<"\n\n";
}

