#include <iostream>

#include "../include/prod2016MC_reducedNANO_Triggers.h"
#include "../include/prod2017MC_reducedNANO_Triggers.h"
#include "../include/prod2018MC_reducedNANO_Triggers.h"
#include "../include/TriggerSet.hh"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TGraph.h"


using namespace std;

void Plot_Efficiency(){
	if(gSystem->OpenDirectory("plots") == 0){
		gSystem->mkdir("plots");
		cout << "Created plots folder." << endl;
	}

	
	

	string gPathname = "/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/";

	TFile* file16 = TFile::Open((gPathname+"single_root_files/prod2016MC_reducedNANO_Triggers_DYinclusive.root").c_str());
	TFile* file17 = TFile::Open((gPathname+"single_root_files/prod2017MC_reducedNANO_Triggers_DYinclusive.root").c_str());
	TFile* f_wjets17 = TFile::Open((gPathname+"output/wjets17.root").c_str());
	// TTree* tree16 = (TTree*)file16->Get("Events");
	

	//wjets incl. - 2017 muons
	vector<TEfficiency*> wjets17_mu_effs;
	TriggerSet wjets17_mu(f_wjets17);
	wjets17_mu.SetSampleName("WJetsToLNu 2017");
	wjets17_mu.AddTrigger("HLT_IsoMu24");
	wjets17_mu.AddTrigger("HLT_IsoMu27");
	wjets17_mu.AddTrigger("HLT_OldMu100");
	wjets17_mu.AddTrigger("HLT_TkMu100");
	wjets17_mu.AddTrigger("HLT_Mu50");
	wjets17_mu.AddTrigger("HLT_Mu55");
	wjets17_mu.SetVar("Muon_pt");
	wjets17_mu.SetOutputName("WJets17_AllTrigs_MupT_loose.root");

	wjets17_mu_effs = wjets17_mu.Analyze();
	wjets17_mu.makePlots(wjets17_mu_effs);



	//wjets incl. - 2017 electrons
	// TriggerSet wjets17_ele(f_wjets17);
	// wjets17_ele.SetSampleName("WJetsToLNu 2017");
	// wjets17_ele.AddTrigger("HLT_IsoMu24");
	// wjets17_ele.AddTrigger("HLT_IsoMu27");
	// wjets17_ele.AddTrigger("HLT_OldMu100");
	// wjets17_ele.AddTrigger("HLT_TkMu100");
	// wjets17_ele.AddTrigger("HLT_Mu50");
	// wjets17_ele.AddTrigger("HLT_Mu55");
	// wjets17_ele.SetVar("Muon_pt");
	// wjets17_ele.SetOutputName("WJets17_AllTrigs_ElepT_loose.root");

	// wjets17_ele_effs = wjets17_ele.Analyze();
	// wjets17_ele.makePlots(wjets17_ele_effs);





	
}