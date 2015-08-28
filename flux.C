#include <iostream>
#include <unistd.h>

#include <TString.h>

#include <TChain.h>

#include "FluxSelector.h"

using namespace std;

void print_usage(const char * cmd)
{
  cout << cmd << " -i input_file -o output_file [-e energy_cut] [-s]" << endl;
}


int main (int argc, char * argv[])
{
  extern char * optarg;

  TString inputName;
  TString outputName;
  Double_t eCut = 0;
  Bool_t saveSurface = true;
  while (true) {
    const int option = getopt(argc, argv, "i:o:e:S");
    if(option == -1) break;
    switch (option) {
    case 'i':
      inputName = optarg;
      break;
    case 'o':
      outputName = optarg;
      break;
    case 'e':
      eCut = TString(optarg).Atof();
      break;
    case 'S':
      saveSurface = false;
      break;
    default:
      print_usage(argv[0]);
      return 1;
    }
  }

  if (inputName.IsNull()) {
    print_usage(argv[0]);
    return 1;
  }
  if (outputName.IsNull()) {
    outputName = "flux_out.root";
  }
  TChain ch("mcTree");
  ch.Add(inputName.Data());

  FluxSelector * selector = new FluxSelector();
  selector->setOutputName(outputName.Data());

  if (eCut>0) {
    selector->setEnergyCut(eCut);
  }
  selector->setSurfaceOutput(saveSurface);

  ch.Process(selector);
  return 0;
}
