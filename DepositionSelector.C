#define DepositionSelector_cxx
// The class definition in DepositionSelector.h has been generated automatically
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
// Root > T->Process("DepositionSelector.C")
// Root > T->Process("DepositionSelector.C","some options")
// Root > T->Process("DepositionSelector.C+")
//

#include "DepositionSelector.h"
#include "EnergyDeposition.h"

#include <TH2.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>
#include <algorithm>
#include <iostream>

using namespace std;

bool earlyHit(const EnergyDeposition &a, const EnergyDeposition &b) {
  return a.getTime() < b.getTime();
}

void DepositionSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void DepositionSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // create the output tree
   o_tree = new TTree("mc_out", "Processed MC Tree");
   o_originalId = 0;
   o_eventId = 0;
   o_tree->Branch("originalId", &o_originalId, "originalId/I");
   o_tree->Branch("eventId", &o_eventId, "eventId/I");
   o_tree->Branch("nDeposition", &o_nDeposition, "nDeposition/I");
   o_tree->Branch("nNuclearRecoil", &o_nNuclearRecoil, "nNuclearRecoil/I");
   o_tree->Branch("nElectronRecoil", &o_nElectronRecoil, "nElectronRecoil/I");
   o_tree->Branch("totalEnergy", &o_totalEnergy, "totalEnergy/D");
   o_tree->Branch("recoilType", &o_recoilType, "recoilType[nDeposition]/I");
   o_tree->Branch("x", &o_x, "x[nDeposition]/D");
   o_tree->Branch("y", &o_y, "y[nDeposition]/D");
   o_tree->Branch("z", &o_z, "z[nDeposition]/D");
   o_tree->Branch("t", &o_t, "t[nDeposition]/D");
   o_tree->Branch("energyNr", &o_energyNr, "energyNr[nDeposition]/D");
   o_tree->Branch("energyEr", &o_energyEr, "energyEr[nDeposition]/D");
}

Bool_t DepositionSelector::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either DepositionSelector::GetEntry() or TBranch::GetEntry()
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
  if (entry==0) {
    cout << fChain->GetTree()->GetDirectory()->GetName() << endl;
  }
  fChain->GetTree()->GetEntry(entry);
  vector<EnergyDeposition> vEd;
  o_originalId = eventId;
  for (Int_t i=0; i<nHits; ++i) {
    if ((*energy)[i]<0.01)
      continue;
    Double_t x = (*xd)[i];
    Double_t y = (*yd)[i];
    Double_t z = (*zd)[i];
    Double_t r = TMath::Sqrt(x*x + y*y);
    if (r>300.0)
      continue;
    TString ts((*type)[i]);
    TString parent((*parentType)[i]);
    // create energy deposition object
    EnergyDeposition edo;
    edo.setXYZ(x, y, z);
    edo.setTypeString((*type)[i]);
    edo.setVolume((*volume)[i]);
    edo.setTime((*td)[i]);
    if (edo.getTypeString().BeginsWith("e")||edo.getTypeString().BeginsWith("gamma")) {
      edo.setType(2);
      edo.setEnergyEr((*energy)[i]);
    } else {
      edo.setType(1);
      edo.setEnergyNr((*energy)[i]);
    }

    // merge it with existing depositions
    bool merged = false;
    for (size_t j=0; j<vEd.size(); ++j) {
      EnergyDeposition & eEd = vEd[j];
      Double_t delta_t = eEd.getTime() - edo.getTime();
      if (edo.getVolume().CompareTo(eEd.getVolume())!=0)
        continue;
      if (delta_t > 2e-4)
        continue;
      Double_t delta_z = eEd.getZ() - edo.getZ();
      if (TMath::Abs(delta_t * 1e6 * 1.7 - delta_z) < 8.5) {
        eEd.merge(edo);
        merged = true;
        break;
      }
    }
    if (!merged)
      vEd.push_back(edo);
  }
  // after the loop, all the depositions have been placed in a vector
  // and the adjcent depositions have been merged.
  sort(vEd.begin(), vEd.end(), earlyHit);
  Double_t preTime = -1;
  resetEvent();
  o_eventId++;

  for (size_t i=0; i<vEd.size(); ++i) {
    EnergyDeposition & edo = vEd[i];
    if (edo.getVolume().CompareTo("LXeSD")!=0)
      continue;
    if ((edo.getTime() - preTime) > 2e-4 && preTime>0) {
      // 200us seperation, fill the event
      if (o_nDeposition>0) {
        o_tree->Fill();
        o_eventId++;
        resetEvent();
      }
    }
    preTime = edo.getTime();
    o_nDeposition++;
    o_totalEnergy += edo.getEnergy();
    o_recoilType[o_nDeposition-1] = edo.getType();
    o_x[o_nDeposition-1] = edo.getX();
    o_y[o_nDeposition-1] = edo.getY();
    o_z[o_nDeposition-1] = edo.getZ();
    o_t[o_nDeposition-1] = edo.getTime();
    if (edo.getType()==1) {
      o_energyNr[o_nNuclearRecoil++] = edo.getEnergyNr();
    } else if (edo.getType()==2) {
      o_energyEr[o_nElectronRecoil++] = edo.getEnergyEr();
    } else if (edo.getType()==3) {
      o_energyMixEr[o_nMixedRecoil] = edo.getEnergyEr();
      o_energyMixNr[o_nMixedRecoil] = edo.getEnergyNr();
      o_nMixedRecoil++;
    }
  }
  // fill the data to tree.
  if (o_nDeposition>0) {
    o_tree->Fill();
  }
  return kTRUE;
}

void DepositionSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
  TFile outfile(ofname.Data(), "RECREATE");
  o_tree->Write();
  outfile.Close();
 
}

void DepositionSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}

void DepositionSelector::resetEvent()
{
  o_nDeposition = 0;
  o_nNuclearRecoil = 0;
  o_nElectronRecoil = 0;
  o_nMixedRecoil = 0;
  o_totalEnergy = 0;
}

void DepositionSelector::setOutputName(const char * name)
{
  ofname = name;
}
