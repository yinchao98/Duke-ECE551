#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //WRITE ME
	// initialize count_t
	counts_t* countList = malloc(sizeof(*countList));
	countList->countsArray = malloc(sizeof(*(countList->countsArray)));
	countList->arraySize = 0;
	countList->unknown = malloc(sizeof(*(countList->unknown)));
	char* unknownName = "<unknown>";
	// initialize unknown
	countList->unknown->key = malloc((strlen(unknownName) + 1) * sizeof(*(countList->unknown->key)));
	strcpy(countList->unknown->key, unknownName);
	countList->unknown->count = 0;

	return countList;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
	// if name is NULL - > UNKNOWN
	if (name == NULL) {
		(c->unknown->count)++;
	} else {
		// else
		int nameLen = strlen(name);
		int countsSize = c->arraySize;
		for (int i = 0; i < countsSize; i++) {
			// key existed
			if(!strcmp(c->countsArray[i]->key, name)) {
				(c->countsArray[i]->count)++;
				return;
			} 
		}
		// new key
		(c->arraySize)++;
		countsSize++;
		c->countsArray = realloc(c->countsArray, (countsSize) * sizeof(*(c->countsArray)));
		c->countsArray[countsSize - 1] = malloc(sizeof(**(c->countsArray)));
		c->countsArray[countsSize - 1]->key = malloc((nameLen + 1) * sizeof(*(c->countsArray[countsSize - 1]->key)));
		c->countsArray[countsSize - 1]->count = 1;
		strcpy(c->countsArray[countsSize - 1]->key, name);
	}
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
	int countsSize = c->arraySize;
	for (int i = 0; i < countsSize; i++) {
		fprintf(outFile, "%s:%d\n", c->countsArray[i]->key, c->countsArray[i]->count);
	}
	if(c->unknown->count != 0) {
		fprintf(outFile, "%s:%d\n", c->unknown->key, c->unknown->count);
	}
}

void freeCounts(counts_t * c) {
  //WRITE ME
	int countsSize = c->arraySize;
	for (int i = 0; i < countsSize; i++) {
		free(c->countsArray[i]->key);
		free(c->countsArray[i]);
	}
	free(c->countsArray);
	free(c->unknown->key);
	free(c->unknown);
	free(c);
}
