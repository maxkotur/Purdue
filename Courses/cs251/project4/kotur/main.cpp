#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Node.hpp"
#include "Rhymer.hpp"
#include "BinarySearchTree.hpp"

using namespace std;

void read_part_1(ifstream &inputfile, ofstream &outputfile) {
  int part;
  inputfile >> part;
  if (part == 1) {
    int length;
    inputfile >> length;
    Rhymer rhyme(length);
    for (int i = 0; i < length; i++) {
      string word;
      inputfile >> word;
      word = rhyme.reverse(word);
      rhyme.getArray()[i] = word;
    }
    rhyme.quickSort(0, length - 1);
    for (int i = 0; i < length; i++) {
      outputfile << rhyme.reverse(rhyme.getArray()[i]) << "\n";
    }
  }
  else if (part == 2) {
    int key;
    inputfile >> key;
    int length;
    inputfile >> length;
    Rhymer rhyme(length);
    string *nonrev = new string[length];
    for (int i = 0; i < length; i++) {
      string word;
      inputfile >> word;
      nonrev[i] = word;
      word = rhyme.reverse(word);
      rhyme.getArray()[i] = word;
    }
    vector<pair<string, int>> suffix;
    string *arr = rhyme.getArray();
    for (int i = 0; i < length; i++) {
      for (int k = 0; k < arr[i].length(); k++) {
        string share = arr[i].substr(0, k + 1);
        int count = 0;
        bool truth = false;
        pair<string,int> p;
        for (int j = 0; j < length; j++) {
          if (arr[j].size() < k + 1) {
            continue;
          }
          if (share.compare(arr[j].substr(0, k + 1)) == 0) {
            if (count == 0) {
              p.first = rhyme.reverse(share);
              for (int l = 0; l < suffix.size(); l++) {
                if (suffix[l].first == p.first) {
                  truth = true;
                  break;
                }
              }
            }
            count++;
          }
          if (truth) {
            break;
          }
        }
        if (truth) {
          continue;
        }
        if (count < key) {
          break;
        }
        else if (count >= key) {
          p.second = count;
          suffix.push_back(p);
        }
      }
    }
    pair<string, int> *suff = &suffix[0];
    rhyme.setSuffix(suff);
    rhyme.SuffixQuickSort(0, suffix.size() - 1);
    suff = rhyme.getSuffix();
    rhyme.setArray(nonrev);
    rhyme.quickSort(0, length - 1);
    nonrev = rhyme.getArray();
    for (int i = 0; i < suffix.size(); i++) {
      string s = suff[i].first;
      outputfile << s << " -> [";
      int count = 0;
      for (int j = 0; j < length; j++) {
        if (nonrev[j].size() < s.length()) {
          continue;
        }
        int sec = suff[i].second;
        if (rhyme.reverse(s).compare(rhyme.reverse(
          nonrev[j]).substr(0, s.length())) == 0) {
          count++;
          if (sec == count) {
            outputfile << nonrev[j];
          }
          else {
            outputfile << nonrev[j] << ", ";
          }
        }
        if (sec == count) {
          break;
        }
      }
      outputfile << "]\n";
    }
  }
}

void read_part_2(ifstream &inputfile, ofstream &outputfile) {
  int length;
  inputfile >> length;
  BinarySearchTree tree;
  for (int i = 0; i < length; i++) {
    string cmd;
    inputfile >> cmd;
    if (cmd == "insert") {
      int key;
      inputfile >> key;
      tree.insertKey(key);
    }
    else if (cmd == "delete") {
      int key;
      inputfile >> key;
      int del = tree.deleteKey(key);
      if (del == 0) {
        outputfile << "deleted\n";
      }
      else {
        outputfile << "deletion failed\n";
      }
    }
    else if (cmd == "search") {
      int key;
      inputfile >> key;
      bool search = tree.searchKey(key);
      if (search) {
        outputfile << "found\n";
      }
      else {
        outputfile << "not found\n";
      }
    }
    else if (cmd == "range") {
      int left;
      int right;
      inputfile >> left >> right;
      int range = tree.rangeSum(left, right);
      if (!tree.truth) {
        tree.truth = true;
        outputfile << "none\n";
      }
      else {
        outputfile << range << "\n";
      }
    }
    else if (cmd == "height") {
      int key;
      inputfile >> key;
      int height = tree.height(key);
      if (!tree.truth) {
        tree.truth = true;
        outputfile << "none\n";
      }
      else {
        outputfile << height << "\n";
      }
    }
    else if (cmd == "postorder") {
      vector<int> post = tree.postorder();
      if (post.empty()) {
        outputfile << "none\n";
      }
      else {
        for (int j = 0; j < post.size(); j++) {
          outputfile << post[j] << " ";
        }
        outputfile << "\n";
      }
    }
    else if (cmd == "levelorder") {
      vector<int> level = tree.levelorder();
      if (level.empty()) {
        outputfile << "none\n";
      }
      else {
        for (int j = 0; j < level.size(); j++) {
          outputfile << level[j] << " ";
        }
        outputfile << "\n";
      }
    }
    else if (cmd == "lca") {
      int key1, key2;
      inputfile >> key1 >> key2;
      int lca = tree.LCA(key1, key2);
      if (!tree.truth) {
        tree.truth = true;
        outputfile << "none\n" ;
      }
      else {
        outputfile << lca << "\n";
      }
    }
    else if (cmd == "floor") {
      int key;
      inputfile >> key;
      int floor = tree.Floor(key);
      if (!tree.truth) {
        tree.truth = true;
        outputfile << "none\n";
      }
      else {
        outputfile << floor << "\n";
      }
    }
    else if (cmd == "ceil") {
      int key;
      inputfile >> key;
      int ceil = tree.ceil(key);
      if (!tree.truth) {
        tree.truth = true;
        outputfile << "none\n";
      }
      else {
        outputfile << ceil << "\n";
      }
    }
    else if (cmd == "dist") {
      int key1, key2;
      inputfile >> key1 >> key2;
      int dist = tree.dist(key1, key2);
      if (!tree.truth) {
        tree.truth = true;
        outputfile << "none\n";
      }
      else {
        outputfile << dist << "\n";
      }
    }
    else if (cmd == "insertRB") {
      int key;
      inputfile >> key;
      tree.insertRB(key);
    }
    else {
      int key;
      inputfile >> key;
      int Bheight = tree.getBlackHeight(key);
      if (!tree.truth) {
        tree.truth = true;
        outputfile << "none\n";
      }
      else {
        outputfile << Bheight << "\n";
      }
    }
  }
}

int main(int argc, char *argv[]) {
    //Read in the test case
    ifstream inputfile;
    ofstream outputfile;

    if(argc==3) {
        inputfile.open(argv[1]);
        outputfile.open(argv[2]);
    }
    else {
        cout<<"Not enough arguments"<<endl;
    }

    string str;

    getline(inputfile, str);
    int part;
    stringstream convert(str);
    convert >> part;

    switch(part) {
        case 1:
            read_part_1(inputfile, outputfile);
            break;
        case 2:
            read_part_2(inputfile,outputfile);
            break;
    }

	return 0;
}

