#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
	if(winPages.size() < 1 || losePages.size() < 1) {
		std::cerr << "WIN page or LOSE page doesn't exist" << std::endl;
    	exit(EXIT_FAILURE);
	}
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
				pages[pageNum - 1].refPage.push_back(std::pair<unsigned, unsigned>(i + 1, j + 1));
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
      	int choiceNum = atoi(s.c_str());
      	if(choiceNum < 1 || choiceNum > pages[pageNum - 1].navigation.size()) {
      		std::cout << "That is not a valid choice, please try again" << std::endl;
      		continue;
      	}
      	pageNum = pages[pageNum - 1].navigation[choiceNum - 1].first;
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
		if(reachableSet.size() == tempSet.size()) {
			break;
		}
		tempSet = reachableSet;
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

std::vector<std::pair<unsigned, unsigned> > Book::solveStory(std::set<unsigned> reachable) {
	std::set<unsigned>::iterator it = reachable.begin();
	while(it != reachable.end()) {
		if(pages[*it - 1].isEnd()) {
			if(pages[*it - 1].result) {
				break;
			}
		}
		++it;
	}
	if(it == reachable.end()) {
		std::cout << "There is no way to win" << std::endl;
		exit(EXIT_SUCCESS);
	}
	std::vector<std::pair<unsigned, unsigned> > solution;
	solution.insert(solution.begin(), std::pair<unsigned, unsigned>(*it, 0));
	unsigned pageNum = *it;
	unsigned choice;
	while(pageNum != 1) {
		for(size_t i = 0; i < pages[pageNum - 1].refPage.size(); i++) {
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

void Book::printSolution(std::vector<std::pair<unsigned, unsigned> > solution) {
	for(size_t i = 0; i < solution.size(); i++) {
		if(solution[i].second == 0) {
			std::cout << "Page " << solution[i].first << " WIN" << std::endl; 
		} else {
			std::cout << "Page " << solution[i].first << " Choice " << solution[i].second << std::endl;
		}
	}
}

