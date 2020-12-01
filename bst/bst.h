#include <cstdio>
#include <cstdlib>
#include <iostream>

template<typename T>
class BST {
private:
  class Node {
  public:
    T data;
    Node * left;
    Node * right;
    explicit Node(T el): data(el), left(NULL), right(NULL) {}
  };
  Node * root;
  template<bool removeAll>
  Node * remove(const T & el, Node * current) {
    if(current == NULL) {
      return NULL;
    }
    if(el == current->data) {
      Node * ans;
      if(removeAll) {
        ans = remove<removeAll>(el, current->left);
        ans  = remove<removeAll>(el, ans->right);
      } else {
        ans = current->left;
      }
      return ans;
    } else if(el < current->data) {
      current->left = remove<removeAll>(el, current->left);
    } else {
      current->right = remove<removeAll>(el, current->right);
    }  
    return current;
  }

public:
    // default constructor
  BST<T>(): root(NULL) {}
    // copy constructor
  BST(const BST & rhs): root(NULL) {
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
  BST& operator=(const BST & rhs) {
    if(this!= &rhs){
      destroy(root);
      root=copyHelper(rhs.root);
    }
    return *this;
  }
  // destructor
  ~BST<T>() {
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

  // add helper
  Node * insertHelper(Node * current, T toAdd) {
    if(current == NULL) {
      Node * ans = new Node(toAdd);
      return ans;
    } else {
      if(toAdd < current->data) {
        Node * newLeft = insertHelper(current->left, toAdd);
        current->left = newLeft;
      } else {
        Node * newRight = insertHelper(current->right, toAdd);
        current->right = newRight;
      }
    }
    return current;
  }
  // add new data
  void insertOrder(T el) {
    root = insertHelper(root, el);
  }

  Node * findHelper(Node * current, const T & el) {
    if(current == NULL) {
      return NULL;
    } 
    if(current->data == el) {
      return current;
    } else if(current->data < el) {
      current = current->left;
      return findHelper(current, el);
    } else {
      current = current->right;
      return findHelper(current, el);
    }
  }

  // return a pointer to the node with el
  Node * find(const T & el) {
    Node * ans = findHelper(root, el);
    if(ans == NULL) {
      throw std::invalid_argument("the key does not exist!\n"); 
    }
    return ans;
  }

  // recursive remove function
  void remove(const T & data) {
    root = remove<false>(data, root);
  }

  void removeAll(const T & data) {
    root = remove<true>(data, root);
  }

  // inorder traverse
  void inOrder(Node * current) {
    if(current != NULL) {
      inOrder(current->left);
      std::cout << current->data << " ";
      inOrder(current->right);
    }
  }

  void inOrderPrint() {
    inOrder(root);
    std::cout << std::endl;
  }

};
