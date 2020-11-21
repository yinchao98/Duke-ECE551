#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "page.h"

// TODO: store the number of page

void Page::checkChoices(std::vector<std::string> choices) {
	if(choices[0] == "WIN" || choices[0] == "LOSE") {
		if(choices.size() == 1) {
			if(choices[0] == "WIN") {
				addResult(true);
			} else {
				addResult(false);
			}
		} else {
			std::cerr << "wrong page file format -> navigation" << std::endl;
        	exit(EXIT_FAILURE);
		}
	} else {
		std::vector<std::string>::iterator it = choices.begin();
		while(it != choices.end()) {
			std::string str(*it);
			size_t index1 = str.find_first_of(':');
			if(index1 == std::string::npos) {
    			std::cerr << "wrong page file format -> navigation" << std::endl;
        		exit(EXIT_FAILURE);
    		}
			std::string pageNum(str.substr(0, index1));
			std::string choice(str.substr(++index1));
			// TODO: change the type
			int value = atoi(pageNum.c_str());
			if(value < 1) {
				std::cerr << "wrong page file format -> navigation" << std::endl;
        		exit(EXIT_FAILURE);
			}
			addNavigation(value, choice);
			++it;
		}
	}
}

bool Page::readPage(char* pageFile) {
	std::ifstream f;
	f.open(pageFile);
	if (f.fail()) {
        return false;
    }
    std::vector<std::string> choices;
    std::string text;
    bool partition = false;
    while (!f.eof()) {
        std::string s;
        std::getline(f, s);
        if(partition) {
        	text += s;
        	text += '\n';
        }
        else 
        	if(s[0] != '#') {
        		choices.push_back(s);
        	} else {
        		partition = true;
        	}
    }
    if(!partition) {
    	std::cerr << "wrong page file format -> partition" << std::endl;
        exit(EXIT_FAILURE);
    }
    // TODO: two more newlines in text
    addText(text);
    checkChoices(choices);
    f.close();
    return true;
}

void Page::addResult(bool r) {
	result = r;
}

void Page::addNavigation(unsigned pageNum, std::string choice) {
	navigation.push_back(std::pair<unsigned, std::string>(pageNum, choice));
}

void Page::addText(std::string t) {
	text = t;
}

void Page::printPage() {
	std::cout << text;
	if(isEnd()) {
		if(result == true) {
			std::cout << "Congratulations! You have won. Hooray!" << std::endl;
		} else {
			std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
		}
	} else {
		std::cout << "What would you like to do ?" << std::endl;
		std::cout << std::endl;
		std::vector<std::pair<unsigned, std::string> >::iterator it = navigation.begin();
		unsigned i = 1;
		while(it != navigation.end()) {
			std::cout << " " << i << ". ";
			std::cout << it->second << std::endl;
			++it;
			++i;
		}
	}
}

bool Page::isEnd() {
	return navigation.size() == 0;
}


