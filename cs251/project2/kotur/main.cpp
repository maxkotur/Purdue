#include <iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "stack.cpp"
#include "circular_deque.cpp"

using namespace std;

Pair find(char cha, Pair pair, char **search,	int rows, int cols, int count) {
	int counter = 0;
	if (pair.row == 0	&& pair.col == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else if (pair.row == 0 && pair.col == cols - 1) {
		for (int i = 0; i < 2; i++) {
			for (int j = cols - 2; j < cols; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else if (pair.row == rows - 1 && pair.col == 0) {
		for (int i = rows - 2; i < rows; i++) {
			for (int j = 0; j < 2; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else if (pair.row == rows - 1 && pair.col == cols - 1) {
		for (int i = rows - 2; i < rows; i++) {
			for (int j = cols - 2; j < cols; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else if (pair.row == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = pair.col - 1; j < pair.col + 2; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else if (pair.col == 0) {
		for (int i = pair.row - 1; i < pair.row + 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else if (pair.row == rows - 1) {
		for (int i = rows - 2; i < rows; i++) {
			for (int j = pair.col - 1; j < pair.col + 2; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else if (pair.col == cols - 1) {
		for (int i = pair.row - 1; i < pair.row + 2; i++) {
			for (int j = cols - 2; j < cols; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	else {
		for (int i = pair.row - 1; i < pair.row + 2; i++) {
			for (int j = pair.col - 1; j < pair.col + 2; j++) {
				if (search[i][j] == cha) {
					if (counter == count) {
						Pair p;
						p.row = i;
						p.col = j;
						return p;
					}
					counter++;
				}
			}
		}
	}
	Pair bad;
	bad.row = -1;
	bad.col = -1;
	return bad;
}

void read_part_1(ifstream &inputfile, ofstream &outputfile)
{
	// TODO: Part1 : Create stack
	Stack stack;
	int n;
	char sort;
	inputfile >> n;
	Pair bad;
	bad.row = -1;
	bad.col = -1;
	for (int i = 0; i < n; i++) {
		inputfile >> sort;
		if (sort == 'i') {
			Pair p;
			inputfile >> p.row >> p.col;
			stack.push(p);
		}
		if (sort == 'p') {
			Pair p = stack.pop();
			if (p.row == bad.row && p.col == bad.col) {
				outputfile << "empty\n";
			}
			else {
				outputfile << p.row << " " << p.col << "\n";
			}
		}
	}
}

void read_part_2(ifstream &inputfile, ofstream &outputfile)
{
	//TODO: Part 2: Run the word search
	Stack stack;
	int rows;
	int cols;
	inputfile >> rows >> cols;
	char **search;
	search = new char*[rows];
	for (int i = 0; i < rows; i++) {
		search[i] = new char[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			inputfile >> search[i][j];
		}
	}
	string word;
	getline(inputfile, word);
	getline(inputfile, word);
	int c = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (search[i][j] == word[0]) {
				c++;
			}
		}
	}
	if (c == 0) {
		outputfile << "not found\n";
		return;
	}
	Pair pairs[c];
	c = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (search[i][j] == word[0]) {
				Pair p;
				p.row = i;
				p.col = j;
				pairs[c] = p;
				c++;
			}
		}
	}
	int w_count = 1;
	int count = 0;
	Pair bad;
	bad.row = -1;
	bad.col = -1;
	for (int i = 0; i < c; i++) {
		stack.push(pairs[i]);
		Pair p = pairs[i];
		while (1) {
			if (w_count == word.length()) {
				Pair fin[w_count];
				for (int j = w_count - 1; j > -1; j--) {
					Pair add;
					add.row = stack.head->data.row;
					add.col = stack.head->data.col;
					fin[j] = add;
					stack.pop();
				}
				for (int j = 0; j < w_count; j++) {
					outputfile << fin[j].row << " " << fin[j].col << "\n";
				}
				return;
			}
			p = find(word.at(w_count), stack.head->data, search, rows, cols, count);
			if (p.row == bad.row && p.col == bad.col && w_count == 1) {
				stack.pop();
				count = 0;
				break;
			}
			else if (p.row == bad.row && p.col == bad.col) {
				stack.pop();
				w_count--;
				count++;
			}
			else {
				stack.push(p);
				w_count++;
				count = 0;
			}
		}
	}
	outputfile << "not found\n";
}

void read_part_3(ifstream &inputfile, ofstream &outputfile)
{
	//TODO: Part 3: Circular double ended queue
	Deque deque;
	int length;
	char cmd;
	int num;
	inputfile >> length;
	for (int i = 0; i < length; i++) {
		inputfile >> cmd;
		if (cmd == 'e') {
			inputfile >> cmd;
			if (cmd == 'f') {
				inputfile >> num;
				deque.enqueue_front(num);
			}
			else {
				inputfile >> num;
				deque.enqueue_back(num);
			}
		}
		else if (cmd == 'd') {
			inputfile >> cmd;
			if (cmd == 'f') {
				if (deque.items == 0) {
					outputfile << "empty\n";
				}
				else {
					int n = deque.dequeue_front();
					outputfile << n << "\n";
				}
			}
			else {
				if (deque.items == 0) {
					outputfile << "empty\n";
				}
				else {
					int n = deque.dequeue_back();
					outputfile << n << "\n";
				}
			}
		}
		else {
			outputfile << deque.print_array_size() << " " <<
			deque.print_front_index() << " " <<
			deque.print_rear_index() << "\n";
		}
	}
}


int main(int argc, char *argv[])
{
	// Read in the test case
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(argv[1]);
	outputfile.open(argv[2]);

	string str;

	getline(inputfile, str);
	int part;
	stringstream convert(str);
	convert >> part;

	switch(part)
	{
		case 1:
			read_part_1(inputfile, outputfile);
			break;
		case 2:
			read_part_2(inputfile, outputfile);
			break;
		case 3:
			read_part_3(inputfile, outputfile);
			break;
	}

	return 0;
}
