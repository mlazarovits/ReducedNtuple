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

	
	vector<TEfficiency*> effs;

	string gPathname = "/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/";

	TFile* file16 = TFile::Open((gPathname+"single_root_files/prod2016MC_reducedNANO_Triggers_DYinclusive.root").c_str());
	TFile* file17 = TFile::Open((gPathname+"single_root_files/prod2017MC_reducedNANO_Triggers_DYinclusive.root").c_str());
	TFile* f_wjets17 = TFile::Open((gPathname+"output/wjets17.root").c_str());
	// TTree* tree16 = (TTree*)file16->Get("Events");
	
	
	//DY incl. - 2016
	TriggerSet trigs16(file16);
	trigs16.SetSampleName("DYJetstoLL 2016");
	trigs16.AddTrigger("HLT_Ele27_WPTight_Gsf"); //isolated
	trigs16.AddTrigger("HLT_Ele25_eta2p1_WPTight_Gsf"); 
	// trigs16.AddTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
	// trigs16.AddTrigger("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
	// trigs16.AddTrigger("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL");
	trigs16.SetVar("Electron_pt");
	trigs16.SetOutputName("DYJets16_AllTrigs_ElepT.root");

	// effs = trigs16.Analyze();

	//DY incl. - 2017
	TriggerSet dytrigs17(file17);
	dytrigs17.SetSampleName("DYJetstoLL 2017");
	dytrigs17.AddTrigger("HLT_IsoMu24");
	dytrigs17.AddTrigger("HLT_Mu50");
	dytrigs17.AddTrigger("HLT_Mu55");
	dytrigs17.SetVar("Muon_pt");
	dytrigs17.SetOutputName("DYJets17_AllTrigs_MupT.root");

	//wjets incl. - 2017
	TriggerSet wjets17_trigs(f_wjets17);
	wjets17_trigs.SetSampleName("WJetsToLNu 2017");
	wjets17_trigs.AddTrigger("HLT_IsoMu24");
	wjets17_trigs.AddTrigger("HLT_Mu50");
	wjets17_trigs.AddTrigger("HLT_Mu55");
	wjets17_trigs.SetVar("Muon_pt");
	wjets17_trigs.SetOutputName("WJets17_AllTrigs_MupT_loose.root");


	string x_label = wjets17_trigs.GetVar();
	string title = wjets17_trigs.GetSampleName();
	effs = wjets17_trigs.Analyze();



	wjets17_trigs.makePlots(effs);





	
}