#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//any functions you want your main to use

// try to open a file
FILE* tryOpen(char* fileName);
char* parseContent(FILE* f);
char* replaceTemplate(char* story, catarray_t* array);
char* replaceBlank(char* story);
catarray_t* parseLine(FILE* f);




#endif
