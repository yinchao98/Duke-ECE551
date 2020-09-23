#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
	char* suffix = ".counts";

	int inputLen = strlen(inputName);
	int suffixLen = strlen(suffix);

	char* outputFileName = malloc((inputLen + suffixLen + 1) * sizeof(*outputFileName));
	strcpy(outputFileName, inputName);
	strcat(outputFileName, suffix);

	return outputFileName;

}
