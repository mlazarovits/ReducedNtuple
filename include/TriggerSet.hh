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
		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(m_triggers.at(i)).c_str(),20,0,200);
		TLeaf* l_trig = m_tree->GetLeaf(m_triggers.at(i).c_str());
		if(l_trig == NULL){
			cout << "Error: Trigger " << m_triggers.at(i) << " not found" << endl;
			return vec_eff;
		}
		vec_eff.push_back(eff);
		vec_ltrig.push_back(l_trig);
	}

	nEntries = m_tree->GetEntries();
	for(int evt = 0; evt < 100000; evt++){
		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);

		for(int nTrig = 0; nTrig < m_triggers.size(); nTrig++){
			// vec_branch.at(i)->GetBranch()->GetEntry(evt);
			vec_eff.at(nTrig)->Fill((vec_ltrig.at(nTrig)->GetValue()),l_var->GetValue());
		}
	}
	cout << endl;


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
		gr_effs[i]->SetMarkerSize(2);
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

	string filename = ("/home/t3-ku/mlazarov/CMSSW_10_1_4_patch1/src/ReducedNtuple/effPlots/"+m_outname+".root").c_str()

	TFile* file = new TFile(filename,"RECREATE");
	cout << "file: " << filename << "created" << endl;
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