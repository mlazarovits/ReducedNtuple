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

	
	vector<TEfficiency*> effs;

	string gPathname = "/home/t3-ku/mlazarov/CMSSW_10_6_5/src/ReducedNtuple/";

	TFile* file16 = TFile::Open((gPathname+"single_root_files/prod2016MC_reducedNANO_Triggers_DYinclusive.root").c_str());
	TFile* file17 = TFile::Open((gPathname+"single_root_files/prod2017MC_reducedNANO_Triggers_DYinclusive.root").c_str());
	TFile* f_wjets17 = TFile::Open(gPathname+"output/wjets17.root").c_str();
	// TTree* tree16 = (TTree*)file16->Get("Events");
	
	
	//DY incl. - 2016
	TriggerSet trigs16(file16);
	trigs16.SetSampleName("DYJetstoLL 2016");
	trigs16.AddTrigger("HLT_Ele27_WPTight_Gsf"); //isolated
	trigs16.AddTrigger("HLT_Ele25_eta2p1_WPTight_Gsf"); 
	// trigs16.AddTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
	// trigs16.AddTrigger("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
	// trigs16.AddTrigger("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL");
	trigs16.SetVar("Electron_pt");
	trigs16.SetOutputName("DYJets16_AllTrigs_ElepT.root");

	// effs = trigs16.Analyze();

	//DY incl. - 2017
	// TriggerSet dytrigs17(file17);
	// dytrigs17.SetSampleName("DYJetstoLL 2017");
	// dytrigs17.AddTrigger("HLT_IsoMu24");
	// dytrigs17.AddTrigger("HLT_Mu50");
	// dytrigs17.AddTrigger("HLT_Mu55");
	// dytrigs17.SetVar("Muon_pt");
	// dytrigs17.SetOutputName("DYJets17_AllTrigs_MupT.root");

	TriggerSet wjets17_trigs(f_wjets17);
	wjets17_trigs.SetSampleName("WJetsToLNu 2017");
	wjets17_trigs.AddTrigger("HLT_IsoMu24");
	wjets17_trigs.AddTrigger("HLT_Mu50");
	wjets17_trigs.AddTrigger("HLT_Mu55");
	wjets17_trigs.SetVar("Muon_pt");
	wjets17_trigs.SetOutputName("WJets17_AllTrigs_MupT.root");


	string x_label = wjets17_trigs.GetVar();
	string title = wjets17_trigs.GetSampleName();
	effs = wjets17_trigs.Analyze();





	wjets17_trigs.makePlots(effs);


	// vector<TGraphAsymmErrors*> gr_effs;
	// TMultiGraph* mg = new TMultiGraph();


	// cv->cd();
	// cv->SetGridx();
	// cv->SetGridy();
	// cv->SetLeftMargin(0.13);
	// cv->SetRightMargin(0.04);
	// cv->SetBottomMargin(0.15);
	// cv->SetTopMargin(0.085);

	// effs[0]->Draw("AP");
	// cv->Update();
	// gr_effs.push_back(effs[0]->GetPaintedGraph());
	// for(int i = 1; i < effs.size(); i++){
	// 	effs[i]->Draw("same");
	// 	cv->Update();
	// 	gr_effs.push_back(effs[i]->GetPaintedGraph());
	// }


	// cout << "# of triggers: " << gr_effs.size() << endl;
	// // double fmax = -1.;
	// // int imax = -1;
	// // for(int i = 0; i < gr_effs.size(); i++){
	// // 	if(gr_effs[i]->GetMaximum() > fmax){
	// // 		fmax = gr_effs[i]->GetMaximum();
	// // 		imax = i;
	// // 	}
	// // }
	// // cout << "imax: " << endl;
	// // gr_effs[imax]->Draw();

	// cv->Update();

	// for(int i = 0; i < gr_effs.size(); i++){
	// 	gr_effs[i]->SetMarkerSize(2);
	// 	gr_effs[i]->SetLineWidth(2);
	// 	if(i/3 == 0){
	// 		gr_effs[i]->SetMarkerStyle(22);
	// 	} 
	// 	else {
	// 		gr_effs[i]->SetMarkerStyle(21);
	// 	}
	// 	if(i % 3 == 0){
	// 		gr_effs[i]->SetMarkerColor(kBlue-7);
	// 		gr_effs[i]->SetLineColor(kBlue-7);
	// 	}
	// 	if(i % 3 == 1){
	// 		gr_effs[i]->SetMarkerColor(kRed-7);
	// 		gr_effs[i]->SetLineColor(kRed-7);
	// 	}
	// 	if(i % 3 == 2){
	// 		gr_effs[i]->SetMarkerColor(kGreen-7);
	// 		gr_effs[i]->SetLineColor(kGreen-7);
	// 	}
	// 	// gr_effs[i]->Draw("same");
	// 	mg->Add(gr_effs[i]);
	// 	// cv->Update();
	// 	leg->AddEntry(gr_effs[i]);
	// }
	// leg->SetTextFont(132);
	// leg->SetTextSize(0.03);
	// leg->SetFillColor(kWhite);
	// leg->SetLineColor(kWhite);
	// leg->SetShadowColor(kWhite);

	// mg->Draw("AP");
	// leg->Draw("SAME");
	// cv->Update();

	// string g_PlotTitle = title+" Trigger Efficiencies";
	// mg->GetXaxis()->SetTitle(x_label.c_str());
	// mg->GetYaxis()->SetTitle("#epsilon");
	// // mg->SetMinimum(0.0);
	// // mg->SetMaximum(1.0);

	// TLatex l;
	// l.SetTextFont(132);
	// l.SetNDC();
	// l.SetTextSize(0.035);
	// l.SetTextFont(42);
	// l.SetTextSize(0.03);
	// l.SetTextFont(61);
	// l.DrawLatex(0.16,0.92,"CMS");
	// l.SetTextFont(52);
	// l.DrawLatex(0.21,0.92,"Preliminary");
	// l.SetTextFont(132);
	// l.SetNDC();
	// l.SetTextSize(0.05);
	// l.SetTextFont(132);
	// l.DrawLatex(0.40,0.92,g_PlotTitle.c_str());
	// cv->Update();

	// TFile* file = new TFile((gPathname+"effPlots/"+wjets17_trigs.GetOutputName()).c_str(),"RECREATE");
	// file->cd();
	// cv->Write();
	
	
	// // cv->Close();
	// // file->Close();







	
}