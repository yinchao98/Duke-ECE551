#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	checkArgs(argc, 2);
	FILE* f = tryOpen(argv[1]);
	catarray_t* array = parseLine(f);
	printWords(array);
	freeArray(array);
	tryClose(f);
	
	return EXIT_SUCCESS;
}
