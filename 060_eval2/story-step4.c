#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

	char* catFileName = NULL;
	char* storyFileName = NULL;
	int reused = 0;
	// if there's one optional argument
	if(argc == 4) {
		// check if the optional argument is -n
		checkOptArg(argv[1]);
		// get the file name from the third and fourth argument
		catFileName = argv[2];
		storyFileName = argv[3];
	} else if (argc == 3){ // if there's no optional argument
		// get the file name from the second and third argument
		catFileName = argv[1];
		storyFileName = argv[2];
		// the word can be reused
		reused = 1;
	}
	// open two files
	FILE* category = tryOpen(catFileName);
	FILE* story = tryOpen(storyFileName);
	// parse the line into struct
	catarray_t* array = parseLine(category);
	// extract the story template string
	char* storyTemplate = parseContent(story);
	// replace the template with words 
	char* result = replaceTemplate(storyTemplate, array, reused);
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
