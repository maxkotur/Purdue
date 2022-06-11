#include <iostream>
#include "circular_deque.h"

using namespace std;

Deque::Deque()
{
	//TODO: Write the Deque constructor
	//NOTE: Start with an array of size 2!
	array[2];
	size = 2;
	items = 0;
	f_index = -1;
	b_index = -1;
}

void Deque::enqueue_front(int n)
{
	//TODO: Front enqueue method
	if (items == size) {
		int *add = new int[size * 2];
		int j = 0;
		for (int i = f_index; i < size - f_index; i++) {
			add[j] = array[i];
			j++;
		}
		for (int i = 0; i < f_index; i++) {
			add[j] = array[i];
			j++;
		}
		f_index = 0;
		b_index = size - 1;
		size *= 2;
		array = add;
	}
	if (f_index == -1 && b_index == -1) {
		array[0] = n;
		f_index = 0;
		b_index = 0;
		items++;
		return;
	}
	if (f_index == 0) {
		array[size - 1] = n;
		f_index = size - 1;
		items++;
		return;
	}
	f_index--;
	array[f_index] = n;
	items++;
}

void Deque::enqueue_back(int n)
{
	//TODO: Back enqueue
	if (items == size) {
		int *add = new int[size * 2];
		int j = 0;
		for (int i = f_index; i < size - f_index; i++) {
			add[j] = array[i];
			j++;
		}
		for (int i = 0; i < f_index; i++) {
			add[j] = array[i];
			j++;
		}
		f_index = 0;
		b_index = size - 1;
		size *= 2;
		array = add;
	}
	if (f_index == -1 && b_index == -1) {
		array[0] = n;
		f_index = 0;
		b_index = 0;
		items++;
		return;
	}
	if (b_index == size - 1) {
		array[0] = n;
		b_index = 0;
		items++;
		return;
	}
	b_index++;
	array[b_index] = n;
	items++;
}

int Deque::dequeue_front()
{
	//TODO: front dequeue
	if (f_index == size - 1) {
		f_index = 0;
		items--;
		return array[size - 1];
	}
	f_index++;
	items--;
	return array[f_index - 1];
}

int Deque::dequeue_back()
{
	//TODO: back dequeue
	if (b_index == 0) {
		b_index = size - 1;
		items--;
		return array[0];
	}
	b_index--;
	items--;
	return array[b_index + 1];
}

int Deque::print_array_size()
{
	//TODO: get the size of the allocated array
	return size;
}

int Deque::print_front_index()
{
	//TODO: get the front index
	return f_index;
}

int Deque::print_rear_index()
{
	//TODO: get the rear index
	return b_index;
}
