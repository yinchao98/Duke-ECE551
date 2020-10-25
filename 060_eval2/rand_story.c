#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// given a filename, and try to open the file
FILE* tryOpen(char* fileName) {
	FILE* f = fopen(fileName, "r");
	// if fails, exits
	if(f == NULL) {
		fprintf(stderr, "Fail to open the file!\n");
		exit(EXIT_FAILURE);
	}
	return f;
}

char* parseContent(FILE* f) {
	int c = 0;
	char* content = NULL;
	int count = 0;
	while((c = fgetc(f)) != EOF) {
		content = realloc(content, (count + 1) * sizeof(*content));
		content[count] = c;
		count++;
	}
	content = realloc(content, (count + 1) * sizeof(*content));
	content[count] = '\0';
	return content;

}

char* findTemplate(char* str) {
	char* ptr = str;
	if(*ptr != '_') {
		fprintf(stderr, "Invalid\n");
		exit(EXIT_FAILURE);
	}
	ptr++;
	return strchr(ptr, '_');
}

char* replaceBlank(char* story) {
	const char* cat = chooseWord("verb", NULL);
	int catLength = strlen(cat);
	// result stores the final replaced string
	char* result = NULL;
	char* ptr = story;
	int count = 0;
	while(*ptr != '\0') {
		if(*ptr != '_') {
			result = realloc(result, (count + 2) * sizeof(*result));
			result[count] = *ptr;
			result[count + 1] = '\0';
			ptr++;
			count++;
		} else {
			ptr = findTemplate(ptr);
			if(ptr == NULL) {
				fprintf(stderr, "Invalid format\n");
				exit(EXIT_FAILURE);
			}
			count += catLength;
			result = realloc(result, (count + 1) * sizeof(*result));
			strcat(result, cat);
			result[count] = '\0';
			ptr++;
		}
	}
	return result;
}

char* templateStr(char* start, char* end) {
	char* ptr = start + 1;
	if(*end != '_') {
		fprintf(stderr, "Invalid format\n");
		exit(EXIT_FAILURE);
	}
	int length = end - start - 1;
	char* template = malloc((length + 1) * sizeof(*template));
	strncpy(template, ptr, length);
	template[length] = '\0';
	return template;
}

int checkInt(char* template) {
	int value = atoi(template);
	return value;
}

int checkTemplate(char* template, catarray_t* array) {
	for(int i = 0; i < array->n; i++) {
		if(!strcmp(template, array->arr[i].name)) {
			return i;
		}
	}
	return -1;
}

char* getTemplateWord(char* template, category_t usedWord, catarray_t* array) {
	int i = checkInt(template);
	int j = checkTemplate(template, array);
	const char* replaceWord = NULL;
	if(i >= 1 && i <= usedWord.n_words) {
		replaceWord = usedWord.words[usedWord.n_words - i];
	}else if(j != -1) {
		replaceWord = chooseWord(template, array);
	} else {
		fprintf(stderr, "Invalid template format!\n");
		exit(EXIT_FAILURE);
	}
	return (char*)replaceWord;
}

char* replaceTemplate(char* story, catarray_t* array) {
	char* result = NULL;
	char* ptr = story;
	char* temp = NULL;
	char* template = NULL;
	char* replaceWord = NULL;
	int count = 0;
	category_t usedWord;
	usedWord.n_words = 0;
	usedWord.words = NULL;
	while(*ptr != '\0') {
		if(*ptr != '_') {
			result = realloc(result, (count + 2) * sizeof(*result));
			result[count] = *ptr;
			result[count + 1] = '\0';
			ptr++;
			count++;
		} else {
			temp = findTemplate(ptr);
			template = templateStr(ptr, temp);
			// if template is an integer >= 1
			replaceWord = getTemplateWord(template, usedWord, array);
			usedWord.n_words++;
			usedWord.words = realloc(usedWord.words, (usedWord.n_words) * sizeof(*usedWord.words));
			usedWord.words[usedWord.n_words - 1] = replaceWord;
			count += strlen(replaceWord);
			result = realloc(result, (count + 1) * sizeof(*result));
			strcat(result, replaceWord);
			result[count] = '\0';
			ptr = temp + 1;
		}
	}
	return result;
}

char* getName(char* line) {
	char* name = NULL;
	char* temp1 = strchr(line, ':');
    if(temp1 == NULL) {
    	fprintf(stderr, "Invalid format!\n");
      	exit(EXIT_FAILURE);
    }
    name = malloc((temp1 - line + 1) * sizeof(*name));
    strncpy(name, line, (temp1 - line));
    name[temp1 - line] = '\0';
    return name;
}

char* getWord(char* line) {
	char* word = NULL;
	char* temp1 = strchr(line, ':');
	temp1++;
    char* temp2 = strchr(line, '\n');
    word = malloc((temp2 - temp1 + 1) * sizeof(*word));
    strncpy(word, temp1, (temp2 - temp1));
    word[temp2 - temp1] = '\0';
    return word;
}

catarray_t* parseLine(FILE* f) {
	char * curr = NULL;
	char * name = NULL;
	char * word = NULL;
	size_t sz = 0;
	catarray_t* result = malloc(sizeof(*result));
	result->n = 0;
	while (getline(&curr,&sz, f) >= 0) {
      // name
      name = getName(curr);
      // word
      word = getWord(curr);
      int exist = 0;
      // if already have the category
      for(size_t i = 0; i < result->n; i++) {
      	if(!strcmp(name, result->arr[i].name)) {
      		(result->arr[i].n_words)++;
      		result->arr[i].words = realloc(result->arr[i].words, result->arr[i].n_words * sizeof(*(result->arr[i].words)));
      		result->arr[i].words[(result->arr[i].n_words) - 1] = word;
      		exist = 1;
      		break;
      	}
      }
      // add new category
      if(!exist) {
		result->n++;
	    result->arr = realloc(result->arr, (result->n) * sizeof(*result->arr));
	    result->arr[(result->n) - 1].name = name;
	    result->arr[(result->n) - 1].n_words = 1;
	    result->arr[(result->n) - 1].words = realloc(result->arr[(result->n) - 1].words, result->arr[(result->n) - 1].n_words * sizeof(*(result->arr[(result->n) - 1].words)));
	    result->arr[(result->n) - 1].words[result->arr[(result->n) - 1].n_words - 1] = word;
	    curr = NULL;
      }
    }
    return result;
}

