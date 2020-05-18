#include <iostream>

#include "../include/prod2016MC_reducedNANO_EventFilters.h"
#include "../include/prod2017MC_reducedNANO_EventFilters.h"
#include "../include/prod2018MC_reducedNANO_EventFilters.h"
#include "../include/FilterSet.hh"
#include "../include/JSONTool.hh"

#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TGraph.h"


using namespace std;

void PlotEfficiency_Filters(TString inFile, TString outName, bool debug=false){
TString name;
if(debug) name = inFile+"test";
else name = outName+"_AllFilters_loose";

if(gSystem->AccessPathName(inFile)){
	cout << "Error: file not found" << endl;
	return;
}
TFile* file = TFile::Open(inFile);
FilterSet filters(file, debug);
filters.SetSampleName(name);

if(strstr(inFile,"16")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.AddJSONFile("json/GoodRunList/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt");
	filters.SetVar("MET_pt");

}
else if(strstr(inFile,"17")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.AddJSONFile("json/GoodRunList/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt");
	filters.SetVar("METFixEE2017_pt");
}
else if(strstr(inFile,"18")){
	filters.AddFilter("Flag_HBHENoiseFilter");
	filters.AddFilter("Flag_HBHENoiseIsoFilter");
	filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
	filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
	filters.AddFilter("Flag_goodVertices");
	filters.AddJSONFile("json/GoodRunList/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt");
	filters.AddFilter("Flag_BadPFMuonFilter");
	filters.SetVar("MET_pt");

}

else{
	cout << "Invalid file given" << endl;
	return;
}

filters.SetOutputName(name+".root");

vector<TEfficiency*> effs = filters.Analyze();
filters.makePlots(effs);






	
}
