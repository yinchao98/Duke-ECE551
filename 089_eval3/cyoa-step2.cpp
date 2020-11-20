#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "book.h"

int main(int argc, char** argv) {
	Book book1;
	book1.readPages(argv[1]);
	book1.checkPages();
	book1.startStory();

	return EXIT_SUCCESS;
}
