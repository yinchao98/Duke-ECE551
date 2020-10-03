#include "pandemic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int isNumber(char c) {
  if (c >= 48 && c<=57) {
    return 1;
  }
  return 0;
}

double ariMean(unsigned *dataArray, size_t totalNum) {
  double sum = 0;
  for(size_t i = 0; i < totalNum; i++) {
    sum += *(dataArray + i);
  }
  return sum/totalNum;
}
country_t parseLine(char * line) {
  //WRITE ME
  char* splitPointer = strchr(line, ',');
  // check whether there's a comma which splits the name and population
  if(splitPointer == NULL) {
    fprintf(stderr, "There's no comma to split!\n");
    exit(EXIT_FAILURE);
  }
  // check whether the name length is smaller than 64
  if((splitPointer - line) > 64) {
    fprintf(stderr, "name length is larger than 64!\n");
    exit(EXIT_FAILURE);
  }
  // assign ans->name
  char* ptr = line;
  int i = 0;
  country_t ans;
  while(ptr != splitPointer) {
    ans.name[i] = *ptr;
    i++;
    ptr++;
  }
  ans.name[i] = '\0';
  // check whether the population is valid
  ptr++;
  while(*ptr != '\n') {
    if(!isNumber(*ptr)) {
      fprintf(stderr, "The population is invalid!\n");
      exit(EXIT_FAILURE);
    }
    ptr++;
  }
  // convert the character of population to a uint64_t type
  ans.population = strtoul(++splitPointer, &ptr, 10);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  size_t avgLen = n_days - 6;
  for(size_t i = 0; i < avgLen; i++) {
    *(avg + i) = ariMean(data + i, 7);
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
