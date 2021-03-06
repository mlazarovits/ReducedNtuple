#ifndef TriggerSet_HH
#define TriggerSet_HH

#include <string>
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>
#include "../include/prod2016MC_reducedNANO_Triggers.h"
#include "../include/prod2017MC_reducedNANO_Triggers.h"
#include "../include/prod2018MC_reducedNANO_Triggers.h"
// #include "TEfficiency.h"
#include <TLatex.h>


using namespace std;

class TriggerSet{
public:
	
	TriggerSet(TFile* file, bool i_debug=false);
	// TriggerSet(prod2016MC_reducedNANO_Triggers trig16);
	// TriggerSet(prod2016MC_reducedNANO_Triggers trig17);
	// TriggerSet(prod2016MC_reducedNANO_Triggers trig18);
	virtual ~TriggerSet(){};

	void AddFile(const string& filename);
	int GetNFile() const;
	string GetFile(int n);

	void SetSampleName(const string& samplename);
	string GetSampleName() const;

	void SetOutputName(const string& outname);
	string GetOutputName() const;

	void AddTrigger(string trigger);
	vector<string> GetTriggers();

	void SetVar(string var);
	string GetVar();

	vector<TLeaf*> ScanTriggers(string target,string trigger);

	vector<TEfficiency*> Analyze();
	TEfficiency* Analyze2D();

	void makePlots(vector<TEfficiency*> effs);
	void make2DPlot(TEfficiency* eff);

	void SetCuts(string cuts);


	

private:
	
	float calcHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf);
	TLorentzVector calcMHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf);
	Double_t calcInvMass2Muons(int Muon1, int Muon2);	
	Double_t calcPt2Muons(int Muon1, int Muon2);
	void initializeAnalyze();
	std::vector<Double_t> makeEffBins(TString inputvar);


	// bool GoldenMuonSelection();
	// bool DoubleMuonSelection();


	string m_samplename;
	string m_trigname;
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

	TLeaf* l_reqTrigger;
	
	TLeaf* l_var;
	TLeaf* l_weight;

	vector<string> m_triggers;
	
	vector<string> m_filenames;

	bool debug=false;

	




};
#endif
// #define 

inline TriggerSet::TriggerSet(TFile* file,bool i_debug=false){
	m_tree = (TTree*)file->Get("Events");
	if(m_tree == NULL){
		cout << "Error: No tree found" << endl;
	}
	debug = i_debug;
}



inline void TriggerSet::AddFile(const string& filename){
	m_filenames.push_back(filename);
}

inline int TriggerSet::GetNFile() const {
  return m_filenames.size();
}
inline string TriggerSet::GetFile(int n){
  int N = GetNFile();
  if(n < 0 || n >= N)
    return "NO FILE";
  return m_filenames[n];
}




inline void TriggerSet::SetSampleName(const string& samplename){
	m_samplename = samplename;
}

inline string TriggerSet::GetSampleName() const{
	return m_samplename;
}

inline void TriggerSet::SetOutputName(const string& outname){
	m_outname = outname;
}
inline string TriggerSet::GetOutputName() const {
	return m_outname;
}




inline void TriggerSet::AddTrigger(string trigger){
	m_triggers.push_back(trigger);
}

inline vector<string> TriggerSet::GetTriggers(){
	return m_triggers;
}

inline void TriggerSet::SetVar(string var){
	m_var = var;
}

inline string TriggerSet::GetVar(){
	return m_var;
}

inline vector<TLeaf*> TriggerSet::ScanTriggers(string target,string trigger){
	int num = 0;
		size_t pos = 0;
		// string targetOR = "||"
		while( (pos = trigger.find(target,pos)) != std::string::npos ){
			++num;
			pos += target.length();
		}
	int nTrig = num+1;

	vector<TLeaf*> vec_trig;
	char str_trig[nTrig][100];
	string choptrig;
	for(int i = 1; i < nTrig; i++){
		choptrig += "%s "+ target;
	}
	choptrig += " %s";


	return vec_trig;
}



inline void TriggerSet::SetCuts(string cuts){
	m_cuts = cuts;
}



// inline bool TriggerSet::GoldenMuonSelection(){
// 	float mu_absMiniIso = 0.0;
// 	float mu_sip3d = 0.0;
// 	float isGoldenCounter = 0.0;
// 	bool isGolden;
// 	int nMuon = l_nMuon->GetValue();

// 	//replace with electron IDs
// 	for(int i = 0; i < nMuon; i++){
// 	// cout << "med id: " << l_Muon_mediumId->GetValue(i) << endl;
// 		mu_absMiniIso = l_Muon_minipfRelIso_all->GetValue(i)*l_Muonpt->GetValue(i);
// 		mu_sip3d = l_Muon_sip3d->GetValue(i);
// 		if(mu_absMiniIso < 6. && mu_sip3d < 4 && l_Muon_mediumId->GetValue(i)){
// 			isGoldenCounter += 1.0;
// 		}
// 		else{
// 			continue;
// 		}
// 	}
// 	if(isGoldenCounter > 0.0) isGolden = true;
// 	else isGolden = false;

// 	return isGolden;
// }



// inline bool TriggerSet::DoubleMuonSelection(){
// 	bool iso = false;
// 	bool double_lep = false;
// 	bool METval = false;
// 	bool mHTval = false;
// 	bool invMuonMassval = false;
// 	bool invMuonpTval = false;
// 	bool reqTrigger = false;
	

// 	Double_t invMuonMass = calcInvMass2Muons(0, 1);
// 	Double_t invMuonpT = calcPt2Muons(0, 1);
// 	float HT = calcHT(l_nJet, l_Jet_pt, l_Jet_eta, l_Jet_phi, l_Jet_mass);
// 	TLorentzVector MHT = calcMHT(l_nJet, l_Jet_pt, l_Jet_eta, l_Jet_phi, l_Jet_mass);


// 	bool isGood = false;


// 	if(l_nMuon->GetValue() == 2) double_lep = true;

// 	if(l_MET->GetValue() >= 200) METval = true;
// 	if(MHT.Pt() >= 60) mHTval = true;


// 	if(invMuonMass >= 4 && invMuonMass < 60) invMuonMassval = true;
// 	if(invMuonpT >= 3) invMuonpTval = true;
// 	if(l_reqTrigger->GetValue() == true) reqTrigger = true;

// 	if(double_lep && METval && mHTval && invMuonMass && invMuonpT && reqTrigger) isGood = true;

// 	return isGood;
// }





inline float TriggerSet::calcHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf){
	double HT = 0.;
	for(int i = 0; i < nJet_leaf->GetValue(); i++){
		HT+=Jet_pt_leaf->GetValue(i);
	}
	return HT;
}


inline TLorentzVector TriggerSet::calcMHT(TLeaf* nJet_leaf, TLeaf* Jet_pt_leaf, TLeaf* Jet_eta_leaf, TLeaf* Jet_phi_leaf, TLeaf* Jet_mass_leaf){
	TLorentzVector MHT(0.,0.,0.,0.);
	for(int i = 0; i < nJet_leaf->GetValue(); i++){
		TLorentzVector dummy;
		dummy.SetPtEtaPhiM(Jet_pt_leaf->GetValue(i),Jet_eta_leaf->GetValue(i),Jet_phi_leaf->GetValue(i),Jet_mass_leaf->GetValue(i));
		MHT -= dummy;
	}
	return MHT;
}

inline Double_t TriggerSet::calcInvMass2Muons(int Muon1, int Muon2){
	TLorentzVector lep1;
	TLorentzVector lep2;
	lep1.SetPtEtaPhiM(l_Muonpt->GetValue(Muon1),l_Muoneta->GetValue(Muon1),l_Muonphi->GetValue(Muon1),l_Muonmass->GetValue(Muon1));
	lep2.SetPtEtaPhiM(l_Muonpt->GetValue(Muon2),l_Muoneta->GetValue(Muon2),l_Muonphi->GetValue(Muon2),l_Muonmass->GetValue(Muon2));
	Double_t invmass = (lep1 + lep2).M();
	return invmass;
}

inline Double_t TriggerSet::calcPt2Muons(int Muon1, int Muon2){
	TLorentzVector lep1;
	TLorentzVector lep2;
	lep1.SetPtEtaPhiM(l_Muonpt->GetValue(Muon1),l_Muoneta->GetValue(Muon1),l_Muonphi->GetValue(Muon1),l_Muonmass->GetValue(Muon1));
	lep2.SetPtEtaPhiM(l_Muonpt->GetValue(Muon2),l_Muoneta->GetValue(Muon2),l_Muonphi->GetValue(Muon2),l_Muonmass->GetValue(Muon2));
	Double_t pt = (lep1 + lep2).Pt();
	return pt;
}




inline void TriggerSet::initializeAnalyze(){
	l_nMuon = m_tree->GetLeaf("nMuon");
	l_Muonpt = m_tree->GetLeaf("Muon_pt");
	l_Muoneta = m_tree->GetLeaf("Muon_eta");
	l_Muonphi = m_tree->GetLeaf("Muon_phi");
	l_Muonmass = m_tree->GetLeaf("Muon_mass");
	l_Muon_mediumId = m_tree->GetLeaf("Muon_mediumId");
	l_Muon_mediumPromptId = m_tree->GetLeaf("Muon_mediumPromptId");
	l_Muon_tightId = m_tree->GetLeaf("Muon_tightId");
	l_Muon_miniIsoId = m_tree->GetLeaf("Muon_miniIsoId");
	l_Muon_minipfRelIso_all = m_tree->GetLeaf("Muon_miniPFRelIso_all");
	l_Muon_sip3d = m_tree->GetLeaf("Muon_sip3d");

	l_reqTrigger = m_tree->GetLeaf("HLT_IsoMu27");

	if(strstr(m_samplename.c_str(),"2017")){
		l_MET = m_tree->GetLeaf("METFixEE2017_pt");
	}
	
	l_nJet = m_tree->GetLeaf("nJet");
	l_Jet_mass = m_tree->GetLeaf("Jet_mass");
	l_Jet_phi = m_tree->GetLeaf("Jet_phi");
	l_Jet_eta = m_tree->GetLeaf("Jet_eta");
	l_Jet_pt = m_tree->GetLeaf("Jet_pt");

	l_nElectron = m_tree->GetLeaf("nElectron");
	l_Electron_pfRelIso03_all = m_tree->GetLeaf("Muon_pfRelIso03_all");
	
	l_var = m_tree->GetLeaf(m_var.c_str());
	l_weight = m_tree->GetLeaf("Generator_weight");
}



inline std::vector<Double_t> TriggerSet::makeEffBins(TString inputvar){
	Int_t nBins;
	std::vector<Double_t> effbins;
	//set bins of TEff object
	if(inputvar == "pt"){
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
	else if(inputvar == "eta"){

		// nBins = 200;
		// effbins.push_back(-3.05);
		// for(int i = 1; i < nBins+2; i++){
		// 	effbins.push_back(effbins.at(i-1) + 0.05);
		// 	// cout << effbins.at(i) << endl;
		// }
		//SOS binning
		// nBins = 5;
		effbins.push_back(0.0);
		// for(int i = 1; i < 2; i++){
		effbins.push_back(effbins.at(0) + 0.8);
		effbins.push_back(effbins.at(1) + 0.45);
		effbins.push_back(effbins.at(2) + 0.35);
		effbins.push_back(effbins.at(3) + 0.5);
		effbins.push_back(effbins.at(4) + 0.3);
		effbins.push_back(effbins.at(5) + 0.1);
		// }
	}
	else{
		//generic binning
		for(int i = 0; i < 20; i++){
			effbins.push_back(i*10.);
		}
	}
	return effbins;
}


inline TEfficiency* TriggerSet::Analyze2D(){
	// vector<TEfficiency*> vec_eff;
	// vector<TLeaf*> vec_ltrig;
	TEfficiency* eff;
	TLeaf* l_trig;
	
	initializeAnalyze();

	int nEntries;
	if(l_var == NULL){
		cout << "Error: Variable " << m_var.c_str() << " not found" << endl;
		return eff;
	}

	vector<Double_t> effbinsx = makeEffBins("pt");
	Int_t nBinsx = effbinsx.size()-2;
	std::vector<Double_t> effbinsy = makeEffBins("eta");
	Int_t nBinsy = effbinsy.size()-2;


	//create TEfficiency objects and get trigger leaves
	string title = (m_var+" vs."+m_triggers.at(0)+" Efficiency").c_str();
	string x_label = (";"+m_var).c_str();
	string y_label = ";#epsilon";
	eff = new TEfficiency(m_triggers.at(0).c_str(),(m_triggers.at(0)).c_str(),nBinsx,&effbinsx.at(0),nBinsy,&effbinsy.at(0));
	
	l_trig = m_tree->GetLeaf(m_triggers.at(0).c_str());

	
	if(l_trig == NULL){
		cout << "Error: Trigger " << m_triggers.at(0) << " not found" << endl;
		return eff;
	}
	

	if(debug == true) nEntries = 1E6;
	else if (debug == false) nEntries = m_tree->GetEntries();

	

	for(int evt = 0; evt < nEntries; evt++){
		bool iso = false;
		bool double_lep = false;
		bool METval = false;
		bool mHTval = false;
		bool reqTrig = false;
		bool invMuonMassval = false;
		bool invMuonpTval = false;

		bool isGolden = false;
		// bool sip3dval = false;
		// bool absminiIsoval = false;
		// bool mediumIdval = false;
		Double_t invMuonpT;
		Double_t invMuonMass;

		float mu_absMiniIso = 0.0;
				float mu_sip3d = 0.0;
				float isGoldenCounter = 0.0;
				// bool isGolden;

		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);

	    float HT = calcHT(l_nJet, l_Jet_pt, l_Jet_eta, l_Jet_phi, l_Jet_mass);
	    TLorentzVector MHT = calcMHT(l_nJet, l_Jet_pt, l_Jet_eta, l_Jet_phi, l_Jet_mass);

	    bool cuts;
	    float muonminipfRelIso_counter = 0.;

	    if(strstr(m_var.c_str(),"Muon")){
		    int nMuon = l_nMuon->GetValue();
		    float MET = l_MET->GetValue();
		    if(nMuon != 2) continue;

			if(m_cuts == "GoldenMuon"){
				
				// if(nMuon == 2) double_lep = true;
				// if(MET >= 80) METval = true;//continue;
				// if(MHT.Pt() >= 60) mHTval = true;//continue;				

				//replace with electron IDs
				for(int i = 0; i < nMuon; i++){
					// cout << "med id: " << l_Muon_mediumId->GetValue(i) << endl;
					mu_absMiniIso = l_Muon_minipfRelIso_all->GetValue(i)*l_Muonpt->GetValue(i);
					mu_sip3d = l_Muon_sip3d->GetValue(i);
					// if(mu_sip3d < 4.){
					// 	sip3dval = true;
					// }
					// if(mu_absMiniIso < 6.) absminiIsoval = true;
					// if(l_Muon_mediumId->GetValue(i)) mediumIdval = true;
					if(mu_sip3d < 4. && mu_absMiniIso < 6. && l_Muon_mediumId->GetValue(i)){
						isGoldenCounter += 1.;

					}
				}
				
				if(isGoldenCounter >= 1.0){
					isGolden = true;
				}

				
				if(MET >= 200) METval = true;//continue;
				if(MHT.Pt() >= 60) mHTval = true;//continue;

				invMuonMass = calcInvMass2Muons(0, 1);
				invMuonpT = calcPt2Muons(0, 1);


				if(invMuonMass >= 4 && invMuonMass < 60) invMuonMassval = true;
				if(invMuonpT >= 3) invMuonpTval = true;
				if(l_reqTrigger->GetValue() == true) reqTrig = true;
				
			}

			else if(m_cuts == "DoubleMuon"){
				if(MET >= 200) METval = true;//continue;
				if(MHT.Pt() >= 60) mHTval = true;//continue;

				invMuonMass = calcInvMass2Muons(0, 1);
				invMuonpT = calcPt2Muons(0, 1);


				if(invMuonMass >= 4 && invMuonMass < 60) invMuonMassval = true;
				if(invMuonpT >= 3) invMuonpTval = true;
				if(l_reqTrigger->GetValue() == true) reqTrig = true;
			}

			for(int i = 0; i < l_nMuon->GetValue();i++){
				if(l_Muon_minipfRelIso_all->GetValue(i) < 0.1) muonminipfRelIso_counter += 1.;
			}
			if(muonminipfRelIso_counter >= 1.) iso = true;
		}
		

		if(strstr(m_var.c_str(),"Electron")){

			int nElectron = l_nElectron->GetValue();
			if(nElectron != 1) continue; //at least 1 electron
		}






		if(strstr(m_triggers.at(0).c_str(),"Iso")){ //iso req for iso triggers
			if(!iso) continue;
		}

		bool bPassed = l_trig->GetValue();
		// cout << "#goldens: " << isGoldenCounter << " " << isGolden << endl;


		if(strstr(m_triggers.at(0).c_str(),"Double")){
			if( m_cuts == "GoldenMuon"){ 
				if(!METval) continue;
				// cout << "2" << endl;

				if(!mHTval) continue;
				// cout << "3" << endl;

				if(!reqTrig) continue;
				// cout << "4" << endl;

				if(!invMuonMassval) continue;
				// cout << "5" << endl;

				if(!invMuonpTval) continue;
				// cout << "6" << endl;
				// cout << isGolden << endl;

				if(!isGolden) continue;

				
			}
			else if(m_cuts == "DoubleMuon"){
				if(!METval) continue;
				if(!mHTval) continue;
				if(!reqTrig) continue;
				if(!invMuonMassval) continue;
				if(!invMuonpTval) continue;
			}

			eff->Fill((bPassed),l_Muonpt->GetValue(1),fabs(l_Muoneta->GetValue(1)));  //subleading lepton
		}
		

		else{
			eff->Fill((bPassed),l_var->GetValue(0)); //leading lepton
		}
			
	}
	cout << endl;

	return eff;
}



inline vector<TEfficiency*> TriggerSet::Analyze(){
	vector<TEfficiency*> vec_eff;
	vector<TLeaf*> vec_ltrig;
	
	initializeAnalyze();

	int nEntries;
	if(l_var == NULL){
		cout << "Error: Variable " << m_var.c_str() << " not found" << endl;
		return vec_eff;
	}

	vector<Double_t> effbins = makeEffBins(m_var.c_str());
	Int_t nBins = effbins.size()-2;
	

	//create TEfficiency objects and get trigger leaves
	for(int i = 0; i < m_triggers.size(); i++){
		string title = (m_var+" vs."+m_triggers.at(i)+" Efficiency").c_str();
		string x_label = (";"+m_var).c_str();
		string y_label = ";#epsilon";
		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(m_triggers.at(i)).c_str(),nBins,&effbins.at(0));
		
		TLeaf* l_trig = m_tree->GetLeaf(m_triggers.at(i).c_str());

		
		if(l_trig == NULL){
			cout << "Error: Trigger " << m_triggers.at(i) << " not found" << endl;
			return vec_eff;
		}
		vec_eff.push_back(eff);
		vec_ltrig.push_back(l_trig);
	}

	if(debug == true) nEntries = 1E6;
	else if (debug == false) nEntries = m_tree->GetEntries();

	

	for(int evt = 0; evt < nEntries; evt++){
		
		bool iso = false;
		bool double_lep = false;
		bool METval = false;
		bool mHTval = false;
		bool invMuonMassval = false;
		bool invMuonpTval = false;
		Double_t invMuonpT;
		Double_t invMuonMass;

		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);

	    float HT = calcHT(l_nJet, l_Jet_pt, l_Jet_eta, l_Jet_phi, l_Jet_mass);
	    TLorentzVector MHT = calcMHT(l_nJet, l_Jet_pt, l_Jet_eta, l_Jet_phi, l_Jet_mass);




	    if(strstr(m_var.c_str(),"Muon")){
		    int nMuon = l_nMuon->GetValue();
		    float MET = l_MET->GetValue();		   

		    if(nMuon >= 2) double_lep = true;
			// if(nMuon != 2) continue; 

			if(MET >= 200) METval = true;//continue;
			if(MHT.Pt() >= 60) mHTval = true;//continue;

			invMuonMass = calcInvMass2Muons(0, 1);
			invMuonpT = calcPt2Muons(0, 1);
			if(invMuonMass >= 4 && invMuonMass < 60) invMuonMassval = true;
			if(invMuonpT >= 3) invMuonpTval = true;
			if(l_reqTrigger->GetValue() == false) continue;


			


			// muselections.push_back(MuonmediumId_counter);
			// muselections.push_back(MuontightId_counter);
			// muselections.push_back(MuonmedpromptId_counter);
			// muselections.push_back(muonminiIso_counter);
			// muselections.push_back(muonminipfRelIso_counter);
			// muselections.push_back(mu_pt);
			// muselections.push_back(mu_eta);


			// vector<float> muonSelections = muonSelection(nMuon);
			// int NmuonSelections = muonSelections.size();


			// if(strstr(m_var.c_str(),"eta")){
			// 	if(muonSelections.at(NmuonSelections-2) < 125.) continue; //mupt cut
			// }

			// //eta cut for pt plots
			// // else if(strstr(m_var.c_str(),"pt")){
			// // 	if(abs(muonSelections.at(NmuonSelections-1)) < 1.4) continue;
			// // }

			// if(muonSelections.at(4) >= 1) iso = true;
				
		}

		if(strstr(m_var.c_str(),"Electron")){

			int nElectron = l_nElectron->GetValue();
			if(nElectron != 1) continue; //at least 1 electron

			// // int ElemediumId_counter = 0;
			// // int EletightId_counter = 0;
			// // int ElemedpromptId_counter = 0;
			// // int ElepfRelIso03_counter = 0;

			// vector<float> eleSelections = electronSelection(nElectron);
			// int NeleSelections = eleSelections.size();

		
			// if(eleSelections[NeleSelections] != 1) continue;  //at least 1 pfrel ele

			}




		for(int nTrig = 0; nTrig < m_triggers.size(); nTrig++){


			if(strstr(m_triggers.at(nTrig).c_str(),"Iso")){ //iso req for iso triggers
				if(!iso) continue;
			}


			bool bPassed = vec_ltrig.at(nTrig)->GetValue();

			if(strstr(m_triggers.at(nTrig).c_str(),"Double")){ //iso req for iso triggers
				if(!double_lep) continue;
				if(!METval) continue;
				if(!mHTval) continue;
				if(!invMuonMassval) continue;
				if(!invMuonpTval) continue;
				vec_eff.at(nTrig)->Fill((bPassed),l_Muonpt->GetValue(1));  //subleading lepton
			}
			else{
				vec_eff.at(nTrig)->Fill((bPassed),l_var->GetValue(0)); //leading lepton
			}
			
		}
	}
	cout << endl;

	return vec_eff;
}


inline void TriggerSet::make2DPlot(TEfficiency* eff){
	gStyle->SetPalette(kRainBow);
	gStyle->SetPaintTextFormat("0.2f");
	//GET EFFICIENCIES ON PLOT
	TCanvas* cv = new TCanvas("cv","cv",800,600);
	cv->cd();
	eff->Draw("colztext");
	cv->Update();
	
	TH2* h = eff->GetPaintedHistogram();
	
	
	cv->Update();

	TString g_PlotTitle = m_samplename+" Trigger Efficiencies";
	h->GetZaxis()->SetTitle((m_triggers.at(0)+" Efficiency").c_str());
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
		TString filename = ("/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/effPlots/"+m_outname).c_str();

		TFile* file = new TFile(filename,"RECREATE");
		cout << "file: " << filename << " created" << endl;
		file->cd();
		cv->Write();
	}
	else{
		return;
	}
}


inline void TriggerSet::makePlots(vector<TEfficiency*> effs){
	TCanvas* cv = new TCanvas("cv","cv",800,600);
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


	cout << "# of triggers: " << gr_effs.size() << endl;
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
	Int_t chopcolor = gr_effs.size()/3;
	Int_t chopmarker = gr_effs.size()/3;

	for(int i = 0; i < gr_effs.size(); i++){
		gr_effs[i]->SetMarkerSize(1.5);
		gr_effs[i]->SetLineWidth(2);
		gr_effs[i]->GetYaxis()->SetRangeUser(0.0,1.0);
		
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

	string g_PlotTitle = m_samplename+" Trigger Efficiencies";
	mg->GetXaxis()->SetTitle(m_var.c_str());
	mg->GetYaxis()->SetTitle("#epsilon");
	

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
		TString filename = ("/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/effPlots/"+m_outname).c_str();

		TFile* file = new TFile(filename,"RECREATE");
		cout << "file: " << filename << " created" << endl;
		file->cd();
		cv->Write();
	}
	else{
		return;
	}
	



}
