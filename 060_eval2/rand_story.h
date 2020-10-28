#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*function: checkArgs
			check the number of arguments*/
void checkArgs(int argc, int expected);

/*function: checkOptArg
			check the optional argument*/
void checkOptArg(char* argv);

/*function: tryOpen
			given a filename, try to open*/
FILE* tryOpen(char* fileName);

/*function: tryClose
			given a FILE pointer, try to close*/
void tryClose(FILE* f);

/*function: freeArray
			given the catarray_t pointer, free all the memory about it*/
void freeArray(catarray_t* array);

/*function: parseContent
			given a FILE pointer, parse all the content
			in the file to a string*/
char* parseContent(FILE* f);

/*function: parseLine
			given a FILE pointer, parse the line into
			catarray struct*/
catarray_t* parseLine(FILE* f);

/*function: replaceTemplate
			given the story template string, the catarray_t pointer 
			and one int reused to represent whether to reuse the 
			word or not, replace the blank with corresponding 
			replace word*/
char* replaceTemplate(char* story, catarray_t* array, int reused);


#endif
