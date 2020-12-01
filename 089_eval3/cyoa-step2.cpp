#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "book.h"

int main(int argc, char** argv) {

  // check args
  if(argc != 2) {
    std::cerr << "invalid number of arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  Book book1;
  // read pages from the directory
  book1.readPages(argv[1]);
  // check the pages
  book1.checkPages();
  // from page1 to start the story
  book1.startStory();

  return EXIT_SUCCESS;
}
