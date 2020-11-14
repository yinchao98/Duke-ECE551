#include "function.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

/*int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if(low < high - 1) {
    int mid = (low + high) / 2;
    if(f->invoke(mid) == 0) {
      return mid;
    }
    if(f->invoke(mid) < 0) {
      return binarySearchForZero(f, mid, high);
    } else {
      return binarySearchForZero(f, low, mid);
    }
  }
  return low;
  }*/

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int fx = f->invoke(mid);
    if (fx == 0) {
      return mid;
    }
    else if (fx > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
  }
  return low;
}

