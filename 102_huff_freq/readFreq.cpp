#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f;
  f.open(fname);
  if(f.fail()) {
    std::cerr << "cannot open the file" << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t *freq = new uint64_t[257];
  int c = 0;
  while ((c = f.get()) != EOF) {
    freq[c]++;
  }
  freq[256]++;
  f.close();
  return freq;
}
