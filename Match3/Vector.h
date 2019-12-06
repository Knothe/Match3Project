#pragma once
#include <iostream>
#include "MessageException.h"

template<class T>
class Vector
{
private:
	T* arr;
	int size;
	int capacity;
	void CopyNewVector(int newSize);

public:
	Vector();
	Vector(int size);
	T GetAt(unsigned int index);
	void PushBack(T val);
	void Clear();
	void TightVector();
	int GetSize();
	void Print();
	bool hasValue(T val);
	void PushAt(int pos, T val);
};
/*
Stats class with capacity = 0 and size = 0
*/
template<class T>
Vector<T>::Vector() {
	size = 0;
	capacity = 1;
	arr = new T[capacity];
}
/*
Starts with a set size and capacity
@param size: starting size of the vector
*/
template<class T>
Vector<T>::Vector(int size) {
	this->size = size;
	capacity = size;
	arr = new T[capacity];
	for (int i = 0; i < size; i++) {
		arr[i] = NULL;
	}
}
/*
Return value in a position inside the bounds of the size
@param index: position in the vector
@return value
*/
template<class T>
T Vector<T>::GetAt(unsigned int index) {
	if (index < size)
		return arr[index];
	else
		throw MessageException("Index out of the array");
}
/*
Increments the size of the vector and adds a value at the end
@param val: value to add
*/
template<class T>
void Vector<T>::PushBack(T val) {
	if (size >= capacity) 
		CopyNewVector(capacity * 2);

	arr[size] = val;
	size++;
}
/*
Clears the vector and defines the capacity = 0
*/
template<class T>
void Vector<T>::Clear() {
	size = 0;
	capacity = 1;
	delete arr;
	arr = new T[capacity];
}
/*
Sets the capacity equal to the size of the vector
*/
template <class T>
void Vector<T>::TightVector() {
	if (capacity > size) 
		CopyNewVector(size);
	
}
/*
Sets new size for the vector
If the new size is bigger the data stays
If the new size is smaller the data is deleted
*/
template <class T>
void Vector<T>::CopyNewVector(int newSize) {
	T* newArr = new T[newSize];
	if (newSize >= size) {
		for (int i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
	}
	capacity = newSize;
	arr = newArr;
}
/*
Returns vector size
*/
template<class T>
int Vector<T>::GetSize() {
	return size;
}
/* 
TODO: Remember to delete later
*/
template<class T>
void Vector<T>::Print() {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << std::endl;
	}
	std::cout << "Size: " << size << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
}
/*
Searchs for a specific value
@param val: value to search
@return true if exists, false if not
*/
template<class T>
bool Vector<T>::hasValue(T val) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == val)
			return true;
	}
	return false;
}
/*
*/
template<class T>
void  Vector<T>::PushAt(int pos, T val) {
	if (pos < size) {
		arr[pos] = val;
	}
}
