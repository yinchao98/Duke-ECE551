#include "pandemic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MILLION 100000;


// to see if the input character is a number
// return 0(is not a number), 1(is a number)
int isNumber(char c) {
  // ascii of number is between 48 and 57
  if (c >= 48 && c<=57) {
    return 1;
  }
  return 0;
}

// check if the name length is < 64
void checkName(char* start, char* end) {
  if((end - start) > 63) {
    fprintf(stderr, "name length is too long!\n");
    exit(EXIT_FAILURE);
  }
}

// copy the name to dest
void copyName(char* start, char* end, char* dest) {
  size_t i = 0;
  while(start != end) {
    dest[i] = *start;
    i++;
    start++;
  }
  // add null terminator
  dest[i] = '\0';
}

// check if the string from start to end is legal
void checkPop(char* start, char* end) {
  while(start != end) {
    if(!isNumber(*start)) {
      fprintf(stderr, "The population is invalid!\n");
      exit(EXIT_FAILURE);
    }
    start++;
  }
}

// convert the string to uint64
unsigned long convertPop(char* start) {
  unsigned long population = strtoul(start, NULL, 10);
  // check whether the population is out of the bound
  if(errno == ERANGE) {
    fprintf(stderr, "The population is too large!\n");
    exit(EXIT_FAILURE);
  }
  errno = 0;
  // check whether the population is 0
  if(population == 0) {
    fprintf(stderr, "The population cannot be 0!\n");
    exit(EXIT_FAILURE);
  }
  return population;
}

// calculate the arithmetic mean of an array
double ariMean(unsigned *dataArray, size_t totalNum) {
  double sum = 0;
  // from 0 to totalNum, iteratively calculate the sum
  for(size_t i = 0; i < totalNum; i++) {
    sum += *(dataArray + i);
  }
  // calculate the arithmetic mean
  return sum/totalNum;
}

// get the index of the maximum number of the data array
size_t maxNumInd(unsigned *data, size_t n_days) {
  size_t index = 0;
  unsigned maxNum = *data;
  // from 1 to n_days, iteratively compare and get the index of maximum number 
  for(size_t i = 1; i < n_days; i++) {
    if(*(data + i) > maxNum) {
      maxNum = *(data + i);
      index = i;
    }
  }
  return index;
}

// convert a line to country_t struct
country_t parseLine(char * line) {

  // check line pointer
  if (line == NULL) {
    fprintf(stderr, "The line pointer is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // get the pointer which points to the comma
  char* splitPointer = strchr(line, ',');
  // check whether there's a comma which splits the name and population
  if(splitPointer == NULL) {
    fprintf(stderr, "There's no comma to split!\n");
    exit(EXIT_FAILURE);
  }
  // check whether the name length is smaller than 64
  checkName(line, splitPointer);
  // copy name to ans.name
  country_t ans;
  char* ptr = line;
  copyName(ptr, splitPointer, ans.name);

  char* newLine = strchr(line, '\n');
  // check if population is legal
  checkPop(++splitPointer, newLine);
  // convert the character of population to a uint64_t type
  ans.population = convertPop(splitPointer);
  return ans;
}

// calculates the seven-day running average of case data
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {

  // check data pointer 
  if (data == NULL) {
    fprintf(stderr, "The data is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // check n_days
  if (n_days <= 6) {
    fprintf(stderr, "The number of n_days is invalid!\n");
    exit(EXIT_FAILURE);
  }
  size_t avgLen = n_days - 6;
  // from 0 to avgLen, iteratively calculate the seven-day average
  for(size_t i = 0; i < avgLen; i++) {
    *(avg + i) = ariMean(data + i, 7);
  }
}

// calculate the cumulative number of cases that day per 100,000 people
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {

  // check data pointer
  if (data == NULL) {
    fprintf(stderr, "The data is invalid!\n");
    exit(EXIT_FAILURE);
  }

  unsigned cumData = 0;
  double cumPerMillion = 0;
  // from 0 to n_days
  for(size_t i = 0; i < n_days; i++) {
    // calculate the cumulative data
    cumData += *(data + i);
    // check cumData
    if (cumData > pop) {
      fprintf(stderr, "The cumData is larger than population!\n");
      exit(EXIT_FAILURE);
    }
    // calculate the data per 100,000 people
    cumPerMillion = (cumData * 1.0) / pop * MILLION;
    *(cum + i) = cumPerMillion;
  }

}

// find the maximum number of daily cases of all countries
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {

  // check the country_t pointer
  if (countries == NULL) {
    fprintf(stderr, "The countries struct is invalid!\n");
    exit(EXIT_FAILURE);
  }
  // check data pointer
  if (data == NULL) {
    fprintf(stderr, "The data pointer is invalid!\n");
    exit(EXIT_FAILURE);
  }
  unsigned maxNum[n_countries];
  // from 0 to n_countries
  for(size_t i = 0; i < n_countries; i++) {
    // find the maximum number of each country
    size_t index = maxNumInd(*(data + i), n_days);
    maxNum[i] = *(*(data + i) + index);
  }
  // find the largest maximum number of all countries
  size_t indexCountry = maxNumInd(maxNum, n_countries);
  // assign the country_name and number_cases according to index
  char* country_name = (*(countries + indexCountry)).name;
  unsigned number_cases = maxNum[indexCountry];
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}

