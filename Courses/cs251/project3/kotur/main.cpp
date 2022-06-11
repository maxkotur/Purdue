#include <iostream>
#include<sstream>
#include<fstream>

#include "HashTable.hpp"
#include "HeapPriorityQueue.hpp"

using namespace std;
void read_part_1(ifstream &inputfile, ofstream &outputfile) {
	HashTable <const int&> hash(3);
	int length;
	inputfile >> length;
	char cmd;
	string key;
	int value;
	for (int i = 0; i < length; i++) {
		inputfile >> cmd;
		if (cmd == 'p') {
			inputfile >> key >> value;
      const string &k = key;
      const int &num = value;
      const int &val = hash.put(k, num);
			if (hash.getnull()) {
				hash.setnull(false);
				outputfile << "null\n";
			}
			else {
				int v = val;
				outputfile << v << "\n";
			}
		}
		else if (cmd == 'g') {
			inputfile >> key;
      const int &val = hash.get(key);
			if (hash.getnull()) {
				hash.setnull(false);
				outputfile << "null\n";
			}
			else {
				int v = val;
				outputfile << v << "\n";
			}
		}
		else if (cmd == 'r') {
			inputfile >> key >> value;
			const string &k = key;
			const int &num = value;
      const int &val = hash.replace(k, num);
			if (hash.getnull()) {
				hash.setnull(false);
				outputfile << "null\n";
			}
			else {
				int v = val;
				outputfile << v << "\n";
			}
		}
		else if (cmd == 'd') {
			inputfile >> key;
			const string &k = key;
      const int &val = hash.remove(k);
			if (hash.getnull()) {
				hash.setnull(false);
				outputfile << "null\n";
			}
			else {
				int v = val;
				outputfile << v << "\n";
			}
		}
		else if (cmd == 's') {
			int size = hash.size();
			outputfile << size << "\n";
		}
		else if (cmd == 'c') {
			inputfile >> key;
			bool contains = hash.containsKey(key);
			if (contains) {
				outputfile << "1\n";
			}
			else {
				outputfile << "0\n";
			}
		}
		else if (cmd == 'm') {
			int index;
			inputfile >> index;
			int collisions = hash.getCollision(index);
			outputfile << collisions << "\n";
		}
	}
}

void read_part_3(ifstream &inputfile, ofstream &outputfile) {
  HeapPriorityQueue <int> heap(10);
  int length;
	inputfile >> length;
  char cmd;
  for (int i = 0; i < length; i++) {
    inputfile >> cmd;
    if (cmd == 'i') {
      int value;
      inputfile >> value;
      const int &val = value;
      heap.insert(val);
    }
    else if (cmd == 'm') {
      if (heap.size() == 0) {
        outputfile << "empty\n";
      }
      else {
        int min = heap.min();
        outputfile << min << "\n";
      }
    }
    else if (cmd == 'r') {
      if (heap.size() == 0) {
        outputfile << "empty\n";
      }
      else {
        heap.removeMin();
      }
    }
    else if (cmd == 's') {
      if (heap.size() == 0) {
        outputfile << "empty\n";
      }
      else {
        int* items;
        int length = heap.size();
        items = heap.sort();
        for (int i = 0; i < length; i++) {
          outputfile << items[i] << "\n";
        }
      }
    }
  }
}


int main(int argc, char *argv[]) {
	//Read in the test case
   ifstream inputfile;
   ofstream outputfile;

   inputfile.open(argv[1]);
   outputfile.open(argv[2]);

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
           read_part_1(inputfile, outputfile);
           break;
       case 3:
           read_part_3(inputfile, outputfile);
           break;
   }

	return 0;
}

