#include <iostream>

#include "../include/prod2016MC_reducedNANO_EventFilters.h"
#include "../include/prod2017MC_reducedNANO_EventFilters.h"
#include "../include/prod2018MC_reducedNANO_EventFilters.h"
#include "../include/FilterSet.hh"

#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TGraph.h"


using namespace std;

void PlotEfficiency_Filters(TFile* file, TString sampleName){
	// if(gSystem->OpenDirectory("plots") == 0){
	// 	gSystem->mkdir("plots");
	// 	cout << "Created plots folder." << endl;
	// }

	
	// string gPathname = "/home/t3-ku/mlazarov/Ewkinos/CMSSW_10_6_5/src/ReducedNtuple/";
	// TFile* f_wjets16 = TFile::Open((gPathname+"output/Summer16_94X_WJetsToLNu_EventFilters.root").c_str());
	// TFile* f_wjets17 = TFile::Open((gPathname+"output/Fall17_94X_WJetsToLNu_EventFilters.root").c_str());
	// TFile* f_wjets18 = TFile::Open((gPathname+"output/Autumn18_102X_WJetsToLNu_EventFilters.root").c_str());

	// TFile* f_QCD16 = TFile::Open((gPathname+"output/Summer16_102X_QCD_HT700to1000_EventFilters.root").c_str());
	// TFile* f_QCD17 = TFile::Open((gPathname+"output/Fall17_102X_QCD_HT700to1000_EventFilters.root").c_str());
	// TFile* f_QCD18 = TFile::Open((gPathname+"output/Autumn18_102X_QCD_HT700to1000_EventFilters.root").c_str());


TString name = sampleName+"AllFilters_loose";
FilterSet filters(file);
filters.SetSampleName(name);

if(strstr(sampleName,"16")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_eeBadScFilter");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.SetVar("MET_pt");

}
else if(strstr(sampleName,"17")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_eeBadScFilter");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.AddFilter("Flag_BadChargedCandidateFilter");
	filters.SetVar("METFixEE2017_pt");
}
else if(strstr(sampleName,"18")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_eeBadScFilter");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.AddFilter("Flag_BadChargedCandidateFilter");
	filters.SetVar("MET_pt");

}

else{
	cout << "Check file and sampleName given" << endl;
	return;
}

filters.SetOutputName(name+".root");

vector<TEfficiency*> effs = filters.Analyze();
filters.makePlots(effs);






	
}
