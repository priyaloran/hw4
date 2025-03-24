#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
// Note: Did not add any cout statements
#endif

#include "equal-paths.h"
using namespace std;

// You may add any prototypes of helper functions here
// This helper function will traverse the tree and check
// all path lengths and then check if they are equal size.
// Traversal is from the root to the leaves (can't recurse up
// unless we have parent nodes) so we compare every path going down
// once we reach a leaf
// Note: fullLength must be passed by reference to be rememberred
// by future calls, else it gets deleted
bool helper(Node* curr, int length, int& fullLength, bool& first) 
{

  // First check if the tree is empty. This is the base case
  if (curr == NULL) {
    return true;
  }

  // Second we traverse down the tree until we hit a leaf (left and right are NULL)
  // Once it is a leaf, count the height
  if ((curr->left == NULL) && (curr->right == NULL))  {
    // Now check if we are at our first leaf or not
    // Our first path will obviously be true sicne we haven't
    // compared it to any other path
    if (first)  {
      first = false;
      fullLength = length;
      return true;
    }
    else  {
      // Since we now have another path, we need to compare it
      bool compare = true;
      if (length == fullLength) {
        compare = true;
      }
      else  {
        compare = false;
      }
      return compare;
    }
  }

  // Third is the recursive case, check the left and right of the tree
  bool check1 = helper(curr->left, length + 1, fullLength, first);
  bool check2 = helper(curr->right, length + 1, fullLength, first);

  // Return the results of recursing
  return check1 && check2;

}


bool equalPaths(Node * root)
{
  
  // Initially the full length of the tree we don't know yet,
  // so we set it to 0
  int set = 0;
  bool first = true;
  
  // Now, return the result of our helper
  return helper(root, 0, set, first);

}

