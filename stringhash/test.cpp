#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "stringhash.h"
#include <vector>
#include <map>

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "wrong number of arguments" << std::endl;
		return EXIT_FAILURE;
	}
	int m = atoi(argv[1]);
	StringHasher hash(m);
	std::string inputStr;
	std::vector<std::string> dataVector;
	while(!std::cin.eof()) {
		std::string s;
      	std::getline(std::cin, s);
      	dataVector.push_back(s);
	}
	std::vector<std::string>::iterator it = dataVector.begin();
	std::map<unsigned, unsigned> collisions;
	
	while(it != dataVector.end()) {
		unsigned key = hash(*it);
		std::map<unsigned, unsigned>::iterator it2 = collisions.find(key);
		if(it2 != collisions.end()) {
			(*it2).second++;
		} else {
			collisions.insert(std::pair<unsigned, unsigned>(key, 0));
		}
		++it;
	}
	std::map<unsigned, unsigned>::iterator it3 = collisions.begin();
	unsigned maxCollisionNum = 0;
	while(it3 != collisions.end()) {
		std::cout << "#" << (*it3).first << ", " << (*it3).second << std::endl;
		if(maxCollisionNum < (*it3).second) {
			maxCollisionNum = (*it3).second;
		}
		++it3;
	}
	std::cout << "#maxCollisionNum = " << maxCollisionNum << std::endl;
	return EXIT_SUCCESS;
}
