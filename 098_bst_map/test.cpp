#include <cstdio>
#include <cstdlib>
#include "bstmap.h"


int main() {
  BstMap<int, int> map;
  map.add(33, 1);
  map.add(44, 2);
  map.add(12, 3);
  map.add(55, 4);
  map.add(99, 5);
  map.add(16, 6);
  map.add(77, 7);
  map.add(0, 8);
  map.add(-1, 9);
  map.add(100, 10);

  std::cout << "The expected answer is -1 0 12 16 33 44 55 77 99 100" << std::endl;
  map.inOrderPrint();
  int ans1 = map.lookup(44);
  int ans2 = map.lookup(77);
  std::cout << "ans1 should be 2 and =" << ans1 << "\n";
  std::cout << "ans2 should be 7 and =" << ans2 << "\n";
  map.remove(12);
  map.inOrderPrint();

  BstMap<int, int> map2(map);
  map2.inOrderPrint();

  
  return EXIT_SUCCESS;
}
