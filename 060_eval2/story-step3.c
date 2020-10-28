#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

	// check the number of arguments
	checkArgs(argc, 3);
	// open two files
	FILE* category = tryOpen(argv[1]);
	FILE* story = tryOpen(argv[2]);
	// parse the line into the struct
	catarray_t* array = parseLine(category);
	// extract the story template
	char* storyTemplate = parseContent(story);
	// replace the template with corresponding words
	char* result = replaceTemplate(storyTemplate, array, 1);
	// print the replaced string
	printf("%s", result);
	// free the memory 
	free(storyTemplate);
	free(result);
	// close two files
	tryClose(category);
	tryClose(story);
	
	return EXIT_SUCCESS;
}
