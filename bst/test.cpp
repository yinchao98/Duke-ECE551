#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "bst.h"

int main() {
	BST<int> bst1;
	bst1.insertOrder(60);
	bst1.insertOrder(70);
	bst1.insertOrder(15);
	bst1.insertOrder(20);
	bst1.insertOrder(75);
	bst1.insertOrder(65);
	bst1.insertOrder(18);
	bst1.insertOrder(20);
	bst1.inOrderPrint();
	bst1.removeAll(20);
	bst1.inOrderPrint();

}
