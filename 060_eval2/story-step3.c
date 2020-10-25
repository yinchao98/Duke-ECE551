#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	FILE* category = tryOpen(argv[1]);
	FILE* story = tryOpen(argv[2]);
	catarray_t* array = parseLine(category);
	char* storyTemplate = parseContent(story);
	char* result = replaceTemplate(storyTemplate, array);
	printf("%s", result);
	
	return EXIT_SUCCESS;
}
