#include <iostream>

#include "../include/prod2016MC_reducedNANO_Triggers.h"
#include "../include/prod2017MC_reducedNANO_Triggers.h"
#include "../include/prod2018MC_reducedNANO_Triggers.h"
#include "../include/TriggerSet.hh"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TGraph.h"

using namespace std;

void Plot_Efficiency(){
	if(gSystem->OpenDirectory("plots") == 0){
		gSystem->mkdir("plots");
		cout << "Created plots folder." << endl;
	}

	TCanvas* cv = new TCanvas("cv","cv",600,600);
	TLegend* leg = new TLegend(0.688,0.22,0.93,0.42);
	vector<TEfficiency*> effs16;

	TString gPathname = "/home/t3-ku/mlazarov/CMSSW_10_1_4_patch1/src/ReducedNtuple/single_root_files/";
	// TString dyJets16Pathname = gPathname+"Summer16_94X_DYJetstoLL/root/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_94X/";
	// TString dyJets17Pathname = gPathname+"Fall17_94X_DYJetstoLL/root/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_94X/";
	// TString dyJets18Pathname = gPathname+"Autumn18_102X_DYJetstoLL/root/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8_Autumn18_102X/";

	TFile* file16 = TFile::Open(gPathname+"prod2016MC_reducedNANO_Triggers_DYinclusive.root");
	// TTree* tree16 = (TTree*)file16->Get("Events");
	



	// TString filename = "dyJetsToLL_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL";
	
	TriggerSet trigs16(file16);
	// file16->Close();
	// trigs16.AddFile(gPathname+dyJets16Pathname);
	trigs16.SetSampleName("DYJetstoLL, 2016");
	trigs16.AddTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
	trigs16.AddTrigger("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
	trigs16.AddTrigger("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL");
	trigs16.SetVar("Electron_pt");
	trigs16.SetOutputName("DYJets16_AllTrigs.root");
	string x_label = trigs16.GetVar();
	string title = trigs16.GetSampleName();
	effs16 = trigs16.Analyze();
	vector<TGraphAsymmErrors*> gr_effs16;
	TMultiGraph* mg = new TMultiGraph();


	cv->cd();
	cv->SetGridx();
	cv->SetGridy();

	effs16[0]->Draw("AP");
	cv->Update();
	gr_effs16.push_back(effs16[0]->GetPaintedGraph());
	for(int i = 1; i < effs16.size(); i++){
		effs16[i]->Draw("same");
		cv->Update();
		gr_effs16.push_back(effs16[i]->GetPaintedGraph());
	}


	cout << "# of triggers: " << gr_effs16.size() << endl;
	// double fmax = -1.;
	// int imax = -1;
	// for(int i = 0; i < gr_effs16.size(); i++){
	// 	if(gr_effs16[i]->GetMaximum() > fmax){
	// 		fmax = gr_effs16[i]->GetMaximum();
	// 		imax = i;
	// 	}
	// }
	// cout << "imax: " << endl;
	// gr_effs16[imax]->Draw();

	cv->Update();

	for(int i = 0; i < effs16.size(); i++){
		gr_effs16[i]->SetMarkerStyle(kCircle);
		if(i % 3 == 0){
			gr_effs16[i]->SetMarkerColor(kBlue-7);
			gr_effs16[i]->SetLineColor(kBlue-7);
		}
		if(i % 3 == 1){
			gr_effs16[i]->SetMarkerColor(kRed-7);
			gr_effs16[i]->SetLineColor(kRed-7);
		}
		if(i % 3 == 2){
			gr_effs16[i]->SetMarkerColor(kGreen-7);
			gr_effs16[i]->SetLineColor(kGreen-7);
		}
		// gr_effs16[i]->Draw("same");
		mg->Add(gr_effs16[i]);
		// cv->Update();
		leg->AddEntry(gr_effs16[i]);
	}
	mg->SetTitle((title+" Trigger Efficiencies").c_str());
	mg->GetXaxis()->SetTitle(x_label.c_str());
	mg->GetYaxis()->SetTitle("#epsilon");
	mg->SetMinimum(0.0);
	mg->SetMaximum(1.0);

	mg->Draw("SAME");
	leg->Draw("SAME");
	cv->Update();

	TLatex l;
	l.SetTextFont(132);
	l.SetNDC();
	l.SetTextSize(0.035);
	l.SetTextFont(42);
	l.SetTextSize(0.04);
	l.SetTextFont(61);
	l.DrawLatex(0.16,0.943,"CMS");
	l.SetTextFont(52);
	l.DrawLatex(0.23,0.943,"Preliminary");
	cv->Update();

	TFile* file = new TFile("EFFTEST.root","RECREATE");
	file->cd();
	cv->Write();
	
	
	cv->Close();
	file->Close();











	//DYJets2016

	// int nEntries16 = trigClass16->fChain->GetEntries();
	// TEfficiency* eff16 = new TEfficiency("eff","my_efficiency;x;#epsilon",20,0,2000);
	
	// bool trigPass16;
	// Float_t ele_pt16;
	// Float_t mu_pt16;

	// for(int evt = 0; evt < nEntries16; evt++){
	// 	trigClass16->GetEntry(evt);
	// 	for(int ele = 0; ele < Electron_pt.size(); ele++){
	// 		ele_pt16 = trigClass16->Electron_pt->at(ele);
	// 		// trigPass16 = trigClass16->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL == 1; //pass trigger

	// 		eff16->Fill(trigClass16->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL,ele_pt16);
	// 	}
	// }
	// eff16->SetFillColor(kGreen);
	// leg->AddEntry(eff16,"2016");
	// eff16->Draw("AP");

	// //DYJets2017
	// TChain* chain17 = new TChain("Events");		
	// chain17->Add(dyJets17Pathname+"*.root");

	// prod2017MC_reducedNANO_Triggers* trigClass17 = new prod2017MC_reducedNANO_Triggers(chain17);

	// int nEntries17 = trigClass17->fChain->GetEntries();
	// TEfficiency* eff17 = new TEfficiency("eff","my_efficiency;x;#epsilon",20,0,2000);
	
	// bool trigPass17;
	// Float_t ele_pt17;
	// Float_t mu_pt17;

	// for(int evt = 0; evt < nEntries17; evt++){
	// 	trigClass17->GetEntry(evt);
	// 	ele_pt17 = trigClass17->Electron_pt[0];
	// 	trigPass17 = trigClass17->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL == 1; //pass trigger

		
	// 	eff17->Fill(trigPass17,ele_pt17);

	// }
	// eff17->SetFillColor(kRed);
	// leg->AddEntry(eff17,"2017");
	// eff17->Draw("SAME");
	// // delete chain;

	// //DYJets2018
	// TChain* chain18 = new TChain("Events");		
	// chain18->Add(dyJets18Pathname+"*.root");

	// prod2018MC_reducedNANO_Triggers* trigClass18 = new prod2018MC_reducedNANO_Triggers(chain18);

	// int nEntries18 = trigClass18->fChain->GetEntries();
	// TEfficiency* eff18 = new TEfficiency("eff","my_efficiency;x;#epsilon",20,0,2000);
	
	// bool trigPass18;
	// Float_t ele_pt18;
	// Float_t mu_pt18;

	// for(int evt = 0; evt < nEntries18; evt++){
	// 	trigClass18->GetEntry(evt);
	// 	ele_pt18 = trigClass18->Electron_pt->at(0);
	// 	trigPass18 = trigClass18->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL == 1; //pass trigger

		
	// 	eff18->Fill(trigPass18,ele_pt18);
	// }
	// eff18->SetFillColor(kBlue);
	// leg->AddEntry(eff18,"2018");
	// eff18->Draw("SAME");

	// cv->SaveAs("plots/"+filename+".pdf");
	// cv->Close();
	// delete cv;
	// delete chain16;
	// delete chain17;
	// delete chain18;




	
}