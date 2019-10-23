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
	TLegend* leg = new TLegend(0.3,0.72,0.9,0.92);
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
		gr_effs16[i]->SetMarkerSize(1);
		gr_effs16[i]->SetLineWidth(4);
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
	leg->SetTextFont(132);
	leg->SetTextSize(0.045);
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);

	mg->Draw("AP");
	leg->Draw("SAME");
	cv->Update();

	mg->SetTitle((title+" Trigger Efficiencies").c_str());
	mg->GetXaxis()->SetTitle(x_label.c_str());
	mg->GetYaxis()->SetTitle("#epsilon");
	// mg->SetMinimum(0.0);
	// mg->SetMaximum(1.0);

	TLatex l;
	l.SetTextFont(132);
	l.SetNDC();
	l.SetTextSize(0.035);
	l.SetTextFont(42);
	l.SetTextSize(0.04);
	l.SetTextFont(61);
	l.DrawLatex(0.16,0.9,"CMS");
	l.SetTextFont(52);
	l.DrawLatex(0.25,0.9,"Preliminary");
	cv->Update();

	TFile* file = new TFile("EFFTEST.root","RECREATE");
	file->cd();
	cv->Write();
	
	
	cv->Close();
	file->Close();







	
}