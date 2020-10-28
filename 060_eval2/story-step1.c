#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	
	// check number of arguments
	checkArgs(argc, 2);
	// open the story file
	FILE* f = tryOpen(argv[1]);
	// get the story template string
	char* storyTemplate = parseContent(f);
	// replace the template with "cat"
	char* result = replaceTemplate(storyTemplate, NULL, 1);
	// print out the replaced string
	printf("%s", result);
	// free the memory
	free(storyTemplate);
	free(result);
	// close the file
	tryClose(f);

	return EXIT_SUCCESS;
}



