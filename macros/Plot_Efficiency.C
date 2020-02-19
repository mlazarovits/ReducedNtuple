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

void Plot_Efficiency(TString sampleName, TString physicsobj){
	if(gSystem->OpenDirectory("plots") == 0){
		gSystem->mkdir("plots");
		cout << "Created plots folder." << endl;
	}

	
	string gPathname = "/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/";
	TFile* f_wjets16 = NULL;	//TFile::Open((gPathname+"output/wjets16.root").c_str());
	TFile* f_wjets17 = TFile::Open((gPathname+"output/wjets17.root").c_str());
	TFile* f_wjets18 = NULL;	//TFile::Open((gPathname+"output/wjets18.root").c_str());
	TFile* f_dyjets17 = TFile::Open((gPathname+"output/dyjets17.root").c_str());
////////////////////////////////////WJETSTOLNU 2016 SINGLE MUON//////////////////////////////////////////////////////////////////
	//wjets incl. - 2016 muons
if(sampleName=="wjets16" && physicsobj=="Muon"){
	if(f_wjets16 == NULL) return;
	vector<TEfficiency*> wjets16_mu_effs;
	TriggerSet wjets16_mu(f_wjets16);
	wjets16_mu.SetSampleName("WJetsToLNu 2016 Loose ID");
	wjets16_mu.AddTrigger("HLT_IsoMu24");
	wjets16_mu.AddTrigger("HLT_IsoTkMu24");
	wjets16_mu.AddTrigger("HLT_Mu50");
	wjets16_mu.AddTrigger("HLT_TkMu50");
	wjets16_mu.SetVar("Muon_pt");
	wjets16_mu.SetOutputName("WJets16_AllTrigs_SingleMuon_loose.root");

	wjets16_mu_effs = wjets16_mu.Analyze();
	wjets16_mu.makePlots(wjets16_mu_effs);
}
// ////////////////////////////////////WJETSTOLNU 2016 SINGLE ELECTRON//////////////////////////////////////////////////////////////////
// 	//wjets incl. - 2016 electrons
else if(sampleName=="wjets16" && physicsobj=="Electron"){
	if(f_wjets16 == NULL) return;
	vector<TEfficiency*> wjets16_ele_effs;
	TriggerSet wjets16_ele(f_wjets16);
	wjets16_ele.SetSampleName("WJetsToLNu 2016 Loose ID");
	wjets16_ele.AddTrigger("HLT_Ele27_WPTight_Gsf");
	wjets16_ele.AddTrigger("HLT_Photon175");
	wjets16_ele.AddTrigger("HLT_Ele115_CaloIdVT_GsfTrkIdT");
	wjets16_ele.AddTrigger("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50");
	wjets16_ele.AddTrigger("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165");
	wjets16_ele.AddTrigger("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165");
	wjets16_ele.SetVar("Electron_pt");
	wjets16_ele.SetOutputName("WJets16_AllTrigs_SingleEle_loose.root");

	wjets16_ele_effs = wjets16_ele.Analyze();
	wjets16_ele.makePlots(wjets16_ele_effs);
}

////////////////////////////////////WJETSTOLNU 2017 SINGLE MUON//////////////////////////////////////////////////////////////////
////////////////////////////////////WJETSTOLNU 2017 SINGLE MUON//////////////////////////////////////////////////////////////////
	//wjets incl. - 2017 muons
else if(sampleName=="wjets17" && physicsobj=="Muon"){
	if(f_wjets17 == NULL) return;

	string var = "pt"; 

	vector<TEfficiency*> wjets17_mu_effs;
	TriggerSet wjets17_mu(f_wjets17);
	wjets17_mu.SetSampleName("WJetsToLNu 2017 Loose ID");

	// wjets17_mu.AddTrigger("HLT_IsoMu24");
	// wjets17_mu.AddTrigger("HLT_IsoMu27");
	// wjets17_mu.AddTrigger("HLT_OldMu100");
	// wjets17_mu.AddTrigger("HLT_TkMu100");
	// wjets17_mu.AddTrigger("HLT_Mu50");
	// wjets17_mu.AddTrigger("HLT_Mu55");

	wjets17_mu.AddTrigger("HLT_DoubleMu3_DZ_PFMET50_PFMHT60");
	wjets17_mu.AddTrigger("HLT_DoubleMu3_DZ_PFMET70_PFMHT70");
	wjets17_mu.AddTrigger("HLT_DoubleMu3_DZ_PFMET90_PFMHT90");
	wjets17_mu.SetVar("Muon_"+var);
	wjets17_mu.SetOutputName("WJets17_AllTrigs_SingleMuon_loose_"+var+"_ptcut125.root");

	wjets17_mu_effs = wjets17_mu.Analyze();
	wjets17_mu.makePlots(wjets17_mu_effs);
}

////////////////////////////////////WJETSTOLNU 2017 SINGLE ELECTRON//////////////////////////////////////////////////////////////////
	//wjets incl. - 2017 electrons
else if(sampleName=="wjets17" && physicsobj=="Electron"){
	if(f_wjets17 == NULL) return;

	vector<TEfficiency*> wjets17_ele_effs;
	TriggerSet wjets17_ele(f_wjets17);
	wjets17_ele.SetSampleName("WJetsToLNu 2017 Loose ID");
	wjets17_ele.AddTrigger("HLT_Ele32_WPTight_Gsf_L1DoubleEG"); //with HLT_Ele35_WPTight_Gsf_L1EGMT requirement
	wjets17_ele.AddTrigger("HLT_Ele35_WPTight_Gsf");
	wjets17_ele.AddTrigger("HLT_Photon200");
	wjets17_ele.AddTrigger("HLT_Ele115_CaloIdVT_GsfTrkIdT");
	wjets17_ele.AddTrigger("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165");
	wjets17_ele.SetVar("Electron_pt");
	wjets17_ele.SetOutputName("WJets17_AllTrigs_SingleEle_loose.root");

	wjets17_ele_effs = wjets17_ele.Analyze();
	wjets17_ele.makePlots(wjets17_ele_effs);
}


// ////////////////////////////////////WJETSTOLNU 2018 SINGLE MUON//////////////////////////////////////////////////////////////////
// ////////////////////////////////////WJETSTOLNU 2018 SINGLE MUON//////////////////////////////////////////////////////////////////
// 	//wjets incl. - 2018 muons
else if(sampleName=="wjets18" && physicsobj=="Muon"){
	if(f_wjets18 == NULL) return;

	vector<TEfficiency*> wjets18_mu_effs;
	TriggerSet wjets18_mu(f_wjets18);
	wjets18_mu.SetSampleName("WJetsToLNu 2018 Loose ID");
	wjets18_mu.AddTrigger("HLT_IsoMu24");
	wjets18_mu.AddTrigger("HLT_OldMu100");
	wjets18_mu.AddTrigger("HLT_TkMu100");
	wjets18_mu.AddTrigger("HLT_Mu50");
	wjets18_mu.AddTrigger("HLT_Mu55");
	wjets18_mu.SetVar("Muon_pt");
	wjets18_mu.SetOutputName("WJets18_AllTrigs_SingleMuon_loose.root");

	wjets18_mu_effs = wjets18_mu.Analyze();
	wjets18_mu.makePlots(wjets18_mu_effs);
}
// ////////////////////////////////////WJETSTOLNU 2018 SINGLE ELECTRON//////////////////////////////////////////////////////////////////
// 	//wjets incl. - 2018 electrons
else if(sampleName=="wjets18" && physicsobj=="Electron"){
	if(f_wjets18 == NULL) return;

	vector<TEfficiency*> wjets18_ele_effs;
	TriggerSet wjets18_ele(f_wjets18);
	wjets18_ele.SetSampleName("WJetsToLNu 2018 Loose ID");
	wjets18_ele.AddTrigger("HLT_Ele32_WPTight_Gsf");
	wjets18_ele.AddTrigger("HLT_Photon200");
	wjets18_ele.AddTrigger("HLT_Ele115_CaloIdVT_GsfTrkIdT");
	wjets18_ele.AddTrigger("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165");
	wjets18_ele.SetVar("Electron_pt");
	wjets18_ele.SetOutputName("WJets18_AllTrigs_SingleEle_loose.root");

	wjets18_ele_effs = wjets18_ele.Analyze();
	wjets18_ele.makePlots(wjets18_ele_effs);
}



// ////////////////////////////////////DYJETSTOLL 2017 DOUBLE MUON//////////////////////////////////////////////////////////////////
// ////////////////////////////////////DYJETSTOLL 2017 DOUBLE MUON//////////////////////////////////////////////////////////////////
else if(sampleName=="dyjets17" && physicsobj=="Muon"){
	if(f_dyjets17 == NULL) return;

	vector<TEfficiency*> dyjets17_mu_effs;
	TriggerSet dyjets17_mu(f_dyjets17);
	dyjets17_mu.SetSampleName("DY+JetstoLL 2017 No ID");

	dyjets17_mu.AddTrigger("HLT_DoubleMu3_DZ_PFMET50_PFMHT60");
	dyjets17_mu.AddTrigger("HLT_DoubleMu3_DZ_PFMET70_PFMHT70");
	dyjets17_mu.AddTrigger("HLT_DoubleMu3_DZ_PFMET90_PFMHT90");

	dyjets17_mu.SetVar("Muon_pt");
	dyjets17_mu.SetOutputName("DYJets17_DoubleMuMETTrigs_DoubleMu_METcut200.root");

	dyjets17_mu_effs = dyjets17_mu.Analyze();
	dyjets17_mu.makePlots(dyjets17_mu_effs);
}

else{
	cout << "Invalid sampleName and/or unrecognized phyiscs object" << endl;
	return;
}




	
}