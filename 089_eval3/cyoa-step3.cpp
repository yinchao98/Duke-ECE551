#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "book.h"

int main(int argc, char** argv) {
	Book book1;
	book1.readPages(argv[1]);
	book1.checkPages();
	std::set<unsigned> set = book1.getReachable();
	book1.notReachable(set);
	return EXIT_SUCCESS;
}
