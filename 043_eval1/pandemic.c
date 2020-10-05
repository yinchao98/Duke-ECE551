#include "pandemic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MILLION 100000;

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

size_t maxNumInd(unsigned *data, size_t n_days) {
  size_t index = 0;
  unsigned maxNum = *data;
  for(size_t i = 1; i < n_days; i++) {
    if(*(data + i) > maxNum) {
      maxNum = *(data + i);
      index = i;
    }
  }
  return index;
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
  // check data
  if (data == NULL) {
    fprintf(stderr, "The data is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // check n_days
  if (n_days <= 6) {
    fprintf(stderr, "The number of n_days is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // calculate the arithmetic mean
  size_t avgLen = n_days - 6;
  for(size_t i = 0; i < avgLen; i++) {
    *(avg + i) = ariMean(data + i, 7);
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  // check data
  if (data == NULL) {
    fprintf(stderr, "The data is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // check n_days
  if (n_days < 0) {
    fprintf(stderr, "The number of n_days is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // check pop
  if (pop <= 0) {
    fprintf(stderr, "The number of population is invalid!\n");
    exit(EXIT_FAILURE);
  }
  unsigned cumData = 0;
  double cumPerMillion = 0;
  for(size_t i = 0; i < n_days; i++) {
    cumData += *(data + i);
    cumPerMillion = (cumData * 1.0) / pop * MILLION;
    *(cum + i) = cumPerMillion;
  }

}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  unsigned maxNum[n_countries];
  // compute each maxNum of each country
  for(size_t i = 0; i < n_countries; i++) {
     //size_t index = maxNumInd(*data, n_days);
    size_t index = maxNumInd(*(data + i), n_days);
    maxNum[i] = *(*(data + i) + index);
  }
  // compute the largest maxNum of all countries
  size_t indexCountry = maxNumInd(maxNum, n_countries);
  char* country_name = (*(countries + indexCountry)).name;
  unsigned number_cases = maxNum[indexCountry];
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}

