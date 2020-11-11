#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <assert.h>

//YOUR CODE GOES HERE
class IndException : public std::exception {
public:
	virtual const char * what() const throw() { 
  	return "The index is out of bound!\n"; 
  }
};


template<typename T>
class LinkedList {
private:
	class Node {
	public:
		T data;
		Node * next;
		Node * prev;
		Node() : data(0), next(NULL), prev(NULL){};
    	Node(T d, Node * a, Node * b) : data(d), next(a), prev(b){};
	};
	Node * head;
	Node * tail;
	int size;
public:
	LinkedList(): head(NULL), tail(NULL), size(0){};
	LinkedList(const LinkedList & rhs): head(NULL), tail(NULL), size(0){
		Node * current = rhs.head;
		while(current != NULL) {
			addBack(current->data);
			current = current->next;
		}
	}
	LinkedList & operator=(const LinkedList & rhs) {
		if(this != rhs) {
			// copy to a new linkedlist
			LinkedList tempList(rhs);
			// delete old linkedList
			while(head != NULL) {
				Node * tempNode = head->next;
				delete head;
				head = tempNode;
			}
			this = tempList;
		}
		return *this;
	}
	~LinkedList() {
		while(head != NULL) {
			Node * temp = head->next;
			delete head;
			head = temp;
		}
		size = 0;
		tail = NULL;
	}
	void addFront(const T & item) {
		head = new Node(item, head, NULL);
		if(tail == NULL) {
			tail = head;
		} else {
			head->next->prev = head;
		}
 		size++;
	}
	void addBack(const T & item) {
		tail = new Node(item, NULL, tail);
		if(head == NULL) {
			head = tail;
		} else {
			tail->prev->next = tail;
		}
		size++;
	}
	bool remove(const T & item) {
		if(head == NULL) {
			return false;
		}
		// remove the head
		if(head->data == item) {
			Node * temp = head->next;
			delete head;
			head = temp;
			if(head == NULL) {
				tail = NULL;
			} else {
				head->prev = NULL;
			}
			size--;
			return true;
		}
		Node * current = head;
		while(current->next != NULL) {
			if(current->next->data == item) {
				if(current->next->next == NULL) {
					delete current->next;
					tail = current;
					current->next = NULL;
				} else {
					Node * temp = current->next->next;
					delete current->next;
					current->next = temp;
					current->next->prev = current;
				}
				size--;
				return true;
			}
			current = current->next;
		}
		return false;
	}
	T & operator[](int index) {
		try {
			Node * current = head;
			for(int i = 0; i < index; i++) {
				current = current->next;
			}
			return current->data;
		}
		catch (IndException & e) {
			throw e;
		}
		
	}
	const T & operator[](int index) const {
		try {
			Node * current = head;
			for(int i = 0; i < index; i++) {
				current = current->next;
			}
			return current->data;
		}
		catch (IndException & e) {
			throw e;
		}
	}
	int find(const T & item) const {
		Node * current = head;
		int index = 0;
		while(current != NULL) {
			if(current->data == item) {
				return index;
			}
			index++;
			current = current->next;
		}
		return -1;
	}
	int getSize() const{
		return size;
	}
};

#endif
