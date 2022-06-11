//
//  HashTable.hpp
//  SeperateChaining
//
//  Created by Wenjie Bai on 2/6/19.
//  Copyright © 2019 Wenjie Bai. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include "NotImplementedException.hpp"
//throw NotImplementedException whenever you are asked to pop something
//from an empty container.
#include <iostream>
#include <list>
#include <iterator>
#include <utility>
#include <vector>
#include <string>
using namespace std;


const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
  53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
  137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
  223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271};

template <typename V> class
Entry {
public:
    Entry(const string& k, const V& v)
    :   _key(k),   _value(v) { }
    const string& getkey() const {return _key;}
    void setkey(const string key) {_key = key;}
    const V& getvalue() const {return _value;}
    void setvalue(V& value) {_value = value;}
private:
    string _key;
    V _value;
};

template <typename V>
class HashTable {
public:
    HashTable(int capacity) {
      table = new list<Entry<V>>[capacity];
      items = 0;
      length = capacity;
      null = false;
    }

    int size() {
      return items;
    }

    int hashCode(const string& s) {
      string str = s;
      int sum = 0;
      int letter;
      for (int i = 0; i < str.length(); i++) {
        letter = str.at(i);
        sum += letter;
      }
      return sum % length;
    }

    V put(const string& k, const V& v) {
      int index = hashCode(k);
      Entry<V> value(k, v);
      int check = 0;
      typename list<Entry<V>>::iterator it;
      for (it = table[index].begin(); it != table[index].end(); it++) {
        if (it->getkey() == k && it->getvalue() == v) {
          Entry<V> old(it->getkey(), it->getvalue());
          it = table[index].erase(it);
          table[index].insert(it, value);
          check == 1;
          break;
        }
      }
      if (check == 0) {
        table[index].push_back(value);
        null = true;
      }
      items++;
      check = length/items;
      if (check <= 2) {
        rehash();
      }
      return value.getvalue();
    }

    V get(const string& k) {
      int index = hashCode(k);
      typename list<Entry<V>>::iterator it;
      it = table[index].begin();
      for (it; it != table[index].end(); it++) {
        if (it->getkey() == k) {
          return it->getvalue();
        }
      }
      null = true;
      Entry<V> value("", 0);
      return value.getvalue();
    }

    bool containsKey(const string& k) {
      int index = hashCode(k);
      typename list<Entry<V>>::iterator it;
      it = table[index].begin();
      for (it; it != table[index].end(); it++) {
        if (it->getkey() == k) {
          return true;
        }
      }
      return false;
    }

    V remove(const string& k) {
      if (items == 0) {
        throw NotImplementedException();
        null = true;
        Entry<V> value("", 0);
        return value.getvalue();
      }
      int index = hashCode(k);
      typename list<Entry<V>>::iterator it;
      it = table[index].begin();
      for (it; it != table[index].end(); it++) {
        if (it->getkey() == k) {
          Entry<V> value(k, it->getvalue());
          it = table[index].erase(it);
          items--;
          return value.getvalue();
        }
      }
      null = true;
      Entry<V> value("", 0);
      return value.getvalue();
    }

    size_t getCollision(int hashIndex) {
      return table[hashIndex].size();
    }

    V replace(const string& k, const V& v) {
      int index = hashCode(k);
      Entry<V> value(k, v);
      typename list<Entry<V>>::iterator it;
      it = table[index].begin();
      for (it; it != table[index].end(); it++) {
        if (it->getkey() == k) {
          it = table[index].erase(it);
          table[index].insert(it, value);
          return value.getvalue();
        }
      }
      null = true;
      return value.getvalue();
    }

    void rehash() {
      int old = length;
      length *= 2;
      for (int i = 0; i < 58; i++) {
        if (primes[i] > length) {
          length = primes[i];
          break;
        }
      }
      list<Entry<V>> *rehash = new list<Entry<V>>[length];
      for (int i = 0; i < old; i++) {
        typename list<Entry<V>>::iterator it;
        it = table[i].begin();
        for (it; it != table[i].end(); it++) {
          int index = hashCode(it->getkey());
          Entry<V> value(it->getkey(), it->getvalue());
          rehash[index].push_back(value);
        }
      }
      table = rehash;
    }

    void setnull(bool nul) {
      null = nul;
      return;
    }

    bool getnull() {
      return null;
    }

private:
    //vector<list<Entry<V>>> theLists;   // The array of Lists
    list<Entry<V>> *table;
    int items;
    int length;
    bool null;
};
#endif /* HashTable_hpp */
