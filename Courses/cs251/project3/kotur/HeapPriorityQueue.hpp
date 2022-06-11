//
//  HeapPriorityQueue.hpp
//
//  Created by Wenjie Bai on 2/7/19.
//  Copyright © 2019 Wenjie Bai. All rights reserved.
//

#ifndef HeapPriorityQueue_hpp
#define HeapPriorityQueue_hpp

#include <stdio.h>
#include "NotImplementedException.hpp"
//throw NotImplementedException whenever you are asked to pop something
//from an empty container.
#include <vector>
using namespace std;

template <typename Item>
class HeapPriorityQueue {
public:
    HeapPriorityQueue(int capacity) {
      array.resize(capacity);
      currentSize = 0;
      length = capacity;
    }

    bool empty() const {
      if (array.empty()) {
        return true;
      }
      return false;
    }

    const Item& min() const {
      if (currentSize == 0) {
        throw NotImplementedException();
        const Item &temp = 0;
        return temp;
      }
      Item smallest = array[0];
      for (int i = 1; i < currentSize; i++) {
        if (smallest > array[i]) {
          smallest = array[i];
        }
      }
      const Item &small = smallest;
      return small;
    }

    void insert(const Item &x) {
      array.insert(array.begin(), x);
      currentSize++;
    }

    void removeMin() {
      if (currentSize == 0) {
        throw NotImplementedException();
        return;
      }
      for (int i = 0; i < currentSize; i++) {
        if (array[i] == min()) {
          array.erase(array.begin() + i);
          break;
        }
      }
      currentSize--;
    }

    int* sort() {
      int* items = new int[currentSize];
      int size = currentSize;
      for (int i = 0; i < size; i++) {
        items[i] = min();
        removeMin();
      }
      currentSize = 0;
      return items;
    }

    void resize() {
      array.resize(length*2);
      length *= 2;
    }

    int size() {
      return currentSize;
    }

private:
    int currentSize;  // Number of elements in heap
    vector<Item> array;        // The heap array
    int length;

};
#endif /* HeapPriorityQueue_hpp */

