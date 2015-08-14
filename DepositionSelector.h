//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 13 17:55:10 2015 by ROOT version 5.34/19
// from TTree mcTree/Tree with MC info
// found on file: data.root
//////////////////////////////////////////////////////////

#ifndef DepositionSelector_h
#define DepositionSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTree.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>

using std::vector;
using std::string;

// Fixed size dimensions of array or collections stored in the TTree if any.

class DepositionSelector : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           runId;
   Int_t           eventId;
   Int_t           nHits;
   vector<int>     *trackId;
   vector<int>     *parentId;
   vector<string>  *type;
   vector<string>  *parentType;
   vector<string>  *creatorProcess;
   vector<string>  *depositionProcess;
   vector<string>  *volume;
   Double_t        totalEnergy;
   vector<double>  *xd;
   vector<double>  *yd;
   vector<double>  *zd;
   vector<double>  *td;
   vector<double>  *energy;

   // List of branches
   TBranch        *b_runId;   //!
   TBranch        *b_eventId;   //!
   TBranch        *b_nHits;   //!
   TBranch        *b_trackId;   //!
   TBranch        *b_parentId;   //!
   TBranch        *b_type;   //!
   TBranch        *b_parentType;   //!
   TBranch        *b_creatorProcess;   //!
   TBranch        *b_depositionProcess;   //!
   TBranch        *b_volume;   //!
   TBranch        *b_totalEnergy;   //!
   TBranch        *b_xd;   //!
   TBranch        *b_yd;   //!
   TBranch        *b_zd;   //!
   TBranch        *b_td;   //!
   TBranch        *b_energy;   //!

  DepositionSelector(TTree * /*tree*/ =0) : fChain(0) { ofname = "mcout.root"; }
   virtual ~DepositionSelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

  // custom function
  void setOutputName(const char * name);
   // variables for the output file

   TTree * o_tree;
   Int_t o_originalId;
   Int_t o_eventId;
   Int_t o_nDeposition;
   Int_t o_nNuclearRecoil;
   Int_t o_nElectronRecoil;
   Int_t o_nMixedRecoil;
   Double_t o_totalEnergy;
   Int_t o_recoilType[1000];
   Double_t o_x[1000];
   Double_t o_y[1000];
   Double_t o_z[1000];
   Double_t o_t[1000];
   Double_t o_energyNr[1000];
   Double_t o_energyEr[1000];
   Double_t o_energyMixNr[1000];
   Double_t o_energyMixEr[1000];

  TString ofname;               // name of the output file
private:

  void resetEvent();
  //   ClassDef(DepositionSelector,0);
};

#endif

#ifdef DepositionSelector_cxx
void DepositionSelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   trackId = 0;
   parentId = 0;
   type = 0;
   parentType = 0;
   creatorProcess = 0;
   depositionProcess = 0;
   volume = 0;
   xd = 0;
   yd = 0;
   zd = 0;
   td = 0;
   energy = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runId", &runId, &b_runId);
   fChain->SetBranchAddress("eventId", &eventId, &b_eventId);
   fChain->SetBranchAddress("nHits", &nHits, &b_nHits);
   fChain->SetBranchAddress("trackId", &trackId, &b_trackId);
   fChain->SetBranchAddress("parentId", &parentId, &b_parentId);
   fChain->SetBranchAddress("type", &type, &b_type);
   fChain->SetBranchAddress("parentType", &parentType, &b_parentType);
   fChain->SetBranchAddress("creatorProcess", &creatorProcess, &b_creatorProcess);
   fChain->SetBranchAddress("depositionProcess", &depositionProcess, &b_depositionProcess);
   fChain->SetBranchAddress("volume", &volume, &b_volume);
   fChain->SetBranchAddress("totalEnergy", &totalEnergy, &b_totalEnergy);
   fChain->SetBranchAddress("xd", &xd, &b_xd);
   fChain->SetBranchAddress("yd", &yd, &b_yd);
   fChain->SetBranchAddress("zd", &zd, &b_zd);
   fChain->SetBranchAddress("td", &td, &b_td);
   fChain->SetBranchAddress("energy", &energy, &b_energy);
}

Bool_t DepositionSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef DepositionSelector_cxx
