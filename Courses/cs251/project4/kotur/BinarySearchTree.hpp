#ifndef BinarySearchTreehpp
#define BinarySearchTreehpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Node.hpp"
#include <stack>
#include <queue>
#include <vector>

using namespace std;

class BinarySearchTree {
public:
  BinarySearchTree() {
    root = NULL;
    truth = true;
  }

  Node *root;
  bool truth;

  void insertKey(int key) {
    if (root == NULL) {
      Node *tree = new Node(key);
      root = tree;
      return;
    }
    Node *temp = root;
    Node *add = NULL;
    while (temp != NULL) {
      add = temp;
      if (key < temp->key) {
        temp = temp->left;
      }
      else {
        temp = temp->right;
      }
    }
    Node *tree = new Node(key);
    if (key < add->key) {
      add->left = tree;
    }
    else {
      add->right = tree;
    }
    tree->parent = add;
    return;
  }

  int deleteKey(int key) {
    if (root == NULL) {
      return -1;
    }
    if (root->key == key) {
      if (root->left == NULL && root->right == NULL) {
        root = NULL;
      }
      else if (root->left != NULL && root->right == NULL) {
        root = root->left;
      }
      else if (root->left == NULL && root->right != NULL) {
        root = root->right;
      }
      else {
        Node *temp = root;
        temp = root->right;
        while (temp->left != NULL) {
          temp = temp->left;
        }
        root->key = temp->key;
        temp = NULL;
      }
      return 0;
    }
    Node *temp = root;
    Node *parent = NULL;
    while (temp != NULL) {
      if (key < temp->key) {
        parent = temp;
        temp = temp->left;
      }
      else if (key > temp->key) {
        parent = temp;
        temp = temp->right;
      }
      else {
        if (temp->left == NULL && temp->right == NULL) {
          if (parent->left == temp) {
            parent->left = NULL;
          }
          else if (parent->right == temp) {
            parent->right = NULL;
          }
          temp = NULL;
        }
        else if (temp->left != NULL && temp->right == NULL) {
          if (parent->left == temp) {
            parent->left = temp->left;
            temp->left = NULL;
          }
          else if (parent->right == temp) {
            parent->right = temp->left;
            temp->left = NULL;
          }
        }
        else if (temp->left == NULL && temp->right != NULL) {
          if (parent->left == temp) {
            parent->left = temp->right;
            temp->right = NULL;
          }
          else if (parent->right == temp) {
            parent->right = temp->right;
            temp->right = NULL;
          }
        }
        else {
          Node *n = temp;
          n = temp->right;
          while (n->left != NULL) {
            n = n->left;
          }
          temp->key = n->key;
          n = NULL;
        }
        return 0;
      }
    }
    return -1;
  }

  bool searchKey(int key) {
    if (root == NULL) {
      return false;
    }
    Node *temp = root;
    while (temp != NULL) {
      if (key < temp->key) {
        temp = temp->left;
      }
      else if (key > temp->key) {
        temp = temp->right;
      }
      else {
        return true;
      }
    }
    return false;
  }

  int rangeSum(int left, int right) {
    if (root == NULL) {
      truth = false;
      return 0;
    }
    int sum = 0;
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
      Node *temp = q.front();
      q.pop();
      if (temp->key >= left && temp->key <= right) {
        sum += temp->key;
      }
      if (temp->left != NULL) {
        q.push(temp->left);
      }
      if (temp->right != NULL) {
        q.push(temp->right);
      }
    }
    return sum;
  }

  int height(int key) {
    if (root == NULL) {
      truth = false;
      return -1;
    }
    Node *temp = root;
    int count = 0;
    while (temp != NULL) {
      if (key < temp->key) {
        temp = temp->left;
      }
      else if (key > temp->key) {
        temp = temp->right;
      }
      else {
        return count;
      }
      count++;
    }
    truth = false;
    return -1;
  }

  vector<int> postorder() {
    if (root == NULL) {
      return vector<int>();
    }
    stack<Node *> child;
    vector<int> parent;
    child.push(root);
    while (!child.empty()) {
      Node *temp = child.top();
      parent.insert(parent.begin(), temp->key);
      child.pop();
      if (temp->left != NULL) {
        child.push(temp->left);
      }
      if (temp->right != NULL) {
        child.push(temp->right);
      }
    }
    return parent;
  }

  vector<int> levelorder() {
    if (root == NULL) {
      return vector<int>();
    }
    queue<Node *> q;
    vector<int> order;
    q.push(root);
    while (!q.empty()) {
      Node *temp = q.front();
      order.push_back(temp->key);
      q.pop();
      if (temp->left != NULL) {
        q.push(temp->left);
      }
      if (temp->right != NULL) {
        q.push(temp->right);
      }
    }
    return order;
  }

  int LCA(int key1, int key2) {
    if (root == NULL) {
      truth = false;
      return -1;
    }
    if (key1 == key2) {
      return key1;
    }
    vector<int> node1;
    vector<int> node2;
    bool present = false;
    Node *temp = root;
    if (key1 == root->key) {
      node1.push_back(root->key);
    }
    else {
      while (temp != NULL) {
        if (key1 < temp->key) {
          node1.push_back(temp->key);
          temp = temp->left;
        }
        else if (key1 > temp->key) {
          node1.push_back(temp->key);
          temp = temp->right;
        }
        else {
          present = true;
          break;
        }
      }
      if (!present) {
        truth = false;
        return -1;
      }
    }
    temp = root;
    present = false;
    if (key2 == root->key) {
      node2.push_back(root->key);
    }
    else {
      while (temp != NULL) {
        if (key2 < temp->key) {
          node2.push_back(temp->key);
          temp = temp->left;
        }
        else if (key2 > temp->key) {
          node2.push_back(temp->key);
          temp = temp->right;
        }
        else {
          present = true;
          break;
        }
      }
      if (!present) {
        truth = false;
        return -1;
      }
    }
    int count = 0;
    if (node1.size() > node2.size()) {
      count = node2.size();
    }
    else {
      count = node1.size();
    }
    for (int i = count - 1; i > -1; i++) {
      if (node1[i] == node2[i]) {
        return node1[i];
      }
    }
    truth = false;
    return -1;
  }

  int Floor(int key) {
    if (root == NULL) {
      truth = false;
      return -1;
    }
    queue<Node *> q;
    vector<int> nodes;
    q.push(root);
    while (!q.empty()) {
      Node *temp = q.front();
      nodes.push_back(temp->key);
      q.pop();
      if (temp->left != NULL) {
        q.push(temp->left);
      }
      if (temp->right != NULL) {
        q.push(temp->right);
      }
    }
    int floor = nodes[0];
    for (int i = 1; i < nodes.size(); i++) {
      if (nodes[i] <= key) {
        floor = nodes[i];
      }
    }
    for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i] > floor && nodes[i] <= key) {
        floor = nodes[i];
      }
    }
    if (floor > key) {
      truth = false;
      return -1;
    }
    return floor;
  }

  int ceil(int key) {
    if (root == NULL) {
      truth = false;
      return -1;
    }
    queue<Node *> q;
    vector<int> nodes;
    q.push(root);
    while (!q.empty()) {
      Node *temp = q.front();
      nodes.push_back(temp->key);
      q.pop();
      if (temp->left != NULL) {
        q.push(temp->left);
      }
      if (temp->right != NULL) {
        q.push(temp->right);
      }
    }
    int ceil = nodes[0];
    for (int i = 1; i < nodes.size(); i++) {
      if (nodes[i] >= key) {
        ceil = nodes[i];
      }
    }
    for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i] < ceil && nodes[i] >= key) {
        ceil = nodes[i];
      }
    }
    if (ceil < key) {
      truth = false;
      return -1;
    }
    return ceil;
  }

  int dist(int key1, int key2) {
    if (root == NULL) {
      truth = false;
      return -1;
    }
    if (key1 == key2) {
      return 0;
    }
    int lca = LCA(key1, key2);
    if (lca == -1) {
      truth = false;
      return -1;
    }
    Node *temp = root;
    while (temp != NULL) {
      if (lca < temp->key) {
        temp = temp->left;
      }
      else if (lca > temp->key) {
        temp = temp->right;
      }
      else {
        break;
      }
    }
    Node *common = temp;
    int d1 = 0;
    while (common != NULL) {
      if (key1 < common->key) {
        common = common->left;
        d1++;
      }
      else if (key1 > common->key) {
        common = common->right;
        d1++;
      }
      else {
        break;
      }
    }
    common = temp;
    int d2 = 0;
    while (common != NULL) {
      if (key2 < common->key) {
        common = common->left;
        d1++;
      }
      else if (key2 > common->key) {
        common = common->right;
        d1++;
      }
      else {
        break;
      }
    }
    return d1+d2;
  }

  void insertRB(int key) {
    insertKey(key);
    Node *temp = root;
    while (temp != NULL) {
      if (key < temp->key) {
        temp = temp->left;
      }
      else if (key > temp->key) {
        temp = temp->right;
      }
      else {
        break;
      }
    }
    restructure(temp);
  }

  void rotateRight(Node *temp) {
    Node *l = temp->left;
    temp->left = l->right;
    if (l->right != NULL) {
      l->right->parent = temp;
    }
    l->parent = temp->parent;
    if (temp->parent == NULL) {
      root = l;
    }
    else if (temp->parent->left == temp) {
      temp->parent->left = l;
    }
    else {
      temp->parent->right = l;
    }
    l->right = temp;
    temp->parent = l;
  }

  void rotateLeft(Node *temp) {
    Node *r = temp->right;
    temp->right = r->left;
    if (r->left != NULL) {
      r->left->parent = temp;
    }
    r->parent = temp->parent;
    if (temp->parent == NULL) {
      root = r;
    }
    else if (temp->parent->left == temp) {
      temp->parent->left = r;
    }
    else {
      temp->parent->right = r;
    }
    r->left = temp;
    temp->parent = r;
  }

  void restructure(Node *temp) {
    Node *n;
    while (temp->parent != NULL && temp->parent->color == 'R') {
      Node *grandpa = temp->parent->parent;
      if (grandpa->left == temp->parent) {
        n = grandpa->right;
        if (n != NULL && n->color == 'R') {
          temp->parent->color = 'B';
          n->color = 'B';
          grandpa->color = 'R';
          temp = grandpa;
        }
        else {
          if (temp->parent->right == temp) {
            temp = temp->parent;
            rotateLeft(temp);
          }
          temp->parent->color = 'B';
          grandpa->color = 'R';
          rotateRight(grandpa);
        }
      }
      else if (grandpa->right == temp->parent) {
        n = grandpa->left;
        if (n != NULL && n->color == 'R') {
          temp->parent->color = 'B';
          n->color = 'B';
          grandpa->color = 'R';
          temp = grandpa;
        }
        else {
          if (temp->parent->left == temp) {
            temp = temp->parent;
            rotateRight(temp);
          }
          temp->parent->color = 'B';
          grandpa->color = 'R';
          rotateLeft(grandpa);
        }
      }
    }
    root->color = 'B';
  }

  int getBlackHeight(int key) {
    if (root == NULL) {
      truth = false;
      return -1;
    }
    Node *temp = root;
    if (key != root->key) {
      if (!searchKey(key)) {
        truth = false;
        return -1;
      }
      while (temp != NULL) {
        if (key < temp->key) {
          temp = temp->left;
        }
        else if (key > temp->key) {
          temp = temp->right;
        }
        else {
          break;
        }
      }
    }
    queue<pair<Node *, int>> q;
    pair<Node *, int> r = {temp, 1};
    q.push(r);
    while (!q.empty()) {
      r = q.front();
      q.pop();
      temp = r.first;
      int h = r.second;
      if (temp->left == NULL && temp->right == NULL) {
        return h;
      }
      if (temp->left != NULL) {
        r.first = temp->left;
        if (temp->left->color == 'B') {
          r.second = h + 1;
        }
        q.push(r);
      }
      if (temp->right != NULL) {
        r.first = temp->right;
        if (temp->right->color == 'B') {
          r.second = h + 1;
        }
        q.push(r);
      }
    }
    truth = false;
    return -1;
  }
};

#endif // BinarySearchTreehpp
