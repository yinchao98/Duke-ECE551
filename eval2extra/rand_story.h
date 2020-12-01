#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <cstdlib>
#include <cstdio>
#include <string>
#include "category.h"

/*function: errorHandling
			print the errorMsg to stderr and exit*/
void errorHandling(std::string errorMsg);

/*function: checkArgs
			check the number of arguments*/
void checkArgs(int argc, int expected);

/*function: parseContent
			given a FILE pointer, parse all the content
			in the file to a string*/
std::string parseContent(char* file);

/*function: parseLine
			given a FILE pointer, parse the line into
			catarray struct*/
Category<std::string, std::string> parseLine(char* file);

/*function: replaceTemplate
			given the story template string, the catarray_t pointer 
			and one int reused to represent whether to reuse the 
			word or not, replace the blank with corresponding 
			replace word*/
std::string replaceTemplate(std::string story, Category<std::string, std::string> & cat);

#endif
