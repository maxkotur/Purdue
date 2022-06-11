#ifndef Rhymer_hpp
#define Rhymer_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Rhymer {
public:
  Rhymer(int length) {
    array = new string[length];
    suffix = new pair<string, int>[0];
  }

  pair<string, int> *getSuffix(){
    return suffix;
  }

  void setSuffix(pair<string, int> *suff) {
    suffix = suff;
  }

  string *getArray(){
    return array;
  }

  void setArray(string *arr) {
    array = arr;
  }

  string reverse(string word) {
    int len = word.length();
    for (int i = 0; i < len/2; i++) {
      swap(word.at(i), word.at(len - i - 1));
    }
    return word;
  }

  bool alphasort(string word, string comp) {
    int c = word.compare(comp);
    if (c > 0) {
      return false;
    }
    return true;
  }

  void swapper(int start, int end) {
    string temp = array[end];
    array[end] = array[start];
    array[start] = temp;
  }

  int partition(int start, int end) {
    string pivot = array[end];
    int j = start - 1;
    for (int i = start; i < end; i++) {
      if (!alphasort(pivot, array[i])) {
        j++;
        swapper(j, i);
      }
    }
    swapper(j + 1, end);
    return j + 1;
  }

  void quickSort(int start, int end) {
    int part;
    if (start < end) {
      part = partition(start, end);
      quickSort(start, part - 1);
      quickSort(part + 1, end);
    }
  }

  void SuffixSwapper(int start, int end) {
    pair<string, int> temp = suffix[end];
    suffix[end] = suffix[start];
    suffix[start] = temp;
  }

  int SuffixPartition(int start, int end) {
    string pivot = suffix[end].first;
    int j = start - 1;
    for (int i = start; i < end; i++) {
      if (!alphasort(pivot, suffix[i].first)) {
        j++;
        SuffixSwapper(j, i);
      }
    }
    SuffixSwapper(j + 1, end);
    return j + 1;
  }

  void SuffixQuickSort(int start, int end) {
    int part;
    if (start < end) {
      part = SuffixPartition(start, end);
      SuffixQuickSort(start, part - 1);
      SuffixQuickSort(part + 1, end);
    }
  }

private:
  string *array;
  pair<string, int> *suffix;
};

#endif // Rhymer_hpp
