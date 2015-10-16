#include <iostream>
#include <unistd.h>

#include <TString.h>

#include <TChain.h>

#include "PEASelector.h"

using namespace std;

void print_usage(const char * cmd)
{
  cout << cmd << " -i input_file -o output_file -w half_width" << endl;
}


int main (int argc, char * argv[])
{
  extern char * optarg;

  TString inputName;
  TString outputName;
  Double_t hw = 6;
  //  Bool_t saveSurface = true;
  while (true) {
    const int option = getopt(argc, argv, "i:o:w:");
    if(option == -1) break;
    switch (option) {
    case 'i':
      inputName = optarg;
      break;
    case 'o':
      outputName = optarg;
      break;
    case 'w':
      hw = TString(optarg).Atof();
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
    outputName = "pea_out.root";
  }
  TChain ch("mcTree");
  ch.Add(inputName.Data());

  PEASelector * selector = new PEASelector();
  selector->setOutputName(outputName.Data());

  selector->setHalfWidth(hw);

  ch.Process(selector);
  return 0;
}
