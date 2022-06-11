#include <iostream>

using namespace std;

class Deque
{
	public:
		Deque();
		void enqueue_front(int);
		void enqueue_back(int);
		int dequeue_front();
		int dequeue_back();
		int print_array_size();
		int print_front_index();
		int print_rear_index();
		int size;
		int *array;
		int items;
		int f_index;
		int b_index;
};

