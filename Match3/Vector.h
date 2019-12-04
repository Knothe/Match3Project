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
};

template<class T>
Vector<T>::Vector() {
	size = 0;
	capacity = 1;
	arr = new T[capacity];
}

template<class T>
Vector<T>::Vector(int size) {
	size = size;
	capacity = size;
	arr = new T[capacity];
}

template<class T>
T Vector<T>::GetAt(unsigned int index) {
	if (index < size)
		return arr[index];
	else
		throw MessageException("Index out of the array");
}

template<class T>
void Vector<T>::PushBack(T val) {
	if (size >= capacity) 
		CopyNewVector(capacity * 2);

	arr[size] = val;
	size++;
}

template<class T>
void Vector<T>::Clear() {
	size = 0;
	capacity = 1;
	delete arr;
	arr = new T[capacity];
}

template <class T>
void Vector<T>::TightVector() {
	if (capacity > size) 
		CopyNewVector(size);
	
}

template <class T>
void Vector<T>::CopyNewVector(int newSize) {
	T* newArr = new T[newSize];
	if (newSize >= size) {
		for (int i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
	}
	capacity = newSize;
	delete arr;
	arr = newArr;
}

template<class T>
int Vector<T>::GetSize() {
	return size;
}

template<class T>
void Vector<T>::Print() {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << std::endl;
	}
	std::cout << "Size: " << size << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
}

template<class T>
bool Vector<T>::hasValue(T val) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == val)
			return true;
	}
	return false;
}