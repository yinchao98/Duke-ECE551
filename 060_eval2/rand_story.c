#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*function: errorHandling
  print the errorMsg to stderr and exit*/
void errorHandling(const char* errorMsg) {
  fprintf(stderr, "%s", errorMsg);
  exit(EXIT_FAILURE);
}

/*function: checkArgs
  check the number of arguments*/
void checkArgs(int argc, int expected) {
  // if argc doesn't match the expected, exits
  if(argc != expected) {
    errorHandling("Invalid argc!\n");
  }
}

/*function: checkOptArg
  check the optional argument*/
void checkOptArg(char* argv) {
  if(strcmp(argv, "-n") != 0) {
    errorHandling("Invalid optional argument!\n");
  }
}

/*function: tryOpen
  given a filename, try to open*/
FILE* tryOpen(char* fileName) {
  FILE* f = fopen(fileName, "r");
  // if fails, exits
  if(f == NULL) {
    errorHandling("Fail to open the file!\n");
  }
  return f;
}

/*function: tryClose
  given a FILE pointer, try to close*/
void tryClose(FILE* f) {
  // if fails, exits
  if(fclose(f) == -1) {
    errorHandling("Fail to close the file!\n");
  }
}

/*function: parseContent
  given a FILE pointer, parse all the content
  in the file to a string*/
char* parseContent(FILE* f) {
  int c = 0;
  char* content = NULL;
  int count = 0;
  // get the character into c, until meet the end of file
  while((c = fgetc(f)) != EOF) {
    content = realloc(content, (count + 1) * sizeof(*content));
    content[count] = c;
    count++;
  }
  // null terminate
  content = realloc(content, (count + 1) * sizeof(*content));
  content[count] = '\0';
  return content;
}

/*function: getName
  given a line, extract the name before semicolon
  character into a char pointer*/
char* getName(char* line) {
  char* name = NULL;
  char* temp1 = strchr(line, ':');
  // if there's not a semicolon, exits
  if(temp1 == NULL) {
    errorHandling("Invalid word format!\n");
  }
  name = malloc((temp1 - line + 1) * sizeof(*name));
  strncpy(name, line, (temp1 - line));
  name[temp1 - line] = '\0';
  return name;
}

/*function: getWord
  given a line, extract the word after semicolon
  character into a char pointer*/
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

/*function: updateCatWord
  given a catarray, the index of category and a word,
  add the word into this category*/
void updateCatWord(catarray_t* cat, size_t i, char* word) {
  // check if this category already has the word
  for(int j = 0; j < cat->arr[i].n_words; j++) {
    if(!strcmp(word, cat->arr[i].words[j])) {
      free(word);
      return;
    }
  }
  // add new word
  cat->arr[i].n_words++;
  cat->arr[i].words = realloc(cat->arr[i].words, cat->arr[i].n_words * sizeof(*(cat->arr[i].words)));
  cat->arr[i].words[(cat->arr[i].n_words) - 1] = word;
}

/*function: addNewCat
  given a catarray, the name of category and a word,
  add one new category and put the word into it*/
void addNewCat(catarray_t* cat, char* name, char* word) {
  // add new category
  cat->n++;
  cat->arr = realloc(cat->arr, (cat->n) * sizeof(*cat->arr));
  cat->arr[(cat->n) - 1].name = name;
  cat->arr[(cat->n) - 1].n_words = 1;
  cat->arr[(cat->n) - 1].words = NULL;
  // add new word
  cat->arr[(cat->n) - 1].words = realloc(cat->arr[(cat->n) - 1].words, cat->arr[(cat->n) - 1].n_words * sizeof(*(cat->arr[(cat->n) - 1].words)));
  cat->arr[(cat->n) - 1].words[cat->arr[(cat->n) - 1].n_words - 1] = word;
}

/*function: parseLine
  given a FILE pointer, parse the line into
  catarray struct*/
catarray_t* parseLine(FILE* f) {
  char * curr = NULL;
  size_t sz = 0;
  catarray_t* result = malloc(sizeof(*result));
  result->arr = NULL;
  result->n = 0;
  while (getline(&curr,&sz, f) >= 0) {
    // extract the name
    char* name = getName(curr);
    // extract the word
    char* word = getWord(curr);
    int exist = 0;
    // from 0 to result->n, try to match the category name
    for(size_t i = 0; i < result->n; i++) {
      // if already have this category
      if(!strcmp(name, result->arr[i].name)) {
	free(name);
	// put the word into this category
	updateCatWord(result, i, word);
	exist = 1;
	break;
      }
    }
    // if the category doesn't exist, add a new category
    if(!exist) {
      addNewCat(result, name, word);
    }
    free(curr);
    curr = NULL;
  }
  free(curr);
  return result;
}

/*function: findTemplate
  given a char pointer which starts with a'_', 
  find if there is a second '_', return the pointer*/
char* findTemplate(char* str) {
  char* ptr = str;
  // if the string is not started with '_', exits
  if(*ptr != '_') {
    errorHandling("Invalid blank format!\n");
  }
  ptr++;
  char* newLine = strchr(ptr, '\n');
  char* end = strchr(ptr, '_');
  // if the string is not ended with '_', exits
  if(end == NULL) {
    errorHandling("Invalid blank format!\n");
  }
  // if the two '_' are not in one line
  if(end - newLine > 0) {
    errorHandling("Invalid blank format!\n");
  }
  return end;
}

/*function: templateStr
  given two pointers which point at the first and 
  second '_', extract the template between two '_'*/
char* templateStr(char* start, char* end) {
  char* ptr = start + 1;
  int length = end - start - 1;
  char* template = malloc((length + 1) * sizeof(*template));
  strncpy(template, ptr, length);
  template[length] = '\0';
  return template;
}

/*function: checkInt
  convert the template string into a number*/
int checkInt(char* template) {
  char* ptr = template;
  // check if all the characters are digits
  while(*ptr != '\0') {
    // if not, return -1
    if(*ptr < 48 || *ptr > 57) {
      return -1;
    }
    ptr++;
  }
  // if it is a valid number, convert to int value
  int value = atoi(template);
  return value;
}

/*function: checkTemplate
  return the index of template in catarray*/
int checkTemplate(char* template, catarray_t* array) {
  for(int i = 0; i < array->n; i++) {
    if(!strcmp(template, array->arr[i].name)) {
      return i;
    }
  }
  // if there's no category named template, return -1
  return -1;
}

/*function: getTemplateWord
  given the template, usedWord category and catarray
  return the corresponding replaceWord*/
char* getTemplateWord(char* template, category_t usedWord, catarray_t* array) {
  const char* replaceWord = NULL;
  // if array is NULL, the replaceWord should return "cat"
  if (array == NULL) {
    replaceWord = chooseWord(template, array);
    return (char*)replaceWord;
  }
  int j = checkTemplate(template, array);
  int i = checkInt(template);
  // if the template is a valid integer
  if(i >= 1 && i <= usedWord.n_words) {
    replaceWord = usedWord.words[usedWord.n_words - i];
    return (char*)replaceWord;
  } 
  // if the template is a valid category name
  if(j != -1) {
    // randomly choose the replaceWord from the category
    replaceWord = chooseWord(template, array);
    return (char*)replaceWord;
  }
  // otherwise, the template is invalid, exits
  errorHandling("Invalid template!\n");
  return NULL;
}

/*function: freeArray
  given the catarray_t pointer, free all the memory about it*/
void freeArray(catarray_t* array) {
  for(int i = 0; i < array->n; i++) {
    for(int j = 0; j < array->arr[i].n_words; j++) {
      free(array->arr[i].words[j]);
    }
    free(array->arr[i].words);
    free(array->arr[i].name);
  }
  free(array->arr);
  free(array);
}

/*function: freeCat
  given the category, free all the memory about it*/
void freeCat(category_t cat) {
  for(int i = 0; i < cat.n_words; i++) {
    free(cat.words[i]);
  }
  free(cat.words);
}

/*function: removeWord
  given the catarray_t, remove the word from the corresponding
  category*/
catarray_t* removeWord(catarray_t* array, char* template, char* word) {
  // create a new catarray_t pointer to store the correct array
  catarray_t* temp = malloc(sizeof(*temp));
  temp->n = array->n;
  temp->arr = malloc(array->n * sizeof(*temp->arr));
  for(int i = 0; i < array->n; i++) {
    // deep copy the category name
    temp->arr[i].name = strdup(array->arr[i].name);
    temp->arr[i].words = NULL;
    temp->arr[i].n_words = 0;
    int count = 0;
    for(int j = 0; j < array->arr[i].n_words; j++) {
      // if the word is that we want to remove, do not copy
      if((!strcmp(word, array->arr[i].words[j])) && (!strcmp(template, array->arr[i].name))) {
	continue;
      } else {
	// copy the word
	temp->arr[i].words = realloc(temp->arr[i].words, (count + 1) * sizeof(*(temp->arr[i].words)));
	temp->arr[i].words[count] = strdup(array->arr[i].words[j]);
	count++;
      }
    }
    temp->arr[i].n_words = count;
  }
  // free the previous old array
  freeArray(array);
  return temp;
}

/*function: replaceTemplate
  given the story template string, the catarray_t pointer 
  and one int reused to represent whether to reuse the 
  word or not, replace the blank with corresponding 
  replace word*/
char* replaceTemplate(char* story, catarray_t* array, int reused) {
  char* result = NULL;
  char* ptr = story;
  int count = 0;
  // create a category_t to store the replace word used before
  category_t usedWord;
  usedWord.n_words = 0;
  usedWord.words = NULL;
  while(*ptr != '\0') {
    // if the character is not blank
    if(*ptr != '_') {
      // copy the character
      result = realloc(result, (count + 2) * sizeof(*result));
      result[count] = *ptr;
      result[count + 1] = '\0';
      ptr++;
      count++;
    } else { // otherwise: meets with blank and template
      // find the second '_'
      char* endPtr = findTemplate(ptr);
      // extract the template between two '_'
      char* template = templateStr(ptr, endPtr);
      // get the corresponding replaceWord according to template
      char* replaceWord = getTemplateWord(template, usedWord, array);
      // update usedWord category to store the replaceWord 
      usedWord.n_words++;
      usedWord.words = realloc(usedWord.words, (usedWord.n_words) * sizeof(*usedWord.words));
      usedWord.words[usedWord.n_words - 1] = strdup(replaceWord);
      // concatenate the string with replaceWord
      count += strlen(usedWord.words[usedWord.n_words - 1]);
      result = realloc(result, (count + 1) * sizeof(*result));
      strcat(result, usedWord.words[usedWord.n_words - 1]);
      result[count] = '\0';
      // start with the character after the second '_'
      ptr = endPtr + 1;
      // if cannot reuse the word, remove it from the array
      if(!reused && array!= NULL) {
	array = removeWord(array, template, replaceWord);
      }
      free(template);
    }
  }
  freeCat(usedWord);
  if(array != NULL) {
    freeArray(array);
  }
  // if result is null
  if(result == NULL) {
    result = realloc(result, sizeof(*result));
    result[0] = '\0';
  }
  return result;
}


