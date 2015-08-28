//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 29 17:40:03 2015 by ROOT version 5.34/19
// from TChain mcTree/
//////////////////////////////////////////////////////////

#ifndef FluxSelector_h
#define FluxSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>

using std::vector;
using std::string;
// Fixed size dimensions of array or collections stored in the TTree if any.

class FluxSelector : public TSelector {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  // Declaration of leaf types
  Int_t           runId;
  Int_t           eventId;
  Int_t           nTracks;
  vector<double>  *trackEnergy;
  vector<string>  *trackName;
  vector<double>  *px;
  vector<double>  *py;
  vector<double>  *pz;
  vector<int>     *surface;

  // List of branches
  TBranch        *b_runId;   //!
  TBranch        *b_eventId;   //!
  TBranch        *b_nTracks;   //!
  TBranch        *b_trackEnergy;   //!
  TBranch        *b_trackName;   //!
  TBranch        *b_px;   //!
  TBranch        *b_py;   //!
  TBranch        *b_pz;   //!
  TBranch        *b_surface;   //!

  FluxSelector(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~FluxSelector() { }
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

  void setOutputName (const char * name);
  void setSurfaceOutput (Bool_t t);
  void setEnergyCut (Double_t eCut);

  TH1D * histoThetaSurfaceXP;
  TH1D * histoThetaSurfaceYP;
  TH1D * histoThetaSurfaceZP;

  TH1D * histoThetaSurfaceXM;
  TH1D * histoThetaSurfaceYM;
  TH1D * histoThetaSurfaceZM;

  TH1D * histoThetaAll;

  TH1D * histoCosThetaSurfaceXP;
  TH1D * histoCosThetaSurfaceYP;
  TH1D * histoCosThetaSurfaceZP;

  TH1D * histoCosThetaSurfaceXM;
  TH1D * histoCosThetaSurfaceYM;
  TH1D * histoCosThetaSurfaceZM;

  TH1D * histoPhiSurfaceXP;
  TH1D * histoPhiSurfaceYP;
  TH1D * histoPhiSurfaceZP;

  TH1D * histoPhiSurfaceXM;
  TH1D * histoPhiSurfaceYM;
  TH1D * histoPhiSurfaceZM;

  TH1D * histoEAll;
  TH1D * histoESurfaceXP;
  TH1D * histoESurfaceYP;
  TH1D * histoESurfaceZP;
  TH1D * histoESurfaceXM;
  TH1D * histoESurfaceYM;
  TH1D * histoESurfaceZM;
  
  TString out_name;

  Double_t energyCut;
  Long_t nEvents;
  Bool_t surfaceOutput;
  //   ClassDef(FluxSelector,0);
};

#endif

#ifdef FluxSelector_cxx
void FluxSelector::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  trackEnergy = 0;
  trackName = 0;
  px = 0;
  py = 0;
  pz = 0;
  surface = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("runId", &runId, &b_runId);
  fChain->SetBranchAddress("eventId", &eventId, &b_eventId);
  fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
  fChain->SetBranchAddress("trackEnergy", &trackEnergy, &b_trackEnergy);
  fChain->SetBranchAddress("trackName", &trackName, &b_trackName);
  fChain->SetBranchAddress("px", &px, &b_px);
  fChain->SetBranchAddress("py", &py, &b_py);
  fChain->SetBranchAddress("pz", &pz, &b_pz);
  fChain->SetBranchAddress("surface", &surface, &b_surface);
}

Bool_t FluxSelector::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef FluxSelector_cxx
