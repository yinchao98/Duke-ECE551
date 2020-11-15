#include <cstdio>
#include <cstdlib>
#include "bstset.h"


int main() {
  BstSet<int> set;
  set.add(33);
  set.add(44);
  set.add(12);
  set.add(55);
  set.add(99);
  set.add(16);
  set.add(77);
  set.add(0);
  set.add(-1);
  set.add(100);

  std::cout << "The expected answer is -1 0 12 16 33 44 55 77 99 100" << std::endl;
  set.inOrderPrint();
  bool ans1 = set.contains(44);
  bool ans2 = set.contains(77);
  bool ans3 = set.contains(-55);
  std::cout << "ans1 should be true and =" << ans1 << "\n";
  std::cout << "ans2 should be true and =" << ans2 << "\n";
  std::cout << "ans3 should be false and =" << ans3 << "\n";
  set.remove(12);
  set.inOrderPrint();

  BstSet<int> set2(set);
  set2.inOrderPrint();

  
  return EXIT_SUCCESS;
}
