#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "rand_story.h"

int main(int argc, char** argv) {

	// check the number of arguments
	checkArgs(argc, 3);
	// parse the line into the struct
	Category<std::string, std::string> category = parseLine(argv[1]);
	category.printCat();
	// extract the story template
	std::string storyTemplate = parseContent(argv[2]);
	// replace the template with corresponding words
	std::string result = replaceTemplate(storyTemplate, category);
	// print the replaced string
	std::cout << result;

	
	return EXIT_SUCCESS;
}
