#include<vector>
#include<cstdlib>
#include<iostream>
#include<utility>

// IndException class, throw if the index is invalid
class IndException : public std::exception {
public:
  virtual const char * what() const throw() { 
    return "The index is out of bound!\n"; 
  }
};

template<typename T>
class Container {
private:
  static const int DEFAULT_THRESHOLD = 100;
  size_t maxSize;
  size_t size;
  std::vector<std::pair<T, int> >* vector;

  // private method: find the element with minimum access number 
  std::pair<T, int>* findMin() {
    if (size == 0) {
      return NULL;
    }
    std::pair<T, int> * min = NULL;
    for (typename std::vector<std::pair<T, int> >::iterator it = vector->begin(); it != vector->end(); ++it) {
      if (min == NULL || min->second > (*it).second){
        min = &(*it);
      }
    }
    return min;
  }

public:
  // default constructor
  Container() : maxSize(DEFAULT_THRESHOLD), size(0), vector(new std::vector<std::pair<T, int> >()) {}

  // constructor with initialized maximumSize
  Container(size_t s) : maxSize(s), size(0), vector(new std::vector<std::pair<T, int> >()) {}

  // destructor
  ~Container() { delete vector; }

  // copy constructor
  Container(const Container & other) : maxSize(other.maxSize), vector(new std::vector<std::pair<T, int> >()), size(0) {
    for (size_t i = 0; i < other.size; i++) {
        this->insertNew(other[i]);
    }
  }

  // assign operator
  Container& operator=(const Container & other) {
    // copy to a new vector pointer
    std::vector<std::pair<T, int> > * newVec = new std::vector<std::pair<T, int> >();
    for (size_t i = 0; i < other.size; i++) {
      newVec->insertNew(other[i]);
    }
    // swap
    delete this->vector;
    this->vector = newVec;
    this->maxSize = other.maxSize;
    this->size = other.size;
    newVec = NULL;
    return *this;
  }

  // [] operator
  T& operator[](int index) {
    try {
      return vector[index]->first;
    }
    catch(IndException & e) {
      throw e;
    }
  }

  // const [] operator
  const T& operator[](int index) const {
    try {
      return vector[index]->first;
    }
    catch(IndException & e) {
      throw e;
    }
  }

  // get the value through index
  T getValue(size_t index) {
    try {
      std::pair<T, int>* target = &this->vector->at(index);
      target->second++;
      return target->first;
    }
    catch(IndException & e) {
      throw e;
    }
  }

  // insert a new element
  void insertNew(T& element) {
    if (size < maxSize){
      vector->push_back(std::pair<T, int>(element, 0));
      size++;
    } else { // if oversize, find the min element and replace
      std::pair<T, int>* min = findMin();
      min->first = element;
      min->second = 0;
    }
  }

  // modify the existing element
  void modifyExisting(size_t index, T & newElement) {
    try {
      std::pair<T, int>* target = &this->vector->at(index);
      target->first = newElement;
      target->second++;
    }
    catch (IndException & e){
      throw e;
    }
  }

  // define the iterator
  typename std::vector<std::pair<T, int> >::iterator getIterator(){
    return this->vector->begin();
  }

  // remove the element
  void removeExisting(typename std::vector<std::pair<T, int> >::iterator it){
    this->vector->erase(it);
    size--;
  }

  template<typename S>
  friend std::ostream& operator<<(std::ostream& ostream, const Container<S>& container);

};

template<typename S>
std::ostream& operator<<(std::ostream& ostream, const Container<S>& container){
  ostream << "[";
  for (typename std::vector<std::pair<S, int> >::iterator it = container.vector->begin(); it != container.vector->end(); ++it){
    std::pair<S, int>& current = *it;
    ostream << "(";
    ostream << current.first << ", " << current.second << ")";
    if (it < container.vector->end() - 1) {
      ostream << ", ";
    }
  }
  ostream << "]" << std::endl;
  return ostream;
}
