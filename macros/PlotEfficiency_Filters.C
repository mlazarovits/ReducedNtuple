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
string gPath = "/home/t3-ku/mlazarov/Ewkinos/CMSSW_10_6_5/src/ReducedNtuple/DataRootFiles/";
if(debug) name = inFile+"test";
else name = outName+"_AllFilters";
TChain* chain = new TChain("Events");
TFile* file;





if(strstr(inFile, "all")){
	file = new TFile(inFile, "RECREATE");
	chain->SetBranchStatus("*",0);
	chain->SetBranchStatus("Flag_HBHENoiseFilter",1);
	chain->SetBranchStatus("Flag_HBHENoiseIsoFilter",1);
	chain->SetBranchStatus("Flag_globalSuperTightHalo2016Filter",1);
	chain->SetBranchStatus("Flag_EcalDeadCellTriggerPrimitiveFilter",1);
	chain->SetBranchStatus("Flag_goodVertices",1);
	chain->SetBranchStatus("Flag_BadPFMuonFilter",1);
	if(strstr(inFile,"16")){
		chain->AddFile((gPath+"MET_Run2016B.root").c_str());
		chain->AddFile((gPath+"MET_Run2016C.root").c_str());
		chain->AddFile((gPath+"MET_Run2016D.root").c_str());
		chain->AddFile((gPath+"MET_Run2016E.root").c_str());
	}
	else if(strstr(inFile,"17")){
		chain->AddFile((gPath+"MET_Run2017B.root").c_str());
		chain->AddFile((gPath+"MET_Run2017C.root").c_str());
		chain->AddFile((gPath+"MET_Run2017D.root").c_str());
		chain->AddFile((gPath+"MET_Run2017E.root").c_str());
	}
	else if(strstr(inFile,"18")){
		chain->AddFile((gPath+"MET_Run2018A.root").c_str());
		chain->AddFile((gPath+"MET_Run2018B.root").c_str());
		chain->AddFile((gPath+"MET_Run2018C.root").c_str());
		chain->AddFile((gPath+"MET_Run2018D.root").c_str());
	}
	chain->CloneTree(-1,"fast");
	
	file->Write();
	

}
else{ 
	if(gSystem->AccessPathName(inFile)){
		cout << "Error: file not found" << endl;
		return;
	}
	file = TFile::Open(inFile);
}


FilterSet filters(file, debug);
filters.SetSampleName(name);
filters.AddFilter("Flag_HBHENoiseFilter");
filters.AddFilter("Flag_HBHENoiseIsoFilter");
filters.AddFilter("Flag_globalSuperTightHalo2016Filter");
filters.AddFilter("Flag_EcalDeadCellTriggerPrimitiveFilter");
filters.AddFilter("Flag_goodVertices");
filters.AddFilter("Flag_BadPFMuonFilter");

if(strstr(inFile,"16")){
	filters.AddJSONFile("json/GoodRunList/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt");
	filters.SetVar("MET_pt");

}
else if(strstr(inFile,"17")){
	filters.AddJSONFile("json/GoodRunList/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt");
	filters.SetVar("METFixEE2017_pt");
}
else if(strstr(inFile,"18")){
	filters.AddJSONFile("json/GoodRunList/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt");
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
