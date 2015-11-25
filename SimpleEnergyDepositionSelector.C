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
#include <TMath.h>
#include <TString.h>
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
   _fo = new TFile(out_name.Data(), "RECREATE");
   outTree = new TTree("simple_out", "Simple Out Tree");
   outTree->Branch("runId", &crun_id, "runId/I");
   outTree->Branch("eventId", &event_id, "eventId/I");
   outTree->Branch("parent", &_parent);
   outTree->Branch("t0", &t0, "t0/D");
   outTree->Branch("t1", &t1, "t1/D");
   outTree->Branch("energy", &_energy, "energy/D");
   if (calculateDis) {
     outTree->Branch("maxDx", &_maxDx, "maxDx/D");
     outTree->Branch("maxDy", &_maxDy, "maxDy/D");
     outTree->Branch("maxDz", &_maxDz, "maxDz/D");
     outTree->Branch("maxDd", &_maxDd, "maxDd/D");
   }
   outTree->Branch("primaryX", &_primaryX, "primaryX/D");
   outTree->Branch("primaryY", &_primaryY, "primaryY/D");
   outTree->Branch("primaryZ", &_primaryZ, "primaryZ/D");
   t0 = -1;
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
  if (nHits==0)
    return kTRUE;
  // create the new simple event data object for this entry
  SimpleEnergyData npd;
  npd.setRunId(run_id);
  npd.setEventId(eventId);
  if (useFVCut) {
    // calculate total energy deposited in FV
    double e = 0;
    for (int i=0; i<nHits; ++i) {
      if (TMath::Abs((*zd)[i])>(fvHeight/2))
        continue;
      double r2 = (*xd)[i]*(*xd)[i] + (*yd)[i]*(*yd)[i];
      if (r2 > fvRadiusSquare)
        continue;
      e += (*energy)[i];
    }
    npd.setEnergy(e);
  } else {
    npd.setEnergy(totalEnergy);
  }
  npd.setT0((*td)[0]);
  npd.setParent((*primaryType)[0]);
  npd.setPrimaryX((*primaryX)[0]);
  npd.setPrimaryY((*primaryY)[0]);
  npd.setPrimaryZ((*primaryZ)[0]);

  // check the 200 ms window
  if (npd.getEnergy()>0 && pd.getEnergy()>0 && pd.getRunId() == npd.getRunId()
      && pd.getEventId() == npd.getEventId()
      && pd.getT0()>0 && npd.getT0() < 0.2
      && ((pd.getParent().find("Rn220")==0 && npd.getParent().find("Po216")==0)
	  || (pd.getParent().find("Bi214")==0 && npd.getParent().find("Po214")==0)
          || (pd.getParent().find("Bi212")==0 && npd.getParent().find("Po212")==0
              ))){
    // within the window, merge the two data.
    pd.mergeData(npd);
    // calculate the hit distance in the two entries.
    if (calculateDis) {
      calculateHitDistance(entry);
    }
  } else {
    // save the previous data object
    if (pd.getT0()>0 && pd.getEnergy()>0) {
      crun_id = pd.getRunId();
      event_id = pd.getEventId();
      _parent = pd.getParent();
      t0 = pd.getT0();
      t1 = npd.getT0();
      _energy = pd.getEnergy();
      _primaryX = pd.getPrimaryX();
      _primaryY = pd.getPrimaryY();
      _primaryZ = pd.getPrimaryZ();
      outTree->Fill();
    }
    // calculate the maximum hit distance
    if (calculateDis) {
      calculateHitDistance();
    }
    pd = npd;
  }
  if (entry == fChain->GetTree()->GetEntries()) {
    _parent = pd.getParent();
    t0 = pd.getT0();
    t1 = pd.getT0();
    _energy = pd.getEnergy();
    _primaryX = pd.getPrimaryX();
    _primaryY = pd.getPrimaryY();
    _primaryZ = pd.getPrimaryZ();
    if (_energy>0) {
      outTree->Fill();
    }
    pd.setT0(-1);
  }
  return kTRUE;
}

void SimpleEnergyDepositionSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

  outTree->Write();
  _fo->Close();
}

void SimpleEnergyDepositionSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}

void SimpleEnergyDepositionSelector::setOutputName(const char * name)
{
  out_name = name;
}

void SimpleEnergyDepositionSelector::calculateHitDistance()
{
  _maxDx = 0;
  _maxDy = 0;
  _maxDz = 0;
  _maxDd = 0;

  Double_t maxX(-10000), maxY(-10000), maxZ(-10000),
    minX(10000), minY(10000), minZ(10000);
  Double_t d(0);
  for (Int_t i=0; i<nHits; ++i) {
    if ((*xd)[i]>maxX) {
      maxX = (*xd)[i];
    }
    if ((*yd)[i]>maxY) {
      maxY = (*yd)[i];
    }
    if ((*zd)[i]>maxZ) {
      maxZ = (*zd)[i];
    }
    if ((*xd)[i]<minX) {
      minX = (*xd)[i];
    }
    if ((*yd)[i]<minY) {
      minY = (*yd)[i];
    }
    if ((*zd)[i]<minZ) {
      minZ = (*zd)[i];
    }
    for (Int_t j=1; j<nHits; ++j) {
      d = ((*xd)[i] - (*xd)[j])*((*xd)[i] - (*xd)[j]) + ((*yd)[i] - (*yd)[j])*((*yd)[i] - (*yd)[j]) + ((*zd)[i] - (*zd)[j])*((*zd)[i] - (*zd)[j]);
      if (d>_maxDd)
        _maxDd =d;
    }
  }
  _maxDx = maxX - minX;
  _maxDy = maxY - minY;
  _maxDz = maxZ - minZ;
  _maxDd = TMath::Sqrt(_maxDd);
}

void SimpleEnergyDepositionSelector::calculateHitDistance(Long64_t entry)
{
  _maxDx = 0;
  _maxDy = 0;
  _maxDz = 0;
  _maxDd = 0;

  vector<double> xv, yv, zv;
  Double_t maxX(-10000), maxY(-10000), maxZ(-10000),
    minX(10000), minY(10000), minZ(10000);
  Double_t d;
  for (Int_t i=0; i<nHits; ++i) {
    if ((*xd)[i]>maxX) {
      maxX = (*xd)[i];
    }
    if ((*yd)[i]>maxY) {
      maxY = (*yd)[i];
    }
    if ((*zd)[i]>maxZ) {
      maxZ = (*zd)[i];
    }
    if ((*xd)[i]<minX) {
      minX = (*xd)[i];
    }
    if ((*yd)[i]<minY) {
      minY = (*yd)[i];
    }
    if ((*zd)[i]<minZ) {
      minZ = (*zd)[i];
    }
    xv.push_back((*xd)[i]);
    yv.push_back((*yd)[i]);
    zv.push_back((*zd)[i]);
  }

  // load the previous entry
  fChain -> GetTree() -> GetEntry(entry - 1);
  for (Int_t i=0; i<nHits; ++i) {
    if ((*xd)[i]>maxX) {
      maxX = (*xd)[i];
    }
    if ((*yd)[i]>maxY) {
      maxY = (*yd)[i];
    }
    if ((*zd)[i]>maxZ) {
      maxZ = (*zd)[i];
    }
    if ((*xd)[i]<minX) {
      minX = (*xd)[i];
    }
    if ((*yd)[i]<minY) {
      minY = (*yd)[i];
    }
    if ((*zd)[i]<minZ) {
      minZ = (*zd)[i];
    }
    xv.push_back((*xd)[i]);
    yv.push_back((*yd)[i]);
    zv.push_back((*zd)[i]);
  }

  for (size_t i=0; i<xv.size(); ++i) {
    for (size_t j=0; j<xv.size(); ++j) {
      d = (xv[i] - xv[j])*(xv[i] - xv[j]) + (yv[i] - yv[j])*(yv[i] - yv[j]) + (zv[i] - zv[j])*(zv[i] - zv[j]);
      if (d>_maxDd)
        _maxDd = d;
    }
  }
  _maxDx = maxX - minX;
  _maxDy = maxY - minY;
  _maxDz = maxZ - minZ;
  _maxDd = TMath::Sqrt(_maxDd);
}

void SimpleEnergyDepositionSelector::enableDistance(bool b)
{
  calculateDis = b;
}

void SimpleEnergyDepositionSelector::enableFVCut(bool b)
{
  useFVCut = b;
}

void SimpleEnergyDepositionSelector::setFVHeight(double h)
{
  fvHeight = h;
}

void SimpleEnergyDepositionSelector::setFVRadius(double r)
{
  fvRadius = r;
  fvRadiusSquare = r*r;
}
