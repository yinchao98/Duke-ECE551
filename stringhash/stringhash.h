#include <cstdio>
#include <cstdlib>
#include <iostream>

class StringHasher {
private:
	const int multiplyBy;
public:
	StringHasher(): multiplyBy(29) {}
	StringHasher(int m): multiplyBy(m) {}
	unsigned operator()(const std::string & str) const {
		unsigned ans = 0;
		for(std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			ans = ans * multiplyBy + *it;
		}
		return ans;
	}
};
