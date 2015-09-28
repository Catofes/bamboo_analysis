#define SimpleEnergyDepositionSelector_cxx
// The class definition in SimpleEnergyDepositionSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("SimpleEnergyDepositionSelector.C")
// Root > T->Process("SimpleEnergyDepositionSelector.C","some options")
// Root > T->Process("SimpleEnergyDepositionSelector.C+")
//

#include "SimpleEnergyDepositionSelector.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>

using namespace std;

void SimpleEnergyDepositionSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void SimpleEnergyDepositionSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   run_id = 0;
   outTree = new TTree("simple_out", "Simple Out Tree");
   outTree->Branch("runId", &run_id, "runId/I");
   outTree->Branch("eventId", &eventId, "eventId/I");
   outTree->Branch("parent", &_parent);
   outTree->Branch("t0", &t0, "t0/D");
   outTree->Branch("t1", &t1, "t1/D");
   outTree->Branch("energy", &_energy, "energy/D");
   outTree->Branch("energySmeared", &_energySmeared, "energySmeared/D");
   outTree->Branch("primaryX", &_primaryX, "primaryX/D");
   outTree->Branch("primaryY", &_primaryY, "primaryY/D");
   outTree->Branch("primaryZ", &_primaryZ, "primaryZ/D");
   t0 = -1;
   tr.SetSeed(0);
}

Bool_t SimpleEnergyDepositionSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either SimpleEnergyDepositionSelector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
  if (entry == 0) {
    cout << fChain->GetTree()->GetDirectory()->GetName() << endl;
    run_id++;
  }

  fChain->GetTree()->GetEntry(entry);

  SimpleEnergyData npd;
  npd.setRunId(run_id);
  npd.setEventId(eventId);
  npd.setEnergy(totalEnergy);
  npd.setT0((*td)[0]);
  npd.setParent((*primaryType)[0]);
  npd.setPrimaryX((*primaryX)[0]);
  npd.setPrimaryY((*primaryY)[0]);
  npd.setPrimaryZ((*primaryZ)[0]);

  // 200 ms window
  if (pd.getRunId() == npd.getRunId()
      && pd.getEventId() == npd.getEventId()
      && pd.getT0()>0 && npd.getT0() < 0.2) {
    // within the window, merge the two data.
    pd.mergeData(npd);
  } else {
    // save the previous data object
    _parent = pd.getParent();
    t0 = pd.getT0();
    t1 = npd.getT0();
    _energy = pd.getEnergy();
    _energySmeared = tr.Gaus(_energy, 0.03*_energy);
    _primaryX = pd.getPrimaryX();
    _primaryY = pd.getPrimaryY();
    _primaryZ = pd.getPrimaryZ();
    outTree->Fill();
    pd = npd;
  }
  if (entry == fChain->GetTree()->GetEntries()) {
    _parent = pd.getParent();
    t0 = pd.getT0();
    t1 = pd.getT0();
    _energy = pd.getEnergy();
    _energySmeared = tr.Gaus(_energy, 0.03*_energy);
    _primaryX = pd.getPrimaryX();
    _primaryY = pd.getPrimaryY();
    _primaryZ = pd.getPrimaryZ();
    outTree->Fill();
  }
  return kTRUE;
}

void SimpleEnergyDepositionSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

  TFile fo("simple_out.root", "RECREATE");
  outTree->Write();
  fo.Close();
}

void SimpleEnergyDepositionSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
