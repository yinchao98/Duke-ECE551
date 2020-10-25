#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	FILE* f = tryOpen(argv[1]);
	char* storyTemplate = parseContent(f);
	char* result = replaceBlank(storyTemplate);
	printf("%s", result);
	return EXIT_SUCCESS;
}



