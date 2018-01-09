#include "stack_list.h"

/*template<class T>
StackList<T>::StackList(int size)
{
	capacity = size;
	//elements = malloc(size * sizeof(T));
	elements = new T[capacity];
}*/

template <class T>
void StackList<T>::push(T elem)
{
	if (numElements == capacity)
	{
		// allocate twice as much space
		T larger_list = new T[2 * capacity];
		// TODO: USE MEMCOPY
		for (int i = 0; i < capacity; i++)
		{
			larger_list[i] = elements[i];	
		}
		delete[] elements;
		elements = larger_list;
		capacity *= 2;
	}
	elements[numElements] = elem;
	numElements++;
}

template <class T>
T StackList<T>::pop()
{
	size--;
	return elements[numElements];
}

template <class T>
T StackList<T>::peek()
{
	return elements[numElements - 1];
}

template <class T>
T StackList<T>::get(int index)
{
	return elements[index]; 	
}

template <class T>
void StackList<T>::set(int index, T elem)
{
	elements[index] = elem;	
}

template <class T>
int StackList<T>::size()
{
	return numElements;	
}

template <class T>
void StackList<T>::clear()
{
	numElements = 0;	
}
	
/*template <class T>
StackList<T>::~StackList<T>()
{
	delete[] elements;	
	elements = 0;
}*/