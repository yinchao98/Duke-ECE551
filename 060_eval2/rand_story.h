#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//any functions you want your main to use

// try to open a file
void checkArgs(int argc, int expected);
FILE* tryOpen(char* fileName);
void tryClose(FILE* f);
void freeArray(catarray_t* array);
char* parseContent(FILE* f);
char* replaceTemplate(char* story, catarray_t* array, int reused);
char* replaceBlank(char* story);
catarray_t* parseLine(FILE* f);




#endif
