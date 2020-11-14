#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "function.h"

//int binarySearchForZero(function, low, high);
int binarySearchForZero(Function<int, int> * f, int low, int high);
  
class CountedIntFn: public Function<int, int> {
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int n = 0;
  if (high > low) {
    n = log2(high - low) + 1;
  } else {
    n = 1;
  }
  CountedIntFn *function = new CountedIntFn(n, f, mesg);
  int ans = binarySearchForZero(function, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "expected invoke times: %d, but actually had: %d", expected_ans, ans);
    exit(EXIT_FAILURE);
  }
}

class SinFunction: public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

class NegFunction: public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return (-1) * arg;
  }
};

class PosFunction: public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return arg;
  }
};

int main() {
  SinFunction *sinFun = new SinFunction();
  check(sinFun, 0, 150000, 52359, "normal sin");
  check(sinFun, 1, 1, 1, "sin: low = high = 1");
  check(sinFun, -1, -1, -1, "sin: low = high = -1");
  check(sinFun, 0, 100000, 52359, "normal sin");
  check(sinFun, 1, 52359, 52358, "normal sin");
  NegFunction *negFun = new NegFunction();
  //check(negFun, 1, 10, 9, "fx is all negative");
  PosFunction *posFun = new PosFunction();
  check(posFun, 1, 10, 1, "fx is all postive");
  check(posFun, -5, 5, 0, "(low+high)/2 == 0");
  check(posFun, -2, 8, 0, "posFunc");
  check(negFun, -10, 9, 0, "negFunc");
  
  // large value
  check(posFun, -10000000, 100000, 0, "posFunc1");
  check(posFun, -10000000, -2, -3, "posFunc2");
  return EXIT_SUCCESS;
}

