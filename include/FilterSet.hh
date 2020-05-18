#ifndef FilterSet_HH
#define FilterSet_HH

#include <string>
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TH2.h>
#include <TLatex.h>
#include <TLorentzVector.h>

#include "prod2016MC_reducedNANO_EventFilters.h"
#include "prod2017MC_reducedNANO_EventFilters.h"
#include "prod2018MC_reducedNANO_EventFilters.h"
#include "JSONTool.hh"



using namespace std;

class FilterSet{
public:
	
	FilterSet(TFile* file, bool i_debug=false);
	// FilterSet(prod2016MC_reducedNANO_Filters filter16);
	// FilterSet(prod2016MC_reducedNANO_Filters filter17);
	// FilterSet(prod2016MC_reducedNANO_Filters filter18);
	virtual ~FilterSet(){};

	void AddFile(const string& filename);
	int GetNFile() const;
	string GetFile(int n);

	void SetSampleName(const TString& samplename);
	string GetSampleName() const;

	void SetOutputName(const TString& outname);
	string GetOutputName() const;

	void AddFilter(string Filter);
	vector<string> GetFilters();

	void SetVar(string var);
	string GetVar();

	vector<TLeaf*> ScanFilters(string target,string Filter);

	vector<TEfficiency*> Analyze();
	TEfficiency* Analyze2D();

	void makePlots(vector<TEfficiency*> effs);
	void make2DPlot(TEfficiency* eff);

	void SetCuts(string cuts);

	void AddJSONFile(const string& jsonfile);


	

private:
	
	float calcHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf);
	TLorentzVector calcMHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf);
	Double_t calcInvMass2Muons(int Muon1, int Muon2);	
	Double_t calcPt2Muons(int Muon1, int Muon2);
	std::vector<Double_t> makeEffBins(TString inputvar);

	JSONTool m_JSONTool;

	int run;
	int lumiBlock;



	string m_samplename;
	string m_filtername;
	string m_outname;
	TTree* m_tree;
	string m_var;
	string m_cuts;

	float etacut;

	TLeaf* l_nMuon;
	TLeaf* l_Muon_mediumId;
	TLeaf* l_Muon_mediumPromptId;
	TLeaf* l_Muon_tightId;
	TLeaf* l_Muon_miniIsoId;
	TLeaf* l_Muon_minipfRelIso_all;
	TLeaf* l_Muonpt;
	TLeaf* l_Muoneta;
	TLeaf* l_Muonphi;
	TLeaf* l_Muonmass;
	TLeaf* l_Muon_sip3d;


	TLeaf* l_nElectron;
	TLeaf* l_Electron_pfRelIso03_all;
	TLeaf* l_MET;
	TLeaf* l_nJet;
	TLeaf* l_Jet_pt;
	TLeaf* l_Jet_eta;
	TLeaf* l_Jet_phi;
	TLeaf* l_Jet_mass;

	TLeaf* l_reqFilter;
	
	TLeaf* l_var;
	TLeaf* l_weight;


	vector<string> m_Filters;
	
	vector<string> m_filenames;

	bool debug=false;

	




};
#endif
// #define 

inline FilterSet::FilterSet(TFile* file,bool i_debug=false){
	m_tree = (TTree*)file->Get("Events");
	if(m_tree == NULL){
		cout << "Error: No tree found" << endl;
	}
	debug = i_debug;
	l_var = m_tree->GetLeaf(m_var.c_str());
}



inline void FilterSet::AddFile(const string& filename){
	m_filenames.push_back(filename);
}

inline int FilterSet::GetNFile() const {
  return m_filenames.size();
}
inline string FilterSet::GetFile(int n){
  int N = GetNFile();
  if(n < 0 || n >= N)
    return "NO FILE";
  return m_filenames[n];
}




inline void FilterSet::SetSampleName(const TString& samplename){
	m_samplename = samplename;
}

inline string FilterSet::GetSampleName() const{
	return m_samplename;
}

inline void FilterSet::SetOutputName(const TString& outname){
	m_outname = outname;
}
inline string FilterSet::GetOutputName() const {
	return m_outname;
}




inline void FilterSet::AddFilter(string Filter){
	m_Filters.push_back(Filter);
}

inline vector<string> FilterSet::GetFilters(){
	return m_Filters;
}

inline void FilterSet::SetVar(string var){
	m_var = var;
}

inline string FilterSet::GetVar(){
	return m_var;
}

inline vector<TLeaf*> FilterSet::ScanFilters(string target,string Filter){
	int num = 0;
		size_t pos = 0;
		// string targetOR = "||"
		while( (pos = Filter.find(target,pos)) != std::string::npos ){
			++num;
			pos += target.length();
		}
	int nfilter = num+1;

	vector<TLeaf*> vec_filter;
	char str_filter[nfilter][100];
	string chopfilter;
	for(int i = 1; i < nfilter; i++){
		chopfilter += "%s "+ target;
	}
	chopfilter += " %s";


	return vec_filter;
}



inline void FilterSet::SetCuts(string cuts){
	m_cuts = cuts;
}


inline void FilterSet::AddJSONFile(const string& jsonfile){
	m_JSONTool.BuildMap(jsonfile);
}



inline float FilterSet::calcHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf){
	double HT = 0.;
	for(int i = 0; i < nJet_leaf->GetValue(); i++){
		HT+=Jet_pt_leaf->GetValue(i);
	}
	return HT;
}


inline TLorentzVector FilterSet::calcMHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf){
	TLorentzVector MHT(0.,0.,0.,0.);
	for(int i = 0; i < nJet_leaf->GetValue(); i++){
		TLorentzVector dummy;
		dummy.SetPtEtaPhiM(Jet_pt_leaf->GetValue(i),Jet_eta_leaf->GetValue(i),Jet_phi_leaf->GetValue(i),Jet_mass_leaf->GetValue(i));
		MHT -= dummy;
	}
	return MHT;
}

inline Double_t FilterSet::calcInvMass2Muons(int Muon1, int Muon2){
	TLorentzVector lep1;
	TLorentzVector lep2;
	lep1.SetPtEtaPhiM(l_Muonpt->GetValue(Muon1),l_Muoneta->GetValue(Muon1),l_Muonphi->GetValue(Muon1),l_Muonmass->GetValue(Muon1));
	lep2.SetPtEtaPhiM(l_Muonpt->GetValue(Muon2),l_Muoneta->GetValue(Muon2),l_Muonphi->GetValue(Muon2),l_Muonmass->GetValue(Muon2));
	Double_t invmass = (lep1 + lep2).M();
	return invmass;
}

inline Double_t FilterSet::calcPt2Muons(int Muon1, int Muon2){
	TLorentzVector lep1;
	TLorentzVector lep2;
	lep1.SetPtEtaPhiM(l_Muonpt->GetValue(Muon1),l_Muoneta->GetValue(Muon1),l_Muonphi->GetValue(Muon1),l_Muonmass->GetValue(Muon1));
	lep2.SetPtEtaPhiM(l_Muonpt->GetValue(Muon2),l_Muoneta->GetValue(Muon2),l_Muonphi->GetValue(Muon2),l_Muonmass->GetValue(Muon2));
	Double_t pt = (lep1 + lep2).Pt();
	return pt;
}






inline std::vector<Double_t> FilterSet::makeEffBins(TString inputvar){
	Int_t nBins;
	std::vector<Double_t> effbins;
	//set bins of TEff object
	if(strstr(inputvar,"pt")){
		nBins = 20;
		effbins.push_back(0.0);
		//SOS binning
		for(int i = 1; i < 2; i++){
			effbins.push_back(effbins.at(i-1) + 4.0);
			// cout << effbins[i] << endl;
		}
		for(int i = 2; i < 5; i++){
			effbins.push_back(effbins.at(i-1) + 1.0);
			// cout << effbins[i] << endl;
		}
		for(int i = 5; i < 6; i++){
			effbins.push_back(effbins.at(i-1) + 3.);
		}
		for(int i = 6; i < 11; i++){
			effbins.push_back(effbins.at(i-1) + 5.);
		}
	}
	else if(strstr(inputvar,"eta")){

		effbins.push_back(0.0);
		effbins.push_back(effbins.at(0) + 0.8);
		effbins.push_back(effbins.at(1) + 0.45);
		effbins.push_back(effbins.at(2) + 0.35);
		effbins.push_back(effbins.at(3) + 0.5);
		effbins.push_back(effbins.at(4) + 0.3);
		effbins.push_back(effbins.at(5) + 0.1);
	}
	else if(strstr(inputvar,"MET")){
		for(int i = 0; i < 20; i++){
			effbins.push_back(i*10.);
		}
		for(int i = 0; i < 2; i++){
			effbins.push_back(i*50 + 200);
		}
		for(int i = 0; i < 4; i++){
			effbins.push_back(i*100 + 300);
		}
	}
	else{
		//generic binning
		for(int i = 0; i < 20; i++){
			effbins.push_back(i*10.);
		}
	}
	return effbins;
}


inline TEfficiency* FilterSet::Analyze2D(){
	// vector<TEfficiency*> vec_eff;
	// vector<TLeaf*> vec_lfilter;
	TEfficiency* eff;
	TLeaf* l_filter;
	
	

	int nEntries;
	if(l_var == NULL){
		cout << "Error: Variable " << m_var.c_str() << " not found" << endl;
		return eff;
	}

	vector<Double_t> effbinsx = makeEffBins("pt");
	Int_t nBinsx = effbinsx.size()-2;
	std::vector<Double_t> effbinsy = makeEffBins("eta");
	Int_t nBinsy = effbinsy.size()-2;


	//create TEfficiency objects and get Filter leaves
	string title = (m_var+" vs."+m_Filters.at(0)+" Efficiency").c_str();
	string x_label = (";"+m_var).c_str();
	string y_label = ";#epsilon";
	eff = new TEfficiency(m_Filters.at(0).c_str(),(m_Filters.at(0)).c_str(),nBinsx,&effbinsx.at(0),nBinsy,&effbinsy.at(0));
	
	l_filter = m_tree->GetLeaf(m_Filters.at(0).c_str());

	
	if(l_filter == NULL){
		cout << "Error: Filter " << m_Filters.at(0) << " not found" << endl;
		return eff;
	}
	

	if(debug == true) nEntries = 1E6;
	else if (debug == false) nEntries = m_tree->GetEntries();

	

	for(int evt = 0; evt < nEntries; evt++){
		
		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);

	    

		bool bPassed = l_filter->GetValue();
		

		//FIX 2D PLOT TO ACTUALLY FILL WITH 2 VARIABLES
		eff->Fill((bPassed),l_var->GetValue(0)); 
		
			
	}
	cout << endl;

	return eff;
}



inline vector<TEfficiency*> FilterSet::Analyze(){
	vector<TEfficiency*> vec_eff;
	vector<TLeaf*> vec_lfilter;


	l_var = m_tree->GetLeaf(GetVar().c_str());

	
	


	int nEntries;
	if(l_var == NULL){
		cout << "Error: Variable " << m_var.c_str() << " not found" << endl;
		return vec_eff;
	}

	vector<Double_t> effbins = makeEffBins(m_var.c_str());
	Int_t nBins = effbins.size()-2;
	

	//create TEfficiency objects and get Filter leaves
	for(int i = 0; i < m_Filters.size(); i++){
		string title = (m_var+" vs."+m_Filters.at(i)+" Efficiency").c_str();
		string x_label = (";"+m_var).c_str();
		string y_label = ";#epsilon";
		TEfficiency* eff = new TEfficiency(m_Filters.at(i).c_str(),(m_Filters.at(i)).c_str(),nBins,&effbins.at(0));
		
		TLeaf* l_filter = m_tree->GetLeaf(m_Filters.at(i).c_str());

		
		if(l_filter == NULL){
			cout << "Error: Filter " << m_Filters.at(i) << " not found" << endl;
			return vec_eff;
		}
		vec_eff.push_back(eff);
		vec_lfilter.push_back(l_filter);
	}

	if(debug == true) nEntries = 1E6;
	else if (debug == false) nEntries = m_tree->GetEntries();

	

	for(int evt = 0; evt < nEntries; evt++){
		
		

		m_tree->GetEntry(evt);
		run = m_tree->GetLeaf("run")->GetValue();
		lumiBlock = m_tree->GetLeaf("luminosityBlock")->GetValue();




		

		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);

	    //check for good run
		if(!m_JSONTool.IsGood(run,lumiBlock)) continue;


		for(int nfilter = 0; nfilter < m_Filters.size(); nfilter++){


			bool bPassed = vec_lfilter.at(nfilter)->GetValue();
			vec_eff.at(nfilter)->Fill(!bPassed,l_var->GetValue()); 
			
			
		}
	}
	cout << endl;

	return vec_eff;
}


inline void FilterSet::make2DPlot(TEfficiency* eff){
	gStyle->SetPalette(kRainBow);
	gStyle->SetPaintTextFormat("0.2f");
	//GET EFFICIENCIES ON PLOT
	TCanvas* cv = new TCanvas("cv","cv",800,600);
	cv->cd();
	eff->Draw("colztext");
	cv->Update();
	
	TH2* h = eff->GetPaintedHistogram();
	
	
	cv->Update();

	TString g_PlotTitle = m_samplename+" Filter Efficiencies";
	h->GetZaxis()->SetTitle((m_Filters.at(0)+" Efficiency").c_str());
	h->SetMaximum(1.0);
	h->SetMinimum(0.0);
	h->GetXaxis()->SetTitle("Subleading Muon pT (GeV)");
	h->GetYaxis()->SetTitle("Subleading Muon #eta");
	h->SetTitle(g_PlotTitle);

	Int_t gBin;
	Double_t error;
	
	for(int i = 1; i < 10; i++){
		for(int j = 1; j < 6; j++){
			gBin = h->GetBin(i,j);
			cout << "X bin #: " << i << " Y bin #: " << j << endl;
			cout << "global bin: " << gBin << endl;
			cout << "Bin Content: " << h->GetBinContent(gBin) << endl;
			cout << "Bin Error: " << h->GetBinError(gBin) << endl;
			cout << "Efficiency: " << eff->GetEfficiency(gBin) << endl;
			cout << "Eff error up: " << eff->GetEfficiencyErrorUp(gBin) << endl;
			cout << "Eff error low: " << eff->GetEfficiencyErrorLow(gBin) << endl;
			cout << "\n" << endl;

			if(eff->GetEfficiencyErrorUp(gBin) >= eff->GetEfficiencyErrorLow(gBin)){
				error = eff->GetEfficiencyErrorUp(gBin);
			}
			else if(eff->GetEfficiencyErrorUp(gBin) < eff->GetEfficiencyErrorLow(gBin)){
				error = eff->GetEfficiencyErrorLow(gBin);	
			}
			h->SetBinError(gBin,error);
			
		}
	}
	cv->Update();
	h->Draw("colztextE");

	TLatex l;
	l.SetTextFont(132);
	l.SetNDC();
	l.SetTextSize(0.035);
	l.SetTextFont(42);
	l.SetTextSize(0.03);
	l.SetTextFont(61);
	l.DrawLatex(0.16,0.92,"CMS");
	l.SetTextFont(52);
	l.DrawLatex(0.21,0.92,"Preliminary");
	l.SetTextFont(132);
	l.SetNDC();
	l.SetTextSize(0.05);
	l.SetTextFont(132);
	l.DrawLatex(0.40,0.92,g_PlotTitle);
	cv->Update();

	if(!debug){
		TString filename = ("/home/t3-ku/mlazarov/Ewkinos/CMSSW_10_6_5/src/ReducedNtuple/Filters"+m_outname).c_str();

		TFile* file = new TFile(filename,"RECREATE");
		cout << "file: " << filename << " created" << endl;
		file->cd();
		cv->Write();
	}
	else{
		return;
	}
}


inline void FilterSet::makePlots(vector<TEfficiency*> effs){
	TCanvas* cv = new TCanvas("cv","cv",900,700);
	TLegend* leg = new TLegend(0.35,0.2,0.95,0.4);
	vector<TGraphAsymmErrors*> gr_effs;
	TMultiGraph* mg = new TMultiGraph();


	cv->cd();
	cv->SetGridx();
	cv->SetGridy();
	cv->SetLeftMargin(0.13);
	cv->SetRightMargin(0.04);
	cv->SetBottomMargin(0.15);
	cv->SetTopMargin(0.085);

	effs[0]->Draw("AP");
	cv->Update();
	gr_effs.push_back(effs[0]->GetPaintedGraph());
	for(int i = 1; i < effs.size(); i++){
		effs[i]->Draw("same");
		cv->Update();
		gr_effs.push_back(effs[i]->GetPaintedGraph());
	}


	cout << "# of Filters: " << gr_effs.size() << endl;
	// double fmax = -1.;
	// int imax = -1;
	// for(int i = 0; i < gr_effs.size(); i++){
	// 	if(gr_effs[i]->GetMaximum() > fmax){
	// 		fmax = gr_effs[i]->GetMaximum();
	// 		imax = i;
	// 	}
	// }
	// cout << "imax: " << endl;
	// gr_effs[imax]->Draw();

	cv->Update();
	Int_t chopcolor = gr_effs.size()/2;
	Int_t chopmarker = gr_effs.size()/2;

	for(int i = 0; i < gr_effs.size(); i++){
		gr_effs[i]->SetMarkerSize(1.5);
		gr_effs[i]->SetLineWidth(2);
		// gr_effs[i]->GetYaxis()->SetRangeUser(0.0,1.0);
		
		if(i / chopmarker == 0){
			gr_effs[i]->SetMarkerStyle(22); //triangle
		} 
		else if(i / chopmarker == 1){
			gr_effs[i]->SetMarkerStyle(21);//square
		}
		else if(i /chopmarker == 2){
			gr_effs[i]->SetMarkerStyle(20); //circle
		}
		if(i % chopcolor == 0){
			gr_effs[i]->SetMarkerColor(kBlue-7);
			gr_effs[i]->SetLineColor(kBlue-7);
		}
		else if(i % chopcolor == 1){
			gr_effs[i]->SetMarkerColor(kRed-7);
			gr_effs[i]->SetLineColor(kRed-7);
		}
		else if(i % chopcolor == 2){
			gr_effs[i]->SetMarkerColor(kGreen-7);
			gr_effs[i]->SetLineColor(kGreen-7);
		}
		else{
			gr_effs[i]->SetMarkerColor(kCyan-7);
			gr_effs[i]->SetLineColor(kCyan-7);
		}
		// gr_effs[i]->Draw("same");
		mg->Add(gr_effs[i]);
		// cv->Update();
		leg->AddEntry(gr_effs[i]);
	}
	leg->SetTextFont(132);
	leg->SetTextSize(0.03);
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);

	mg->Draw("AP");
	leg->Draw("SAME");
	cv->Update();

	string g_PlotTitle = m_samplename+" Filter Efficiencies";
	mg->GetXaxis()->SetTitle(m_var.c_str());
	mg->GetYaxis()->SetTitle("1 - #epsilon");
	mg->GetYaxis()->SetRangeUser(0.000001,0.1);
	cv->SetLogy();
	

	TLatex l;
	l.SetTextFont(132);
	l.SetNDC();
	l.SetTextSize(0.035);
	l.SetTextFont(42);
	l.SetTextSize(0.03);
	l.SetTextFont(61);
	l.DrawLatex(0.16,0.92,"CMS");
	l.SetTextFont(52);
	l.DrawLatex(0.21,0.92,"Preliminary");
	l.SetTextFont(132);
	l.SetNDC();
	l.SetTextSize(0.05);
	l.SetTextFont(132);
	l.DrawLatex(0.40,0.92,g_PlotTitle.c_str());
	cv->Update();

	if(!debug){
		TString filename = ("/home/t3-ku/mlazarov/Ewkinos/CMSSW_10_6_5/src/ReducedNtuple/effPlots/Filters/"+m_outname).c_str();

		TFile* file = new TFile(filename,"RECREATE");
		cout << "file: " << filename << " created" << endl;
		file->cd();
		cv->Write();
	}
	else{
		return;
	}
	



}
