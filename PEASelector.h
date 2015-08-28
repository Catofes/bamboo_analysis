//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Aug  1 21:41:27 2015 by ROOT version 5.34/19
// from TTree mcTree/Tree with MC info
// found on file: test_analysis.root
//////////////////////////////////////////////////////////

#ifndef PEASelector_h
#define PEASelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1D.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>

using std::vector;
using std::string;
// Fixed size dimensions of array or collections stored in the TTree if any.

class PEASelector : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           runId;
   Int_t           eventId;
   Int_t           nPrimaries;
   vector<string>  *primaryType;
   vector<int>     *primaryId;
   vector<double>  *primaryEnergy;
   vector<double>  *primaryPx;
   vector<double>  *primaryPy;
   vector<double>  *primaryPz;
   vector<double>  *primaryX;
   vector<double>  *primaryY;
   vector<double>  *primaryZ;

   // List of branches
   TBranch        *b_runId;   //!
   TBranch        *b_eventId;   //!
   TBranch        *b_nPrimaries;   //!
   TBranch        *b_primaryType;   //!
   TBranch        *b_primaryId;   //!
   TBranch        *b_primaryEnergy;   //!
   TBranch        *b_primaryPx;   //!
   TBranch        *b_primaryPy;   //!
   TBranch        *b_primaryPz;   //!
   TBranch        *b_primaryX;   //!
   TBranch        *b_primaryY;   //!
   TBranch        *b_primaryZ;   //!

   PEASelector(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~PEASelector() { }
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

   void setOutputName(const char * name);
   void setHalfWidth(Double_t hw);

   TH1D * thPEnergy;
   TH1D * thPTheta;

   TString out_name;
   Double_t halfWidth;             /* half width */

};

#endif

#ifdef PEASelector_cxx
void PEASelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   // trackEnergy = 0;
   // trackName = 0;
   // px = 0;
   // py = 0;
   // pz = 0;
   // surface = 0;
   primaryType = 0;
   primaryId = 0;
   primaryEnergy = 0;
   primaryPx = 0;
   primaryPy = 0;
   primaryPz = 0;
   primaryX = 0;
   primaryY = 0;
   primaryZ = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runId", &runId, &b_runId);
   fChain->SetBranchAddress("eventId", &eventId, &b_eventId);
   fChain->SetBranchAddress("nPrimaries", &nPrimaries, &b_nPrimaries);
   fChain->SetBranchAddress("primaryType", &primaryType, &b_primaryType);
   fChain->SetBranchAddress("primaryId", &primaryId, &b_primaryId);
   fChain->SetBranchAddress("primaryEnergy", &primaryEnergy, &b_primaryEnergy);
   fChain->SetBranchAddress("primaryPx", &primaryPx, &b_primaryPx);
   fChain->SetBranchAddress("primaryPy", &primaryPy, &b_primaryPy);
   fChain->SetBranchAddress("primaryPz", &primaryPz, &b_primaryPz);
   fChain->SetBranchAddress("primaryX", &primaryX, &b_primaryX);
   fChain->SetBranchAddress("primaryY", &primaryY, &b_primaryY);
   fChain->SetBranchAddress("primaryZ", &primaryZ, &b_primaryZ);
}

Bool_t PEASelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef PEASelector_cxx
