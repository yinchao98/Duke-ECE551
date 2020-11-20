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
public:
	Page(): result(false), navigation(), text() {}
	Page(const Page & rhs): result(rhs.result), 
							navigation(rhs.navigation), text(rhs.text) {}
	Page & operator=(const Page & rhs) {
		if(this != &rhs) {
			result = rhs.result;
			navigation = rhs.navigation;
			text = rhs.text;
		}
		return *this;
	}
	~Page() {}
	void checkChoices(std::vector<std::string> choices);
	bool readPage(char* pageFile);
	void addResult(bool r);
	void addNavigation(unsigned pageNum, std::string choice);
	void addText(std::string t);
	void printPage();
	bool isEnd();
};
