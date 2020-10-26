#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

template<typename T>
void printElements(T& container) {
  typename T::iterator it = container.begin();
  while(it != container.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  // if there's no input file, use standard input

  if (argc == 1) {
    std::vector<std::string> dataVector;
    while (!std::cin.eof()) {
      std::string s;
      std::getline(std::cin, s);
      dataVector.push_back(s);
    }
    std::sort(dataVector.begin(), dataVector.end());
    printElements<std::vector<std::string> >(dataVector);
  } else { 
    for (int i = 1; i < argc; i++) {
      std::ifstream f;
      f.open(argv[i]);
      if (f.fail()) {
        std::cerr << "cannot read the file" << std::endl;
        return EXIT_FAILURE;
      }
      std::vector<std::string> dataVector;
      while (!f.eof()) {
        std::string s;
        std::getline(f, s);
        dataVector.push_back(s);
      }
      std::sort(dataVector.begin(), dataVector.end());
      printElements<std::vector<std::string> >(dataVector);
      f.close();
    }
  }
  return EXIT_SUCCESS;
}
