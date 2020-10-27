#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	//checkargs
	FILE* category = tryOpen(argv[2]);
	FILE* story = tryOpen(argv[3]);
	catarray_t* array = parseLine(category);
	printWords(array);
	char* storyTemplate = parseContent(story);
	printf("%s", storyTemplate);
	char* result = NULL;
	if(argc == 4) {
		result = replaceTemplate(storyTemplate, array, 0);
	} else {
		result = replaceTemplate(storyTemplate, array, 1);
	}
	
	printf("%s", result);
	
	return EXIT_SUCCESS;
}
