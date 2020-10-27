#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	//checkargs
	char* result = NULL;
	FILE* category = NULL;
	FILE* story = NULL;
	char* storyTemplate = NULL;
	if(argc == 4) {
		category = tryOpen(argv[2]);
		story = tryOpen(argv[3]);
		catarray_t* array = parseLine(category);
		storyTemplate = parseContent(story);
		result = replaceTemplate(storyTemplate, array, 0);
	} else {
		category = tryOpen(argv[1]);
		story = tryOpen(argv[2]);
		catarray_t* array = parseLine(category);
		storyTemplate = parseContent(story);
		result = replaceTemplate(storyTemplate, array, 1);
	}
	printf("%s", result);
	free(storyTemplate);
	free(result);
	tryClose(category);
	tryClose(story);
	return EXIT_SUCCESS;
}
