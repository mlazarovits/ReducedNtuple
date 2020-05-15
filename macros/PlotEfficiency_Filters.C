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

void PlotEfficiency_Filters(TString sfile, bool debug=false){
TString name
if(debug) name = sfile+"test";
else name = sfile+"_AllFilters_loose";

if(gSystem->AccessPathName(sfile+".root")){
	cout << "Error: file not found" << endl;
	return;
}
TFile* file = TFile::Open(sfile);
FilterSet filters(file, debug);
filters.SetSampleName(name);

if(strstr(sampleName,"16")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.SetVar("MET_pt");

}
else if(strstr(sampleName,"17")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.SetVar("METFixEE2017_pt");
}
else if(strstr(sampleName,"18")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.SetVar("MET_pt");

}

else{
	cout << "Invalid file or sampleName given" << endl;
	return;
}

filters.SetOutputName(name+".root");

vector<TEfficiency*> effs = filters.Analyze();
filters.makePlots(effs);






	
}
