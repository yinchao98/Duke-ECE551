#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <utility>

class Page {
 public:
  bool result;
  std::vector<std::pair<unsigned, std::string> > navigation;
  std::string text;
  std::vector<std::pair<unsigned, unsigned> > refPage;
 public:
  // default constructor
 Page(): result(false), navigation(), text(), refPage() {}
  // copy constructor
 Page(const Page & rhs): result(rhs.result), navigation(rhs.navigation),
    text(rhs.text), refPage(rhs.refPage) {}
  // assignment operator
  Page & operator=(const Page & rhs) {
    if(this != &rhs) {
      result = rhs.result;
      navigation = rhs.navigation;
      text = rhs.text;
      refPage = rhs.refPage;
    }
    return *this;
  }
  // default destructor
  ~Page() {}
  // read the navigation part into the field
  void readChoices(std::vector<std::string> choices);
  // check if the choices are valid in navigation, return valid pagenum and choice
  std::pair<unsigned, std::string> checkChoices(std::string choice);
  // read page information from the file, return true if the file can be read
  bool readPage(char* pageFile);
  // add win or lose result
  void addResult(bool r);
  // add choices from navigation part
  void addNavigation(unsigned pageNum, std::string choice);
  // add text part
  void addText(std::string t);
  // print the page according to the format
  void printPage();
  // return if this page is a story ending page
  bool isEnd();
};

void errorHandling(std::string errorMsg);
