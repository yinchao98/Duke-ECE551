#include "rand_story.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

/*function: errorHandling
			print the errorMsg to stderr and exit*/
void errorHandling(std::string errorMsg) {
	std::cerr << errorMsg;
	exit(EXIT_FAILURE);
}

/*function: checkArgs
			check the number of arguments*/
void checkArgs(int argc, int expected) {
	// if argc doesn't match the expected, exits
	if(argc != expected) {
		errorHandling("Invalid argc!\n");
	}
}

/*function: parseContent
			given a FILE pointer, parse all the content
			in the file to a string*/
std::string parseContent(char* file) {
	std::ifstream f;
	f.open(file);
	// if fails, exits
	if (f.fail()) {
		errorHandling("Fail to open the file!\n");
	}
	std::string content;
	// get the line into content, until meet the end of file
	while (!f.eof()) {
        std::string s;
        std::getline(f, s);
        if(s == "" && f.eof()) {
        	break;
        }
        content += s;
        content += '\n';
    }
    f.close();
	return content;
}

/*function: getName
			given a line, extract the name before semicolon
			character into a char pointer*/
std::string getName(std::string line) {
	size_t index = line.find_first_of(':');
	// if there's not a semicolon, exits
    if(index == std::string::npos) {
    	errorHandling("Invalid word format!\n");
    }
    std::string name(line.substr(0, index));
    return name;
}

/*function: getWord
			given a line, extract the word after semicolon
			character into a char pointer*/
std::string getWord(std::string line) {
	size_t index1 = line.find_first_of(':');
	index1++;
    std::string word(line.substr(index1));
    return word;
}

/*function: parseLine
			given a FILE pointer, parse the line into
			catarray struct*/
Category<std::string, std::string> parseLine(char* file) {
	std::ifstream f;
	f.open(file);
	// if fails, exits
	if (f.fail()) {
		errorHandling("Fail to open the file!\n");
	}
	// class Category
	Category<std::string, std::string> cat;
	while (!f.eof()) {
		// extract name and word
        std::string s;
        std::getline(f, s);
        if(s == "" && f.eof()) {
        	break;
        }
        std::string name = getName(s);
        std::string word = getWord(s);
        cat.add(name, word);
    }
    f.close();
    return cat;
}

/*function: findTemplate
			given a char pointer which starts with a'_', 
			find if there is a second '_', return the pointer*/
size_t findTemplate(std::string str) {
	size_t index1 = str.find_first_of('_');
	// if there's not a semicolon, exits
    if(index1 == std::string::npos) {
    	errorHandling("Invalid blank format!\n");
    }
	size_t index2 = str.find_first_of('\n');
	// if the two '_' are not in one line
	if(index1 - index2 > 0) {
		errorHandling("Invalid blank format!\n");
	}
	return index1;
}

/*function: templateStr
			given two pointers which point at the first and 
			second '_', extract the template between two '_'*/
std::string templateStr(size_t index1, size_t index2) {
	std::string templateName(index1, index2 - index1);
	return templateName;
}

/*function: checkInt
			convert the template string into a number*/
int checkInt(std::string templateName) {
	// check if all the characters are digit
	for(size_t i = 0; i < templateName.length(); i++) {
		if(templateName[i] < 48 || templateName[i] > 57) {
			return -1;
		}
	}
	// if it is a valid number, convert to int value
	int value = atoi(templateName.c_str());
	return value;
}

/*function: checkTemplate
			return the index of template in catarray*/
bool checkTemplate(std::string templateName, Category<std::string, std::string> & cat) {
	return cat.contains(templateName);
}

/*function: getTemplateWord
			given the template, usedWord category and catarray
			return the corresponding replaceWord*/
std::string getTemplateWord(std::string templateName, Category<std::string, std::string> & cat, std::vector<std::string> & usedWords) {
	int i = checkInt(templateName);
	bool j = checkTemplate(templateName, cat);
	std::string replaceWord;
	// if the template is a valid integer
	if(i >= 1 && i <= (int)usedWords.size()) {
		replaceWord = usedWords[usedWords.size() - i];
		return replaceWord;
	} 
	// if the template is a valid category name
	if(j == true) {
		// randomly choose the replaceWord from the category
		replaceWord = cat.chooseWord(templateName);
		return replaceWord;
	}
	// otherwise, the template is invalid, exits
	errorHandling("Invalid template!\n");
	return NULL;
}

/*function: replaceTemplate
			given the story template string, the catarray_t pointer 
			and one int reused to represent whether to reuse the 
			word or not, replace the blank with corresponding 
			replace word*/
std::string replaceTemplate(std::string story, Category<std::string, std::string> & cat) {
	std::vector<std::string> usedWords;
	std::string result;
	size_t i = 0;
	while(i < story.length()) {
		if(story[i] != '_') {
			// copy the character
			result += story[i];
			i++;
		} else {
			// find the second '_'
			size_t startPos = i + 1;
			std::string str1(story.substr(startPos));
			size_t index2 = str1.find_first_of('_');
			// extract the template between two '_'
			std::string templateName(str1.substr(0, index2));
			// get the corresponding replaceWord according to template
			std::string replaceWord(getTemplateWord(templateName, cat, usedWords));
			// update usedWord category to store the replaceWord 
			usedWords.push_back(replaceWord);
			result += replaceWord;
			i += templateName.length() + 2;
		}
	}
	return result;
}


