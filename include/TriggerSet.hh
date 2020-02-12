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
	std::vector<float> muonSelection(int nMuon);
	std::vector<float> electronSelection(int nElectron);

	string m_samplename;
	string m_trigname;
	string m_outname;
	TTree* m_tree;
	string m_var;

	TLeaf* l_nMuon;
	TLeaf* l_Muon_mediumId;
	TLeaf* l_Muon_mediumPromptId;
	TLeaf* l_Muon_tightId;
	TLeaf* l_Muon_miniIsoId;
	TLeaf* l_Muon_minipfRelIso_all;
	TLeaf* l_Muonpt;
	TLeaf* l_Muoneta;
	TLeaf* l_nElectron;
	TLeaf* l_Electron_pfRelIso03_all;
	
	TLeaf* l_var;
	TLeaf* l_weight;

	// TChain* m_chain;
	vector<string> m_triggers;
	
	vector<string> m_filenames;

	bool debug=false;

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

		// sscanf(trigger.c_str(),choptrig,str_trig[i]); //scan for triggers and store them in separate strings
		
		// for(int i = 0; i < nTrigOR; i++){ //add to vector
		// 	TLeaf* l_temp = m_tree->GetLeaf(str_trig[i]);
		// 	vec_trig.push_back(l_temp);
		// 	delete l_temp;
		// }

	return vec_trig;
}

inline std::vector<float> TriggerSet::muonSelection(int nMuon){
	std::vector<float> muselections;

	float MuonmediumId_counter = 0;
	float MuontightId_counter = 0;
	float MuonmedpromptId_counter = 0;
	float muonminiIso_counter = 0;
	float muonminipfRelIso_counter = 0;
	float mu_pt = -9999;
	float mu_eta = -9999;
	
		
	

	for(int i = 0; i < nMuon; i++){
		// cout << "med id: " << l_Muon_mediumId->GetValue(i) << endl;
		if(l_Muon_mediumId->GetValue(i) == true) MuonmediumId_counter += 1;
		if(l_Muon_tightId->GetValue(i) == true) MuontightId_counter += 1;
		if(l_Muon_mediumPromptId->GetValue(i) == true) MuonmedpromptId_counter += 1;
		if(l_Muon_miniIsoId->GetValue(i) == 4) muonminiIso_counter += 1; //1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight
		if(l_Muon_minipfRelIso_all->GetValue(i) < 0.1) muonminipfRelIso_counter += 1;
	
	}
	//if(eta){
	mu_pt = l_Muonpt->GetValue(0); //pt of leading muon
	mu_eta = l_Muoneta->GetValue(0); //eta of leading muon
	//}

	muselections.push_back(MuonmediumId_counter);
	muselections.push_back(MuontightId_counter);
	muselections.push_back(MuonmedpromptId_counter);
	muselections.push_back(muonminiIso_counter);
	muselections.push_back(muonminipfRelIso_counter);
	muselections.push_back(mu_pt);
	muselections.push_back(mu_eta);


	return muselections;

}

inline std::vector<float> TriggerSet::electronSelection(int nElectron){
	std::vector<float> eleselections;

	float ElemediumId_counter = 0;
	float EletightId_counter = 0;
	float ElemedpromptId_counter = 0;
	float ElepfRelIso03_counter = 0;


	//replace with electron IDs
	for(int i = 0; i < nElectron; i++){
	// cout << "med id: " << l_Muon_mediumId->GetValue(i) << endl;
		if(l_Electron_pfRelIso03_all->GetValue(i) < 0.1) ElepfRelIso03_counter += 1;
		
	}



	eleselections.push_back(ElemediumId_counter);
	eleselections.push_back(EletightId_counter);
	eleselections.push_back(ElemedpromptId_counter);
	eleselections.push_back(ElepfRelIso03_counter);

	return eleselections;
}



inline vector<TEfficiency*> TriggerSet::Analyze(){
	vector<TEfficiency*> vec_eff;
	vector<TLeaf*> vec_ltrig;
	
	l_nMuon = m_tree->GetLeaf("nMuon");
	l_Muonpt = m_tree->GetLeaf("Muon_pt");
	l_Muoneta = m_tree->GetLeaf("Muon_eta");
	l_Muon_mediumId = m_tree->GetLeaf("Muon_mediumId");
	l_Muon_mediumPromptId = m_tree->GetLeaf("Muon_mediumPromptId");
	l_Muon_tightId = m_tree->GetLeaf("Muon_tightId");
	l_Muon_miniIsoId = m_tree->GetLeaf("Muon_miniIsoId");
	l_Muon_minipfRelIso_all = m_tree->GetLeaf("Muon_miniPFRelIso_all");

	l_nElectron = m_tree->GetLeaf("nElectron");
	l_Electron_pfRelIso03_all = m_tree->GetLeaf("Muon_pfRelIso03_all");
	
	l_var = m_tree->GetLeaf(m_var.c_str());
	l_weight = m_tree->GetLeaf("Generator_weight");

	int nEntries;
	if(l_var == NULL){
		cout << "Error: Variable " << m_var.c_str() << " not found" << endl;
		return vec_eff;
	}


	Int_t nBins;		
	std::vector<Double_t> effbins;
	//set bins of TEff object
	if(strstr(m_var.c_str(),"pt")){
		nBins = 70;
		effbins.push_back(0.0);
		for(int i = 1; i < 51; i++){
			effbins.push_back(effbins.at(i-1) + 2.0);
		}
		for(int i = 51; i < nBins+2; i++){
			effbins.push_back(effbins.at(i-1) + 10.0);
		}
	}
	if(strstr(m_var.c_str(),"eta")){
		nBins = 200;
		effbins.push_back(-3.05);
		for(int i = 1; i < nBins+2; i++){
			effbins.push_back(effbins.at(i-1) + 0.05);
			// cout << effbins.at(i) << endl;
		}
	}


	//create TEfficiency objects and get trigger leaves
	for(int i = 0; i < m_triggers.size(); i++){
		string title = (m_var+" vs."+m_triggers.at(i)+" Efficiency").c_str();
		string x_label = (";"+m_var).c_str();
		string y_label = ";#epsilon";
		TEfficiency* eff = new TEfficiency(m_triggers.at(i).c_str(),(m_triggers.at(i)).c_str(),nBins,&effbins.at(0));
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
	

	bool iso = false;

	for(int evt = 0; evt < nEntries; evt++){
		m_tree->GetEntry(evt);
		if (evt % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", evt, nEntries);
		}
	    fflush(stdout);


	    if(strstr(m_var.c_str(),"Muon")){
		    int nMuon = l_nMuon->GetValue();
			if(nMuon != 1) continue; 

			// muselections.push_back(MuonmediumId_counter);
			// muselections.push_back(MuontightId_counter);
			// muselections.push_back(MuonmedpromptId_counter);
			// muselections.push_back(muonminiIso_counter);
			// muselections.push_back(muonminipfRelIso_counter);
			// muselections.push_back(mu_pt);
			// muselections.push_back(mu_eta);


			vector<float> muonSelections = muonSelection(nMuon);
			int NmuonSelections = muonSelections.size();


			if(strstr(m_var.c_str(),"eta")){
				if(muonSelections.at(NmuonSelections-2) < 200) continue; //mupt cut
			}
			else if(strstr(m_var.c_str(),"pt")){
				if(abs(muonSelections.at(NmuonSelections-1)) > 1.5) continue;
			}

			if(muonSelections.at(4) >= 1) iso = true;
				
			

		}

		if(strstr(m_var.c_str(),"Electron")){

			int nElectron = l_nElectron->GetValue();
			if(nElectron != 1) continue; //at least 1 electron

			// int ElemediumId_counter = 0;
			// int EletightId_counter = 0;
			// int ElemedpromptId_counter = 0;
			// int ElepfRelIso03_counter = 0;

			vector<float> eleSelections = electronSelection(nElectron);
			int NeleSelections = eleSelections.size();

		
			if(eleSelections[NeleSelections] != 1) continue;  //at least 1 pfrel ele

			}

		for(int nTrig = 0; nTrig < m_triggers.size(); nTrig++){
			if(strstr(m_triggers.at(nTrig).c_str(),"Iso")){
				if(!iso) continue;
				// if(iso) cout << "iso passed " << evt << endl;
			}
			bool bPassed = vec_ltrig.at(nTrig)->GetValue();
			// cout << bPassed << endl;
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
	Int_t chopcolor = gr_effs.size()/2;
	Int_t chopmarker = gr_effs.size()/3;

	for(int i = 0; i < gr_effs.size(); i++){
		gr_effs[i]->SetMarkerSize(1.5);
		gr_effs[i]->SetLineWidth(2);
		
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

inline bool TriggerSet::global_cuts(const Long64_t& jentry, double x_val)
{
 bool cut = true;
 TLeaf* leaf = m_tree->GetLeaf(m_var.c_str());
 leaf->GetBranch()->GetEntry(jentry);
 if(x_val/leaf->GetValue() < 5.) cut = false;
 return cut;
}