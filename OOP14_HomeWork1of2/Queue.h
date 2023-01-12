#pragma once
#include <iostream>
using namespace std;

// it's common queue
class Queue {
	int* Wait; 
	int MaxQueueLenght; 
	int QueueLenght; 

public:
	Queue(int m); 
	~Queue(); 
	void add(int c); // add element
	int extract(); // get element
	void clear(); // clear all queue
	bool isEmpty(); // it's empty or not
	bool isFull();  // it's full or not
	int getCount(); // number of elements
	void show(); // show all queue
};


void Queue::show() {
	for (int i = 0; i < QueueLenght; i++) {
		cout << Wait[i] << " ";
	}
	cout << endl;
}

Queue::~Queue() {
	delete[] Wait;
}

Queue::Queue(int m) {
	MaxQueueLenght = m;
	Wait = new int[MaxQueueLenght];
}

bool Queue::isEmpty() {
	return QueueLenght == 0;
}

bool Queue::isFull() {
	return QueueLenght == MaxQueueLenght;
}

int Queue::getCount() {
	return QueueLenght;
}

void Queue::add(int c) {
	if (!isFull()) Wait[QueueLenght++] = c;
}

int Queue::extract() {
	if (!isEmpty()) {
		int temp = Wait[0];
		for (int i = 1; i < QueueLenght; i++) {
			Wait[i - 1] = Wait[i];
		}
		QueueLenght--;
		return temp;
	}
	else return -1;
}

void Queue::clear() {
	QueueLenght = 0;
}