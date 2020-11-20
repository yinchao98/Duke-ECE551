#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "page.h"

int main(int argc, char** argv) {
	Page page1;
	if(page1.readPage(argv[1]) == false) {
		std::cerr << "cannot open the file" << std::endl;
        exit(EXIT_FAILURE);
	}
	page1.printPage();
	
	return EXIT_SUCCESS;
}
