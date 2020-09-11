#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int* array, size_t n);

void check(int* array, size_t n, size_t expected_ans) {
  if (maxSeq(array, n) != expected_ans){
    exit(EXIT_FAILURE);
  }
}

int main(){
  int array1[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  check(array1, 10, 4);
  
  int array2[4] = {-5, -3, 0, -1};
  check(array2, 4, 3);

  int array3[1] = {0};
  check(array3, 1, 1);

  int array4[] = {};
  check(array4, 0, 0);

  int array5[6] = {-2, -2, 1, 2, 3, 3};
  check(array5, 6, 4);

  int array6[20] = {1, 3, 4, 1, 9, 3, 5, 8, 2, 2, 10, 1000, 999, 999, 1001, 2000, 3000, 5000, 30, 20};
  check(array6, 20, 5);
 
  
  return EXIT_SUCCESS;
}
