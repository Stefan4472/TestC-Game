#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

// simple stack implementation backed by an array

template <class T>
class StackList {
	T* elements = 0;
	int numElements = 0;
	int capacity = 0;
	
	public:
		// create a new stack with given capacity
		//StackList(int size);
		// add element to the top of the stack
		void push(T elem);
		// remove and return the top element
		T pop();
		// return the top element
		T peek();
		// return element at given index TODO: OVERRIDE WITH []
		T get(int index);
		// set element at given index
		void set(int index, T elem);
		// return number of elements in the stack
		int size();
		// clear the elements out of the stack
		void clear();
		// destroy the stack
		//~StackList();
};
#endif