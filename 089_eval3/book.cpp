#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "book.h"

void Book::addPage(Page page) {
	pages.push_back(page);
}

void Book::readPages(char* dirPath) {
	bool openPage = true;
	unsigned num = 1;
	while(true) {
		Page page;
		std::string fileName(dirPath);
		fileName += "//page";
		fileName += std::to_string(num);
		fileName += ".txt";
		const char* file = fileName.c_str();
		openPage = page.readPage((char*)file);
		if(!openPage) {
			break;
		}
		addPage(page);
		if(page.isEnd()) {
			if(page.result) {
				winPages.push_back(num);
			} else {
				losePages.push_back(num);
			}
		}
		num++;
	}
	if(pages.size() == 0) {
		std::cerr << "page1 doesn't exist" << std::endl;
    	exit(EXIT_FAILURE);
	}
}

void Book::checkPages() {
	std::vector<bool> pageVisited(pages.size(), false);
	pageVisited[0] = true;
	for(size_t i = 0; i < pages.size(); i++) {
		if(pages[i].isEnd() == true) {
			continue;
		} 
		for(size_t j = 0; j < pages[i].navigation.size(); j++) {
			unsigned pageNum = pages[i].navigation[j].first;
			if(pageNum >= 1 && pageNum <= pages.size()) {
				pageVisited[pageNum - 1] = true;
			} else {
				std::cerr << "page conditions are not met" << std::endl;
    			exit(EXIT_FAILURE);
			}
		}
	}
	for(size_t i = 0; i < pageVisited.size(); i++) {
		if(pageVisited[i] == false) {
			std::cerr << "page conditions are not met" << std::endl;
        	exit(EXIT_FAILURE);
		}
	}
}

void Book::startStory() {
	pages[0].printPage();
	int pageNum = 1;
	while (true) {
		if(pages[pageNum - 1].isEnd()) {
			exit(EXIT_SUCCESS);
		}
      	std::string s;
      	std::getline(std::cin, s);
      	pageNum = atoi(s.c_str());
      	if(pageNum <= 1 || pageNum > pages.size()) {
      		std::cout << "That is not a valid choice, please try again" << std::endl;
      		continue;
      	}
      	pages[pageNum - 1].printPage();
    }
}

std::set<unsigned> Book::getReachable() {
	std::set<unsigned> reachableSet;
	reachableSet.insert(1);
	std::set<unsigned> tempSet = reachableSet;
	while(true) {
		std::set<unsigned>::iterator it = reachableSet.begin();
		while(it != reachableSet.end()) {
			if(pages[*it - 1].isEnd()) {
				++it;
				continue;
			}
			for(size_t i = 0; i < pages[*it - 1].navigation.size(); i++) {
				reachableSet.insert(pages[*it - 1].navigation[i].first);
			}
			++it;
		}
		if(reachableSet == tempSet) {
			break;
		}
	}
	return reachableSet;
}

void Book::notReachable(std::set<unsigned> reachable) {
	for(size_t i = 0; i < pages.size(); i++) {
		std::set<unsigned>::iterator it;
		it = reachable.find(i + 1);
		if(it == reachable.end()) {
			std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
		}
		++it;
	}
}

