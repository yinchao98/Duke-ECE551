#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
	FILE *f = fopen(fname, "r");
	if (f == NULL) {
		fprintf(stderr,"Could not open the file!\n");
		exit(EXIT_FAILURE);
	}
	size_t sz = 0;
	ssize_t len = 0;
	char* line = NULL;
	kvarray_t* kvarrayList = malloc(sizeof(*kvarrayList));
	kvarrayList->kvpairArray = malloc(sizeof(*(kvarrayList->kvpairArray)));
	kvarrayList->length = 0;

	int arrayLength = 0;
	while((len = getline(&line, &sz, f)) >= 0) {

		//key-value pair
		kvpair_t* kvpair = malloc(sizeof(*kvpair));
		kvpair->key = malloc(sizeof(*(kvpair->key)));
		kvpair->value = malloc(sizeof(*(kvpair->value)));

		char* pointer = strchr(line, '=');
		if(pointer == NULL){
			exit(EXIT_FAILURE);
		}
		// key
		kvpair->key = realloc(kvpair->key, (pointer - line + 1) * sizeof(*(kvpair->key)));
		strncpy(kvpair->key, line, pointer - line);
		kvpair->key[pointer - line] = '\0';
		// value
		size_t i = pointer - line + 1;
		size_t j = 0;
		while(line[i] != '\n') {
			kvpair->value = realloc(kvpair->value, (j + 2) * sizeof(*(kvpair->value)));
			kvpair->value[j] = line[i];
			i++;
			j++;
		}
		kvpair->value[j] = '\0';
		// put key-value pairs into array
		arrayLength++;
		kvarrayList->length = arrayLength;
		kvarrayList->kvpairArray = realloc(kvarrayList->kvpairArray, (kvarrayList->length) * sizeof(*(kvarrayList->kvpairArray)));
		kvarrayList->kvpairArray[arrayLength - 1] = kvpair;

	}
	if(fclose(f) == -1) {
		fprintf(stderr,"Could not close the file!\n");
		exit(EXIT_FAILURE);
	}
	free(line);
	return kvarrayList;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
	for(size_t i = 0; i < pairs->length; i++) {
		free(pairs->kvpairArray[i]->key);
		free(pairs->kvpairArray[i]->value);
		free(pairs->kvpairArray[i]);
	}
	free(pairs->kvpairArray);
	free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
	for(int i = 0; i < pairs->length; i++) {
		printf("key = '%s' value = '%s'\n", pairs->kvpairArray[i]->key, pairs->kvpairArray[i]->value);
	}

}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
	for(size_t i = 0; i < pairs->length; i++) {
		if(!strcmp(key, pairs->kvpairArray[i]->key)){
			return pairs->kvpairArray[i]->value;
		}
	}
	return NULL;
}

