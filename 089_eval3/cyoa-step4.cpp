#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
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
  // get the reachable pages
  std::set<unsigned> set = book1.getReachable();
  // get the solution to WIN
  std::vector<std::pair<unsigned, unsigned> > solution = book1.solveStory(set);
  // if the solution has no element
  if(solution.size() == 0) {
    std::cout << "There is no way to win" << std::endl;
    return EXIT_SUCCESS;
  }
  // print the solution
  book1.printSolution(solution);
	
  return EXIT_SUCCESS;
}
