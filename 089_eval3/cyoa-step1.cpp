#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "page.h"

int main(int argc, char** argv) {

  // check args
  if(argc != 2) {
    std::cerr << "invalid number of arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  Page page1;
  // read page information
  if(page1.readPage(argv[1]) == false) {
    std::cerr << "cannot open the file" << std::endl;
    exit(EXIT_FAILURE);
  }
  // print out this page
  page1.printPage();
	
  return EXIT_SUCCESS;
}
