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
#include "TEfficiency.h"


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

	void makePlots(vector<TEfficiency*> effs);


	bool global_cuts(const Long64_t& jentry, double x_val);


private:
	string m_samplename;
	string m_trigname;
	string m_outname;
	TTree* m_tree;
	string m_var;

	// TChain* m_chain;
	vector<string> m_triggers;
	
	vector<string> m_filenames;

	bool debug;

	// prod2016MC_reducedNANO_Triggers m_Triggers_2016(NULL);
	// prod2017MC_reducedNANO_Triggers m_Triggers_2017(NULL);
	// prod2018MC_reducedNANO_Triggers m_Triggers_2018(NULL);




};
#endif
// #define 

inline TriggerSet::TriggerSet(TFile* file,bool i_debug=false){
	m_tree = (TTree*)file->Get("Events");
	if(m_tree == NULL){
		cout << "Error: No tree found" << endl;
	}
	i_debug = debug;
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

		// sscanf(trigger.c_str(),choptrig,str_trig[i]); //scan for triggers and store them in separate strings
		
		// for(int i = 0; i < nTrigOR; i++){ //add to vector
		// 	TLeaf* l_temp = m_tree->GetLeaf(str_trig[i]);
		// 	vec_trig.push_back(l_temp);
		// 	delete l_temp;
		// }

	return vec_trig;
}

inline vector<TEfficiency*> TriggerSet::Analyze(){
	vector<TEfficiency*> vec_eff;
	vector<TLeaf*> vec_ltrig;
	
	TLeaf* l_nMuon = m_tree->GetLeaf("nMuon");
	TLeaf* l_Muon_mediumId = m_tree->GetLeaf("Muon_mediumId");
	TLeaf* l_Muon_mediumPromptId = m_tree->GetLeaf("Muon_mediumPromptId");
	TLeaf* l_Muon_tightId = m_tree->GetLeaf("Muon_tightId");
	TLeaf* l_Muon_miniIsoId = m_tree->GetLeaf("Muon_miniIsoId");

	TLeaf* l_nElectron = m_tree->GetLeaf("nElectron");
	TLeaf* l_Electron_mediumId = m_tree->GetLeaf("Electron_mediumId");
	TLeaf* l_Electron_mediumPromptId = m_tree->GetLeaf("Electron_mediumPromptId");
	TLeaf* l_Electron_tightId = m_tree->GetLeaf("Electron_tightId");
	TLeaf* l_Electron_miniIsoId = m_tree->GetLeaf("Electron_miniIsoId");
	
	TLeaf* l_var = m_tree->GetLeaf(m_var.c_str());
	TLeaf* l_weight = m_tree->GetLeaf("Generator_weight");

	int nEntries;
	if(l_var == NULL){
		cout << "Error: Variable " << m_var.c_str() << " not found" << endl;
		return vec_eff;
	}

	//create TEfficiency objects and get trigger leaves
	for(int i = 0; i < m_triggers.size(); i++){
		string title = (m_var+" vs."+m_triggers.at(i)+" Efficiency").c_str();
		string x_label = (";"+m_var).c_str();
		string y_label = ";#epsilon";
		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(m_triggers.at(i)).c_str(),100,0,200);
		
		//scan for trigger ORs and ANDs
		// if(strstr(m_triggers.at(i).c_str(),"||")) //OR triggers			
	
		// else if(strstr(m_triggers.at(i).c_str(),"&&")) //AND triggers
		
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
		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);

		for(int nTrig = 0; nTrig < m_triggers.size(); nTrig++){
			//VARIABLE SELECTION - MUON
			if(strstr(m_var.c_str(),"Muon")){

				int nMuon = l_nMuon->GetValue();
				if(nMuon != 1) continue; //exactly 1 muon
				int MuonmediumId_counter = 0;
				int MuontightId_counter = 0;
				int MuonmedpromptId_counter = 0;
				int muonminiIso_counter = 0;


				for(int i = 0; i < nMuon; i++){
					// cout << "med id: " << l_Muon_mediumId->GetValue(i) << endl;
					if(l_Muon_mediumId->GetValue(i) == true) MuonmediumId_counter += 1;
					else if(l_Muon_tightId->GetValue(i) == true) MuontightId_counter += 1;
					else if(l_Muon_mediumPromptId->GetValue(i) == true) MuonmedpromptId_counter += 1;
					if(l_Muon_miniIsoId->GetValue(i) == 2) muonminiIso_counter += 1; //1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight
					// else continue;	
				}

				// if(MuonmediumId_counter < 1) continue;  //at least 1 mediumId muon
				// if(MuontightId_counter < 1) continue; //at least 1 tightId muon
				if(nTrig == 0 || nTrig == 1){ //only apply iso selection to triggers with that
					if(muonminiIso_counter != 1) continue; //exactly 1 miniIsoId muon
				}	
				
			}
			//VARIABLE SELECTION - ELECTRON
			if(strstr(m_var.c_str(),"Electron")){

				int nElectron = l_nElectron->GetValue();
				if(nElectron < 1) continue; //at least 1 muon
				// int ElemediumId_counter = 0;
				// int EletightId_counter = 0;
				// int ElemedpromptId_counter = 0;

				//replace with electron IDs
				// for(int i = 0; i < nElectron; i++){
				// // cout << "med id: " << l_Muon_mediumId->GetValue(i) << endl;
				// if(l_Electron_mediumId->GetValue(i) == true) ElemediumId_counter += 1;
				// if(l_Electron_tightId->GetValue(i) == true) EletightId_counter += 1;
				// if(l_Electron_mediumPromptId->GetValue(i) == true) ElemedpromptId_counter += 1;
				// else continue;	
				// }

				// if(ElemediumId_counter < 1) continue;  //at least 1 mediumId muon
				// if(EletightId_counter < 1) continue; //at least 1 tightId muon

				// if(l_Muon_miniIsoId != 2) continue; //medium miniIsoId
			}

			

			bool bPassed = vec_ltrig.at(nTrig)->GetValue();

			
			vec_eff.at(nTrig)->Fill((bPassed),l_var->GetValue());
		}
	}
	cout << endl;


	
	return vec_eff;
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

	for(int i = 0; i < gr_effs.size(); i++){
		gr_effs[i]->SetMarkerSize(1.5);
		gr_effs[i]->SetLineWidth(2);
		if(i/3 == 0){
			gr_effs[i]->SetMarkerStyle(22);
		} 
		else {
			gr_effs[i]->SetMarkerStyle(21);
		}
		if(i % 3 == 0){
			gr_effs[i]->SetMarkerColor(kBlue-7);
			gr_effs[i]->SetLineColor(kBlue-7);
		}
		if(i % 3 == 1){
			gr_effs[i]->SetMarkerColor(kRed-7);
			gr_effs[i]->SetLineColor(kRed-7);
		}
		if(i % 3 == 2){
			gr_effs[i]->SetMarkerColor(kGreen-7);
			gr_effs[i]->SetLineColor(kGreen-7);
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
	// mg->SetMinimum(0.0);
	// mg->SetMaximum(1.0);

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

	TString filename = ("/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/effPlots/"+m_outname).c_str();

	TFile* file = new TFile(filename,"RECREATE");
	cout << "file: " << filename << " created" << endl;
	file->cd();
	cv->Write();



}

inline bool TriggerSet::global_cuts(const Long64_t& jentry, double x_val)
{
 bool cut = true;
 TLeaf* leaf = m_tree->GetLeaf(m_var.c_str());
 leaf->GetBranch()->GetEntry(jentry);
 if(x_val/leaf->GetValue() < 5.) cut = false;
 return cut;
}