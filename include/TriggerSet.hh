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

class TriggerClass{
public:
	TriggerSet(TFile* file);
	// TriggerSet(prod2016MC_reducedNANO_Triggers trig16);
	// TriggerSet(prod2016MC_reducedNANO_Triggers trig17);
	// TriggerSet(prod2016MC_reducedNANO_Triggers trig18);
	virtual ~TriggerSet();

	void AddFile(const string& filename);
	int GetNFile() const;
	string GetFile(int n);

	void SetSampleName(const string& samplename);
	string GetSampleName() const;

	void SetOutputName(const string& outname);
	string GetOutputName() const;

	void SetTriggers(vector<string> triggers);
	vector<string> GetTriggers();

	void SetVar(string var);
	string GetVar();

	vector<TEfficiency*> Analyze();



	bool global_cuts(TTree*& fChain, const Long64_t& jentry, double x_val);


private:
	string m_samplename;
	string m_trigname;
	string m_outname;
	TTree* m_tree;
	// TChain* m_chain;
	vector<string> m_triggers;
	string m_var;
	vector<string> m_FileNames;

	prod2016MC_reducedNANO_Triggers m_Triggers_2016(NULL);
	prod2017MC_reducedNANO_Triggers m_Triggers_2017(NULL);
	prod2018MC_reducedNANO_Triggers m_Triggers_2018(NULL);




};
#endif
// #define 

inline TriggerSet::TriggerSet(TFile* file){
	m_tree = (TTree*)file->Get("Events");
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
  return m_FileNames.size();
}
inline string TriggerSet::GetFile(int n){
  int N = GetNFile();
  if(n < 0 || n >= N)
    return "NO FILE";
  return m_FileNames[n];
}




inline void TriggerSet::SetSampleName(const string& samplename){
	m_samplename = samplename;
}

inline string TriggerSet::GetSampleName() const{
	return m_samplename;
}

inline void TriggerSet::SetOutputName(const string& outname){
	m_outname = outname
}
inline string TriggerSet::GetOutputName() const {
	return m_outname
}




inline void TriggerSet::SetTriggers(vector<string> triggers){
	m_triggers.push_back(triggers);
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


	TBranch* b_var = m_tree->GetBranch(m_var.c_str());
	TBranch* b_weight = m_tree->GetBranch("Generator_weight");
	vector<TEfficiency*> vec_eff;
	vector<TBranch*> vec_btrig;
	int nEntries;

	for(int i = 0; i < m_triggers.size(); i++){
		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(m_triggers.at(i)+" vs. "+m_var" Efficiency").c_str(),20,0,200);
		TBranch* b_trig = m_tree->GetBranch(m_triggers.at(i).c_str());
		vec_eff.push_back(eff);
		vec_btrig.push_back(b_trig);
	}

	nEntries = m_tree->GetEntries();
	for(evt = 0; evt < nEntries; evt++){
		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);

		for(nTrig = 0; nTrig < m_triggers.size(); nTrig++){
			// vec_branch.at(i)->GetBranch()->GetEntry(evt);
			vec_eff.at(i)->Fill(m_tree->vec_btrig.at(nTrig),m_tree->b_var);
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

inline bool TriggerSet::global_cuts(TTree*& fChain, const Long64_t& jentry, double x_val)
{
 bool cut = true;
 TLeaf* leafr = fChain->GetLeaf(m_var);
 lear->GetBranch()->GetEntry(jentry);
 if(x_val/leaf->GetValue() < 5.) cut = false;
 return cut;
}