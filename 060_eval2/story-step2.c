#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	FILE* f = tryOpen(argv[1]);
	catarray_t* array = parseLine(f);
	printWords(array);
	
	return EXIT_SUCCESS;
}
