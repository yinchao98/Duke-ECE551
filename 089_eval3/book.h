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
	Book(): pages(), winPages(), losePages(){}
	~Book() {}
	void addPage(Page page);
	void readPages(char* dirPath);
	void checkPages();
	void startStory();
	std::set<unsigned> getReachable();
	void notReachable(std::set<unsigned> reachable);
	std::vector<std::pair<unsigned, unsigned> > solveStory(std::set<unsigned> reachable);
	void printSolution(std::vector<std::pair<unsigned, unsigned> > solution);
};
