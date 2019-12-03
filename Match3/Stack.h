#pragma once
#include "NodoS.h"

template<class T>
class Stack
{
private:
	NodoS<T>* first;
	int size;
public:
	Stack();
	~Stack();
	void Push(T val);
	void Pop();
	void Clear();
	int GetSize();
	T Top();
};


template<class T>
Stack<T>::Stack() {
	first = NULL;
	size = 0;
}

template<class T>
Stack<T>::~Stack() {

}

template<class T>
void Stack<T>::Push(T val) {
	size++;
	NodoS<T>* n = new NodoS<T>(val);
	n->next = first;
	first = n;
}

template<class T>
void Stack<T>::Pop() {
	if (size > 1) {
		first = first->next;
		size--;
	}
	else {
		size = 0;
		first = NULL;
	}
}

template<class T>
void Stack<T>::Clear() {
	size = 0;
	first = NULL;
}

template<class T>
int Stack<T>::GetSize() {
	return size;
}

template<class T>
T Stack<T>::Top() {
	return first->value;
}