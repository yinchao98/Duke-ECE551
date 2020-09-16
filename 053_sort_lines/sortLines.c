#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
//This function print data and free the previous allocation
void printData(char** data, size_t count) {
  for (size_t j = 0; j < count; j++) {
      printf("%s", *(data + j));
      free(*(data + j));
    }
}

int main(int argc, char ** argv) {
  char** data = NULL;
  char* curr = NULL;
  size_t sz = 0;
  size_t count = 0;
  // if there's no input file, use standard input
  if (argc == 1) {
    while (getline(&curr,&sz, stdin) != EOF) {
      data = realloc(data, (count + 1) * sizeof(*data));
      data[count] = curr;
      curr = NULL;
      count++;
    }
    free(curr);
    sortData(data, count);
    printData(data, count);
    free(data);
  } else { 
    for (size_t i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      while (getline(&curr,&sz, f) >= 0) {
        data = realloc(data, (count + 1) * sizeof(*data));
        data[count] = curr;
        curr = NULL;
        count++;
      }
      free(curr);
      sortData(data, count);
      printData(data, count);
      free(data);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
      f = NULL;
    }
  }
  return EXIT_SUCCESS;
}
