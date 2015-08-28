#define FluxSelector_cxx
// The class definition in FluxSelector.h has been generated automatically
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
// Root > T->Process("FluxSelector.C")
// Root > T->Process("FluxSelector.C","some options")
// Root > T->Process("FluxSelector.C+")
//

#include "FluxSelector.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>

#include <iostream>

using namespace std;

void FluxSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

  cout << "begin of selector" << endl;
   histoThetaAll = new TH1D ("theta_all", "#theta normalized to each surface", 180, 0, 0.5*TMath::Pi());

   histoThetaSurfaceXP = new TH1D ("theta_xp", "#theta at X+", 180, 0, 0.5*TMath::Pi());
   histoThetaSurfaceYP = new TH1D ("theta_yp", "#theta at Y+", 180, 0, 0.5*TMath::Pi());
   histoThetaSurfaceZP = new TH1D ("theta_zp", "#theta at Z+", 180, 0, 0.5*TMath::Pi());
   histoThetaSurfaceXM = new TH1D ("theta_xm", "#theta at X-", 180, 0, 0.5*TMath::Pi());
   histoThetaSurfaceYM = new TH1D ("theta_ym", "#theta at Y-", 180, 0, 0.5*TMath::Pi());
   histoThetaSurfaceZM = new TH1D ("theta_zm", "#theta at Z-", 180, 0, 0.5*TMath::Pi());

   histoCosThetaSurfaceXP = new TH1D ("costheta_xp", "Cos#theta at X+", 100, 0, 1);
   histoCosThetaSurfaceYP = new TH1D ("costheta_yp", "Cos#theta at Y+", 100, 0, 1);
   histoCosThetaSurfaceZP = new TH1D ("costheta_zp", "Cos#theta at Z+", 100, 0, 1);
   histoCosThetaSurfaceXM = new TH1D ("costheta_xm", "Cos#theta at X-", 100, 0, 1);
   histoCosThetaSurfaceYM = new TH1D ("costheta_ym", "Cos#theta at Y-", 100, 0, 1);
   histoCosThetaSurfaceZM = new TH1D ("costheta_zm", "Cos#theta at Z-", 100, 0, 1);

   histoPhiSurfaceXP = new TH1D ("phi_xp", "#phi at X+", 360, 0, 2*TMath::Pi());
   histoPhiSurfaceYP = new TH1D ("phi_yp", "#phi at Y+", 360, 0, 2*TMath::Pi());
   histoPhiSurfaceZP = new TH1D ("phi_zp", "#phi at Z+", 360, 0, 2*TMath::Pi());

   histoPhiSurfaceXM = new TH1D ("phi_xm", "#phi at X-", 360, 0, 2*TMath::Pi());
   histoPhiSurfaceYM = new TH1D ("phi_ym", "#phi at Y-", 360, 0, 2*TMath::Pi());
   histoPhiSurfaceZM = new TH1D ("phi_zm", "#phi at Z-", 360, 0, 2*TMath::Pi());

   histoEAll = new TH1D ("e_all", "Flux Energy", 1500, 0, 15000);
   histoESurfaceXP = new TH1D ("e_xp", "Flux Energy (X+)", 1500, 0, 15000);
   histoESurfaceYP = new TH1D ("e_yp", "Flux Energy (Y+)", 1500, 0, 15000);
   histoESurfaceZP = new TH1D ("e_zp", "Flux Energy (Z+)", 1500, 0, 15000);
   histoESurfaceXM = new TH1D ("e_xm", "Flux Energy (X-)", 1500, 0, 15000);
   histoESurfaceYM = new TH1D ("e_ym", "Flux Energy (Y-)", 1500, 0, 15000);
   histoESurfaceZM = new TH1D ("e_zm", "Flux Energy (Z-)", 1500, 0, 15000);
   nEvents = 0;
}

void FluxSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t FluxSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either FluxSelector::GetEntry() or TBranch::GetEntry()
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
  }

  fChain->GetTree()->GetEntry(entry);
  double r;
  double costheta;
  double theta;
  double phi;
  double cosphi;
  double rpx, rpy, rpz;
  double rphi;
  double track_energy;
  std::vector<int> & rsurface = * surface;
  for (Int_t i=0; i<nTracks; ++i) {
    track_energy = (*trackEnergy)[i];
    r = (*px)[i]*(*px)[i] + (*py)[i]*(*py)[i] + (*pz)[i]*(*pz)[i];
    r = TMath::Sqrt(r);
    if (rsurface[i]==1 || rsurface[i]==-1) {
      rpx = (*py)[i];
      rpy = (*pz)[i];
      rpz = (*px)[i];
    } else if (rsurface[i]==2 || rsurface[i]==-2) {
      rpx = (*pz)[i];
      rpy = (*px)[i];
      rpz = (*py)[i];
    } else {
      rpx = (*px)[i];
      rpy = (*py)[i];
      rpz = (*pz)[i];
    }
    if (rsurface[i]>0) {
      rpx = -rpx;
      rpy = -rpy;
      rpz = -rpz;
    }
    rphi = TMath::Sqrt(rpx*rpx + rpy*rpy);
    costheta = rpz / r;
    theta = TMath::ACos(costheta);
    cosphi = rpx/rphi;
    phi = TMath::ACos(cosphi);
    if (rpy<0)
      phi = TMath::TwoPi()-phi;
    histoEAll->Fill(track_energy);
    if (track_energy < energyCut)
      continue;
    histoThetaAll->Fill(theta);
    if (rsurface[i]==1) {
      histoThetaSurfaceXP->Fill(theta);
      histoCosThetaSurfaceXP->Fill(costheta);
      histoPhiSurfaceXP->Fill(phi);
      histoESurfaceXP->Fill(track_energy);
    } else if (rsurface[i]==-1) {
      histoThetaSurfaceXM->Fill(theta);
      histoCosThetaSurfaceXM->Fill(costheta);
      histoPhiSurfaceXM->Fill(phi);
      histoESurfaceXM->Fill(track_energy);
    } else if (rsurface[i]==2) {
      histoThetaSurfaceYP->Fill(theta);
      histoCosThetaSurfaceYP->Fill(costheta);
      histoPhiSurfaceYP->Fill(phi);
      histoESurfaceYP->Fill(track_energy);
    } else if (rsurface[i]==-2) {
      histoThetaSurfaceYM->Fill(theta);
      histoCosThetaSurfaceYM->Fill(costheta);
      histoPhiSurfaceYM->Fill(phi);
      histoESurfaceYM->Fill(track_energy);
    } else if (rsurface[i]==3) {
      histoThetaSurfaceZP->Fill(theta);
      histoCosThetaSurfaceZP->Fill(costheta);
      histoPhiSurfaceZP->Fill(phi);
      histoESurfaceZP->Fill(track_energy);
    } else { // rsurface[i] == -3
      histoThetaSurfaceZM->Fill(theta);
      histoCosThetaSurfaceZM->Fill(costheta);
      histoPhiSurfaceZM->Fill(phi);
      histoESurfaceZM->Fill(track_energy);
    }
    nEvents++;
  }
  return kTRUE;
}

void FluxSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void FluxSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  TFile outfile(out_name.Data(), "RECREATE");
  histoThetaAll->Write();
  histoEAll->Write();

  if (surfaceOutput) {
    histoThetaSurfaceXP->Write();
    histoThetaSurfaceYP->Write();
    histoThetaSurfaceZP->Write();

    histoThetaSurfaceXM->Write();
    histoThetaSurfaceYM->Write();
    histoThetaSurfaceZM->Write();

    histoCosThetaSurfaceXP->Write();
    histoCosThetaSurfaceYP->Write();
    histoCosThetaSurfaceZP->Write();

    histoCosThetaSurfaceXM->Write();
    histoCosThetaSurfaceYM->Write();
    histoCosThetaSurfaceZM->Write();

    histoPhiSurfaceXP->Write();
    histoPhiSurfaceYP->Write();
    histoPhiSurfaceZP->Write();

    histoPhiSurfaceXM->Write();
    histoPhiSurfaceYM->Write();
    histoPhiSurfaceZM->Write();

    histoESurfaceXP->Write();
    histoESurfaceYP->Write();
    histoESurfaceZP->Write();
    histoESurfaceXM->Write();
    histoESurfaceYM->Write();
    histoESurfaceZM->Write();
  }  
  outfile.Close();
  if (energyCut>0) {
    cout << nEvents << " with energy > " << energyCut << " was counted." << endl;
  }
  if (!surfaceOutput) {
    cout << nEvents << endl;
  }
}

void FluxSelector::setOutputName(const char * name)
{
  out_name = name;
}

void FluxSelector::setSurfaceOutput(Bool_t t)
{
  surfaceOutput = t;
  cout << "surface output is ";
  if (t)
    cout << "on.";
  else
    cout << "off.";
  cout << endl;
}

void FluxSelector::setEnergyCut(Double_t eCut)
{
  energyCut = eCut;
  cout << "energy cut = " << energyCut << " keV." << endl;
}
