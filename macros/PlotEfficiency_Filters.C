#include <iostream>

#include "../include/prod2016MC_reducedNANO_EventFilters.h"
#include "../include/prod2017MC_reducedNANO_EventFilters.h"
#include "../include/prod2018MC_reducedNANO_EventFilters.h"
#include "../include/TriggerSet.hh"

#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TGraph.h"


using namespace std;

void PlotEfficiency_Filters(TString sampleName){
	if(gSystem->OpenDirectory("plots") == 0){
		gSystem->mkdir("plots");
		cout << "Created plots folder." << endl;
	}

	
	string gPathname = "/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/";
	TFile* f_wjets16 = TFile::Open((gPathname+"output/Summer16_94X_QCD_EventFilters.root").c_str());
	TFile* f_wjets17 = TFile::Open((gPathname+"output/Fall17_94X_QCD_EventFilters.root").c_str());
	TFile* f_wjets18 = TFile::Open((gPathname+"output/Autumn18_102X_WJetsLNu_EventFilters.root").c_str());

	TFile* f_QCD16 = TFile::Open((gPathname+"output/Summer16_94X_QCD_EventFilters.root").c_str());
	TFile* f_QCD17 = TFile::Open((gPathname+"output/Fall17_94X_QCD_EventFilters..root").c_str());
	TFile* f_QCD18 = NULL; //TFile::Open((gPathname+".root").c_str());

if(sampleName=="wjets"){
	if(f_wjets16 == NULL) return;
	string name = "WJets16_AllFilters_loose";
	TriggerSet wjets16(f_wjets16);
	wjets16.SetSampleName(name);

	wjets16.AddTrigger("Flag_HBHENoiseFilter");
	wjets16.AddTrigger("Flag_HBHENoiseIsoFilter");
	wjets16.AddTrigger("Flag_globalSuperTightHalo2016Filter");
	wjets16.AddTrigger("Flag_EcalDeadCellTriggerPrimitiveFilter");
	wjets16.AddTrigger("Flag_goodVertices");
	wjets16.AddTrigger("Flag_eeBadScFilter");
	wjets16.AddTrigger("Flag_BadPFMuonFilter");

	wjets16.SetVar("MET_pt");
	wjets16.SetOutputName(name+".root");

	vector<TEfficiency*> wjets16_effs = wjets16.Analyze();
	wjets16.makePlots(wjets16_effs);
}


else if(sampleName=="wjets17"){
	if(f_wjets17 == NULL) return;
	string name = "WJets17_AllFilters_loose";
	TriggerSet wjets17(f_wjets17);
	wjets17.SetSampleName(name);

	wjets17.AddTrigger("Flag_HBHENoiseFilter");
	wjets17.AddTrigger("Flag_HBHENoiseIsoFilter");
	wjets17.AddTrigger("Flag_globalSuperTightHalo2016Filter");
	wjets17.AddTrigger("Flag_EcalDeadCellTriggerPrimitiveFilter");
	wjets17.AddTrigger("Flag_goodVertices");
	wjets17.AddTrigger("Flag_eeBadScFilter");
	wjets17.AddTrigger("Flag_BadChargedCandidateFilter");
	wjets17.AddTrigger("Flag_BadPFMuonFilter");

	wjets17.SetVar("METFixEE2017_pt");
	wjets17.SetOutputName(name+".root");

	vector<TEfficiency*> wjets17_effs = wjets17.Analyze();
	wjets17.makePlots(wjets17_effs);
}


else if(sampleName=="wjets18"){
	if(f_wjets18 == NULL) return;
	string name = "WJets18_AllFilters_loose";
	TriggerSet wjets18(f_wjets18);
	wjets18.SetSampleName(name);

	wjets18.AddTrigger("Flag_HBHENoiseFilter");
	wjets18.AddTrigger("Flag_HBHENoiseIsoFilter");
	wjets18.AddTrigger("Flag_globalSuperTightHalo2016Filter");
	wjets18.AddTrigger("Flag_EcalDeadCellTriggerPrimitiveFilter");
	wjets18.AddTrigger("Flag_goodVertices");
	wjets18.AddTrigger("Flag_eeBadScFilter");
	wjets18.AddTrigger("Flag_BadChargedCandidateFilter");
	wjets18.AddTrigger("Flag_BadPFMuonFilter");

	wjets18.SetVar("MET_pt");
	wjets18.SetOutputName(name+".root");

	vector<TEfficiency*> wjets18_effs = wjets18.Analyze();
	wjets18.makePlots(wjets18_effs);
}

else if(sampleName=="QCD16"){
	if(f_QCD16 == NULL) return;
	string name = "QCD16_AllFilters_loose";
	TriggerSet QCD16(f_QCD16);
	QCD16.SetSampleName(name);

	QCD16.AddTrigger("Flag_");

	QCD16.SetVar("MET_pt");
	QCD16.SetOutputName(name+".root");

	vector<TEfficiency*> QCD16_effs = QCD16.Analyze();
	QCD16.makePlots(QCD16_effs);
}
	


else if(sampleName=="QCD17"){
	if(f_QCD17 == NULL) return;
	string name = "QCD17_AllFilters_loose";
	TriggerSet QCD17(f_QCD17);
	QCD17.SetSampleName(name);

	QCD17.AddTrigger("Flag_");

	QCD17.SetVar("MET_pt");
	QCD17.SetOutputName(name+".root");

	vector<TEfficiency*> QCD17_effs = QCD17.Analyze();
	QCD17.makePlots(QCD17_effs);
}




else if(sampleName=="QCD18"){
	if(f_QCD18 == NULL) return;
	string name = "QCD18_AllFilters_loose";
	TriggerSet QCD18(f_QCD18);
	QCD18.SetSampleName(name);

	QCD18.AddTrigger("Flag_");

	QCD18.SetVar("MET_pt");
	QCD18.SetOutputName(name+".root");

	vector<TEfficiency*> QCD18_effs = QCD18.Analyze();
	QCD18.makePlots(QCD18_effs);
}


else{
	cout << "Invalid sampleName" << endl;
	return;
}




	
}