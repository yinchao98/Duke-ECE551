#include <cstdlib>
#include <cstdio>
#include "il.h"
#include <assert.h>

void testList() {
  IntList l1;
  assert(l1.head == NULL && l1.tail == NULL);
  assert(l1.getSize() == 0 && l1.size == 0);
  assert(l1.find(0) == -1);
  // l1: 5 4 3
  l1.addFront(4);
  assert(l1[0] == 4);
  assert(l1.getSize() == 1 && l1.size == 1);
  assert(l1.head != NULL);
  assert(l1.head == l1.tail);
  assert(l1.head->data == 4);
  assert(l1.tail->data == 4);
  assert(l1.head->next == NULL);
  assert(l1.head->prev == NULL);
  assert(l1.find(4) == 0);
  assert(l1.find(0) == -1);
  l1.addFront(5);
  assert(l1[0] == 5 && l1[1] == 4);
  assert(l1.getSize() == 2 && l1.size == 2);
  assert(l1.head != NULL);
  assert(l1.head->data == 5);
  assert(l1.tail->data == 4);
  assert(l1.head->next == l1.tail);
  assert(l1.head->prev == NULL);
  assert(l1.tail->next == NULL);
  assert(l1.tail->prev == l1.head);
  assert(l1.find(4) == 1 && l1.find(5) == 0);
  assert(l1.find(0) == -1);
  l1.addBack(3);
  assert(l1.head != NULL);
  assert(l1.tail != NULL);
  assert(l1.head->data == 5);
  assert(l1.head->next->data == 4);
  assert(l1.tail->data == 3);
  assert(l1.head->next == l1.tail->prev);
  assert(l1.getSize() == 3 && l1.size == 3);
  assert(l1.find(5) == 0 && l1.find(4) == 1 && l1.find(3) == 2);
  assert(l1[0] == 5 && l1[1] == 4 && l1[2] == 3);
  // copy constructor
  IntList l2(l1);
  assert(l2.size == 3 && l2.getSize() == 3);
  assert(l2[0] == 5 && l2[1] == 4 && l2[2] == 3);
  assert(l2.head->data == 5);
  assert(l2.head->next->data == 4);
  assert(l2.tail->data == 3);
  assert(l2.head->next->next == l2.tail);
  assert(l2.tail->prev->prev == l2.head);
  assert(l1.head != l2.head && l1.tail != l2.tail);
  assert(l2.find(5) == 0);
  assert(l2.find(4) == 1);
  assert(l2.find(3) == 2);
  assert(l2.find(-1) == -1);
  l2[1] = 2;
  assert(l2.find(2) == 1);
  assert(l2.find(4) == -1);
  assert(l2.size == 3 && l2.getSize() == 3);
  l2[1] = 4;
  // assignment operator
  IntList l3;
  l3 = l1;
  assert(l3.size == 3 && l3.getSize() == 3);
  assert(l3[0] == 5 && l3[1] == 4 && l3[2] == 3);
  assert(l3.head->next->next == l3.tail);
  assert(l3.tail->prev->prev == l3.head);
  assert(l1.head != l3.head && l1.tail != l3.tail);
  assert(l3.head->data == 5);
  assert(l3.head->next->data == 4);
  assert(l3.tail->data == 3);
  assert(l3.find(5) == 0);
  assert(l3.find(4) == 1);
  assert(l3.find(3) == 2);
  assert(l3.find(-1) == -1);
  l3[1] = 2;
  assert(l3.find(2) == 1);
  assert(l3.find(4) == -1);
  assert(l3.size == 3 && l3.getSize() == 3);
  l3[1] = 4;
  // remove
  assert(l3.remove(4));
  assert(l3.size == 2 && l3.getSize() == 2);
  assert(l3[0] == 5 && l3[1] == 3);
  // l2 = l3
  l2 = l3;
  assert(l2.head != l3.head);
  assert(l2.size == 2 && l2.getSize() == 2);
  assert(l2.head->next == l2.tail);
  assert(l2.tail->prev == l2.head);
  assert(l2[0] == 5 && l2[1] == 3);
  // remove
  assert(l3.remove(0) == false);
  assert(l3.head->next == l3.tail);
  assert(l3.tail->prev == l3.head);
  assert(l3.size == 2 && l3.getSize() == 2);
  assert(l3[0] == 5 && l3[1] == 3);
  assert(l3.remove(5));
  assert(l3.head == l3.tail);
  assert(l3.head->next == NULL && l3.tail->prev == NULL);
  assert(l3.size == 1 && l3.getSize() == 1);
  assert(l3[0] == 3);
  assert(l3.remove(3));
  assert(l3.head == NULL && l3.tail == NULL);
  assert(l3.getSize() == 0 && l3.size == 0);
  
}

int main() {
  testList();
  return EXIT_SUCCESS;
}
