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
	TriggerSet(){};
	TriggerSet(prod2016MC_reducedNANO_Triggers trig16);
	TriggerSet(prod2016MC_reducedNANO_Triggers trig17);
	TriggerSet(prod2016MC_reducedNANO_Triggers trig18);
	virtual ~TriggerSet();

	void AddFile(const string& filename);
	int GetNFile() const;
	string GetFile(int n);

	void SetTitle(const string& title);
	string GetTitle() const;

	void SetTriggers(vector<string> triggers);
	vector<string> GetTriggers();

	void SetVar(string var);
	string GetVar();

	TEfficiency* Analyze();



	bool global_cuts(TTree*& fChain, const Long64_t& jentry, double x_val);


private:
	string m_title;
	vector<string> m_triggers;
	string m_var;
	vector<string> m_FileNames;

	prod2016MC_reducedNANO_Triggers m_Triggers_2016(NULL);
	prod2017MC_reducedNANO_Triggers m_Triggers_2017(NULL);
	prod2018MC_reducedNANO_Triggers m_Triggers_2018(NULL);




};
#endif
// #define 


inline TriggerSet::TriggerSet(prod2016MC_reducedNANO_Triggers trig16){
	m_Triggers_2016 = trig16;
}

inline TriggerSet::TriggerSet(prod2017MC_reducedNANO_Triggers trig17){
	m_Triggers_2017 = trig17;
}

inline TriggerSet::TriggerSet(prod2016MC_reducedNANO_Triggers trig18){
	m_Triggers_2018 = trig18;
}

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


inline void TriggerSet::SetTitle(const string& title){
	title = m_title;
}

inline string TriggerSet::GetTitle() const{
	return m_title;
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

inline TEfficiency* TriggerSet::Analyze(TChain* chain){
	TLeaf* var_leaf = chain->GetLeaf(m_var.c_str());
	TLeaf* weight_leaf = chain->GetLeaf("")

}

inline bool TriggerSet::global_cuts(TTree*& fChain, const Long64_t& jentry, double x_val)
{
 bool cut = true;
 TLeaf* leafr = fChain->GetLeaf(m_var);
 lear->GetBranch()->GetEntry(jentry);
 if(x_val/leaf->GetValue() < 5.) cut = false;
 return cut;
}