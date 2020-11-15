#include <cstdio>
#include <cstdlib>
#include "map.h"
#include <iostream>

template<typename K, typename V>
class BstMap: public Map<K,V> {
private:
  class Node {
  public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(): key(0), value(0), left(NULL), right(NULL) {}
    Node(K k, V v): key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

public:
    // default constructor
  BstMap<K,V>(): root(NULL) {}
    // copy constructor
  BstMap(const BstMap & rhs): root(NULL) {
    root = copyHelper(rhs.root);
  }
  Node* copyHelper(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node *copyNode = new Node(current->key, current->value);
    copyNode->left = copyHelper(current->left);
    copyNode->right = copyHelper(current->right);
    return copyNode;
  }
  BstMap& operator=(const BstMap & rhs) {
    if(this!= &rhs){
      destroy(root);
      root=copyHelper(rhs.root);
    }
    return *this;
  }
  // destructor
  ~BstMap<K,V>() {
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
    // add new key-value pair
  virtual void add(const K& key, const V& value) {
    Node** current = &root;
    while(*current!=NULL) {
        // if key is the same, replace
      if(key == (*current)->key) {
       (*current)->value = value;
       return;
     }
     if(key < (*current)->key) {
       current = &(*current)->left;
     } else {
       current = &(*current)->right;
     }
   }
   *current = new Node(key, value);
 }
    // look up a value
  virtual const V & lookup(const K& key) const throw(std::invalid_argument) {
    Node * current = root;
    while(current != NULL) {
      if(key == current->key) {
       return current->value;
      }
     if(key < current->key) {
       current = current->left;
      } else {
       current = current->right;
      }
    }
    throw std::invalid_argument("the key does not exist!\n");
  }
    // remove a key
  virtual void remove(const K& key) {
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
         (*replaceNode)->value = (*current)->value;
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
      std::cout << "(" << current->key << ", " << current->value << ") ";
      inOrder(current->right);
    }
  }

  void inOrderPrint() {
    inOrder(root);
    std::cout << std::endl;
  }

};
