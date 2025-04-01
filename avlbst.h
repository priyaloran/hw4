#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); //DONE
    virtual void remove(const Key& key);  //DONE
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    // We are going to create 2 helper functions for the rotations
    // We need a left and right rotation we will call rotation1 and
    // rotation2 respectively
    void rotation1(AVLNode<Key, Value>* curr);
    void rotation2(AVLNode<Key, Value>* curr);
    // This helper is to rebalance the tree after insert
    void insertHelper(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* curr);
    // This helper is to rebalance the tree after remove
    void removeHelper(int num, AVLNode<Key, Value>* curr);
    // This is the helper for predecessor
    AVLNode<Key, Value>* predecessor2(AVLNode<Key, Value>* curr);
    // This is the helper for internalFind
    AVLNode<Key, Value>* internalFind2(const Key& key);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
// For this class we must ensure the tree is balanced
// by doing rotations to the left and right with the
// formulas we used in class. We need to first treat it 
// like a BST by traversing the tree and insert when
// we can't traverse further. Then we update the value
// and perform rotations
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
  
  // It is crucial to check if the tree is empty as well, because
  // we need to assign the root a new node and then we are just done
  if (static_cast<AVLNode<Key, Value>*>(this->root_) == NULL)  {
    this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    return;
  }

  // First lets insert the new item by using the BST property
  // like how we did with the BST
  AVLNode<Key, Value>* parent = NULL;
  AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(static_cast<AVLNode<Key, Value>*>(this->root_));
  // As long as we are not at the bottom, traverse down to place
  // the value 
  while (curr != NULL)  {
    parent = curr;
    if (new_item.first < curr->getKey())  {
      curr = curr->getLeft();
    }
    else if (new_item.first > curr->getKey())  {
      curr = curr->getRight();
    }
    else  {
      curr->setValue(new_item.second);
        return;
    }
  }

  // Now we put the new item in this position
  AVLNode<Key, Value>* add = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
  add->setBalance(0);
  // If the parent is the root (NULL), just add it to the root
  // Otherwise use the BST property again with the new parent position
  // to put the new value in the left or right spot
  if (parent == NULL) {
    this->root_ = add;
    return;
  }
  else if (new_item.first < parent->getKey()) {
    parent->setLeft(add);
  }
  else  {
    parent->setRight(add);
  }

  // Finally we must rebalance the tree
  // This is where we must use helper function to do rotations
  // Rotations must be made if the balance factor is -2 or 2
  // - If it is -2, we must do a left rotation on the child 
  // and a right rotation on the parent and then finally a right rotation
  // - If it is 2, we must do a right rotation on the child and a 
  // left rotation on the parent and then finally a left rotation
  if  (parent->getBalance() == -1 || parent->getBalance() == 1)  {
    parent->setBalance(0);
    return;
  }
  else if (parent->getBalance() == 0) {
    if (add == parent->getLeft()) {
      parent->setBalance(-1);
    }
    else  {
      parent->setBalance(1);
    }
    insertHelper(parent, add);
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertHelper(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* curr)
{
  if (parent == NULL) {
    return;
  }

  AVLNode<Key, Value>* grand = parent->getParent();
  if (grand == NULL)  {
    return;
  }

  if (parent == grand->getLeft()) {
    grand->updateBalance(-1);

    if (grand->getBalance() == 0) {
      return;
    }
    else if (grand->getBalance() == -1) {
      insertHelper(grand, parent);
    }
    else if (grand->getBalance() == -2) {
      if (curr == parent->getLeft())  {
        rotation2(grand);
        parent->setBalance(0);
        grand->setBalance(0);
      }
      else  {
        rotation1(parent);
        rotation2(grand);
        if (curr->getBalance() == -1) {
          parent->setBalance(0);
          grand->setBalance(1);
          curr->setBalance(0);
        }
        else if (curr->getBalance() == 0) {
          parent->setBalance(0);
          grand->setBalance(0);
        }
        else if (curr->getBalance() == 1) {
          parent->setBalance(-1);
          grand->setBalance(0);
          curr->setBalance(0);
        }
      }
    }
  }

  else {
    grand->updateBalance(1);

    if (grand->getBalance() == 0) {
      return;
    }
    else if (grand->getBalance() == 1) {
      insertHelper(grand, parent);
    }
    else if (grand->getBalance() == 2) {
      if (curr == parent->getLeft())  {
        rotation2(parent);
        rotation1(grand);
        if (curr->getBalance() == 1) {
          parent->setBalance(0);
          grand->setBalance(-1);
        }
        else if (curr->getBalance() == 0) {
          parent->setBalance(0);
          grand->setBalance(0);
        }
        else if (curr->getBalance() == -1)  {
          parent->setBalance(1);
          grand->setBalance(0);
        }
        curr->setBalance(0);
      }
      else  {
        rotation1(grand);
        parent->setBalance(0);
        grand->setBalance(0);
      }
    }
  }
}

// Now lets impliment the helper functions for the insert function
// Left rotation balance factors are greater than 1 because
// insertion was in the right of the subtree
template<class Key, class Value>
void AVLTree<Key, Value>::rotation1(AVLNode<Key, Value>* curr)  
{
  // We must save a node (the input) and fix its left, right, and parent node
  // in the left direction
  // The curr must be rotated left around fixNode so that fixNode
  // is the new root
  AVLNode<Key, Value>* fixNode = curr->getRight();

  if (curr == static_cast<AVLNode<Key, Value>*>(this->root_))  {
    this->root_ = fixNode;
    fixNode->setParent(NULL);
  }

  else  {
    if (curr->getParent()->getLeft() == curr) {
      curr->getParent()->setLeft(fixNode);
      fixNode->setParent(curr->getParent());
    }
    else if (curr->getParent()->getRight() == curr) {
      curr->getParent()->setRight(fixNode);
      fixNode->setParent(curr->getParent());
    }
  }

  AVLNode<Key, Value>* b = fixNode->getLeft();
  curr->setParent(fixNode);
  fixNode->setLeft(curr);
  curr->setRight(b);

  if  (b != NULL) {
    b->setParent(curr);
  }

}

// Same intuition as the left rotation, but the right rotation
// balance factors are less than 1 because
// insertion was in the left of the subtree
template<class Key, class Value>
void AVLTree<Key, Value>::rotation2(AVLNode<Key, Value>* curr)  
{

  AVLNode<Key, Value>* fixNode = curr->getLeft();

  if (curr == static_cast<AVLNode<Key, Value>*>(this->root_))  {
    this->root_ = fixNode;
    fixNode->setParent(NULL);
  }

  else  {
    if (curr->getParent()->getLeft() == curr) {
      curr->getParent()->setLeft(fixNode);
      fixNode->setParent(curr->getParent());
    }
    else if (curr->getParent()->getRight() == curr) {
      curr->getParent()->setRight(fixNode);
      fixNode->setParent(curr->getParent());
    }
  }

  AVLNode<Key, Value>* b = fixNode->getRight();
  curr->setParent(fixNode);
  fixNode->setRight(curr);
  curr->setLeft(b);

  if  (b != NULL) {
    b->setParent(curr);
  }
  
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
// Remove function is similar to insert, but we must find the node
// to remove and handle the same 3 cases as BST tree, and then 
// traverse up to rebalance the tree
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)  
{
  // We can use the helper function in the BST class to help us find
  // the node to remove
  AVLNode<Key, Value>* target = this->internalFind2(key);

  // Check if the key actually exists after that function
  if (target == NULL) return;

  // Create the difference variable for balancing
  int x = 0;

  // Our first case is if there are two children
  if (target->getLeft() != NULL && target->getRight() != NULL) {
      // Since predecessors only exist if the node has a left child,
      // this node will have a predecessor
      AVLNode<Key, Value>* pred = this->predecessor2(target);
      this->nodeSwap(target, pred);
  }

  // Store the node so we can check if it has a certain
  // number of children
  AVLNode<Key, Value>* parent = target->getParent();
      if (parent != NULL) {
      if (parent->getLeft() == target)  {
        x = 1;
      }
      else  {
        x = -1;
      }
  }

  AVLNode<Key, Value>* child = NULL;

  if (target->getLeft() != NULL)  {
    child = target->getLeft();
  }
  else  {
    child = target->getRight();
  }

    if (child != NULL) {
        // Our second/third case involves only one child (left or right)
        child->setParent(target->getParent());
        if (parent == NULL) {
            this->root_ = child;
        } else if (parent->getLeft() == target) {
            parent->setLeft(child);
        } else {
            parent->setRight(child);
        }
        delete target;
        removeHelper(x, parent);
  // Our fourth case involves no children
  // Check if the node is the root
    } else {
        // 
        if (parent == NULL) {
            delete target;
            this->root_ = NULL;
        } else {
            if (parent->getLeft() == target) {
                parent->setLeft(NULL);
                x = 1;
            } else {
                parent->setRight(NULL);
                x = -1;
            }
            delete target;
            removeHelper(x, parent);
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::removeHelper(int num, AVLNode<Key, Value>* curr)
{
  if (curr == NULL) {
    return;
  }

  AVLNode<Key, Value>* parent = curr->getParent();
  int num2 = 0;

  if (parent != NULL) {
    if (static_cast<AVLNode<Key,Value>*>(parent->getLeft()) == curr)  {
      num2 = 1;
    }
    else  {
      num2 = -1;
    }
  }

  int balance = curr->getBalance() + num;

  if ((balance) == -2) {
    AVLNode<Key, Value>* left = curr->getLeft();
    int balance_left = left->getBalance();

    if (balance_left == -1) {
      rotation2(curr);
      curr->setBalance(0);
      left->setBalance(0);
      removeHelper(num2, parent);
    }
    else if (balance_left == 0) {
      rotation2(curr);
      curr->setBalance(-1);
      left->setBalance(1);
      return;
    }
    else if (balance_left == 1) {
      AVLNode<Key, Value>* right = left->getRight();
      rotation1(left);
      rotation2(curr);
      
      if (right->getBalance() == 1) {
        curr->setBalance(0);
        left->setBalance(-1);
      }
      else if (right->getBalance() == 0) {
        curr->setBalance(0);
        left->setBalance(0);
      }
      else  {
        curr->setBalance(1);
        left->setBalance(0);
      }
      right->setBalance(0);
      removeHelper(num2, parent);
    }
  }

  else if ((balance) == 2) {
    AVLNode<Key, Value>* right = curr->getRight();
    int balance_right = right->getBalance();

    if (balance_right == 1) {
      rotation1(curr);
      curr->setBalance(0);
      right->setBalance(0);
      removeHelper(num2, parent);
    }
    else if (balance_right == 0) {
      rotation1(curr);
      curr->setBalance(1);
      right->setBalance(-1);
      return;
    }
    else if (balance_right == -1) {
      AVLNode<Key, Value>* left = right->getLeft();
      rotation2(right);
      rotation1(curr);
      
      if (left->getBalance() == -1) {
        curr->setBalance(0);
        right->setBalance(1);
      }
      else if (left->getBalance() == 0) {
        curr->setBalance(0);
        right->setBalance(0);
      }
      else  {
        curr->setBalance(-1);
        right->setBalance(0);
      }

      left->setBalance(0);
      removeHelper(num2, parent);
    }
  }

  else if ((balance) == -1 || (balance) == 1)   {
    curr->setBalance(balance);
    return;
  }

  else  {
    curr->setBalance(0);
    removeHelper(num2, parent);
  }

}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::internalFind2(const Key& key) 
{
  // First store the node we are using and its parent
  AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);

  while (curr != NULL)  {

    // Now traverse using the BST property
    if (key < curr->getKey())  {
      // Set it to the left node
      curr = curr->getLeft();
    }
    else if (key > curr->getKey()) {
      curr = curr->getRight();
    }
    else if (key == curr->getKey()) {
      // Key already exists so return it as is
      return curr;
    }
  }

  return NULL;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor2(AVLNode<Key, Value>* curr)  
{
    // First check if the node is null
  if (curr == NULL)  {
    return NULL;
  }

  // First lets traverse the left subtree by going all the
  // way to the leafs on the left side
  // and getting the right most leaf if there is one
  if (curr->getLeft()) {
    AVLNode<Key, Value>* old = curr->getLeft();
    while (old->getRight() != NULL)  {
      old = old->getRight();
    }
    return old;
  }
  else  {
    AVLNode<Key, Value>* copy = curr;
    while (copy != NULL)  {
      AVLNode<Key, Value>* child = copy;
      copy = copy->getParent();
      
      if  (copy == NULL)  {
        return NULL;
      }
      if (copy->getRight() == child)  {
        return copy;
      }
    } 
  }
  return NULL;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif