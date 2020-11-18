#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>

template<typename K, typename V>
class Category {
private:
	std::map<K, std::set<V> > map;
	unsigned size;
public:
	// default constructor
	Category(): map(), size(0) {}
	// copy constructor
	Category(const Category & rhs): map(rhs.map), size(rhs.size) {}
	// assignment operator
	Category & operator=(const Category & rhs) {
		if(this != &rhs) {
			std::map<K, std::set<V> > tempMap(rhs.map);
			delete map;
			map = tempMap;
			tempMap = NULL;
		}
		return *this;
	}
	// destructor
	~Category() {}
	// add new element
	void add(K & key, V & value) {
	    typename std::map<K, std::set<V> >::iterator it;
	    it = map.find(key);
	    // if there's already the key
	    if (it != map.end()) {
	    	it->second.insert(value);
	    } else { // add a new key value pair
	    	std::set<V> v;
	    	v.insert(value);
	    	map.insert(typename std::map<K, std::set<V> >::value_type(key, v));
	    	size++;
	    }
	    return;
	}
	// randomly choose word from key
 	const V & chooseWord(K & key) const{
 		std::set<V> words = map.at(key);
 		srand((unsigned)time(NULL));
 		int rad = random()% words.size();
 		typename std::set<V>::iterator it = words.begin();
 		std::advance(it, rad);
		return *it;
 	}
 	// check if contains the key
 	bool contains(K & key) {
 		typename std::map<K, std::set<V> >::iterator it;
 		it = map.find(key);
 		if(it == map.end()) {
 			return false;
 		}
 		return true;
 	}
 	// get size
 	unsigned getSize() {
 		return size;
 	}

 	void printCat() {
		typename std::map<K, std::set<V> >::iterator it1 = map.begin();
		typename std::set<V>::iterator it2;
		while(it1 != map.end()) {
			std::string categoryName(it1->first);
			std::set<std::string> words = it1->second;
			it2 = words.begin();
			std::cout << categoryName << ":";
			while(it2 != words.end()) {
				std::string wordName = *it2;
				std::cout << wordName << " ";
				++it2;
			}
			std::cout << std::endl;
			++it1;
		}
 	}

	// template<typename A, typename B>
 //    friend std::ostream& operator<<(std::ostream& ostream, const Category<A,B> & category);
	
};

// template<typename A, typename B>
// std::ostream& operator<<(std::ostream& ostream, const Category<A, B> & category){
// 	std::map<A, std::set<B> > categoryMap = category.map;
// 	typename std::map<A, std::set<B> >::iterator it1 = categoryMap.begin();
// 	typename std::set<B>::iterator it2;
// 	while(it1 != category.map.end()) {
// 		std::string categoryName(it1->first);
// 		std::set<std::string> words = it1->second;
// 		it2 = words.begin();
// 		ostream << " " << categoryName << ":" << std::endl;
// 		while(it2 != words.end()) {
// 			std::string wordName = *it2;
// 			ostream << wordName << std::endl;
// 			++it2;
// 		}
// 		++it1;
// 	}
//   	return ostream;
// }


