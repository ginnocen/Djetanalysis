#include <TChain.h>
#include "TBranch.h"
#include "TLeaf.h"
#include <TFile.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>

using namespace std;

list<string> triggerBranchList;

void getTriggerList(TTree *tin){
	
	TBranch* branch = 0;
	TIter nextb(tin->GetListOfBranches());
	while ((branch = (TBranch*) nextb())) {
		string branchName(branch->GetName());
		std::size_t versLoc = branchName.find("_v");
		
		//Find both before and after the version number to make sure the prescales are kept...
		if(versLoc!=string::npos){
			string branchSubName = branchName.substr(0,versLoc) + branchName.substr(versLoc+3);
			triggerBranchList.push_back(branchSubName);
		}
		else{
			triggerBranchList.push_back(branchName);
		}
	
	}
}

TBranch *smartBranchFind(TChain *ch, string branchname){

	TObjArray *branches = ch->GetTree()->GetListOfBranches();
	int nb = branches->GetEntriesFast();
	for(int ibranch=0; ibranch<nb; ibranch++){
		
		TBranch *origBranch = (TBranch*)branches->UncheckedAt(ibranch);
				
		string inBranchName(origBranch->GetName());
		bool isPrescale=false;
		std::size_t psLoc = inBranchName.find("_Prescl");
		if(psLoc!=string::npos) isPrescale=true;
		
		std::size_t versLoc = inBranchName.find("_v");
		string shortName = inBranchName.substr(0,versLoc);
		if(isPrescale && versLoc!=string::npos) shortName+=inBranchName.substr(psLoc);
		if(shortName.compare(branchname)==0){
			return origBranch;
		}
	}
	
	cout << "Warning! Could not find " << branchname << endl;
	return 0;
	
}

void mergeTriggerTree(TChain *ch, TFile *outFile){
	
	TTree *tout = new TTree("HltTree","");	
	cout << "tree entries: " << ch->GetEntries() << endl;
		
	if(!triggerBranchList.size()){
		cout << " Warning! No triggers found!!" << endl;
		exit(0);
	}
	
	TBranch *brToAdd[triggerBranchList.size()];
	TBranch *oldBranch[triggerBranchList.size()];
	int valArray[triggerBranchList.size()];
	bool trgFlags[triggerBranchList.size()];
		
	int dummy=0;
	for(std::list<string>::iterator ibranch=triggerBranchList.begin(); ibranch!=triggerBranchList.end(); ibranch++, dummy++){
	
		//cout << "starting branch: " << *ibranch << endl;

		oldBranch[dummy] = smartBranchFind(ch, *ibranch);
		if(!oldBranch[dummy]){
			cout << "WARNING! Could not find branch " << *ibranch << " in tree " << ch->GetName() << endl;
			trgFlags[dummy]=0;
		}
		else{
			trgFlags[dummy]=1;
			oldBranch[dummy]->SetAddress(&valArray[dummy]);
			brToAdd[dummy] = tout->Branch((*ibranch).c_str(), &valArray[dummy]);
		}
	}

	for(int ientry=0; ientry<ch->GetEntries(); ientry++){
		if(ientry && ientry%10000==0) cout << " at entry " << ientry << endl;
		dummy=0;
		for(std::list<string>::iterator ibranch=triggerBranchList.begin(); ibranch!=triggerBranchList.end(); ibranch++, dummy++){
			//cout << "at entry " << ientry << " starting branch: " << *ibranch << endl;
			if(trgFlags[dummy]) oldBranch[dummy]->GetEntry(ientry);
		}
		tout->Fill();
	}
	tout->Write();
	
}


void merge8TeVForest(string fname_s = "0000_part1")
{
        string fname="list"+fname_s+".txt";
        string outfile="PbPb_dataForest"+fname_s+".root";

	cout  << fname << endl;

	string filename;
	std::ifstream ifstr(fname.c_str());
	if(!ifstr){ cout << "file not found!" << endl; exit(0); }
	ifstr >> filename;

	TChain *dummyChain = new TChain("hiEvtAnalyzer/HiTree");
	dummyChain->Add(filename.c_str());
	TFile *testFile = dummyChain->GetFile();
	TList *topKeyList = testFile->GetListOfKeys();

	std::vector<TString> trees;
	std::vector<TString> dir;

	for(int i = 0; i < topKeyList->GetEntries(); ++i)
	{
		TDirectoryFile *dFile = (TDirectoryFile*)testFile->Get(topKeyList->At(i)->GetName());
		if(strcmp(dFile->ClassName(), "TDirectoryFile") != 0) continue;

		TList *bottomKeyList = dFile->GetListOfKeys();

		for(int j = 0; j < bottomKeyList->GetEntries(); ++j)
		{
			TString treeName = dFile->GetName();
			treeName += "/";
			treeName += bottomKeyList->At(j)->GetName();

			TTree* tree = (TTree*)testFile->Get(treeName);
			if(strcmp(tree->ClassName(), "TTree") != 0 && strcmp(tree->ClassName(), "TNtuple") != 0) continue;

			bool flag=false;
			for(unsigned int itree=0; itree<trees.size(); itree++){
				if(treeName == trees[itree]) flag=true;
			}
			if(flag) continue;
			
			if(dFile->GetName()==(TString)"hltobject") continue;

			trees.push_back(treeName);
			dir.push_back(dFile->GetName());
			
			//Load trigger names
			if(treeName=="hltanalysis/HltTree") getTriggerList(tree);
		}
	}
	testFile->Close();
	delete dummyChain;

	const int Ntrees = trees.size();
	TChain* ch[Ntrees];

	ifstr.seekg(0);
	Long64_t nentries=0;
	for(int i = 0; i < Ntrees; ++i){
		ch[i] = new TChain(trees[i]);
		ifstr.clear();
		ifstr.seekg(0);
		while(ifstr>>filename){
			ch[i]->Add(filename.c_str());
		}
		std::cout << "Tree loaded : " << trees[i] << std::endl;
		std::cout << "Entries : " << ch[i]->GetEntries() << std::endl;
    // If the number of entries in this tree is different from other
    //     // trees there is a problem. Quit and inform the user without
    //         // producing output.
		if(i == 0) nentries = ch[i]->GetEntries();
		else if (nentries != ch[i]->GetEntries() && trees[i]!="HiForest/HiForestInfo" && trees[i]!="runAnalyzer/run" && trees[i]!="Dfinder/ntGen")
		{   
			std::cout << "ERROR: number of entries in tree does not match." << std::endl;
			std::cout << "Exiting. Please check input." << std::endl;
			exit(1);
		}
	}

	TFile* file = new TFile(outfile.c_str(), "RECREATE");

	for(int i = 0; i < Ntrees; ++i)
	{   
		file->cd();
		std::cout << trees[i] << std::endl;
		if (i==0)
		{   
			file->mkdir(dir[i])->cd();
		}
		else 
		{   
			if ( dir[i] != dir[i-1] )
				file->mkdir(dir[i])->cd();
			else
				file->cd(dir[i]);
		}
		if(dir[i]!="hltanalysis" && trees[i]!="HltTree") ch[i]->Merge(file,0,"keep");
		else mergeTriggerTree(ch[i], file);
	}
	
	cout <<"Good"<<endl;            
    //file->Write();
	file->Close();
	
	std::cout << "Done. Output: " << outfile << std::endl;
}
