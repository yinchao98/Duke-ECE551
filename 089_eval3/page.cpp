#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "page.h"

// handle errors 
void errorHandling(std::string errorMsg) {
  std::cerr << errorMsg << std::endl;
  exit(EXIT_FAILURE);
}

// read the navigation part into the field
void Page::readChoices(std::vector<std::string> choices) {
  // if the navigation is WIN or LOSE, put it into result field
  if(choices[0] == "WIN" || choices[0] == "LOSE") {
    if(choices.size() == 1) {
      if(choices[0] == "WIN") {
	addResult(true);
      } else {
	addResult(false);
      }
    } else {
      errorHandling("wrong page file format -> navigation");
    }
  } else { // check each choice format, put the choices into navigation field
    std::vector<std::string>::iterator it = choices.begin();
    while(it != choices.end()) {
      std::string str(*it);
      std::pair<unsigned, std::string> choice = checkChoices(str);
      addNavigation(choice.first, choice.second);
      ++it;
    }
  }
}

// check if the choices are valid in navigation
std::pair<unsigned, std::string> Page::checkChoices(std::string str) {
  size_t index1 = str.find_first_of(':');
  if(index1 == std::string::npos) {
    errorHandling("wrong page file format -> navigation");
  }
  std::string pageNum(str.substr(0, index1));
  std::string choice(str.substr(++index1));
  // check if pageNum is a valid number
  for(size_t i = 0; i < pageNum.length(); i++) {
    if(pageNum[i] < 48 || pageNum[i] > 57) {
      errorHandling("wrong page file format -> navigation");
    }
  }
  int value = atoi(pageNum.c_str());
  if(value == 0) {
    errorHandling("wrong page file format -> navigation");
  }
  return std::pair<unsigned, std::string>(value, choice);
}

// read page information from the file, put into fields
bool Page::readPage(char* pageFile) {
  std::ifstream f;
  // if cannot open the file, return false to show there's no more page
  f.open(pageFile);
  if (f.fail()) {
    return false;
  }
  std::vector<std::string> choices;
  std::string text;
  bool partition = false;
  while (!f.eof()) {
    std::string s;
    std::getline(f, s);
    // after '#' line is text part
    if(partition) {
      text += s;
      text += '\n';
    } // before '#' line is navigation part
    else 
      if(s[0] != '#') {
	choices.push_back(s);
      } else {
	partition = true;
      }
  }
  // if there's no partition, wrong format
  if(!partition) {
    errorHandling("wrong page file format -> partition");
  }
  // write into fields
  addText(text);
  readChoices(choices);
  f.close();
  return true;
}

// add win or lose result
void Page::addResult(bool r) {
  result = r;
}

// add choices from navigation part
void Page::addNavigation(unsigned pageNum, std::string choice) {
  navigation.push_back(std::pair<unsigned, std::string>(pageNum, choice));
}

// add text part
void Page::addText(std::string t) {
  text = t;
}

// print the page according to the format
void Page::printPage() {
  // first print the text
  std::cout << text;
  // if this page is story ending, print out the result
  if(isEnd()) {
    if(result == true) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    } else {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
  } else { // if it is not ending, giving the choices
    std::cout << "What would you like to do ?" << std::endl;
    std::cout << std::endl;
    std::vector<std::pair<unsigned, std::string> >::iterator it = navigation.begin();
    unsigned i = 1;
    while(it != navigation.end()) {
      std::cout << " " << i << ". ";
      std::cout << it->second << std::endl;
      ++it;
      ++i;
    }
  }
}

// return if this page is a story ending page
bool Page::isEnd() {
  return navigation.size() == 0;
}


