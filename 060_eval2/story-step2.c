#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

	// check number of arguments
	checkArgs(argc, 2);
	// open the file
	FILE* f = tryOpen(argv[1]);
	// parse the line of the file into the struct
	catarray_t* array = parseLine(f);
	// print the struct
	printWords(array);
	// free the struct
	freeArray(array);
	// close the file
	tryClose(f);
	
	return EXIT_SUCCESS;
}
