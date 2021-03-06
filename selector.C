#include <iostream>

#include <TChain.h>

#include "DepositionSelector.h"

using namespace std;
int main (int argc, char * argv[])
{
  if (argc!=3) {
    cerr << "Usage: " << argv[0] << " input_file output_file" << endl;
    return 1;
  }
  TChain ch("mcTree");
  ch.Add(argv[1]);

  DepositionSelector * selector = new DepositionSelector();
  selector->setOutputName(argv[2]);

  ch.Process(selector);

  return 0;
}
