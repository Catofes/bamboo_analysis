#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH1I.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;



double Q_value = 2457.83; // (keV)

double getSigma(double fhwm);
double smearEnergy(double e, double sigma);

TRandom3 tr;

int main(int argc, char * argv[])
{
  if (argc!=3) {
    cerr << "Usage: " << argv[0] << " input_file output_file." << endl;
    return 1;
  }
  // variables in tree
  int run_id;
  int event_id;
  string * parent = 0;
  double t0;
  double t1;
  double energy;
  double maxDx;
  double maxDy;
  double maxDz;
  double maxDd;
  double primaryX;
  double primaryY;
  double primaryZ;

  // open the file for read
  TFile f(argv[1], "READ");
  TTree * tree = (TTree *) f.Get("simple_out");
  TBranch * b_parent;
  // mapping
  tree->SetMakeClass(1);
  tree->SetBranchAddress("runId", &run_id);
  tree->SetBranchAddress("eventId", &event_id);
  tree->SetBranchAddress("parent", &parent, &b_parent);
  tree->SetBranchAddress("t0", &t0);
  tree->SetBranchAddress("t1", &t1);
  tree->SetBranchAddress("energy", &energy);
  tree->SetBranchAddress("maxDx", &maxDx);
  tree->SetBranchAddress("maxDy", &maxDy);
  tree->SetBranchAddress("maxDz", &maxDz);
  tree->SetBranchAddress("maxDd", &maxDd);
  tree->SetBranchAddress("primaryX", &primaryX);
  tree->SetBranchAddress("primaryY", &primaryY);
  tree->SetBranchAddress("primaryZ", &primaryZ);

  // ROI
  double fwhm_0_5 = 0.005 * Q_value;
  double fwhm_1 = 0.01 * Q_value;
  double fwhm_3 = 0.03 * Q_value;

  double sigma_0_5 = getSigma(fwhm_0_5);
  double sigma_1 = getSigma(fwhm_1);
  double sigma_3 = getSigma(fwhm_3);

  double l_edge_0_5 = Q_value - 2 * sigma_0_5;
  double u_edge_0_5 = Q_value + 2 * sigma_0_5;
  double l_edge_1 = Q_value - 2 * sigma_1;
  double u_edge_1 = Q_value + 2 * sigma_1;
  double l_edge_3 = Q_value - 2 * sigma_3;
  double u_edge_3 = Q_value + 2 * sigma_3;
  cout << "0.5% FHWM " << fwhm_0_5 << " - sigma " << sigma_0_5 << endl;
  cout << "1.0% FHWM " << fwhm_1 << " - sigma " << sigma_1 << endl;
  cout << "3.0% FHWM " << fwhm_3 << " - sigma " << sigma_3 << endl;

  cout << "0.5% FHWM - (" << l_edge_0_5 << ", " << u_edge_0_5 << ")." << endl;
  cout << "1.0% FHWM - (" << l_edge_1 << ", " << u_edge_1 << ")." << endl;
  cout << "3.0% FHWM - (" << l_edge_3 << ", " << u_edge_3 << ")." << endl;

  // output file, only with the smeared energy.
  TFile fo(argv[2], "RECREATE");
  TTree * out_tree = new TTree ("smear_e", "smeared energy");
  // output variables
  double e_smear_0_5, e_smear_1, e_smear_3;
  string pparent;
  out_tree->Branch("runId", &run_id, "runId/I");
  out_tree->Branch("eventId", &event_id, "eventId/I");
  out_tree->Branch("parent", &pparent);
  out_tree->Branch("energy", &energy, "energy/D");
  out_tree->Branch("e_smear_0_5", &e_smear_0_5, "e_smear_0_5/D");
  out_tree->Branch("e_smear_1", &e_smear_1, "e_smear_1/D");
  out_tree->Branch("e_smear_3", &e_smear_3, "e_smear_3/D");
  out_tree->Branch("maxDx", &maxDx, "maxDx/D");
  out_tree->Branch("maxDy", &maxDy, "maxDy/D");
  out_tree->Branch("maxDz", &maxDz, "maxDz/D");
  out_tree->Branch("maxDd", &maxDd, "maxDd/D");
  out_tree->Branch("primaryX", &primaryX, "primaryX/D");
  out_tree->Branch("primaryY", &primaryY, "primaryY/D");
  out_tree->Branch("primaryZ", &primaryZ, "primaryZ/D");

  long nEntries = tree->GetEntries();
  cout << nEntries << endl;
  // loop over entries and smear the energy

  tr.SetSeed(0);
  // TCanvas c1("c1", "c1", 800, 600);
  // TH1D * th_esm = new TH1D("th_esm", "smeared energy", 500, 2200, 2700);
  // for (int i=0; i<1000; ++i) {
  //   double esm = smearEnergy(Q_value, sigma_3);
  //   th_esm->Fill(esm);
  // }
  // th_esm->Draw();
  // c1.Print("esm.png");
  vector<double> es;		// selected energy
  int n_0_5(0), ns_0_5(0);
  int n_1(0), ns_1(0);
  int n_3(0), ns_3(0);

  TTree * count_tree = new TTree ("count_tree", "tree of counts");
  count_tree->Branch("ns_0_5", &ns_0_5, "ns_0_5/I");
  count_tree->Branch("ns_1", &ns_1, "ns_1/I");
  count_tree->Branch("ns_3", &ns_3, "ns_3/I");
  double times = 6.0;
  for (long i=0; i<nEntries; ++i) {
    tree->GetEntry(i);
    e_smear_0_5 = 0;
    e_smear_1 = 0;
    e_smear_3 = 0;
    if (energy>Q_value-times*sigma_0_5 && energy<Q_value+times*sigma_0_5) {
      e_smear_0_5 = smearEnergy(energy, sigma_0_5);
      if (energy>Q_value-2*sigma_0_5 && energy<Q_value+2*sigma_0_5) {
	n_0_5++;
      }
      if (e_smear_0_5>Q_value-2*sigma_0_5&&e_smear_0_5<Q_value+2*sigma_0_5) {
	ns_0_5++;
      }
    }
    if (energy>Q_value-times*sigma_1 && energy<Q_value+times*sigma_1) {
      e_smear_1 = smearEnergy(energy, sigma_1);
      if (energy>Q_value-2*sigma_1 && energy<Q_value+2*sigma_1) {
	n_1++;
      }
      if (e_smear_1>Q_value-2*sigma_1&&e_smear_1<Q_value+2*sigma_1) {
	ns_1++;
      }
    }
    if (energy>Q_value-times*sigma_3 && energy<Q_value+times*sigma_3) {
      e_smear_3 = smearEnergy(energy, sigma_3);
      if (energy>Q_value-2*sigma_3 && energy<Q_value+2*sigma_3) {
	n_3++;
      }
      if (e_smear_3>Q_value-2*sigma_3&&e_smear_3<Q_value+2*sigma_3) {
	ns_3++;
      }
      es.push_back(energy);
      pparent = * parent;
      //      cout << event_id << " " << * parent << endl;
      out_tree->Fill();
    }
  }
  // print out the values
  cout << "0.5%: " << n_0_5 << " (original), " << ns_0_5 << " (smeared)." << endl;
  cout << "1.0%: " << n_1 << " (original), " << ns_1 << " (smeared)." << endl;
  cout << "3.0%: " << n_3 << " (original), " << ns_3 << " (smeared)." << endl;
  out_tree->Write();
  // further simulation
  for (int i=0; i<500; ++i) {
    ns_0_5 = 0;
    ns_1 = 0;
    ns_3 = 0;
    for (size_t j=0; j<es.size(); ++j) {
      double e = es[j];
      if (e>Q_value-times*sigma_0_5&&e<Q_value+times*sigma_0_5) {
	double ex = smearEnergy(e, sigma_0_5);
	if (ex>Q_value-2*sigma_0_5&&e<Q_value+2*sigma_0_5) {
	  ns_0_5++;
	}
      }
      if (e>Q_value-times*sigma_1&&e<Q_value+times*sigma_1) {
	double ex = smearEnergy(e, sigma_1);
	if (ex>Q_value-2*sigma_1&&e<Q_value+2*sigma_1) {
	  ns_1++;
	}
      }
      if (e>Q_value-times*sigma_3&&e<Q_value+times*sigma_3) {
	double ex = smearEnergy(e, sigma_3);
	if (ex>Q_value-2*sigma_3&&e<Q_value+2*sigma_3) {
	  ns_3++;
	}
      }
    }
    count_tree->Fill();
  }
  count_tree->Write();
  fo.Close();
  f.Close();
}

double getSigma (double fhwm)
{
  return fhwm/(2.*TMath::Sqrt(2.*TMath::Log(2.)));
}

double smearEnergy (double e, double sigma)
{
  return tr.Gaus(e, sigma);
}
