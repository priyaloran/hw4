#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //DONE
    virtual ~BinarySearchTree(); //DONE
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //DONE
    virtual void remove(const Key& key); //DONE
    void clear(); //DONE
    bool isBalanced() const; //DONE
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; //DONE
    Node<Key, Value> *getSmallestNode() const;  //DONE
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); //DONE
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2);

    // Add helper functions here
    // Add a helper function for traversal of the tree since a lot of 
    // function may require this
    // Node<Key, Value>* traverse(const Key& k) const;
    // Add a function for the recursive algorithm in clear()
    void clear2(Node<Key, Value>* curr);
    // Add a function for the recursive algorithm in getSmallestNode()
    Node<Key, Value>* getSmallestNode2(Node<Key, Value>* curr) const;
    // Add a function for the recursive algorithm in isBalanced()
    bool balance2(Node<Key, Value>* curr, int& height) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) :
  // Initialize to the given pointer
  current_(ptr)
{
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
  // Just initialize to NULL
  current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
  return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
  return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
  // Must check if the lhs and rhs iterators are the same node
  return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
  // Must check if the lhs and rhs iterators are pointing
  // to different nodes
  return current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
  // Just return the pointer if the current iterator points to NULL
  if (current_ == NULL) {
    return *this;
  }

  // Move to the right after going to the left most subtree
  if (current_->getRight() != NULL) {
    current_ = current_->getRight();
    while (current_->getLeft() != NULL) {
      current_ = current_->getLeft();
    }
  }
  // Another case would be that there is no right subtree to
  // traverse, so just move up from the parent
  else  {
    Node<Key, Value>* parent = current_->getParent();
    // Go until you are not at the bottom and there are still
    // right positions
    while(parent != NULL && current_ == parent->getRight()) {
      current_ = parent;
      parent = parent->getParent();
    }
    current_ = parent;
  }

  return *this;

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
// SEVENTH: Create the binary search tree by just 
// making an empty tree (set root to NULL)
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
  root_ = NULL;
}

// EIGTH: Just free all the nodes with the clear() function
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
  clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
// FIRST: Write the function for insert for this BST class
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // First we always check if the data structure is empty or not
    if (root_ == NULL) {
      // If it is empty, we must create the start of the tree
      // The parent of the pair is NULL
      root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
      return;
    }

    // Now we must traverse the tree to find where to put the new value
    Node<Key, Value>* target = root_;
    Node<Key, Value>* parent = NULL;
    // Go until the end of the tree is not reached
    while (target != NULL)  {
      parent = target;
      // If the target is greater than the given key value,
      // we go left. Otherwise we go right (use BST property)
      if (keyValuePair.first < target->getKey())  {
        target = target->getLeft();
      }
      else if (keyValuePair.first > target->getKey())  {
        target = target->getRight();
      }
      // Must update the value at that node if a key already exists 
      else  {
        target->setValue(keyValuePair.second);
        return;
      }
    }

    // Once the correct position is found, we must update the new value
    Node<Key, Value>* node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    // Same logic, change left vs right child based on BST property
    if (keyValuePair.first < parent->getKey())  {
      parent->setLeft(node);
    }
    else  {
      parent->setRight(node);
    }

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
// SECOND: For this function there are three main cases we will handle
// - Remove the leaf nodes
// - Promote the child of a node with one child
// - Swap with its predecessor of a node with two children
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
  // First lets store the position of the node we want to remove
  // and parent/child nodes
  Node<Key, Value>* target = internalFind(key);

  // There are two situations. The node is either in the tree or not
  if (!target) {
    return;
  }

  // This block is the code for our three cases (if the key is found)
  // First lets check if there are two children
  if (target->getLeft() && target->getRight())  {
    // Since predecessors only exist if the node has a left child,
    // this node will have a predecessor
    Node<Key, Value>* remove = predecessor(target);
    if (remove)  {
      nodeSwap(target, remove);
    }
  }

  // Since now we know the target is in the tree,
  // we can get its parent (otherwise the function would have ended)
  Node<Key, Value>* parent = target->getParent();
  Node<Key, Value>* child = NULL;

  // Then lets check if there is only one child
  if (target->getLeft() != NULL)  {
    child = target->getLeft();
  }
  else if (target->getRight() != NULL)  {
    child = target->getRight();
  }

  // Then check if the node is the root
  if (target == root_)  {
    root_ = child;
  }
  // Otherwise the node is not the root and has a parent
  // We must then re-assign the children to get prepared for 
  // removal
  else  {
    // Change the parent
    if (parent->getLeft() == target)  {
      parent->setLeft(child);
    }
    else {
      parent->setRight(child);
    }
  }
  // And change the child
    if (child != NULL)  {
      child->setParent(parent);
    }

  // Finally do the actual removal
  delete target;

}

// THIRD: This is a static function for checking in-order predecessor
// of a target node and it is the largest key that is < the current node
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
  // First check if the node is null
  if (current == NULL)  {
    return NULL;
  }

  // First lets traverse the left subtree by going all the
  // way to the leafs on the left side
  // and getting the right most leaf if there is one
  if (current->getLeft()) {
    Node<Key, Value>* old = current->getLeft();
    while (old->getRight() != NULL)  {
      old = old->getRight();
    }
    return old;
  }

  // If the predecessor is in the right subtree then we must 
  // find a child that is right of its parent 
  Node<Key, Value>* parent = current->getParent();
  // Keep going left of the nodes until we reach a node
  // with no left children. Then get the right child
  while (parent && (current == parent->getLeft()))  {
    current = parent;
    parent = parent->getParent();
  }

  // If no predecessor, then just return the parent
  return parent;

}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
// FOURTH: Essentially we want to make an empty tree
// so just delete every single node in a recursive function
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
  // Just call the helper and the set the root to NULL
  // to create an empty tree
  clear2(root_);
  root_ = NULL;
}

// Helper function for the clear() function above
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear2(Node<Key, Value>* curr)
{
  // We initially get the root of a tree and delete from 
  // bottom to top with head recursion
  // Base case checks if tree is empty
  if (curr == NULL) {
    return;
  }

  // Recursive case calls left and right subtree
  clear2(curr->getLeft());
  clear2(curr->getRight());

  // Delete the current node
  delete curr;

}

/**
* A helper function to find the smallest node in the tree.
*/
// FIFTH: We must return a pointer to the smallest node in the tree
// so my approach is to solve this recursively by finding the lestmost
// node
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
  // Use the helper and return it
  // We start at the root
  return getSmallestNode2(root_);
}

// Helper function for getSmallestNode() function above
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode2(Node<Key, Value>* curr) const
{
  // Base case checks if we are at the end or left most node
  if (curr == NULL || curr->getLeft() == NULL)  {
    return curr;
  }

  // Recursive case keeps going left
  curr = curr->getLeft();
  return getSmallestNode2(curr);
  
}

// This is my helper function to traverse the tree
// I just realized this is a function we have to implement anyway
// called internalFind()
/*
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::traverse(const Key& k) const
{
  // First store the node we are using and its parent
  Node<Key, Value>* curr = root_;
  Node<Key, Value>* parent = NULL;

  while (curr != NULL)  {
    // Set the current node the the last node
    parent = curr;

    // Now traverse using the BST property
    if (k < curr->getKey())  {
      // Set it to the left node
      curr = curr->getLeft();
    }
    else if (k > curr->getKey()) {
      curr = curr->getRight();
    }
    else if (k == curr->getKey()) {
      // Key already exists so return it as is
      return curr;
    }
  }
  
  return parent;

}
*/

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
  // First store the node we are using and its parent
  Node<Key, Value>* curr = root_;

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

/**
 * Return true iff the BST is balanced.
 */
// SIXTH: Working with recursively traversing BST tree
// to check if left subtree height is within 1 of right subtree height
// We should build another recursive helper function like the other
// functions above
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
  // Use the helper function by starting with the root_
  // and checking every subtree traverse down
  int h = 0;  // Stores the current height
  return balance2(root_, h);

}

// Helper function for the function above
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balance2(Node<Key, Value>* curr, int& height) const
{
  // Base case checks if the node is null which means it is balanced
  // The height would stay at 0
  if (curr == NULL) {
    height = 0;
    return true;
  }

  // Recursive case checks left and right subtree heights to 
  // ensure balance
  int height1 = 0;
  int height2 = 0;
  bool left = balance2(curr->getLeft(), height1);
  bool right = balance2(curr->getRight(), height2);
  // The height is found by comparing left and right heights
  if (height1 > height2)  {
    height = height1 + 1;
  }
  else  {
    height = height2 + 1;
  }
  // And then return the boolean value if the tree is balanced
  // Basically if the difference is not within -1 to 1
  int check = height1 - height2;
  if (check < -1 || check > 1)  {
    return false;
  }
  return left && right;

}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
