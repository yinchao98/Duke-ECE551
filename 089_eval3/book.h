#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "page.h"

class Book {
 private:	
  std::vector<Page> pages;
  std::vector<unsigned> winPages;
  std::vector<unsigned> losePages;
 public:
  // default constructor
 Book(): pages(), winPages(), losePages(){}
  // default destructor
  ~Book() {}
  // add page into pages
  void addPage(Page page);
  // read each page from the given directory
  void readPages(char* dirPath);
  // check if the pages are valid 
  void checkPages();
  // from page1 to start the story
  void startStory();
  // get reachable pages
  std::set<unsigned> getReachable();
  // print out unreachable pages
  void notReachable(std::set<unsigned> reachable);
  // return one solution to WIN
  std::vector<std::pair<unsigned, unsigned> > solveStory(std::set<unsigned> reachable);
  // print out the solution
  void printSolution(std::vector<std::pair<unsigned, unsigned> > solution);
};
