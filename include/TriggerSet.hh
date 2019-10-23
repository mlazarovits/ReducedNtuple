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
	TriggerSet(TFile* file);
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

	vector<TEfficiency*> Analyze();



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

	// prod2016MC_reducedNANO_Triggers m_Triggers_2016(NULL);
	// prod2017MC_reducedNANO_Triggers m_Triggers_2017(NULL);
	// prod2018MC_reducedNANO_Triggers m_Triggers_2018(NULL);




};
#endif
// #define 

inline TriggerSet::TriggerSet(TFile* file){
	m_tree = (TTree*)file->Get("Events");
	if(m_tree == NULL){
		cout << "Error: No tree found" << endl;
	}
}


// inline TriggerSet::TriggerSet(prod2016MC_reducedNANO_Triggers trig16){
// 	m_Triggers_2016 = trig16;
// }

// inline TriggerSet::TriggerSet(prod2017MC_reducedNANO_Triggers trig17){
// 	m_Triggers_2017 = trig17;
// }

// inline TriggerSet::TriggerSet(prod2016MC_reducedNANO_Triggers trig18){
// 	m_Triggers_2018 = trig18;
// }



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

inline vector<TEfficiency*> TriggerSet::Analyze(){


	// TBranch* b_var = m_tree->GetBranch(m_var.c_str());
	// TBranch* b_weight = m_tree->GetBranch("Generator_weight");
	TLeaf* l_var = m_tree->GetLeaf(m_var.c_str());
	TLeaf* l_weight = m_tree->GetLeaf("Generator_weight");
	vector<TEfficiency*> vec_eff;
	vector<TLeaf*> vec_ltrig;
	int nEntries;
	if(l_var == NULL){
		cout << "Error: Variable " << m_var.c_str() << " not found" << endl;
		return vec_eff;
	}

	for(int i = 0; i < m_triggers.size(); i++){
		string title = (m_var+" vs."+m_triggers.at(i)+" Efficiency").c_str();
		string x_label = (";"+m_var).c_str();
		string y_label = ";#epsilon";
		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(title+x_label+y_label).c_str(),20,0,200);
		TLeaf* l_trig = m_tree->GetLeaf(m_triggers.at(i).c_str());
		if(l_trig == NULL){
			cout << "Error: Trigger " << m_triggers.at(i) << " not found" << endl;
			return vec_eff;
		}
		vec_eff.push_back(eff);
		vec_ltrig.push_back(l_trig);
	}

	nEntries = m_tree->GetEntries();
	for(int evt = 0; evt < nEntries; evt++){
		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);
	    cout << "\n" << endl;

		for(int nTrig = 0; nTrig < m_triggers.size(); nTrig++){
			// vec_branch.at(i)->GetBranch()->GetEntry(evt);
			vec_eff.at(nTrig)->Fill(vec_ltrig.at(nTrig)->GetValue(),l_var->GetValue());
		}
	}


	// //2017
	// if(m_Triggers_2016 == NULL && m_Triggers_2017 != NULL && m_Triggers_2018 == NULL){
	// 	TLeaf* var_leaf = m_Triggers_2017->GetLeaf(m_var.c_str());
	// 	TLeaf* weight_leaf = m_Triggers_2017->GetLeaf("Generator_weight");
	// 	vector<TEfficiency*> vec_eff;
	// 	vector<TLeaf*> vec_leaf;
	// 	int nEntries;

	// 	for(int i = 0; i < m_triggers.size(); i++){
	// 		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(m_triggers.at(i)+" vs. "+m_var" Efficiency").c_str(),20,0,200);
	// 		TLeaf* leaf = m_Triggers_2017->GetLeaf(m_triggers.at(i).c_str());
	// 		vec_eff.push_back(eff);
	// 		vec_leaf.push_back(leaf);
	// 	}

	// 	nEntries = m_Triggers_2017->GetEntries();
	// 	for(evt = 0; evt < nEntries; evt++){
	// 		var_leaf->GetBranch()->GetEntry(evt);
	// 		weight_leaf->GetBranch()->GetEntru(evt);
	// 		for(nTrig = 0; nTrig < m_triggers.size(); nTrig++){
	// 			vec_leaf.at(i)->GetBranch->GetEntry(evt);
	// 			vec_eff.at(i)->Fill(vec_leaf.at(nTrig)->GetValue(),var_leaf->GetValue());
	// 		}
	// 	}
	// }



	// //2018
	// if(m_Triggers_2016 == NULL && m_Triggers_2017 == NULL && m_Triggers_2018 != NULL){
	// 	TLeaf* var_leaf = m_Triggers_2018->GetLeaf(m_var.c_str());
	// 	TLeaf* weight_leaf = m_Triggers_2018->GetLeaf("Generator_weight");
	// 	vector<TEfficiency*> vec_eff;
	// 	vector<TLeaf*> vec_leaf;
	// 	int nEntries;

	// 	for(int i = 0; i < m_triggers.size(); i++){
	// 		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(m_triggers.at(i)+" vs. "+m_var" Efficiency").c_str(),20,0,200);
	// 		TLeaf* leaf = m_Triggers_2018->GetLeaf(m_triggers.at(i).c_str());
	// 		vec_eff.push_back(eff);
	// 		vec_leaf.push_back(leaf);
	// 	}

	// 	nEntries = m_Triggers_2018->GetEntries();
	// 	for(evt = 0; evt < nEntries; evt++){
	// 		var_leaf->GetBranch()->GetEntry(evt);
	// 		weight_leaf->GetBranch()->GetEntru(evt);
	// 		for(nTrig = 0; nTrig < m_triggers.size(); nTrig++){
	// 			vec_leaf.at(i)->GetBranch->GetEntry(evt);
	// 			vec_eff.at(i)->Fill(vec_leaf.at(nTrig)->GetValue(),var_leaf->GetValue());
	// 		}
	// 	}
	// }	
	return vec_eff;
}

inline bool TriggerSet::global_cuts(const Long64_t& jentry, double x_val)
{
 bool cut = true;
 TLeaf* leaf = m_tree->GetLeaf(m_var.c_str());
 leaf->GetBranch()->GetEntry(jentry);
 if(x_val/leaf->GetValue() < 5.) cut = false;
 return cut;
}