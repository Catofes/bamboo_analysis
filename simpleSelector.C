#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <TChain.h>

#include "SimpleEnergyDepositionSelector.h"

using namespace std;
int main (int argc, char * argv[])
{
  extern char * optarg;
  string input_name;
  string output_name;
  stringstream ss;
  bool useFVCut = false;
  double height(1600);
  double radius(687);
  while (true) {
    const int option = getopt(argc, argv, "i:o:h:r:f");
    if (option == -1) {
      break;
    }
    switch (option) {
    case 'i':
      input_name = optarg;
      break;
    case 'o':
      output_name = optarg;
      break;
    case 'f':
      useFVCut = true;
      break;
    case 'h':
      ss.clear();
      ss.str(optarg);
      ss >> height;
      break;
    case 'r':
      ss.clear();
      ss.str(optarg);
      ss >> radius;
      break;
    }
  }

  if (input_name.empty() || output_name.empty()) {
    cerr << "Usage: " << argv[0] << " -i input_file -o output_file [ -f -h height -r radius ]" << endl;
    return 1;
  }

  TChain ch("mcTree");
  ch.Add(input_name.c_str());

  SimpleEnergyDepositionSelector * selector = new SimpleEnergyDepositionSelector();
  selector->setOutputName(output_name.c_str());
  selector->enableFVCut(useFVCut);
  if (useFVCut) {
    selector->setFVHeight(height);
    selector->setFVRadius(radius);
  }
  ch.Process(selector);

  return 0;
}
