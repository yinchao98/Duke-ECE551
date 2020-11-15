#include <cstdio>
#include <cstdlib>
#include "set.h"
#include <iostream>

template<typename T>
class BstSet: public Set<T> {
private:
  class Node {
  public:
    T key;
    Node * left;
    Node * right;
    Node(): key(0), left(NULL), right(NULL) {}
    Node(T k): key(k), left(NULL), right(NULL) {}
  };
  Node * root;

public:
    // default constructor
  BstSet<T>(): root(NULL) {}
    // copy constructor
  BstSet(const BstSet & rhs): root(NULL) {
    root = copyHelper(rhs.root);
  }
  Node* copyHelper(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node *copyNode = new Node(current->key);
    copyNode->left = copyHelper(current->left);
    copyNode->right = copyHelper(current->right);
    return copyNode;
  }
  BstSet& operator=(const BstSet & rhs) {
    if(this!= &rhs){
      destroy(root);
      root=copyHelper(rhs.root);
    }
    return *this;
  }
  // destructor
  ~BstSet<T>() {
    destroy(root);
    //root = NULL;
  }
    // destroy
  void destroy(Node * current) {
    if(current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
    // add new key
  virtual void add(const T& key) {
    Node** current = &root;
    while(*current!=NULL) {
        // if key is the same, replace
      if(key == (*current)->key) {
        return;
      }
      if(key < (*current)->key) {
        current = &(*current)->left;
      } else {
       current = &(*current)->right;
      }
    }
    *current = new Node(key);
  }
    // look up if the key exists
  virtual bool contains(const T& key) const {
    Node * current = root;
    while(current != NULL) {
      if(key == current->key) {
       return true;
      }
     if(key < current->key) {
       current = current->left;
      } else {
       current = current->right;
      }
    }
    return false;
  }
  // remove a key
  virtual void remove(const T& key) {
        // search for the key
    Node ** current = &root;
    Node * temp =NULL;
    while(*current != NULL){
      if((*current)->key == key) {
    	// remove the node
       if((*current)->left == NULL) {
         temp = (*current)->right;
         delete *current;
         (*current) = temp;
       } else if ((*current)->right == NULL) {
         temp = (*current)->left;
         delete *current;
         (*current) = temp;
       } else {
         Node ** replaceNode = current;
    	  // go left
         current = &(*current)->left;
    	  // all the way right
         while((*current)->right != NULL) {
           current = &(*current)->right;
         }
         (*replaceNode)->key = (*current)->key;
         temp = (*current)->left;
         delete(*current);
         *current = temp;
       }
     } else if (key < (*current)->key) {
       current = &(*current)->left;
     } else {
       current = &(*current)->right;
     }
   }
  }

  // inorder traverse
  void inOrder(Node * current) {
    if(current != NULL) {
      inOrder(current->left);
      std::cout << current->key << " ";
      inOrder(current->right);
    }
  }

  void inOrderPrint() {
    inOrder(root);
    std::cout << std::endl;
  }

};
