#include <iostream>

#include <TChain.h>

#include "FluxSelector.h"

using namespace std;
int main (int argc, char * argv[])
{
  if (argc!=3 && argc!=4) {
    cerr << "Usage: " << argv[0] << " input_file output_file [energy_cut]" << endl;
    return 1;
  }
  TChain ch("mcTree");
  ch.Add(argv[1]);

  FluxSelector * selector = new FluxSelector();
  selector->setOutputName(argv[2]);

  if (argc==3) {
    ch.Process(selector);
  } else {
    ch.Process(selector, argv[3]);
  }

  return 0;
}
