#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>

using namespace std;

class Node {
public:
  Node(int k) {
    key = k;
    color = 'R';
    left = NULL;
    right = NULL;
    parent = NULL;
  }

  Node *left;
  Node *right;
  Node *parent;
  char color;
  int key;
};

#endif // Node_hpp

