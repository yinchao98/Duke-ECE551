#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	checkArgs(argc, 2);
	FILE* f = tryOpen(argv[1]);
	char* storyTemplate = parseContent(f);
	//char* result = replaceBlank(storyTemplate);
	char* result = replaceTemplate(storyTemplate, NULL, 1);
	printf("%s", result);
	free(storyTemplate);
	free(result);
	tryClose(f);

	return EXIT_SUCCESS;
}



