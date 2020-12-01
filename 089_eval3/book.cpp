#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "book.h"

// add page into pages
void Book::addPage(Page page) {
  pages.push_back(page);
}

// read each page from the given directory
void Book::readPages(char* dirPath) {
  bool openPage = true;
  unsigned num = 1;
  // start from page1 to read
  while(true) {
    Page page;
    // give the specific filename
    std::string fileName(dirPath);
    fileName += "//page";
    fileName += std::to_string(num);
    fileName += ".txt";
    const char* file = fileName.c_str();
    // read the information into page
    openPage = page.readPage((char*)file);
    if(!openPage) {
      break;
    }
    // add the page into pages vector
    addPage(page);
    // add the specific page into win or lose page
    if(page.isEnd()) {
      if(page.result) {
	winPages.push_back(num);
      } else {
	losePages.push_back(num);
      }
    }
    num++;
  }
  // page1 must exist
  if(pages.size() == 0) {
    errorHandling("page1 doesn't exist");
  }
}

// check if the pages are valid 
void Book::checkPages() {
  // there are at least one win page and one lose page
  if(winPages.size() < 1 || losePages.size() < 1) {
    errorHandling("WIN page or LOSE page doesn't exist");
  }
  std::vector<bool> pageVisited(pages.size(), false);
  pageVisited[0] = true;
  for(size_t i = 0; i < pages.size(); i++) {
    if(pages[i].isEnd() == true) {
      continue;
    } 
    for(size_t j = 0; j < pages[i].navigation.size(); j++) {
      unsigned pageNum = pages[i].navigation[j].first;
      // Every page that is referenced by a choice is valid 
      if(pageNum >= 1 && pageNum <= pages.size()) {
	pageVisited[pageNum - 1] = true;
	pages[pageNum - 1].refPage.push_back(std::pair<unsigned, unsigned>(i + 1, j + 1));
      } else {
	errorHandling("page conditions are not met");
      }
    }
  }
  // Every page (except page 1) is referenced by at least one *other page
  for(size_t i = 0; i < pageVisited.size(); i++) {
    if(pageVisited[i] == false) {
      errorHandling("page conditions are not met");
    }
  }
}

// from page1 to start the story
void Book::startStory() {
  pages[0].printPage();
  int pageNum = 1;
  while (true) {
    if(pages[pageNum - 1].isEnd()) {
      return;
    }
    std::string s;
    std::getline(std::cin, s);
    bool invalid = false;
    // check if the input pageNum is a valid number
    for(size_t i = 0; i < s.length(); i++) {
      if(s[i] < 48 || s[i] > 57) {
	invalid = true;
      }
    }
    int choiceNum = atoi(s.c_str());
    if(choiceNum < 1 || choiceNum > pages[pageNum - 1].navigation.size()) {
      invalid = true;
    }
    if(invalid) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
      continue;
    }
    // print out next specific page
    pageNum = pages[pageNum - 1].navigation[choiceNum - 1].first;
    pages[pageNum - 1].printPage();
  }
}

// get reachable pages
std::set<unsigned> Book::getReachable() {
  std::set<unsigned> reachableSet;
  reachableSet.insert(1);
  std::set<unsigned> tempSet = reachableSet;
  while(true) {
    std::set<unsigned>::iterator it = reachableSet.begin();
    //For each page in the set
    while(it != reachableSet.end()) {
      if(pages[*it - 1].isEnd()) {
	++it;
	continue;
      }
      //Add to the set all the pages that are the targets of that page's choices
      for(size_t i = 0; i < pages[*it - 1].navigation.size(); i++) {
	reachableSet.insert(pages[*it - 1].navigation[i].first);
      }
      ++it;
    }
    // If the set is not changed, then finish
    if(reachableSet.size() == tempSet.size()) {
      break;
    }
    // If the set is changed, repeat
    tempSet = reachableSet;
  }
  return reachableSet;
}

// print out unreachable pages
void Book::notReachable(std::set<unsigned> reachable) {
  // in numerical order, find if the page is in the reachable set
  for(size_t i = 0; i < pages.size(); i++) {
    std::set<unsigned>::iterator it;
    it = reachable.find(i + 1);
    if(it == reachable.end()) {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
    ++it;
  }
}

// return one solution to WIN
std::vector<std::pair<unsigned, unsigned> > Book::solveStory(std::set<unsigned> reachable) {
  std::vector<std::pair<unsigned, unsigned> > solution;
  // from the reachable set, find a page that is WIN
  std::set<unsigned>::iterator it = reachable.begin();
  while(it != reachable.end()) {
    if(pages[*it - 1].isEnd()) {
      if(pages[*it - 1].result) {
	break;
      }
    }
    ++it;
  }
  // if there's no WIN page in the set, return a null vector
  if(it == reachable.end()) {
    return solution;
  }
  // insert the WIN page
  solution.insert(solution.begin(), std::pair<unsigned, unsigned>(*it, 0));
  unsigned pageNum = *it;
  unsigned choice;
  // from the WIN page work backward until get to the page1
  while(pageNum != 1) {
    for(size_t i = 0; i < pages[pageNum - 1].refPage.size(); i++) {
      // get one reference page in reachable set
      it = reachable.find(pages[pageNum - 1].refPage[i].first);
      if(it != reachable.end()) {
	choice = pages[pageNum - 1].refPage[i].second;
	break;
      }
    }
    pageNum = *it;
    solution.insert(solution.begin(), std::pair<unsigned, unsigned>(pageNum, choice));
  }
  return solution;
}

// print out the solution
void Book::printSolution(std::vector<std::pair<unsigned, unsigned> > solution) {
  for(size_t i = 0; i < solution.size(); i++) {
    if(solution[i].second == 0) {
      std::cout << "Page " << solution[i].first << " WIN" << std::endl; 
    } else {
      std::cout << "Page " << solution[i].first << " Choice " << solution[i].second << std::endl;
    }
  }
}

